#include "Global.h"

#ifndef DATA_OPERATE_H
#define DATA_OPERATE_H

UserData *loadUserData();                                         //�����û�����Ϊ��������ͷָ��(���ܻ������⣿)
UserData *searchUserData(UserData *head, char *name);             //ͨ���û��������û����ݣ����ؽṹ��ָ��
void addUserData(UserData *head, UserData data);                  //Ϊ�ڴ��е�������ļ��е��û��������������
void updateUserHighestScore(int newHighestScore, UserData *user); //�����û�����߷���
void saveGame(int lastLevel, int lastScore, UserData **user);     //�浵

#endif