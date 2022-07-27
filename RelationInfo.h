#include "string.h"
#include "common/macro.h"

class RelationInfo{
private:
    GETSETVAR(int, user_id)
    int friend_list_[10240];
    GETSETVAR(int, friend_count)
    int black_list_[10240];
    GETSETVAR(int, black_count)
public:
    int CheckFriend(int other_id);
    int CheckBlack(int other_id);
    int AddFriend(int other_id);
    int DelFriend(int other_id);
    int AddBlack(int other_id);
    int DeleteBlac(int other_id);
    int GetFriendByIndex(int index);
    int GetBlackByIndex(int index);
    
};
