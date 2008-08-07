// DlgOnlineHour.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgOnlineHour.h"
#include ".\basedlg.h"

// CDlgOnlineHour 对话框

IMPLEMENT_DYNAMIC(CDlgOnlineHour, CDialog)
CDlgOnlineHour::CDlgOnlineHour(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgOnlineHour::IDD, pParent)
{
}

CDlgOnlineHour::~CDlgOnlineHour()
{
}

void CDlgOnlineHour::OnApply() {
}

void CDlgOnlineHour::OnShow() {
}


void CDlgOnlineHour::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgOnlineHour, CDialog)
END_MESSAGE_MAP()


// CDlgOnlineHour 消息处理程序
