#include "GameEngine.h"
#pragma comment(lib, "MSIMG32.LIB") //导入外部依赖项

extern GameStatus Status;
extern userData *user;

boolean isNewGame = true;
Hook *hook = (Hook *)malloc(sizeof(Hook)); //创建钩子对象
MineLink *minelink = createMineLink(20);   //随机生成矿物
int goal = 0;

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

void init(int goal, Hook *hook, MineLink *minelink)
{

    initHook(hook);
    minelink = createMineLink(20); //生成矿物
    countGameTime(0, isNewGame);
    setGoal(&goal, minelink, isNewGame);
    swangHook(hook, isNewGame);
    exbandHook(hook, minelink, isNewGame);
    backHook(hook, isNewGame);
    updateMiner(hook, isNewGame);
    drawMine(minelink, isNewGame);
    if (isNewGame)
    {
        isNewGame = false;
    }
}

void mainEngine()
{
    /*主引擎*/
    ExMessage action;
    DWORD currentTime, lastTime;
    HANDLE keyPressThread = CreateThread(NULL, 0, detectKeyPress, hook, 0, NULL); //创建线程检测按键事件
    lastTime = GetTickCount();
    // setGoal(&goal, minelink, true);
    init(goal, hook, minelink);
    setGoal(&goal, minelink, false);
    while (true)
    {
        if (Status == GAMING)
        {
            currentTime = GetTickCount();
            if (currentTime - lastTime >= 10) // 0.01秒刷新一帧
            {
                peekmessage(&action, EM_KEY); //获取消息
                updateData(hook);
                updateGraph(goal, hook);
                flushmessage();
                lastTime = currentTime;
            }
        }
        else if (Status == WIN)
        {
            EasyPutImage(0, 0, "img/win.jpg", getwidth(), getheight());
            Sleep(3000);
            Status = MAIN_MENU;
            isNewGame = true;
            break;
        }
        else if (Status == LOSE)
        {

            EasyPutImage(0, 0, "img/lose.jpg", getwidth(), getheight());
            Sleep(3000);
            Status = MAIN_MENU;
            isNewGame = true;
            break;
        }
    }
}

void updateData(Hook *hook)
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

void updateGraph(int goal, Hook *hook)
{
    BeginBatchDraw();

    EasyPutImage(0, 0, "img/gameBackground.jpg", getwidth(), getheight());
    drawMiner(updateMiner(hook, false));
    displayGameTime(countGameTime(goal, false));
    displayMoney(countMoney(0, false));
    displayGoal(goal);
    displayLevel(countLevel(0, false, false));
    drawMine(minelink, false);
    drawHook(hook);

    FlushBatchDraw();
}