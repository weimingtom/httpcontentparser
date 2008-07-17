// DlgImageRule.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgImageRule.h"


// CDlgImageRule 对话框

IMPLEMENT_DYNAMIC(CDlgImageRule, CDialog)
CDlgImageRule::CDlgImageRule(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgImageRule::IDD, pParent)
{
}

CDlgImageRule::~CDlgImageRule()
{
}

void CDlgImageRule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImageRule, CDialog)
END_MESSAGE_MAP()


// CDlgImageRule 消息处理程序
