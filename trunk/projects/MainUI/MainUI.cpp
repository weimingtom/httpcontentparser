// MainUI.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\MainUIDlg.h"
#include ".\Globalvariable.h"
#include ".\Services.h"
#include <apputility\apputility.h>
#include <typeconvert.h>
#include <app_constants.h>
#include <com\comutility.h>
#include <apputility\AppinstallValidate.h>
#include <softwareStatus.h>
#include ".\share.h"
#include <logger\logger.h>
#include <logger\loggerlevel.h>
#include ".\firstpwddlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#pragma   comment(linker,"/section:shared,rws")   
#pragma data_seg("shared")
HWND share_hwnd = 0;
int mainui_app_count = 0;
#pragma data_seg()

#define MUTEX_NAME TEXT("2A144C85-AF84-4f88-8F7D-6C794A2800EB")
#define LOGGER_FILE		".\\log\\Family007.log"
#define DEBUG_LOGGER_FILE		".\\log\\dFamily007.log"

IDNSSetting *g_dnssetting = NULL;
extern bool g_parentModel = false;

// ��ʼ��COM
namespace {
AutoInitInScale g_auto_com_init;

void initlogger() {
	using namespace boost::logging;
	init_debug_logger(DEBUG_LOGGER_FILE);
	init_app_logger(LOGGER_FILE);
	set_logger_level(LOGGER_LEVEL);
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

bool exit_directly() {
	HANDLE hMutex = CreateMutex(NULL, FALSE, MUTEX_NAME);
	if (hMutex == NULL) {
		__LFAT__("CreateMutex FAILED with ERRNO : " << GetLastError());
	}

	WaitForSingleObject(hMutex, INFINITE);

	bool result = false;
	if (mainui_app_count != 0) {
		result =  true;
	}	else {
		mainui_app_count++;
		result =  false;
	}

	ReleaseMutex(hMutex);
	CloseHandle(hMutex);
	return result;
}

BOOL CMainUIApp::InitInstance() {
	if (exit_directly() == true) {
		// ���share_hwnd�Ѿ���ʼ��
		if (share_hwnd != NULL) {
			ShowWindow(share_hwnd, SW_SHOW);
			SetForegroundWindow(share_hwnd);
		}
		__LTRC__("Exit directly");
		return FALSE;
	}

	// ��ȡӦ�ó���״̬
	LONG app_status = SNOWMAN_STATUS_TRIAL;
	try {
		ISnowmanSetting * pSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&pSetting);
		if (FAILED(hr)) {
			__LERR__( "Create Snowsetting with HRESULT vlaue "<<std::hex<<hr);
		}
		pSetting->getApplicationStatus(&app_status);
	} catch (...) {
		__LERR__("CATCH(...)");
	}

	// ��ʼ��LOGGER
	AppUtility::AppInstallValidate validator(VLAIDATE_NONE, app_status);
	validator.repair();

	if (Services::firstOpen()) {
		CFirstPwdDlg dlg;
		dlg.DoModal();
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
		__LERR__("Create DNSString with HRESULT vlaue "<<std::hex<<hr);
		AfxMessageBox(str);
		return FALSE;
	}

	g_parentModel = Services::isParentModel();
	return TRUE;
}
