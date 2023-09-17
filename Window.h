#pragma once
#include<tchar.h>
#include"Data.h"
#include <atlimage.h>
#include"em.h"
#undef UNICODE
#undef _UNICODE
using namespace std;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//int WINAPI Init_Window(HINSTANCE hInstance, int nCmdShow)
//
	
//}
bool convert2bmp(HBITMAP& bitmap, LPCWSTR url)
{
	CImage img;
	HRESULT ret = img.Load(url);
	bitmap = img.Detach();
	return true;
}

void WINAPI Create_Window(HINSTANCE hInstance,int nCmdShow)
{
	wnd.cbSize = sizeof(WNDCLASSEX);
	wnd.style = CS_HREDRAW | CS_VREDRAW;
	wnd.lpfnWndProc = WindowProc;
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hInstance = hInstance;
	wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wnd.lpszMenuName = NULL;
	wnd.lpszClassName = szCLassName;
	wnd.hIconSm = NULL;
	RegisterClassEx(&wnd);

	HWND hwnd = CreateWindowEx(0, szCLassName, szAppName, WS_SYSMENU | WS_POPUP, random() % cx, -100, 400, 300, NULL, NULL, hInstance, NULL);
	//HWND hW = FindWindowA(NULL, "Œ“¿¥£°£°£°");
	//extern HWND hwnd

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
}