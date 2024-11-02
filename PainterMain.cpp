#include "PainterMain.hpp"

using std::default_random_engine;
using std::uniform_int_distribution;

default_random_engine random_engine(time(nullptr));
uniform_int_distribution<int> random_generate(0, 255);

PRGB startColor = { 0,0,0 };
PRGB endColor = { 255,255,255 };

void LButtonEvent(PAINTER* Painter, LPARAM lParam) {
	POINT Point;
	Point.x = GET_X_LPARAM(lParam);
	Point.y = GET_Y_LPARAM(lParam);
	if (Painter->ForceClosestPoint.x >= 0 && Painter->ForceClosestPoint.y >= 0) {
		Points.push_back(Painter->ForceClosestPoint);
	}
	else {
		Points.push_back(Point);
	}
}


//画板
void onPainterMain(HWND hwndModel, PAINTER *Painter) {
	POINT cursorPoint;
	GetCursorPos(&cursorPoint);
	Painter->BeginPainter();

	if (l == 10) {
		startColor.r = random_generate(random_engine);
		startColor.g = random_generate(random_engine);
		startColor.b = random_generate(random_engine);
		endColor.r = random_generate(random_engine);
		endColor.g = random_generate(random_engine);
		endColor.b = random_generate(random_engine);
		l = 0;
	}
	ScreenToClient(hwndModel, &cursorPoint);

	POINT Point1;
	POINT Point2;
	for (int i = 0; i < Points.size(); i+=2) {
		Point1 = Points.at(i);
		if (i + 2 > Points.size()) {
			// 创建备份移除最后一个点
			vector<POINT> buffer = Points;
			buffer.pop_back();
			Painter->BresenhamLine(Point1.x, Point1.y, cursorPoint.x, cursorPoint.y, startColor, endColor, &buffer, 20);
		}
		else {
			Point2 = Points.at(i + 1);
			Painter->BresenhamLine(Point1.x, Point1.y, Point2.x, Point2.y, startColor, endColor);
		}
	}

	l++;
	Painter->EndPainter();
	return;
}