#pragma once

//���ļ��洢��Ҫ�õ��Ĺ��ߺ���

#include <graphics.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <vector>


#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")



#define WIN_WIDTH  1012//����  ��
#define WIN_HEIGHT 450//����  ��

#define OBSTACLE_COUNT 6//�ϰ���

#define WIN_SCORE 15  //ʤ������


void putimagePNG(int  picture_x, int picture_y, IMAGE* picture); //xΪ����ͼƬ��X���꣬yΪY����

void putimagePNG2(int x, int y, int winWidth, IMAGE* picture);

void putimagePNG2(int x, int y, IMAGE* picture);

//���ؾ����ϴε��������õ�ʱ��
int getDelay();




// ����PNGͼ��ȥ͸������
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y); //xΪҪ����ͼƬ��X���꣬yΪY����


//�ж����������Ƿ��ཻ      (�������ϽǺ����½� = ��������)
// ������
// 1.��һ���������Ͻ�  x  ����
// 2.��һ���������Ͻ�  y
// 3.��һ���������½�  x
// 4.��һ���������½�  y
// 
// 5.�ڶ����������Ͻ�  x
// 6.�ڶ����������Ͻ�  y
// 7.�ڶ����������½�  x
// 8.�ڶ����������½�  y
//����ֵ���ཻΪ��       ����ֵ�����ཻΪ��
bool rectIntersect(int x01, int y01, int x02, int y02, int x11, int y11, int x12, int y12);



//��������

//�����������ļ���ԴĿ¼  ��  ���ַ�����
void  playSound(const char* name);



//Ԥ������Ч  �������ļ���
void  preLoadSound(const char* name);




//��Ѫ��  ������
//1.2.���Ͻ�����
//3.4.���
// 5.����    �߿�
// 6.����    ��ɫ
// 7.��Ѫ����ɫ  ����
// 8.�����ɫ
// 9.����    Ѫ���ٷֱ�				���磺100 / 1000.0  ����1000������   ��1000�����100��Ѫ��
// 
void drawBloodBar(int x, int y, int width, int height, 
			      int lineWidth, int boardColor, 
				  int emptyColor, int fillColor, float percent);