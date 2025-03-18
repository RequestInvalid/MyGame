#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <tchar.h>
#include <Windows.h>
#include <graphics.h>
#include <conio.h>

#define GAME_WIDTH 960
#define GAME_HEIGHT 540

#ifndef MACRO
#define MACRO
//����ö��������״̬��
typedef enum
{
    MAIN_MENU,
    GAME,
    LOGIN,
    REGISTER,
    RANK,
    EXIT,
} GameStatus;

//�û����ݽṹ��
typedef struct userData
{
    char username[21];
    char pasport[19];
    long int highest_score = 0;
    struct userData *next;
} userData;
#endif

/*��������*/
void gameLoop();                                                               //��Ϸѭ���壬�л���Ϸ����״̬
int determineMouse(ExMessage msg, int startX, int startY, int endX, int endY); //�����������Ƿ���ĳһ������
void mainMenu();                                                               //���˵�
char *charInRange(char *str, int start, int end);                              //����ָ����Χ�ڵ��ַ���
                                                                               // void loginBox();                                                               //���õ�¼��
                                                                               // void registerBox();                              //����ע���
                                                                               // userData *loadUserData();                        //�����û�����Ϊ����������ͷָ��(���ܻ������⣿)
                                                                               // void addUserData(userData *head, userData data); //Ϊ�ڴ��е��������ļ��е��û���������������