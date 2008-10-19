#ifndef _FILTER_SETTING_SYS_UTILITY_H__
#define _FILTER_SETTING_SYS_UTILITY_H__


#define CONFIG_FILE_NAME					TEXT("config.xml")
#define EYECARE_APP_FILENAME				TEXT("Eyecare.exe")

// 保存屏幕
DWORD GenScreenSPFile(TCHAR *fullpath, const int len, HMODULE hModule);

DWORD GetScreenRecordPath(TCHAR * fullpath, const int len, HMODULE hModule);

// 清空屏幕缓存
void ClearScreen(HMODULE hModule);

// 启动眼睛保护程序
void StartEyecare(HMODULE hModule);

// 获取主界面的路径
void GetMainUIPath(TCHAR * fullpath, const int len, HMODULE hModule);
void GetMainUIPath(TCHAR * fullpath, const int len, const TCHAR * installPath);
// 启动主界面
void StartMainUI(HMODULE hModule);

// 清空所有
void ClearHistory(HMODULE hModule);

// 获取安装路径
const TCHAR * GetInstallPath(TCHAR *install_path, const int len, HMODULE hModule);

// 获取配置文件的路径
const TCHAR * GetAppConfigFilename(TCHAR *fullpath, const int len, HMODULE);

// 获取指定文件的目录
const TCHAR* GetFileNameDir(const TCHAR *filename, TCHAR *directory, const unsigned len);

// 获取保存图片的路径
const TCHAR * GetImageDirectory(TCHAR * filename, const unsigned len, const TCHAR * installPath);

// 获取文字内容的保存路径
const TCHAR * GetPageDirectory(TCHAR * filename, const unsigned len, const TCHAR * installPath);

// 获取保存网址的文件
const TCHAR * GetWebSiteRecordPath(TCHAR *filename, const unsigned len, const TCHAR * installPath);

// 获取历史的文件
const TCHAR * GetRecordConfigfile(TCHAR *filename, const unsigned len, const TCHAR * installPath);

// 开机自动运行
INT RegisterAutoRun(const TCHAR * fullpath, BOOL auto_run);

BOOL isAutoRun(HMODULE hModule);

// 过滤包是否已经安装
BOOL isPacketFiltersInstalled(HMODULE hModule);
UINT InstallPacketsFilter(HMODULE hModule);

UINT RegisterServices(HMODULE hModule);
// 当前的Eyecare是否在运行
HWND GetEyecareApp();
#endif  // _FILTER_SETTING_SYS_UTILITY_H__