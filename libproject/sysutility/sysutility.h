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

// ��ð�װĿ¼
const TCHAR *GetInstallDir(const TCHAR *directory, const unsigned len);

// ��ȡָ���ļ���Ŀ¼
const TCHAR* GetFileNameDir(TCHAR *filename, TCHAR *directory, const unsigned len);

// ��ȡ����ͼƬ��·��
const TCHAR * GetImageDirectory(TCHAR * filename, const unsigned len);

// ��ȡ�������ݵı���·��
const TCHAR * GetPageDirectory(TCHAR * filename, const unsigned len);

// ��ȡ������ַ���ļ�
const TCHAR * GetWebSiteRecordPath(TCHAR *filename, const unsigned len);

// ��ȡ��ʷ���ļ�
const TCHAR * GetRecordConfigfile(TCHAR *filename, const unsigned len);
#endif  // _FILTER_SETTING_SYS_UTILITY_H__