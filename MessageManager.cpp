/*************************************************************************
	> File Name: MessageManager.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 15 Apr 2022 10:17:53 PM CST
 ************************************************************************/

#include <bits/stdc++.h>
using namespace std;
#include "MessageManager.h"

#include "common/color.h"
#include "common/head.h"


void MessageManager::Start(){
    //todo
    //get message id from db
    set_cur_message_id(10001);
    return ;
}
void MessageManager::Proc(){
    return ;
}
void MessageManager::Restart(){
    return ;
}
void MessageManager::Shutdown(){
    return ;
}
MessageInfo* MessageManager::GetMessage(int user_id, int message_id){
    for(int i = 0; i < message_count_; i++){
        if(messages_[i].user_id() == user_id && messages_[i].message_id() == message_id){
            return &messages_[i];
        }
    }
    return NULL;
}
MessageInfo* MessageManager::GetMessage(int message_id){
    for(int i = 0; i < message_count_; i++){
        DBG(GREEN"<mess>" NONE"messages_[i].message_id() = %d message_id = %d\n", messages_[i].message_id(), message_id);
        if(messages_[i].message_id() == message_id){
            return &messages_[i];
        }
    }
    return NULL;
}
int MessageManager::PublishMessage(MessageInfo message){
    if(message_count_ > 10239){
        return MESSAGE_TOO_MUCH;
    } 
    int ret_mess_id = cur_message_id();
    messages_[message_count_].set_message_id(cur_message_id());
    messages_[message_count_].set_user_id(message.user_id());
    messages_[message_count_].set_publish_time(message.publish_time());
    messages_[message_count_].set_content(message.content());
    cur_message_id_++;
    message_count_++;
    return ret_mess_id;
}
int MessageManager::DeleteMessage(int message_id){
    for(int i = 0; i < message_count_; i++){
        if(messages_[i].message_id() == message_id){
            messages_[i].set_message_id(messages_[message_count_ - 1].message_id());//这里直接使用上一个消息进行了覆盖，但是没有考虑上一个是否存在
            messages_[i].set_user_id(messages_[message_count_ - 1].user_id());
            messages_[i].set_publish_time(messages_[message_count_ - 1].publish_time());
            messages_[i].set_content(messages_[message_count_ - 1].content());
            message_count_--;
            return SUCCESS;
        }
    }
    
    return MESSAGE_NOT_EXIST;
}
int MessageManager::PushUserMessageId(int user_id, int message_id){
    map<int, vector<int> >::iterator iter;
    iter = user_messages_.find(user_id);
    if(iter == user_messages_.end()){//新用发送消息的消息
        vector<int> mess_ids;
        mess_ids.push_back(message_id);
        user_messages_.insert(pair<int, vector<int> >(user_id, mess_ids));
        DBG(GREEN"<mess>" NONE"user_id = %d message_id = %d\n", user_id, message_id);
        return 1;
    }    
    iter->second.push_back(message_id);
    return 0;
}
vector<int> MessageManager::GetMessageIds(int user_id){
    map<int, vector<int> >::iterator iter;
    iter = user_messages_.find(user_id);
    if(iter != user_messages_.end()){
        DBG(GREEN"<mess>" NONE"GetMessageIds: find !\n");
        return iter->second;
    }
    return vector<int>();
}

