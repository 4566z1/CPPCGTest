#pragma once
#ifndef _PAINTERMAIN_
#define _PAINTERMAIN_
#include <random>
#include <Windows.h>
#include <windowsx.h>
#include <iostream>
#include <vector>
#include "PaintFramework.hpp"

using std::vector;

// 画板相关参数
int l = 0;
vector<POINT> Points;

extern void onPainterMain(HWND hwndModel, PAINTER* Painter);
extern void LButtonEvent(PAINTER* Painter, LPARAM lParam);

#endif // !_PAINTERMAIN_
