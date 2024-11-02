#include "PaintFramework.hpp"
#include "3DCube.hpp"
#include <random>
#define HEIGHT 800
#define WIDTH 1000

PAINTER* Painter;
HWND hwndModel;
extern LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
extern void CALLBACK PaintProc(HWND, UINT, UINT_PTR, DWORD);
extern void onPaint();

int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int iCmdShow) {

	MSG msg;
	WNDCLASS wndclass{ 0 };
	HDC hdc = 0;

	wndclass.hInstance = hInstance; 
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); 
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL; 
	wndclass.lpszClassName = L"Window";
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;

	if (!RegisterClass(&wndclass)) {
		return 0;
	}

	hwndModel = CreateWindow(L"Window",
		L"窗口",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WIDTH,
		HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwndModel, SW_SHOW);
	UpdateWindow(hwndModel);
	
	Painter = new PAINTER(hwndModel);

	// 随机坐标初始化圆 
	//

	UINT_PTR TimerId = SetTimer(hwndModel, NULL, 1000, PaintProc);
	
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	delete Painter;
	KillTimer(hwndModel, TimerId);
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	LPPAINTSTRUCT ps{ 0 };

	switch (msg) {
	//case WM_LBUTTONDOWN:
	//	break;
	case WM_PAINT:
		if (Painter) {
			onPaint();
		}
		break;
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void onPaint() {
	onCubePaint(Painter);
	return;
}

void CALLBACK PaintProc(HWND hwnd, UINT msg, UINT_PTR timerId, DWORD time) {
	InvalidateRect(hwnd, nullptr, false);
	return;
}
