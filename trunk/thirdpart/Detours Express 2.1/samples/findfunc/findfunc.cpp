//////////////////////////////////////////////////////////////////////////////
//
//  Detour Test Program (findfunc.cpp of findfunc.exe)
//
//  Microsoft Research Detours Package, Version 2.1.
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//

#include <windows.h>
#include <stdio.h>
#include <detours.h>
#include "target.h"

int __cdecl main(void)
{
    printf("findfunc.exe: Starting.\n");
    fflush(stdout);

    printf("DLLs:\n");
    for (HMODULE hModule = NULL; (hModule = DetourEnumerateModules(hModule)) != NULL;) {
        CHAR szName[MAX_PATH];
        GetModuleFileName(hModule, szName, sizeof(szName));
        printf("  %p: %s\n", hModule, szName);
    }

    DWORD dwCount = 10000;
    for (int i = 0; i < 3; i++) {
        printf("findfunc.exe: Calling (%d).\n", dwCount);
        dwCount = Target(dwCount) + 10000;
    }
    return 0;
}
//
///////////////////////////////////////////////////////////////// End of File.
