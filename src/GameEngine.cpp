#include "GameEngine.h"
#pragma comment(lib, "MSIMG32.LIB") //�����ⲿ������

extern GameStatus Status;
extern userData *user;

Hook *hook = (Hook *)malloc(sizeof(Hook)); //�������Ӷ���

void test()
{
    IMAGE img1, img2;
    IMAGE *img3 = updateMiner();
    TransparentImage(NULL, 455, 10, img3, 100, 100, BLACK);
    loadimage(&img1, _T("img/hook.png"));
    swangHook(hook);                                   //������ת
    rotateimage(&img2, &img1, hook->angle * PI / 180); //��ת����
    TransparentImage(NULL, hook->x, hook->y, &img2, 71, 40, BLACK);
}

void mainEngine()
{
    /*������*/
    ExMessage action;
    initHook(hook);
    while (1)
    {
        Sleep(10);            //����0.01�루����֡��Ϊ100fps��
        peekmessage(&action); //��ȡ��Ϣ
        UpdateGraph(&action);
        flushmessage();
    }
}

void UpdateGraph(ExMessage *action)
{
    BeginBatchDraw();
    EasyPutImage(0, 0, "img/gameBackground.jpg", getwidth(), getheight());
    test();
    FlushBatchDraw();
}