// Repair.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include ".\Repair.h"
#include ".\RepairDlg.h"
#include <sysutility.h>
#include <app_constants.h>
#include <AppinstallValidate.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRepairApp

BEGIN_MESSAGE_MAP(CRepairApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CRepairApp ����

CRepairApp::CRepairApp()
{
}


// Ψһ��һ�� CRepairApp ����

CRepairApp theApp;


// CRepairApp ��ʼ��

BOOL CRepairApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	
	AppInstallValidate validator(VLAIDATE_NONE);
	validator.repair((HMODULE)AfxGetInstanceHandle());

	TCHAR errMsg[MAX_PATH];
	validator.getErrorMessage(errMsg, MAX_PATH);
	if (_tcslen(errMsg) > 0) {
		AfxMessageBox(errMsg);
		return FALSE;
	}

	CString strSucc;
	strSucc.LoadString(IDS_REPAIR_SUCCESS);
	AfxMessageBox(strSucc);
	return FALSE;
}
