#ifndef _FILTER_SETTING_SYS_UTILITY_H__
#define _FILTER_SETTING_SYS_UTILITY_H__

#include <utility\strutility.h>

#define CONFIG_FILE_NAME					TEXT("nwist.dll")
#define EYECARE_APP_FILENAME				TEXT("Eyecare.exe")
#define LOCKPC_APP_FILENAME					TEXT("LockPC.exe")

// ������Ļ
DWORD GenScreenSPFile(TCHAR *fullpath, const int len, HMODULE hModule);

DWORD GetScreenRecordPath(TCHAR * fullpath, const int len, HMODULE hModule);

// �����Ļ����
void ClearScreen(HMODULE hModule);

// �����۾���������
void StartEyecare(HMODULE hModule);

// ���������
void LockComputer(HMODULE hModule);

// ��ȡ�������·��
HWND GetMainUIHWND();
void GetMainUIPath(TCHAR * fullpath, const int len, HMODULE hModule);
void GetMainUIPath(TCHAR * fullpath, const int len, const TCHAR * installPath);
// ����������
void StartMainUI(HMODULE hModule);

// �������
void ClearHistory(HMODULE hModule);

// ��ȡ��װ·��
const TCHAR * GetInstallPath(TCHAR *install_path, const int len, HMODULE hModule);
const TCHAR * GetInstallPathFromRegistry(TCHAR * install_path, const DWORD len);

// ��ȡ�����ļ���·��
const TCHAR * GetAppConfigFilename(TCHAR *fullpath, const int len, HMODULE);

// ��ȡָ���ļ���Ŀ¼
const TCHAR* GetFileNameDir(const TCHAR *filename, TCHAR *directory, const unsigned len);

// ��ȡ����ͼƬ��·��
const TCHAR * GetImageDirectory(TCHAR * filename, const unsigned len, const TCHAR * installPath);

// ��ȡ�������ݵı���·��
const TCHAR * GetPageDirectory(TCHAR * filename, const unsigned len, const TCHAR * installPath);

// ��ȡ�����Ѵ�ʵ��ļ�
const TCHAR * GetSeachWordFile(TCHAR * filename, const unsigned len);

// ��ȡ������ַ���ļ�
const TCHAR * GetWebSiteFile(TCHAR *filename, const unsigned len, const TCHAR * installPath);
const TCHAR * GetPornWebSiteFile(TCHAR *filename, const unsigned len, const TCHAR * installPath);

// ��ȡ��ʷ���ļ�
const TCHAR * GetRecordConfigfile(TCHAR *filename, const unsigned len, const TCHAR * installPath);

// �����Զ�����
INT RegisterAutoRun(const TCHAR * fullpath, BOOL auto_run);

BOOL isAutoRun(HMODULE hModule);

// ��ǰ��Eyecare�Ƿ�������
HWND GetEyecareApp();

// ��ȡĿ¼�µ��ļ�
void GetFilespathInDir(const TCHAR * dir, const TCHAR *exp, std::vector<strutility::_tstring> * files);

void DeleteFiles(const TCHAR * dir, const TCHAR * exp);

#endif  // _FILTER_SETTING_SYS_UTILITY_H__