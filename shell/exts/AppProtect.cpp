// AppProtect.cpp : CAppProtect 的实现

#include "stdafx.h"
#include "AppProtect.h"
#include <utility\strutility.h>
#include <Debugoutput.h>
#include ".\global.h"

// CAppProtect
UINT CAppProtect::CopyCallback(HWND hwnd, UINT wFunc, UINT wFlags, LPCTSTR pszSrcFile,  DWORD dwSrcAttribs, LPCTSTR pszDestFile, DWORD dwDestAttribs) {
	TCHAR driver[MAX_PATH], folder[MAX_PATH], name[MAX_PATH], ext[MAX_PATH], path[MAX_PATH], comfilename[MAX_PATH];
	// 获取DLL路径
	GetModuleFileName(NULL, comfilename, MAX_PATH);

	_DEBUG_STREAM_TRC_("[AppProtected] programm path " << comfilename);
	return IDYES;

	_tsplitpath(comfilename, driver, folder, name, ext);
	
	// 生成目录
	_sntprintf(path, MAX_PATH, TEXT("%s\\%s"), driver, folder);

	// 如果操作任何一个本目录下的文件
	if (NULL != _tcsstr(pszSrcFile, path)) {
		return IDCANCEL;
	}

	return IDYES;
}
