#ifndef _FILTER_SETTING_SYS_UTILITY_H__
#define _FILTER_SETTING_SYS_UTILITY_H__

void RegisterServiceProcess();

// 保存屏幕
void SaveScreen(HMODULE hModule);
// 清空屏幕缓存
void ClearScreen(HMODULE hModule);

// 启动眼睛保护程序
void StartEyecare(HMODULE hModule);

// 清空所有
void ClearHistory(HMODULE hModule);

#endif  // _FILTER_SETTING_SYS_UTILITY_H__