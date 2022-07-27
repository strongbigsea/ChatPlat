/*************************************************************************
	> File Name: RelationManager.h
	> Author: 
	> Mail: 
	> Created Time: Fri 15 Apr 2022 08:31:40 AM CST
 ************************************************************************/

#ifndef _RELATIONMANAGER_H
#define _RELATIONMANAGER_H
#include "RelationInfo.h"
#include "common/macro.h"
#include "common/ret_value.h"
class RelationManager{
private:
    RelationInfo relations_[10240];
    GETSETVAR(int, relation_count)
public:
    void Start();
    void Proc();
    void Restart();
    void Shutdown();

public:
    int UserRelationInit(int user_id);//用户刚开始是需要进行初始化的,刚开始没有好友信息
    RelationInfo* GetRelation(int user_id);
    int AddFriend(int user_id, int other_id);
    int DelFriend(int user_id, int other_id);
    //add black to to
    //DelBlack() to do 
    
};
#endif
