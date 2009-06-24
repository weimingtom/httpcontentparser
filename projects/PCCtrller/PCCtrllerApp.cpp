#include "stdafx.h"
#include ".\pcctrllerapp.h"
#include ".\bkframe.h"
#include "COMutility.h"
#include <logger\logger.h>
#include <logger\loggerlevel.h>
#include <app_constants.h>
#include <sstream>
#include <DebugOutput.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define COM_LOCKPC_MUTEX			TEXT("5DB981F7-74B5-4803-80D5-CE591FC3BFDC")
#pragma data_seg("Shared") 
int volatile lockpc_initialize =0; 
#pragma data_seg() 
#pragma comment(linker,"/section:Shared,RWS") 

bool exit_directly() {
	HANDLE hMutex = CreateMutex(NULL, FALSE, COM_LOCKPC_MUTEX);
	if (hMutex == NULL) {
		__LFAT__("CreateMutex FAILED with ERRNO : " << GetLastError());
	}

	WaitForSingleObject(hMutex, INFINITE);

	if (lockpc_initialize != 0) {
		CloseHandle(hMutex);
		return true;
	}	else {
		lockpc_initialize++;
		CloseHandle(hMutex);
		return false;
	}
}


// 根据应用程序传入的参数判断
// 此次应该运行LockPC还是Eyecare
// 或者什么都不运行
int PCCtrllerApp::initializeAppModel() {
	if (NULL != _tcsstr(GetCommandLine(), LAUNCH_LOCK_PARAM)) {
		appmodel_ = LOCKPC_MODEL;
	} else if (NULL != _tcsstr(GetCommandLine() ,LAUNCH_EYECARE_PARAM)) {
		appmodel_ = EYECARE_MODEL;
	} else {
		appmodel_ = UNKNOW_MODEL;
	}

	return appmodel_;
}

// CtttApp

BEGIN_MESSAGE_MAP(PCCtrllerApp, CWinApp)
END_MESSAGE_MAP()

PCCtrllerApp theApp;

PCCtrllerApp::PCCtrllerApp(void)
{
}

PCCtrllerApp::~PCCtrllerApp(void)
{
}


BOOL PCCtrllerApp::InitInstance() {
	init_app_logger(".\\log\\PCCtrller.log");
	init_debug_logger(".\\log\\dPCCtrller.log", false, true);
	set_logger_level(LOGGER_LEVEL);

	__LTRC__("InitInstance");
	_DEBUG_STREAM_TRC_("InitInstance");
	// 如果已经有一个启动了
	if (exit_directly()) {
		__LTRC__("exit directly");
		_DEBUG_STREAM_TRC_("exit directly");
		return FALSE;
	}

	if (UNKNOW_MODEL == initializeAppModel()) {
		return FALSE;
	}

	InitCommonControls();

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		//todo AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();

	

	CBkFrame* pFrame = new CBkFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;

	pFrame->Create();
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	
	return TRUE;
}
int PCCtrllerApp::ExitInstance()
{
	__LTRC__("ExitInstance");
	return CWinApp::ExitInstance();
}
