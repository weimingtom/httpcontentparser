// DlgRegister.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgRegister.h"
#include ".\dlgregister.h"


// CDlgRegister �Ի���

IMPLEMENT_DYNAMIC(CDlgRegister, CPopupDialog)
CDlgRegister::CDlgRegister(CWnd* pParent /*=NULL*/)
	: CPopupDialog(CDlgRegister::IDD, pParent) {
}

CDlgRegister::~CDlgRegister() {
}

void CDlgRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgRegister, CPopupDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgRegister ��Ϣ�������

void CDlgRegister::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}

void CDlgRegister::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}
