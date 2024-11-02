#include "Diamond.hpp"

int i = 0;
// 快速绘制金刚石动画
void onDiamondPaint(PAINTER *Painter, int screen_width, int screen_height,int n, bool isAnimated) {
	default_random_engine random_engine(time(nullptr));
	uniform_int_distribution<int> random_generate(0, 255);
	Painter->BeginPainter();
	if(isAnimated)
		Painter->DiamondCircle(screen_width/ 2, screen_height / 2, 300, i, RGB(random_generate(random_engine), random_generate(random_engine), random_generate(random_engine)));
	else
		Painter->DiamondCircle(screen_width / 2, screen_height / 2, 300, n, RGB(random_generate(random_engine), random_generate(random_engine), random_generate(random_engine)));
	Painter->EndPainter();
	if(isAnimated)
		Sleep(100);
	i++;
	return;
}