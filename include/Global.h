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
    int highest_score = 0;
    struct userData *next;
} userData;
#endif

/*��������*/
int determineMouse(ExMessage msg, int startX, int startY, int endX, int endY);            //�����������Ƿ���ĳһ������
char *charInRange(char *str, int start, int end);                                         //����ָ����Χ�ڵ��ַ���
void TransparentImage(IMAGE *dstimg, int x, int y, IMAGE *srcimg, UINT transparentcolor); //����͸��ͼƬ