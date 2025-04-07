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

void initLargeGold(Mine *mine); // ��ʼ������
void initMidGold(Mine *mine);   // ��ʼ���н��
void initSmallGold(Mine *mine); // ��ʼ��С���
void initDiamond(Mine *mine);   // ��ʼ����ʯ
void initStone(Mine *mine);     // ��ʼ��ʯͷ

void drawMine(MineLink *head, boolean isNewGame);

#endif