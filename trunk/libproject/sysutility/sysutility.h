#ifndef _FILTER_SETTING_SYS_UTILITY_H__
#define _FILTER_SETTING_SYS_UTILITY_H__


// ������Ļ
DWORD GenScreenSPFile(TCHAR *fullpath, const int len, HMODULE hModule);

// �����Ļ����
void ClearScreen(HMODULE hModule);

// �����۾���������
void StartEyecare(HMODULE hModule);

// �������
void ClearHistory(HMODULE hModule);

// ��ȡָ���ļ���Ŀ¼
const TCHAR* GetFileNameDir(const TCHAR *filename, TCHAR *directory, const unsigned len);

// ��ȡ����ͼƬ��·��
const TCHAR * GetImageDirectory(TCHAR * filename, const unsigned len, const TCHAR * installPath);

// ��ȡ�������ݵı���·��
const TCHAR * GetPageDirectory(TCHAR * filename, const unsigned len, const TCHAR * installPath);

// ��ȡ������ַ���ļ�
const TCHAR * GetWebSiteRecordPath(TCHAR *filename, const unsigned len, const TCHAR * installPath);

// ��ȡ��ʷ���ļ�
const TCHAR * GetRecordConfigfile(TCHAR *filename, const unsigned len, const TCHAR * installPath);
#endif  // _FILTER_SETTING_SYS_UTILITY_H__