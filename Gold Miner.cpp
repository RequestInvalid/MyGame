#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <tchar.h>
#include <Windows.h>
#include <graphics.h>
#include <conio.h>

#define GAME_WIDTH 960
#define GAME_HEIGHT 540

//利用枚举来创造状态机
typedef enum
{
    MAIN_MENU,
    LOGIN,
    REGISTER,
    RANK,
    EXIT,
} GameStatus;

GameStatus Status = MAIN_MENU; //初始化状态机

//用户数据结构体
typedef struct userData
{
    char username[33];
    char pasport[19];
    int highest_score = 0;
    struct userData *next;
} userData;

/*函数声明*/
void gameLoop();                                                               //游戏循环体，切换游戏窗口状态
int determineMouse(ExMessage msg, int startX, int startY, int endX, int endY); //检测鼠标坐标是否在某一矩形内
void mainMenu();                                                               //主菜单
void loginBox();                                                               //设置登录框
void registerBox();                                                            //设置注册框
void drawUserName();                                                           //用户名输出框动画
userData *loadUserData();                                                      //加载用户数据为链表，返回头指针(可能还有问题？)
void addUserData(userData *head, userData data);                               //为内存中的链表和文件中的用户数据添加新数据

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
    FILE *file = fopen("log.dat", "w+");
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
        if (mouse.message == WM_LBUTTONDOWN)
        {
            fprintf(file, "%d, %d\n", mouse.x, mouse.y);
        }
    }
}

void loginBox()
{
    /*设置登录框*/
    IMAGE login_box;
    ExMessage action;
    userData user_input; //存储用户输入的结构体
    int name_length = 0, passport_length = 0;
    FILE *file = fopen("user.dat", "ab+");
    LOGFONT login_font;

    settextstyle(30, 0, _T("微软雅黑"));
    setbkmode(TRANSPARENT);
    gettextstyle(&login_font);
    login_font.lfQuality = ANTIALIASED_QUALITY;
    login_font.lfWeight = FW_BOLD;
    settextcolor(BLACK);
    settextstyle(&login_font); //设置输出字体

    setfillcolor(WHITE);

    loadimage(&login_box, _T("resource/login.png"), 350, 350); //加载缩小后的登录框图片
    putimage(305, 95, &login_box);
    while (1)
    {
        action = getmessage();
        if (action.message == WM_LBUTTONUP)
        {
            if (determineMouse(action, 606, 123, 637, 153)) //退出按钮
            {
                Status = MAIN_MENU;
                return;
            }
            else if (determineMouse(action, 351, 238, 614, 284)) //输入用户名窗口
            {
                outtextxy(351, 245, _T("|")); //测试代码，记得删除
                while (1)
                {
                    action = getmessage();
                    if (action.message == WM_LBUTTONUP) //判断鼠标左键按下时的位置
                    {
                        if (determineMouse(action, 606, 123, 637, 153))
                        {
                            Status = MAIN_MENU;
                            return;
                        }
                        else if (!determineMouse(action, 351, 238, 614, 284))
                        {
                            break;
                        }
                    }
                    else if (action.message == WM_KEYDOWN) //判断按键按下事件
                    {
                        if ((action.vkcode >= 'A' && action.vkcode <= 'Z') ||
                            (action.vkcode >= '0' && action.vkcode <= '9'))
                        {
                            solidrectangle(351, 245, 351 + textwidth(user_input.username), 245 + textheight(user_input.username));
                            user_input.username[name_length] = tolower(action.vkcode);
                            outtextxy(351, 245, user_input.username);
                            name_length++;
                        }
                        else if (action.vkcode == VK_BACK)
                        {
                            name_length--;
                            solidrectangle(351, 245, 351 + textwidth(user_input.username), 245 + textheight(user_input.username));
                            outtextxy(351, 245, user_input.username); //有问题
                        }
                    }
                }
            }
            else if (determineMouse(action, 351, 342, 614, 387)) //输入密码窗口
            {
            }
        }
    }
}

void registerBox()
{
    /*设置注册框*/
    IMAGE register_box;
    ExMessage mouse;
    loadimage(&register_box, _T("resource/register.png"), 350, 350); //加载缩小后的注册框图片
    putimage(305, 95, &register_box);
    while (1)
    {
        mouse = getmessage();
        if (mouse.x > 606 && mouse.y > 123 && mouse.x < 637 && mouse.y < 153)
        {
            if (mouse.message == WM_LBUTTONUP)
            {
                Status = MAIN_MENU;
                return;
            }
        }
    }
}

void drawUserName()
{
    /*用户名输出框动画*/
    ExMessage login_action;
    while (1)
    {
        login_action = getmessage();
    }
}

userData *loadUserData()
{
    /*加载用户数据为链表，返回头指针(可能还有问题？)*/
    userData *head, *ptr, *temp;
    FILE *user_file = fopen("user.dat", "rb");
    if (!user_file)
    {
        /*判断是否存在用户数据文件，否则创建文件*/
        FILE *user_file = fopen("user.dat", "wb");
        fclose(user_file);
        return NULL;
    }
    head = (userData *)malloc(sizeof(userData));
    if (fread(head, sizeof(userData), 1, user_file) == 0)
    {
        /*判断文件是否存在数据，否则返回NULL*/
        fclose(user_file);
        return NULL;
    }
    ptr = head;
    ptr->next = (userData *)malloc(sizeof(userData));
    while (fread(ptr->next, sizeof(userData), 1, user_file))
    {
        ptr = ptr->next;
        ptr->next = (userData *)malloc(sizeof(userData));
    }
    ptr->next = NULL;
    fclose(user_file);
    return head;
}

void addUserData(userData *head, userData data)
{
    /*为内存中的链表和文件中的用户数据添加新数据*/
    userData *ptr, *temp;
    FILE *user_file = fopen("user.dat", "ab+");
    *temp = data;
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
        fwrite(head, sizeof(userData), 1, user_file);
        fclose(user_file);
        return;
    }
    ptr = head;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = temp;
    fwrite(temp, sizeof(userData), 1, user_file);
    fclose(user_file);
}
