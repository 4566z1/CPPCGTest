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
	// ��������
	HBRUSH brush = 0;
	HPEN pen = 0;
	HDC dst_hdc = 0;
	HDC src_hdc = 0;
	HWND dst_hwnd = 0;

	// ˫�������
	HBITMAP newBitmap, oldBitmap;

	// ��������غ���
	void ForcePointCheck(int current_x, int current_y, vector<POINT>* ForcePoints, int ForceDistant);

public:
	// ��������
	LONG paint_width = 0;
	LONG paint_height = 0;
	
	// ��������ر���
	POINT ForceClosestPoint = { -1,-1 };

	// ������ͼ����
	void setBrush(DWORD color);
	void setPen(int width, DWORD color, int style = PS_SOLID);
	void line(int src_x, int src_y, int x, int y, bool isMove = true);
	void move(int dst_x, int dst_y);
	void BresenhamLine(int src_x, int src_y, int x, int y, PRGB StartColor, PRGB EndColor, vector<POINT>* ForcePoints = nullptr, int ForceDistant = 20);
	void Cicle(int x, int y, int radius);
	void pixel(int x, int y, DWORD color);
	void CRectangle(int src_x, int src_y, int dst_x, int dst_y);

	// ��������
	void DiamondCircle(int x, int y, int r, int n, COLORREF color, bool isAnimated = false);
	void AnimationLine(int src_x, int src_y, int x, int y, int time, int width, COLORREF color);

	void BeginPainter(); // ��ʼ����
	void EndPainter(); // ֹͣ��������ջ���
	void ShowPainter(); // ֱ��չʾ����������ջ���

	// ��ʼ��
	PAINTER(HWND hwnd);
	~PAINTER();
};

#endif // !_PAINTFRAME_
