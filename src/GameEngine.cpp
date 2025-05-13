#include "GameEngine.h"

extern GameStatus Status;
extern UserData *user;

bool isNewGame = true;
Hook *hook = (Hook *)malloc(sizeof(Hook)); //�������Ӷ���
MineLink *minelink;
int goal = 0;

DWORD WINAPI detectKeyPress(LPVOID param)
{
    /*���̼߳�ⰴ���¼����߳�*/
    Hook *hook = (Hook *)param; // ��ȡ����Ĺ��Ӷ���ָ��
    ExMessage mouse;

    while (true)
    {
        peekmessage(&mouse, EM_MOUSE);
        // �����̰����¼�
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) // ����·�����Ƿ���
        {
            if (hook->state == HOOK_ROTATE) // ���ڹ��Ӵ�����ת״̬ʱ����
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
        Sleep(10); // ���� CPU ռ��
    }
    return 0;
}

void init(int *goal, Hook *hook, MineLink **minelink)
{
    if (isNewGame)
    {
        srand(42); //��������״̬
        countLevel(isNewGame, false);
        if (user->lastLevel != 0)
        {
            for (int i = 0; i < user->lastLevel; i++)
            {
                *minelink = createMineLink(20); //���ɿ���
            }
            for (int i = 0; i < user->lastLevel - 1; i++)
            {
                countLevel(false, true);
            }
            countMoney(user->lastScore, isNewGame);
        }
        else
        {
            *minelink = createMineLink(20);
            countMoney(0, isNewGame);
        }
        updateMiner(hook, isNewGame);
        drawMine(*minelink, isNewGame);
        isNewGame = false;
    }
    else
    {
        *minelink = createMineLink(20);
        countLevel(isNewGame, true);
    }
    initHook(hook);
    countGameTime(0, true);
    setGoal(goal, *minelink, isNewGame);
    swangHook(hook, isNewGame);
    extendHook(hook, *minelink, isNewGame);
    backHook(hook, isNewGame);
    goalScene(*goal);
}

void mainEngine()
{
    /*������*/
    ExMessage action;
    DWORD currentTime, lastTime;
    HANDLE keyPressThread = CreateThread(NULL, 0, detectKeyPress, hook, 0, NULL); //�����߳̾����ⰴ���¼�
    lastTime = GetTickCount();
    init(&goal, hook, &minelink); //��ʼ�����״̬
    while (true)
    {
        if (Status == GAMING)
        {
            currentTime = GetTickCount();
            if (currentTime - lastTime >= 10) // 0.01��ˢ��һ֡
            {
                peekmessage(&action, EM_KEY); //��ȡ��Ϣ
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
            saveGame(countLevel(false, false) + 1, countMoney(0, false), &user); //��浵ʵ�ִ�
            Sleep(4000);
            Status = GAMING;
            break;
        }
        else if (Status == LOSE)
        {
            saveGame(0, 0, &user); //��Ϸʧ�����ô浵״̬
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
    /*������Ϸ����*/
    if (hook->state == HOOK_EXTEND)
    {
        extendHook(hook, minelink, false);
    }
    else if (hook->state == HOOK_BACK)
    {
        backHook(hook, false); //�����ջ�
    }
    else if (hook->state == HOOK_ROTATE)
    {
        swangHook(hook, false); //������ת
    }
    else
    {
        moveHookAndMine(hook, hook->mine, &minelink);
    }
}

void updateGraph(int goal, Hook *hook)
{
    /*���»���*/
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
    settextstyle(55, 0, _T("����"));
    setbkmode(TRANSPARENT);
    gettextstyle(&f);
    f.lfQuality = ANTIALIASED_QUALITY;
    f.lfWeight = FW_LIGHT;
    settextcolor(RGB(0, 100, 0)); //���ý�Ǯ��������ɫΪ����ɫ
    settextstyle(&f);
    TCHAR str[6];
    _stprintf(str, _T("$%d"), goal);
    EasyPutImage(0, 0, "img/goal.jpg", GAME_WIDTH, GAME_HEIGHT);
    outtextxy(250, 230, str);
    PlaySound(_T("sounds/goal.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(1258);
}

void loseScene()
{
    /*ʧ�ܳ���*/
    EasyPutImage(0, 0, "img/lose.jpg", GAME_WIDTH, GAME_HEIGHT);
    Sleep(1258);
    //�����û�����߼�¼
    if (user->highestScore < countMoney(0, false))
    {
        user->highestScore = countMoney(0, false);
        UserData *head = loadUserData();
        updateUserHighestScore(user->highestScore, user);
    }
    EasyPutImage(0, 0, "img/endScore.png", GAME_WIDTH, GAME_HEIGHT);
    LOGFONT f;
    settextstyle(30, 0, _T("����"));
    setbkmode(TRANSPARENT);
    gettextstyle(&f);
    f.lfQuality = ANTIALIASED_QUALITY;
    f.lfWeight = FW_LIGHT;
    settextcolor(RED);
    TCHAR scoreStr[20];
    _stprintf(scoreStr, _T("���ķ�����%d"), countMoney(0, false));
    outtextxy(250, 210, scoreStr);
    _stprintf(scoreStr, _T("������߷֣�%d"), user->highestScore);
    outtextxy(250, 260, scoreStr);
    Sleep(5000);
    Status = MAIN_MENU;
    isNewGame = true;
}

void gamePause()
{
    /*��Ϸ��ͣ*/
    ExMessage mouse;
    LOGFONT f; //��ʼ�������ʽ
    static int lastChoice = -1;

    settextstyle(35, 0, _T("����"));
    setbkmode(TRANSPARENT); //�������屳��͸��
    gettextstyle(&f);
    f.lfQuality = ANTIALIASED_QUALITY; //�����
    f.lfWeight = FW_BOLD;              //����
    settextcolor(BROWN);               //��ɫ����
    settextstyle(&f);
    if (Status == PAUSE)
    {
        BeginBatchDraw();
        EasyPutImage(0, 0, "img/pause.png", GAME_WIDTH, GAME_HEIGHT);
        peekmessage(&mouse); //��ȡ�����Ϣ
        /*������Ϸ*/
        if (determineMouse(mouse, 400, 178, 540, 211))
        {
            if (lastChoice != 1)
            {
                lastChoice = 1;
                PlaySound(_T("sounds/slip.wav"), NULL, SND_ASYNC | SND_FILENAME);
            }
            settextcolor(BLACK);
            outtextxy(400, 178, _T("������Ϸ"));
            settextcolor(BROWN);
            outtextxy(400, 338, _T("ֱ���˳�"));
            outtextxy(380, 258, _T("���沢�˳�"));
            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
            {
                Status = GAMING;
            }
        }
        /*���沢�˳�*/
        else if (determineMouse(mouse, 380, 258, 555, 291))
        {
            if (lastChoice != 2)
            {
                lastChoice = 2;
                PlaySound(_T("sounds/slip.wav"), NULL, SND_ASYNC | SND_FILENAME);
            }
            settextcolor(BLACK);
            outtextxy(380, 258, _T("���沢�˳�"));
            settextcolor(BROWN);
            outtextxy(400, 178, _T("������Ϸ"));
            outtextxy(400, 338, _T("ֱ���˳�"));
            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) //�������α��������������ı����������������StatusΪWINʱ����
            {
                Status = MAIN_MENU;
                isNewGame = true;
            }
        }
        /*ֱ���˳�*/
        else if (determineMouse(mouse, 380, 338, 555, 371))
        {
            if (lastChoice != 3)
            {
                lastChoice = 3;
                PlaySound(_T("sounds/slip.wav"), NULL, SND_ASYNC | SND_FILENAME);
            }
            settextcolor(BLACK);
            outtextxy(400, 338, _T("ֱ���˳�"));
            settextcolor(BROWN);
            outtextxy(400, 178, _T("������Ϸ"));
            outtextxy(380, 258, _T("���沢�˳�"));
            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
            {
                saveGame(0, 0, &user); //ֱ���˳�ʱ����浵
                Status = MAIN_MENU;
                isNewGame = true;
            }
        }
        else
        {
            if (lastChoice != -1)
            {
                lastChoice = -1;
            }
            settextcolor(BROWN);
            outtextxy(400, 178, _T("������Ϸ"));
            outtextxy(380, 258, _T("���沢�˳�"));
            outtextxy(400, 338, _T("ֱ���˳�"));
        }
        flushmessage(EM_MOUSE);
        FlushBatchDraw();
    }
}