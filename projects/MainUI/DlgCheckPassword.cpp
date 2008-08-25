// DlgCheckPassword.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgCheckPassword.h"
#include ".\dlgcheckpassword.h"


// CDlgCheckPassword �Ի���

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


// CDlgCheckPassword ��Ϣ�������

void CDlgCheckPassword::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}

BOOL CDlgCheckPassword::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_btnOk.SetStyleBorder(CGuiButton::STYLEXP);
	m_btnOk.SetCaption("OK");
	m_btnCancel.SetStyleBorder(CGuiButton::STYLEXP);
	m_btnCancel.SetCaption("Cancel");

	// set Icon
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	return TRUE;  // return TRUE unless you set the focus to a control
}

HCURSOR CDlgCheckPassword::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
