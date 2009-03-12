// MainUI.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\MainUIDlg.h"
#include ".\globalvariable.h"
#include ".\mainui.h"
#include ".\services.h"
#include <apputility.h>
#include <typeconvert.h>
#include <app_constants.h>
#include <com\comutility.h>
#include <AppinstallValidate.h>


IDNSSetting *g_dnssetting = NULL;
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

void initializeSetting() {
		// ��ʼ������
	TCHAR config_path[MAX_PATH];
	GetAppConfigFilename(config_path, MAX_PATH);
	g_configuration.loadConfig(config_path);
}

BOOL CMainUIApp::InitInstance()
{
	CoInitialize(NULL);
	
	// TODO enable the following code
	// AppInstallValidate validator(VLAIDATE_NONE);
	// validator.repair((HMODULE)AfxGetInstanceHandle());

	// ��ȡ������Ϣ
	initializeSetting();

	HWND hwnd = GetMainUIHWND();
	if (hwnd != NULL) {
		::SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOMOVE);
		return FALSE;
	}


	if (FALSE == Initialize()) {
		return FALSE;
	}

	m_GdiplusToken = NULL;
	GdiplusStartupInput gdiplusStartupInput;
	Status status = GdiplusStartup( &m_GdiplusToken, &gdiplusStartupInput, NULL);

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();
	CWinApp::InitInstance();
	AfxEnableControlContainer();

	//============================================
	CMainUIDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK) 	{
	}
	else if (nResponse == IDCANCEL) {
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	// ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

int CMainUIApp::ExitInstance()
{
	GdiplusShutdown( m_GdiplusToken);
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

	g_parentModel = Services::isParentModel();
	return TRUE;
}
