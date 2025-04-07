#include "Mine.h"

int randomInRange(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

int countGameTime(boolean isNewGame = false)
{
    static int gameTime;
    if (isNewGame == true)
    {
        gameTime = 60;
        return 0;
    }
    static DWORD currentTime, lastTime = 0;
    if (!lastTime)
    {
        lastTime = GetTickCount();
    }
    currentTime = GetTickCount();
    if (currentTime - lastTime >= 1000)
    {
        lastTime = currentTime;
        if (gameTime > 0)
        {
            gameTime--;
        }
    }
    return gameTime;
}

void displayGameTime(int GameTime)
{
    LOGFONT f;
    settextstyle(35, 0, _T("楷体"));
    setbkmode(TRANSPARENT);
    gettextstyle(&f);
    f.lfQuality = ANTIALIASED_QUALITY;
    f.lfWeight = FW_BOLD;
    settextcolor(BLACK);
    settextstyle(&f);
    char str[2];
    sprintf(str, "%d", GameTime);
    outtextxy(890, 15, str);
}

void initLargeGold(Mine *mine)
{
    mine->type = MAX_GOLD;
    mine->backSpeed = 4;
    mine->isCollected = false;
    mine->radius = 34;
    mine->value = 500;
}

void initMidGold(Mine *mine)
{
    mine->type = MID_GOLD;
    mine->backSpeed = 6;       // 中金矿回收速度较快
    mine->isCollected = false; // 初始状态未被收集
    mine->radius = 15;         // 中金矿半径较小
    mine->value = 300;         // 中金矿价值较低
}

void initSmallGold(Mine *mine)
{
    mine->type = MIN_GOLD;
    mine->backSpeed = 8;       // 小金矿回收速度最快
    mine->isCollected = false; // 初始状态未被收集
    mine->radius = 10;         // 小金矿半径最小
    mine->value = 50;          // 小金矿价值最低
}

void initDiamond(Mine *mine)
{
    mine->type = DIAMOND;
    mine->backSpeed = 8;       // 钻石回收速度较慢
    mine->isCollected = false; // 初始状态未被收集
    mine->radius = 12;         // 钻石半径
    mine->value = 800;         // 钻石价值最高
}

void initStone(Mine *mine)
{
    mine->type = STONE;
    mine->backSpeed = 4;       // 石头回收速度最慢
    mine->isCollected = false; // 初始状态未被收集
    mine->radius = 32;         // 石头半径较大
    mine->value = 20;          // 石头价值最低
}

boolean isValidPosition(MineLink *head, int x, int y, int radius)
{
    /*检查新矿物坐标是否与已有矿物冲突*/
    MineLink *current = head;
    while (current != NULL)
    {
        float distance = calculateDistance(current->mine.x, current->mine.y, x, y);
        if (distance < current->mine.radius + radius)
        {
            return false; // 坐标冲突
        }
        current = current->next;
    }
    return true; // 坐标有效
}

MineType randomMineType()
{
    /*随机生成矿物类型*/
    int type = randomInRange(0, 4); // 0: MAX_GOLD, 1: MID_GOLD, 2: MIN_GOLD, 3: DIAMOND, 4: STONE
    return (MineType)type;
}

void initMine(Mine *mine, MineType type)
{
    /*根据矿物类型初始化矿物信息*/
    switch (type)
    {
    case MAX_GOLD:
        initLargeGold(mine);
        break;
    case MID_GOLD:
        initMidGold(mine);
        break;
    case MIN_GOLD:
        initSmallGold(mine);
        break;
    case DIAMOND:
        initDiamond(mine);
        break;
    case STONE:
        initStone(mine);
        break;
    }
}

MineLink *createMineLink(int count)
{
    /*创建矿物链表*/
    srand(42); // 固定种子，保证随机数一致性

    MineLink *head = NULL;
    MineLink *tail = NULL;

    for (int i = 0; i < count; i++)
    {
        MineLink *newNode = (MineLink *)malloc(sizeof(MineLink));
        if (!newNode)
        {
            exit(1);
        }

        // 随机生成矿物类型
        MineType type = randomMineType();
        initMine(&newNode->mine, type);

        // 随机生成矿物坐标
        int x, y;
        do
        {
            x = randomInRange(50, 910);  // 避免靠近左右端点
            y = randomInRange(180, 500); // 避免靠近上下端点
        } while (!isValidPosition(head, x, y, newNode->mine.radius));

        newNode->mine.x = x;
        newNode->mine.y = y;
        newNode->next = NULL;

        // 将新节点添加到链表
        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    return head;
}

void deleteMine(MineLink *head, MineLink *mine)
{
    if (head == mine)
    {
        MineLink *temp = head;
        head = head->next;
        free(temp);
    }
    else
    {
        MineLink *current = head;
        while (current != NULL && current->next != mine)
        {
            current = current->next;
        }
        if (current != NULL)
        {
            current->next = mine->next;
            free(mine);
        }
    }
}

void drawMine(MineLink *head, boolean isNewGame = false)
{
    static IMAGE mineImg[5];
    if (isNewGame)
    {
        loadimage(&mineImg[0], _T("img/largeGold.png"));
        loadimage(&mineImg[1], _T("img/midGold.png"));
        loadimage(&mineImg[2], _T("img/smallGold.png"));
        loadimage(&mineImg[3], _T("img/diamond.png"));
        loadimage(&mineImg[4], _T("img/stone.png"));
        return;
    }
    MineLink *ptr = head;
    while (ptr != NULL)
    {
        if (!ptr->mine.isCollected)
        {
            int x = ptr->mine.x - (mineImg[ptr->mine.type].getwidth() / 2);
            int y = ptr->mine.y - (mineImg[ptr->mine.type].getheight() / 2);
            TransparentImage(NULL, x, y, &mineImg[ptr->mine.type], mineImg[ptr->mine.type].getwidth(), mineImg[ptr->mine.type].getheight(), BLACK);
        }
        ptr = ptr->next;
    }
}

boolean isTouchHook(Hook *hook, Mine mine)
{
    return calculateDistance(hook->midX, hook->midY, mine.x, mine.y) < (mine.radius + 10) ? true : false;
}

void moveMine()
{
}
