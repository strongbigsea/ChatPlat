/*************************************************************************
	> File Name: BusManager.h
	> Author: 
	> Mail: 
	> Created Time: Wed 27 Jul 2022 09:24:43 AM CST
 ************************************************************************/

#ifndef _BUSMANAGER_H
#define _BUSMANAGER_H
#include "Channel.h"
class BusManager{
    private:
        Channel channel_[4];
    public:
        Init();
        int CheckRecf(int self_id);
        char* Recv(int from,int to);
        int Send(int from,int to, char* dat);
};
#endif
