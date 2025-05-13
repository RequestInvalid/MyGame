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

void updateUserHighestScore(int newHighestScore, UserData *user)
{
    /*�����û�����߷���*/
    UserData *head = loadUserData();
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
            ptr->highestScore = newHighestScore;
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

void saveGame(int lastLevel, int lastScore, UserData **user)
{
    /*�浵*/
    if (user == NULL)
        return;

    (*user)->lastLevel = lastLevel;

    // ��ȡ�����û����ݵ�����
    UserData *head = loadUserData();
    if (head == NULL)
        return;

    // �ҵ���Ӧ�û�������lastLevel
    UserData *ptr = head;
    while (ptr != NULL)
    {
        if (strcmp(ptr->username, (*user)->username) == 0)
        {
            ptr->lastLevel = lastLevel;
            ptr->lastScore = lastScore;
            break;
        }
        ptr = ptr->next;
    }

    // ���������ļ�
    FILE *user_file = fopen("user.dat", "wb");
    if (!user_file)
        return;

    ptr = head;
    while (ptr != NULL)
    {
        fwrite(ptr, sizeof(UserData), 1, user_file);
        ptr = ptr->next;
    }
    fclose(user_file);
}