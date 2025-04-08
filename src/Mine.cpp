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
    settextstyle(35, 0, _T("����"));
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
    mine->backSpeed = 2;
    mine->radius = 34;
    mine->value = 500;
}

void initMidGold(Mine *mine)
{
    mine->type = MID_GOLD;
    mine->backSpeed = 4; // �н������ٶȽϿ�
    mine->radius = 15;   // �н��뾶��С
    mine->value = 300;   // �н���ֵ�ϵ�
}

void initSmallGold(Mine *mine)
{
    mine->type = MIN_GOLD;
    mine->backSpeed = 8; // С�������ٶ����
    mine->radius = 10;   // С���뾶��С
    mine->value = 50;    // С����ֵ���
}

void initDiamond(Mine *mine)
{
    mine->type = DIAMOND;
    mine->backSpeed = 8; // ��ʯ�����ٶȽ���
    mine->radius = 12;   // ��ʯ�뾶
    mine->value = 800;   // ��ʯ��ֵ���
}

void initStone(Mine *mine)
{
    mine->type = STONE;
    mine->backSpeed = 1; // ʯͷ�����ٶ�����
    mine->radius = 32;   // ʯͷ�뾶�ϴ�
    mine->value = 20;    // ʯͷ��ֵ���
}

boolean isValidPosition(MineLink *head, int x, int y, int radius)
{
    /*����¿��������Ƿ������п����ͻ*/
    MineLink *current = head;
    while (current != NULL)
    {
        float distance = calculateDistance(current->mine.x, current->mine.y, x, y);
        if (distance < current->mine.radius + radius)
        {
            return false; // �����ͻ
        }
        current = current->next;
    }
    return true; // ������Ч
}

MineType randomMineType()
{
    /*������ɿ�������*/
    int type = randomInRange(0, 4); // 0: MAX_GOLD, 1: MID_GOLD, 2: MIN_GOLD, 3: DIAMOND, 4: STONE
    return (MineType)type;
}

void initMine(Mine *mine, MineType type)
{
    /*���ݿ������ͳ�ʼ��������Ϣ*/
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
    /*������������*/
    srand(42); // �̶����ӣ���֤�����һ����

    MineLink *head = NULL;
    MineLink *tail = NULL;

    for (int i = 0; i < count; i++)
    {
        MineLink *newNode = (MineLink *)malloc(sizeof(MineLink));
        if (!newNode)
        {
            exit(1);
        }

        // ������ɿ�������
        MineType type = randomMineType();
        initMine(&newNode->mine, type);

        // ������ɿ�������
        int x, y;
        do
        {
            x = randomInRange(50, 910);  // ���⿿�����Ҷ˵�
            y = randomInRange(180, 500); // ���⿿�����¶˵�
        } while (!isValidPosition(head, x, y, newNode->mine.radius));

        newNode->mine.x = x;
        newNode->mine.y = y;
        newNode->next = NULL;

        // ���½ڵ���ӵ�����
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
        int x = ptr->mine.x - (mineImg[ptr->mine.type].getwidth() / 2);
        int y = ptr->mine.y - (mineImg[ptr->mine.type].getheight() / 2);
        TransparentImage(NULL, x, y, &mineImg[ptr->mine.type], mineImg[ptr->mine.type].getwidth(), mineImg[ptr->mine.type].getheight(), BLACK);
        ptr = ptr->next;
    }
}

MineLink *isTouchHook(Hook *hook, MineLink *head)
{
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
            hook->state = HOOK_ROTATE;
            deleteMine(head, mine);
            initHook(hook); // ���ù���״̬
        }
        else
        {
            // �ջع���ʱ���¹�������
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
