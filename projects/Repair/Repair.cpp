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


#define INSTALLER_PARAMETER		TEXT("installer")
#define UNINSTALL_PARAMETER	TEXT("uninstaller")
#define SILENCE_PARAMETER	TEXT("silence")


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
LONG setAppStatusForUninstaller() {
	// ����״̬�� ���
	LONG app_status = SNOWMAN_STATUS_TRIAL;
	try {
		// ��ȡӦ�ó���״̬
		ISnowmanSetting * pSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&pSetting);
		if (SUCCEEDED(hr)) {
			hr = pSetting->getApplicationStatus(&app_status);
			if (FAILED(hr)) {
				__LERR__("failed  on get state with HRESULT "<<hr);
			}
			pSetting->setApplicationStatus(SNOWMAN_STATUS_UNINSTALL);
		} else {
			__LERR__("failed  on create snowman with HRESULT "<<hr);
		}
	} catch (...) {
	}

	return app_status;
}
LONG setAppStatusForInstaller() {
	// ����״̬�� ���
	LONG app_status = SNOWMAN_STATUS_TRIAL;
	try {
		// ��ȡӦ�ó���״̬
		ISnowmanSetting * pSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&pSetting);
		if (SUCCEEDED(hr)) {
			hr = pSetting->getApplicationStatus(&app_status);
			if (FAILED(hr)) {
				__LERR__("failed  on get state with HRESULT "<<hr);
			}

			// �������Ϊж��״̬�� ������Ϊtrial״̬
			// ��һ��ʩ���ڱ�֤�û��ڰ�װ�����ʱ��
			// ����Ҫ�������ã� �Ϳ��Դﵽ���°�װ��Ŀ��
			// ������һ��Ϊ���뱣֤�û��ܹ���ȷ��ȡ״̬��Ϣ
			// �������û���װ֮�󣬴ӳ���״̬��ע��״̬

			if (app_status == SNOWMAN_STATUS_UNINSTALL) {
				pSetting->setApplicationStatus(SNOWMAN_STATUS_TRIAL);
			}
		} else {
			__LERR__("failed  on create snowman with HRESULT "<<hr);
		}
	} catch (...) {
	}

	return app_status;
}

LONG getAppStatus() {
	LONG status = SNOWMAN_STATUS_TRIAL;
	try {
		// ��ȡӦ�ó���״̬
		ISnowmanSetting * pSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&pSetting);
		if (SUCCEEDED(hr)) {
			pSetting->getApplicationStatus(&status);
		} else {
			__LERR__("failed  on create snowman with HRESULT "<<hr);
		}
	} catch (...) {
	}

	return status;
}

void Uninstall() {
	// ����ж��״̬
	LONG app_status = getAppStatus();	//SNOWMAN_STATUS_TRIAL;

	setAppStatusForUninstaller();	// ����״̬Ϊж��

	AppUtility::AppInstallValidate validator(VLAIDATE_NONE, app_status);
	validator.uninstall();
}

void Install() {
	// ����Ӧ�ó���״̬
	// ȷ���䲻�ᱻж��
	setAppStatusForInstaller();

	LONG app_status = getAppStatus();	//SNOWMAN_STATUS_TRIAL;
	AppUtility::AppInstallValidate validator(VLAIDATE_NONE, app_status);
	validator.repair(true);

	TCHAR errMsg[MAX_PATH];
	validator.getErrorMessage(errMsg, MAX_PATH);
	if (_tcslen(errMsg) > 0) {
		__LERR__("failed  on repair on reason that "<<errMsg);
		if (NULL == _tcsstr(GetCommandLine(), SILENCE_PARAMETER)) {
			AfxMessageBox(errMsg);
		}
		return;
	}


	CString strSucc;
	strSucc.LoadString(IDS_REPAIR_SUCCESS);
	if (NULL == _tcsstr(GetCommandLine(), SILENCE_PARAMETER)) {
		AfxMessageBox(strSucc);
	}

	__LTRC__("succeeded on repair.");
}

BOOL CRepairApp::InitInstance()
{
	init_debug_logger(".\\log\\dEyecare.log");
	init_app_logger(".\\log\\Eyecare.log");
	set_logger_level(LOGGER_LEVEL);

	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	CoInitialize(NULL);

	// �����Installer���ã� ���������Ƿ���ж��״̬
	// �������Ϊ����״̬
	if (NULL != _tcsstr(GetCommandLine(), INSTALLER_PARAMETER)) {
		__LTRC__("installer call repair");
		Install();
	} else if (NULL != _tcsstr(GetCommandLine(), UNINSTALL_PARAMETER)) {
		__LTRC__("uninstaller call repair");
		Uninstall();
	} else {
		__LTRC__("user double click");
		Install();
	}

	return TRUE;
}
