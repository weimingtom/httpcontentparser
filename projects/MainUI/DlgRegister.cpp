// DlgRegister.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgRegister.h"
#include ".\dlgregister.h"


// CDlgRegister 对话框

IMPLEMENT_DYNAMIC(CDlgRegister, CDialog)
CDlgRegister::CDlgRegister(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRegister::IDD, pParent) {
}

CDlgRegister::~CDlgRegister() {
}

void CDlgRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgRegister, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgRegister 消息处理程序

void CDlgRegister::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CDlgRegister::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
