// DlgDNSRule.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgDNSRule.h"
#include ".\dlgdnsrule.h"


// CDlgDNSRule �Ի���

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


// CDlgDNSRule ��Ϣ�������

BOOL CDlgDNSRule::OnInitDialog()
{
	CBaseDlg::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
}
