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


void CDlgHelp::OnRestore() {

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
	ON_LBN_KILLFOCUS(IDC_LIST1, OnLbnKillfocusList1)
	ON_LBN_SELCANCEL(IDC_LIST1, OnLbnSelcancelList1)
	ON_LBN_SELCHANGE(IDC_LIST1, OnLbnSelchangeList1)
END_MESSAGE_MAP()


// CDlgHelp ��Ϣ�������

BOOL CDlgHelp::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgHelp::OnLbnKillfocusList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CDlgHelp::OnLbnSelcancelList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CDlgHelp::OnLbnSelchangeList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
