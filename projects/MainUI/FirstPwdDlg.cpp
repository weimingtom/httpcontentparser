// FirstPwdDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "FirstPwdDlg.h"
#include ".\firstpwddlg.h"
#include ".\services.h"


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
		// 如果设置失败，应该重新设置
		if (false == Services::setPwdForFirstTime(m_strNewPwd)) {
			resetField();
			tip.LoadString(IDS_PWD_FAILED_ON_CHANGE);
			::MessageBox(NULL, tip, caption,MB_OK | MB_ICONEXCLAMATION);
			// 同时切换到父模式
			Services::switchParentModel(m_strNewPwd);
			return ;
		} else {
			tip.LoadString(IDS_PWD_SET_SUCCESS);
			::MessageBox(NULL, tip, caption,MB_OK | MB_ICONEXCLAMATION);
			OnOK();
		}
	}
}
