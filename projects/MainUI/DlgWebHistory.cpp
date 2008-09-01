// DlgWebHistory.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgWebHistory.h"


// CDlgWebHistory 对话框

IMPLEMENT_DYNAMIC(CDlgWebHistory, CDialog)
CDlgWebHistory::CDlgWebHistory(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgWebHistory::IDD, pParent) {
}

CDlgWebHistory::~CDlgWebHistory()
{
}

void CDlgWebHistory::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_EXPORT_WEBSITES, m_btnExportWebSiteList);
	DDX_Control(pDX, IDC_BTN_HISTORY, m_btnViewtheHistory);
	DDX_Control(pDX, IDC_BUN_CLEAR_CACHE, m_btnClearCache);
	DDX_Control(pDX, IDC_STA_TOOLS, m_staTools);
	DDX_Control(pDX, IDC_STA_HISTORY, m_staHistory);
	DDX_Control(pDX, IDC_STA_TYPES, m_staTypes);
}


void CDlgWebHistory::OnApply() {
}
void CDlgWebHistory::OnShow() {
}

BEGIN_MESSAGE_MAP(CDlgWebHistory, CDialog)
END_MESSAGE_MAP()


// CDlgWebHistory 消息处理程序
