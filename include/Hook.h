#ifndef HOOK_H
#define HOOK_H

#include "Global.h"
#include "Mine.h"

#define PI 3.14159265358979323846 // 圆周率常量

// 钩子状态枚举
typedef enum
{
    HOOK_ROTATE,  // 钩子旋转
    HOOK_EXTEND,  // 钩子伸长
    HOOK_BACK,    // 钩子收回
    HOOK_GETMINE, // 钩子抓住矿物
} HookState;

// 钩子结构体
typedef struct
{
    int x, y, midX, midY, sizeX, sizeY; // 钩子位置
    float length;                       // 当前绳子长度
    float angle;                        // 旋转角度（角度制）
    float speed;                        // 旋转速度
    float extendSpeed;                  // 伸展速度
    float backSpeed;                    // 收回速度
    HookState state;                    // 当前钩子状态
    MineLink *mine;                     //抓到的矿物
    float maxLength;

} Hook;

// 钩子相关函数
void initHook(Hook *hook); // 初始化钩子

void swangHook(Hook *hook, boolean isNewGame);     // 钩子旋转
void exbandHook(Hook *hook, boolean isNewGame);    // 钩子伸展
void backHook(Hook *hook, boolean isNewGame);      // 钩子收回
IMAGE *updateMiner(Hook *hook, boolean isNewGame); // 更新矿工状态
void updateHook(Hook *hook);                       // 更新钩子状态

void drawHook(Hook *hook);  // 绘制钩子
void drawMiner(IMAGE *img); // 绘制矿工

#endif
