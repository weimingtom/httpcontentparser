#include "stdafx.h"
#include "sysutility.h"
#include <assert.h>


namespace {
	DWORD GetScreenRecordDir(TCHAR *moduleDir, const int len, HMODULE hModule);	//
	DWORD GetImageRecordDir(TCHAR *moduleDir, const int len, HMODULE hModule);	// ����ͼ���Ŀ¼
	DWORD GenerateImageFile(TCHAR *file, const int len, HMODULE hModule);	// �Զ������ļ���
	DWORD GetHistoryRecordDir(TCHAR *moduleDir, const int len, HMODULE hModule);
	DWORD GetSoftwareDir(TCHAR *dir, const int len, HMODULE hModule);			// ��ȡ������ڵ�Ŀ¼
};



void StartEyecare(HMODULE hModule) {
	TCHAR filename[MAX_PATH];
	GetSoftwareDir(filename, MAX_PATH, hModule);
	WinExec(filename, SW_MAXIMIZE);
}


DWORD GenScreenSPFile(TCHAR *fullpath, const int len, HMODULE hModule) {
	TCHAR dir[MAX_PATH];
	GetScreenRecordDir(dir, MAX_PATH, hModule);

	// ��ȡʱ��
	SYSTEMTIME time;
	GetLocalTime(&time);
	TCHAR filename[MAX_PATH];
	_sntprintf(filename, MAX_PATH, TEXT("%02d%02d%04d%02d%02d%02d.bmp"), time.wMonth, time.wDay,time.wYear, time.wHour, time.wMinute, time.wSecond);

	// ��ȡ��Ŀ¼
	_sntprintf(fullpath, MAX_PATH, TEXT("%s%s"), dir, filename);
	return (DWORD)_tcslen(fullpath);
}
void ClearHistory(HMODULE hModule) {
	TCHAR dir[MAX_PATH], arg1 [MAX_PATH];
	GetHistoryRecordDir(dir, MAX_PATH, hModule);
	_sntprintf(arg1, MAX_PATH , TEXT("%s*"), dir);
	_execlp("del", arg1, TEXT("/q"));
}

void ClearScreen(HMODULE hModule) {
	TCHAR dir[MAX_PATH], arg1 [MAX_PATH];
	GetScreenRecordDir(dir, MAX_PATH, hModule);
	_sntprintf(arg1, MAX_PATH , TEXT("%s*"), dir);
	_execlp(TEXT("del"), arg1, TEXT("/q"));
}

const TCHAR * GetAppConfigFilename(TCHAR *fullpath, const int len, HMODULE hModule) {
	TCHAR filename[MAX_PATH], directory[MAX_PATH];
	GetModuleFileName((HMODULE)hModule, filename, MAX_PATH);
	GetFileNameDir(filename, directory, MAX_PATH);
	assert (_tcslen(directory) != 0);
	_sntprintf(fullpath, len, "%s\\%s", directory, CONFIG_FILE_NAME);
	return fullpath;
}

const TCHAR* GetFileNameDir(const TCHAR *filename, TCHAR *directory, const unsigned len) {
	TCHAR dir[MAX_PATH], driver[MAX_PATH];
	_tsplitpath(filename, driver, dir, NULL, NULL);
	_sntprintf(directory, len, TEXT("%s\\%s"), driver, dir);
	return directory;
}


const TCHAR * GetPageDirectory(TCHAR * filename, const unsigned len, const TCHAR * installPath) {
	assert (filename != NULL);
	_sntprintf(filename, MAX_PATH, TEXT("%s\\%s"), installPath, TEXT("History\\text\\"));
	return filename;
}

const TCHAR * GetImageDirectory(TCHAR * filename, const unsigned len, const TCHAR * installPath) {
	assert (filename != NULL);
	_sntprintf(filename, MAX_PATH, TEXT("%s\\%s"), installPath, TEXT("History\\images\\"));
	return filename;
}



const TCHAR * GetWebSiteRecordPath(TCHAR *filename, const unsigned len, const TCHAR * installPath) {
	assert (filename != NULL);
	_sntprintf(filename, MAX_PATH, TEXT("%s\\%s"), installPath, TEXT("History\\websites\\websites.xml"));
	return filename;
}

const TCHAR * GetRecordConfigfile(TCHAR *filename, const unsigned len, const TCHAR * installPath) {
	assert (filename != NULL);
	_sntprintf(filename, MAX_PATH, TEXT("%s\\%s"), installPath, TEXT("History\\config.xml"));
	return filename;
}
//////////////////////////////////////////////////
// utility functions

namespace {

// ��ȡ�������Ŀ¼
DWORD GetSoftwareDir(TCHAR *softDir, const int len, HMODULE hModule) {
	TCHAR moduleName[MAX_PATH], driver[MAX_PATH], dir[MAX_PATH];
	DWORD length = GetModuleFileName(hModule, moduleName, MAX_PATH);
	_tsplitpath(moduleName, driver, dir, NULL, NULL);
	_sntprintf(softDir, len, "%s%s", driver, dir);
	return (DWORD)_tcslen(softDir);
}

// ������Ļ��ͼ��Ŀ¼
DWORD GetScreenRecordDir(TCHAR *screendir, const int len, HMODULE hModule) {
	TCHAR moduleDir[MAX_PATH];
	GetSoftwareDir(moduleDir, len, hModule);
	_sntprintf(screendir, MAX_PATH, TEXT("%s%s\\"), moduleDir,TEXT("Screen\\"));
	if (_tchdir(screendir) == -1)
		_tmkdir(screendir);

	return (DWORD)_tcslen(screendir);
}

// ��ȡ������ʷ��
DWORD GetHistoryRecordDir(TCHAR *historyDir, const int len, HMODULE hModule) {
	TCHAR moduleDir[MAX_PATH];
	GetSoftwareDir(moduleDir, len, hModule);
	_sntprintf(historyDir, MAX_PATH, TEXT("%s%s\\"), moduleDir,TEXT("History\\"));
	if (_tchdir(historyDir) == -1)
		_tmkdir(historyDir);

	return (DWORD)_tcslen(historyDir);
}



};