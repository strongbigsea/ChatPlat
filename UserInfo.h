#ifndef USER_INFO
#define USER_INFO
#include "string.h"
#include "common/macro.h"
#include "proto/user_info_base.pb.h"
class UserInfo {
public:
    int FromPb(ssp::UserInfoBase &pb_user);
    int ToPb(ssp::UserInfoBase &pb_user);
private:
    GETSETVAR(int, user_id)
    GETSETSTR(256, user_name)//专门定义字符串类型的宏
    GETSETSTR(256, nick_name)
    GETSETVAR(int, reg_time)
    GETSETVAR(int, from)
    GETSETVAR(int, login_time)
    GETSETVAR(int, last_login_time)
    GETSETVAR(int, fresh_time)
    GETSETSTR(256, password)
    GETSETVAR(int, logout_time)
    GETSETVAR(int, db_flag)
};
#endif