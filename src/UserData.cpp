#include "UserData.h"

userData *loadUserData()
{
    /*�����û����ݣ��ؽ�Ϊ��������ͷָ��*/
    userData *head, *ptr;
    FILE *user_file = fopen("user.dat", "rb");
    if (!user_file)
    {
        /*�ж��Ƿ�����û������ļ������򴴽��ļ�*/
        FILE *user_file = fopen("user.dat", "wb");
        fclose(user_file);
        return NULL;
    }
    head = (userData *)malloc(sizeof(userData));
    if (fread(head, sizeof(userData), 1, user_file) == 0)
    {
        /*�ж��ļ��Ƿ�������ݣ����򷵻�NULL*/
        fclose(user_file);
        return NULL;
    }
    ptr = head;
    ptr->next = (userData *)malloc(sizeof(userData));
    while (fread(ptr->next, sizeof(userData), 1, user_file))
    {
        ptr = ptr->next;
        ptr->next = (userData *)malloc(sizeof(userData));
    }
    ptr->next = NULL;
    fclose(user_file);
    return head;
}

userData *searchUserData(userData *head, char *name)
{
    /*�������в���ָ���û������û����ݣ�����ָ��*/
    if (head == NULL)
    {
        return NULL;
    }
    userData *ptr = head;
    while (ptr != NULL)
    {
        if (!strcmp(ptr->username, name))
        {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

void addUserData(userData *head, userData data)
{
    /*Ϊ�ڴ��е�������ļ��е��û��������������*/
    userData *ptr, *temp;
    FILE *user_file = fopen("user.dat", "ab+");
    *temp = data;
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
        fwrite(head, sizeof(userData), 1, user_file);
        fclose(user_file);
        return;
    }
    ptr = head;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = temp;
    fwrite(temp, sizeof(userData), 1, user_file);
    fclose(user_file);
}

void updateUserHighestScore(userData *head, userData *user, int new_highest_score)
{
    if (head == NULL)
    {
        return;
    }
    // �ҵ���Ӧ���û�
    userData *ptr = head;
    while (ptr != NULL)
    {
        if (strcmp(ptr->username, user->username) == 0)
        {
            // ������߷�
            ptr->highest_score = new_highest_score;
            break;
        }
        ptr = ptr->next;
    }
    if (ptr == NULL)
    {
        return;
    }
    // �����º������д���ļ�
    FILE *user_file = fopen("user.dat", "wb");
    if (!user_file)
    {
        return;
    }
    ptr = head;
    while (ptr != NULL)
    {
        fwrite(ptr, sizeof(userData), 1, user_file);
        ptr = ptr->next;
    }
    fclose(user_file);
}