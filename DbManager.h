/*************************************************************************
	> File Name: DbManager.h
	> Author: 
	> Mail: 
	> Created Time: Fri 22 Apr 2022 03:02:12 PM CST
 ************************************************************************/
#ifndef _DBMANAGER_H
#define _DBMANAGER_H
#include <string>
#include <iostream>
#include "mysql/mysql.h"
#include "UserInfo.h"
#include "common/macro.h"
using namespace std;
class DbManager {
private:
    GETSETVAR(int, transection);//初始化时设置隔离
private:
    MYSQL* conn;
    MYSQL_RES *result;
    MYSQL_ROW row;
public:
    int Init();
    int ExecSql(string sql);
    int GetUsersBegin();
    int GetUsersOneByOne(UserInfo *user);
    int GetUsersEnd();
    int GetCurUserId();
    int DbInsertUser(UserInfo *user);
};
#endif
