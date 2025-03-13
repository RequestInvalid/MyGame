#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <tchar.h>
#include <Windows.h>
#include <graphics.h>
#include <conio.h>

#define GAME_WIDTH 960
#define GAME_HEIGHT 540

#ifndef MACRO
#define MACRO
//利用枚举来创造状态机
typedef enum
{
    MAIN_MENU,
    GAME,
    LOGIN,
    REGISTER,
    RANK,
    EXIT,
} GameStatus;

//用户数据结构体
typedef struct userData
{
    char username[21];
    char pasport[19];
    int highest_score = 0;
    struct userData *next;
} userData;
#endif

/*函数声明*/
void gameLoop();                                                               //游戏循环体，切换游戏窗口状态
int determineMouse(ExMessage msg, int startX, int startY, int endX, int endY); //检测鼠标坐标是否在某一矩形内
void mainMenu();                                                               //主菜单
char *charInRange(char *str, int start, int end);                              //返回指定范围内的字符串
                                                                               // void loginBox();                                                               //设置登录框
                                                                               // void registerBox();                              //设置注册框
                                                                               // userData *loadUserData();                        //加载用户数据为链表，返回头指针(可能还有问题？)
                                                                               // void addUserData(userData *head, userData data); //为内存中的链表和文件中的用户数据添加新数据