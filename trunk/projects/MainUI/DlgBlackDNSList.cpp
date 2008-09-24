// DlgDNSRule.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\DlgBlackDNSList.h"
#include ".\ContentList.h"
#include ".\globalvariable.h"

// CDlgBlackDNSList �Ի���

IMPLEMENT_DYNAMIC(CDlgBlackDNSList, CDialog)
CDlgBlackDNSList::CDlgBlackDNSList(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgBlackDNSList::IDD, pParent)
{
	m_bEnableBlackDNS = TRUE;
}

CDlgBlackDNSList::~CDlgBlackDNSList()
{
}
void CDlgBlackDNSList::OnRestore() {

}

void CDlgBlackDNSList::OnApply() {
	rules.OnApply();

	// DNS CHECK�Ƿ����
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
	DDX_Check(pDX, IDC_CHK_ENABLE_DNS, m_bEnableBlackDNS);
}

void CDlgBlackDNSList::initializeData() {
	g_configuration.getBlackURLSet()->beginEnum((Enumerator1<std::string>*)this);
	m_bEnableBlackDNS = g_configuration.getBlackURLSet()->needChecked();
	UpdateData(FALSE);
}

int CDlgBlackDNSList::Enum(const std::string &dns) {
	ListBox.AddItem(dns.c_str());
	return 0;
}

BEGIN_MESSAGE_MAP(CDlgBlackDNSList, CDialog)
END_MESSAGE_MAP()


// CDlgBlackDNSList ��Ϣ�������

BOOL CDlgBlackDNSList::OnInitDialog()
{
	CBaseDlg::OnInitDialog();
	ListBox.setOnTextChanged(&rules);

	initializeData();

	return TRUE;  // return TRUE unless you set the focus to a control
}
