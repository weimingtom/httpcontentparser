// DlgRegister.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgRegister.h"
#include ".\dlgregister.h"
#include ".\services.h"


// CDlgRegister 对话框

IMPLEMENT_DYNAMIC(CDlgRegister, CPopupDialog)
CDlgRegister::CDlgRegister(CWnd* pParent /*=NULL*/)
: CPopupDialog(CDlgRegister::IDD, pParent) , m_strSN(_T(""))
{
}

CDlgRegister::~CDlgRegister() {
}

void CDlgRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_REGSN, m_strSN);
}


BEGIN_MESSAGE_MAP(CDlgRegister, CPopupDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgRegister 消息处理程序

void CDlgRegister::OnBnClickedOk()
{
	UpdateData(TRUE);
	CString tipMessage, tipTitle;
	tipTitle.LoadString(IDS_APP_NAME);
	if (true == Services::registerSN(std::string((LPCTSTR)m_strSN))) {
		tipMessage.LoadString(IDS_REGISTER_RIGHT);
	} else {
		tipMessage.LoadString(IDS_REGISTER_WRONGSN);
	}
	::MessageBox(NULL, tipMessage, tipTitle, MB_OK);
	OnOK();
}

void CDlgRegister::OnBnClickedCancel()
{
	OnCancel();
}
