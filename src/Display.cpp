#include "Display.h"

void displayGameTime(int GameTime)
{
    /*��ʾ��Ϸʣ��ʱ��*/
    LOGFONT f;
    settextstyle(35, 0, _T("����"));
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
    /*��ʾ����*/
    LOGFONT f;
    settextstyle(35, 0, _T("����"));
    setbkmode(TRANSPARENT);
    gettextstyle(&f);
    f.lfQuality = ANTIALIASED_QUALITY;
    f.lfWeight = FW_BOLD;
    settextcolor(RGB(0, 100, 0)); //���ý�Ǯ��������ɫΪ����ɫ
    settextstyle(&f);
    TCHAR str[6];
    _stprintf(str, _T("$%d"), money);
    outtextxy(90, 17, str);
}

void displayGoal(int goal)
{
    /*��ʾĿ�����*/
    LOGFONT f;
    settextstyle(35, 0, _T("����"));
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
    /*��ʾ�ؿ���*/
    LOGFONT f;
    settextstyle(35, 0, _T("����"));
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
