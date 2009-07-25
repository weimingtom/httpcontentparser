// AutoTraHotKeyCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "mainui.h"
#include "AutoTraHotKeyCtrl.h"


// CAutoTraHotKeyCtrl
IMPLEMENT_DYNAMIC(CAutoTraHotKeyCtrl, CHotKeyCtrl)
CAutoTraHotKeyCtrl::CAutoTraHotKeyCtrl()
{
}

CAutoTraHotKeyCtrl::~CAutoTraHotKeyCtrl()
{
}


BEGIN_MESSAGE_MAP(CAutoTraHotKeyCtrl, CHotKeyCtrl)
END_MESSAGE_MAP()

void CAutoTraHotKeyCtrl::SetHotKey(WORD wVirtualKeyCode, WORD wModifiers) {
	WORD wNewMod = getModifierKey(wModifiers);
	CHotKeyCtrl::SetHotKey(wVirtualKeyCode, wNewMod);
}
void CAutoTraHotKeyCtrl::GetHotKey(WORD &wVirtualKeyCode, WORD &wModifier) {
	WORD wNewMod = 0;
	CHotKeyCtrl::GetHotKey(wVirtualKeyCode, wNewMod);
	wModifier = getModifierKeyMFC(wNewMod);
}


// CAutoTraHotKeyCtrl 消息处理程序
// 注意API的HOTKEY与MFC定义的值不相同，真是晕菜
WORD  CAutoTraHotKeyCtrl::getModifierKey(WORD kModify_mfc) {
	WORD vModifiers  = 0;
	if (kModify_mfc & HOTKEYF_SHIFT)
		vModifiers |= MOD_SHIFT;
	if (kModify_mfc & HOTKEYF_CONTROL)
		vModifiers |= MOD_CONTROL;
	if (kModify_mfc & HOTKEYF_ALT)
		vModifiers |= MOD_ALT;

	return vModifiers;
}

WORD  CAutoTraHotKeyCtrl::getModifierKeyMFC(WORD kModify) {
	WORD vModifiers_mfc  = 0;
	if (kModify & MOD_SHIFT)
		vModifiers_mfc |= HOTKEYF_SHIFT;
	if (kModify & MOD_CONTROL)
		vModifiers_mfc |= HOTKEYF_CONTROL;
	if (kModify & MOD_ALT)
		vModifiers_mfc |= HOTKEYF_ALT;

	return vModifiers_mfc; 
}

