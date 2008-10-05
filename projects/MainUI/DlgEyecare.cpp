// DlgEyecare.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgEyecare.h"
#include ".\dlgeyecare.h"
#include ".\globalvariable.h"
#include <comdef.h>

// CDlgEyecare 对话框

IMPLEMENT_DYNAMIC(CDlgEyecare, CDialog)
CDlgEyecare::CDlgEyecare(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgEyecare::IDD, pParent)
	, m_strRetryPwd(_T(""))
	, m_strPassword(_T(""))
	, m_nEnterTime(0)
	, m_nEyecareTime(0)
	, m_bUseSUPWD(FALSE)
{
}

CDlgEyecare::~CDlgEyecare()
{
}

void CDlgEyecare::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STA_EYECARE_TIME, m_staEyecare);
	DDX_Control(pDX, IDC_STA_PASSWORD, m_staPwd);
	DDX_Control(pDX, IDC_CHK_USE_SUPWD, m_chkUseSuPwd);
	DDX_Control(pDX, IDC_BTN_RESET, m_btnResetPwd);
	DDX_Control(pDX, IDC_BTN_SETPWD, m_btnSetPwd);
	DDX_Control(pDX, IDC_EDIT_PWD, m_edtPwd);
	DDX_Control(pDX, IDC_EDT_PWD_RETRY, m_edtRetry);
	DDX_Control(pDX, IDC_EDT_ENTERTIME, m_edtEnterTime);
	DDX_Control(pDX, IDC_EDT_RESTTIME, m_edtRestTime);


	//==============================================
	DDX_Text(pDX, IDC_EDT_PWD_RETRY, m_strRetryPwd);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPassword);
	DDX_Text(pDX, IDC_EDT_ENTERTIME, m_nEnterTime);
	DDX_Text(pDX, IDC_EDT_RESTTIME, m_nEyecareTime);
	DDX_Check(pDX, IDC_CHK_USE_SUPWD, m_bUseSUPWD);
}


void CDlgEyecare::OnRestore() {

}

// 设置时间间隔
void CDlgEyecare::setEyecareTimespan() {
	try {
		UpdateData(TRUE);
		IEyecare *pEyeCare = NULL;
		CoCreateInstance(CLSID_Eyecare, NULL, CLSCTX_LOCAL_SERVER, IID_IEyecare, (LPVOID*)&pEyeCare);
		pEyeCare->setEnterTime(m_nEnterTime * 60);
		pEyeCare->setEyecareTime(m_nEyecareTime * 60);
		pEyeCare->Release();
	} catch (_com_error&) {
		// AfxMessageBox("");
	}
}

// 设置输入密码结束锁定后的模式
void CDlgEyecare::setEyecareTerminatedMode() {
	try {
		UpdateData(TRUE);
		IEyecare *pEyeCare = NULL;
		CoCreateInstance(CLSID_Eyecare, NULL, CLSCTX_LOCAL_SERVER, IID_IEyecare, (LPVOID*)&pEyeCare);
		UINT checked = GetCheckedRadioButton(IDC_RAD_ENTER_SU_MODE, IDC_RAD_JUST_RESET_TIMER);
		const int mode = (checked ==  IDC_RAD_ENTER_SU_MODE) ? 
			EyecareSetting::EYECARE_TERMIN_ENTERSU : EyecareSetting::EYECARE_TERMIN_RESETTIMER;

		pEyeCare->setTermMode(mode);
		pEyeCare->Release();
	} catch(_com_error&) {
	}
}

void CDlgEyecare::OnApply() {
	setEyecareTimespan();
	setEyecareTerminatedMode();
}

void CDlgEyecare::OnShow() {
}

void CDlgEyecare::initializeSetting() {
	SetPwdEditState();

	// 读出出示信息
	m_nEnterTime = g_configuration.getEyecareSetting()->getEnterTime() / 60;
	m_nEyecareTime = g_configuration.getEyecareSetting()->getEyecareTime() / 60;

	const int mode = g_configuration.getEyecareSetting()->getTerminatedMode();
	assert(mode == EyecareSetting::EYECARE_TERMIN_ENTERSU || mode == EyecareSetting::EYECARE_TERMIN_RESETTIMER);
	
	UINT checked = (mode == EyecareSetting::EYECARE_TERMIN_RESETTIMER) ? IDC_RAD_JUST_RESET_TIMER : IDC_RAD_ENTER_SU_MODE;
	CheckRadioButton(IDC_RAD_ENTER_SU_MODE, IDC_RAD_JUST_RESET_TIMER, checked);
	
	UpdateData(FALSE);
}

BEGIN_MESSAGE_MAP(CDlgEyecare, CDialog)
	ON_BN_CLICKED(IDC_CHK_USE_SUPWD, OnBnClickedChkUseSupwd)
	ON_BN_CLICKED(IDC_BTN_RESET, OnBnClickedBtnReset)
END_MESSAGE_MAP()


// CDlgEyecare 消息处理程序
BOOL CDlgEyecare::OnInitDialog()
{
	CBaseDlg::OnInitDialog();
	initializeSetting();
	return TRUE;
}



void CDlgEyecare::OnBnClickedChkUseSupwd() {
	UpdateData(TRUE);
	SetPwdEditState();
}

void CDlgEyecare::SetPwdEditState() {
	if (TRUE == m_bUseSUPWD) {
		m_edtPwd.EnableWindow(FALSE);
		m_edtRetry.EnableWindow(FALSE);
		m_btnResetPwd.EnableWindow(FALSE);
		m_btnSetPwd.EnableWindow(FALSE);
	} else {
		m_edtPwd.EnableWindow(TRUE);
		m_edtRetry.EnableWindow(TRUE);
		m_btnResetPwd.EnableWindow(TRUE);
		m_btnSetPwd.EnableWindow(TRUE);
	}
}

void CDlgEyecare::OnBnClickedBtnReset()
{
	m_strRetryPwd = "";
	m_strPassword = "";
	UpdateData(FALSE);
}
