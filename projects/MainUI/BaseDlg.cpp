#include "StdAfx.h"
#include ".\basedlg.h"
#include ".\resource.h"
#include <app_constants.h>

CBaseDlg::CBaseDlg(UINT uTemplate, CWnd *pParent) : CDialog(uTemplate, pParent) {
	auther_name_ = ANOTHER_GENERIC;
}

CBaseDlg::~CBaseDlg(void)
{
}
void CBaseDlg::SetModify(const bool changed) {
	changed_ = changed;
	AfxGetMainWnd()->GetDlgItem(IDC_MAIN_OK)->EnableWindow(changed);
	AfxGetMainWnd()->GetDlgItem(IDC_MAIN_APPLY)->EnableWindow(changed);
}

// 在切换窗口之后
INT_PTR  CBaseDlg::AfterChange() {
	AfxGetMainWnd()->GetDlgItem(IDC_MAIN_OK)->EnableWindow(FALSE);
	AfxGetMainWnd()->GetDlgItem(IDC_MAIN_APPLY)->EnableWindow(FALSE);
	return 0;
}

INT_PTR CBaseDlg::Apply() {
	return OnApply();
}
// 回复设置
INT_PTR CBaseDlg::Restore() {
	try {
		SetModify(false);
		restoreSetting();
	} catch (...) {
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONEXCLAMATION);
	}
	return 0;
}

// 在改变窗口之前
// 
INT_PTR  CBaseDlg::BeforeChange() {
	if (Modified() == true) {
		CString tips, caption;
		tips.LoadString(IDS_APP_NAME);
		caption.LoadString(IDS_TIP_SETTING_CHANGED);
		INT_PTR result = ::MessageBox(NULL, caption, tips, MB_YESNO | MB_ICONEXCLAMATION);
		if (result == IDYES) {
			Apply();
			SetModify(false);
			return 1;
		} else {
			SetModify(false);
			Restore();
			return 0;
		}
	} else {
		return 1;
	}
}


BEGIN_MESSAGE_MAP(CBaseDlg, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

HBRUSH CBaseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	return hbr;
}
