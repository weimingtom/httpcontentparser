// FirstPwdDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "FirstPwdDlg.h"
#include ".\firstpwddlg.h"


// CFirstPwdDlg 对话框

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


// CFirstPwdDlg 消息处理程序

void CFirstPwdDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
