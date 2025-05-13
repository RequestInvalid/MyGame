#include "Rank.h"

extern GameStatus Status;

void displayRank()
{
    /* չʾ���а� */
    // cleardevice();
    IMAGE rankBackground;
    loadimage(&rankBackground, _T("img/rank.jpg"), GAME_WIDTH, GAME_HEIGHT);
    putimage(0, 0, &rankBackground);

    // ����������ʽ
    LOGFONT f;
    settextstyle(30, 0, _T("����"));
    setbkmode(TRANSPARENT);
    gettextstyle(&f);
    f.lfQuality = ANTIALIASED_QUALITY;
    f.lfWeight = FW_BOLD;
    settextcolor(WHITE);
    settextstyle(&f);

    // �����û�����
    UserData *head = loadUserData();
    if (head == NULL)
    {
        outtextxy(385, 200, _T("�����������"));
        Sleep(3000);
        Status = MAIN_MENU;
        return;
    }

    // ���û����ݰ���߷�����
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

    // ��ʾ���а�
    int y = 100;
    ptr = sortedList;
    int rank = 1;
    TCHAR buffer[50];
    while (ptr != NULL && rank <= 10) // ֻ��ʾǰ 10 ��
    {
        _stprintf(buffer, _T("�� %d ��: %s - ��߷�: %d"), rank, ptr->username, ptr->highestScore);
        outtextxy(200, y, buffer);
        y += 40;
        rank++;
        ptr = ptr->next;
    }

    // �ͷ���������
    while (sortedList != NULL)
    {
        UserData *temp = sortedList;
        sortedList = sortedList->next;
        free(temp);
    }

    // �������˵�
    Sleep(5000);
    Status = MAIN_MENU;
}