#pragma once
#include "afxwin.h"

class CBaseDlg : public CDialog {
public:
	CBaseDlg(UINT uTemplate, CWnd *pParent);
	~CBaseDlg(void);

	virtual void OnApply() = 0;
private:
	CBaseDlg() {}
};
