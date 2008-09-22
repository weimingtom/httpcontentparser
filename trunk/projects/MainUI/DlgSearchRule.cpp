// DlgSearchRule.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgSearchRule.h"
#include "globalvariable.h"
#include ".\dlgsearchrule.h"

// CDlgSearchRule �Ի���

IMPLEMENT_DYNAMIC(CDlgSearchRule, CDialog)
CDlgSearchRule::CDlgSearchRule(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgSearchRule::IDD, pParent)
	, m_bEnableSearchRule(TRUE)
{
}

CDlgSearchRule::~CDlgSearchRule()
{
}

void CDlgSearchRule::OnRestore() {

}

void CDlgSearchRule::OnApply() {
	// DNS CHECK�Ƿ����
//	ASSERT(g_globalSetting != NULL);
// 	g_dnssetting->enableDNSCheck((m_chkEnableSearchChk.GetCheck() == BST_CHECKED));
}

void CDlgSearchRule::OnShow() {
	ListBox.SetFocus();
	ListBox.ShowWindow(SW_SHOW);
	ListBox.UpdateWindow();
}


void CDlgSearchRule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEARCH_LIST, ListBox);
	DDX_Control(pDX, IDC_CHK_ENABLE_SEARCH, m_chkEnableSearchChk);
	DDX_Check(pDX, IDC_CHK_ENABLE_SEARCH, m_bEnableSearchRule);
}

void CDlgSearchRule::initializeData() {
	g_configuration.getSearchRule()->enumBlackWord((Enumerator1<std::string>*)this);
	m_bEnableSearchRule = g_configuration.getSearchRule()->isEnabled();

	UpdateData(FALSE);
}

int CDlgSearchRule::Enum(const std::string &words) {
	ListBox.AddItem(words.c_str());
	return 0;
}

BEGIN_MESSAGE_MAP(CDlgSearchRule, CDialog)
END_MESSAGE_MAP()


// CDlgSearchRule ��Ϣ�������

BOOL CDlgSearchRule::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	initializeData();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
