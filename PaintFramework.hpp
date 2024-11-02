#pragma once
#ifndef _PAINTFRAME_
#define _PAINTFRAME_
#include <Windows.h>
#include <iostream>
#include <algorithm>
#include <vector>
using std::vector;

struct PRGB {
	int r;
	int g;
	int b;
};

struct CPOINT {
	int x;
	int y;
	PRGB color;
};

struct LINE_POINT {
	CPOINT src_Point;
	CPOINT dst_Point;
};

class PAINTER {
private:
	// 基本参数
	HBRUSH brush = 0;
	HPEN pen = 0;
	HDC dst_hdc = 0;
	HDC src_hdc = 0;
	HWND dst_hwnd = 0;

	// 双缓冲变量
	HBITMAP newBitmap, oldBitmap;

	// 引力域相关函数
	void ForcePointCheck(int current_x, int current_y, vector<POINT>* ForcePoints, int ForceDistant);

public:
	// 基本参数
	LONG paint_width = 0;
	LONG paint_height = 0;
	
	// 引力域相关变量
	POINT ForceClosestPoint = { -1,-1 };

	// 基本画图函数
	void setBrush(DWORD color);
	void setPen(int width, DWORD color, int style = PS_SOLID);
	void line(int src_x, int src_y, int x, int y, bool isMove = true);
	void move(int dst_x, int dst_y);
	void BresenhamLine(int src_x, int src_y, int x, int y, PRGB StartColor, PRGB EndColor, vector<POINT>* ForcePoints = nullptr, int ForceDistant = 20);
	void Cicle(int x, int y, int radius);
	void pixel(int x, int y, DWORD color);
	void CRectangle(int src_x, int src_y, int dst_x, int dst_y);

	// 动画函数
	void DiamondCircle(int x, int y, int r, int n, COLORREF color, bool isAnimated = false);
	void AnimationLine(int src_x, int src_y, int x, int y, int time, int width, COLORREF color);

	void BeginPainter(); // 开始作画
	void EndPainter(); // 停止作画，清空画板
	void ShowPainter(); // 直接展示作画，不清空画板

	// 初始化
	PAINTER(HWND hwnd);
	~PAINTER();
};

#endif // !_PAINTFRAME_
