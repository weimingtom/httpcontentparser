// DlgProgramControl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgProgramControl.h"
#include ".\dlgprogramcontrol.h"


// CDlgProgramControl �Ի���

IMPLEMENT_DYNAMIC(CDlgProgramControl, CDialog)
CDlgProgramControl::CDlgProgramControl(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgProgramControl::IDD, pParent)
{
}

CDlgProgramControl::~CDlgProgramControl()
{
}

void CDlgProgramControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

int CDlgProgramControl::OnApply() {
	return -1;
}
void CDlgProgramControl::OnShow() {
}
void CDlgProgramControl::restoreSetting() {
}


BEGIN_MESSAGE_MAP(CDlgProgramControl, CDialog)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_SET, OnBnClickedBtnSet)
END_MESSAGE_MAP()


// CDlgProgramControl ��Ϣ�������

void CDlgProgramControl::OnBnClickedBtnAdd()
{
}

void CDlgProgramControl::OnBnClickedBtnSet()
{
}
