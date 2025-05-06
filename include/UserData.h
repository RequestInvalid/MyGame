#include "Global.h"

#ifndef DATA_OPERATE_H
#define DATA_OPERATE_H

UserData *loadUserData();                                                           //�����û�����Ϊ��������ͷָ��(���ܻ������⣿)
UserData *searchUserData(UserData *head, char *name);                               //ͨ���û��������û����ݣ����ؽṹ��ָ��
void addUserData(UserData *head, UserData data);                                    //Ϊ�ڴ��е�������ļ��е��û��������������
void updateUserHighestScore(UserData *head, UserData *user, int new_highest_score); //�����û�����߷���

#endif