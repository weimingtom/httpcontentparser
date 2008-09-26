#ifndef _FILTER_SETTING_SYS_UTILITY_H__
#define _FILTER_SETTING_SYS_UTILITY_H__


// 保存屏幕
DWORD GenScreenSPFile(TCHAR *fullpath, const int len, HMODULE hModule);

// 清空屏幕缓存
void ClearScreen(HMODULE hModule);

// 启动眼睛保护程序
void StartEyecare(HMODULE hModule);

// 清空所有
void ClearHistory(HMODULE hModule);

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
#endif  // _FILTER_SETTING_SYS_UTILITY_H__