#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <tchar.h>
#include <Windows.h>
#include <graphics.h>
#include <conio.h>

#define GAME_WIDTH 960
#define GAME_HEIGHT 540

#ifndef GLOBAL_H
#define GLOBAL_H
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
int determineMouse(ExMessage msg, int startX, int startY, int endX, int endY);                                           //检测鼠标坐标是否在某一矩形内
char *charInRange(char *str, int start, int end);                                                                        //返回指定范围内的字符串
void TransparentImage(IMAGE *dstimg, int x, int y, IMAGE *srcimg, int widthDest, int heightDest, UINT transparentcolor); //绘制透明图片
void EasyPutImage(int x, int y, const char *img, int sizeX, int sizeY);