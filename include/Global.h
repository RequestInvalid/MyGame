#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <tchar.h>
#include <Windows.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>

#define GAME_WIDTH 960
#define GAME_HEIGHT 540

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

/*��������*/
int determineMouse(ExMessage msg, int startX, int startY, int endX, int endY);                                           //�����������Ƿ���ĳһ������
char *charInRange(char *str, int start, int end);                                                                        //����ָ����Χ�ڵ��ַ���
void TransparentImage(IMAGE *dstimg, int x, int y, IMAGE *srcimg, int widthDest, int heightDest, UINT transparentcolor); //����͸��ͼƬ
void EasyPutImage(int x, int y, const char *img, int sizeX, int sizeY);
float calculateDistance(int x1, int y1, int x2, int y2);

#endif