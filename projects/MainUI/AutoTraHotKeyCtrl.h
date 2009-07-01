#pragma once


// CAutoTraHotKeyCtrl

class CAutoTraHotKeyCtrl : public CHotKeyCtrl
{
	DECLARE_DYNAMIC(CAutoTraHotKeyCtrl)

public:
	CAutoTraHotKeyCtrl();
	virtual ~CAutoTraHotKeyCtrl();

public:
	void SetHotKey(WORD wVirtualKeyCode, WORD wModifiers);
	void GetHotKey(WORD &wVirtualKeyCode, WORD &wModifier);

private:
	DWORD GetHotKey();
protected:
	DECLARE_MESSAGE_MAP()

private:
	WORD  getModifierKey(WORD kModify_mfc);
	WORD  getModifierKeyMFC(WORD kModify);
};


