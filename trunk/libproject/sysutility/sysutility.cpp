#include "stdafx.h"
#include "sysutility.h"
#include ".\xinstall.h"
#include <utility\strutility.h>
#include <app_constants.h>
#include <assert.h>
#include <process.h>
#include <stdlib.h> 
#include  <io.h>



#define SCREEN_SAVE_TYPE	TEXT("jpg")
namespace {
	void GetScreenRecordDir(TCHAR *moduleDir, const int len, HMODULE hModule);	//
	void GetImageRecordDir(TCHAR *moduleDir, const int len, HMODULE hModule);	// ����ͼ���Ŀ¼
	void GetTextRecordDir(TCHAR *moduleDir, const int len, HMODULE hModule);
	void GenerateImageFile(TCHAR *file, const int len, HMODULE hModule);	// �Զ������ļ���
	void GetHistoryRecordDir(TCHAR *moduleDir, const int len, HMODULE hModule);
	void GenerateFullPath(TCHAR *fullpath, const int len, const TCHAR * dir, const TCHAR * filename);
	void GetFilespathInDir(const TCHAR * dir, const TCHAR *exp, std::vector<strutility::_tstring> * files);

	void DeleteFiles(const TCHAR * dir, const TCHAR * exp);
	
	HKEY GetAutoRunKey();
};



// �����Ƿ����Զ����е�
BOOL isAutoRun(HMODULE hModule) {
	TCHAR fullpath[MAX_PATH];
	GetModuleFileName(hModule, fullpath, MAX_PATH);

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
// ע�����
// returns : 0 ����ɹ�
//			 -1 �����ļ�������
BOOL isPacketFiltersInstalled(HMODULE hModule) {
	TCHAR install_path[MAX_PATH], fullpath[MAX_PATH];
	GetInstallPath(install_path, MAX_PATH, hModule);

	_sntprintf(fullpath, MAX_PATH, TEXT("%s%s"), install_path, PACKETSGRASPER_DLL_NAME);


	CXInstall	m_Install;
	return m_Install.IsInstalled(fullpath);
}

UINT InstallPacketsFilter(HMODULE hModule) {
	TCHAR install_path[MAX_PATH], fullpath[MAX_PATH];
	GetInstallPath(install_path, MAX_PATH, hModule);

	_sntprintf(fullpath, MAX_PATH, TEXT("%s%s"), install_path, PACKETSGRASPER_DLL_NAME);

	// �ļ�������
	if (_taccess(fullpath, 0) == -1) {
		return PACKETSFILTERED_FILE_NOT_FOUND;
	}

	CXInstall	m_Install;
	return m_Install.InstallProvider(fullpath);
}

UINT RegisterServices(HMODULE hModule) {	
	TCHAR install_path[MAX_PATH], fullpath[MAX_PATH], cmd[MAX_PATH];
	GetInstallPath(install_path, MAX_PATH, hModule);

	_sntprintf(fullpath, MAX_PATH, TEXT("%s%s"), install_path, SERVICE_FILENAME);
	if (_taccess(fullpath, 0) != -1) {
		_sntprintf(cmd, MAX_PATH, "%s /RegServer", fullpath);
		return PACKETSFILTERED_INSTALL_SUCC;
	} else {
		// ����ļ��������򷵻�FALSE
		return PACKETSFILTERED_FILE_NOT_FOUND;
	}
}

UINT UnRegisterServices(HMODULE hModule) {
	TCHAR install_path[MAX_PATH], fullpath[MAX_PATH], cmd[MAX_PATH];
	GetInstallPath(install_path, MAX_PATH, hModule);

	_sntprintf(fullpath, MAX_PATH, TEXT("%s%s"), install_path, SERVICE_FILENAME);
	if (_taccess(fullpath, 0) != -1) {
		_sntprintf(cmd, MAX_PATH, "%s /unregserver", fullpath);
		return PACKETSFILTERED_INSTALL_SUCC;
	} else {
		// ����ļ��������򷵻�FALSE
		return PACKETSFILTERED_FILE_NOT_FOUND;
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
void GetMainUIPath(TCHAR * fullpath, const int len, HMODULE hModule) {
	TCHAR installpath[MAX_PATH];
	GetInstallPath(installpath, len, hModule);
	_sntprintf(fullpath, len, "%s%s", installpath, APPLICATION_MAINUI_NAME);
}

void GetMainUIPath(TCHAR * fullpath, const int len, const TCHAR * installPath) {
	_sntprintf(fullpath, len, "%s%s", installPath, APPLICATION_MAINUI_NAME);
}

void StartMainUI(HMODULE hModule) {
	TCHAR  fullpath[MAX_PATH];
	GetMainUIPath(fullpath, MAX_PATH, hModule);
	WinExec(fullpath, SW_SHOW);
}

void LockComputer(HMODULE hModule) {
	TCHAR install_path[MAX_PATH], fullpath[MAX_PATH];
	GetInstallPath(install_path, MAX_PATH, hModule);

	_sntprintf(fullpath, MAX_PATH, "%s%s", install_path, LOCKPC_APP_FILENAME);
	WinExec(fullpath, SW_MAXIMIZE);
}

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

DWORD GetScreenRecordPath(TCHAR * fullpath, const int len, HMODULE hModule) {
	GetScreenRecordDir(fullpath, MAX_PATH, hModule);
	return (DWORD) strlen (fullpath);
}
DWORD GenScreenSPFile(TCHAR *fullpath, const int len, HMODULE hModule) {
	TCHAR dir[MAX_PATH];
	GetScreenRecordDir(dir, MAX_PATH, hModule);

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
void ClearHistory(HMODULE hModule) {
	TCHAR dir[MAX_PATH] = {0}, filepath[MAX_PATH] = {0};
	GetImageRecordDir(dir, MAX_PATH, hModule);
	DeleteFiles(dir, TEXT("*.*"));

	GetTextRecordDir(dir, MAX_PATH, hModule);
	DeleteFiles(dir, TEXT("*.*"));

	GetInstallPath(dir, MAX_PATH, hModule);
	GetWebSiteFile(filepath, MAX_PATH, dir);
	DeleteFile(filepath);

	GetPornWebSiteFile(filepath, MAX_PATH, dir);
	DeleteFile(filepath);
}

void ClearScreen(HMODULE hModule) {
	TCHAR dir[MAX_PATH];
	GetScreenRecordDir(dir, MAX_PATH, hModule);
	DeleteFiles(dir, TEXT("*.jpg"));
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

const TCHAR * GetWebSiteFile(TCHAR *filename, const unsigned len, const TCHAR * installPath) {
	assert (filename != NULL);
	assert ( true == strutility::endwith(installPath, "\\"));
	GenerateFullPath(filename, MAX_PATH, installPath, TEXT("History\\websites\\websites.txt"));
	return filename;
}
const TCHAR * GetPornWebSiteFile(TCHAR *filename, const unsigned len, const TCHAR * installPath) {
	assert (filename != NULL);
	assert ( true == strutility::endwith(installPath, "\\"));
	GenerateFullPath(filename, MAX_PATH, installPath, TEXT("History\\websites\\pornwebsites.txt"));
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

void GetImageRecordDir(TCHAR *imagedir, const int len, HMODULE hModule) {
	TCHAR history_dir[MAX_PATH];
	GetHistoryRecordDir(history_dir, len, hModule);
	_sntprintf(imagedir, MAX_PATH, TEXT("%s%s"), history_dir,TEXT("images\\"));
	if (_tchdir(imagedir) == -1)
		_tmkdir(imagedir);
}

void GetTextRecordDir(TCHAR *textdir, const int len, HMODULE hModule) {
	TCHAR history_dir[MAX_PATH];
	GetHistoryRecordDir(history_dir, len, hModule);
	_sntprintf(textdir, MAX_PATH, TEXT("%s%s"), history_dir,TEXT("text\\"));
	if (_tchdir(textdir) == -1)
		_tmkdir(textdir);
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