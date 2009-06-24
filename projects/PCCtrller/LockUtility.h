#ifndef _PCCTRLLER_LOCKUTILITY_H__
#define _PCCTRLLER_LOCKUTILITY_H__

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
void LockScreen();
void UnlockScreen();

#endif  // _PCCTRLLER_LOCKUTILITY_H__