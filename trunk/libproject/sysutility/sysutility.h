#ifndef _FILTER_SETTING_SYS_UTILITY_H__
#define _FILTER_SETTING_SYS_UTILITY_H__


#define CONFIG_FILE_NAME					TEXT("config.xml")
#define EYECARE_APP_FILENAME				TEXT("Eyecare.exe")

// ������Ļ
DWORD GenScreenSPFile(TCHAR *fullpath, const int len, HMODULE hModule);

// �����Ļ����
void ClearScreen(HMODULE hModule);

// �����۾���������
void StartEyecare(HMODULE hModule);

// �������
void ClearHistory(HMODULE hModule);

// ��ȡ��װ·��
const TCHAR * GetInstallPath(TCHAR *install_path, const int len, HMODULE hModule);

// ��ȡ�����ļ���·��
const TCHAR * GetAppConfigFilename(TCHAR *fullpath, const int len, HMODULE);

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

BOOL isPacketFiltersInstalled(HMODULE hModule);
UINT InstallPacketsFilter(HMODULE hModule);

UINT RegisterServices(HMODULE hModule);
// ��ǰ��Eyecare�Ƿ�������
HWND GetEyecareApp();
#endif  // _FILTER_SETTING_SYS_UTILITY_H__