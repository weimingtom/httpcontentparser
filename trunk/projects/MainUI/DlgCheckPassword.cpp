// DlgCheckPassword.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgCheckPassword.h"
#include ".\dlgcheckpassword.h"


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
	// TODO: 在此添加控件通知处理程序代码
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
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	return TRUE;  // return TRUE unless you set the focus to a control
}

HCURSOR CDlgCheckPassword::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
