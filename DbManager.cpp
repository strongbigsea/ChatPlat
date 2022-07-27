/*************************************************************************
	> File Name: DbManager.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 22 Apr 2022 03:12:03 PM CST
 ************************************************************************/
#include "DbManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "common/ret_value.h"
using namespace std;
char mysql_user_name[256];
char mysql_password[256];
int DbManager::Init()
{
    FILE* f = fopen("mysql.ini", "r");
    fscanf(f, "%s", mysql_user_name);
    fscanf(f, "%s", mysql_password);
    fclose(f);
    conn = mysql_init(NULL);
    if (conn == NULL) {
        return DB_CONN_INIT_FAIL;
    }
    conn = mysql_real_connect(conn, "112.124.8.48", mysql_user_name, mysql_password, "ssp", 0, NULL, 0);
    if (conn == NULL) {
        return DB_CONN_CONNECT_FAIL;
    }
    return SUCCESS;
}
int DbManager::ExecSql(string sql)
{
    if (mysql_query(conn, sql.c_str())) { //对于其他类型的语句，执行成功时返回TRUE，失败时返回false
        return DB_QUERY_FAIL;
    } else {
        result = mysql_use_result(conn); //先查询是否有结果
        if (result) {
            int field_count = mysql_num_fields(result);
            int row_count = mysql_num_rows(result);
            //printf("rows : %d fields : %d \n", row_count, field_count);
            while (result) { //遍历结果集中的每一行
                row = mysql_fetch_row(result);
                if (row == NULL) {
                    printf("No more data \n");
                    break;
                }
                /*for (int i = 0; i < field_count; i++) { //对每一行的列进行分割
                    printf("%s\t", row[i]);
                }
                printf("\n");*/
            }
            row_count = mysql_num_rows(result);
            printf("rows : %d fields : %d \n", row_count, field_count);
        }
        mysql_free_result(result);
    }

    return 0;
}
int DbManager::GetUsersBegin()
{
    if (transection() == 1) {
        return DB_BUSY;
    }
    set_transection(1);
    int ret = mysql_query(conn, "select * from tb_user;");
    if (ret) {//失败返回非0 
        set_transection(0);
        return DB_QUERY_FAIL;
    }
    result = mysql_use_result(conn);
    return 0;
}
int DbManager::GetUsersOneByOne(UserInfo* user)
{
    if (result) {
        row = mysql_fetch_row(result);
        if (row == NULL) {
            return DB_NO_MORE_DATA;
        }
        // row[0] = user_id  row[1] = user_info, protobuf
        ssp::UserInfoBase pb_user;
        char user_info[10240];
        int len=strlen(row[1]);
		for(int i=0;i<len/2;i++){
			user_info[i]=(row[1][2*i]-'a')*16+(row[1][2*i+1]-'a');//将两位合并为一位 拼装
		}
        int ret = pb_user.ParseFromArray(user_info, 10240);
        //printf("from base %s, %d\n", user_info, ret);
        user->FromPb(pb_user);
    } else {
        return DB_NO_MORE_DATA;
    }
    return SUCCESS;
}
int DbManager::GetUsersEnd()
{
    set_transection(0);
    mysql_free_result(result);
    return 0;
}
int DbManager::GetCurUserId()
{
    int user_id = 10001;
    int ret = mysql_query(conn, "select value from tb_var where key_str = 'user_id';");
    if (ret) {
        printf("query failed with cur_id : %d\n", ret);
        return user_id;
    } else {
        result = mysql_use_result(conn);
        if (result) {
            row = mysql_fetch_row(result);
            if (row == NULL) {
                printf("result is null with cur_user_id \n");
                return user_id;
            }
            sscanf(row[0], "%d", &user_id);//这里的user_id 会随着用户的更新而发生改变
        }
        mysql_free_result(result);
    }
    return user_id;
}

int DbManager::DbInsertUser(UserInfo *user){//向数据库中插入用户
    ssp::UserInfoBase pb_user;
    user->ToPb(pb_user);
    printf("user    password: %s\n",user->password());
	printf("pb_user password: %s\n",pb_user.password().c_str());
    char user_id[256];
    sprintf(user_id, "%d", user->user_id());
    char user_info[10240];
    pb_user.SerializeToArray(user_info, 10240);
    char user_info2[10240];
    for(int i=0;i<pb_user.ByteSize();i++){
		int l=user_info[i]&0x000f;
		int h=(user_info[i]&0x00f0)>>4;
        user_info2[i*2]=h+'a';//防止出现0 被截断。对原来user_infoz转换
		user_info2[i*2+1]=l+'a';//将原来的一位变为了两位
	}
    string insertSql="insert into tb_user values ('";//数据库插入语句。字符串的拼接
	insertSql+=user_id;
	insertSql+="','";
	insertSql+=user_info2;
	insertSql+="')";
	//printf("insert: %s\n",insertSql.c_str());
	int ret=mysql_query(conn,insertSql.c_str());
    if(ret==0){
		return SUCCESS;
	}else{
		printf("insert user failed : %d\n",ret);
		return DB_QUERY_FAIL;
	}
    return SUCCESS;
}
