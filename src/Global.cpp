#include "Global.h"

int determineMouse(ExMessage msg, int startX, int startY, int endX, int endY)
{
    /*�����������Ƿ���ĳһ������*/
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
    /*����ָ����Χ�ڵ��ַ���*/
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
    /*����͸��ͼƬ*/
    HDC dstDC = GetImageHDC(dstimg);
    HDC srcDC = GetImageHDC(srcimg);
    int w = srcimg->getwidth();
    int h = srcimg->getheight();
    // ʹ�� Windows GDI ����ʵ��͸��λͼ
    TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);
}
