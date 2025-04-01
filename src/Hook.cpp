#include "Hook.h"

void initHook(Hook *hook)
{
    hook->x = 483;
    hook->y = 118;
    hook->sizeX = 71;
    hook->sizeY = 40;
    hook->length = 70;
    hook->angle = 0; // ��ʼ�Ƕ�
}

void swangHook(Hook *hook)
{
    static DWORD currentTime, lastTime = 0;
    static float dAngle = 2.0f; // ������ת�ٶ�
    if (lastTime == 0)
    {
        lastTime = GetTickCount();
    }
    currentTime = GetTickCount();
    if (currentTime - lastTime >= 10)
    {
        if (hook->angle <= 60 && hook->angle >= -60)
        {
            hook->angle += dAngle; // �ı���ת�Ƕ�
        }
        else
        {
            if (hook->angle > 60)
            {
                hook->angle = 60;
            }
            else if (hook->angle < -60)
            {
                hook->angle = -60;
            }
            dAngle = -dAngle; // ������ת
        }
        hook->midX = 483 + sin(hook->angle * PI / 180) * hook->length;
        hook->midY = 88 + cos(hook->angle * PI / 180) * hook->length;
        hook->sizeX = (int)(fabs(71 * cos(hook->angle * PI / 180))) + (fabs(40 * sin(hook->angle * PI / 180)));
        hook->sizeY = (int)(fabs(71 * sin(hook->angle * PI / 180))) + (fabs(40 * cos(hook->angle * PI / 180)));
        hook->x = hook->midX - (hook->sizeX / 2);
        hook->y = hook->midY - (hook->sizeY / 2);
        lastTime = currentTime;
    }
}

void updateHook(Hook *hook)
{
    static DWORD currentTime, lastTime = 0;
    static double dAngle = 1.0f; // ������ת�Ƕ�
    if (lastTime == 0)
    {
        lastTime = GetTickCount();
    }
    currentTime = GetTickCount();
    if (hook->state == HOOK_ROTATE)
    {
        if (currentTime - lastTime >= 10)
        {
            if (hook->angle < 60 && hook->angle > -60)
            {
                hook->angle += dAngle; // ��ת�Ƕ�
            }
            else
            {
                dAngle = -dAngle; // ������ת
            }
            lastTime = currentTime;
        }
    }
}

IMAGE *updateMiner()
{
    static DWORD currentTime, lastTime = 0;
    static IMAGE minerUp, minerDown;
    static boolean isUp = true;
    loadimage(&minerUp, _T("img/minerup.png"));
    loadimage(&minerDown, _T("img/minerdown.png"));
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
