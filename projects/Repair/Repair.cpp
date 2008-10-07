// Repair.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include ".\Repair.h"
#include ".\RepairDlg.h"
#include <sysutility.h>
#include <app_constants.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRepairApp

BEGIN_MESSAGE_MAP(CRepairApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CRepairApp 构造

CRepairApp::CRepairApp()
{
}


// 唯一的一个 CRepairApp 对象

CRepairApp theApp;


// CRepairApp 初始化

BOOL CRepairApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControls()。否则，将无法创建窗口。
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	
	// 注册应用程序
	UINT result = InstallPacketsFilter((HMODULE)AfxGetInstanceHandle());
	if (result == PACKETSFILTERED_FILE_NOT_FOUND) {
		CString str;
		str.LoadString(IDS_FILENOT_FOUNT);
		AfxMessageBox(str, MB_ICONSTOP | MB_OK );
		return FALSE;
	} else if (result != PACKETSFILTERED_INSTALL_SUCC &&
		result != PACKETSFILTERED_ALREADY_INSTALL) {
		CString strFailed;
		strFailed.LoadString(IDS_INSTALL_FAILED);
		AfxMessageBox(strFailed, MB_ICONSTOP | MB_OK);
		return FALSE;
	}

	// 注册过滤程序
	result = RegisterServices((HMODULE)AfxGetInstanceHandle());
	if (result == PACKETSFILTERED_FILE_NOT_FOUND) {
		CString str;
		str.LoadString(IDS_FILENOT_FOUNT);
		AfxMessageBox(str, MB_ICONSTOP | MB_OK);
		return FALSE;
	}

	CString strSucc;
	strSucc.LoadString(IDS_REPAIR_SUCCESS);
	AfxMessageBox(strSucc);
	return FALSE;
}
