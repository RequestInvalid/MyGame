#include "UserData.h"

UserData *loadUserData()
{
    /*加载用户数据，重建为链表，返回头指针*/
    UserData *head, *ptr;
    FILE *user_file = fopen("user.dat", "rb");
    if (!user_file)
    {
        /*判断是否存在用户数据文件，否则创建文件*/
        FILE *user_file = fopen("user.dat", "wb");
        fclose(user_file);
        return NULL;
    }
    head = (UserData *)malloc(sizeof(UserData));
    if (fread(head, sizeof(UserData), 1, user_file) == 0)
    {
        /*判断文件是否存在数据，否则返回NULL*/
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
    /*在链表中查找指定用户名的用户数据，返回指针*/
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
    /*为内存中的链表和文件中的用户数据添加新数据*/
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
    // 找到对应的用户
    UserData *ptr = head;
    while (ptr != NULL)
    {
        if (strcmp(ptr->username, user->username) == 0)
        {
            // 更新最高分
            ptr->highest_score = new_highest_score;
            break;
        }
        ptr = ptr->next;
    }
    if (ptr == NULL)
    {
        return;
    }
    // 将更新后的链表写入文件
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
