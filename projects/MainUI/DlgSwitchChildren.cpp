// DlgSwitchChildren.cpp : implementation file
//

#include "stdafx.h"
#include "DlgSwitchChildren.h"
#include "resource.h"
#include "globalvariable.h"

// CDlgSwitchChildren dialog

IMPLEMENT_DYNAMIC(CDlgSwitchChildren, CDialog)

CDlgSwitchChildren::CDlgSwitchChildren(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSwitchChildren::IDD, pParent)
	, m_bDontAskmeAgain(FALSE)
{

}

CDlgSwitchChildren::~CDlgSwitchChildren()
{
}

void CDlgSwitchChildren::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHK_DONT_ASKME_AGAIN, m_bDontAskmeAgain);
}


BEGIN_MESSAGE_MAP(CDlgSwitchChildren, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgSwitchChildren::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgSwitchChildren message handlers

void CDlgSwitchChildren::OnBnClickedOk()
{
	OnOK();
}
