// Lev1DlgRules.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "Lev1DlgRules.h"
#include ".\lev1dlgrules.h"


// CLev1DlgRules 对话框

IMPLEMENT_DYNAMIC(CLev1DlgRules, CDialog)
CLev1DlgRules::CLev1DlgRules(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CLev1DlgRules::IDD, pParent)
{
}

CLev1DlgRules::~CLev1DlgRules()
{
}

std::string CLev1DlgRules::getHelpLink() const {
	return "";
}


void CLev1DlgRules::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLev1DlgRules, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

void CLev1DlgRules::restoreSetting() {
}

INT_PTR CLev1DlgRules::OnApply() {
	return 0;
}

void CLev1DlgRules::OnShow() {
}

// CLev1DlgRules 消息处理程序

BOOL CLev1DlgRules::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	return TRUE; 
}

HBRUSH CLev1DlgRules::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return CBaseDlg::OnCtlColor(pDC, pWnd, nCtlColor);
}
