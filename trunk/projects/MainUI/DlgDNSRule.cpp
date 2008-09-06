// DlgDNSRule.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgDNSRule.h"
#include ".\dlgdnsrule.h"
#include "ContentList.h"
#include "globalvariable.h"

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
	rules.OnApply();

	// DNS CHECK是否可用
	ASSERT(g_dnssetting != NULL);
	g_dnssetting->enableBlackDNSCheck((m_chkEnableDNS.GetCheck() == BST_CHECKED));
}

void CDlgDNSRule::OnShow() {
	ListBox.SetFocus();
	ListBox.ShowWindow(SW_SHOW);
	ListBox.UpdateWindow();
}

void CDlgDNSRule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DNS_LIST, ListBox);
	DDX_Control(pDX, IDC_CHK_ENABLE_DNS, m_chkEnableDNS);
}


BEGIN_MESSAGE_MAP(CDlgDNSRule, CDialog)
END_MESSAGE_MAP()


// CDlgDNSRule 消息处理程序

BOOL CDlgDNSRule::OnInitDialog()
{
	CBaseDlg::OnInitDialog();
	ListBox.setOnTextChanged(&rules);
	return TRUE;  // return TRUE unless you set the focus to a control
}
