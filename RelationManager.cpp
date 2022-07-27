/*************************************************************************
	> File Name: RelationManager.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 15 Apr 2022 08:39:08 AM CST
 ************************************************************************/

#include <bits/stdc++.h>
#include "RelationManager.h"

void RelationManager::Start(){
    return ;
}
void RelationManager::Restart(){
    return ;
}
void RelationManager::Shutdown(){
    return ;
}
void RelationManager::Proc(){
    return ;
}
int RelationManager::UserRelationInit(int user_id){
    for(int i=0;i<relation_count_;i++){
		if(relations_[i].user_id()==user_id){
			return RELATION_EXIST;
		}
	}
    if(relation_count_ < 10239){
        relations_[relation_count_].set_user_id(user_id);
        relation_count_++;
        return SUCCESS;
    }else{
        return RELATION_TOO_MUCH;
    }
}
RelationInfo* RelationManager::GetRelation(int user_id){
    for(int i = 0; i < relation_count_;i++){
        if(relations_[i].user_id() == user_id){
            return &relations_[i];
        }
    } 
    return NULL; 
}
int RelationManager::AddFriend(int user_id, int other_id){
    RelationInfo* relation =GetRelation(user_id);
    if(relation == NULL){
        return RELATION_NOT_EXIST;
    }
    int ret = relation->AddFriend(other_id);
    return ret;
}
int RelationManager::DelFriend(int user_id, int other_id){
    RelationInfo* relation = GetRelation(user_id);
    if(relation == NULL){
        return RELATION_NOT_EXIST;
    }
    int ret = relation->DelFriend(other_id);
    return ret;
    
}
