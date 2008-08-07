// HelpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgHelp.h"
#include ".\dlghelp.h"


// CHelpDlg 对话框

IMPLEMENT_DYNAMIC(CDlgHelp, CDialog)
CDlgHelp::CDlgHelp(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgHelp::IDD, pParent)
{
}

CDlgHelp::~CDlgHelp()
{
}

void CDlgHelp::OnApply() {
}

void CDlgHelp::OnShow() {
}

void CDlgHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgHelp, CDialog)
END_MESSAGE_MAP()


// CDlgHelp 消息处理程序

BOOL CDlgHelp::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
