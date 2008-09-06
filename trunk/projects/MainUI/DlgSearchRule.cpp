// DlgSearchRule.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgSearchRule.h"
#include "globalvariable.h"

// CDlgSearchRule �Ի���

IMPLEMENT_DYNAMIC(CDlgSearchRule, CDialog)
CDlgSearchRule::CDlgSearchRule(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgSearchRule::IDD, pParent)
{
}

CDlgSearchRule::~CDlgSearchRule()
{
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
}


BEGIN_MESSAGE_MAP(CDlgSearchRule, CDialog)
END_MESSAGE_MAP()


// CDlgSearchRule ��Ϣ�������
