// PopTipRegDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include ".\services.h"
#include "PopTipRegDlg.h"
#include ".\poptipregdlg.h"
#include <assert.h>

// CPopTipRegDlg �Ի���
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
		// ���û��ע��
		show_count_++;
		call_should_show_before_init = true;
		return ((show_count_ % SHOW_TIMES) == 0);
	} else {
		// ����Ѿ�ע�ᣬ��Զ����Ӧ�õ���
		return false;
	}
}
// CPopTipRegDlg ��Ϣ�������

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
