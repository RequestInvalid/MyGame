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

void drawMine(MineLink *head, boolean isNewGame)
{
    /*根据传入的矿物链表绘制矿物*/
    static IMAGE mineImg[5];
    if (isNewGame)
    {
        loadimage(&mineImg[0], _T("img/largeGold.png"));
        loadimage(&mineImg[1], _T("img/midGold.png"));
        loadimage(&mineImg[2], _T("img/smallGold.png"));
        loadimage(&mineImg[3], _T("img/diamond.png"));
        loadimage(&mineImg[4], _T("img/stone.png"));
        return;
    }
    MineLink *ptr = head;
    while (ptr != NULL)
    {
        int x = ptr->mine.x - (mineImg[ptr->mine.type].getwidth() / 2);
        int y = ptr->mine.y - (mineImg[ptr->mine.type].getheight() / 2);
        TransparentImage(NULL, x, y, &mineImg[ptr->mine.type], mineImg[ptr->mine.type].getwidth(), mineImg[ptr->mine.type].getheight(), BLACK);
        ptr = ptr->next;
    }
}