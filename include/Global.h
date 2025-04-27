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
typedef enum GameStatus
{
    MAIN_MENU,
    GAMING,
    LOGIN,
    REGISTER,
    RANK,
    WIN,
    LOSE,
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

/*������ؽṹ��*/
typedef enum MineType
{
    MAX_GOLD,
    MID_GOLD,
    MIN_GOLD,
    DIAMOND,
    STONE,
} MineType;

typedef struct Mine
{
    MineType type;
    int value;
    int x;
    int y;
    int radius;
    float backSpeed;
} Mine;

typedef struct MineLink
{
    Mine mine;
    struct MineLink *next;
} MineLink;

/*������ؽṹ��*/
// ����״̬ö��
typedef enum HookState
{
    HOOK_ROTATE, // ������ת
    HOOK_EXTEND, // �����쳤
    HOOK_BACK,   // �����ջ�
    HOOK_CATCH,  // ����ץס����
} HookState;

// ���ӽṹ��
typedef struct Hook
{
    int x, y, midX, midY, sizeX, sizeY; // ����λ��
    float length;                       // ��ǰ���ӳ���
    float angle;                        // ��ת�Ƕȣ��Ƕ��ƣ�
    // float speed;                        // ��ת�ٶ�
    float extendSpeed; // ��չ�ٶ�
    float backSpeed;   // �ջ��ٶ�
    MineLink *mine;    //ץ���Ŀ���
    HookState state;   // ��ǰ����״̬
} Hook;

/*��������*/
int determineMouse(ExMessage msg, int startX, int startY, int endX, int endY);                                           //�����������Ƿ���ĳһ������
TCHAR *charInRange(char *str, int start, int end);                                                                       //����ָ����Χ�ڵ��ַ���
void TransparentImage(IMAGE *dstimg, int x, int y, IMAGE *srcimg, int widthDest, int heightDest, UINT transparentcolor); //����͸��ͼƬ
void EasyPutImage(int x, int y, const char *img, int sizeX, int sizeY);
float calculateDistance(int x1, int y1, int x2, int y2);

#endif
