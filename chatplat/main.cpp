/*************************************************************************
	> FileName: main.cpp
	> Author  : Li Chao
 ************************************************************************/

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
			continue;
		}
		common_req.ParseFromArray(sock.recv_buffer,10240);
		memset(sock.recv_buffer,0,common_req.ByteSize());
		int cmd_id=common_req.header().cmd_type();
		printf("----[debug]cmd_id:%d\n",cmd_id);
		common_rsp.Clear();//todo 比较放在这里和放在分支下的效率
		common_rsp.mutable_header()->set_ver(common_req.header().ver());
		common_rsp.mutable_header()->set_cmd_type(cmd_id+1);
		switch(cmd_id){
			case REG_REQ:
			{
				common_rsp.mutable_reg_rsp()->Clear();
				int user_id=user_svr.GetUserIdByUserName(common_req.reg_req().user_name().c_str());
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
				common_rsp.mutable_login_rsp()->Clear();//发送请求之前把接收到的缓存清空
				ret=user_svr.LoginCheck(common_req.login_req().user_name().c_str(),
										common_req.login_req().password().c_str());
				
				int user_id=user_svr.GetUserIdByUserName(common_req.login_req().user_name().c_str());
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
				ret=user_svr.CheckExist(user_id);
				if(ret==USER_EXIST){
					MessageInfo message;
					message.set_user_id(user_id);
					message.set_content(common_req.publish_message_req().content().c_str());
					message.set_publish_time(time_now);
					ret=mess_svr.PublishMessage(message);
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
						common_rsp.mutable_get_photo_rsp()->set_last_publisher_id(photo->last_publisher_id());
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
				if(ret==USER_EXIST){
					vector<int> ids=mess_svr.GetMessageIds(user_id);//获取消息列表
					for(int i=0;i<ids.size();i++){
						MessageInfo* message=mess_svr.GetMessage(ids[i]);//获取每条消息
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
