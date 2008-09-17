// DlgOnlineHour.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgOnlineHour.h"
#include ".\basedlg.h"
#include ".\dlgonlinehour.h"
#include "resource.h"

// CDlgOnlineHour 对话框
IMPLEMENT_DYNAMIC(CDlgOnlineHour, CDialog)
CDlgOnlineHour::CDlgOnlineHour(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgOnlineHour::IDD, pParent)
{
}

CDlgOnlineHour::~CDlgOnlineHour()
{
}

void CDlgOnlineHour::OnRestore() {

}

void CDlgOnlineHour::OnApply() {
}

void CDlgOnlineHour::OnShow() {
}


void CDlgOnlineHour::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_TIMECTRL, m_chkTimeCtrl);
}


BEGIN_MESSAGE_MAP(CDlgOnlineHour, CDialog)
END_MESSAGE_MAP()


// CDlgOnlineHour 消息处理程序

BOOL CDlgOnlineHour::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	CRect rect;
	GetDlgItem(IDC_STA_CELLS)->GetWindowRect(rect);
	cells.Create(NULL, NULL, WS_CHILD, rect, this, IDC_WND_HELLO);
	// ScreenToClient(&rect);
	cells.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
}

