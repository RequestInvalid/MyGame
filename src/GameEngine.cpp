#include "GameEngine.h"
#pragma comment(lib, "MSIMG32.LIB") //导入外部依赖项

extern GameStatus Status;
extern userData *user;

Hook *hook = (Hook *)malloc(sizeof(Hook)); //创建钩子对象
MineLink *minelink = createMineLink(10);   //随机生成矿物

// test
void test()
{
    IMAGE img, img2, img3;
    loadimage(&img, _T("img/largeGold.png"));
    loadimage(&img2, _T("img/midGold.png"));
    loadimage(&img3, _T("img/smallGold.png"));
    TransparentImage(NULL, 100, 100, &img, img.getwidth(), img.getheight(), BLACK);
    TransparentImage(NULL, 200, 200, &img2, img2.getwidth(), img2.getheight(), BLACK);
    TransparentImage(NULL, 300, 300, &img3, img3.getwidth(), img3.getheight(), BLACK);
}

DWORD WINAPI detectKeyPress(LPVOID param)
{
    /*多线程检测按键事件的线程*/
    Hook *hook = (Hook *)param; // 获取传入的钩子对象指针

    while (true)
    {
        // 检测键盘按下事件
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) // 检测下方向键是否按下
        {
            if (hook->state == HOOK_ROTATE) // 仅在钩子处于旋转状态时处理
            {
                hook->state = HOOK_EXTEND;
            }
        }
        // Sleep(10); // 减少 CPU 占用
    }
    return 0;
}

void init(Hook *hook)
{
    initHook(hook);
    countGameTime(true);
    swangHook(hook, true);
    exbandHook(hook, minelink, true);
    backHook(hook, true);
    updateMiner(hook, true);
    drawMine(minelink, true);
}

void mainEngine()
{
    /*主引擎*/
    ExMessage action;
    DWORD currentTime, lastTime;
    HANDLE keyPressThread = CreateThread(NULL, 0, detectKeyPress, hook, 0, NULL); //创建线程检测按键事件
    init(hook);
    lastTime = GetTickCount();
    while (true)
    {
        currentTime = GetTickCount();
        if (currentTime - lastTime >= 10) // 0.01秒刷新一帧
        {
            peekmessage(&action, EM_KEY); //获取消息
            updateData(&action, hook);
            updateGraph();
            flushmessage();
            lastTime = currentTime;
        }
    }
}

void updateData(ExMessage *msg, Hook *hook) //参数msg没用，记得删
{
    if (hook->state == HOOK_EXTEND)
    {
        exbandHook(hook, minelink, false);
    }
    else if (hook->state == HOOK_BACK)
    {
        backHook(hook, false); //钩子收回
    }
    else if (hook->state == HOOK_ROTATE)
    {
        swangHook(hook, false); //钩子旋转
    }
    else
    {
        moveHookAndMine(hook, hook->mine, &minelink);
    }
}

void updateGraph()
{
    BeginBatchDraw();

    EasyPutImage(0, 0, "img/gameBackground.jpg", getwidth(), getheight());
    drawMiner(updateMiner(hook, false));
    displayGameTime(countGameTime(false));
    drawMine(minelink, false);
    drawHook(hook);
    // test();

    FlushBatchDraw();
}