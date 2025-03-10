#include "LoginAndRegister.h"
#include "DataOperate.h"

GameStatus Status = MAIN_MENU; //初始化状态机

int main()
{
    /*主函数*/
    initgraph(GAME_WIDTH, GAME_HEIGHT);
    gameLoop();
    closegraph();
    return 0;
}

void gameLoop()
{
    /*游戏循环体，切换游戏窗口状态*/
    while (Status != EXIT)
    {
        cleardevice();
        switch (Status)
        {
        case MAIN_MENU:
            mainMenu();
            break;
        case LOGIN:
            loginBox();
            break;
        case REGISTER:
            registerBox();
            break;
        }
    }
}

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

void mainMenu()
{
    /*主菜单*/
    int location[4][4] = {//记录主菜单按钮坐标
                          {240, 60, 310, 93},
                          {240, 113, 310, 146},
                          {220, 166, 326, 199},
                          {240, 219, 310, 252}};
    TCHAR text[][12] = {_T("登录"), _T("注册"), _T("排行榜"), _T("退出")}; //记录主菜单按钮文本
    ExMessage mouse;
    IMAGE img;
    SIZE textsize;
    // FILE *file = fopen("log.dat", "w+");//测试代码，用于输出鼠标坐标
    setbkmode(TRANSPARENT); //设置画布背景为透明
    loadimage(&img, _T("resource/startMenu.jpg"), getwidth(), getheight());
    putimage(0, 0, &img);
    LOGFONT f; //初始化字体格式
    settextstyle(35, 0, _T("楷体"));
    setbkmode(TRANSPARENT); //设置字体背景透明
    gettextstyle(&f);
    f.lfQuality = ANTIALIASED_QUALITY; //抗锯齿
    f.lfWeight = FW_BOLD;              //粗体
    settextcolor(BROWN);               //棕色字体
    settextstyle(&f);
    while (1)
    {
        mouse = getmessage();
        for (int i = 0; i < 4; i++) //检测鼠标是否与文字重叠
        {

            if (determineMouse(mouse, location[i][0], location[i][1], location[i][2], location[i][3]))
            {
                settextcolor(BLACK);
                outtextxy(location[i][0], location[i][1], text[i]);
                settextcolor(BROWN);
                if (mouse.message == WM_LBUTTONUP) //检测鼠标是否按下文字
                {
                    switch (i)
                    {
                    case 0:
                        Status = LOGIN; //设置状态为登录
                        return;
                    case 1:
                        Status = REGISTER; //设置状态为登录注册
                        return;
                    case 2:
                        Status = RANK;
                        return;
                    case 3:
                        Status = EXIT; //设置装态为退出，暂时只有一个此类终止状态
                        return;
                    }
                }
            }
            else
            {
                settextcolor(BROWN);
                outtextxy(location[i][0], location[i][1], text[i]);
            }
        }
        //测试用代码，用于输出鼠标左键时鼠标坐标
        // if (mouse.message == WM_LBUTTONDOWN)
        // {
        //     fprintf(file, "%d, %d\n", mouse.x, mouse.y);
        // }
    }
}

char *charInRange(char *str, int start, int end)
{
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