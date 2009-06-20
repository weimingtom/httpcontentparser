// Repair.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include ".\Repair.h"
#include ".\RepairDlg.h"
#include <apputility.h>
#include <app_constants.h>
#include <AppinstallValidate.h>
#include <softwareStatus.h>
#include <COM\FilterSetting_i.c>
#include <COM\FilterSetting.h>
#include <logger\logger.h>
#include <logger\loggerlevel.h>

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
	init_debug_logger(".\\log\\dEyecare.log");
	init_app_logger(".\\log\\Eyecare.log");
	set_logger_level(LOGGER_LEVEL);

	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	CoInitialize(NULL);

	// ����û���ȥOVERTIME״̬����ֱ���˳���
	// �����û������κ�״̬�����и��޸�
	// ��һ�û��޷������أ�

	LONG app_status = SNOWMAN_STATUS_TRIAL;
	try {
		// ��ȡӦ�ó���״̬
		ISnowmanSetting * pSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&pSetting);
		if (SUCCEEDED(hr)) 
			pSetting->getApplicationStatus(&app_status);
	} catch (...) {
	}

	AppUtility::AppInstallValidate validator(VLAIDATE_NONE, app_status);
	validator.repair(true);

	TCHAR errMsg[MAX_PATH];
	validator.getErrorMessage(errMsg, MAX_PATH);
	if (_tcslen(errMsg) > 0) {
		__LERR__("failed  on repair on reason that "<<errMsg);
		if (NULL == _tcsstr(GetCommandLine(), "silence")) {
			AfxMessageBox(errMsg);
		}
		return FALSE;
	}


	CString strSucc;
	strSucc.LoadString(IDS_REPAIR_SUCCESS);
	if (NULL == _tcsstr(GetCommandLine(), "silence")) {
		AfxMessageBox(strSucc);
	}

	// ����״̬�� ���
	app_status = SNOWMAN_STATUS_TRIAL;
	try {
		// ��ȡӦ�ó���״̬
		ISnowmanSetting * pSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&pSetting);
		if (SUCCEEDED(hr)) {
			pSetting->getApplicationStatus(&app_status);

			// �������Ϊж��״̬�� ������Ϊtrial״̬
			// ��һ��ʩ���ڱ�֤�û��ڰ�װ�����ʱ��
			// ����Ҫ�������ã� �Ϳ��Դﵽ���°�װ��Ŀ��
			// ������һ��Ϊ���뱣֤�û��ܹ���ȷ��ȡ״̬��Ϣ
			// �������û���װ֮�󣬴ӳ���״̬��ע��״̬

			if (app_status == SNOWMAN_STATUS_UNINSTALL) {
				pSetting->setApplicationStatus(SNOWMAN_STATUS_TRIAL);
			}
		}
	} catch (...) {
	}

	__LTRC__("succeeded on repair.");


	return TRUE;
}
