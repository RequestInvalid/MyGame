#include "GameEngine.h"
#pragma comment(lib, "MSIMG32.LIB") //导入外部依赖项

extern GameStatus Status;
extern userData *user;

boolean isNewGame = true;
Hook *hook = (Hook *)malloc(sizeof(Hook)); //创建钩子对象
MineLink *minelink;
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
        Sleep(10); // 减少 CPU 占用
    }
    return 0;
}

void init(int *goal, Hook *hook, MineLink **minelink)
{

    if (isNewGame)
    {
        srand(42); //重设种子状态
        initHook(hook);
        *minelink = createMineLink(20); //生成矿物
        countGameTime(0, true);
        countMoney(0, isNewGame);
        countLevel(isNewGame, false);
        setGoal(goal, *minelink, isNewGame);
        swangHook(hook, isNewGame);
        exbandHook(hook, *minelink, isNewGame);
        backHook(hook, isNewGame);
        updateMiner(hook, isNewGame);
        drawMine(*minelink, isNewGame);
        isNewGame = false;
    }
    else
    {
        initHook(hook);
        *minelink = createMineLink(20); //生成矿物
        setGoal(goal, *minelink, isNewGame);
        countGameTime(0, true);
        countLevel(isNewGame, true);
        swangHook(hook, isNewGame);
        exbandHook(hook, *minelink, isNewGame);
        backHook(hook, isNewGame);
    }
    goalScene(*goal);
}

void mainEngine()
{
    /*主引擎*/
    ExMessage action;
    DWORD currentTime, lastTime;
    HANDLE keyPressThread = CreateThread(NULL, 0, detectKeyPress, hook, 0, NULL); //创建线程检测按键事件
    lastTime = GetTickCount();
    init(&goal, hook, &minelink); //初始化组件状态
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
            Status = GAMING;
            break;
        }
        else if (Status == LOSE)
        {

            EasyPutImage(0, 0, "img/lose.jpg", getwidth(), getheight());
            Sleep(3000);
            //更新用户的最高记录
            if (user->highest_score < countMoney(0, false))
            {
                userData *head = loadUserData(); //加载用户数据
                updateUserHighestScore(head, user, countMoney(0, false));
            }
            Status = MAIN_MENU;
            isNewGame = true; //更改新游戏状态为真
            break;
        }
    }
}

void updateData(Hook *hook)
{
    /*更新游戏数据*/
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
    /*更新画面*/
    BeginBatchDraw();

    EasyPutImage(0, 0, "img/gameBackground.jpg", getwidth(), getheight());
    drawMiner(updateMiner(hook, false));
    displayGameTime(countGameTime(goal, false));
    displayMoney(countMoney(0, false));
    displayGoal(goal);
    displayLevel(countLevel(false, false));
    drawMine(minelink, false);
    drawHook(hook);

    FlushBatchDraw();
}

void goalScene(int goal)
{
    LOGFONT f;
    settextstyle(55, 0, _T("楷体"));
    setbkmode(TRANSPARENT);
    gettextstyle(&f);
    f.lfQuality = ANTIALIASED_QUALITY;
    f.lfWeight = FW_LIGHT;
    settextcolor(RGB(0, 100, 0)); //设置金钱数量的颜色为深绿色
    settextstyle(&f);
    TCHAR str[6];
    _stprintf(str, _T("$%d"), goal);
    EasyPutImage(0, 0, "img/goal.jpg", getwidth(), getheight());
    outtextxy(250, 230, str);
    Sleep(2000);
}