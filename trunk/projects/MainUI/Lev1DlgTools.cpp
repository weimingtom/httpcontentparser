// Lev1DlgTools.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "Lev1DlgTools.h"


// CLev1DlgTools 对话框

IMPLEMENT_DYNAMIC(CLev1DlgTools, CDialog)
CLev1DlgTools::CLev1DlgTools(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CLev1DlgTools::IDD, pParent)
{
}

CLev1DlgTools::~CLev1DlgTools()
{
}

void CLev1DlgTools::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


void CLev1DlgTools::OnRestore() {

}

void CLev1DlgTools::OnApply() {
}
void CLev1DlgTools::OnShow() {
}

BEGIN_MESSAGE_MAP(CLev1DlgTools, CDialog)
END_MESSAGE_MAP()


// CLev1DlgTools 消息处理程序
