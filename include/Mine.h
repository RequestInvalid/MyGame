#ifndef MINE_H
#define MINE_H

#include "Global.h"
#include "Hook.h"

int countGameTime(int goal, bool isNextLevel);
int countMoney(int addScore, bool isNewGame);
int countLevel(bool isNewGame, bool isNextLevel);
void setGoal(int *goal, MineLink *head, bool isNewGame);

MineLink *createMineLink(int count);
void deleteMine(MineLink **head, MineLink *mine);
MineLink *isTouchHook(Hook *hook, MineLink *head);
void moveHookAndMine(Hook *hook, MineLink *mine, MineLink **head);

void drawMine(MineLink *head, bool isNewGame);

#endif