#include "Global.h"
#include "UserData.h"
#include "Hook.h"
#include "Mine.h"

void init(int *goal, Hook *hook, MineLink **minelink);
void mainEngine();
void updateData(Hook *hook);
void updateGraph(int goal, Hook *hook);
void goalScene(int goal);
void loseScene();