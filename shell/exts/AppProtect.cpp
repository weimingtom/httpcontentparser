// AppProtect.cpp : CAppProtect ��ʵ��

#include "stdafx.h"
#include "AppProtect.h"
#include <utility\strutility.h>
#include <Debugoutput.h>
#include ".\global.h"

// CAppProtect
UINT CAppProtect::CopyCallback(HWND hwnd, UINT wFunc, UINT wFlags, LPCTSTR pszSrcFile,  DWORD dwSrcAttribs, LPCTSTR pszDestFile, DWORD dwDestAttribs) {
	TCHAR driver[MAX_PATH], folder[MAX_PATH], name[MAX_PATH], ext[MAX_PATH], path[MAX_PATH], comfilename[MAX_PATH];
	// ��ȡDLL·��
	GetModuleFileName(NULL, comfilename, MAX_PATH);

	_DEBUG_STREAM_TRC_("[AppProtected] programm path " << comfilename);
	return IDYES;

	_tsplitpath(comfilename, driver, folder, name, ext);
	
	// ����Ŀ¼
	_sntprintf(path, MAX_PATH, TEXT("%s\\%s"), driver, folder);

	// ��������κ�һ����Ŀ¼�µ��ļ�
	if (NULL != _tcsstr(pszSrcFile, path)) {
		return IDCANCEL;
	}

	return IDYES;
}
