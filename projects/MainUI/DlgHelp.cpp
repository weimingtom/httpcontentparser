// HelpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgHelp.h"
#include ".\dlghelp.h"


// CHelpDlg 对话框

IMPLEMENT_DYNAMIC(CDlgHelp, CDialog)
CDlgHelp::CDlgHelp(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgHelp::IDD, pParent)
{
}

CDlgHelp::~CDlgHelp()
{
}

std::string CDlgHelp::getHelpLink() const {
	return "";
}


void CDlgHelp::restoreSetting() {
}

INT_PTR CDlgHelp::OnApply() {
	return 0;
}

void CDlgHelp::OnShow() {
}

void CDlgHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgHelp, CDialog)
	ON_LBN_KILLFOCUS(IDC_LIST1, OnLbnKillfocusList1)
	ON_LBN_SELCANCEL(IDC_LIST1, OnLbnSelcancelList1)
	ON_LBN_SELCHANGE(IDC_LIST1, OnLbnSelchangeList1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDlgHelp 消息处理程序

BOOL CDlgHelp::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgHelp::OnLbnKillfocusList1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDlgHelp::OnLbnSelcancelList1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDlgHelp::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
}

HBRUSH CDlgHelp::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return CBaseDlg::OnCtlColor(pDC, pWnd, nCtlColor);
}
