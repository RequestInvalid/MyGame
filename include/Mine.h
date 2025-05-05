#ifndef MINE_H
#define MINE_H

#include "Global.h"
#include "Hook.h"

int countGameTime(int goal, boolean isNextLevel);
int countMoney(int addScore, boolean isNewGame);
int countLevel(boolean isNewGame, boolean isNextLevel);
void setGoal(int *goal, MineLink *head, boolean isNewGame);

MineLink *createMineLink(int count);
void deleteMine(MineLink **head, MineLink *mine);
MineLink *isTouchHook(Hook *hook, MineLink *head);
void moveHookAndMine(Hook *hook, MineLink *mine, MineLink **head);

void drawMine(MineLink *head, boolean isNewGame);

#endif