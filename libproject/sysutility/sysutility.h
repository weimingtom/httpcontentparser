#ifndef _FILTER_SETTING_SYS_UTILITY_H__
#define _FILTER_SETTING_SYS_UTILITY_H__


// ������Ļ
void SaveScreen(HMODULE hModule);
// �����Ļ����
void ClearScreen(HMODULE hModule);

// �����۾���������
void StartEyecare(HMODULE hModule);

// �������
void ClearHistory(HMODULE hModule);


// ��ȡָ���ļ���Ŀ¼
char* GetFileNameDir(const TCHAR *filename, TCHAR *directory, const int len);

#endif  // _FILTER_SETTING_SYS_UTILITY_H__