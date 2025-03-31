#include "GameEngine.h"
#pragma comment(lib, "MSIMG32.LIB") //导入外部依赖项

extern GameStatus Status;
extern userData *user;

Hook *hook = (Hook *)malloc(sizeof(Hook)); //创建钩子对象

void test()
{
    IMAGE img1, img2;
    IMAGE *img3 = updateMiner();
    TransparentImage(NULL, 455, 10, img3, 100, 100, BLACK);
    loadimage(&img1, _T("img/hook.png"));
    swangHook(hook);                                   //钩子旋转
    rotateimage(&img2, &img1, hook->angle * PI / 180); //旋转钩子
    TransparentImage(NULL, hook->x, hook->y, &img2, 71, 40, BLACK);
}

void mainEngine()
{
    /*主引擎*/
    ExMessage action;
    initHook(hook);
    while (1)
    {
        Sleep(10);            //休眠0.01秒（设置帧率为100fps）
        peekmessage(&action); //获取消息
        UpdateGraph(&action);
        flushmessage();
    }
}

void UpdateGraph(ExMessage *action)
{
    BeginBatchDraw();
    EasyPutImage(0, 0, "img/gameBackground.jpg", getwidth(), getheight());
    test();
    FlushBatchDraw();
}