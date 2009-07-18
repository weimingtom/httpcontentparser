#ifndef _FILTER_SETTING_SYS_UTILITY_H__
#define _FILTER_SETTING_SYS_UTILITY_H__

#include <utility\strutility.h>

// ������Ļ
DWORD GenScreenSPFile(TCHAR *fullpath, const int len);

DWORD GetScreenRecordPath(TCHAR * fullpath, const int len);

// �����Ļ����
void ClearScreen();

// �����۾���������
void StartEyecare();

// ���������
void LockComputer();

// ��ȡ�������HWND
HWND GetMainUIHWND();

// ��ȡ�������·��
void GetMainUIPath(TCHAR * fullpath, const int len);
// ����������
void StartMainUI();

// �������
void ClearHistory();

// ��ȡ��װ·��
const TCHAR * GetInstallPath(TCHAR *install_path, const int len);
const TCHAR * GetInstallPathFromRegistry(TCHAR * install_path, const DWORD len);

const TCHAR * GetUninstallUtility(TCHAR * fullpath, const int len);

// ��ȡ�����ļ���·��
const TCHAR * GetAppConfigFilename(TCHAR *fullpath, const int len);

// ��ȡָ���ļ���Ŀ¼
const TCHAR* GetFileNameDir(const TCHAR *filename, TCHAR *directory, const unsigned len);
const TCHAR* GetFileName(const TCHAR *fullname, TCHAR * ename, const unsigned len);

// ��ȡ����ͼƬ��·��
const TCHAR * GetImageDirectory(TCHAR * filename, const unsigned len);
const TCHAR * GetLogDirectory(TCHAR * filename, const unsigned len);

// ��ȡ�������ݵı���·��
const TCHAR * GetPageDirectory(TCHAR * filename, const unsigned len);

// ��ȡ�����Ѵ�ʵ��ļ�
const TCHAR * GetSearchWordFile(TCHAR * filename, const unsigned len);

// ��ȡ������ַ���ļ�
const TCHAR* GetWebSiteFile(TCHAR * filename, const unsigned len);
const TCHAR * GetPornWebSiteFile(TCHAR *filename, const unsigned len);

// ��ȡ��ʷ���ļ�
const TCHAR * GetRecordConfigfile(TCHAR *filename, const unsigned len);

// �����Զ�����
INT RegisterAutoRun(const TCHAR * fullpath, BOOL auto_run);

BOOL isAutoRun();

// ��ȡĿ¼�µ��ļ�
void GetFilespathInDir(const TCHAR * dir, const TCHAR *exp, std::vector<strutility::_tstring> * files);

void DeleteFiles(const TCHAR * dir, const TCHAR * exp);

#endif  // _FILTER_SETTING_SYS_UTILITY_H__