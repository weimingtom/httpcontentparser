// DlgOptions.cpp : ʵ���ļ�
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

// CDlgOptions �Ի���

IMPLEMENT_DYNAMIC(CDlgOptions, CDialog)
CDlgOptions::CDlgOptions(CWnd* pParent /*=NULL*/)
: CBaseDlg(CDlgOptions::IDD, pParent)
, m_bAutoRun(FALSE)
{
}

CDlgOptions::~CDlgOptions() {
}

namespace {
	// ע��API��HOTKEY��MFC�����ֵ����ͬ�������β�
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
			AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
			return FALSE;
		}
	}

	BOOL setHotkey(WORD vKey, WORD vModifiers_mfc, const int type) {
		// ����ע����ǰ���ȼ�
		UnregisterHotKey(AfxGetMainWnd()->GetSafeHwnd(), type);

		WORD vModifier = getModifierKey(vModifiers_mfc);
		if (0 != vModifier && 0 != vKey) {	
			if (!RegisterHotKey(AfxGetMainWnd()->GetSafeHwnd(), type, vModifier,vKey)) {
				// ���ʧ�ܣ�������Ϊ0
				UnregisterHotKey(AfxGetMainWnd()->GetSafeHwnd(), type);
				return FALSE;
			}
		} else {
			UnregisterHotKey(AfxGetMainWnd()->GetSafeHwnd(), type);
		}

		// ��COM Service֪����Ϣ���Ա㱣��
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
	// ע���ȼ�
	WORD vModifiers_mfc, vKey;

	// ������ʾ�Ի�����ȼ�
	m_hotKeyShowDlg.GetHotKey(vKey, vModifiers_mfc);
	if (FALSE == ::setHotkey(vKey, vModifiers_mfc, HOTKEY_SHOW_MAINUI)) {
		AfxMessageBox(IDS_HOTKEY_CONFLICT, MB_OK | MB_ICONERROR);;
		return FAILED_APPLY;
	}

	// �����л��û����ȼ�
	m_hotkeySwitchUser.GetHotKey(vKey, vModifiers_mfc);
	if (FALSE == ::setHotkey(vKey, vModifiers_mfc, HOTKEY_SHOW_SWITCH_USER)) {
		AfxMessageBox(IDS_HOTKEY_CONFLICT, MB_OK | MB_ICONERROR);
		return FAILED_APPLY;
	}


	// ������������ ����ͨ��COM����
	m_hotkeyLaunch.GetHotKey(vKey, vModifiers_mfc);
	WORD vModifier = getModifierKey(vModifiers_mfc);
	if (!notifyCOMServiceHotkey(vKey, vModifier, HOTKEY_LANUCH_MAINUI)) {
		AfxMessageBox(IDS_HOTKEY_CONFLICT, MB_OK | MB_ICONERROR);
		return FAILED_APPLY;
	}

	return SUCCESS_APPLY;
}


int CDlgOptions::OnApply() {
	SetAutoRun();
	if ( FAILED_APPLY== setHotKey()) {
		// ����ȼ���ͻ
		Restore();
		return FAILED_APPLY;
	}
	return SUCCESS_APPLY;
}


// �ָ�����
void CDlgOptions::restoreSetting() {	
	try {
		AutoInitInScale auto_init_com;
		IAppSetting *app = NULL;
		HRESULT hr = CoCreateInstance(CLSID_AppSetting, NULL, CLSCTX_LOCAL_SERVER, IID_IAppSetting, (LPVOID*)&app);
		if (FAILED(hr)) {
			AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		// �ȼ�
		WORD vKey, vModifier;
		app->getHotkey(HOTKEY_LANUCH_MAINUI, &vKey, &vModifier);
		m_hotkeyLaunch.SetHotKey(vKey, vModifier);

		app->getHotkey(HOTKEY_SHOW_MAINUI, &vKey, &vModifier);
		m_hotKeyShowDlg.SetHotKey(vKey, vModifier);

		app->getHotkey(HOTKEY_SHOW_SWITCH_USER, &vKey, &vModifier);
		m_hotkeySwitchUser.SetHotKey(vKey, vModifier);

		// �Զ�����
		m_bAutoRun = isAutoRun();
		m_bOld_autorun = m_bAutoRun;

		UpdateData(FALSE);
	} catch (...) {

		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONEXCLAMATION);
	}
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


// CDlgOptions ��Ϣ�������
BOOL CDlgOptions::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	Restore();
	if (FAILED_APPLY == setHotKey()) {
		// ����ȼ���ͻ
		Restore();
	}
	return TRUE;
}

void CDlgOptions::OnBnClickedChkAutoload() {
	SetModify(true);
}

// ���а�����������Ӧ��Ϣ����HOTKEY CONTROL
// ����button 'OK' and 'Cancel' ����
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

