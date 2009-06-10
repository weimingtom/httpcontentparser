#include "stdafx.h"
#include ".\apputility.h"
#include ".\xinstall.h"
#include <utility\strutility.h>
#include <app_constants.h>
#include <assert.h>
#include <process.h>
#include <stdlib.h> 
#include  <io.h>



#define SCREEN_SAVE_TYPE	TEXT("jpg")
namespace {
	void GetScreenRecordDir(TCHAR *moduleDir, const int len);	//
	void GetImageRecordDir(TCHAR *moduleDir, const int len);	// ����ͼ���Ŀ¼
	void GetTextRecordDir(TCHAR *moduleDir, const int len);
	void GenerateImageFile(TCHAR *file, const int len);	// �Զ������ļ���
	void GetHistoryRecordDir(TCHAR *moduleDir, const int len);
	void GenerateFullPath(TCHAR *fullpath, const int len, const TCHAR * dir, const TCHAR * filename);
	
	HKEY GetAutoRunKey();
};



// �����Ƿ����Զ����е�
BOOL isAutoRun() {
	TCHAR fullpath[MAX_PATH];
	GetModuleFileName(NULL, fullpath, MAX_PATH);

	// ��ȡ�Զ�����HKEY
	HKEY hKey = GetAutoRunKey();
	if (NULL == hKey) {
		return FALSE;
	}

	TCHAR value[MAX_PATH] = {0};
	DWORD length = MAX_PATH;
	DWORD type = REG_SZ;
	LONG result = RegQueryValueEx (hKey, REGISTER_MAINUI_KEY, NULL, &type, (LPBYTE)value, &length);
	RegCloseKey(hKey);

	
	if (ERROR_SUCCESS != result) {
		return FALSE;
	}

	if (_tcscmp(fullpath, value) != 0) {
		return FALSE;
	}

	return TRUE;
}



// �����Զ�����
INT RegisterAutoRun(const TCHAR * fullpath, BOOL auto_run) {
	HKEY hKey = GetAutoRunKey();
	if (NULL == hKey) {
		return -1;
	}

	// ����ע�����
	if ( TRUE == auto_run) {
		if (ERROR_SUCCESS == RegSetValueEx( hKey,REGISTER_MAINUI_KEY , 0, REG_SZ, (const BYTE*)(LPCSTR)fullpath, (DWORD)_tcslen(fullpath))) {
			RegCloseKey(hKey);
			return 0;
		} else {
			return -1;
		}
	} else {
		if (ERROR_SUCCESS == RegDeleteKey(hKey, REGISTER_MAINUI_KEY)) {
			RegCloseKey(hKey);
			return 0;
		} else {
			return -1;
		}
	}
}



namespace {
BOOL CALLBACK EnumWndProc(HWND hwnd, LPARAM lParam)
{
	HANDLE h = GetProp(hwnd, MAIN_WINDOW_PROP_NAME);
	if( h == (HWND)MAIN_WINDOW_PROP_VALUE)
	{
		*(HWND*)lParam = hwnd;
		return false;
	}
	return true;
}

};
// ��ȡ�����򴰿�
HWND GetMainUIHWND() {
	HWND hwnd = NULL;
	EnumWindows(EnumWndProc, (LPARAM)&hwnd);
	return hwnd;
}

// ����������
void GetMainUIPath(TCHAR * fullpath, const int len) {
	TCHAR installpath[MAX_PATH];
	GetInstallPath(installpath, len);
	_sntprintf(fullpath, len, "%s%s", installpath, APPLICATION_MAINUI_NAME);
}

const TCHAR * GetUninstallUtility(TCHAR * fullpath, const int len) {
	TCHAR installpath[MAX_PATH];
	GetInstallPath(installpath, len);
	_sntprintf(fullpath, len, "%s%s", installpath, UNINSTALL_UTILITY);
	return fullpath;
}

void StartMainUI() {
	TCHAR  fullpath[MAX_PATH];
	GetMainUIPath(fullpath, MAX_PATH);
	WinExec(fullpath, SW_SHOW);
}

void LockComputer() {
	TCHAR install_path[MAX_PATH], fullpath[MAX_PATH], cmdLine[MAX_PATH * 2];
	GetInstallPath(install_path, MAX_PATH);
	
	_sntprintf(fullpath, MAX_PATH, "%s%s", install_path, LOCKPC_APP_FILENAME);
	_sntprintf(cmdLine, MAX_PATH *2, "%s %s", fullpath, LAUNCH_PARAM);
	WinExec(cmdLine, SW_MAXIMIZE);
}

void StartEyecare() {
	// ���ȼ��Ӧ�ó����Ƿ��Ѿ�����
	HWND hOld = GetEyecareApp();
	if (NULL != hOld) {
		return;
	}

	TCHAR install_path[MAX_PATH], fullpath[MAX_PATH], cmdLine[MAX_PATH * 2];
	GetInstallPath(install_path, MAX_PATH);

	_sntprintf(fullpath, MAX_PATH, "%s%s", install_path, EYECARE_APP_FILENAME);
	_sntprintf(cmdLine, MAX_PATH *2, "%s %s", fullpath, LAUNCH_PARAM);
	WinExec(cmdLine, SW_MAXIMIZE);
}

DWORD GetScreenRecordPath(TCHAR * fullpath, const int len) {
	GetScreenRecordDir(fullpath, MAX_PATH);
	return (DWORD) strlen (fullpath);
}
DWORD GenScreenSPFile(TCHAR *fullpath, const int len) {
	TCHAR dir[MAX_PATH];
	GetScreenRecordDir(dir, MAX_PATH);

	// ��ȡʱ��
	SYSTEMTIME time;
	GetLocalTime(&time);
	TCHAR filename[MAX_PATH];
	_sntprintf(filename, MAX_PATH, TEXT("%04d%02d%02d%02d%02d%02d.%s"), 
		time.wYear, time.wMonth, time.wDay, 
		time.wHour, time.wMinute, time.wSecond,
		SCREEN_SAVE_TYPE);

	// ��ȡ��Ŀ¼
	_sntprintf(fullpath, MAX_PATH, TEXT("%s%s"), dir, filename);
	return (DWORD)_tcslen(fullpath);
}
void ClearHistory() {
	TCHAR dir[MAX_PATH] = {0}, filepath[MAX_PATH] = {0};
	GetImageRecordDir(dir, MAX_PATH);
	DeleteFiles(dir, TEXT("*.*"));

	GetTextRecordDir(dir, MAX_PATH);
	DeleteFiles(dir, TEXT("*.*"));

	GetWebSiteFile(filepath, MAX_PATH);
	DeleteFile(filepath);

	GetPornWebSiteFile(filepath, MAX_PATH);
	DeleteFile(filepath);

	GetSearchWordFile(filepath, MAX_PATH);
	DeleteFile(filepath);
}

void ClearScreen() {
	TCHAR dir[MAX_PATH];
	GetScreenRecordDir(dir, MAX_PATH);
	DeleteFiles(dir, TEXT("*.jpg"));
}

const TCHAR * GetAppConfigFilename(TCHAR *fullpath, const int len) {
	TCHAR filename[MAX_PATH], directory[MAX_PATH];
	GetModuleFileName(NULL, filename, MAX_PATH);
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

const TCHAR * GetSearchWordFile(TCHAR * filename, const unsigned len) {
	TCHAR installpath[MAX_PATH];
	GetInstallPath(installpath, MAX_PATH);

	_sntprintf(filename, len, TEXT("%s%s"), installpath, "History\\seachword");
	return filename;
}

const TCHAR * GetPageDirectory(TCHAR * pagePath, const unsigned len) {
	TCHAR installPath[MAX_PATH];
	GetInstallPath(installPath, MAX_PATH);

	assert (pagePath != NULL);
	assert ( true == strutility::endwith(installPath, TEXT("\\")));
	GenerateFullPath(pagePath, MAX_PATH, installPath, TEXT("History\\text\\"));

	// ���·���������򴴽�
	if (_taccess(pagePath, 0) == -1) {
		TCHAR parent_dir[MAX_PATH];
		GenerateFullPath(parent_dir, MAX_PATH, installPath, TEXT("History\\"));
		_mkdir(parent_dir);
		_mkdir(pagePath);
	}
	return pagePath;
}

const TCHAR * GetImageDirectory(TCHAR * imagepath, const unsigned len) {
	TCHAR installPath[MAX_PATH];
	GetInstallPath(installPath, MAX_PATH);

	assert (imagepath != NULL);
	assert ( true == strutility::endwith(installPath, "\\"));

	GenerateFullPath(imagepath, MAX_PATH, installPath, TEXT("History\\images\\"));

	// ���·���������򴴽�
	if (_taccess(imagepath, 0) == -1) {
		TCHAR parent_dir[MAX_PATH];
		GenerateFullPath(parent_dir, MAX_PATH, installPath, TEXT("History\\"));
		_mkdir(parent_dir);
		_mkdir(imagepath);
	}
	return imagepath;
}

const TCHAR * GetWebSiteFile(TCHAR *filename, const unsigned len) {
	TCHAR installPath[MAX_PATH];
	GetInstallPath(installPath, MAX_PATH);

	assert (filename != NULL);
	assert ( true == strutility::endwith(installPath, "\\"));
	GenerateFullPath(filename, MAX_PATH, installPath, TEXT("History\\websites\\websites.txt"));
	return filename;
}
const TCHAR * GetPornWebSiteFile(TCHAR *filename, const unsigned len) {
	TCHAR installPath[MAX_PATH];
	GetInstallPath(installPath, MAX_PATH);

	assert (filename != NULL);
	assert ( true == strutility::endwith(installPath, "\\"));
	GenerateFullPath(filename, MAX_PATH, installPath, TEXT("History\\websites\\pornwebsites.txt"));
	return filename;
}

// ��ȡ��¼ͼƬ ������ʷ���ļ���·��
const TCHAR * GetRecordConfigfile(TCHAR *filename, const unsigned len) {
	TCHAR installPath[MAX_PATH];
	GetInstallPath(installPath, MAX_PATH);

	assert (filename != NULL);
	assert (strutility::endwith(installPath, "\\") == true);
	GenerateFullPath(filename, MAX_PATH, installPath, TEXT("History\\config.xml"));
	return filename;
}

// ��ȡ�������Ŀ¼
const TCHAR * GetInstallPath(TCHAR *install_path, const int len) {
	TCHAR moduleName[MAX_PATH];
	DWORD length = GetModuleFileName(NULL, moduleName, MAX_PATH);
	GetFileNameDir(moduleName, install_path, MAX_PATH);
	return install_path;
}

const TCHAR * GetInstallPathFromRegistry(TCHAR * install_path, const DWORD len) {
	HKEY hKey;
	long   ret = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_SOFTWARE_DIR,  0,   KEY_READ,   &hKey);
	if (ERROR_SUCCESS != ret)
		return NULL;

	TCHAR value[MAX_PATH] = {0};
	DWORD length = MAX_PATH;
	DWORD type = REG_SZ;
	LONG result = RegQueryValueEx (hKey, REG_SOFTWARE_INSTALLPATH, NULL, &type, (LPBYTE)value, &length);
	RegCloseKey(hKey);

	if (length > 0) {
		assert (len > length);
		_tcsncpy(install_path, value, len);
		return install_path;
	} else {
		return NULL;
	}
}




void GetFilespathInDir(const TCHAR * dir,  const TCHAR *exp, 
					   std::vector<strutility::_tstring> * files) {
	using namespace std;
	using namespace strutility;

	TCHAR fileexp[MAX_PATH];
	_sntprintf(fileexp, MAX_PATH, TEXT("%s%s"), dir, exp);
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

void DeleteFiles(const TCHAR * dir, const TCHAR * exp) {
	// ��ȡ�����ļ�
	using namespace std;
	using namespace strutility;

	vector<_tstring> vecfilepaths;
	GetFilespathInDir(dir, exp, &vecfilepaths);

	vector<_tstring>::iterator iter = vecfilepaths.begin();
	for (; iter != vecfilepaths.end(); ++iter) {
		DeleteFile(iter->c_str());
	}
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
void GetScreenRecordDir(TCHAR *screendir, const int len) {
	TCHAR moduleDir[MAX_PATH];
	GetInstallPath(moduleDir, len);
	_sntprintf(screendir, MAX_PATH, TEXT("%s%s"), moduleDir,TEXT("Screen\\"));
	if (_tchdir(screendir) == -1)
		_tmkdir(screendir);
}

// ��ȡ������ʷ��
void GetHistoryRecordDir(TCHAR *historyDir, const int len) {
	TCHAR moduleDir[MAX_PATH];
	GetInstallPath(moduleDir, len);
	_sntprintf(historyDir, MAX_PATH, TEXT("%s%s"), moduleDir,TEXT("History\\"));
	if (_tchdir(historyDir) == -1)
		_tmkdir(historyDir);
}

void GetImageRecordDir(TCHAR *imagedir, const int len) {
	TCHAR history_dir[MAX_PATH];
	GetHistoryRecordDir(history_dir, len);
	_sntprintf(imagedir, MAX_PATH, TEXT("%s%s"), history_dir,TEXT("images\\"));
	if (_tchdir(imagedir) == -1)
		_tmkdir(imagedir);
}

void GetTextRecordDir(TCHAR *textdir, const int len) {
	TCHAR history_dir[MAX_PATH];
	GetHistoryRecordDir(history_dir, len);
	_sntprintf(textdir, MAX_PATH, TEXT("%s%s"), history_dir,TEXT("text\\"));
	if (_tchdir(textdir) == -1)
		_tmkdir(textdir);
}


// ��ȡ�Զ����еı���
HKEY GetAutoRunKey() {
	HKEY hKey;
	if( RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_ALL_ACCESS, &hKey )  == ERROR_SUCCESS )  {
		return hKey;
	} else {
		return NULL;
	}
}

};