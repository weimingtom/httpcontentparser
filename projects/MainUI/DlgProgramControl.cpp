// DlgProgramControl.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgProgramControl.h"
#include ".\dlgprogramcontrol.h"


// CDlgProgramControl 对话框

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
	DDX_Control(pDX, IDC_LIST_PROGRAM, m_list);
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


// CDlgProgramControl 消息处理程序

void CDlgProgramControl::OnBnClickedBtnAdd()
{

	TCHAR * FILE_FILTER = _T("*Exectuable files(*.exe); *.exe|All Files (*.*)|*.*||");

	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, FILE_FILTER);
	if (IDOK == dlg.DoModal()) {
	}
}

void CDlgProgramControl::OnBnClickedBtnSet()
{
}
