#include "LoginAndRegister.h"
#include "Rank.h"
#include "UserData.h"
#include "GameEngine.h"

GameStatus Status = MAIN_MENU; //��ʼ��״̬
UserData *user;                //�û�����ָ��

static int location[4][4] = { //��¼���˵���ť����
    {240, 60, 310, 93},
    {240, 113, 310, 146},
    {220, 166, 326, 199},
    {240, 219, 310, 252}};
static TCHAR text[][12] = {_T("��¼"), _T("ע��"), _T("���а�"), _T("�˳�")}; //��¼���˵���ť�ı�

void gameLoop(); //��Ϸѭ���壬�л���Ϸ����״̬
void mainMenu(); //���˵�

int main()
{
    /*������*/
    initgraph(GAME_WIDTH, GAME_HEIGHT);
    HWND hwnd = GetHWnd();
    SetWindowText(hwnd, "�ƽ��");
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
            testLogin();
            break;
        case REGISTER:
            registerBox();
            break;
        case RANK:
            displayRank();
            break;
        case GAMING:
            mainEngine();
            break;
        }
    }
}

void mainMenu()
{
    /*���˵�*/
    ExMessage mouse;
    IMAGE img;
    LOGFONT f; //��ʼ�������ʽ

    loadimage(&img, _T("img/startMenu.jpg"), GAME_WIDTH, GAME_HEIGHT);
    settextstyle(35, 0, _T("����"));
    setbkmode(TRANSPARENT); //�������屳��͸��
    gettextstyle(&f);
    f.lfQuality = ANTIALIASED_QUALITY; //�����
    f.lfWeight = FW_BOLD;              //����
    settextcolor(BROWN);               //��ɫ����
    settextstyle(&f);
    while (true)
    {
        BeginBatchDraw();
        putimage(0, 0, &img);
        peekmessage(&mouse, EM_MOUSE); //��ȡ�����Ϣ
        for (int i = 0; i < 4; i++)
        {
            static int lastChoice = -1;
            if (determineMouse(mouse, location[i][0], location[i][1], location[i][2], location[i][3]))
            {
                if (lastChoice != i)
                {
                    lastChoice = i;
                    PlaySound(_T("sounds/slip.wav"), NULL, SND_ASYNC | SND_FILENAME);
                }
                settextcolor(BLACK);
                if (mouse.message == WM_LBUTTONUP) //�������Ƿ�������
                {
                    switch (i)
                    {
                    case 0:
                        Status = LOGIN; //����״̬Ϊ��¼
                        EndBatchDraw();
                        return;
                    case 1:
                        Status = REGISTER; //����״̬Ϊ��¼ע��
                        EndBatchDraw();
                        return;
                    case 2:
                        Status = RANK;
                        EndBatchDraw();
                        return;
                    case 3:
                        Status = EXIT; //����װ̬Ϊ�˳�
                        EndBatchDraw();
                        return;
                    }
                }
            }
            else
            {
                settextcolor(BROWN);
            }
            outtextxy(location[i][0], location[i][1], text[i]);
        }
        flushmessage(EM_MOUSE);
        FlushBatchDraw();
    }
}
