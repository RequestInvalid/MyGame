#include "Global.h"
#include "Hook.h"
#include "Mine.h"

void init(int *goal, Hook *hook, MineLink **minelink);
void mainEngine();
void updateData(Hook *hook);
void updateGraph(int goal, Hook *hook);