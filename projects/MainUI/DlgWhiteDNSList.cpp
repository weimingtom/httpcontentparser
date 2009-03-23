// DlgWhiteDNSList.cpp : 实现文件
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\DlgWhiteDNSList.h"
#include ".\dlgwhitednslist.h"
#include ".\globalvariable.h"
#include <typeconvert.h>

// CDlgWhiteDNSList 对话框

IMPLEMENT_DYNAMIC(CDlgWhiteDNSList, CDialog)
CDlgWhiteDNSList::CDlgWhiteDNSList(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgWhiteDNSList::IDD, pParent)
	, rules(this, this)
	, m_bEnableWhiteDNS(TRUE)
	, m_bCheckDenyAllOthers(FALSE)
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
	DDX_Check(pDX, IDC_CHK_WHITE_DNSLIST, m_bEnableWhiteDNS);
	DDX_Check(pDX, IDC_CHK_DENY_OTHERS, m_bCheckDenyAllOthers);
}

int CDlgWhiteDNSList::OnApply() {
	UpdateData(TRUE);

	rules.Apply();
	ASSERT(g_dnssetting != NULL);
	g_dnssetting->enableWhiteDNSCheck(convert(m_chkWhiteDNSList.GetCheck() == BST_CHECKED));
	g_dnssetting->justEnableWhiteDNS(convert(m_bCheckDenyAllOthers));
	return 0;
}

void CDlgWhiteDNSList::OnShow() {
	ListBox.SetFocus();
	ListBox.ShowWindow(SW_SHOW);
	ListBox.UpdateWindow();
}

// 初始化设置
void CDlgWhiteDNSList::restoreSetting() {
	rules.Reset();
	ListBox.GetListCtrl()->DeleteAllItems();

	try {
		BSTR cur, next;
		g_dnssetting->getFirstWhiteDNS(&cur);
		while (_bstr_t(cur).length() != 0) {
			ListBox.AddItem((TCHAR*)_bstr_t(cur));
			g_dnssetting->getNextWhiteDNS(cur, &next);
			SysFreeString(cur); 
			cur = next;
		}

		VARIANT_BOOL isEnabled;
		g_dnssetting->isWhiteDNSSettingEnable(&isEnabled);
		m_bEnableWhiteDNS = convert(isEnabled);
		g_dnssetting->isJustEnableWhiteDNS(&isEnabled);
		m_bCheckDenyAllOthers = convert(isEnabled);

		UpdateData(FALSE);
	} catch(...) {
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
		return ;
	}
}

// 修改规则
void CDlgWhiteDNSList::OnAddItem(const CString &str) {
	ASSERT (NULL != g_dnssetting);
	g_dnssetting->addWhiteDNS(_bstr_t(str));
}
void CDlgWhiteDNSList::OnDelItem(const CString &str) {
	ASSERT (NULL != g_dnssetting);
	g_dnssetting->removeWhiteDNS(_bstr_t(str));
}
bool CDlgWhiteDNSList::ValidateItem(const CString & str, CString &output) {
	output = str;
	return true;
}


BEGIN_MESSAGE_MAP(CDlgWhiteDNSList, CDialog)
	ON_BN_CLICKED(IDC_CHK_DENY_OTHERS, OnBnClickedChkDenyOthers)
	ON_BN_CLICKED(IDC_CHK_WHITE_DNSLIST, OnBnClickedChkWhiteDnslist)
END_MESSAGE_MAP()


// CDlgWhiteDNSList 消息处理程序

BOOL CDlgWhiteDNSList::OnInitDialog()
{
	CBaseDlg::OnInitDialog();
	ListBox.setOnTextChanged(&rules);

	Restore();

	return TRUE;  // return TRUE unless you set the focus to a control
}

// 当点击此按钮时，另外一个复选框会被自动选中并不
void CDlgWhiteDNSList::OnBnClickedChkDenyOthers() {
	UpdateData(TRUE);
	if (m_bCheckDenyAllOthers == TRUE) {
		m_bEnableWhiteDNS = TRUE;
	}
	UpdateData(FALSE);
	SetModify(true);
}

// 当此复选框未被选中时，另外一个复选框也不能被选中
void CDlgWhiteDNSList::OnBnClickedChkWhiteDnslist() {
	UpdateData(TRUE);
	if (m_bEnableWhiteDNS== FALSE) {
		m_bCheckDenyAllOthers = FALSE;
	}
	UpdateData(FALSE);
	SetModify(true);
}
