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
		int result =  CDialog::DoModal();
		m_bOpened_ = false;
		return result;
	} else {
		SetForegroundWindow();
		return IDCANCEL;
	}
}
