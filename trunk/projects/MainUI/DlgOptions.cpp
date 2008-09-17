// DlgOptions.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgOptions.h"
#include ".\dlgoptions.h"
#include <hotkey.h>
#include <comdef.h>
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>


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

void CDlgOptions::setHotKey() {
	try {
		IAppSetting *pAppSetting = NULL;
		CoCreateInstance(CLSID_AppSetting, NULL, CLSCTX_ALL, IID_IAppSetting, (LPVOID*)&pAppSetting);
		VARIANT_BOOL  succ;
		WORD vKey, vModifiers;

		// 设置显示对话框的热键
		m_hotKeyShowDlg.GetHotKey(vKey, vModifiers);
		if (vKey != 0 || vModifiers != 0) {
			pAppSetting->setHotkey(vKey, vModifiers, HOTKEY_ID_POPUP_MAIN, &succ);
			if (succ == VARIANT_FALSE)
				throw int(0);
		}

		//  设置切换用户的热键
		m_hotkeySwitchUser.GetHotKey(vKey, vModifiers);
		if (vKey != 0 || vModifiers != 0) {
			pAppSetting->setHotkey(vKey, vModifiers, HOTKEY_ID_SWITCH_USER, &succ);
			if (succ == VARIANT_FALSE)
				throw int(0);
		}

		pAppSetting->Release();
	} catch (...) {
		AfxMessageBox("Set Hotkey failed!");
	}
}

void CDlgOptions::OnRestore() {

}


void CDlgOptions::OnApply() {
	setHotKey();
}
void CDlgOptions::OnShow() {
}

BEGIN_MESSAGE_MAP(CDlgOptions, CDialog)
END_MESSAGE_MAP()


// CDlgOptions 消息处理程序

BOOL CDlgOptions::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
}
