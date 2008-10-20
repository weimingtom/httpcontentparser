// DlgOptions.cpp : 实现文件
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\dlgoptions.h"
#include ".\globalvariable.h"
#include <app_constants.h>
#include <xmldefined.h>
#include <sysutility.h>
#include <comdef.h>
#include <com\comutility.h>
#include <typeconvert.h>

// CDlgOptions 对话框

IMPLEMENT_DYNAMIC(CDlgOptions, CDialog)
CDlgOptions::CDlgOptions(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgOptions::IDD, pParent)
	, m_bAutoRun(FALSE)
{
}

CDlgOptions::~CDlgOptions() {
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

WORD  getModifierKeyMFC(WORD kModify) {
	WORD vModifiers_mfc  = 0;
	if (kModify & MOD_SHIFT)
		vModifiers_mfc |= HOTKEYF_SHIFT;
	if (kModify & MOD_CONTROL)
		vModifiers_mfc |= HOTKEYF_CONTROL;
	if (kModify & MOD_ALT)
		vModifiers_mfc |= HOTKEYF_ALT;

	return vModifiers_mfc;
}

BOOL setLaunchHotkey(WORD vKey, WORD vModifiers, const int type) {
	try {
		AutoInitInScale auto_init_com;
		VARIANT_BOOL bSucc;
		IAppSetting *app = NULL;
		CoCreateInstance(CLSID_AppSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IAppSetting, (LPVOID*)&app);
		app->setHotkey(vKey, vModifiers, type, &bSucc);
		return convert(bSucc);
	} catch(...) {
		return FALSE;
	}
}

TCHAR * getHotkeyname(const int type) {
	switch (type) {
		case HOTKEY_SHOW_MAINUI:
			return CONFIG_HOTKEY_SHOWUI;
		case HOTKEY_SHOW_SWITCH_USER:
			return CONFIG_HOTKEY_SWITCHUSER;
		case HOTKEY_LANUCH_MAINUI:
			return CONFIG_HOTKEY_LAUNCH;
		default:
			ASSERT(false);
			return TEXT("");
	}
}

BOOL setHotkey(WORD vKey, WORD vModifiers_mfc, const int type) {
	WORD vModifier = getModifierKey(vModifiers_mfc);
	if (0 != vModifier && 0 != vKey) {
		if (!RegisterHotKey(AfxGetMainWnd()->GetSafeHwnd() ,type, vModifier,vKey)) 
			return FALSE;
	} else {
		UnregisterHotKey(AfxGetMainWnd()->GetSafeHwnd() ,type);
	}

	g_configuration.getHotkey()->setHotkey(getHotkeyname(type), (unsigned)MAKELPARAM(vModifier, vKey));
	return TRUE;
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

int CDlgOptions::setHotKey() {
	CString strPrompt;
	strPrompt.LoadString(IDS_HOTKEY_CONFLICT);

	// 注册热键
	WORD vModifiers_mfc, vKey;

	// 设置显示对话框的热键
	m_hotKeyShowDlg.GetHotKey(vKey, vModifiers_mfc);
	if (FALSE == ::setHotkey(vKey, vModifiers_mfc, HOTKEY_SHOW_MAINUI)) {
		AfxMessageBox(strPrompt);
		return -1;
	}

	// 设置显示对话框的热键
	m_hotkeySwitchUser.GetHotKey(vKey, vModifiers_mfc);
	if (FALSE == ::setHotkey(vKey, vModifiers_mfc, HOTKEY_SHOW_SWITCH_USER)) {
		AfxMessageBox(strPrompt);
		return -1;
	}


	// 设置启动程序， 必须通过COM设置
	m_hotkeyLaunch.GetHotKey(vKey, vModifiers_mfc);
	WORD vModifier = getModifierKey(vModifiers_mfc);
	if (!setLaunchHotkey(vKey, vModifier, HOTKEY_LANUCH_MAINUI)) {
		CString strPrompt;
		strPrompt.LoadString(IDS_HOTKEY_CONFLICT);
		MessageBox(strPrompt);
		return -1;
	}

	// 保存热键
	g_configuration.getHotkey()->setHotkey(getHotkeyname(HOTKEY_LANUCH_MAINUI),
		(unsigned)MAKELPARAM(vModifier, vKey));

	return 0;
}


int CDlgOptions::OnApply() {
	SetAutoRun();
	if ( -1 == setHotKey()) {
		return -1;
	}
	return 0;
}

// 恢复设置
void CDlgOptions::restoreSetting() {	
	// 热键
	DWORD hotkey = (DWORD)g_configuration.getHotkey()->getHotkey(getHotkeyname(HOTKEY_LANUCH_MAINUI));
	m_hotkeyLaunch.SetHotKey(HIWORD(hotkey),	getModifierKeyMFC(LOWORD(hotkey)));

	hotkey = (DWORD)g_configuration.getHotkey()->getHotkey(getHotkeyname(HOTKEY_SHOW_MAINUI));
	m_hotKeyShowDlg.SetHotKey(HIWORD(hotkey),	getModifierKeyMFC(LOWORD(hotkey)));

	hotkey = (DWORD)g_configuration.getHotkey()->getHotkey(getHotkeyname(HOTKEY_SHOW_SWITCH_USER));
	m_hotkeySwitchUser.SetHotKey(HIWORD(hotkey), getModifierKeyMFC(LOWORD(hotkey)));

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

void CDlgOptions::OnBnClickedChkAutoload() {
	SetModify(true);
}