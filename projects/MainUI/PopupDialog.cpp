#include "StdAfx.h"
#include ".\popupdialog.h"

CPopupDialog::CPopupDialog(int id, CWnd* pParent) 
	: CDialog(id, pParent)
{
	m_bOpened_ = false;
}

CPopupDialog::~CPopupDialog(void)
{
}


INT_PTR CPopupDialog::DoModal()
{
	if (false == m_bOpened_) {
		m_bOpened_ = true;
		return CDialog::DoModal();
	} else {
		SetForegroundWindow();
		return IDCANCEL;
	}
}
BEGIN_MESSAGE_MAP(CPopupDialog, CDialog)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

void CPopupDialog::OnDestroy()
{
	CDialog::OnDestroy();

	m_bOpened_  = false;
}
