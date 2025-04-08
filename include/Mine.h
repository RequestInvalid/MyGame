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

void initLargeGold(Mine *mine); // ��ʼ������
void initMidGold(Mine *mine);   // ��ʼ���н��
void initSmallGold(Mine *mine); // ��ʼ��С���
void initDiamond(Mine *mine);   // ��ʼ����ʯ
void initStone(Mine *mine);     // ��ʼ��ʯͷ

void drawMine(MineLink *head, boolean isNewGame);

#endif