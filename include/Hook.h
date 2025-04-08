#ifndef HOOK_H
#define HOOK_H

#include "Global.h"
#include "Mine.h"

#define PI 3.14159265358979323846 // Բ���ʳ���

// ������غ���
void initHook(Hook *hook); // ��ʼ������

void swangHook(Hook *hook, boolean isNewGame);                  // ������ת
void exbandHook(Hook *hook, MineLink *head, boolean isNewGame); // ������չ
void backHook(Hook *hook, boolean isNewGame);                   // �����ջ�
IMAGE *updateMiner(Hook *hook, boolean isNewGame);              // ���¿�״̬
void updateHook(Hook *hook);                                    // ���¹���״̬

void drawHook(Hook *hook);  // ���ƹ���
void drawMiner(IMAGE *img); // ���ƿ�

#endif
