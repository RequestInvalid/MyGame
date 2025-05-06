#include "Hook.h"

void initHook(Hook *hook)
{
    hook->x = 483;
    hook->y = 118;
    hook->sizeX = 45;
    hook->sizeY = 20;
    hook->length = 35; // 初始长度，也即旋转钩子时长度
    hook->angle = 0;   // 初始角度
    hook->extendSpeed = 10;
    hook->backSpeed = 10;
    hook->mine = NULL; // 初始化抓到的矿物为NULL
    hook->state = HOOK_ROTATE;
}

void swangHook(Hook *hook, boolean isNewGame = false)
{
    static DWORD currentTime, lastTime = 0;
    static float dAngle = 2.0f; // 钩子旋转速度
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
            hook->angle += dAngle; // 改变旋转角度
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
            dAngle = -dAngle; // 反向旋转
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
    /*钩子伸展和收回的逻辑*/
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
            // 到达窗口边框返回
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
            // 伸展钩子时更新钩子坐标
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
    /*钩子收回的逻辑*/
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
            // 收回钩子时更新钩子坐标
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
    // 加载原始图片
    loadimage(&srcImg, _T("img/hook.png"), 45, 20);
    int srcWidth = srcImg.getwidth();
    int srcHeight = srcImg.getheight();
    // 创建足够大的目标图像
    rotImg.Resize(hook->sizeX, hook->sizeY);
    // 旋转图片
    rotateimage(&rotImg, &srcImg, hook->angle * PI / 180, BLACK, true, true);
    // 使用透明方式显示旋转后的图片
    TransparentImage(NULL, hook->x, hook->y, &rotImg, hook->sizeX, hook->sizeY, BLACK);
    // 获取缆绳偏移量
    int offsetX = (int)(hook->midX - (10 * sin(hook->angle * PI / 180)));
    int offsetY = (int)(hook->midY - (10 * cos(hook->angle * PI / 180)));
    // 绘制缆绳
    setlinecolor(BLACK);
    setlinestyle(PS_SOLID, 3);
    line(483, 88, offsetX, offsetY);
}

void drawMiner(IMAGE *img)
{
    TransparentImage(NULL, 455, 10, img, 100, 100, BLACK);
}