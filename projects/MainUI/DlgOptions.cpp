// DlgOptions.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgOptions.h"
#include ".\dlgoptions.h"
#include <app_constants.h>
#include <sysutility.h>
#include <comdef.h>
#include <com\comutility.h>
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <typeconvert.h>

// CDlgOptions 对话框

IMPLEMENT_DYNAMIC(CDlgOptions, CDialog)
CDlgOptions::CDlgOptions(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgOptions::IDD, pParent)
	, m_bAutoRun(FALSE)
{
	m_wLaunchKey = 0;
	m_wLaunchModifier = 0;
	m_wMainUIKey = 0;
	m_wMainUIModifier = 0;
	m_wSwitchUserKey = 0;
	m_wSwitchUserModifier = 0;
}

CDlgOptions::~CDlgOptions()
{
}

namespace {
// 注意API的HOTKEY与MFC定义的值不相同，真是晕菜
WORD  getModifierKey(WORD kModify_mfc) {
	WORD vModifiers  = 0;
	if (kModify_mfc & HOTKEYF_SHIFT)
		vModifiers |= MOD_SHIFT;
	if (kModify_mfc & HOTKEYF_CONTROL)
		vModifiers |= MOD_CONTROL;
	if (kModify_mfc & HOTKEYF_ALT)
		vModifiers |= MOD_ALT;

	return vModifiers;
}

BOOL setLaunchHotkey(WORD vKey, WORD vModifiers) {
	try {
		AutoInitInScale auto_init_com;
		VARIANT_BOOL bSucc;
		IAppSetting *app = NULL;
		CoCreateInstance(CLSID_AppSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IAppSetting, (LPVOID*)&app);
		app->setHotkey(vKey, vModifiers, HOTKEY_LANUCH_MAINUI, &bSucc);
		return convert(bSucc);
	} catch(...) {
		return FALSE;
	}
}
};

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
	DDX_Control(pDX, IDC_HOTKEY_LAUNCH, m_hotkeyLaunch);
}

void CDlgOptions::setHotKey() {
	CString strPrompt;
	strPrompt.LoadString(IDS_HOTKEY_CONFLICT);

	// 注册热键
	WORD vModifiers_mfc;

	// 设置显示对话框的热键
	m_hotKeyShowDlg.GetHotKey(m_wMainUIKey, vModifiers_mfc);
	m_wMainUIModifier = getModifierKey(vModifiers_mfc);
	if (0 != m_wMainUIKey && 0 != m_wMainUIModifier) {
		if (!RegisterHotKey(AfxGetMainWnd()->GetSafeHwnd() ,HOTKEY_SHOW_MAINUI, m_wMainUIModifier,m_wMainUIKey)) {
			MessageBox(strPrompt);
			return;
		}
	} else {
		UnregisterHotKey(AfxGetMainWnd()->GetSafeHwnd() ,HOTKEY_SHOW_MAINUI);
	}

	// 设置显示对话框的热键
	m_hotkeySwitchUser.GetHotKey(m_wSwitchUserKey, vModifiers_mfc);
	m_wSwitchUserModifier = getModifierKey(vModifiers_mfc);
	if (0 != m_wSwitchUserModifier && 0 != m_wSwitchUserKey) {
		if (!RegisterHotKey(AfxGetMainWnd()->GetSafeHwnd(), HOTKEY_SHOW_SWITCH_USER, m_wSwitchUserModifier, m_wSwitchUserKey)) {
			MessageBox(strPrompt);
			return;
		}
	} else {
		UnregisterHotKey(AfxGetMainWnd()->GetSafeHwnd() ,HOTKEY_SHOW_SWITCH_USER);
	}

	// 设置启动程序， 必须通过COM设置
	m_hotkeyLaunch.GetHotKey(m_wLaunchKey, vModifiers_mfc);
	m_wLaunchModifier = getModifierKey(vModifiers_mfc);
	if (!setLaunchHotkey(m_wLaunchKey, m_wLaunchModifier)) {
		MessageBox(strPrompt);
		return;
	}
}


int CDlgOptions::OnApply() {
	setHotKey();
	SetAutoRun();
	return 0;
}

void CDlgOptions::restoreSetting() {	
	// 热键
	m_hotkeyLaunch.SetHotKey(m_wLaunchKey, m_wLaunchModifier);
	m_hotKeyShowDlg.SetHotKey(m_wMainUIKey, m_wMainUIModifier);
	m_hotkeySwitchUser.SetHotKey(m_wSwitchUserKey, m_wSwitchUserModifier);

	// 自动运行
	m_bAutoRun = isAutoRun((HMODULE)AfxGetInstanceHandle());
	m_bOld_autorun = m_bAutoRun;
	UpdateData(FALSE);
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
	ON_BN_CLICKED(IDC_CHK_AUTOLOAD, OnBnClickedChkAutoload)
END_MESSAGE_MAP()


// CDlgOptions 消息处理程序
BOOL CDlgOptions::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	Restore();
	return TRUE;
}

void CDlgOptions::OnBnClickedChkAutoload()
{
	SetModify(true);
}
