// DlgOptions.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgOptions.h"
#include ".\dlgoptions.h"
#include <hotkey.h>
#include <sysutility.h>
#include <comdef.h>
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>


// CDlgOptions 对话框

IMPLEMENT_DYNAMIC(CDlgOptions, CDialog)
CDlgOptions::CDlgOptions(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgOptions::IDD, pParent)
	, m_bAutoRun(FALSE)
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
	DDX_Check(pDX, IDC_CHK_AUTOLOAD, m_bAutoRun);
}

void CDlgOptions::setHotKey() {
	CString strPrompt;
	strPrompt.LoadString(IDS_HOTKEY_CONFLICT);

	// 设置显示对话框的热键
	//WORD vKey, vModifiers;
	//m_hotKeyShowDlg.GetHotKey(vKey, vModifiers);

	//if (!RegisterHotKey(AfxGetMainWnd()->GetSafeHwnd() ,100,vModifiers,vKey)) {
	//	
	//	MessageBox(strPrompt);
	//	return;
	//}

	//m_hotkeySwitchUser.GetHotKey(vKey, vModifiers);
	//if (!RegisterHotKey(AfxGetMainWnd()->GetSafeHwnd(),100,vModifiers,vKey)) {
	//	MessageBox(strPrompt);
	//	return;
	//}
}

void CDlgOptions::OnRestore() {
}


void CDlgOptions::OnApply() {
	setHotKey();

	SetAutoRun();
}
void CDlgOptions::OnShow() {
}

void CDlgOptions::SetAutoRun() {
	UpdateData();
	if (m_bAutoRun != m_bOld_autorun) {
		m_bOld_autorun = m_bAutoRun;
		TCHAR fullpath[MAX_PATH];
		GetModuleFileName((HMODULE)AfxGetInstanceHandle(), fullpath, MAX_PATH);
		RegisterAutoRun(fullpath, m_bOld_autorun);
	}
}

BEGIN_MESSAGE_MAP(CDlgOptions, CDialog)
END_MESSAGE_MAP()


// CDlgOptions 消息处理程序
BOOL CDlgOptions::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	m_bAutoRun = isAutoRun((HMODULE)AfxGetInstanceHandle());
	m_bOld_autorun = m_bAutoRun;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
}
