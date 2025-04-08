#include "GameEngine.h"
#pragma comment(lib, "MSIMG32.LIB") //�����ⲿ������

extern GameStatus Status;
extern userData *user;

Hook *hook = (Hook *)malloc(sizeof(Hook)); //�������Ӷ���
MineLink *minelink = createMineLink(10);   //������ɿ���

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
    /*������*/
    ExMessage action;
    DWORD currentTime, lastTime;
    HANDLE keyPressThread = CreateThread(NULL, 0, detectKeyPress, hook, 0, NULL); //�����̼߳�ⰴ���¼�
    init(hook);
    lastTime = GetTickCount();
    while (true)
    {
        currentTime = GetTickCount();
        if (currentTime - lastTime >= 10) // 0.01��ˢ��һ֡
        {
            peekmessage(&action, EM_KEY); //��ȡ��Ϣ
            updateData(&action, hook);
            updateGraph();
            flushmessage();
            lastTime = currentTime;
        }
    }
}

void updateData(ExMessage *msg, Hook *hook) //����msgû�ã��ǵ�ɾ
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