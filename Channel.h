/*************************************************************************
	> File Name: Channel.h
	> Author: 
	> Mail: 
	> Created Time: Wed 27 Jul 2022 09:28:44 AM CST
 ************************************************************************/

#ifndef _CHANNEL_H
#define _CHANNEL_H
#include "./common/macro.h"
#include "BusBlock.h"

class Channel{
    public:
        char* name;
        int from, to;
        BusBlock block;
};
#endif
