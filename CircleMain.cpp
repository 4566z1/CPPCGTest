#include "CircleMain.hpp"

//圆相关参数
int n = 0;
int t = 0;
Circle* circle1;

void onInitCircle(HWND hwndModel, PAINTER* Painter) {
	default_random_engine random_engine(time(nullptr));
	uniform_int_distribution<int> random_generate(0, 255);
	RECT rect;
	GetClientRect(hwndModel, &rect);
	long width = rect.right - rect.left;
	long height = rect.bottom - rect.top;
	uniform_int_distribution<int> random_generate1(0, width);
	uniform_int_distribution<int> random_generate2(0, height);
	circle1 = new Circle(0, 10, 20, random_generate1(random_engine), random_generate2(random_engine));
}

void onPaintCircle(PAINTER* Painter) {
  if (n == 100) {
		t++;
		n = 0;
	}
	Painter->BeginPainter();
	Painter->setPen(5, RGB(255, 109, 0));
	Painter->setBrush(RGB(255, 109, 0));

	// 更新
	circle1->update(Painter->paint_width, Painter->paint_height, t);

	// 绘制
	Painter->Cicle(circle1->x, circle1->y, circle1->radius);

	Painter->EndPainter();
	n++;
	return;
}

void Circle::update(int width, int height, int time) {
	if (x + radius >= width)
		speed = -speed - accleration * time;
	if (x - radius < 0)
		speed = abs(speed) + accleration * time;
	if (y + radius >= height)
		speed = -speed - accleration * time;
	if (y + radius < 0)
		speed = abs(speed) + accleration * time;
	this->x += speed;
	this->y += speed;
	return;
}

Circle::Circle(int acc, int speed, int r, int x, int y): accleration(acc), speed(speed), radius(r), x(x), y(y) {
	return;
}
