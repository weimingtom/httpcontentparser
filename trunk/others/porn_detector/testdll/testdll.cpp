#include "stdafx.h"
#include <windows.h> 
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

#define uint8 BYTE
#include ".\antiporndll.h"

int _tmain(int argc, TCHAR *argv[]) {	
	WIN32_FIND_DATA ffd;
	TCHAR szDir[MAX_PATH];
	TCHAR szDirPre[MAX_PATH];
	size_t length_of_arg;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError=0;
	
	// Initialize.
	PornDetectorBase* pPornDetector = NULL;
	if (!CreateObject(&pPornDetector)) {
		printf("Load Model Failed!\n");
		return 0;
	}
	
	StringCchLength(argv[1], MAX_PATH, &length_of_arg);
	
	if (length_of_arg > (MAX_PATH - 2)) {
		_tprintf(TEXT("Directory path is too long.\n"));
		return (-1);
	}
	
	StringCchCopy (szDir, MAX_PATH, argv[1]);	
	StringCchCat (szDir, MAX_PATH, TEXT("\\*.*"));
	
	// Find the first file in the directory.
	hFind = FindFirstFile(szDir, &ffd);
	
	double score;
	if (INVALID_HANDLE_VALUE == hFind) {
		dwError = GetLastError();
		_tprintf (TEXT("FindFirstFile failed (%u)\n"), dwError);
		return dwError;
	} 
	else {
		StringCchCopy (szDirPre, MAX_PATH, argv[1]);
		StringCchCat (szDirPre, MAX_PATH, ffd.cFileName);
		
		bool flag = pPornDetector->Detection(szDirPre, &score);
		printf("%s: %lf\n", ffd.cFileName, score);
		// printf("%lf\n", score);
		
		// List all the other files in the directory.
		while (FindNextFile(hFind, &ffd) != 0) {
			StringCchCopy (szDirPre, MAX_PATH, argv[1]);
			StringCchCat (szDirPre, MAX_PATH, ffd.cFileName);
			bool flag = pPornDetector->Detection(szDirPre, &score);		
			printf("%s: %lf\n", ffd.cFileName, score);
			// printf("%lf\n", score);
		}
		
		dwError = GetLastError();
		if (dwError != ERROR_NO_MORE_FILES) {
			goto Cleanup;
		}
	}
	
Cleanup:
	FindClose(hFind);
	DeleteObject();
	
	return dwError;
}
