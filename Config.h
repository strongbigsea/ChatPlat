/*************************************************************************
	> File Name: Config.h
	> Author: 
	> Mail: 
	> Created Time: Sat 16 Apr 2022 01:48:03 PM CST
 ************************************************************************/

#ifndef _CONFIG_H
#define _CONFIG_H
#include "common/macro.h"
class Config{
private:
    GETSETVAR(int, socket_port)
    GETSETSTR(256, socket_addr)
public:
    int ReadConfig();
};
#endif
