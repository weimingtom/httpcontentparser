// DlgCheckPassword.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include ".\dlgcheckpassword.h"
#include <typeconvert.h>
#include ".\resource.h"


// CDlgCheckPassword �Ի���

IMPLEMENT_DYNAMIC(CDlgCheckPassword, CDialog)
CDlgCheckPassword::CDlgCheckPassword(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCheckPassword::IDD, pParent)
	, m_strPassword(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_KEY);
}

CDlgCheckPassword::~CDlgCheckPassword()
{
}

// �������
bool CDlgCheckPassword::checkPassword() {
	return true;
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
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CDlgCheckPassword ��Ϣ�������

void CDlgCheckPassword::OnBnClickedOk()
{
	if (checkPassword() == true) {
		OnOK();
	} else {
		CString strAlert;
		strAlert.LoadString(IDS_CHECK_PASSWORD_WRONG);
		AfxMessageBox(strAlert, MB_OK | MB_ICONSTOP | MB_APPLMODAL );

		m_strPassword = "";
		UpdateData(FALSE);
	}
}

BOOL CDlgCheckPassword::OnInitDialog()
{
	CDialog::OnInitDialog();

	// set Icon
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_strPassword = "";
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
}

HCURSOR CDlgCheckPassword::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDlgCheckPassword::OnDestroy()
{
	CDialog::OnDestroy();
}

void CDlgCheckPassword::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	m_edtPassword.SetFocus();
}
