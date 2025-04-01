#include "GameEngine.h"
#pragma comment(lib, "MSIMG32.LIB") //导入外部依赖项

extern GameStatus Status;
extern userData *user;

Hook *hook = (Hook *)malloc(sizeof(Hook)); //创建钩子对象

void test()
{
    IMAGE *img3 = updateMiner();
    TransparentImage(NULL, 455, 10, img3, 100, 100, BLACK);
    swangHook(hook); //更新钩子状态
    IMAGE img1, img2;

    // 加载原始图片
    loadimage(&img1, _T("img/hook.png"));
    int srcWidth = img1.getwidth();
    int srcHeight = img1.getheight();

    // 创建足够大的目标图像
    img2.Resize(hook->sizeX, hook->sizeY);

    // 旋转图片
    rotateimage(&img2, &img1, hook->angle * PI / 180, BLACK, true, true);

    // 使用透明方式显示旋转后的图片
    TransparentImage(NULL, hook->x, hook->y, &img2, hook->sizeX, hook->sizeY, BLACK);
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