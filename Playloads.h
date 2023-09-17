#pragma once
#include"Data.h"
#pragma warning(disable : 4996)

using namespace std;

int random()
{
    if (prov == NULL)
        if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
            ExitProcess(1);
    int out;
    CryptGenRandom(prov, sizeof(out), (BYTE*)(&out));
    return out & 0x7fffffff;
}

void interval();
void tunnel_screen();
BOOL ReverseTCHAR(TCHAR* lpSrc);
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);
DWORD WINAPI messageBoxThread(LPVOID parameter);
LRESULT CALLBACK msgBoxHook(int nCode, WPARAM wParam, LPARAM lParam);
void Interval_Text();
void RecycleBin(int k, int m);