// PopTipTrayendDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "PopTipTrayendDlg.h"
#include ".\poptiptrayenddlg.h"


// CPopTipTrayendDlg �Ի���

IMPLEMENT_DYNAMIC(CPopTipTrayendDlg, CDialog)
CPopTipTrayendDlg::CPopTipTrayendDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPopTipTrayendDlg::IDD, pParent)
{
}

CPopTipTrayendDlg::~CPopTipTrayendDlg()
{
}

void CPopTipTrayendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPopTipTrayendDlg, CDialog)
	ON_BN_CLICKED(ID_BTN_BESN, OnBnClickedBtnBesn)
	ON_BN_CLICKED(ID_BTN_BUYNOW, OnBnClickedBtnBuynow)
END_MESSAGE_MAP()


// CPopTipTrayendDlg ��Ϣ�������

void CPopTipTrayendDlg::OnBnClickedBtnBesn()
{
	EndDialog(ID_BTN_BESN);
}

void CPopTipTrayendDlg::OnBnClickedBtnBuynow()
{
	EndDialog(ID_BTN_BUYNOW);
}
