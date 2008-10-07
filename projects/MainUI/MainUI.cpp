// MainUI.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\MainUIDlg.h"
#include ".\globalvariable.h"
#include ".\mainui.h"
#include <sysutility.h>
#include <typeconvert.h>
#include <com\cominit.h>

IDNSSetting *g_dnssetting = NULL;
IAppSetting *g_appSetting = NULL;
XMLConfiguration g_configuration;	// ������Ϣ
extern bool g_parentModel = false;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainUIApp

BEGIN_MESSAGE_MAP(CMainUIApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMainUIApp ����

CMainUIApp::CMainUIApp() {
}


// Ψһ��һ�� CMainUIApp ����

CMainUIApp theApp;


// CMainUIApp ��ʼ��

BOOL CMainUIApp::InitInstance()
{
	CoInitialize(NULL);

	if (FALSE == Initialize()) {
		return FALSE;
	}

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();
	CWinApp::InitInstance();
	AfxEnableControlContainer();

	// ��ȡ������Ϣ
	TCHAR config_path[MAX_PATH];
	GetAppConfigFilename(config_path, MAX_PATH, AfxGetInstanceHandle());
	g_configuration.loadConfig(config_path);

	//============================================
	CMainUIDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK) 	{
	}
	else if (nResponse == IDCANCEL) 	{
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	// ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

int CMainUIApp::ExitInstance()
{
	SafeRelease(g_dnssetting);
	CoUninitialize();
	return CWinApp::ExitInstance();
}

// ��һЩ��ʼ���Ĺ���
BOOL CMainUIApp::Initialize(void)
{
	// ��ʼ����ʾ��Ϣ
	CString str;
	str.LoadString(IDS_APP_SERVER_INIT_FAILED);

	// ��ȡDNS�б�
	HRESULT hr = CoCreateInstance(CLSID_DNSSetting, 
		NULL, CLSCTX_LOCAL_SERVER, IID_IDNSSetting, (LPVOID*)&g_dnssetting);
	if (FAILED(hr)) {
		AfxMessageBox(str);
		return FALSE;
	}

	// ��ȡϵͳ����
	hr = CoCreateInstance(CLSID_AppSetting, 
		NULL, CLSCTX_LOCAL_SERVER, IID_IAppSetting, (LPVOID*)&g_appSetting);
	if (FAILED(hr)) {
		AfxMessageBox(str);
		return FALSE;
	}

	// ��ȡ��ǰ״̬
	VARIANT_BOOL bParent;
	g_appSetting->get_ParentModel(&bParent);
	g_parentModel = convert(bParent);
	return 0;
}
