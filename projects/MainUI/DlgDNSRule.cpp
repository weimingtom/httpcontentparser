// DlgDNSRule.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgDNSRule.h"
#include ".\dlgdnsrule.h"


// CDlgDNSRule 对话框

IMPLEMENT_DYNAMIC(CDlgDNSRule, CDialog)
CDlgDNSRule::CDlgDNSRule(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgDNSRule::IDD, pParent)
{
}

CDlgDNSRule::~CDlgDNSRule()
{
}

void CDlgDNSRule::OnApply() {
}

void CDlgDNSRule::OnShow() {
	ListBox.ShowWindow(SW_SHOW);
}

void CDlgDNSRule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DNS_LIST, ListBox);
}


BEGIN_MESSAGE_MAP(CDlgDNSRule, CDialog)
END_MESSAGE_MAP()


// CDlgDNSRule 消息处理程序

BOOL CDlgDNSRule::OnInitDialog()
{
	CBaseDlg::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
}
