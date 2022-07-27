#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include "time.h"

#include "UserManager.h"
#include "RelationManager.h"
#include "MessageManager.h"
#include "PhotoManager.h"
#include "Socket.h"
#include "common/proto.h"
#include "common/ret_value.h"
#include "common/color.h"
#include "common/head.h"
#include "proto/message_define.pb.h"
#include "DbManager.h"
ssp::CommonReq common_req;
ssp::CommonRsp common_rsp;

SspSocket sock;
UserManager user_svr;
RelationManager rela_svr;
MessageManager mess_svr;
PhotoManager photo_svr;
DbManager db_svr;

int main(){
    db_svr.Init();
	user_svr.Start(&db_svr);
	rela_svr.Start();
	mess_svr.Start();
	photo_svr.Start();
	sock.Init();
	sock.SocketInit();
	int server_on=1;
	while(server_on){
		sock.SocketAccept();
		int check_sock=sock.SocketCheckRecv();
		user_svr.Proc();
		rela_svr.Proc();
		mess_svr.Proc();
		photo_svr.Proc();
		int time_now=time(NULL);
		int ret=0;
		if (check_sock==-1){
            usleep(5000); //没有数据则进行休眠
			continue;
		}
		common_req.ParseFromArray(sock.recv_buffer,10240);
		memset(sock.recv_buffer,0,common_req.ByteSize());
		int cmd_id=common_req.header().cmd_type();
		//printf("----[debug]cmd_id:%d\n",cmd_id);
		common_rsp.Clear();//todo 比较放在这里和放在分支下的效率
		common_rsp.mutable_header()->set_ver(common_req.header().ver());
		common_rsp.mutable_header()->set_cmd_type(cmd_id+1);
		switch(cmd_id){
			case REG_REQ:
			{
				common_rsp.mutable_reg_rsp()->Clear();
				int user_id=user_svr.GetUserIdByUserName(common_req.reg_req().user_name().c_str());
                //printf("user name = %s\n", common_req.reg_req().user_name().c_str());
				int ret_value=0;
				if(user_id==USER_NOT_EXIST){
					user_id=user_svr.CreateUser(common_req.reg_req().user_name().c_str(), 
								 				common_req.reg_req().password().c_str(), 
								 				common_req.reg_req().from(), time_now);
				}else{
					ret_value=USER_EXIST;
				}
				common_rsp.mutable_reg_rsp()->set_ret(ret_value);
				common_rsp.mutable_reg_rsp()->set_user_id(user_id);
				common_rsp.SerializeToArray(sock.send_buffer,10240);
				sock.SocketSend(common_rsp.ByteSize());

			}
			break;
			
			case LOGIN_REQ:
			{
				common_rsp.mutable_login_rsp()->Clear();
				ret=user_svr.LoginCheck(common_req.login_req().user_name().c_str(),
										common_req.login_req().password().c_str());
				int user_id=user_svr.GetUserIdByUserName(common_req.login_req().user_name().c_str());
		        int ret1=rela_svr.UserRelationInit(user_id);
				int ret2=photo_svr.CreatePhoto(user_id);	//快照信息的初始化
                DBG(GREEN"[main]" NONE"logincheck=%d rela_create=%d photo_create=%d\n",ret,ret1,ret2);//对值进行检查
				common_rsp.mutable_login_rsp()->set_ret(ret);
				if(ret==SUCCESS){
					common_rsp.mutable_login_rsp()->set_user_id(user_id);
				}
				common_rsp.SerializeToArray(sock.send_buffer,10240);
				sock.SocketSend(common_rsp.ByteSize());
			}
			break;
			case ADD_FRIEND_REQ:
			{
				common_rsp.mutable_add_friend_rsp()->Clear();
				int user_id  = common_req.add_friend_req().user_id();
				int other_id = common_req.add_friend_req().other_id();
				ret=user_svr.CheckExist(user_id);
				if(ret==USER_NOT_EXIST){
					// USER_NOT_EXIST
				}else{
					ret=user_svr.CheckExist(other_id);
					if(ret==USER_EXIST){
						ret=rela_svr.AddFriend(user_id,other_id);
					}else{
						//FRIEND_ID NOT EXIST
					}
				}
				common_rsp.mutable_add_friend_rsp()->set_ret(ret);
				common_rsp.SerializeToArray(sock.send_buffer,10240);
				sock.SocketSend(common_rsp.ByteSize());
			}
			break;
			case PUBLISH_MESSAGE_REQ:
			{
				common_rsp.mutable_publish_message_rsp()->Clear();
				int user_id=common_req.publish_message_req().user_id();
                int mess_id_ret=0;
				ret=user_svr.CheckExist(user_id);
                DBG(GREEN"[main]" NONE" PUBLISH_MESSAGE_REQ : user_id : %d ret = %d\n", user_id, ret);
				if(ret==USER_EXIST){
					MessageInfo message;
					message.set_user_id(user_id);
					message.set_content(common_req.publish_message_req().content().c_str());
					message.set_publish_time(time_now);
					mess_id_ret=mess_svr.PublishMessage(message);
                    DBG(GREEN"[main]" NONE"message_publish = %d content = %s \n", ret, message.content());
				}
                if(mess_id_ret!=MESSAGE_TOO_MUCH){
					RelationInfo* rela_info=rela_svr.GetRelation(user_id);//获取好友消息
					if(rela_info){
						DBG(GREEN"[main]" NONE" friend_count=%d\n",rela_info->friend_count());//可能有多个好友的消息。所以这里是列表的形式
						for(int i=0;i<rela_info->friend_count();i++){
							int friend_id=rela_info->GetFriendByIndex(i);
							photo_svr.UpdatePhoto(friend_id,user_id,time_now,0);//接受者 发送者 发送时间 消息ID
                            DBG(GREEN"[main]" NONE" PUBLISH_MESSAGE_REQ : mess_id_ret : %d", mess_id_ret);
							mess_svr.PushUserMessageId(friend_id,mess_id_ret);//将当前用户ID和发送消息的id进行绑定
						}
					}
				}
				common_rsp.mutable_publish_message_rsp()->set_ret(ret);
				common_rsp.SerializeToArray(sock.send_buffer,10240);
				sock.SocketSend(common_rsp.ByteSize());
			}	
			break;

			case GET_PHOTO_REQ:
			{
				common_rsp.mutable_get_photo_rsp()->Clear();
				int user_id=common_req.get_photo_req().user_id();
				ret=user_svr.CheckExist(user_id);
				if(ret==USER_EXIST){
					PhotoInfo* photo = photo_svr.GetPhoto(user_id);
					if(photo!=NULL){
                        DBG(GREEN"[main]" NONE"last_publisher_id: %d\n",photo->last_publisher_id());
						common_rsp.mutable_get_photo_rsp()->set_last_publisher_id(photo->last_publisher_id());
					}else{
						DBG(RED"[main]" NONE"photo info is null\n");
					}
				}
				common_rsp.mutable_get_photo_rsp()->set_ret(ret);
				common_rsp.SerializeToArray(sock.send_buffer,10240);
				sock.SocketSend(common_rsp.ByteSize());
			}
			break;
			case GET_MESSAGE_LIST_REQ:
			{
				common_rsp.mutable_get_message_list_rsp()->Clear();
				int user_id=common_req.get_message_list_req().user_id();
				ret=user_svr.CheckExist(user_id);
                DBG(GREEN"[in main: get message_list_req]" NONE"user_id = %d ret = %d\n", user_id, ret);
				if(ret==USER_EXIST){
					vector<int> ids=mess_svr.GetMessageIds(user_id);
					for(int i=0;i<ids.size() && i < 10;i++){//限制返回消息的数量
						MessageInfo* message=mess_svr.GetMessage(ids[i]);
                        if(message == NULL){
                            DBG(GREEN"[main]" NONE"message is null\n");
                            continue;
                        }
						ssp::MessageItem* item=common_rsp.mutable_get_message_list_rsp()->add_message_list();
						item->set_publisher_id(message->user_id());
						item->set_publish_time(message->publish_time());
						item->set_content(message->content());
					}
				}
				common_rsp.mutable_get_message_list_rsp()->set_ret(ret);
				common_rsp.SerializeToArray(sock.send_buffer,10240);
				sock.SocketSend(common_rsp.ByteSize());
			}
			break;
			case DEL_FRIEND_REQ:
			{
				common_rsp.mutable_del_friend_rsp()->Clear();
				int user_id  = common_req.del_friend_req().user_id();
				int other_id = common_req.del_friend_req().other_id();
				ret=user_svr.CheckExist(user_id);
				if(ret==USER_NOT_EXIST){
					// USER_NOT_EXIST
				}else{
					ret =user_svr.CheckExist(other_id);
					if(ret==USER_EXIST){
						ret=rela_svr.DelFriend(user_id,other_id);
					}else{
						//FRIEND_ID NOT EXIST
					}
				}
				common_rsp.mutable_del_friend_rsp()->set_ret(ret);
				common_rsp.SerializeToArray(sock.send_buffer,10240);
				sock.SocketSend(common_rsp.ByteSize());
                DBG(GREEN"[main]" NONE"svr send rsp: delete friend user_id = %d other_id = %d\n", user_id, other_id);
			}
			break;
			case SERVER_SHUTDOWN:
			{
				server_on = 0;
			}
			break;
			default:
			break;
		}
		//usleep(5000);
	}
	user_svr.Shutdown();
	rela_svr.Shutdown();
	mess_svr.Shutdown();
	photo_svr.Shutdown();
	return 0;
}
