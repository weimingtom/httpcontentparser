// FirstPwdDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "FirstPwdDlg.h"
#include ".\firstpwddlg.h"


// CFirstPwdDlg �Ի���

IMPLEMENT_DYNAMIC(CFirstPwdDlg, CDialog)
CFirstPwdDlg::CFirstPwdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFirstPwdDlg::IDD, pParent)
	, m_strNewPwd(_T(""))
	, m_strPwdConfirm(_T(""))
{
}

CFirstPwdDlg::~CFirstPwdDlg()
{
}

void CFirstPwdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_NEW, m_strNewPwd);
	DDX_Text(pDX, IDC_EDT_RETRY, m_strPwdConfirm);
}


BEGIN_MESSAGE_MAP(CFirstPwdDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CFirstPwdDlg ��Ϣ�������

void CFirstPwdDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}
