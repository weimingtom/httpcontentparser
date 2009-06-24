// FirstPwdDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "FirstPwdDlg.h"
#include ".\firstpwddlg.h"
#include ".\services.h"

#define PASSWORD_MIN_LENGTH 8


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
	UpdateData(TRUE);
	CString tip, caption;
	caption.LoadString(IDS_APP_NAME);
	if (m_strNewPwd != m_strPwdConfirm) {
		tip.LoadString(IDS_PWD_NOT_SAME_WITH_CONFIRM);
		::MessageBox(NULL, tip, caption,MB_OK | MB_ICONEXCLAMATION);
	} else if (m_strNewPwd.GetLength() < PASSWORD_MIN_LENGTH) {
		// ���볤�Ȳ��ܶ���8λ
		tip.LoadString(IDS_PWD_NEW_PWD_TOO_SHORT);
		::MessageBox(NULL, tip, caption,MB_OK | MB_ICONEXCLAMATION);
	} else {
		// �������벢�رնԻ���
		tip.LoadString(IDS_PWD_SET_SUCCESS);
		::MessageBox(NULL, tip, caption,MB_OK | MB_ICONEXCLAMATION);
		Services::setPwdForFirstTime(m_strNewPwd);
		OnOK();
	}
}
