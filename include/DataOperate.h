#include "Global.h"

#ifndef DATA_OPERATE_H
#define DATA_OPERATE_H

userData *loadUserData();                             //�����û�����Ϊ��������ͷָ��(���ܻ������⣿)
userData *searchUserData(userData *head, char *name); //ͨ���û��������û����ݣ����ؽṹ��ָ��
void addUserData(userData *head, userData data);      //Ϊ�ڴ��е�������ļ��е��û��������������

#endif