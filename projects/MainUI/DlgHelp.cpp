// HelpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgHelp.h"
#include ".\dlghelp.h"


// CHelpDlg �Ի���

IMPLEMENT_DYNAMIC(CDlgHelp, CDialog)
CDlgHelp::CDlgHelp(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgHelp::IDD, pParent)
{
}

CDlgHelp::~CDlgHelp()
{
}

void CDlgHelp::OnApply() {
}

void CDlgHelp::OnShow() {
}

void CDlgHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgHelp, CDialog)
END_MESSAGE_MAP()


// CDlgHelp ��Ϣ�������

BOOL CDlgHelp::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
