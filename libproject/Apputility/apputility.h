#ifndef _FILTER_SETTING_SYS_UTILITY_H__
#define _FILTER_SETTING_SYS_UTILITY_H__

#include <utility\strutility.h>

#define CONFIG_FILE_NAME					TEXT("nwist.dll")
#define EYECARE_APP_FILENAME				TEXT("Eyecare.exe")
#define LOCKPC_APP_FILENAME					TEXT("LockPC.exe")

// 保存屏幕
DWORD GenScreenSPFile(TCHAR *fullpath, const int len, HMODULE hModule);

DWORD GetScreenRecordPath(TCHAR * fullpath, const int len, HMODULE hModule);

// 清空屏幕缓存
void ClearScreen(HMODULE hModule);

// 启动眼睛保护程序
void StartEyecare(HMODULE hModule);

// 锁定计算机
void LockComputer(HMODULE hModule);

// 获取主界面的路径
HWND GetMainUIHWND();
void GetMainUIPath(TCHAR * fullpath, const int len, HMODULE hModule);
void GetMainUIPath(TCHAR * fullpath, const int len, const TCHAR * installPath);
// 启动主界面
void StartMainUI(HMODULE hModule);

// 清空所有
void ClearHistory(HMODULE hModule);

// 获取安装路径
const TCHAR * GetInstallPath(TCHAR *install_path, const int len, HMODULE hModule);
const TCHAR * GetInstallPathFromRegistry(TCHAR * install_path, const DWORD len);

// 获取配置文件的路径
const TCHAR * GetAppConfigFilename(TCHAR *fullpath, const int len, HMODULE);

// 获取指定文件的目录
const TCHAR* GetFileNameDir(const TCHAR *filename, TCHAR *directory, const unsigned len);

// 获取保存图片的路径
const TCHAR * GetImageDirectory(TCHAR * filename, const unsigned len, const TCHAR * installPath);

// 获取文字内容的保存路径
const TCHAR * GetPageDirectory(TCHAR * filename, const unsigned len, const TCHAR * installPath);

// 获取保存搜错词的文件
const TCHAR * GetSeachWordFile(TCHAR * filename, const unsigned len);

// 获取保存网址的文件
const TCHAR * GetWebSiteFile(TCHAR *filename, const unsigned len, const TCHAR * installPath);
const TCHAR * GetPornWebSiteFile(TCHAR *filename, const unsigned len, const TCHAR * installPath);

// 获取历史的文件
const TCHAR * GetRecordConfigfile(TCHAR *filename, const unsigned len, const TCHAR * installPath);

// 开机自动运行
INT RegisterAutoRun(const TCHAR * fullpath, BOOL auto_run);

BOOL isAutoRun(HMODULE hModule);

// 当前的Eyecare是否在运行
HWND GetEyecareApp();

// 获取目录下的文件
void GetFilespathInDir(const TCHAR * dir, const TCHAR *exp, std::vector<strutility::_tstring> * files);

void DeleteFiles(const TCHAR * dir, const TCHAR * exp);

#endif  // _FILTER_SETTING_SYS_UTILITY_H__