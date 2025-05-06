#include "Mine.h"

extern GameStatus Status;

int randomInRange(int min, int max)
{
    /*返回范围内的随机数*/
    return rand() % (max - min + 1) + min;
}

int countGameTime(int goal, boolean isNextLevel)
{
    /*计算游戏剩余时间*/
    static int gameTime;
    if (isNextLevel == true)
    {
        gameTime = 60; //设置游戏时间为60秒
        return 60;
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
        else
        {
            //判断游戏输赢
            if (countMoney(0, false) > goal)
            {
                Status = WIN;
                EndBatchDraw();
            }
            else
            {
                Status = LOSE;
                EndBatchDraw();
            }
        }
    }
    return gameTime;
}

int countMoney(int addMoney, boolean isNewGame)
{
    /*计算得分逻辑*/
    static int money = 0;
    if (isNewGame)
    {
        money = 0;
    }
    money += addMoney;
    return money;
}

void setGoal(int *goal, MineLink *head, boolean isNewGame)
{
    /*设置目标金额*/
    if (isNewGame)
    {
        *goal = 0;
    }
    MineLink *ptr = head;
    int temp = 0;
    while (ptr != NULL)
    {
        temp += ptr->mine.value;
        ptr = ptr->next;
    }
    *goal = countMoney(0, false) + (int)(0.6 * (temp / 10 * 10));
}

int countLevel(boolean isNewGame, boolean isNextLevel)
{
    /*计算当前关卡*/
    static int level = 1;
    if (isNewGame)
    {
        level = 1;
        return level;
    }
    else if (isNextLevel)
    {
        level++;
        return level;
    }
    return level;
}

void initLargeGold(Mine *mine)
{
    /*初始化大金块的数据*/
    mine->type = MAX_GOLD;
    mine->backSpeed = 0.8;
    mine->radius = 34;
    mine->value = 10 * randomInRange(45, 55);
}

void initMidGold(Mine *mine)
{
    /*初始化中金块的数据*/
    mine->type = MID_GOLD;
    mine->backSpeed = 2;
    mine->radius = 22;
    mine->value = 5 * randomInRange(17, 23);
}

void initSmallGold(Mine *mine)
{
    /*初始化小金块的数据*/
    mine->type = MIN_GOLD;
    mine->backSpeed = 6;
    mine->radius = 10;
    mine->value = 10 * randomInRange(4, 7);
}

void initDiamond(Mine *mine)
{
    /*初始化钻石的数据*/
    mine->type = DIAMOND;
    mine->backSpeed = 6; // 钻石回收速度较慢
    mine->radius = 12;   // 钻石半径
    mine->value = 800;   // 钻石价值最高
}

void initStone(Mine *mine)
{
    /*初始化石头的数据*/
    mine->type = STONE;
    mine->backSpeed = 0.7;
    mine->radius = 32;
    mine->value = 5 * randomInRange(3, 5);
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
    int weight = randomInRange(1, 100);
    int type = randomInRange(0, 4); // 0: MAX_GOLD, 1: MID_GOLD, 2: MIN_GOLD, 3: DIAMOND, 4: STONE
    //设置生成矿物的权重
    if (weight <= 40)
    {
        type = 2;
    }
    else if (weight <= 60)
    {
        type = 1;
    }
    else if (weight <= 70)
    {
        type = 0;
    }
    else if (weight <= 90)
    {
        type = 4;
    }
    else
    {
        type = 3;
    }
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

void deleteMine(MineLink **head, MineLink *mine)
{
    /*删除链表中选定的矿物，若矿物存在于链表头部则返回新的头指针*/
    if (*head == mine)
    {
        MineLink *temp = *head;
        *head = (*head)->next;
        free(mine);
    }
    else
    {
        MineLink *current = *head;
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

MineLink *isTouchHook(Hook *hook, MineLink *head)
{
    /*检测钩子是否与矿物链表中的矿物相碰*/
    MineLink *ptr = head;
    while (ptr != NULL)
    {
        if (calculateDistance(hook->midX, hook->midY, ptr->mine.x, ptr->mine.y) < (ptr->mine.radius + 10))
        {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

void moveHookAndMine(Hook *hook, MineLink *mine, MineLink **head)
{
    /*如果钩子抓取到矿物，更新钩子和矿物的坐标*/
    static DWORD currentTime, lastTime = 0;
    if (lastTime == 0)
    {
        lastTime = GetTickCount();
    }
    currentTime = GetTickCount();
    if (currentTime - lastTime >= 10)
    {
        if (calculateDistance(hook->midX, hook->midY, 483, 88) <= 50)
        {
            PlaySound(_T("sounds/addMoney.wav"), NULL, SND_FILENAME | SND_ASYNC);
            hook->state = HOOK_ROTATE;
            countMoney(mine->mine.value, false);
            deleteMine(head, mine);
            hook->length = 35;
            hook->backSpeed = 10;
        }
        else
        {
            // 收回钩子时更新钩子坐标
            hook->length -= hook->backSpeed;
            hook->midX = 483 + sin(hook->angle * PI / 180) * hook->length;
            hook->midY = 88 + cos(hook->angle * PI / 180) * hook->length;
            hook->x = hook->midX - (hook->sizeX / 2);
            hook->y = hook->midY - (hook->sizeY / 2);
            mine->mine.x = hook->midX + sin(hook->angle * PI / 180) * mine->mine.radius;
            mine->mine.y = hook->midY + cos(hook->angle * PI / 180) * mine->mine.radius;
        }
    }
}

void drawMine(MineLink *head, boolean isNewGame)
{
    /*根据传入的矿物链表绘制矿物*/
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
        int x = ptr->mine.x - (mineImg[ptr->mine.type].getwidth() / 2);
        int y = ptr->mine.y - (mineImg[ptr->mine.type].getheight() / 2);
        TransparentImage(NULL, x, y, &mineImg[ptr->mine.type], mineImg[ptr->mine.type].getwidth(), mineImg[ptr->mine.type].getheight(), BLACK);
        ptr = ptr->next;
    }
}