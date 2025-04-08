#ifndef HOOK_H
#define HOOK_H

#include "Global.h"
#include "Mine.h"

#define PI 3.14159265358979323846 // 圆周率常量

// 钩子相关函数
void initHook(Hook *hook); // 初始化钩子

void swangHook(Hook *hook, boolean isNewGame);                  // 钩子旋转
void exbandHook(Hook *hook, MineLink *head, boolean isNewGame); // 钩子伸展
void backHook(Hook *hook, boolean isNewGame);                   // 钩子收回
IMAGE *updateMiner(Hook *hook, boolean isNewGame);              // 更新矿工状态
void updateHook(Hook *hook);                                    // 更新钩子状态

void drawHook(Hook *hook);  // 绘制钩子
void drawMiner(IMAGE *img); // 绘制矿工

#endif
