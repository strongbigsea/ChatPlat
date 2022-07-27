/*************************************************************************
	> File Name: MessageManager.h
	> Author: 
	> Mail: 
	> Created Time: Fri 15 Apr 2022 10:11:46 PM CST
 ************************************************************************/

#ifndef _MESSAGEMANAGER_H
#define _MESSAGEMANAGER_H
#include <vector>
#include <map>
#include "MessageInfo.h"
#include "common/macro.h"
#include "common/ret_value.h"
using namespace std;
class MessageManager{
private:
    MessageInfo messages_[10240];
    GETSETVAR(int, message_count);
    GETSETVAR(int, cur_message_id);
    map<int, vector<int> > user_messages_;

public:
    void Start();
    void Proc();
    void Restart();
    void Shutdown();
public:
    MessageInfo* GetMessage(int user_id, int message_id); 
    MessageInfo* GetMessage(int message_id); 
    int PublishMessage(MessageInfo message);
    int DeleteMessage(int message_id);
    int PushUserMessageId(int user_id, int message_id);
    vector<int> GetMessageIds(int user_id);
    
};

#endif
