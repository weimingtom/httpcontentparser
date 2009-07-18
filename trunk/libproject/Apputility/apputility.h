#ifndef _FILTER_SETTING_SYS_UTILITY_H__
#define _FILTER_SETTING_SYS_UTILITY_H__

#include <utility\strutility.h>

// 保存屏幕
DWORD GenScreenSPFile(TCHAR *fullpath, const int len);

DWORD GetScreenRecordPath(TCHAR * fullpath, const int len);

// 清空屏幕缓存
void ClearScreen();

// 启动眼睛保护程序
void StartEyecare();

// 锁定计算机
void LockComputer();

// 获取主界面的HWND
HWND GetMainUIHWND();

// 获取主界面的路径
void GetMainUIPath(TCHAR * fullpath, const int len);
// 启动主界面
void StartMainUI();

// 清空所有
void ClearHistory();

// 获取安装路径
const TCHAR * GetInstallPath(TCHAR *install_path, const int len);
const TCHAR * GetInstallPathFromRegistry(TCHAR * install_path, const DWORD len);

const TCHAR * GetUninstallUtility(TCHAR * fullpath, const int len);

// 获取配置文件的路径
const TCHAR * GetAppConfigFilename(TCHAR *fullpath, const int len);

// 获取指定文件的目录
const TCHAR* GetFileNameDir(const TCHAR *filename, TCHAR *directory, const unsigned len);
const TCHAR* GetFileName(const TCHAR *fullname, TCHAR * ename, const unsigned len);

// 获取保存图片的路径
const TCHAR * GetImageDirectory(TCHAR * filename, const unsigned len);
const TCHAR * GetLogDirectory(TCHAR * filename, const unsigned len);

// 获取文字内容的保存路径
const TCHAR * GetPageDirectory(TCHAR * filename, const unsigned len);

// 获取保存搜错词的文件
const TCHAR * GetSearchWordFile(TCHAR * filename, const unsigned len);

// 获取保存网址的文件
const TCHAR* GetWebSiteFile(TCHAR * filename, const unsigned len);
const TCHAR * GetPornWebSiteFile(TCHAR *filename, const unsigned len);

// 获取历史的文件
const TCHAR * GetRecordConfigfile(TCHAR *filename, const unsigned len);

// 开机自动运行
INT RegisterAutoRun(const TCHAR * fullpath, BOOL auto_run);

BOOL isAutoRun();

// 获取目录下的文件
void GetFilespathInDir(const TCHAR * dir, const TCHAR *exp, std::vector<strutility::_tstring> * files);

void DeleteFiles(const TCHAR * dir, const TCHAR * exp);

#endif  // _FILTER_SETTING_SYS_UTILITY_H__