/*************************************************************************
	> File Name: Socket.h
	> Author: 
	> Mail: 
	> Created Time: Sat 16 Apr 2022 12:42:23 PM CST
 ************************************************************************/

#ifndef _SOCKET_H
#define _SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "Config.h"
class SspSocket{ //包含了服务端和客户端的地址
public:
    int server_sock;
    struct sockaddr_in server_addr;
    int accept_flag = 0;
    int client_sock;
    struct sockaddr_in client_addr;
   
    char recv_buffer[10240];
    char send_buffer[10240];
    Config config;
    int Init(); 
    int SocketInit();
    int SocketAccept();
    int SocketCheckRecv();
    int SocketSend(int send_size);
    int ClientClose();
    int ServerClose();
    int ClientSocketInit();
    int show_send_buffer(int size);
    int show_recv_buffer(int size);
};
#endif
