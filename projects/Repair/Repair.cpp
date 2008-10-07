// Repair.cpp : ����Ӧ�ó��������Ϊ��
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

	
	// ע��Ӧ�ó���
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

	// ע����˳���
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
