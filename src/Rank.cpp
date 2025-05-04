#include "Rank.h"

extern GameStatus Status;

void displayRank()
{
    /* չʾ���а� */
    cleardevice();
    IMAGE rankBackground;
    loadimage(&rankBackground, _T("img/rankBackground.jpg"), GAME_WIDTH, GAME_HEIGHT);
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
    userData *head = loadUserData();
    if (head == NULL)
    {
        outtextxy(300, 200, _T("�����������"));
        Sleep(3000);
        Status = MAIN_MENU;
        return;
    }

    // ���û����ݰ���߷�����
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

    // ��ʾ���а�
    int y = 100;
    outtextxy(300, 50, _T("���а�"));
    ptr = sortedList;
    int rank = 1;
    TCHAR buffer[50];
    while (ptr != NULL && rank <= 10) // ֻ��ʾǰ 10 ��
    {
        _stprintf(buffer, _T("�� %d ��: %s - ��߷�: %d"), rank, ptr->username, ptr->highest_score);
        outtextxy(200, y, buffer);
        y += 40;
        rank++;
        ptr = ptr->next;
    }

    // �ͷ���������
    while (sortedList != NULL)
    {
        userData *temp = sortedList;
        sortedList = sortedList->next;
        free(temp);
    }

    // �������˵�
    Sleep(5000);
    Status = MAIN_MENU;
}