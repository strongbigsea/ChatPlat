/*************************************************************************
	> File Name: Socket.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 16 Apr 2022 12:47:36 PM CST
 ************************************************************************/
#include <bits/stdc++.h>
#include  "Socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
int SspSocket::Init(){
    accept_flag = 0;
    printf("socketinit~\n");
    config.ReadConfig();
    return 0;
}
int SspSocket::SocketInit(){
    server_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(config.socket_port());
    server_addr.sin_addr.s_addr = inet_addr(config.socket_addr());
    int con_ret = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)); 
    if(con_ret < 0){
        //printf("bind failef !");
        return con_ret;
    }
    listen(server_sock, 10000);
    return 0; 
}
int SspSocket::ClientSocketInit(){
    client_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(config.socket_port());
    server_addr.sin_addr.s_addr = inet_addr(config.socket_addr());
    int con_ret = connect(client_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(con_ret < 0){
        printf("connect failed !\n");
        return con_ret;
    }
    accept_flag = 1;//客户端连接, 代表默认是可以连接的 
    return 0;
}
int SspSocket::SocketAccept(){
    if(accept_flag == 1){//如果已连接，就不会阻塞，直接返回
        return 0;
    }
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    accept_flag = 1;
    return 0;
}
int SspSocket::SocketCheckRecv(){
    if(accept_flag == 0) return -1;
    int ret = recv(client_sock, recv_buffer, 10240,0); 
    if(ret > 0){
        return ret;
    }else{
        return -1;
    }
    return 0;
}
int SspSocket::SocketSend(int send_size){
    int ret = send(client_sock, send_buffer, send_size, 0);
    memset(send_buffer, 0, send_size);
    if(ret < 0){//发送不通，关闭客户端的连接套接字
        ClientClose();
        return -1;
    }
    return 0;
}
int SspSocket::ServerClose(){
    close(server_sock); 
    accept_flag = 0;//标志位置0 
    return 0;    
}
int SspSocket::ClientClose(){
    close(client_sock); 
    return 0;    
}
int SspSocket::show_send_buffer(int size){
    for(int i = 0; i < size; i++){
        int l4 = send_buffer[i] & 0x000f;
        int h4 = (send_buffer[i] >> 4) & 0x000f;
        int l0 = l4 & 0x0001;
        l4 >>= 1;
        int l1 = l4 & 0x0001;
        l4 >>= 1;
        int l2 = l4 & 0x0001;
        l4 >>= 1;
        int l3 = l4 & 0x0001;
        int h0 = h4 & 0x0001;
        h4 >>= 1;
        int h1 = h4 & 0x0001;
        h4 >>= 1;
        int h2 = h4 & 0x0001;
        h4 >>= 1;
        int h3 = h4 & 0x0001;
        printf("%2x %d%d%d%d %d%d%d%d %3d", send_buffer[i], h3, h2, h1, h0, l3, l2, l1, l0, send_buffer[i]);
        if('0' <= send_buffer[i] && send_buffer[i] <= '9') printf("'%c'", send_buffer[i]);
        if('a' <= send_buffer[i] && send_buffer[i] <= 'z') printf("'%c'", send_buffer[i]);
        if('A' <= send_buffer[i] && send_buffer[i] <= 'Z') printf("'%c'", send_buffer[i]);
        printf("\n");
    } 
    return 0;
}
int SspSocket::show_recv_buffer(int size){
     for(int i = 0; i < size; i++){
        int l4 = send_buffer[i] & 0x000f;
        int h4 = (send_buffer[i] >> 4) & 0x000f;
        int l0 = l4 & 0x0001;
        l4 >>= 1;
        int l1 = l4 & 0x0001;
        l4 >>= 1;
        int l2 = l4 & 0x0001;
        l4 >>= 1;
        int l3 = l4 & 0x0001;
        int h0 = h4 & 0x0001;
        h4 >>= 1;
        int h1 = h4 & 0x0001;
        h4 >>= 1;
        int h2 = h4 & 0x0001;
        h4 >>= 1;
        int h3 = h4 & 0x0001;
        printf("%2x %d%d%d%d %d%d%d%d %3d", send_buffer[i], h3, h2, h1, h0, l3, l2, l1, l0, send_buffer[i]);
        if('0' <= send_buffer[i] && send_buffer[i] <= '9') printf("'%c'", send_buffer[i]);
        if('a' <= send_buffer[i] && send_buffer[i] <= 'z') printf("'%c'", send_buffer[i]);
        if('A' <= send_buffer[i] && send_buffer[i] <= 'Z') printf("'%c'", send_buffer[i]);
        printf("\n");
    } 
    return 0;
}
