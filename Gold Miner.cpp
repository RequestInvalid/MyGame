#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <tchar.h>
#include <Windows.h>
#include <graphics.h>
#include <conio.h>

#define GAME_WIDTH 960
#define GAME_HEIGHT 540

//����ö��������״̬��
typedef enum
{
    MAIN_MENU,
    LOGIN,
    REGISTER,
    RANK,
    EXIT,
} GameStatus;

GameStatus Status = MAIN_MENU; //��ʼ��״̬��

//�û����ݽṹ��
typedef struct userData
{
    char username[21];
    char pasport[19];
    int highest_score = 0;
    struct userData *next;
} userData;

/*��������*/
void gameLoop();                                                               //��Ϸѭ���壬�л���Ϸ����״̬
int determineMouse(ExMessage msg, int startX, int startY, int endX, int endY); //�����������Ƿ���ĳһ������
void mainMenu();                                                               //���˵�
char *charInRange(char *str, int start, int end);                              //����ָ����Χ�ڵ��ַ���
void loginBox();                                                               //���õ�¼��
void registerBox();                                                            //����ע���
void drawUserName();                                                           //�û�������򶯻�
userData *loadUserData();                                                      //�����û�����Ϊ��������ͷָ��(���ܻ������⣿)
void addUserData(userData *head, userData data);                               //Ϊ�ڴ��е�������ļ��е��û��������������

int main()
{
    /*������*/
    initgraph(GAME_WIDTH, GAME_HEIGHT);
    gameLoop();
    closegraph();
    return 0;
}

void gameLoop()
{
    /*��Ϸѭ���壬�л���Ϸ����״̬*/
    while (Status != EXIT)
    {
        cleardevice();
        switch (Status)
        {
        case MAIN_MENU:
            mainMenu();
            break;
        case LOGIN:
            loginBox();
            break;
        case REGISTER:
            registerBox();
            break;
        }
    }
}

int determineMouse(ExMessage msg, int startX, int startY, int endX, int endY)
{
    /*�����������Ƿ���ĳһ������*/
    if (msg.x > startX && msg.y > startY && msg.x < endX && msg.y < endY)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void mainMenu()
{
    /*���˵�*/
    int location[4][4] = {//��¼���˵���ť����
                          {240, 60, 310, 93},
                          {240, 113, 310, 146},
                          {220, 166, 326, 199},
                          {240, 219, 310, 252}};
    TCHAR text[][12] = {_T("��¼"), _T("ע��"), _T("���а�"), _T("�˳�")}; //��¼���˵���ť�ı�
    ExMessage mouse;
    IMAGE img;
    SIZE textsize;
    // FILE *file = fopen("log.dat", "w+");//���Դ��룬��������������
    setbkmode(TRANSPARENT); //���û�������Ϊ͸��
    loadimage(&img, _T("resource/startMenu.jpg"), getwidth(), getheight());
    putimage(0, 0, &img);
    LOGFONT f; //��ʼ�������ʽ
    settextstyle(35, 0, _T("����"));
    setbkmode(TRANSPARENT); //�������屳��͸��
    gettextstyle(&f);
    f.lfQuality = ANTIALIASED_QUALITY; //�����
    f.lfWeight = FW_BOLD;              //����
    settextcolor(BROWN);               //��ɫ����
    settextstyle(&f);
    while (1)
    {
        mouse = getmessage();
        for (int i = 0; i < 4; i++) //�������Ƿ��������ص�
        {

            if (determineMouse(mouse, location[i][0], location[i][1], location[i][2], location[i][3]))
            {
                settextcolor(BLACK);
                outtextxy(location[i][0], location[i][1], text[i]);
                settextcolor(BROWN);
                if (mouse.message == WM_LBUTTONUP) //�������Ƿ�������
                {
                    switch (i)
                    {
                    case 0:
                        Status = LOGIN; //����״̬Ϊ��¼
                        return;
                    case 1:
                        Status = REGISTER; //����״̬Ϊ��¼ע��
                        return;
                    case 2:
                        Status = RANK;
                        return;
                    case 3:
                        Status = EXIT; //����װ̬Ϊ�˳�����ʱֻ��һ��������ֹ״̬
                        return;
                    }
                }
            }
            else
            {
                settextcolor(BROWN);
                outtextxy(location[i][0], location[i][1], text[i]);
            }
        }
        //�����ô��룬�������������ʱ�������
        // if (mouse.message == WM_LBUTTONDOWN)
        // {
        //     fprintf(file, "%d, %d\n", mouse.x, mouse.y);
        // }
    }
}

char *charInRange(char *str, int start, int end)
{
    if (end - start <= 0)
    {
        return "";
    }
    char *output = (char *)malloc(sizeof(char) * (end - start + 1));
    for (int i = 0; i < end - start; i++)
    {
        output[i] = str[start + i];
    }
    output[end] = '\0';
    return output;
}

void loginBox()
{
    /*���õ�¼��*/
    IMAGE login_box;
    ExMessage action;
    userData user_input; //�洢�û�����Ľṹ��
    int name_length = 0, passport_length = 0;
    char temp_name[21], temp_passport[19];
    char star[19] = "******************";
    FILE *file = fopen("user.dat", "ab+");
    LOGFONT login_font;

    settextstyle(30, 0, _T("Times New Roman"));
    setbkmode(TRANSPARENT);
    gettextstyle(&login_font);
    login_font.lfQuality = ANTIALIASED_QUALITY;
    login_font.lfWeight = FW_BOLD;
    settextcolor(BLACK);
    settextstyle(&login_font); //�����������

    setfillcolor(WHITE);

    loadimage(&login_box, _T("resource/login.png"), 350, 350); //������С��ĵ�¼��ͼƬ
    putimage(305, 95, &login_box);
    while (1)
    {
        action = getmessage();
        /*�����갴��*/
        if (action.message == WM_LBUTTONUP)
        {
            /*�˳���ť*/
            if (determineMouse(action, 606, 123, 637, 153))
            {
                Status = MAIN_MENU;
                return;
            }
            /*�����û�������*/
            else if (determineMouse(action, 351, 238, 614, 284))
            {
                outtextxy(351, 245, _T("|")); //���Դ��룬�ǵ�ɾ��
                while (1)
                {
                    action = getmessage();
                    if (action.message == WM_LBUTTONUP) //�ж�����������ʱ��λ��
                    {
                        if (determineMouse(action, 606, 123, 637, 153))
                        {
                            Status = MAIN_MENU;
                            return;
                        }
                        else if (!determineMouse(action, 351, 238, 614, 284))
                        {
                            break;
                        }
                    }
                    else if (action.message == WM_KEYDOWN) //�жϰ��������¼�
                    {
                        solidrectangle(351, 245, 351 + textwidth(charInRange(temp_name, 0, name_length)), 245 + textheight(charInRange(temp_name, 0, name_length)));
                        if (GetAsyncKeyState(VK_SHIFT))
                        {
                            if (action.vkcode >= 'A' && action.vkcode <= 'Z' && name_length < 20)
                            {
                                temp_name[name_length] = action.vkcode;
                                name_length++;
                            }
                        }
                        else if (action.vkcode >= 'A' && action.vkcode <= 'Z' && name_length < 20)
                        {
                            temp_name[name_length] = tolower(action.vkcode);
                            name_length++;
                        }
                        else if (action.vkcode >= '0' && action.vkcode <= '9' && name_length < 20)
                        {
                            temp_name[name_length] = action.vkcode;
                            name_length++;
                        }
                        else if (action.vkcode == VK_BACK && name_length > 0)
                        {
                            name_length--;
                        }
                        outtextxy(351, 245, charInRange(temp_name, 0, name_length));
                    }
                }
            }
            /*�������봰��*/
            else if (determineMouse(action, 351, 342, 614, 387))
            {
                outtextxy(351, 342, _T("|")); //���Դ��룬�ǵ�ɾ��
                while (1)
                {
                    action = getmessage();
                    if (action.message == WM_LBUTTONUP) //�ж�����������ʱ��λ��
                    {
                        if (determineMouse(action, 606, 123, 637, 153))
                        {
                            Status = MAIN_MENU;
                            return;
                        }
                        else if (!determineMouse(action, 351, 342, 614, 387))
                        {
                            break;
                        }
                    }
                    else if (action.message == WM_KEYDOWN) //�жϰ��������¼�
                    {
                        solidrectangle(351, 342, 351 + textwidth(charInRange(temp_passport, 0, passport_length + 1)), 342 + textheight(charInRange(temp_passport, 0, passport_length)));
                        if (GetAsyncKeyState(VK_SHIFT))
                        {
                            if (action.vkcode >= 'A' && action.vkcode <= 'Z' && passport_length < 20)
                            {
                                temp_passport[passport_length] = action.vkcode;
                                passport_length++;
                            }
                        }
                        else if (action.vkcode >= 'A' && action.vkcode <= 'Z' && passport_length < 20)
                        {
                            temp_passport[passport_length] = tolower(action.vkcode);
                            passport_length++;
                        }
                        else if (action.vkcode >= '0' && action.vkcode <= '9' && passport_length < 20)
                        {
                            temp_passport[passport_length] = action.vkcode;
                            passport_length++;
                        }
                        else if (action.vkcode == VK_BACK && passport_length > 0)
                        {
                            passport_length--;
                        }
                        outtextxy(351, 342, charInRange(star, 0, passport_length));
                    }
                }
            }
        }
    }
}

void registerBox()
{
    /*����ע���*/
    IMAGE register_box;
    ExMessage mouse;
    loadimage(&register_box, _T("resource/register.png"), 350, 350); //������С���ע���ͼƬ
    putimage(305, 95, &register_box);
    while (1)
    {
        mouse = getmessage();
        if (mouse.x > 606 && mouse.y > 123 && mouse.x < 637 && mouse.y < 153)
        {
            if (mouse.message == WM_LBUTTONUP)
            {
                Status = MAIN_MENU;
                return;
            }
        }
    }
}

void drawUserName()
{
    /*�û�������򶯻�*/
    ExMessage login_action;
    while (1)
    {
        login_action = getmessage();
    }
}

userData *loadUserData()
{
    /*�����û�����Ϊ��������ͷָ��(���ܻ������⣿)*/
    userData *head, *ptr, *temp;
    FILE *user_file = fopen("user.dat", "rb");
    if (!user_file)
    {
        /*�ж��Ƿ�����û������ļ������򴴽��ļ�*/
        FILE *user_file = fopen("user.dat", "wb");
        fclose(user_file);
        return NULL;
    }
    head = (userData *)malloc(sizeof(userData));
    if (fread(head, sizeof(userData), 1, user_file) == 0)
    {
        /*�ж��ļ��Ƿ�������ݣ����򷵻�NULL*/
        fclose(user_file);
        return NULL;
    }
    ptr = head;
    ptr->next = (userData *)malloc(sizeof(userData));
    while (fread(ptr->next, sizeof(userData), 1, user_file))
    {
        ptr = ptr->next;
        ptr->next = (userData *)malloc(sizeof(userData));
    }
    ptr->next = NULL;
    fclose(user_file);
    return head;
}

void addUserData(userData *head, userData data)
{
    /*Ϊ�ڴ��е�������ļ��е��û��������������*/
    userData *ptr, *temp;
    FILE *user_file = fopen("user.dat", "ab+");
    *temp = data;
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
        fwrite(head, sizeof(userData), 1, user_file);
        fclose(user_file);
        return;
    }
    ptr = head;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = temp;
    fwrite(temp, sizeof(userData), 1, user_file);
    fclose(user_file);
}
