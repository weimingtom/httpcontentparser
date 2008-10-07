// DlgCheckPassword.cpp : 实现文件
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\dlgcheckpassword.h"
#include ".\globalvariable.h"
#include <typeconvert.h>
#include <com\COMInit.h>


// CDlgCheckPassword 对话框

IMPLEMENT_DYNAMIC(CDlgCheckPassword, CDialog)
CDlgCheckPassword::CDlgCheckPassword(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCheckPassword::IDD, pParent)
	, m_strPassword(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CDlgCheckPassword::~CDlgCheckPassword()
{
}

// 检测密码
bool CDlgCheckPassword::checkPassword() {
	UpdateData(TRUE);
	AutoInitInScale auto_;
	try {
		VARIANT_BOOL bSucc;
		IAppSetting *appSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IAppSetting, (LPVOID*)&appSetting);
		appSetting->switchModel(VARIANT_TRUE, _bstr_t((LPCTSTR)m_strPassword), &bSucc);

		return convert(bSucc);
	} catch (_com_error &) {
		return false;
	}
}
void CDlgCheckPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_PASSWORD, m_edtPassword);
	DDX_Text(pDX, IDC_EDT_PASSWORD, m_strPassword);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CDlgCheckPassword, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CDlgCheckPassword 消息处理程序

void CDlgCheckPassword::OnBnClickedOk()
{
	if (checkPassword() == true) {
		OnOK();
	} else {
		CString strAlert;
		strAlert.LoadString(IDS_CHECK_PASSWORD_WRONG);
		AfxMessageBox(strAlert, MB_OK | MB_ICONSTOP | MB_APPLMODAL );
	}
}

BOOL CDlgCheckPassword::OnInitDialog()
{
	CDialog::OnInitDialog();

	// set Icon
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	return TRUE;  // return TRUE unless you set the focus to a control
}

HCURSOR CDlgCheckPassword::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
