/*************************************************************************
	> FileName: PhotoManager.cpp
	> Author  : Li Chao
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PhotoManager.h"
#include "common/ret_value.h"

void PhotoManager::Start(){}
void PhotoManager::Proc(){}
void PhotoManager::Shutdown(){}
void PhotoManager::Restart(){}

int PhotoManager::CreatePhoto(int user_id){
	if(photo_count_==10239){
		return PHOTO_TOO_MUCH;
	}
	photos_[photo_count_].set_user_id(user_id);
	photos_[photo_count_].set_last_publisher_id(0);
	photo_count_++;
	return SUCCESS;
}
PhotoInfo* PhotoManager::GetPhoto(int user_id){
	for(int i=0;i<photo_count_;i++){
		if(photos_[i].user_id()==user_id){
			return &photos_[i];
		}
	}
	return NULL;
}

int PhotoManager::UpdatePhoto(int user_id,int publisher_id,int publish_time,int publish_message_id){
	PhotoInfo* photo=GetPhoto(user_id);
	if(photo==NULL){
		return PHOTO_NOT_EXIST;
	}
	photo->set_last_publisher_id(publisher_id);
	return SUCCESS;
}

