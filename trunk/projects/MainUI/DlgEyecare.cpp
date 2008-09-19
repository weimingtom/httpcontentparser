// DlgEyecare.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgEyecare.h"
#include ".\dlgeyecare.h"
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <comdef.h>

// CDlgEyecare 对话框

IMPLEMENT_DYNAMIC(CDlgEyecare, CDialog)
CDlgEyecare::CDlgEyecare(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgEyecare::IDD, pParent)
	, m_strRetryPwd(_T(""))
	, m_strPassword(_T(""))
	, m_nEntertainTime(0)
	, m_nRestTime(0)
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
	DDX_Text(pDX, IDC_EDT_ENTERTIME, m_nEntertainTime);
	DDX_Text(pDX, IDC_EDT_RESTTIME, m_nRestTime);
}


void CDlgEyecare::OnRestore() {

}

void CDlgEyecare::OnApply() {
	try {
		UpdateData(TRUE);
		IEyecare *pEyeCare = NULL;
		CoCreateInstance(CLSID_Eyecare, NULL, CLSCTX_ALL, IID_IEyecare, (LPVOID*)&pEyeCare);
		pEyeCare->setEnterTime(m_nEntertainTime);
		pEyeCare->setEyecareTime(m_nRestTime);
		pEyeCare->Release();
	} catch (_com_error&) {
		// AfxMessageBox("");
	}
}

void CDlgEyecare::OnShow() {
}

BEGIN_MESSAGE_MAP(CDlgEyecare, CDialog)
	ON_BN_CLICKED(IDC_CHK_USE_SUPWD, OnBnClickedChkUseSupwd)
	ON_BN_CLICKED(IDC_BTN_RESET, OnBnClickedBtnReset)
END_MESSAGE_MAP()


// CDlgEyecare 消息处理程序

BOOL CDlgEyecare::OnInitDialog()
{
	CBaseDlg::OnInitDialog();
	m_btnResetPwd.SetStyleBorder(CGuiButton::STYLEXP);
	m_btnResetPwd.SetCaption("Reset");
	m_btnSetPwd.SetStyleBorder(CGuiButton::STYLEXP);
	m_btnSetPwd.SetCaption("Set");
	return TRUE;
}

void CDlgEyecare::OnBnClickedChkUseSupwd()
{
	if (FALSE == m_chkUseSuPwd.m_bCheckBtn) {
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
