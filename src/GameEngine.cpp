#include "GameEngine.h"
#pragma comment(lib, "MSIMG32.LIB") //�����ⲿ������

extern GameStatus Status;
extern userData *user;

Hook *hook = (Hook *)malloc(sizeof(Hook)); //�������Ӷ���

void test()
{
    IMAGE *img3 = updateMiner();
    TransparentImage(NULL, 455, 10, img3, 100, 100, BLACK);
    swangHook(hook); //���¹���״̬
    IMAGE img1, img2;

    // ����ԭʼͼƬ
    loadimage(&img1, _T("img/hook.png"));
    int srcWidth = img1.getwidth();
    int srcHeight = img1.getheight();

    // �����㹻���Ŀ��ͼ��
    img2.Resize(hook->sizeX, hook->sizeY);

    // ��תͼƬ
    rotateimage(&img2, &img1, hook->angle * PI / 180, BLACK, true, true);

    // ʹ��͸����ʽ��ʾ��ת���ͼƬ
    TransparentImage(NULL, hook->x, hook->y, &img2, hook->sizeX, hook->sizeY, BLACK);
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