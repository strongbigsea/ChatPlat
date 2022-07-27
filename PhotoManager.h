/*************************************************************************
	> File Name: PhotoManage.h
	> Author: 
	> Mail: 
	> Created Time: Fri 15 Apr 2022 11:05:20 PM CST
 ************************************************************************/

#ifndef _PHOTOMANAGE_H
#define _PHOTOMANAGE_H
#include "common/macro.h"
#include "common/ret_value.h"
#include "PhotoInfo.h"
class PhotoManager{
private:
    PhotoInfo photos_[10240]; 
    GETSETVAR(int, photo_count)
    
public:
    void Start();
    void Proc();
    void Resatrt();
    void Shutdown();
public:
    int CreatePhoto(int user_id);
    PhotoInfo* GetPhoto(int user_id);
    int UpdatePhoto(int user_id, int publish_id, int publish_time, int publish_message_id);
    int GetPhotoUserId();

};
#endif
