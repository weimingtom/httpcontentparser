#ifndef _FILTER_SETTING_SYS_UTILITY_H__
#define _FILTER_SETTING_SYS_UTILITY_H__

#include <utility\strutility.h>
#include <ApputilityDLL.H>

// 保存屏幕
APPUTILITYDLL_API DWORD GenScreenSPFile(TCHAR *fullpath, const int len);

APPUTILITYDLL_API DWORD GetScreenRecordPath(TCHAR * fullpath, const int len);

// 清空屏幕缓存
APPUTILITYDLL_API   void ClearScreen();

// 启动眼睛保护程序
APPUTILITYDLL_API   void StartEyecare();

// 锁定计算机
APPUTILITYDLL_API   void LockComputer();

// 获取主界面的HWND
APPUTILITYDLL_API   HWND GetMainUIHWND();

// 获取主界面的路径
APPUTILITYDLL_API   void GetMainUIPath(TCHAR * fullpath, const int len);
// 启动主界面
APPUTILITYDLL_API   void StartMainUI();

// 清空所有
APPUTILITYDLL_API   void ClearHistory();

// 获取安装路径
APPUTILITYDLL_API   const TCHAR * GetInstallPath(TCHAR *install_path, const int len);
APPUTILITYDLL_API   const TCHAR * GetInstallPathFromRegistry(TCHAR * install_path, const DWORD len);
APPUTILITYDLL_API   const TCHAR * GetUninstallUtility(TCHAR * fullpath, const int len);
APPUTILITYDLL_API   const TCHAR * GetFileRecordInstallDate(TCHAR * fullpath, const int len);

// 获取配置文件的路径
APPUTILITYDLL_API   const TCHAR * GetAppConfigFilename(TCHAR *fullpath, const int len);

// 获取指定文件的目录
APPUTILITYDLL_API   const TCHAR* GetFileNameDir(const TCHAR *filename, TCHAR *directory, const unsigned len);
APPUTILITYDLL_API   const TCHAR* GetFileName(const TCHAR *fullname, TCHAR * ename, const unsigned len);

// 获取保存图片的路径
APPUTILITYDLL_API   const TCHAR * GetImageDirectory(TCHAR * filename, const unsigned len);
APPUTILITYDLL_API   const TCHAR * GetLogDirectory(TCHAR * filename, const unsigned len);

// 获取文字内容的保存路径
APPUTILITYDLL_API   const TCHAR * GetPageDirectory(TCHAR * filename, const unsigned len);

// 获取保存搜错词的文件
APPUTILITYDLL_API   const TCHAR * GetSearchWordFile(TCHAR * filename, const unsigned len);

// 获取保存网址的文件
APPUTILITYDLL_API   const TCHAR* GetWebSiteFile(TCHAR * filename, const unsigned len);
APPUTILITYDLL_API   const TCHAR * GetPornWebSiteFile(TCHAR *filename, const unsigned len);

// 获取历史的文件
APPUTILITYDLL_API   const TCHAR * GetRecordConfigfile(TCHAR *filename, const unsigned len);

// 开机自动运行
APPUTILITYDLL_API   INT RegisterAutoRun(const TCHAR * fullpath, BOOL auto_run);

APPUTILITYDLL_API   BOOL isAutoRun();

APPUTILITYDLL_API  void Authorization();

// 获取目录下的文件
APPUTILITYDLL_API   void GetFilespathInDir(const TCHAR * dir, const TCHAR *exp, std::vector<strutility::_tstring> * files);

APPUTILITYDLL_API   void DeleteFiles(const TCHAR * dir, const TCHAR * exp);

#endif  // _FILTER_SETTING_SYS_UTILITY_H__