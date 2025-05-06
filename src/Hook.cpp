#include "Hook.h"

void initHook(Hook *hook)
{
    hook->x = 483;
    hook->y = 118;
    hook->sizeX = 45;
    hook->sizeY = 20;
    hook->length = 35; // ��ʼ���ȣ�Ҳ����ת����ʱ����
    hook->angle = 0;   // ��ʼ�Ƕ�
    hook->extendSpeed = 10;
    hook->backSpeed = 10;
    hook->mine = NULL; // ��ʼ��ץ���Ŀ���ΪNULL
    hook->state = HOOK_ROTATE;
}

void swangHook(Hook *hook, boolean isNewGame = false)
{
    static DWORD currentTime, lastTime = 0;
    static float dAngle = 2.0f; // ������ת�ٶ�
    if (isNewGame)
    {
        lastTime = 0;
        return;
    }
    if (lastTime == 0)
    {
        lastTime = GetTickCount();
    }
    currentTime = GetTickCount();
    if (currentTime - lastTime >= 10)
    {
        if (hook->angle <= 75 && hook->angle >= -75)
        {
            hook->angle += dAngle; // �ı���ת�Ƕ�
        }
        else
        {
            if (hook->angle > 75)
            {
                hook->angle = 75;
            }
            else if (hook->angle < -75)
            {
                hook->angle = -75;
            }
            dAngle = -dAngle; // ������ת
        }
        hook->midX = 483 + sin(hook->angle * PI / 180) * hook->length;
        hook->midY = 88 + cos(hook->angle * PI / 180) * hook->length;
        hook->sizeX = (int)(fabs(45 * cos(hook->angle * PI / 180))) + (fabs(20 * sin(hook->angle * PI / 180)));
        hook->sizeY = (int)(fabs(45 * sin(hook->angle * PI / 180))) + (fabs(20 * cos(hook->angle * PI / 180)));
        hook->x = hook->midX - (hook->sizeX / 2);
        hook->y = hook->midY - (hook->sizeY / 2);
        lastTime = currentTime;
    }
}

void extendHook(Hook *hook, MineLink *head, boolean isNewGame = false)
{
    /*������չ���ջص��߼�*/
    static DWORD currentTime, lastTime = 0;
    if (isNewGame)
    {
        lastTime = 0;
        return;
    }
    if (lastTime == 0)
    {
        lastTime = GetTickCount();
    }
    currentTime = GetTickCount();
    if (currentTime - lastTime >= 10)
    {
        MineLink *touchMine = isTouchHook(hook, head);
        if (hook->midX <= 50 || hook->midY >= GAME_HEIGHT - 50 || hook->midX >= GAME_WIDTH - 50)
        {
            // ���ﴰ�ڱ߿򷵻�
            hook->state = HOOK_BACK;
        }
        else if (touchMine != NULL)
        {
            if (touchMine->mine.type == STONE)
            {
                PlaySound(_T("sounds/getStone.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            else
            {
                PlaySound(_T("sounds/getMine.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            hook->backSpeed = touchMine->mine.backSpeed;
            hook->mine = touchMine;
            hook->state = HOOK_CATCH;
        }
        else
        {
            // ��չ����ʱ���¹�������
            hook->length += hook->extendSpeed;
            hook->midX = 483 + sin(hook->angle * PI / 180) * hook->length;
            hook->midY = 88 + cos(hook->angle * PI / 180) * hook->length;
            hook->x = hook->midX - (hook->sizeX / 2);
            hook->y = hook->midY - (hook->sizeY / 2);
        }
    }
}

void backHook(Hook *hook, boolean isNewGame = false)
{
    /*�����ջص��߼�*/
    static DWORD currentTime, lastTime = 0;
    if (isNewGame)
    {
        lastTime = 0;
        return;
    }
    if (lastTime == 0)
    {
        lastTime = GetTickCount();
    }
    currentTime = GetTickCount();
    if (currentTime - lastTime >= 10)
    {
        if (calculateDistance(hook->midX, hook->midY, 483, 88) <= 50)
        {
            hook->state = HOOK_ROTATE;
            hook->length = 35;
            hook->backSpeed = 10;
        }
        else
        {
            // �ջع���ʱ���¹�������
            hook->length -= hook->backSpeed;
            hook->midX = 483 + sin(hook->angle * PI / 180) * hook->length;
            hook->midY = 88 + cos(hook->angle * PI / 180) * hook->length;
            hook->x = hook->midX - (hook->sizeX / 2);
            hook->y = hook->midY - (hook->sizeY / 2);
        }
    }
}

IMAGE *updateMiner(Hook *hook, boolean isNewGame = false)
{
    static DWORD currentTime, lastTime = 0;
    static IMAGE minerUp, minerDown;
    static boolean isUp = true;
    if (isNewGame)
    {
        loadimage(&minerUp, _T("img/minerup.png"));
        loadimage(&minerDown, _T("img/minerdown.png"));
    }
    if (hook->state == HOOK_ROTATE)
    {
        return &minerUp;
    }
    else
    {
        if (lastTime == 0)
        {
            lastTime = GetTickCount();
        }
        currentTime = GetTickCount();
        if (currentTime - lastTime >= 300)
        {
            lastTime = currentTime;
            isUp = !isUp;
        }
        return isUp ? &minerUp : &minerDown;
    }
}

void drawHook(Hook *hook)
{
    IMAGE srcImg, rotImg;
    // ����ԭʼͼƬ
    loadimage(&srcImg, _T("img/hook.png"), 45, 20);
    int srcWidth = srcImg.getwidth();
    int srcHeight = srcImg.getheight();
    // �����㹻���Ŀ��ͼ��
    rotImg.Resize(hook->sizeX, hook->sizeY);
    // ��תͼƬ
    rotateimage(&rotImg, &srcImg, hook->angle * PI / 180, BLACK, true, true);
    // ʹ��͸����ʽ��ʾ��ת���ͼƬ
    TransparentImage(NULL, hook->x, hook->y, &rotImg, hook->sizeX, hook->sizeY, BLACK);
    // ��ȡ����ƫ����
    int offsetX = (int)(hook->midX - (10 * sin(hook->angle * PI / 180)));
    int offsetY = (int)(hook->midY - (10 * cos(hook->angle * PI / 180)));
    // ��������
    setlinecolor(BLACK);
    setlinestyle(PS_SOLID, 3);
    line(483, 88, offsetX, offsetY);
}

void drawMiner(IMAGE *img)
{
    TransparentImage(NULL, 455, 10, img, 100, 100, BLACK);
}