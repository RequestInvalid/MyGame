#include "Global.h"
#include <math.h>

#ifndef HOOK_H
#define HOOK_H

#define PI 3.14159265358979323846 // Բ���ʳ���

// ����״̬ö��
typedef enum
{
    HOOK_ROTATE, // ������ת
    HOOK_EXTEND, // �����쳤
    HOOK_BACK,   // �����ջ�
} HookState;

// ���ӽṹ��
typedef struct
{
    int x, y, midX, midY, sizeX, sizeY; // ����λ��
    float length;                       // ��ǰ���ӳ���
    float angle;                        // ��ת�Ƕȣ��Ƕ��ƣ�
    float speed;                        // ��ת�ٶ�
    float extendSpeed;                  // ��չ�ٶ�
    float backSpeed;                    // �ջ��ٶ�
    HookState state;                    // ��ǰ����״̬
} Hook;

// ������غ���
void initHook(Hook *hook);      // ��ʼ������
void swangHook(Hook *hook);     // ������ת
void exbandHook(Hook *hook);    // ������չ
void backHook(Hook *hook);      // �����ջ�
void updateHook(Hook *hook);    // ���¹���״̬
void drawHook(Hook *hook);      // ���ƹ���
IMAGE *updateMiner(Hook *hook); // ���¿�״̬
void drawMiner(IMAGE *img);     // ���ƿ�

#endif
