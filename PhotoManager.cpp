/*************************************************************************
	> File Name: PhotoManage.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 15 Apr 2022 11:11:05 PM CST
 ************************************************************************/

#include <bits/stdc++.h>
using namespace std;
#include "PhotoManager.h"

void PhotoManager::Start(){
    return ;
}
void PhotoManager::Proc(){
    return ;
}
void PhotoManager::Resatrt(){
    return ;
}
void PhotoManager::Shutdown(){
    return ;
}
int PhotoManager::CreatePhoto(int user_id){
    for(int i=0;i<photo_count_;i++){
		if(photos_[i].user_id()==user_id){
			return PHOTO_EXIST;
		}
	}
    if(photo_count_ > 10239){
        return PHOTO_TOO_MUCH;
    } 
    photos_[photo_count_].set_user_id(user_id);
    photos_[photo_count_].set_last_publisher_id(0);
    photo_count_++;
    return SUCCESS;
}
PhotoInfo* PhotoManager::GetPhoto(int user_id){
    for(int i = 0; i < photo_count_; i++){
        if(photos_[i].user_id() == user_id){
            return &photos_[i];
        } 
    }
    return NULL; 
}
int PhotoManager::UpdatePhoto(int user_id, int publish_id, int publish_time, int publish_message_id){
    PhotoInfo* photo = GetPhoto(user_id);
    if(photo == NULL){
        printf("photo is null\n");
        return PHOTO_NOT_EXIT;
    }
    printf("update %d publisher %d\n",user_id,publish_id);
    photo->set_last_publisher_id(publish_id);
    return SUCCESS;
}
