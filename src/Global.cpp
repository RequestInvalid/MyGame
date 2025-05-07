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

TCHAR *charInRange(char *str, int start, int end)
{
    /*����ָ����Χ�ڵ��ַ���*/
    if (end - start <= 0)
    {
        //���ؿ��ַ���
        TCHAR *emptyStr = (TCHAR *)malloc(1);
        emptyStr[0] = '\0';
        return emptyStr;
    }
    TCHAR *output = (TCHAR *)malloc(sizeof(char) * (end - start + 1));
    for (int i = 0; i < end - start; i++)
    {
        output[i] = str[start + i];
    }
    output[end] = '\0';
    return output;
}

void TransparentImage(IMAGE *dstimg, int x, int y, IMAGE *srcimg, int widthDest, int heightDest, UINT transparentcolor)
{
    /*����͸��ͼƬ*/
    HDC dstDC = GetImageHDC(dstimg);
    HDC srcDC = GetImageHDC(srcimg);
    int w = srcimg->getwidth();
    int h = srcimg->getheight();
    // ʹ�� Windows GDI ����ʵ��͸��λͼ
    TransparentBlt(dstDC, x, y, widthDest, heightDest, srcDC, 0, 0, w, h, transparentcolor);
}

void EasyPutImage(int x, int y, const char *img, int sizeX, int sizeY)
{
    IMAGE image;
    loadimage(&image, (TCHAR *)img, sizeX, sizeY);
    putimage(x, y, &image);
}

float calculateDistance(int x1, int y1, int x2, int y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

bool isKeyPressed(ExMessage *action)
{
    /*���һ�μ��̵���������*/
    static bool isDown = false;
    if (action->message == WM_KEYDOWN && !isDown)
    {
        isDown = true;
    }
    else if (action->message == WM_KEYUP && isDown)
    {
        isDown = false;
        return true;
    }
    return false;
}

// DWORD WINAPI PlaySoundThread(LPVOID lpParam)
// {
//     TCHAR *path = (TCHAR *)lpParam;

//     // ������Ƶ���첽���� + ������ǰ�̣߳�
//     PlaySound((TCHAR *)path, NULL, SND_FILENAME | SND_ASYNC);

//     return 0;
// }

// void PlaySoundAsync(const char *audioPath)
// {
//     // ����һ���̲߳�����Ƶ
//     CreateThread(NULL, 0, PlaySoundThread, (LPVOID)audioPath, 0, NULL);
// }
