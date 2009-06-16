// DlgDNSRule.cpp : 实现文件
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\DlgBlackDNSList.h"
#include ".\ContentList.h"
#include ".\globalvariable.h"
#include <logger\logger.h>
#include <typeconvert.h>

// CDlgBlackDNSList 对话框

IMPLEMENT_DYNAMIC(CDlgBlackDNSList, CDialog)
CDlgBlackDNSList::CDlgBlackDNSList(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgBlackDNSList::IDD, pParent)
	, rules(this, this)
{
	m_bEnableBlackDNS = TRUE;
	auther_name_ = ANOTHER_BWL;
}

CDlgBlackDNSList::~CDlgBlackDNSList()
{
}

std::string CDlgBlackDNSList::getHelpLink() const {
	return "";
}


int CDlgBlackDNSList::OnApply() {
	rules.Apply();

	// DNS CHECK是否可用
	ASSERT(g_dnssetting != NULL);
	g_dnssetting->enableBlackDNSCheck(convert(m_chkEnableDNS.GetCheck() == BST_CHECKED));
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

	try {
		BSTR cur, next;
		g_dnssetting->getFirstBlackDNS(&cur);
		while (_bstr_t(cur).length() != 0) {
			ListBox.AddItem((TCHAR*)_bstr_t(cur));
			g_dnssetting->getNextBlackDNS(cur, &next);
			SysFreeString(cur); 
			cur = next;
		}

		VARIANT_BOOL isEnabled;
		g_dnssetting->isBlackDNSSettingEnable(&isEnabled);
		m_bEnableBlackDNS = convert(isEnabled);

		UpdateData(FALSE);
	} catch(...) {
		__LERR__("CATCH...");
		throw int(SNOWMAN_ERROR_COM_INIT_FAILED);
	}

}

// add items
void CDlgBlackDNSList::OnAddItem(const CString &str) {
	ASSERT (NULL != g_dnssetting);
	g_dnssetting->addBlackDNS(_bstr_t(str));
}
void CDlgBlackDNSList::OnDelItem(const CString &str) {
	ASSERT (NULL != g_dnssetting);
	g_dnssetting->removeBlackDNS(_bstr_t(str));
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

	return TRUE; 
}

void CDlgBlackDNSList::OnBnClickedChkBlackDnslist() {
	SetModify(true);
}

