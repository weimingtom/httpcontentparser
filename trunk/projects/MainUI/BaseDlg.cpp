#include "StdAfx.h"
#include ".\basedlg.h"

CBaseDlg::CBaseDlg(UINT uTemplate, CWnd *pParent) : CDialog(uTemplate, pParent)
{
}

CBaseDlg::~CBaseDlg(void)
{
}


int  CBaseDlg::BeforeChange() {
	if (Modified() == true) {
		int result = AfxMessageBox("Setting have been changed, Would you like apply the change?", MB_YESNO);
		if (result == IDOK) {
			OnApply();
			return 1;
		} else {
			OnRestore();
			return 0;
		}
	} else {
		return 1;
	}
}