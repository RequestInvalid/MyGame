#include "GameEngine.h"
#pragma comment(lib, "MSIMG32.LIB") //�����ⲿ������

extern GameStatus Status;
extern userData *user;

void mainEngin()
{
    /*������*/
    ExMessage action;
    setbkmode(TRANSPARENT);
    while (1)
    {
        Sleep(10); //����0.01�루����֡��Ϊ100fps��
        // action = getmessage();
        UpdateGraph(&action);
        flushmessage();
    }
}

void UpdateGraph(ExMessage *action)
{
    int static tempX = 100;
    BeginBatchDraw();
    IMAGE background, gold;
    loadimage(&background, _T("img/gameBackground.jpg"), getwidth(), getheight());
    loadimage(&gold, _T("img/largeGold.png"), 100, 100);
    putimage(0, 0, &background);
    TransparentImage(NULL, tempX++, 100, &gold, BLACK);
    FlushBatchDraw();
}