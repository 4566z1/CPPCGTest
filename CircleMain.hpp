#pragma once
#ifndef _DATASTRUCT_
#define _DATASTRUCT_
#include <cmath>
#include <ctime>
#include <random>
#include "PaintFramework.hpp"
using std::default_random_engine;
using std::uniform_int_distribution;


extern void onInitCircle(HWND hwndModel, PAINTER* Painter);
extern void onPaintCircle(PAINTER* Painter);

class Circle {
private:
	int accleration;
	int speed;
public:
	int radius;
	int x;
	int y;
	void update(int width, int height, int time);
	Circle(int acc, int speed, int r, int x, int y);
};

#endif // !_DATASTRUCT_
