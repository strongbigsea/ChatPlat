/*************************************************************************
	> FileName: 2client.cpp
	> Author  : Li Chao
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Socket.h"
#include "common/proto.h"
#include "proto/message_define.pb.h"

#define GOTO_NEXT if(ret==0){phase++;}  //重复使用的部分直接定义宏 节约逻辑里面的代码
#define GOTO_LOGIN if(ret==0){phase=5;}
#define GET_OUT if(ret==0){phase=999;}
#define WAIT_RSP_GO_NEXT ret=RecvRsp();GOTO_NEXT
#define WAIT_RSP_GO_LOGIN ret=RecvRsp();GOTO_LOGIN
#define WAIT_RSP_GET_OUT ret=RecvRsp();GET_OUT
#define CHECK_SERVER_ON if(ret<0){ \
							printf("Server Not Ready\n"); \
							return 0; \
						}

#define SEND common_req.SerializeToArray(sock.send_buffer,common_req.ByteSize());\
	int ret=sock.SocketSend(common_req.ByteSize());\
	send_count++;\
	return ret;

int send_count=0;
int recv_count=0;

ssp::CommonReq common_req;
ssp::CommonRsp common_rsp;

SspSocket sock;

int Register(const char *user_name,const char *password){
	common_req.Clear();
	common_req.mutable_header()->set_ver(1);
	common_req.mutable_header()->set_cmd_type(REG_REQ);
	common_req.mutable_reg_req()->set_user_name(user_name);
	common_req.mutable_reg_req()->set_password(password);
	common_req.mutable_reg_req()->set_from(1);
	SEND
}
int Login(const char *user_name,const char* password){
	common_req.Clear();
	common_req.mutable_header()->set_ver(1);
	common_req.mutable_header()->set_cmd_type(LOGIN_REQ);
	common_req.mutable_login_req()->set_user_name(user_name);
	common_req.mutable_login_req()->set_password(password);
	SEND
}
int AddFriend(int user_id,int other_id){//加好友
	common_req.Clear();
	common_req.mutable_header()->set_ver(1);
	common_req.mutable_header()->set_cmd_type(ADD_FRIEND_REQ);
	common_req.mutable_add_friend_req()->set_user_id(user_id);
	common_req.mutable_add_friend_req()->set_other_id(other_id);//用压测工具不断区调优的时侯方便去测，所以这里做成接口形式。
	SEND
}
int DelFriend(int user_id,int other_id){
	common_req.Clear();
	common_req.mutable_header()->set_ver(1);
	common_req.mutable_header()->set_cmd_type(DEL_FRIEND_REQ);
	common_req.mutable_del_friend_req()->set_user_id(user_id);
	common_req.mutable_del_friend_req()->set_other_id(other_id);
	SEND
}
int PublishMessage(int user_id,const char * content){
	common_req.Clear();
	common_req.mutable_header()->set_ver(1);
	common_req.mutable_header()->set_cmd_type(PUBLISH_MESSAGE_REQ);
	common_req.mutable_publish_message_req()->set_user_id(user_id);
	common_req.mutable_publish_message_req()->set_content(content);
	SEND
}
int GetPhoto(int user_id){
	common_req.Clear();
	common_req.mutable_header()->set_ver(1);
	common_req.mutable_header()->set_cmd_type(GET_PHOTO_REQ);
	common_req.mutable_get_photo_req()->set_user_id(user_id);
	SEND
}
int GetMessageList(int user_id){
	common_req.Clear();
	common_req.mutable_header()->set_ver(1);
	common_req.mutable_header()->set_cmd_type(GET_MESSAGE_LIST_REQ);
	common_req.mutable_get_message_list_req()->set_user_id(user_id);
	SEND
}
int ShutDown(){
	common_req.Clear();
	common_req.mutable_header()->set_ver(1);
	common_req.mutable_header()->set_cmd_type(SERVER_SHUTDOWN);
	common_req.SerializeToArray(sock.send_buffer,common_req.ByteSize());//进行序列化
	int ret=sock.SocketSend(common_req.ByteSize());
	return ret;
}
int RecvRsp(){
	int ret=sock.SocketCheckRecv();
	if(ret>0){
		common_rsp.ParseFromArray(sock.recv_buffer,10240);
		int cmd_type=common_rsp.header().cmd_type();
		recv_count++;
		if(recv_count>0)return 0;
		switch(cmd_type){
			case REG_RSP:
				printf("Receive Reg Rsp\n");
				printf("ret    : %d\n",common_rsp.reg_rsp().ret());
				printf("user_id: %d\n",common_rsp.reg_rsp().user_id());
			break;
			case LOGIN_RSP:
				printf("Receive Login Rsp\n");
				printf("ret    : %d\n",common_rsp.login_rsp().ret());
				printf("user_id: %d\n",common_rsp.login_rsp().user_id());
			break;
			case ADD_FRIEND_RSP:
				printf("Receive AddFriend Rsp\n");
				printf("ret    : %d\n",common_rsp.add_friend_rsp().ret());
			break;
			case DEL_FRIEND_RSP:
				printf("Receive DelFriend Rsp\n");
				printf("ret    : %d\n",common_rsp.del_friend_rsp().ret());
			break;
			case PUBLISH_MESSAGE_RSP:
				printf("Receive PublishMessage Rsp\n");
				printf("ret    : %d\n",common_rsp.publish_message_rsp().ret());
			break;
			case GET_PHOTO_RSP:
				printf("Receive GetPhoto Rsp\n");
				printf("ret    : %d\n",common_rsp.get_photo_rsp().ret());
			break;
			case GET_MESSAGE_LIST_RSP:
				printf("Receive GetMessageList Rsp\n");
				printf("ret    : %d\n",common_rsp.get_message_list_rsp().ret());
			break;
			default:
			break;
		}
	}
	return 0;
}
int main(){
	int ret;
	ret=sock.Init();
	ret=sock.ClientSocketInit();
	CHECK_SERVER_ON//宏定义
	int client_on=1;
	int phase=1;//定义不同的阶段
	int time_begin=time(NULL);
	printf("----[debug]begin_time:%d\n",time_begin);
	while(client_on){
		int time_now=time(NULL);
		//printf("----[debug]now_time:%d\n",time_now);
		if(time_now-time_begin>60){//如果时间大于60秒，则自动退出
			printf("----[debug]end_time:%d\n",time_now);
			printf("----[debug]send %d %d\n----[debug]recv %d %d\n",
		  			send_count,send_count/60,
		  			recv_count,recv_count/60);
			phase=999;
		}
		//printf("----[debug]phase=%d\n",phase);
		switch(phase){
			case 1:
				ret=Register("hank1234","12345678");
				GOTO_NEXT
				break;
			case 2:
				WAIT_RSP_GO_NEXT
				break;
			case 3:
				ret=Register("hank5678","88888888");
				GOTO_NEXT
				break;
			case 4://等待服务端关闭
				//WAIT_RSP_GET_OUT
				WAIT_RSP_GO_NEXT
				break;
			case 5:
				ret=Login("hank1234","12345678");
				GOTO_NEXT
				break;
			case 6:
				WAIT_RSP_GO_NEXT
				break;
			case 7:
				ret=Login("hank5678","88888888");
				GOTO_NEXT
				break;
			case 8:
				WAIT_RSP_GO_NEXT
				break;
			case 9:
				ret=AddFriend(10001,10002);
				GOTO_NEXT
				break;
			case 10:
				WAIT_RSP_GO_NEXT
				break;
			case 11:
				ret=PublishMessage(10002,"Hank Is Here");
				GOTO_NEXT
				break;
			case 12:
				WAIT_RSP_GO_NEXT
				break;
			case 13:
				ret=GetPhoto(10001);
				GOTO_NEXT
				break;
			case 14:
				WAIT_RSP_GO_NEXT
				break;
			case 15:
				ret=GetMessageList(10001);
				GOTO_NEXT
				break;
			case 16:
				WAIT_RSP_GO_NEXT
				break;
			case 17:
				DelFriend(10001,10002);
				GOTO_NEXT
				break;
			case 18:
				//WAIT_RSP_GO_NEXT
				WAIT_RSP_GO_LOGIN
				break;
			default:
				ret=ShutDown();
				GOTO_NEXT
				client_on=0;
			break;
		}
		//usleep(5000);
	}

	sock.ClientClose();
	return 0;
}
