#ifndef _FILTER_SETTING_SYS_UTILITY_H__
#define _FILTER_SETTING_SYS_UTILITY_H__

#include <utility\strutility.h>
#include <ApputilityDLL.H>

// ������Ļ
APPUTILITYDLL_API DWORD GenScreenSPFile(TCHAR *fullpath, const int len);

APPUTILITYDLL_API DWORD GetScreenRecordPath(TCHAR * fullpath, const int len);

// �����Ļ����
APPUTILITYDLL_API   void ClearScreen();

// �����۾���������
APPUTILITYDLL_API   void StartEyecare();

// ���������
APPUTILITYDLL_API   void LockComputer();

// ��ȡ�������HWND
APPUTILITYDLL_API   HWND GetMainUIHWND();

// ��ȡ�������·��
APPUTILITYDLL_API   void GetMainUIPath(TCHAR * fullpath, const int len);
// ����������
APPUTILITYDLL_API   void StartMainUI();

// �������
APPUTILITYDLL_API   void ClearHistory();

// ��ȡ��װ·��
APPUTILITYDLL_API   const TCHAR * GetInstallPath(TCHAR *install_path, const int len);
APPUTILITYDLL_API   const TCHAR * GetInstallPathFromRegistry(TCHAR * install_path, const DWORD len);
APPUTILITYDLL_API   const TCHAR * GetUninstallUtility(TCHAR * fullpath, const int len);
APPUTILITYDLL_API   const TCHAR * GetFileRecordInstallDate(TCHAR * fullpath, const int len);

// ��ȡ�����ļ���·��
APPUTILITYDLL_API   const TCHAR * GetAppConfigFilename(TCHAR *fullpath, const int len);

// ��ȡָ���ļ���Ŀ¼
APPUTILITYDLL_API   const TCHAR* GetFileNameDir(const TCHAR *filename, TCHAR *directory, const unsigned len);
APPUTILITYDLL_API   const TCHAR* GetFileName(const TCHAR *fullname, TCHAR * ename, const unsigned len);

// ��ȡ����ͼƬ��·��
APPUTILITYDLL_API   const TCHAR * GetImageDirectory(TCHAR * filename, const unsigned len);
APPUTILITYDLL_API   const TCHAR * GetLogDirectory(TCHAR * filename, const unsigned len);

// ��ȡ�������ݵı���·��
APPUTILITYDLL_API   const TCHAR * GetPageDirectory(TCHAR * filename, const unsigned len);

// ��ȡ�����Ѵ�ʵ��ļ�
APPUTILITYDLL_API   const TCHAR * GetSearchWordFile(TCHAR * filename, const unsigned len);

// ��ȡ������ַ���ļ�
APPUTILITYDLL_API   const TCHAR* GetWebSiteFile(TCHAR * filename, const unsigned len);
APPUTILITYDLL_API   const TCHAR * GetPornWebSiteFile(TCHAR *filename, const unsigned len);

// ��ȡ��ʷ���ļ�
APPUTILITYDLL_API   const TCHAR * GetRecordConfigfile(TCHAR *filename, const unsigned len);

// �����Զ�����
APPUTILITYDLL_API   INT RegisterAutoRun(const TCHAR * fullpath, BOOL auto_run);

APPUTILITYDLL_API   BOOL isAutoRun();

APPUTILITYDLL_API  void Authorization();

// ��ȡĿ¼�µ��ļ�
APPUTILITYDLL_API   void GetFilespathInDir(const TCHAR * dir, const TCHAR *exp, std::vector<strutility::_tstring> * files);

APPUTILITYDLL_API   void DeleteFiles(const TCHAR * dir, const TCHAR * exp);

#endif  // _FILTER_SETTING_SYS_UTILITY_H__