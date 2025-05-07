#include "Rank.h"

extern GameStatus Status;

void displayRank()
{
    /* 展示排行榜 */
    // cleardevice();
    IMAGE rankBackground;
    loadimage(&rankBackground, _T("img/rank.jpg"), GAME_WIDTH, GAME_HEIGHT);
    putimage(0, 0, &rankBackground);

    // 设置字体样式
    LOGFONT f;
    settextstyle(30, 0, _T("楷体"));
    setbkmode(TRANSPARENT);
    gettextstyle(&f);
    f.lfQuality = ANTIALIASED_QUALITY;
    f.lfWeight = FW_BOLD;
    settextcolor(WHITE);
    settextstyle(&f);

    // 加载用户数据
    UserData *head = loadUserData();
    if (head == NULL)
    {
        outtextxy(385, 200, _T("暂无玩家数据"));
        Sleep(3000);
        Status = MAIN_MENU;
        return;
    }

    // 将用户数据按最高分排序
    UserData *sortedList = NULL;
    UserData *ptr = head;
    while (ptr != NULL)
    {
        UserData *newNode = (UserData *)malloc(sizeof(UserData));
        *newNode = *ptr;
        newNode->next = NULL;

        if (sortedList == NULL || newNode->highestScore > sortedList->highestScore)
        {
            newNode->next = sortedList;
            sortedList = newNode;
        }
        else
        {
            UserData *temp = sortedList;
            while (temp->next != NULL && temp->next->highestScore >= newNode->highestScore)
            {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
        ptr = ptr->next;
    }

    // 显示排行榜
    int y = 100;
    ptr = sortedList;
    int rank = 1;
    TCHAR buffer[50];
    while (ptr != NULL && rank <= 10) // 只显示前 10 名
    {
        _stprintf(buffer, _T("第 %d 名: %s - 最高分: %d"), rank, ptr->username, ptr->highestScore);
        outtextxy(200, y, buffer);
        y += 40;
        rank++;
        ptr = ptr->next;
    }

    // 释放排序链表
    while (sortedList != NULL)
    {
        UserData *temp = sortedList;
        sortedList = sortedList->next;
        free(temp);
    }

    // 返回主菜单
    Sleep(5000);
    Status = MAIN_MENU;
}