// DlgSearchRule.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgSearchRule.h"


// CDlgSearchRule 对话框

IMPLEMENT_DYNAMIC(CDlgSearchRule, CDialog)
CDlgSearchRule::CDlgSearchRule(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgSearchRule::IDD, pParent)
{
}

CDlgSearchRule::~CDlgSearchRule()
{
}

void CDlgSearchRule::OnApply() {
}


void CDlgSearchRule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSearchRule, CDialog)
END_MESSAGE_MAP()


// CDlgSearchRule 消息处理程序
