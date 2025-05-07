#ifndef HOOK_H
#define HOOK_H

#include "Global.h"
#include "Mine.h"

#define PI 3.14159265358979323846 // Բ���ʳ���

// ������غ���
void initHook(Hook *hook); // ��ʼ������

void swangHook(Hook *hook, bool isNewGame);                  // ������ת
void extendHook(Hook *hook, MineLink *head, bool isNewGame); // ������չ
void backHook(Hook *hook, bool isNewGame);                   // �����ջ�
IMAGE *updateMiner(Hook *hook, bool isNewGame);              // ���¿�״̬                               // ���¹���״̬

void drawHook(Hook *hook);  // ���ƹ���
void drawMiner(IMAGE *img); // ���ƿ�

#endif
