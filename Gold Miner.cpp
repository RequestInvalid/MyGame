#include "LoginAndRegister.h"
#include "DataOperate.h"

GameStatus Status = MAIN_MENU; //��ʼ��״̬��

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