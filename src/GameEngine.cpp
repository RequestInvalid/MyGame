#include "GameEngine.h"
#pragma comment(lib, "MSIMG32.LIB") //导入外部依赖项

extern GameStatus Status;
extern userData *user;

Hook *hook = (Hook *)malloc(sizeof(Hook)); //创建钩子对象

DWORD WINAPI detectKeyPress(LPVOID param)
{
    /*多线程检测按键事件的线程*/
    Hook *hook = (Hook *)param; // 获取传入的钩子对象指针

    while (1)
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

void mainEngine()
{
    /*主引擎*/
    ExMessage action;
    initHook(hook);
    HANDLE keyPressThread = CreateThread(NULL, 0, detectKeyPress, hook, 0, NULL); //创建线程检测按键事件
    while (1)
    {
        Sleep(10);                    //休眠0.01秒（设置帧率为100fps）
        peekmessage(&action, EM_KEY); //获取消息
        updateData(&action, hook);
        updateGraph();
        flushmessage();
    }
}

void updateData(ExMessage *msg, Hook *hook)
{
    if (hook->state == HOOK_EXTEND)
    {
        exbandHook(hook);
    }
    else if (hook->state == HOOK_BACK)
    {
        backHook(hook); //钩子收回
    }
    else if (hook->state == HOOK_ROTATE)
    {
        swangHook(hook); //钩子旋转
    }
}

void updateGraph()
{
    BeginBatchDraw();
    EasyPutImage(0, 0, "img/gameBackground.jpg", getwidth(), getheight());
    drawMiner(updateMiner(hook));
    drawHook(hook);
    FlushBatchDraw();
}