// DlgOptions.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgOptions.h"


// CDlgOptions 对话框

IMPLEMENT_DYNAMIC(CDlgOptions, CDialog)
CDlgOptions::CDlgOptions(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgOptions::IDD, pParent)
{
}

CDlgOptions::~CDlgOptions()
{
}

void CDlgOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_AUTOLOAD, m_chkAutoLoad);
	DDX_Control(pDX, IDC_STA_SYSTEM, m_staSystemOption);
	DDX_Control(pDX, IDC_STA_OTHERS, m_staOthers);
	DDX_Control(pDX, IDC_STA_HOTKEY, m_staHotkey);
	DDX_Control(pDX, IDC_HOTKEY_SHOWDLG, m_hotKeyShowDlg);
	DDX_Control(pDX, IDC_HOTKEY_SWITCHUSR, m_hotkeySwitchUser);
}


void CDlgOptions::OnApply() {
}
void CDlgOptions::OnShow() {
}

BEGIN_MESSAGE_MAP(CDlgOptions, CDialog)
END_MESSAGE_MAP()


// CDlgOptions 消息处理程序
