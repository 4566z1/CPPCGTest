#include "PaintFramework.hpp"
#define PI 3.1415926535

void PAINTER::CRectangle(int src_x, int src_y, int dst_x, int dst_y) {
	Rectangle(this->src_hdc, src_x, src_y, dst_x, dst_y);
	return;
}

void PAINTER::DiamondCircle(int x, int y, int r, int n, COLORREF color, bool isAnimated) {
	double singleAngle = 2 * PI / n;
	vector<POINT> Points;
	POINT Point;
	for (int i = 0; i < n; i++){
		Point.x = x + r * cos(singleAngle * i);
		Point.y = y + r * sin(singleAngle * i);
		Points.push_back(Point);
	}

	setPen(1, color);
	for (auto Point1 : Points){
		for (auto Point2 : Points){
			if (Point1.x == Point2.x && Point1.y == Point2.y)
				continue;
			line(Point1.x, Point1.y, Point2.x, Point2.y);
			if(isAnimated)
				this->ShowPainter();
		}
	}
	return;
}

void PAINTER::AnimationLine(int src_x, int src_y, int x, int y, int width, int time, COLORREF color) {
	POINT P = { 0 };
	float a = y - src_y;
	float b = x - src_x;
	float c = x * src_y - y * src_x;
	float length = abs(a) > abs(b) ? a : b;

	for (int i = 0; i < abs(length); i++) {
		// Bresenham算法
		if (abs(a) < abs(b)) {
			// X 距离差大
			if (length > 0) {
				P.x = src_x + i;
				P.y = -static_cast<int>((-(a / b) * P.x - (c / b)) + 0.5);
			}
			else {
				P.x = src_x - i;
				P.y = -static_cast<int>((-(a / b) * P.x - (c / b)) + 0.5);
			}
		}
		else if (abs(a) > abs(b)) {
			// Y 距离差大
			if (length > 0) {
				P.y = src_y + i;
				P.x = static_cast<int>((-(b / a) * -P.y - (c / a)) + 0.5);
			}
			else {
				P.y = src_y - i;
				P.x = static_cast<int>((-(b / a) * -P.y - (c / a)) + 0.5);
			}
		}
		else {
			// 修复45角闪烁
			P.x = (b > 0) ? src_x + i : src_x - i;
			P.y = (a > 0) ? src_y + i : src_y - i;
		}

		this->pixel(P.x, P.y, color);
		this->ShowPainter();
		Sleep(time);
	}
	return;
}

void PAINTER::ForcePointCheck(int x, int y, vector<POINT>* ForcePoints, int ForceDistant) {
	// 引力域算法
	if (ForcePoints) {
		vector<POINT> ValidPoints;
		int distance;
		ForceDistant = pow(ForceDistant, 2);
		// 取有效半径内点集
		for (auto Point : *ForcePoints) {
			distance = (Point.x - x) * (Point.x - x) + (Point.y - y) * (Point.y - y);
			if (distance < ForceDistant) {
				ValidPoints.push_back(Point);
			}
		}

		std::sort(ValidPoints.begin(), ValidPoints.end(), [&x, &y](POINT a, POINT b) -> bool {
			int distance1 = (a.x - x) * (a.x - x) + (a.y - y) * (a.y - y);
			int distance2 = (b.x - x) * (b.x - x) + (b.y - y) * (b.y - y);
			return distance1 > distance2;
			});

		if (ValidPoints.size()) {
			POINT validpoint = ValidPoints.front();
			this->ForceClosestPoint = validpoint;
			return;
		}
	}
	this->ForceClosestPoint = { -1,-1 };
	return;
}

void PAINTER::BresenhamLine(int src_x, int src_y, int x, int y, PRGB StartColor, PRGB EndColor, vector<POINT>* ForcePoints, int ForceDistant) {
	CPOINT P;
	float color_k, color_b;

	// 引力域算法
	ForcePointCheck(x, y, ForcePoints, ForceDistant);
	if (this->ForceClosestPoint.x >= 0 && this->ForceClosestPoint.y >= 0) {
		x = ForceClosestPoint.x;
		y = ForceClosestPoint.y;
	}

	float a = y - src_y;
	float b = x - src_x;
	float c = x*src_y - y*src_x;
	float length = abs(a) > abs(b) ? a : b;

	for (int i = 0; i < abs(length); i++) {
		// Bresenham算法(需要优化)
		if (abs(a) < abs(b)) {
			// X 距离差大
			if (length > 0) {
				P.x = src_x + i;
				P.y = -static_cast<int>((-(a / b) * P.x - (c / b)) + 0.5);
			}
			else {	
				P.x = src_x - i;
				P.y = -static_cast<int>((-(a / b) * P.x - (c / b)) + 0.5);
			}
		}
		else if(abs(a) > abs(b)) {
			// Y 距离差大
			if (length > 0) {
				P.y = src_y + i;
				P.x = static_cast<int>((-(b / a) * -P.y - (c / a)) + 0.5);
			}
			else {
				P.y = src_y - i;
				P.x = static_cast<int>((-(b / a) * -P.y - (c / a)) + 0.5);
			}
		}
		else {
			// 修复45角闪烁
			P.x = (b > 0) ? src_x + i : src_x - i;
			P.y = (a > 0) ? src_y + i : src_y - i;
		}

		// 线性插值
		color_k = abs((static_cast<float>(x) - P.x) / (x - src_x));
		color_b = abs((P.x - static_cast<float>(src_x)) / (x - src_x));
		P.color.r = color_k * StartColor.r + color_b * EndColor.r;
		P.color.g = color_k * StartColor.g + color_b * EndColor.g;
		P.color.b = color_k * StartColor.b + color_b * EndColor.b;

		this->pixel(P.x, P.y, RGB(P.color.r, P.color.g, P.color.b));
	}
	return;
}

void PAINTER::pixel(int x, int y, COLORREF color) {
	SetPixel(this->src_hdc, x, y, color);
	return;
}

void PAINTER::BeginPainter() {
	RECT rect{ 0 };

	// 获取绘图区域
	GetClientRect(this->dst_hwnd, &rect);
	paint_width = rect.right - rect.left;
	paint_height = rect.bottom - rect.top;

	// 创建兼容性位图
	this->src_hdc = CreateCompatibleDC(this->dst_hdc);
	newBitmap = CreateCompatibleBitmap(this->dst_hdc, paint_width, paint_height);
	this->oldBitmap = (HBITMAP)SelectObject(this->src_hdc, newBitmap);
	return;
}

void PAINTER::EndPainter() {
	// 显示
	BitBlt(this->dst_hdc, 0, 0, this->paint_width, this->paint_height, this->src_hdc, 0, 0, SRCCOPY);
	// 清理工作
	SelectObject(this->src_hdc, this->oldBitmap);
	DeleteObject(this->newBitmap);
	DeleteObject(this->src_hdc);
	return;
}

void PAINTER::ShowPainter() {
	BitBlt(this->dst_hdc, 0, 0, this->paint_width, this->paint_height, this->src_hdc, 0, 0, SRCCOPY);
	return;
}

void PAINTER::Cicle(int x, int y, int radius) {
	Ellipse(this->src_hdc, x - radius, y - radius, x + radius, y + radius);
	return;
}

void PAINTER::setPen(int width, DWORD color, int style) {
	this->pen = CreatePen(style, width, color);
	SelectObject(this->src_hdc, this->pen);
	return;
}

void PAINTER::setBrush(DWORD color) {
	this->brush = CreateSolidBrush(color);
	SelectObject(this->src_hdc, this->brush);
	return;
}

void PAINTER::move(int dst_x, int dst_y) {
	MoveToEx(this->src_hdc, dst_x, dst_y, nullptr);
	return;
}

void PAINTER::line(int src_x, int src_y, int x, int y, bool isMove) {
	if (isMove) {
		MoveToEx(this->src_hdc, src_x, src_y, nullptr);
	}
	LineTo(this->src_hdc, x, y);
	return;
}

PAINTER::PAINTER(HWND hwnd) : dst_hwnd(hwnd) {
	this->dst_hdc = GetDC(hwnd);
	return;
}

PAINTER::~PAINTER() {
	if (this->src_hdc) {
		ReleaseDC(this->dst_hwnd, this->src_hdc);
	}
	return;
}