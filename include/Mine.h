#ifndef MINE_H
#define MINE_H

#include "Global.h"
#include "Hook.h"

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
    boolean isCollected;
} Mine;

typedef struct MineLink
{
    Mine mine;
    struct MineLink *next;
} MineLink;

int countGameTime(boolean isNewGame);
void displayGameTime(int GameTime);
int countScore(boolean isNewGame);
void displayScore(int score);
MineLink *createMineLink(int count);
void deleteMine(MineLink *head, MineLink *mine);

void initLargeGold(Mine *mine); // 初始化大金矿
void initMidGold(Mine *mine);   // 初始化中金矿
void initSmallGold(Mine *mine); // 初始化小金矿
void initDiamond(Mine *mine);   // 初始化钻石
void initStone(Mine *mine);     // 初始化石头

void drawMine(MineLink *head, boolean isNewGame);

#endif