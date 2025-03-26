#include "Global.h"

int determineMouse(ExMessage msg, int startX, int startY, int endX, int endY)
{
    /*检测鼠标坐标是否在某一矩形内*/
    if (msg.x > startX && msg.y > startY && msg.x < endX && msg.y < endY)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

char *charInRange(char *str, int start, int end)
{
    /*返回指定范围内的字符串*/
    if (end - start <= 0)
    {
        return "";
    }
    char *output = (char *)malloc(sizeof(char) * (end - start + 1));
    for (int i = 0; i < end - start; i++)
    {
        output[i] = str[start + i];
    }
    output[end] = '\0';
    return output;
}

void TransparentImage(IMAGE *dstimg, int x, int y, IMAGE *srcimg, UINT transparentcolor)
{
    /*绘制透明图片*/
    HDC dstDC = GetImageHDC(dstimg);
    HDC srcDC = GetImageHDC(srcimg);
    int w = srcimg->getwidth();
    int h = srcimg->getheight();
    // 使用 Windows GDI 函数实现透明位图
    TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);
}
