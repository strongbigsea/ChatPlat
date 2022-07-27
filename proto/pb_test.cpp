/*************************************************************************
	> File Name: pb_test.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 17 Apr 2022 12:12:53 PM CST
 ************************************************************************/

#include "test.pb.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace ssp;
int isalpha(char ch){
    if(ch >= '0' && ch <= '9') return 1;
    if(ch >= 'a' && ch <= 'z') return 1;
    if(ch >= 'A' && ch <= 'Z') return 1;
    if(ch == '_') return 1;
    return 0;
}
void hexprint(char ch){
    if(isalpha(ch) == 2){
        printf("%d  %c\n", ch, ch);
    }else{
        int b1, b2, b3, b4, b5, b6, b7, b8;
        b8 = ch & 1;
        b7 = (ch >> 1) & 1;
        b6 = (ch >> 2) & 1;
        b5 = (ch >> 3) & 1;
        b4 = (ch >> 4) & 1;
        b3 = (ch >> 5) & 1;
        b2 = (ch >> 6) & 1;
        b1 = (ch >> 7) & 1;
        printf("%d %c %d%d%d%d %d%d%d%d\n",ch, ch, b1, b2, b3, b4, b5, b6, b7, b8);//打印每一位
    }
}
int main(){
    ssp::UserInfoBase ui;
    ui.set_ver(1);
    ui.set_user_id(10001);
    ui.set_user_name("hank1234");
    ui.set_password("12345678");
    ui.set_max_num(63);
    printf("%d %d %s %s\n",ui.ver(), ui.user_id(), ui.user_name().c_str(),ui.password().c_str());
    char buffer[1024];
    ui.SerializeToArray(buffer, 1024);//序列化到数组里面
    int len = strlen(buffer);
    printf("buffer: %d   %s\n", len, buffer);
    for(int i = 0; i < len; i++){
        hexprint(buffer[i]);
    }
    return 0;
}

