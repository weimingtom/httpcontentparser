// MainUI.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\MainUIDlg.h"
#include ".\globalvariable.h"
#include ".\mainui.h"
#include ".\services.h"
#include <sysutility.h>
#include <typeconvert.h>
#include <windowtitle.h>
#include <com\comutility.h>


IDNSSetting *g_dnssetting = NULL;
XMLConfiguration g_configuration;	// ������Ϣ
extern bool g_parentModel = false;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace {
	BOOL CALLBACK EnumWndProc(HWND hwnd, LPARAM lParam)
	{
		HANDLE h = GetProp(hwnd, MAIN_WINDOW_PROP_NAME);
		if( h == (HWND)MAIN_WINDOW_PROP_VALUE)
		{
			*(HWND*)lParam = hwnd;
			return false;
		}
		return true;
	}

};

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

	// ��ȡ������Ϣ
	TCHAR config_path[MAX_PATH];
	GetAppConfigFilename(config_path, MAX_PATH, AfxGetInstanceHandle());
	g_configuration.loadConfig(config_path);

	HWND hwnd = NULL;
	EnumWindows(EnumWndProc, (LPARAM)&hwnd);
	if (hwnd != NULL) {
		// �����ǰ������Parent״̬
		if (Services::isParentModel() == true) {
			SendMessage(hwnd, WM_SETFOCUS, 0, 0);
			BOOL b = ::SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOMOVE);
			return FALSE;
		}
		return FALSE;
	}


	if (FALSE == Initialize()) {
		return FALSE;
	}

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
