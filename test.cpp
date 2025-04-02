#include "Global.h"
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>

#define PI 3.14159265358979323846
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void testRotateImage()
{
    // ��ʼ��ͼ�δ���
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
    // setbkcolor(WHITE);
    setbkmode(TRANSPARENT);
    cleardevice();

    // ����ԭʼͼƬ������Ƿ�ɹ�
    IMAGE srcImg, dstImg;
    loadimage(&srcImg, _T("img/hook.png"));

    // ��ȡͼƬ�ߴ�
    int imgWidth = srcImg.getwidth();
    int imgHeight = srcImg.getheight();

    if (imgWidth == 0 || imgHeight == 0)
    {
        MessageBox(NULL, _T("ͼƬ�ߴ���Ч"), _T("����"), MB_OK | MB_ICONERROR);
        closegraph();
        return;
    }

    // �Ƕȱ���
    double angle = 0.0;

    // ������ת���ͼƬ�ߴ�
    int rotWidth = (int)(fabs(imgWidth * cos(angle)) + fabs(imgHeight * sin(angle)));
    int rotHeight = (int)(fabs(imgWidth * sin(angle)) + fabs(imgHeight * cos(angle)));

    // ��ʼ��Ŀ��ͼ��
    dstImg.Resize(rotWidth, rotHeight);
    srcImg.Resize(rotWidth, rotHeight);
    // ��ѭ��
    while (!_kbhit()) // ��������˳�
    {
        BeginBatchDraw(); // ����������ͼ
        cleardevice();

        try
        {
            // ��תͼƬ
            rotateimage(&dstImg, &srcImg, angle * PI / 180, BLACK, true, true);

            // ������ʾλ��
            int x = WINDOW_WIDTH / 2 - dstImg.getwidth() / 2;
            int y = WINDOW_HEIGHT / 2 - dstImg.getheight() / 2;

            // ��ʾ��ת���ͼƬ
            EasyPutImage(0, 0, "img/gameBackground.jpg", getwidth(), getheight());
            TransparentImage(NULL, x, y, &dstImg, dstImg.getwidth(), dstImg.getheight(), BLACK);
            // ��ʾ��ǰ�Ƕ�
            TCHAR s[20];
            _stprintf_s(s, 20, _T("�Ƕ�: %.1f��"), angle);
            settextcolor(BLACK);
            outtextxy(10, 10, s);

            // ���½Ƕ�
            angle += 1.0;
            if (angle >= 360.0)
                angle = 0.0;
        }
        catch (...)
        {
            MessageBox(NULL, _T("ͼ��������з�������"), _T("����"), MB_OK | MB_ICONERROR);
            break;
        }

        FlushBatchDraw(); // ˢ�»�ͼ
        Sleep(10);
    }

    EndBatchDraw(); // ����������ͼ
    closegraph();
}

int main()
{
    try
    {
        testRotateImage();
    }
    catch (...)
    {
        MessageBox(NULL, _T("������δ֪����"), _T("����"), MB_OK | MB_ICONERROR);
    }
    return 0;
}