#include "StdAfx.h"
#include ".\popupdialog.h"

CPopupDialog::CPopupDialog(INT_PTR id, CWnd* pParent) 
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
		INT_PTR result =  CDialog::DoModal();
		m_bOpened_ = false;
		return result;
	} else {
		SetForegroundWindow();
		return IDCANCEL;
	}
}
