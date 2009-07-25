// PopTipRegDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include ".\services.h"
#include "PopTipRegDlg.h"
#include ".\poptipregdlg.h"
#include <assert.h>

// CPopTipRegDlg 对话框
#define SHOW_TIMES		5

INT_PTR CPopTipRegDlg::show_count_ = -1;

IMPLEMENT_DYNAMIC(CPopTipRegDlg, CDialog)
CPopTipRegDlg::CPopTipRegDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPopTipRegDlg::IDD, pParent)
{
	call_should_show_before_init = false;
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
	if (!Services::registered()) {
		// 如果没有注册
		show_count_++;
		call_should_show_before_init = true;
		return ((show_count_ % SHOW_TIMES) == 0);
	} else {
		// 如果已经注册，永远都不应该弹出
		return false;
	}
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
	assert (call_should_show_before_init);
	CDialog::OnInitDialog();

	return TRUE; 
}
