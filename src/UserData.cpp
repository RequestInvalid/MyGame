#include "UserData.h"

UserData *loadUserData()
{
    /*�����û����ݣ��ؽ�Ϊ��������ͷָ��*/
    UserData *head, *ptr;
    FILE *user_file = fopen("user.dat", "rb");
    if (!user_file)
    {
        /*�ж��Ƿ�����û������ļ������򴴽��ļ�*/
        FILE *user_file = fopen("user.dat", "wb");
        fclose(user_file);
        return NULL;
    }
    head = (UserData *)malloc(sizeof(UserData));
    if (fread(head, sizeof(UserData), 1, user_file) == 0)
    {
        /*�ж��ļ��Ƿ�������ݣ����򷵻�NULL*/
        fclose(user_file);
        return NULL;
    }
    ptr = head;
    ptr->next = (UserData *)malloc(sizeof(UserData));
    while (fread(ptr->next, sizeof(UserData), 1, user_file))
    {
        ptr = ptr->next;
        ptr->next = (UserData *)malloc(sizeof(UserData));
    }
    ptr->next = NULL;
    fclose(user_file);
    return head;
}

UserData *searchUserData(UserData *head, char *name)
{
    /*�������в���ָ���û������û����ݣ�����ָ��*/
    if (head == NULL)
    {
        return NULL;
    }
    UserData *ptr = head;
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

void addUserData(UserData *head, UserData data)
{
    /*Ϊ�ڴ��е�������ļ��е��û��������������*/
    UserData *ptr, *temp;
    FILE *user_file = fopen("user.dat", "ab+");
    *temp = data;
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
        fwrite(head, sizeof(UserData), 1, user_file);
        fclose(user_file);
        return;
    }
    ptr = head;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = temp;
    fwrite(temp, sizeof(UserData), 1, user_file);
    fclose(user_file);
}

void updateUserHighestScore(UserData *head, UserData *user, int new_highest_score)
{
    if (head == NULL)
    {
        return;
    }
    // �ҵ���Ӧ���û�
    UserData *ptr = head;
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
        fwrite(ptr, sizeof(UserData), 1, user_file);
        ptr = ptr->next;
    }
    fclose(user_file);
}
