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
    // 初始化图形窗口
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
    // setbkcolor(WHITE);
    setbkmode(TRANSPARENT);
    cleardevice();

    // 加载原始图片并检查是否成功
    IMAGE srcImg, dstImg;
    loadimage(&srcImg, _T("img/hook.png"));

    // 获取图片尺寸
    int imgWidth = srcImg.getwidth();
    int imgHeight = srcImg.getheight();

    if (imgWidth == 0 || imgHeight == 0)
    {
        MessageBox(NULL, _T("图片尺寸无效"), _T("错误"), MB_OK | MB_ICONERROR);
        closegraph();
        return;
    }

    // 角度变量
    double angle = 0.0;

    // 计算旋转后的图片尺寸
    int rotWidth = (int)(fabs(imgWidth * cos(angle)) + fabs(imgHeight * sin(angle)));
    int rotHeight = (int)(fabs(imgWidth * sin(angle)) + fabs(imgHeight * cos(angle)));

    // 初始化目标图像
    dstImg.Resize(rotWidth, rotHeight);
    srcImg.Resize(rotWidth, rotHeight);
    // 主循环
    while (!_kbhit()) // 按任意键退出
    {
        BeginBatchDraw(); // 开启批量绘图
        cleardevice();

        try
        {
            // 旋转图片
            rotateimage(&dstImg, &srcImg, angle * PI / 180, BLACK, true, true);

            // 计算显示位置
            int x = WINDOW_WIDTH / 2 - dstImg.getwidth() / 2;
            int y = WINDOW_HEIGHT / 2 - dstImg.getheight() / 2;

            // 显示旋转后的图片
            EasyPutImage(0, 0, "img/gameBackground.jpg", getwidth(), getheight());
            TransparentImage(NULL, x, y, &dstImg, dstImg.getwidth(), dstImg.getheight(), BLACK);
            // 显示当前角度
            TCHAR s[20];
            _stprintf_s(s, 20, _T("角度: %.1f°"), angle);
            settextcolor(BLACK);
            outtextxy(10, 10, s);

            // 更新角度
            angle += 1.0;
            if (angle >= 360.0)
                angle = 0.0;
        }
        catch (...)
        {
            MessageBox(NULL, _T("图像处理过程中发生错误"), _T("错误"), MB_OK | MB_ICONERROR);
            break;
        }

        FlushBatchDraw(); // 刷新绘图
        Sleep(10);
    }

    EndBatchDraw(); // 结束批量绘图
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
        MessageBox(NULL, _T("程序发生未知错误"), _T("错误"), MB_OK | MB_ICONERROR);
    }
    return 0;
}