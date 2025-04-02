#include "GameEngine.h"
#pragma comment(lib, "MSIMG32.LIB") //�����ⲿ������

extern GameStatus Status;
extern userData *user;

Hook *hook = (Hook *)malloc(sizeof(Hook)); //�������Ӷ���

DWORD WINAPI detectKeyPress(LPVOID param)
{
    /*���̼߳�ⰴ���¼����߳�*/
    Hook *hook = (Hook *)param; // ��ȡ����Ĺ��Ӷ���ָ��

    while (1)
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

void mainEngine()
{
    /*������*/
    ExMessage action;
    initHook(hook);
    HANDLE keyPressThread = CreateThread(NULL, 0, detectKeyPress, hook, 0, NULL); //�����̼߳�ⰴ���¼�
    while (1)
    {
        Sleep(10);                    //����0.01�루����֡��Ϊ100fps��
        peekmessage(&action, EM_KEY); //��ȡ��Ϣ
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
        backHook(hook); //�����ջ�
    }
    else if (hook->state == HOOK_ROTATE)
    {
        swangHook(hook); //������ת
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