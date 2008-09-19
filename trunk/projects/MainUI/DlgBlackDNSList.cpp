// DlgDNSRule.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgBlackDNSList.h"
#include "ContentList.h"
#include "globalvariable.h"

// CDlgBlackDNSList 对话框

IMPLEMENT_DYNAMIC(CDlgBlackDNSList, CDialog)
CDlgBlackDNSList::CDlgBlackDNSList(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgBlackDNSList::IDD, pParent)
{
}

CDlgBlackDNSList::~CDlgBlackDNSList()
{
}
void CDlgBlackDNSList::OnRestore() {

}

void CDlgBlackDNSList::OnApply() {
	rules.OnApply();

	// DNS CHECK是否可用
	ASSERT(g_dnssetting != NULL);
	g_dnssetting->enableBlackDNSCheck((m_chkEnableDNS.GetCheck() == BST_CHECKED));
}

void CDlgBlackDNSList::OnShow() {
	ListBox.SetFocus();
	ListBox.ShowWindow(SW_SHOW);
	ListBox.UpdateWindow();
}

void CDlgBlackDNSList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DNS_LIST, ListBox);
	DDX_Control(pDX, IDC_CHK_ENABLE_DNS, m_chkEnableDNS);
}

void CDlgBlackDNSList::initializeData() {
	black_url_set.beginEnum((Enumerator1<std::string>*)this);
	m_chkEnableDNS.m_bCheckBtn = black_url_set.needChecked();
}

int CDlgBlackDNSList::Enum(const std::string &dns) {
	ListBox.AddItem(dns.c_str());
	return 0;
}

BEGIN_MESSAGE_MAP(CDlgBlackDNSList, CDialog)
END_MESSAGE_MAP()


// CDlgBlackDNSList 消息处理程序

BOOL CDlgBlackDNSList::OnInitDialog()
{
	CBaseDlg::OnInitDialog();
	ListBox.setOnTextChanged(&rules);

	initializeData();

	return TRUE;  // return TRUE unless you set the focus to a control
}
