#include "GameEngine.h"
#pragma comment(lib, "MSIMG32.LIB") //�����ⲿ������

extern GameStatus Status;
extern userData *user;

boolean isNewGame = true;
Hook *hook = (Hook *)malloc(sizeof(Hook)); //�������Ӷ���
MineLink *minelink = createMineLink(20);   //������ɿ���
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
        // Sleep(10); // ���� CPU ռ��
    }
    return 0;
}

void init(int goal, Hook *hook, MineLink *minelink)
{

    initHook(hook);
    minelink = createMineLink(20); //���ɿ���
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
    /*������*/
    ExMessage action;
    DWORD currentTime, lastTime;
    HANDLE keyPressThread = CreateThread(NULL, 0, detectKeyPress, hook, 0, NULL); //�����̼߳�ⰴ���¼�
    lastTime = GetTickCount();
    // setGoal(&goal, minelink, true);
    init(goal, hook, minelink);
    setGoal(&goal, minelink, false);
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