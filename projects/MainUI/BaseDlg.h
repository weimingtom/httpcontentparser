#pragma once
#include "afxwin.h"

class CBaseDlg : public CDialog {
public:
	CBaseDlg(UINT uTemplate, CWnd *pParent);
	~CBaseDlg(void);

	virtual void OnApply() = 0;
	virtual void OnShow() = 0;
	void OnOK() {}
private:
	CBaseDlg() {}
};
