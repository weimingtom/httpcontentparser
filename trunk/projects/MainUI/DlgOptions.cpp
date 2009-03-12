// DlgOptions.cpp : 实现文件
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\dlgoptions.h"
#include ".\globalvariable.h"
#include <app_constants.h>
#include <xmldefined.h>
#include <apputility.h>
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
		HRESULT hr = CoCreateInstance(CLSID_AppSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IAppSetting, (LPVOID*)&app);
		if (FAILED(hr)) {
			AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONEXCLAMATION);
			return FALSE;
		}

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


void CDlgOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_AUTOLOAD, m_chkAutoLoad);
	DDX_Control(pDX, IDC_STA_SYSTEM, m_staSystemOption);
	DDX_Control(pDX, IDC_STA_HOTKEY, m_staHotkey);
	DDX_Control(pDX, IDC_HOTKEY_SHOWDLG, m_hotKeyShowDlg);
	DDX_Control(pDX, IDC_HOTKEY_SWITCHUSR, m_hotkeySwitchUser);
	DDX_Check(pDX, IDC_CHK_AUTOLOAD, m_bAutoRun);
	DDX_Control(pDX, IDC_HOTKEY_LAUNCH, m_hotkeyLaunch);
}

int CDlgOptions::setHotKey() {
	// 注册热键
	WORD vModifiers_mfc, vKey;

	// 设置显示对话框的热键
	m_hotKeyShowDlg.GetHotKey(vKey, vModifiers_mfc);
	if (FALSE == ::setHotkey(vKey, vModifiers_mfc, HOTKEY_SHOW_MAINUI)) {
		AfxMessageBox(IDS_HOTKEY_CONFLICT, MB_OK | MB_ICONERROR);;
		return FAILED_APPLY;
	}

	// 设置显示对话框的热键
	m_hotkeySwitchUser.GetHotKey(vKey, vModifiers_mfc);
	if (FALSE == ::setHotkey(vKey, vModifiers_mfc, HOTKEY_SHOW_SWITCH_USER)) {
		AfxMessageBox(IDS_HOTKEY_CONFLICT, MB_OK | MB_ICONERROR);
		return FAILED_APPLY;
	}


	// 设置启动程序， 必须通过COM设置
	m_hotkeyLaunch.GetHotKey(vKey, vModifiers_mfc);
	WORD vModifier = getModifierKey(vModifiers_mfc);
	if (!notifyCOMServiceHotkey(vKey, vModifier, HOTKEY_LANUCH_MAINUI)) {
		AfxMessageBox(IDS_HOTKEY_CONFLICT, MB_OK | MB_ICONERROR);
		return FAILED_APPLY;
	}

	// 保存热键
	g_configuration.getHotkey()->setHotkey(getHotkeyname(HOTKEY_LANUCH_MAINUI),
		(unsigned)MAKELPARAM(vModifier, vKey));

	return SUCCESS_APPLY;
}


int CDlgOptions::OnApply() {
	SetAutoRun();
	if ( FAILED_APPLY== setHotKey()) {
		// 如果热键冲突
		Restore();
		return FAILED_APPLY;
	}
	return SUCCESS_APPLY;
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
	m_bAutoRun = isAutoRun();
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
	if (FAILED_APPLY == setHotKey()) {
		// 如果热键冲突
		Restore();
	}
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

