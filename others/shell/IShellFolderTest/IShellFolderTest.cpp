// IShellFolderTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <shlobj.h>

int _tmain(int argc, _TCHAR* argv[])
{
	IShellFolder *pFolder;
	HRESULT hr = SHGetDesktopFolder(&pFolder);

	IEnumIDList * enumidList;
	pFolder->EnumObjects(NULL, SHCONTF_FOLDERS, &enumidList);

	ULONG ed = 0;
	STRRET str;
    LPITEMIDLIST rgelt = NULL;
	TCHAR path[MAX_PATH];
	while (S_OK == enumidList->Next(ed, &rgelt, &ed)) {
		SHGetPathFromIDList(rgelt, path);
		_tprintf(L"%s", path);
	}

	return 0;
} 

