/*************************************************************************
	> File Name: ret_value.h
	> Author: 
	> Mail: 
	> Created Time: Thu 14 Apr 2022 10:53:48 PM CST
 ************************************************************************/

#ifndef _RET_VALUE_H
#define _RET_VALUE_H

#define SUCCESS 0

#define USER_NOT_EXIST 100
#define USER_EXIST 101
#define WRONG_PASSWORD 102
#define USER_TOO_MUCH 103

#define NOT_FRIEND  200
#define ALREADY_RRIEND  201
#define FRIEND_TOO_MUCH  202
#define FRIEND_INDEX_WRONG  203
#define RELATION_EXIST 204
#define NOT_BLACK 211

#define RELATION_TOO_MUCH 220
#define RELATION_NOT_FRIEND 221
#define RELATION_EXIT 222
#define RELATION_NOT_EXIST 223

#define MESSAGE_TOO_MUCH 301 
#define MESSAGE_NOT_EXIST 302

#define PHOTO_NOT_EXIT 400
#define PHOTO_TOO_MUCH 401
#define PHOTO_EXIST 402


#define FLAG_INSERT 501
#define FLAG_DELETE 502
#define FLAG_UPDATE 503

#define DB_CONN_INIT_FAIL 601 
#define DB_CONN_CONNECT_FAIL 602
#define DB_QUERY_FAIL 603
#define DB_BUSY 604
#define DB_NO_MORE_DATA 605
#endif


