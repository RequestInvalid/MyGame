#include "Global.h"
#include <math.h>

#ifndef HOOK_H
#define HOOK_H

#define PI 3.14159265358979323846 // 圆周率常量

// 钩子状态枚举
typedef enum
{
    HOOK_ROTATE, // 钩子旋转
    HOOK_EXTEND, // 钩子伸长
    HOOK_BACK,   // 钩子收回
} HookState;

// 钩子结构体
typedef struct
{
    int x, y, midX, midY, sizeX, sizeY; // 钩子位置
    float length;                       // 当前绳子长度
    float angle;                        // 旋转角度（角度制）
    float speed;                        // 旋转速度
    float extendSpeed;                  // 伸展速度
    float retractSpeed;                 // 收回速度
    HookState state;                    // 当前钩子状态
} Hook;

// 钩子相关函数
void initHook(Hook *hook);
void swangHook(Hook *hook);
void updateHook(Hook *hook);
void drawHook(Hook *hook);
IMAGE *updateMiner();
void updateHook(Hook *hook);

#endif
