#include "Display.h"

void displayGameTime(int GameTime)
{
    /*显示游戏剩余时间*/
    LOGFONT f;
    settextstyle(35, 0, _T("楷体"));
    setbkmode(TRANSPARENT);
    gettextstyle(&f);
    f.lfQuality = ANTIALIASED_QUALITY;
    f.lfWeight = FW_BOLD;
    settextcolor(BLACK);
    settextstyle(&f);
    TCHAR str[3];
    _stprintf(str, _T("%d"), GameTime);
    outtextxy(890, 15, str);
}

void displayMoney(int money)
{
    /*显示分数*/
    LOGFONT f;
    settextstyle(35, 0, _T("楷体"));
    setbkmode(TRANSPARENT);
    gettextstyle(&f);
    f.lfQuality = ANTIALIASED_QUALITY;
    f.lfWeight = FW_BOLD;
    settextcolor(RGB(0, 100, 0)); //设置金钱数量的颜色为深绿色
    settextstyle(&f);
    TCHAR str[6];
    _stprintf(str, _T("$%d"), money);
    outtextxy(90, 17, str);
}

void displayGoal(int goal)
{
    /*显示目标分数*/
    LOGFONT f;
    settextstyle(35, 0, _T("楷体"));
    setbkmode(TRANSPARENT);
    gettextstyle(&f);
    f.lfQuality = ANTIALIASED_QUALITY;
    f.lfWeight = FW_BOLD;
    settextcolor(RGB(255, 153, 0));
    settextstyle(&f);
    TCHAR str[6];
    _stprintf(str, _T("$%d"), goal);
    outtextxy(140, 60, str);
}

void displayLevel(int level)
{
    /*显示关卡数*/
    LOGFONT f;
    settextstyle(35, 0, _T("楷体"));
    setbkmode(TRANSPARENT);
    gettextstyle(&f);
    f.lfQuality = ANTIALIASED_QUALITY;
    f.lfWeight = FW_BOLD;
    settextcolor(BLACK);
    settextstyle(&f);
    TCHAR str[3];
    _stprintf(str, _T("%d"), level);
    outtextxy(860, 60, str);
}
