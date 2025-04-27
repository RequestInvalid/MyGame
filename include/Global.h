#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <tchar.h>
#include <Windows.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>

#define GAME_WIDTH 960
#define GAME_HEIGHT 540
//利用枚举来创造状态机
typedef enum GameStatus
{
    MAIN_MENU,
    GAMING,
    LOGIN,
    REGISTER,
    RANK,
    WIN,
    LOSE,
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

/*矿物相关结构体*/
typedef enum MineType
{
    MAX_GOLD,
    MID_GOLD,
    MIN_GOLD,
    DIAMOND,
    STONE,
} MineType;

typedef struct Mine
{
    MineType type;
    int value;
    int x;
    int y;
    int radius;
    float backSpeed;
} Mine;

typedef struct MineLink
{
    Mine mine;
    struct MineLink *next;
} MineLink;

/*钩子相关结构体*/
// 钩子状态枚举
typedef enum HookState
{
    HOOK_ROTATE, // 钩子旋转
    HOOK_EXTEND, // 钩子伸长
    HOOK_BACK,   // 钩子收回
    HOOK_CATCH,  // 钩子抓住矿物
} HookState;

// 钩子结构体
typedef struct Hook
{
    int x, y, midX, midY, sizeX, sizeY; // 钩子位置
    float length;                       // 当前绳子长度
    float angle;                        // 旋转角度（角度制）
    // float speed;                        // 旋转速度
    float extendSpeed; // 伸展速度
    float backSpeed;   // 收回速度
    MineLink *mine;    //抓到的矿物
    HookState state;   // 当前钩子状态
} Hook;

/*函数声明*/
int determineMouse(ExMessage msg, int startX, int startY, int endX, int endY);                                           //检测鼠标坐标是否在某一矩形内
TCHAR *charInRange(char *str, int start, int end);                                                                       //返回指定范围内的字符串
void TransparentImage(IMAGE *dstimg, int x, int y, IMAGE *srcimg, int widthDest, int heightDest, UINT transparentcolor); //绘制透明图片
void EasyPutImage(int x, int y, const char *img, int sizeX, int sizeY);
float calculateDistance(int x1, int y1, int x2, int y2);

#endif
