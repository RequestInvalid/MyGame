#include "GameEngine.h"
#pragma comment(lib, "MSIMG32.LIB") //导入外部依赖项

extern GameStatus Status;
extern userData *user;

void mainEngin()
{
    /*主引擎*/
    ExMessage action;
    setbkmode(TRANSPARENT);
    while (1)
    {
        Sleep(10); //休眠0.01秒（设置帧率为100fps）
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