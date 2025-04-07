#ifndef HOOK_H
#define HOOK_H

#include "Global.h"
#include "Mine.h"

#define PI 3.14159265358979323846 // Բ���ʳ���

// ����״̬ö��
typedef enum
{
    HOOK_ROTATE,  // ������ת
    HOOK_EXTEND,  // �����쳤
    HOOK_BACK,    // �����ջ�
    HOOK_GETMINE, // ����ץס����
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
    MineLink *mine;                     //ץ���Ŀ���
    float maxLength;

} Hook;

// ������غ���
void initHook(Hook *hook); // ��ʼ������

void swangHook(Hook *hook, boolean isNewGame);     // ������ת
void exbandHook(Hook *hook, boolean isNewGame);    // ������չ
void backHook(Hook *hook, boolean isNewGame);      // �����ջ�
IMAGE *updateMiner(Hook *hook, boolean isNewGame); // ���¿�״̬
void updateHook(Hook *hook);                       // ���¹���״̬

void drawHook(Hook *hook);  // ���ƹ���
void drawMiner(IMAGE *img); // ���ƿ�

#endif
