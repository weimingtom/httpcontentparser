// DlgChangePassword.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgChangePassword.h"
#include ".\dlgchangepassword.h"
#include <typeconvert.h>
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <comdef.h>

// ��ʼ����̬����
int CDlgChangePassword::static_dlg_show_cnt = false;
// CDlgChangePassword �Ի���

IMPLEMENT_DYNAMIC(CDlgChangePassword, CDialog)
CDlgChangePassword::CDlgChangePassword(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChangePassword::IDD, pParent)
	, m_strOrgin(_T(""))
	, m_strNew(_T(""))
	, m_strRetype(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
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

// �������ʱ��Ϸ�
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

	// ��֤����
	// if () {
	// }

	return true;
}

BEGIN_MESSAGE_MAP(CDlgChangePassword, CDialog)
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
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	static_dlg_show_cnt++;
	if (static_dlg_show_cnt > 1) {
		OnCancel();
		return FALSE;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlgChangePassword::OnBnClickedOk()
{
	try {
		UpdateData(TRUE);
		if (validate() == false) {
			resetFileds();
			AfxMessageBox("The Two password are not same!");
			return;
		} else if (checkOriginalPassword() == false) {
			AfxMessageBox("wrong password!");
			return;
		} else {
			// ��������
			IAuthorize *authorize = NULL;
			HRESULT hr = CoCreateInstance(CLSID_Authorize, NULL, CLSCTX_LOCAL_SERVER, IID_IAuthorize, (LPVOID*)&authorize);
			if (FAILED(hr)) {
				AfxMessageBox("check password failed!");
				return ;
			}

			VARIANT_BOOL changed;
			authorize->changePassword(_bstr_t(m_strNew), _bstr_t(m_strOrgin), &changed);
			authorize->Release();

			if (changed == false) {
				AfxMessageBox("change password failed!");
				return;
			}
		}
	} catch (_com_error &) {
		AfxMessageBox("Unknown error!");
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