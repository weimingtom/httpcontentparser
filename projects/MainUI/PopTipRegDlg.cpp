// PopTipRegDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "PopTipRegDlg.h"
#include ".\poptipregdlg.h"


// CPopTipRegDlg 对话框
#define SHOW_TIMES		5

int CPopTipRegDlg::show_count_ = -1;

IMPLEMENT_DYNAMIC(CPopTipRegDlg, CDialog)
CPopTipRegDlg::CPopTipRegDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPopTipRegDlg::IDD, pParent)
{
}

CPopTipRegDlg::~CPopTipRegDlg()
{
}

void CPopTipRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPopTipRegDlg, CDialog)
	ON_BN_CLICKED(ID_BTN_BESN, OnBnClickedBtnBesn)
	ON_BN_CLICKED(ID_BTN_BUYNOW, OnBnClickedBtnBuynow)
END_MESSAGE_MAP()


bool CPopTipRegDlg::shouldShow() {
	show_count_++;
	return ((show_count_ % SHOW_TIMES) == 0);
}
// CPopTipRegDlg 消息处理程序

void CPopTipRegDlg::OnBnClickedBtnBesn()
{
	EndDialog(ID_BTN_BESN);
}

void CPopTipRegDlg::OnBnClickedBtnBuynow()
{
	EndDialog(ID_BTN_BUYNOW);
}

BOOL CPopTipRegDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE; 
}
