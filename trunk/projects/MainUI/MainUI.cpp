// MainUI.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\MainUIDlg.h"
#include ".\Globalvariable.h"
#include ".\Services.h"
#include <apputility.h>
#include <typeconvert.h>
#include <app_constants.h>
#include <com\comutility.h>
#include <AppinstallValidate.h>
#include <softwareStatus.h>
#include ".\share.h"
#include ".\log.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#pragma   comment(linker,"/section:shared,rws")   
#pragma data_seg("shared")
HWND share_hwnd = 0;
#pragma data_seg()

#define MUTEX_NAME TEXT("2A144C85-AF84-4f88-8F7D-6C794A2800EB")
#define WEBSNOW_LOGGER_FILE		".\\log\\websnow.log"
#define WEBSNOW_DEBUG_FILE		".\\log\\dwebsnow.log"

IDNSSetting *g_dnssetting = NULL;
extern bool g_parentModel = false;

// ��ʼ��COM
namespace {
AutoInitInScale g_auto_com_init;
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

BOOL CMainUIApp::InitInstance() {
	{
		LERR_<<"CATCH(...)";
		LERR_<<"CATCH(...)";
		LERR_<<"CATCH(...)";
		CMutex mutext(0, MUTEX_NAME);
		CSingleLock(&mutext, true);
		if (share_hwnd != NULL) {
			ShowWindow(share_hwnd, SW_SHOW);
			SetForegroundWindow(share_hwnd);
			return 0;
		}
	}

	// ��ȡӦ�ó���״̬
	LONG app_status = SNOWMAN_STATUS_TRIAL;
	try {
		ISnowmanSetting * pSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&pSetting);
		if (FAILED(hr)) {
			LERR_<< "Create Snowsetting with HRESULT vlaue "<<hr;
		}
		pSetting->getApplicationStatus(&app_status);
	} catch (...) {
		LERR_<<"CATCH(...)";
	}

	// ��ʼ��LOGGER
	AppUtility::AppInstallValidate validator(VLAIDATE_NONE, app_status);
	validator.repair();


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
		LERR_<<"Create DNSString with HRESULT vlaue "<<hr;
		AfxMessageBox(str);
		return FALSE;
	}

	g_parentModel = Services::isParentModel();
	return TRUE;
}

namespace {
class LoggerInit {
public:
	LoggerInit() {
		using namespace boost::logging;
#ifdef DEBUG
	init_debug_logger(WEBSNOW_DEBUG_FILE, false, true);
	init_app_logger(WEBSNOW_LOGGER_FILE, false, true);
	g_log_level()->set_enabled(level::debug);
#else
	init_app_logger(WEBSNOW_LOGGER_FILE);
	g_log_level()->set_enabled(level::warning);
#endif
	}
};
LoggerInit g_logger_init;
};
