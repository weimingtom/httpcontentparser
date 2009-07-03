// Lev1DlgTools.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "Lev1DlgTools.h"
#include ".\lev1dlgtools.h"


// CLev1DlgTools 对话框

IMPLEMENT_DYNAMIC(CLev1DlgTools, CDialog)
CLev1DlgTools::CLev1DlgTools(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CLev1DlgTools::IDD, pParent)
{
}

CLev1DlgTools::~CLev1DlgTools()
{
}

std::string CLev1DlgTools::getHelpLink() const {
	return "";
}

void CLev1DlgTools::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


void CLev1DlgTools::restoreSetting() {

}

int CLev1DlgTools::OnApply() {
	return 0;
}

void CLev1DlgTools::OnShow() {
}

BEGIN_MESSAGE_MAP(CLev1DlgTools, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CLev1DlgTools 消息处理程序

HBRUSH CLev1DlgTools::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return CBaseDlg::OnCtlColor(pDC, pWnd, nCtlColor);
}
