#include "stdafx.h"
#include "lockutility.h"
#include <logger\logger.h>
#include <logger\loggerlevel.h>
#include <sstream>
#include <winlockdll.h>

namespace {
HHOOK hhkLowLevelKybd = NULL;
};

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
	__AUTO_FUNCTION_SCOPE_TRACE__;

	BOOL fEatKeystroke = FALSE;
	if (nCode == HC_ACTION) {
		switch (wParam) {
		 case WM_KEYDOWN:
		 case WM_SYSKEYDOWN:
		 case WM_KEYUP:
		 case WM_SYSKEYUP: 
			 PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT) lParam;

			 fEatKeystroke = 
				 ((p->vkCode == VK_TAB) && ((p->flags & LLKHF_ALTDOWN) != 0)) ||

				 ((p->vkCode == VK_ESCAPE) && ((p->flags & LLKHF_ALTDOWN) != 0)) ||

				 ((p->vkCode == VK_ESCAPE) && ((GetKeyState(VK_CONTROL) & 0x8000) != 0)) ||
				 ((p->vkCode == VK_LWIN) || (p->vkCode == VK_RWIN));
			 break;
		}
	}

	return(fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam, 	lParam));
}


// 锁定电脑
// 主要指禁用 ATL+CTRL+DEL, ATL+ESC, SWITCH, WIN...
void LockScreen() {
	__AUTO_FUNCTION_SCOPE_TRACE__;

	hhkLowLevelKybd  = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, AfxGetInstanceHandle(), 0);

	CtrlAltDel_Enable_Disable(FALSE);
	Taskbar_Show_Hide(FALSE); 
}

void UnlockScreen() {
	__AUTO_FUNCTION_SCOPE_TRACE__;

	assert (NULL != hhkLowLevelKybd);
	UnhookWindowsHookEx(hhkLowLevelKybd);
	hhkLowLevelKybd = NULL;

	CtrlAltDel_Enable_Disable(TRUE);
	Taskbar_Show_Hide(TRUE); 
}
