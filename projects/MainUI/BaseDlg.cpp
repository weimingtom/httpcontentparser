#include "StdAfx.h"
#include ".\basedlg.h"
#include ".\resource.h"

CBaseDlg::CBaseDlg(UINT uTemplate, CWnd *pParent) : CDialog(uTemplate, pParent)
{
}

CBaseDlg::~CBaseDlg(void)
{
}
void CBaseDlg::SetModify(const bool changed) {
	changed_ = changed;
	GetParent()->GetDlgItem(IDC_MAIN_OK)->EnableWindow(changed);
	GetParent()->GetDlgItem(IDC_MAIN_APPLY)->EnableWindow(changed);
}

int  CBaseDlg::AfterChange() {
	GetParent()->GetDlgItem(IDC_MAIN_OK)->EnableWindow(FALSE);
	GetParent()->GetDlgItem(IDC_MAIN_APPLY)->EnableWindow(FALSE);
	return 0;
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