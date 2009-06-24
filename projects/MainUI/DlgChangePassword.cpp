// DlgChangePassword.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgChangePassword.h"
#include ".\dlgchangepassword.h"
#include ".\services.h"
#include <typeconvert.h>
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <comdef.h>
#include <logger\logger.h>

// 初始化静态变量
int CDlgChangePassword::static_dlg_show_cnt = false;
// CDlgChangePassword 对话框

IMPLEMENT_DYNAMIC(CDlgChangePassword, CPopupDialog)
CDlgChangePassword::CDlgChangePassword(CWnd* pParent /*=NULL*/)
	: CPopupDialog(CDlgChangePassword::IDD, pParent)
	, m_strOrgin(_T(""))
	, m_strNew(_T(""))
	, m_strRetype(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_KEY);
}

CDlgChangePassword::~CDlgChangePassword()
{
}

void CDlgChangePassword::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_ORGIN, m_edtOrgin);
	DDX_Control(pDX, IDC_EDT_NEW, m_edtNew);
	DDX_Control(pDX, IDC_EDT_RETRY, m_edtRetry);
	DDX_Text(pDX, IDC_EDT_ORGIN, m_strOrgin);
	DDX_Text(pDX, IDC_EDT_NEW, m_strNew);
	DDX_Text(pDX, IDC_EDT_RETRY, m_strRetype);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}

// 检测密码时候合法
bool CDlgChangePassword::checkOriginalPassword() {
	IAuthorize *authorize = NULL;
	HRESULT hr = CoCreateInstance(CLSID_Authorize, NULL, CLSCTX_LOCAL_SERVER, IID_IAuthorize, (LPVOID*)&authorize);
	if (FAILED(hr)) {
		return false;
	}

	VARIANT_BOOL check;
	authorize->checkPassword(_bstr_t(m_strOrgin), &check);

	authorize->Release();
	return convert(check);
}

void CDlgChangePassword::resetFileds() {
	m_strNew = "";
	m_strRetype = "";
	m_strOrgin = "";
	UpdateData(TRUE);
}

bool CDlgChangePassword::validate() {
	if (m_strNew != m_strRetype) {
		return false;
	}

	// 验证密码
	// if () {
	// }

	return true;
}

BEGIN_MESSAGE_MAP(CDlgChangePassword, CPopupDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


BOOL CDlgChangePassword::OnInitDialog()
{
	CDialog::OnInitDialog();

	// set Icon
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	static_dlg_show_cnt++;
	if (static_dlg_show_cnt > 1) {
		OnCancel();
		return FALSE;
	}

	resetFileds();
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlgChangePassword::OnBnClickedOk()
{
	try {
		UpdateData(TRUE);
		if (validate() == false) {
			resetFileds();
			AfxMessageBox(IDS_PWD_NOT_SAME_WITH_CONFIRM);
			return;
		} else if (checkOriginalPassword() == false) {
			AfxMessageBox(IDS_PWD_CHECK_FAILED);
			return;
		} else {
			// 更改密码
			if (Services::setNewPwd(m_strNew, m_strOrgin) == false) {
				AfxMessageBox(IDS_PWD_FAILED_ON_CHANGE);
				return;
			}
		}
	} catch (_com_error &e) {
		AfxMessageBox(IDS_UNKNOW_ERROR);
		__LERR__( "_com_error exception with description "<< e.Description());
	}

	OnOK();
}

void CDlgChangePassword::OnBnClickedCancel()
{
	OnCancel();
}

HCURSOR CDlgChangePassword::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDlgChangePassword::OnDestroy()
{
	static_dlg_show_cnt--;
	CDialog::OnDestroy();
}

void CDlgChangePassword::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	m_edtOrgin.SetFocus();
}
