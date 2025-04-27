#include "GameEngine.h"
#pragma comment(lib, "MSIMG32.LIB") //�����ⲿ������

extern GameStatus Status;
extern userData *user;

boolean isNewGame = true;
Hook *hook = (Hook *)malloc(sizeof(Hook)); //�������Ӷ���
MineLink *minelink;
int goal = 0;

DWORD WINAPI detectKeyPress(LPVOID param)
{
    /*���̼߳�ⰴ���¼����߳�*/
    Hook *hook = (Hook *)param; // ��ȡ����Ĺ��Ӷ���ָ��

    while (true)
    {
        // �����̰����¼�
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) // ����·�����Ƿ���
        {
            if (hook->state == HOOK_ROTATE) // ���ڹ��Ӵ�����ת״̬ʱ����
            {
                hook->state = HOOK_EXTEND;
            }
        }
        Sleep(10); // ���� CPU ռ��
    }
    return 0;
}

void init(int *goal, Hook *hook, MineLink **minelink)
{

    if (isNewGame)
    {
        srand(42); //��������״̬
        initHook(hook);
        *minelink = createMineLink(20); //���ɿ���
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
        *minelink = createMineLink(20); //���ɿ���
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
    /*������*/
    ExMessage action;
    DWORD currentTime, lastTime;
    HANDLE keyPressThread = CreateThread(NULL, 0, detectKeyPress, hook, 0, NULL); //�����̼߳�ⰴ���¼�
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
            //�����û�����߼�¼
            if (user->highest_score < countMoney(0, false))
            {
                userData *head = loadUserData(); //�����û�����
                updateUserHighestScore(head, user, countMoney(0, false));
            }
            Status = MAIN_MENU;
            isNewGame = true; //��������Ϸ״̬Ϊ��
            break;
        }
    }
}

void updateData(Hook *hook)
{
    /*������Ϸ����*/
    if (hook->state == HOOK_EXTEND)
    {
        exbandHook(hook, minelink, false);
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
    settextstyle(55, 0, _T("����"));
    setbkmode(TRANSPARENT);
    gettextstyle(&f);
    f.lfQuality = ANTIALIASED_QUALITY;
    f.lfWeight = FW_LIGHT;
    settextcolor(RGB(0, 100, 0)); //���ý�Ǯ��������ɫΪ����ɫ
    settextstyle(&f);
    TCHAR str[6];
    _stprintf(str, _T("$%d"), goal);
    EasyPutImage(0, 0, "img/goal.jpg", getwidth(), getheight());
    outtextxy(250, 230, str);
    Sleep(2000);
}