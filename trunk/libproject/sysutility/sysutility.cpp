#include "stdafx.h"
#include "sysutility.h"
#include <utility\strutility.h>
#include <windowtitle.h>
#include <assert.h>
#include <process.h>


#define SCREEN_SAVE_TYPE	TEXT("jpg")
namespace {
	void GetScreenRecordDir(TCHAR *moduleDir, const int len, HMODULE hModule);	//
	void GetImageRecordDir(TCHAR *moduleDir, const int len, HMODULE hModule);	// ����ͼ���Ŀ¼
	void GenerateImageFile(TCHAR *file, const int len, HMODULE hModule);	// �Զ������ļ���
	void GetHistoryRecordDir(TCHAR *moduleDir, const int len, HMODULE hModule);
	void GenerateFullPath(TCHAR *fullpath, const int len, const TCHAR * dir, const TCHAR * filename);
	void GetFilespathInDir(const TCHAR * dir, std::vector<strutility::_tstring> * files);
};



void StartEyecare(HMODULE hModule) {
	// ���ȼ��Ӧ�ó����Ƿ��Ѿ�����
	HWND hOld = GetEyecareApp();
	if (NULL != hOld) {
		return;
	}

	TCHAR install_path[MAX_PATH], fullpath[MAX_PATH];
	GetInstallPath(install_path, MAX_PATH, hModule);

	_sntprintf(fullpath, MAX_PATH, "%s%s", install_path, EYECARE_APP_FILENAME);
	WinExec(fullpath, SW_MAXIMIZE);
}


DWORD GenScreenSPFile(TCHAR *fullpath, const int len, HMODULE hModule) {
	TCHAR dir[MAX_PATH];
	GetScreenRecordDir(dir, MAX_PATH, hModule);

	// ��ȡʱ��
	SYSTEMTIME time;
	GetLocalTime(&time);
	TCHAR filename[MAX_PATH];
	_sntprintf(filename, MAX_PATH, TEXT("%02d%02d%04d%02d%02d%02d.%s"), 
		time.wMonth, time.wDay,time.wYear, 
		time.wHour, time.wMinute, time.wSecond,
		SCREEN_SAVE_TYPE);

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
	TCHAR dir[MAX_PATH];
	GetScreenRecordDir(dir, MAX_PATH, hModule);
	
	// ��ȡ�����ļ�
	using namespace std;
	using namespace strutility;

	vector<_tstring> vecfilepaths;
	GetFilespathInDir(dir, &vecfilepaths);

	vector<_tstring>::iterator iter = vecfilepaths.begin();
	for (; iter != vecfilepaths.end(); ++iter) {
		DeleteFile(iter->c_str());
	}
}

const TCHAR * GetAppConfigFilename(TCHAR *fullpath, const int len, HMODULE hModule) {
	TCHAR filename[MAX_PATH], directory[MAX_PATH];
	GetModuleFileName((HMODULE)hModule, filename, MAX_PATH);
	GetFileNameDir(filename, directory, MAX_PATH);
	assert (_tcslen(directory) != 0);
	GenerateFullPath(fullpath, len, directory, CONFIG_FILE_NAME);
	return fullpath;
}

const TCHAR* GetFileNameDir(const TCHAR *filename, TCHAR *directory, const unsigned len) {
	TCHAR dir[MAX_PATH], driver[MAX_PATH];
	_tsplitpath(filename, driver, dir, NULL, NULL);
	_sntprintf(directory, len, TEXT("%s%s"), driver, dir);
	return directory;
}


const TCHAR * GetPageDirectory(TCHAR * filename, const unsigned len, const TCHAR * installPath) {
	assert (filename != NULL);
	assert ( true == strutility::endwith(installPath, TEXT("\\")));
	GenerateFullPath(filename, MAX_PATH, installPath, TEXT("History\\text\\"));
	return filename;
}

const TCHAR * GetImageDirectory(TCHAR * filename, const unsigned len, const TCHAR * installPath) {
	assert (filename != NULL);
	assert ( true == strutility::endwith(installPath, "\\"));
	GenerateFullPath(filename, MAX_PATH, installPath, TEXT("History\\images\\"));
	return filename;
}


const TCHAR * GetWebSiteRecordPath(TCHAR *filename, const unsigned len, const TCHAR * installPath) {
	assert (filename != NULL);
	assert ( true == strutility::endwith(installPath, "\\"));
	GenerateFullPath(filename, MAX_PATH, installPath, TEXT("History\\websites\\websites.xml"));
	return filename;
}

// ��ȡ��¼ͼƬ ������ʷ���ļ���·��
const TCHAR * GetRecordConfigfile(TCHAR *filename, const unsigned len, const TCHAR * installPath) {
	assert (filename != NULL);
	assert (strutility::endwith(installPath, "\\") == true);
	GenerateFullPath(filename, MAX_PATH, installPath, TEXT("History\\config.xml"));
	return filename;
}

// ��ȡ�������Ŀ¼
const TCHAR * GetInstallPath(TCHAR *install_path, const int len, HMODULE hModule) {
	TCHAR moduleName[MAX_PATH];
	DWORD length = GetModuleFileName(hModule, moduleName, MAX_PATH);
	GetFileNameDir(moduleName, install_path, MAX_PATH);
	return install_path;
}

// ��ǰ��Eyecare�Ƿ�������
HWND GetEyecareApp() {
	HWND hwnd = FindWindow(EYECARE_MAIN_WND_CLASS, NULL);
	return hwnd;
}
//////////////////////////////////////////////////
// utility functions

namespace {

void GenerateFullPath(TCHAR *fullpath, const int len, const TCHAR * dir, const TCHAR * filename) {
	assert(strutility::endwith(dir, "\\") == true);
	_sntprintf(fullpath, len, TEXT("%s%s"), dir, filename);
}

// ������Ļ��ͼ��Ŀ¼
void GetScreenRecordDir(TCHAR *screendir, const int len, HMODULE hModule) {
	TCHAR moduleDir[MAX_PATH];
	GetInstallPath(moduleDir, len, hModule);
	_sntprintf(screendir, MAX_PATH, TEXT("%s%s"), moduleDir,TEXT("Screen\\"));
	if (_tchdir(screendir) == -1)
		_tmkdir(screendir);
}

// ��ȡ������ʷ��
void GetHistoryRecordDir(TCHAR *historyDir, const int len, HMODULE hModule) {
	TCHAR moduleDir[MAX_PATH];
	GetInstallPath(moduleDir, len, hModule);
	_sntprintf(historyDir, MAX_PATH, TEXT("%s%s"), moduleDir,TEXT("History\\"));
	if (_tchdir(historyDir) == -1)
		_tmkdir(historyDir);
}

void GetFilespathInDir(const TCHAR * dir, std::vector<strutility::_tstring> * files) {
	using namespace std;
	using namespace strutility;

	TCHAR fileexp[MAX_PATH];
	_sntprintf(fileexp, MAX_PATH, "%s*.%s", dir, SCREEN_SAVE_TYPE);
	WIN32_FIND_DATA find_data;
	HANDLE hFind = FindFirstFile(fileexp, &find_data);

	if (INVALID_HANDLE_VALUE == hFind) {
		return;
	}

	// �ǵý���һ���ļ���ӽ�ȥ
	do {
		files->push_back(find_data.cFileName);
	} while (FindNextFile(hFind, &find_data));

	FindClose(hFind);
}

};