/*************************************************************************
	> File Name: dbmain.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 22 Apr 2022 03:54:15 PM CST
 ************************************************************************/
#include "DbManager.h"
#include <bits/stdc++.h>
DbManager db_svr;
using namespace std;
int main()
{
    db_svr.Init();
    //db_svr.ExecSql("delete from tb_user;");
    //db_svr.ExecSql("insert into tb_user values ('10001', 'hank1');");
    //db_svr.ExecSql("insert into tb_user values ('10002', 'hank2');");
    //db_svr.ExecSql("insert into tb_user values ('10003', 'hank3');");
    db_svr.ExecSql("select * from tb_user;");
    return 0;
}

