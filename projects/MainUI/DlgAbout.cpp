// DlgAbout.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgAbout.h"
#include ".\dlgabout.h"
#include ".\Dlgregister.h"

// CDlgAbout 对话框

IMPLEMENT_DYNAMIC(CDlgAbout, CDialog)
CDlgAbout::CDlgAbout(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgAbout::IDD, pParent)
{
}

CDlgAbout::~CDlgAbout()
{
}


int CDlgAbout::OnApply() {
	return 0;
}

void CDlgAbout::OnShow() {
}

void CDlgAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STA_ABOUT, m_staAbout);
	DDX_Control(pDX, IDC_WEBSITE_URL, m_sWebURL);
	DDX_Control(pDX, IDC_OUR_EMAIL, m_sEmail);
	DDX_Control(pDX, IDC_OUR_MAILLIST, m_sMailList);
}


BEGIN_MESSAGE_MAP(CDlgAbout, CDialog)
	ON_BN_CLICKED(IDC_REGISTER, OnBnClickedRegister)
END_MESSAGE_MAP()


// CDlgAbout 消息处理程序

void CDlgAbout::OnBnClickedRegister() {
	CDlgRegister dlg;
	dlg.DoModal();
}

BOOL CDlgAbout::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	CString str;
	str.LoadString(IDS_OUR_MAIL_URL);
	m_sEmail.SetURL(str);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
