// DlgDNSRule.cpp : 实现文件
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\DlgBlackDNSList.h"
#include ".\ContentList.h"
#include ".\globalvariable.h"
#include <typeconvert.h>

// CDlgBlackDNSList 对话框

IMPLEMENT_DYNAMIC(CDlgBlackDNSList, CDialog)
CDlgBlackDNSList::CDlgBlackDNSList(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgBlackDNSList::IDD, pParent)
	, rules(this, this)
{
	m_bEnableBlackDNS = TRUE;
}

CDlgBlackDNSList::~CDlgBlackDNSList()
{
}


int CDlgBlackDNSList::OnApply() {
	rules.Apply();

	// DNS CHECK是否可用
	ASSERT(g_dnssetting != NULL);
	g_dnssetting->enableBlackDNSCheck(convert(m_chkEnableDNS.GetCheck() == BST_CHECKED));

	// 记录在配置文件
	g_configuration.getBlackURLSet()->enable(m_chkEnableDNS.GetCheck() == BST_CHECKED);
	return 0;
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
	DDX_Check(pDX, IDC_CHK_ENABLE_DNS, m_bEnableBlackDNS);
}

void CDlgBlackDNSList::restoreSetting() {
	// 充值
	rules.Reset();
	ListBox.GetListCtrl()->DeleteAllItems();
	
	g_configuration.getBlackURLSet()->beginEnum((Enumerator1<std::string>*)this);
	m_bEnableBlackDNS = g_configuration.getBlackURLSet()->isSettingEnabled();
	UpdateData(FALSE);
}

int CDlgBlackDNSList::Enum(const std::string &dns) {
	ListBox.AddItem(dns.c_str());
	return 0;
}

// add items
void CDlgBlackDNSList::OnAddItem(const CString &str) {
	ASSERT (NULL != g_dnssetting);
	g_dnssetting->addBlackDNS(_bstr_t(str));
	g_configuration.getBlackURLSet()->addDNS((LPCTSTR)str);
}
void CDlgBlackDNSList::OnDelItem(const CString &str) {
	ASSERT (NULL != g_dnssetting);
	g_dnssetting->removeBlackDNS(_bstr_t(str));
	g_configuration.getBlackURLSet()->removeDNS((LPCTSTR)str);
}
bool CDlgBlackDNSList::ValidateItem(const CString & str, CString &output) {
	output = str;
	return true;
}


BEGIN_MESSAGE_MAP(CDlgBlackDNSList, CDialog)
	ON_BN_CLICKED(IDC_CHK_ENABLE_DNS, OnBnClickedChkBlackDnslist)
END_MESSAGE_MAP()


// CDlgBlackDNSList 消息处理程序

BOOL CDlgBlackDNSList::OnInitDialog()
{
	CBaseDlg::OnInitDialog();
	ListBox.setOnTextChanged(&rules);

	Restore();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlgBlackDNSList::OnBnClickedChkBlackDnslist() {
	SetModify(true);
}

