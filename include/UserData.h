#include "Global.h"

#ifndef DATA_OPERATE_H
#define DATA_OPERATE_H

UserData *loadUserData();                                                           //加载用户数据为链表，返回头指针(可能还有问题？)
UserData *searchUserData(UserData *head, char *name);                               //通过用户名查找用户数据，返回结构体指针
void addUserData(UserData *head, UserData data);                                    //为内存中的链表和文件中的用户数据添加新数据
void updateUserHighestScore(UserData *head, UserData *user, int new_highest_score); //更新用户的最高分数

#endif