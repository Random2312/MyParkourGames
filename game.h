#pragma once

//本文件存储需要用到的工具函数

#include <graphics.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <vector>


#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")



#define WIN_WIDTH  1012//窗口  宽
#define WIN_HEIGHT 450//窗口  高

#define OBSTACLE_COUNT 6//障碍物

#define WIN_SCORE 15  //胜利分数


void putimagePNG(int  picture_x, int picture_y, IMAGE* picture); //x为载入图片的X坐标，y为Y坐标

void putimagePNG2(int x, int y, int winWidth, IMAGE* picture);

void putimagePNG2(int x, int y, IMAGE* picture);

//返回距离上次调用他所用的时间
int getDelay();




// 载入PNG图并去透明部分
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y); //x为要载入图片的X坐标，y为Y坐标


//判断两个矩形是否相交      (矩形左上角和右下角 = 整个矩形)
// 参数：
// 1.第一个区域左上角  x  坐标
// 2.第一个区域左上角  y
// 3.第一个区域右下角  x
// 4.第一个区域右下角  y
// 
// 5.第二个区域左上角  x
// 6.第二个区域左上角  y
// 7.第二个区域右下角  x
// 8.第二个区域右下角  y
//返回值：相交为真       返回值：不相交为假
bool rectIntersect(int x01, int y01, int x02, int y02, int x11, int y11, int x12, int y12);



//播放声音

//参数：声音文件资源目录  名  （字符串）
void  playSound(const char* name);



//预加载音效  参数：文件名
void  preLoadSound(const char* name);




//画血条  参数：
//1.2.左上角坐标
//3.4.宽高
// 5.轮廓    线宽
// 6.轮廓    颜色
// 7.掉血后颜色  背景
// 8.填充颜色
// 9.比例    血量百分比				比如：100 / 1000.0  就是1000是满格   在1000中填充100的血量
// 
void drawBloodBar(int x, int y, int width, int height, 
			      int lineWidth, int boardColor, 
				  int emptyColor, int fillColor, float percent);