#ifndef MINE_H
#define MINE_H

#include "Global.h"
#include "Hook.h"

int countGameTime(boolean isNewGame);
void displayGameTime(int GameTime);
int countScore(boolean isNewGame);
void displayScore(int score);
MineLink *createMineLink(int count);
void deleteMine(MineLink **head, MineLink *mine);
MineLink *isTouchHook(Hook *hook, MineLink *head);
void moveHookAndMine(Hook *hook, MineLink *mine, MineLink **head);

void initLargeGold(Mine *mine); // 初始化大金矿
void initMidGold(Mine *mine);   // 初始化中金矿
void initSmallGold(Mine *mine); // 初始化小金矿
void initDiamond(Mine *mine);   // 初始化钻石
void initStone(Mine *mine);     // 初始化石头

void drawMine(MineLink *head, boolean isNewGame);

#endif