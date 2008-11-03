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
#include <timeoutswitch.h>

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

BOOL notifyCOMServiceHotkey(WORD vKey, WORD vModifiers, const int type) {
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

BOOL setHotkey(WORD vKey, WORD vModifiers_mfc, const int type) {
	// 首先注销当前的热键
	UnregisterHotKey(AfxGetMainWnd()->GetSafeHwnd(), type);

	WORD vModifier = getModifierKey(vModifiers_mfc);
	if (0 != vModifier && 0 != vKey) {	
		if (!RegisterHotKey(AfxGetMainWnd()->GetSafeHwnd(), type, vModifier,vKey)) {
			// 如果失败，则设置为0
			g_configuration.getHotkey()->setHotkey(getHotkeyname(type), (unsigned)MAKELPARAM(0, 0));
			UnregisterHotKey(AfxGetMainWnd()->GetSafeHwnd(), type);
			return FALSE;
		}
	} else {
		UnregisterHotKey(AfxGetMainWnd()->GetSafeHwnd(), type);
	}

	// 是COM Service知道信息，以便保存
	g_configuration.getHotkey()->setHotkey(getHotkeyname(type), (unsigned)MAKELPARAM(vModifier, vKey));
	notifyCOMServiceHotkey(vKey, vModifier, type);
	return TRUE;
}
};


// 如过CHECK_BOX选中，则Sliderbar可用，反之则不可用
void CDlgOptions::UpdateAutoswitchState() {
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_ENABLE_TIMEOUT_SWITCH)) {
		m_sldTimeout.EnableWindow(TRUE);
	} else {
		m_sldTimeout.EnableWindow(FALSE);
	}
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
	DDX_Control(pDX, IDC_HOTKEY_LAUNCH, m_hotkeyLaunch);
	DDX_Control(pDX, IDC_STA_TIMEOUT, m_staTimeoutValue);
	DDX_Control(pDX, IDC_SLD_TIMEOUT, m_sldTimeout);
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
	if (!notifyCOMServiceHotkey(vKey, vModifier, HOTKEY_LANUCH_MAINUI)) {
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
		// 如果热键冲突
		Restore();
		return -1;
	}
	return 0;
}

int CDlgOptions::restoreAutoswitchSetting() {
	m_sldTimeout.SetRange(1, 120);
	m_sldTimeout.SetTicFreq(10);
	int pos = g_configuration.getTimeoutSwitch()->getTimeoutValue() / 60;
	m_sldTimeout.SetPos(pos);

	CString str;
	str.Format("%d", pos);
	m_staTimeoutValue.SetWindowText(str);

	CheckDlgButton(IDC_CHK_ENABLE_TIMEOUT_SWITCH, 
		g_configuration.getTimeoutSwitch()->isEnabled() ? BST_CHECKED : BST_UNCHECKED);
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

	restoreAutoswitchSetting();
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
	ON_BN_CLICKED(IDC_CHK_ENABLE_TIMEOUT_SWITCH, OnBnClickedChkEnableTimeoutSwitch)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CDlgOptions 消息处理程序
BOOL CDlgOptions::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	Restore();
	if (-1 == setHotKey()) {
		// 如果热键冲突
		Restore();
	}

	UpdateAutoswitchState();
	return TRUE;
}

void CDlgOptions::OnBnClickedChkAutoload() {
	SetModify(true);
}

// 当有按键按下且相应消息的是HOTKEY CONTROL
// 则是button 'OK' and 'Cancel' 可用
BOOL CDlgOptions::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		if (m_hotkeyLaunch.GetSafeHwnd() == pMsg->hwnd||
			m_hotKeyShowDlg.GetSafeHwnd() == pMsg->hwnd||
			m_hotkeySwitchUser.GetSafeHwnd() == pMsg->hwnd) {
				SetModify(true);
		}	
	}
	return CBaseDlg::PreTranslateMessage(pMsg);
}

void CDlgOptions::OnBnClickedChkEnableTimeoutSwitch()
{
	UpdateAutoswitchState();
	SetModify(true);
}

void CDlgOptions::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar->GetSafeHwnd() == m_sldTimeout.GetSafeHwnd()) {
		CString str;
		str.Format("%d", m_sldTimeout.GetPos());
		m_staTimeoutValue.SetWindowText(str);
		SetModify(true);
	}
	CBaseDlg::OnHScroll(nSBCode, nPos, pScrollBar);
}
