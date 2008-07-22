// DlgDNSRule.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgDNSRule.h"


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
}

void CDlgDNSRule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgDNSRule, CDialog)
END_MESSAGE_MAP()


// CDlgDNSRule 消息处理程序
