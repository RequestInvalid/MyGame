#include "Rank.h"

extern GameStatus Status;

void displayRank()
{
    /* 展示排行榜 */
    cleardevice();
    IMAGE rankBackground;
    loadimage(&rankBackground, _T("img/rankBackground.jpg"), GAME_WIDTH, GAME_HEIGHT);
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
    userData *head = loadUserData();
    if (head == NULL)
    {
        outtextxy(300, 200, _T("暂无玩家数据"));
        Sleep(3000);
        Status = MAIN_MENU;
        return;
    }

    // 将用户数据按最高分排序
    userData *sortedList = NULL;
    userData *ptr = head;
    while (ptr != NULL)
    {
        userData *newNode = (userData *)malloc(sizeof(userData));
        *newNode = *ptr;
        newNode->next = NULL;

        if (sortedList == NULL || newNode->highest_score > sortedList->highest_score)
        {
            newNode->next = sortedList;
            sortedList = newNode;
        }
        else
        {
            userData *temp = sortedList;
            while (temp->next != NULL && temp->next->highest_score >= newNode->highest_score)
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
    outtextxy(300, 50, _T("排行榜"));
    ptr = sortedList;
    int rank = 1;
    TCHAR buffer[50];
    while (ptr != NULL && rank <= 10) // 只显示前 10 名
    {
        _stprintf(buffer, _T("第 %d 名: %s - 最高分: %d"), rank, ptr->username, ptr->highest_score);
        outtextxy(200, y, buffer);
        y += 40;
        rank++;
        ptr = ptr->next;
    }

    // 释放排序链表
    while (sortedList != NULL)
    {
        userData *temp = sortedList;
        sortedList = sortedList->next;
        free(temp);
    }

    // 返回主菜单
    Sleep(5000);
    Status = MAIN_MENU;
}