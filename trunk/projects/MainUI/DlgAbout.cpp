// DlgAbout.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgAbout.h"
#include ".\dlgabout.h"
#include ".\Dlgregister.h"
#include ".\globalvariable.h"
#include ".\services.h"
#include <com\comutility.h>
#include <logger\logger.h>

// CDlgAbout �Ի���

IMPLEMENT_DYNAMIC(CDlgAbout, CDialog)
CDlgAbout::CDlgAbout(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgAbout::IDD, pParent)
	, m_strRegisterInfo(_T(""))
{
	auther_name_ = ANOTHER_ABOUT;
}

CDlgAbout::~CDlgAbout()
{
}


int CDlgAbout::OnApply() {
	return 0;
}

std::string CDlgAbout::getHelpLink() const {
	return "";
}

void CDlgAbout::OnShow() {
	// ��ȡ��Ϣ
	if (Services::registered()) {
		m_strRegisterInfo.LoadString(IDS_REGISTER_DONE);
		m_btnRegistered.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STA_REGISTER_INFO)->SetWindowText(m_strRegisterInfo);
		UpdateData(FALSE);
	} else {
		m_btnRegistered.ShowWindow(SW_SHOW);
		LONG days =Services::trialLeftDays();
		if (days >= 0) {
			CString str;
			str.LoadString(IDS_REGISTER_TRIAL_DAYS);
			m_strRegisterInfo.Format(str, days);
		} else {
			m_strRegisterInfo.LoadString(IDS_REGISTER_OVERTIME);
		}
	}

	UpdateData(FALSE);
}

void CDlgAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STA_ABOUT, m_staAbout);
	DDX_Control(pDX, IDC_WEBSITE_URL, m_sWebURL);
	DDX_Control(pDX, IDC_OUR_EMAIL, m_sEmail);
	DDX_Control(pDX, IDC_OUR_MAILLIST, m_sMailList);
	DDX_Text(pDX, IDC_STA_REGISTER_INFO, m_strRegisterInfo);
	DDX_Control(pDX, IDC_REGISTER, m_btnRegistered);
}


BEGIN_MESSAGE_MAP(CDlgAbout, CDialog)
	ON_BN_CLICKED(IDC_REGISTER, OnBnClickedRegister)
	ON_WM_HELPINFO()
END_MESSAGE_MAP()


// CDlgAbout ��Ϣ�������

void CDlgAbout::OnBnClickedRegister() {
	CDlgRegister dlg;
	dlg.DoModal();

	// ���ע��ɹ���ˢ��״̬
	OnShow();
}

BOOL CDlgAbout::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	CString str;
	str.LoadString(IDS_OUR_MAIL_URL);
	m_sEmail.SetURL(str);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

BOOL CDlgAbout::OnHelpInfo(HELPINFO* pHelpInfo)
{
	return TRUE;
}
