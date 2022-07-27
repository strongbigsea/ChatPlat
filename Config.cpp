/*************************************************************************
	> File Name: Config.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 16 Apr 2022 01:50:30 PM CST
 ************************************************************************/

#include "Config.h"
#include "stdio.h"
#include "string.h"
int Config::ReadConfig(){
    FILE* f = fopen("config.ini","r");
    if(f == NULL){
        return -1;
    }
    while(1){
        char config_line[256];
        if(fscanf(f, "%s",config_line) == EOF){
            break;
        }
        if(strstr(config_line, "socket_addr") != NULL){
            char scaddr[256];
            sscanf(config_line, "socket_addr=%s",scaddr); 
            printf("socket_addr=%s\n", scaddr);
            set_socket_addr(scaddr); 
        }
        if(strstr(config_line, "socket_port") != NULL){
            int port;
            sscanf(config_line, "socket_port=%d",&port);
            printf("port=%d\n", port);
            set_socket_port(port);
        }
    }
    fclose(f);
    return 0;
}
