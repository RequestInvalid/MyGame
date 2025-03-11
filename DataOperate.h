#include "Global.h"

userData *loadUserData();                             //加载用户数据为链表，返回头指针(可能还有问题？)
userData *searchUserData(userData *head, char *name); //通过用户名查找用户数据，返回结构体指针
void addUserData(userData *head, userData data);      //为内存中的链表和文件中的用户数据添加新数据