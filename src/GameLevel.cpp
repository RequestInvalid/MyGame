#include "GameLevel.h"

extern GameStatus Status;
extern userData *user;

void startUp()
{
    IMAGE background;
    loadimage(&background, _T("resource/gameBackground.jpg"), getwidth(), getheight());
    putimage(0, 0, &background);
    while (1)
    {
        continue;
    }
}