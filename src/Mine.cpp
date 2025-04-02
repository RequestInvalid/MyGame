#include "Mine.h"

int countGameTime(boolean isNewGame = false)
{
    static int gameTime;
    if (isNewGame == true)
    {
        gameTime = 60;
        return;
    }
    static DWORD currentTime, lastTime = 0;
    if (!lastTime)
    {
        lastTime = GetTickCount();
    }
    currentTime = GetTickCount();
    if (currentTime - lastTime >= 1000)
    {
        lastTime = currentTime;
        gameTime--;
    }
    return gameTime;
}

void drawGameTime(int GameTime)
{
    LOGFONT f;
    settextstyle(35, 0, _T("¿¬Ìå"));
    setbkmode(TRANSPARENT);
    gettextstyle(&f);
    f.lfQuality = ANTIALIASED_QUALITY;
    f.lfWeight = FW_BOLD;
    settextcolor(BLACK);
    settextstyle(&f);
    char str[2];
    sprintf(str, "%d", GameTime);
    outtextxy(900, 20, str);
}