#include "stdafx.h"
#include ".\apputility.h"
#include ".\xinstall.h"
#include <utility\strutility.h>
#include <app_constants.h>
#include <assert.h>
#include <process.h>
#include <stdlib.h> 
#include  <io.h>
#include <definedmsg.h>

#define EYECARE_APP_FILENAME				TEXT("PCCtrller.exe")
#define LOCKPC_APP_FILENAME					TEXT("PCCtrller.exe")
#define CONFIG_FILE_NAME							TEXT("nwist.dll")

#define SCREEN_SAVE_TYPE	TEXT("jpg")

#define SUBKEY_AUTO_RUN		TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run")
namespace {
	void GetScreenRecordDir(TCHAR *moduleDir, const int len);	//
	void GetImageRecordDir(TCHAR *moduleDir, const int len);	// 保存图像的目录
	void GetTextRecordDir(TCHAR *moduleDir, const int len);
	void GenerateImageFile(TCHAR *file, const int len);	// 自动生成文件名
	void GetHistoryRecordDir(TCHAR *moduleDir, const int len);
	void GenerateFullPath(TCHAR *fullpath, const int len, const TCHAR * dir, const TCHAR * filename);
	
	int GetAutoRunKey(HKEY &hKey);
	int GetSoftwareKey(HKEY &hKey);
	int      EnableAutoRun(const char * path);
	int      DisableAutoRun();

	DWORD OperationAuthorizeEveryOne(LPSTR pstrObjName, SE_OBJECT_TYPE dwObjType, ACCESS_MODE operMode);
	DWORD OperationAuthorizeEveryOne(HANDLE handleObjName, SE_OBJECT_TYPE dwObjType, ACCESS_MODE operMode) ;
	
	BOOL CALLBACK EnumWndProc(HWND hwnd, LPARAM lParam);
};

// 程序是否是自动运行的
APPUTILITYDLL_API   BOOL isAutoRun() {
	int rc = 0;
	TCHAR fullpath[MAX_PATH];
	GetModuleFileName(NULL, fullpath, MAX_PATH);

	// 获取自动运行HKEY
	HKEY hKey;
	rc = GetAutoRunKey(hKey);
	if (rc != ERROR_SUCCESS) {
		goto exit;
	}

	TCHAR value[MAX_PATH] = {0};
	DWORD length = MAX_PATH;
	DWORD type = REG_SZ;
	rc = RegQueryValueEx (hKey, REGISTER_MAINUI_KEY, NULL, &type, (LPBYTE)value, &length);
	
	if (ERROR_SUCCESS != rc) {
		goto exit;
	}

	if (_tcscmp(fullpath, value) != 0) {
		rc = -1;
	}

exit:
	if (NULL != hKey) {
		RegCloseKey(hKey);
	}
	return (rc == 0 ? TRUE : FALSE);
}

// 开机自动运行
APPUTILITYDLL_API    INT RegisterAutoRun(const TCHAR * fullpath, BOOL auto_run) {
	int rc = 0;

	// 生成注册表项
	if ( TRUE == auto_run) {
		rc= EnableAutoRun(fullpath);
	} else {
		rc  = DisableAutoRun();
	}
	return rc;
}

APPUTILITYDLL_API   const TCHAR * GetFileRecordInstallDate(TCHAR * fullpath, const int len) {
	TCHAR windowDir[MAX_PATH];
	GetWindowsDirectory(windowDir, MAX_PATH);
	_sntprintf(fullpath, len, "%s\\%s", windowDir, WINDOWS_FILE_TO_STORE_INSTALLDATE);
	return fullpath;
}


// 启动主程序
APPUTILITYDLL_API   void GetMainUIPath(TCHAR * fullpath, const int len) {
	TCHAR installpath[MAX_PATH];
	GetInstallPath(installpath, len);
	_sntprintf(fullpath, len, "%s%s", installpath, APPLICATION_MAINUI_NAME);
}

APPUTILITYDLL_API   const TCHAR * GetSPIInstallPath(TCHAR * fullpath, const int len) {
	TCHAR installpath[MAX_PATH];
	GetModuleFileName(NULL, installpath, MAX_PATH);
	_sntprintf(fullpath, MAX_PATH, TEXT("%s\\%s"), installpath, PACKETSGRASPER_DLL_NAME);
	return fullpath;
}

// 获取主程序窗口
APPUTILITYDLL_API   HWND GetMainUIHWND() {
	HWND hwnd = NULL;
	EnumWindows(EnumWndProc, (LPARAM)&hwnd);
	return hwnd;
}

APPUTILITYDLL_API   void StartMainUI() {
	TCHAR  fullpath[MAX_PATH];
	GetMainUIPath(fullpath, MAX_PATH);
	WinExec(fullpath, SW_NORMAL);
}

APPUTILITYDLL_API   void LockComputer() {
	TCHAR install_path[MAX_PATH], fullpath[MAX_PATH], cmdLine[MAX_PATH * 2];
	GetInstallPath(install_path, MAX_PATH);
	
	_sntprintf(fullpath, MAX_PATH, "%s%s", install_path, LOCKPC_APP_FILENAME);
	_sntprintf(cmdLine, MAX_PATH *2, "%s %s", fullpath, LAUNCH_LOCK_PARAM);
	WinExec(cmdLine, SW_MAXIMIZE);
}

APPUTILITYDLL_API   void StartEyecare() {
	// 检测应用程序是否打开，交给程序本身自己执行
	TCHAR install_path[MAX_PATH], fullpath[MAX_PATH], cmdLine[MAX_PATH * 2];
	GetInstallPath(install_path, MAX_PATH);

	_sntprintf(fullpath, MAX_PATH, "%s%s", install_path, EYECARE_APP_FILENAME);
	_sntprintf(cmdLine, MAX_PATH *2, "%s %s", fullpath, LAUNCH_EYECARE_PARAM);
	WinExec(cmdLine, SW_MAXIMIZE);
}

APPUTILITYDLL_API   DWORD GetScreenRecordPath(TCHAR * fullpath, const int len) {
	GetScreenRecordDir(fullpath, MAX_PATH);
	return (DWORD) strlen (fullpath);
}
APPUTILITYDLL_API   DWORD GenScreenSPFile(TCHAR *fullpath, const int len) {
	TCHAR dir[MAX_PATH];
	GetScreenRecordDir(dir, MAX_PATH);

	// 获取时间
	SYSTEMTIME time;
	GetLocalTime(&time);
	TCHAR filename[MAX_PATH];
	_sntprintf(filename, MAX_PATH, TEXT("%04d%02d%02d%02d%02d%02d.%s"), 
		time.wYear, time.wMonth, time.wDay, 
		time.wHour, time.wMinute, time.wSecond,
		SCREEN_SAVE_TYPE);

	// 获取到目录
	_sntprintf(fullpath, MAX_PATH, TEXT("%s%s"), dir, filename);
	return (DWORD)_tcslen(fullpath);
}
APPUTILITYDLL_API   void ClearHistory() {
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

APPUTILITYDLL_API   void ClearScreen() {
	TCHAR dir[MAX_PATH];
	GetScreenRecordDir(dir, MAX_PATH);
	DeleteFiles(dir, TEXT("*.jpg"));
}

APPUTILITYDLL_API   const TCHAR * GetAppConfigFilename(TCHAR *fullpath, const int len) {
	TCHAR filename[MAX_PATH], directory[MAX_PATH];
	GetModuleFileName(NULL, filename, MAX_PATH);
	GetFileNameDir(filename, directory, MAX_PATH);
	assert (_tcslen(directory) != 0);
	GenerateFullPath(fullpath, len, directory, CONFIG_FILE_NAME);
	return fullpath;
}

APPUTILITYDLL_API   const TCHAR* GetFileNameDir(const TCHAR *filename, TCHAR *directory, const unsigned len) {
	TCHAR dir[MAX_PATH], driver[MAX_PATH];
	_tsplitpath(filename, driver, dir, NULL, NULL);
	_sntprintf(directory, len, TEXT("%s%s"), driver, dir);
	return directory;
}

APPUTILITYDLL_API   const TCHAR* GetFileName(const TCHAR *fullname, TCHAR * ename, const unsigned len) {
	TCHAR dir[MAX_PATH], driver[MAX_PATH], name[MAX_PATH], ext[MAX_PATH];
	_tsplitpath(fullname, driver, dir, name, ext);
	_sntprintf(ename, len, TEXT("%s%s"), name, ext);
	return ename;
}

APPUTILITYDLL_API   const TCHAR * GetSearchWordFile(TCHAR * filename, const unsigned len) {
	TCHAR installpath[MAX_PATH];
	GetInstallPath(installpath, MAX_PATH);

	_sntprintf(filename, len, TEXT("%s%s"), installpath, "History\\seachword");
	return filename;
}

APPUTILITYDLL_API   const TCHAR * GetLogDirectory(TCHAR * logdir, const unsigned len) {
	TCHAR installPath[MAX_PATH];
	GetInstallPath(installPath, MAX_PATH);

	assert (logdir != NULL);
	assert ( true == strutility::endwith(installPath, TEXT("\\")));
	GenerateFullPath(logdir, MAX_PATH, installPath, TEXT("log"));

	// 如果路径不存在则创建
	if (_taccess(logdir, 0) == -1) {
		_mkdir(logdir);
	}
	return logdir;
}

APPUTILITYDLL_API   const TCHAR * GetPageDirectory(TCHAR * pagePath, const unsigned len) {
	TCHAR installPath[MAX_PATH];
	GetInstallPath(installPath, MAX_PATH);

	assert (pagePath != NULL);
	assert ( true == strutility::endwith(installPath, TEXT("\\")));
	GenerateFullPath(pagePath, MAX_PATH, installPath, TEXT("History\\text\\"));

	// 如果路径不存在则创建
	if (_taccess(pagePath, 0) == -1) {
		TCHAR parent_dir[MAX_PATH];
		GenerateFullPath(parent_dir, MAX_PATH, installPath, TEXT("History\\"));
		_mkdir(parent_dir);
		_mkdir(pagePath);
	}
	return pagePath;
}

APPUTILITYDLL_API   const TCHAR * GetImageDirectory(TCHAR * imagepath, const unsigned len) {
	TCHAR installPath[MAX_PATH];
	GetInstallPath(installPath, MAX_PATH);

	assert (imagepath != NULL);
	assert ( true == strutility::endwith(installPath, "\\"));

	GenerateFullPath(imagepath, MAX_PATH, installPath, TEXT("History\\images\\"));

	// 如果路径不存在则创建
	if (_taccess(imagepath, 0) == -1) {
		TCHAR parent_dir[MAX_PATH];
		GenerateFullPath(parent_dir, MAX_PATH, installPath, TEXT("History\\"));
		_mkdir(parent_dir);
		_mkdir(imagepath);
	}
	return imagepath;
}

APPUTILITYDLL_API   const TCHAR * GetWebSiteFile(TCHAR *filename, const unsigned len) {
	TCHAR installPath[MAX_PATH];
	GetInstallPath(installPath, MAX_PATH);

	assert (filename != NULL);
	assert ( true == strutility::endwith(installPath, "\\"));
	GenerateFullPath(filename, MAX_PATH, installPath, TEXT("History\\websites\\websites.txt"));
	return filename;
}
APPUTILITYDLL_API   const TCHAR * GetPornWebSiteFile(TCHAR *filename, const unsigned len) {
	TCHAR installPath[MAX_PATH];
	GetInstallPath(installPath, MAX_PATH);

	assert (filename != NULL);
	assert ( true == strutility::endwith(installPath, "\\"));
	GenerateFullPath(filename, MAX_PATH, installPath, TEXT("History\\websites\\pornwebsites.txt"));
	return filename;
}

// 获取记录图片 文字历史的文件的路径
APPUTILITYDLL_API   const TCHAR * GetRecordConfigfile(TCHAR *filename, const unsigned len) {
	TCHAR installPath[MAX_PATH];
	GetInstallPath(installPath, MAX_PATH);

	assert (filename != NULL);
	assert (strutility::endwith(installPath, "\\") == true);
	GenerateFullPath(filename, MAX_PATH, installPath, TEXT("History\\config.xml"));
	return filename;
}

// 获取软件所在目录
APPUTILITYDLL_API   const TCHAR * GetInstallPath(TCHAR *install_path, const int len) {
	TCHAR moduleName[MAX_PATH];
	DWORD length = GetModuleFileName(NULL, moduleName, MAX_PATH);
	GetFileNameDir(moduleName, install_path, MAX_PATH);
	return install_path;
}

APPUTILITYDLL_API   const TCHAR * GetInstallPathFromRegistry(TCHAR * install_path, const DWORD len) {
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

APPUTILITYDLL_API   void GetFilespathInDir(const TCHAR * dir,  const TCHAR *exp, 
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

	// 记得将第一个文件添加进去
	do {
		files->push_back(find_data.cFileName);
	} while (FindNextFile(hFind, &find_data));

	FindClose(hFind);
}

APPUTILITYDLL_API   void DeleteFiles(const TCHAR * dir, const TCHAR * exp) {
	// 获取所有文件
	using namespace std;
	using namespace strutility;

	vector<_tstring> vecfilepaths;
	GetFilespathInDir(dir, exp, &vecfilepaths);

	vector<_tstring>::iterator iter = vecfilepaths.begin();
	for (; iter != vecfilepaths.end(); ++iter) {
		DeleteFile(iter->c_str());
	}
}

APPUTILITYDLL_API  void Authorization() {
	// 修改文件的属性
	TCHAR installPath[MAX_PATH];
	TCHAR winfile[MAX_PATH];
	HKEY hAutoRunKey;
	HKEY hSoftwareKey;
	
	GetInstallPath(installPath, MAX_PATH);
	GrantAuthorizeEveryOne(installPath, SE_FILE_OBJECT);

	// 注册表
	if (0 == GetAutoRunKey(hAutoRunKey)) {
		GrantAuthorizeEveryOne((HANDLE)hAutoRunKey, SE_REGISTRY_KEY);
		CloseHandle(hAutoRunKey);
		hAutoRunKey =NULL;
	}

	// 保存软件的注册表项
	if (0 == GetSoftwareKey(hSoftwareKey)) {
		GrantAuthorizeEveryOne((HANDLE)hSoftwareKey, SE_REGISTRY_KEY);
		CloseHandle(hSoftwareKey);
		hSoftwareKey =NULL;
	}

	GetFileRecordInstallDate(winfile, MAX_PATH);
	GrantAuthorizeEveryOne(winfile, SE_FILE_OBJECT);
}

// 设置权限
APPUTILITYDLL_API DWORD GrantAuthorizeEveryOne(LPSTR pstrObjName, SE_OBJECT_TYPE dwObjType) {
	return OperationAuthorizeEveryOne(pstrObjName, dwObjType, SET_ACCESS);
}
APPUTILITYDLL_API DWORD GrantAuthorizeEveryOne(HANDLE handleObjName, SE_OBJECT_TYPE dwObjType) {
	return OperationAuthorizeEveryOne(handleObjName, dwObjType, SET_ACCESS);
}

// 回收权限
APPUTILITYDLL_API DWORD RevokeAuthorizeEveryOne(LPSTR pstrObjName, SE_OBJECT_TYPE dwObjType) {
	return OperationAuthorizeEveryOne(pstrObjName, dwObjType, REVOKE_ACCESS);
}
APPUTILITYDLL_API DWORD RevokeAuthorizeEveryOne(HANDLE handleObjName, SE_OBJECT_TYPE dwObjType) {
	return OperationAuthorizeEveryOne(handleObjName, dwObjType, REVOKE_ACCESS);
}

// 是否拥有权限
APPUTILITYDLL_API DWORD HoldAuthorizeEveryOne(HANDLE handleObjName, SE_OBJECT_TYPE dwObjType) {
	DWORD rc  = 0;
	SECURITY_INFORMATION si =  GROUP_SECURITY_INFORMATION | OWNER_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION;
	PSECURITY_DESCRIPTOR pSE = NULL;
	EXPLICIT_ACCESS ea = {0};
	PSID sidOwner = NULL;
	PSID sidGroup = NULL;
	PACL pDACL = NULL;
	PACL pSACL = NULL;

	rc = GetSecurityInfo(handleObjName, dwObjType, si, &sidOwner, &sidGroup, &pDACL, &pSACL, &pSE);
	if (ERROR_SUCCESS != ERROR_SUCCESS) {
		goto exit;
	}

exit:
	if (pDACL != NULL) {
		LocalFree(pDACL);
	}

	if (pSE != NULL) {
		LocalFree(pSE);
	}

	return rc;
}
APPUTILITYDLL_API DWORD HoldAuthorizeEveryOne(LPSTR pstrObjName, SE_OBJECT_TYPE dwObjType) {
		DWORD rc  = 0;
	SECURITY_INFORMATION si =  GROUP_SECURITY_INFORMATION | OWNER_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION;
	PSECURITY_DESCRIPTOR pSE = NULL;
	EXPLICIT_ACCESS ea = {0};
	PSID sidOwner = NULL;
	PSID sidGroup = NULL;
	PACL pDACL = NULL;
	PACL pSACL = NULL;

	rc = GetNamedSecurityInfo(pstrObjName, dwObjType, si, &sidOwner, &sidGroup, &pDACL, &pSACL, &pSE);
	if (ERROR_SUCCESS != ERROR_SUCCESS) {
		goto exit;
	}

exit:
	if (pDACL != NULL) {
		LocalFree(pDACL);
	}

	if (pSE != NULL) {
		LocalFree(pSE);
	}

	return rc;
}


//////////////////////////////////////////////////
// utility functions

namespace {

void GenerateFullPath(TCHAR *fullpath, const int len, const TCHAR * dir, const TCHAR * filename) {
	assert(strutility::endwith(dir, "\\") == true);
	_sntprintf(fullpath, len, TEXT("%s%s"), dir, filename);
}

// 保存屏幕截图的目录
void GetScreenRecordDir(TCHAR *screendir, const int len) {
	TCHAR moduleDir[MAX_PATH];
	GetInstallPath(moduleDir, len);
	_sntprintf(screendir, MAX_PATH, TEXT("%s%s"), moduleDir,TEXT("Screen\\"));
	if (_tchdir(screendir) == -1)
		_tmkdir(screendir);
}

// 获取保存历史的
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


int GetSoftwareKey(HKEY &hKey)  {
	int rc  = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_SOFTWARE_DIR, 0, KEY_ALL_ACCESS, &hKey );
	return rc;
}
// 获取自动运行的表项
int GetAutoRunKey(HKEY &hKey) {
	int rc  = RegOpenKeyEx(HKEY_LOCAL_MACHINE, SUBKEY_AUTO_RUN, 0, KEY_ALL_ACCESS, &hKey );
	return rc;
}


int EnableAutoRun(const char * path) {
	LONG rc = 0;
	HKEY  hKey;
	rc = GetAutoRunKey(hKey);
	if (rc) {
		goto exit;
	}

	rc = RegSetValueEx( hKey,REGISTER_MAINUI_KEY , 0, REG_SZ, (const BYTE*)(LPCSTR)path, (DWORD)_tcslen(path));
	if (ERROR_SUCCESS != rc) {
		goto exit;
	}

exit:
	if (NULL != hKey) {
		RegCloseKey(hKey);
	}

	return rc;
}
int    DisableAutoRun() {
 	HKEY hKey;
	int rc = GetAutoRunKey(hKey);
	if (ERROR_SUCCESS != rc) {
		rc = 1;
		goto exit;
	}

	rc = RegDeleteValue(hKey, REGISTER_MAINUI_KEY);
	if (ERROR_SUCCESS != rc) {
		rc = 2;
		goto exit;
	}

exit:
	if (NULL != hKey) {
		RegCloseKey(hKey);
		hKey = NULL;
	}
	return rc;
}

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

const DWORD ALL_FILE_RIGHT = STANDARD_RIGHTS_ALL | SPECIFIC_RIGHTS_ALL |GENERIC_ALL;
DWORD OperationAuthorizeEveryOne(HANDLE handleObjName, SE_OBJECT_TYPE dwObjType, ACCESS_MODE operMode)  {
	DWORD rc  = 0;
	SECURITY_INFORMATION si =  GROUP_SECURITY_INFORMATION | OWNER_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION;
	PSECURITY_DESCRIPTOR pSE = NULL;
	EXPLICIT_ACCESS ea = {0};
	PSID sidOwner = NULL;
	PSID sidGroup = NULL;
	PACL pOldDACL = NULL;
	PACL pNewDACL = NULL;
	PACL pSACL = NULL;

	rc = GetSecurityInfo(handleObjName, dwObjType, si, &sidOwner, &sidGroup, &pOldDACL, &pSACL, &pSE);
	if (ERROR_SUCCESS != ERROR_SUCCESS) {
		goto exit;
	}

	si = DACL_SECURITY_INFORMATION;
	BuildExplicitAccessWithName(&ea, TEXT("EveryOne"), ALL_FILE_RIGHT, operMode , CONTAINER_INHERIT_ACE);

	rc = SetEntriesInAcl(1, &ea, pOldDACL, &pNewDACL);
	if (ERROR_SUCCESS != ERROR_SUCCESS) {
		goto exit;
	}

	rc = SetSecurityInfo(handleObjName, dwObjType, si, NULL, NULL, pNewDACL, NULL);
	if (ERROR_SUCCESS != ERROR_SUCCESS) {
		goto exit;
	}

exit:
	if (pOldDACL != NULL) {
		LocalFree(pOldDACL);
	}

	if (pNewDACL != NULL) {
		LocalFree(pNewDACL);
	}

	if (pSE != NULL) {
		LocalFree(pSE);
	}

	return rc;
}

DWORD OperationAuthorizeEveryOne(LPSTR pstrObjName, SE_OBJECT_TYPE dwObjType, ACCESS_MODE operMode) {
	DWORD rc  = 0;
	SECURITY_INFORMATION si =  GROUP_SECURITY_INFORMATION | OWNER_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION;
	PSECURITY_DESCRIPTOR pSE = NULL;
	EXPLICIT_ACCESS ea = {0};
	PSID sidOwner = NULL;
	PSID sidGroup = NULL;
	PACL pOldDACL = NULL;
	PACL pNewDACL = NULL;
	PACL pSACL = NULL;

	rc = GetNamedSecurityInfo(pstrObjName, dwObjType, si, &sidOwner, &sidGroup, &pOldDACL, &pSACL, &pSE);
	if (ERROR_SUCCESS != ERROR_SUCCESS) {
		goto exit;
	}

	si = DACL_SECURITY_INFORMATION;
	BuildExplicitAccessWithName(&ea, TEXT("EveryOne"), ALL_FILE_RIGHT , operMode , CONTAINER_INHERIT_ACE);

	rc = SetEntriesInAcl(1, &ea, pOldDACL, &pNewDACL);
	if (ERROR_SUCCESS != ERROR_SUCCESS) {
		goto exit;
	}

	rc = SetNamedSecurityInfo(pstrObjName, dwObjType, si, NULL, NULL, pNewDACL, NULL);
	if (ERROR_SUCCESS != ERROR_SUCCESS) {
		goto exit;
	}

exit:
	if (pOldDACL != NULL) {
		LocalFree(pOldDACL);
	}

	if (pNewDACL != NULL) {
		LocalFree(pNewDACL);
	}

	if (pSE != NULL) {
		LocalFree(pSE);
	}

	return rc;
}
};