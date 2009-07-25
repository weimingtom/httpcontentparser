// FirstPwdDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "FirstPwdDlg.h"
#include ".\firstpwddlg.h"
#include ".\services.h"


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

void CFirstPwdDlg::resetField() {
	m_strNewPwd = "";
	m_strPwdConfirm = "";
	UpdateData(FALSE);
}
void CFirstPwdDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	CString tip, caption;
	caption.LoadString(IDS_APP_NAME);
	INT_PTR msgId = Services::validatePwd(m_strNewPwd, m_strPwdConfirm);
	if (0 != msgId) {
		tip.LoadString(msgId);
		::MessageBox(NULL, tip, caption,MB_OK | MB_ICONEXCLAMATION);
		resetField();
	} else {
		// �������ʧ�ܣ�Ӧ����������
		if (false == Services::setPwdForFirstTime(m_strNewPwd)) {
			resetField();
			tip.LoadString(IDS_PWD_FAILED_ON_CHANGE);
			::MessageBox(NULL, tip, caption,MB_OK | MB_ICONEXCLAMATION);
			// ͬʱ�л�����ģʽ
			Services::switchParentModel(m_strNewPwd);
			return ;
		} else {
			tip.LoadString(IDS_PWD_SET_SUCCESS);
			::MessageBox(NULL, tip, caption,MB_OK | MB_ICONEXCLAMATION);
			OnOK();
		}
	}
}
