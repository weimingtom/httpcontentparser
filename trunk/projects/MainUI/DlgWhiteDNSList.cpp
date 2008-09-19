// DlgWhiteDNSList.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgWhiteDNSList.h"
#include ".\dlgwhitednslist.h"
#include "globalvariable.h"

// CDlgWhiteDNSList 对话框

IMPLEMENT_DYNAMIC(CDlgWhiteDNSList, CDialog)
CDlgWhiteDNSList::CDlgWhiteDNSList(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgWhiteDNSList::IDD, pParent)
{
}

CDlgWhiteDNSList::~CDlgWhiteDNSList()
{
}

void CDlgWhiteDNSList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_WHITE_DNSLIST, m_chkWhiteDNSList);
	DDX_Control(pDX, IDC_STA_WHIE_DNSLIST, ListBox);
}

void CDlgWhiteDNSList::OnRestore() {

}

void CDlgWhiteDNSList::OnApply() {
	rules.OnApply();
	ASSERT(g_dnssetting != NULL);
	g_dnssetting->enableWhiteDNSCheck((m_chkWhiteDNSList.GetCheck() == BST_CHECKED));
}

void CDlgWhiteDNSList::OnShow() {
	ListBox.SetFocus();
	ListBox.ShowWindow(SW_SHOW);
	ListBox.UpdateWindow();
}

void CDlgWhiteDNSList::initializeData() {
	white_url_set.addDNS("google");
	white_url_set.beginEnum((Enumerator1<std::string>*)this);

	m_chkWhiteDNSList.m_bCheckBtn = white_url_set.needChecked();
}

int CDlgWhiteDNSList::Enum(const std::string &dns) {
	ListBox.AddItem(dns.c_str());
	return 0;
}
BEGIN_MESSAGE_MAP(CDlgWhiteDNSList, CDialog)
END_MESSAGE_MAP()


// CDlgWhiteDNSList 消息处理程序

BOOL CDlgWhiteDNSList::OnInitDialog()
{
	CBaseDlg::OnInitDialog();
	ListBox.setOnTextChanged(&rules);

	initializeData();

	return TRUE;  // return TRUE unless you set the focus to a control
}
