#include "GameEngine.h"

extern GameStatus Status;
extern UserData *user;

bool isNewGame = true;
Hook *hook = (Hook *)malloc(sizeof(Hook)); //创建钩子对象
MineLink *minelink;
int goal = 0;

DWORD WINAPI detectKeyPress(LPVOID param)
{
    /*多线程检测按键事件的线程*/
    Hook *hook = (Hook *)param; // 获取传入的钩子对象指针
    ExMessage mouse;

    while (true)
    {
        peekmessage(&mouse, EM_MOUSE);
        // 检测键盘按下事件
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) // 检测下方向键是否按下
        {
            if (hook->state == HOOK_ROTATE) // 仅在钩子处于旋转状态时处理
            {
                hook->state = HOOK_EXTEND;
                PlaySound(_T("sounds/extend.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
        }
        else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000 || (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && determineMouse(mouse, 740, 30, 810, 80)))
        {
            if (Status == GAMING)
            {
                Status = PAUSE;
            }
        }
        flushmessage(EM_MOUSE);
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
        extendHook(hook, *minelink, isNewGame);
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
        extendHook(hook, *minelink, isNewGame);
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
                flushmessage(EM_KEY);
                lastTime = currentTime;
            }
        }
        else if (Status == PAUSE)
        {
            gamePause();
        }
        else if (Status == WIN)
        {
            EasyPutImage(0, 0, "img/win.jpg", GAME_WIDTH, GAME_HEIGHT);
            PlaySound(_T("sounds/win.wav"), NULL, SND_FILENAME | SND_ASYNC);
            Sleep(4000);
            Status = GAMING;
            break;
        }
        else if (Status == LOSE)
        {
            loseScene();
            break;
        }
        else if (Status == MAIN_MENU)
        {
            break;
        }
    }
}

void updateData(Hook *hook)
{
    /*更新游戏数据*/
    if (hook->state == HOOK_EXTEND)
    {
        extendHook(hook, minelink, false);
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

    IMAGE img;
    loadimage(&img, _T("img/pauseButton.png"), 101, 75);
    EasyPutImage(0, 0, "img/gameBackground.jpg", GAME_WIDTH, GAME_HEIGHT);
    TransparentImage(NULL, 740, 30, &img, 70, 50, BLACK);
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
    EasyPutImage(0, 0, "img/goal.jpg", GAME_WIDTH, GAME_HEIGHT);
    outtextxy(250, 230, str);
    PlaySound(_T("sounds/goal.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(2000);
}

void loseScene()
{
    /*失败场景*/
    EasyPutImage(0, 0, "img/lose.jpg", GAME_WIDTH, GAME_HEIGHT);
    Sleep(2000);
    //更新用户的最高记录
    if (user->highest_score < countMoney(0, false))
    {
        user->highest_score = countMoney(0, false);
        UserData *head = loadUserData();
        updateUserHighestScore(head, user, countMoney(0, false)); //更新用户的最高分
    }
    EasyPutImage(0, 0, "img/endScore.png", GAME_WIDTH, GAME_HEIGHT);
    LOGFONT f;
    settextstyle(30, 0, _T("楷体"));
    setbkmode(TRANSPARENT);
    gettextstyle(&f);
    f.lfQuality = ANTIALIASED_QUALITY;
    f.lfWeight = FW_LIGHT;
    settextcolor(RED);
    TCHAR scoreStr[20];
    _stprintf(scoreStr, _T("您的分数：%d"), countMoney(0, false));
    outtextxy(250, 210, scoreStr);
    _stprintf(scoreStr, _T("您的最高分：%d"), user->highest_score);
    outtextxy(250, 260, scoreStr);
    Sleep(5000);
    Status = MAIN_MENU;
    isNewGame = true;
}

void gamePause()
{
    ExMessage mouse;
    LOGFONT f; //初始化字体格式
    int lastChoice = -1;

    settextstyle(35, 0, _T("楷体"));
    setbkmode(TRANSPARENT); //设置字体背景透明
    gettextstyle(&f);
    f.lfQuality = ANTIALIASED_QUALITY; //抗锯齿
    f.lfWeight = FW_BOLD;              //粗体
    settextcolor(BROWN);               //棕色字体
    settextstyle(&f);
    while (Status == PAUSE)
    {
        BeginBatchDraw();
        EasyPutImage(0, 0, "img/pause.png", GAME_WIDTH, GAME_HEIGHT);
        peekmessage(&mouse); //获取鼠标消息
        outtextxy(400, 200, _T("继续游戏"));
        outtextxy(380, 280, _T("返回主菜单"));
        if (determineMouse(mouse, 400, 200, 540, 233))
        {
            if (lastChoice != 1)
            {
                lastChoice = 1;
                PlaySound(_T("sounds/slip.wav"), NULL, SND_ASYNC | SND_FILENAME);
            }
            settextcolor(BLACK);
            outtextxy(400, 200, _T("继续游戏"));
            settextcolor(BROWN);
            outtextxy(380, 280, _T("返回主菜单"));
            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
            {
                Status = GAMING;
            }
        }
        else if (determineMouse(mouse, 380, 280, 555, 313))
        {
            if (lastChoice != 2)
            {
                lastChoice = 2;
                PlaySound(_T("sounds/slip.wav"), NULL, SND_ASYNC | SND_FILENAME);
            }
            settextcolor(BLACK);
            outtextxy(380, 280, _T("返回主菜单"));
            settextcolor(BROWN);
            outtextxy(400, 200, _T("继续游戏"));
            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
            {
                Status = MAIN_MENU;
                isNewGame = true;
                break;
            }
        }
        else
        {
            lastChoice = -1;
            settextcolor(BROWN);
            outtextxy(400, 200, _T("继续游戏"));
            outtextxy(380, 280, _T("返回主菜单"));
        }
        flushmessage(EM_MOUSE);
        FlushBatchDraw();
    }
}