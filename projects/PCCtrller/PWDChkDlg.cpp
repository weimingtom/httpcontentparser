// PWDChkDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include ".\pcctrllerapp.h"
#include "PWDChkDlg.h"
#include ".\pwdchkdlg.h"
#include "COMutility.h"

// CPWDChkDlg �Ի���
#define  ID_TIMER_1		1
#define  TIME_SPAN_SECONDS    1000

IMPLEMENT_DYNAMIC(CPWDChkDlg, CDialog)
CPWDChkDlg::CPWDChkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPWDChkDlg::IDD, pParent)
	, m_strPwd(_T(""))
{
}

CPWDChkDlg::~CPWDChkDlg()
{
}

void CPWDChkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
}


BEGIN_MESSAGE_MAP(CPWDChkDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_OK, OnBnClickedBtnOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CPWDChkDlg ��Ϣ�������

BOOL CPWDChkDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (theApp.getAppModel() == EYECARE_MODEL) {
		SetWindowText("Eyelight Care");
		SetTimer(ID_TIMER_1, TIME_SPAN_SECONDS, NULL);
	} else {
		SetWindowText("Lock Computer");
	}

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

BOOL CPWDChkDlg::checkPwd() {
	UpdateData(TRUE);
	if (theApp.getAppModel() != EYECARE_MODEL) {
		return ValidatePassword(m_strPwd);
	} else {
		return TRYEndEyecare(m_strPwd);
	}
}
void CPWDChkDlg::OnBnClickedBtnOk()
{
	if (TRUE == checkPwd()) {
		EndDialog(IDOK);
	} else {
		::MessageBox(GetSafeHwnd(), "Wrong Password!", "Error", MB_OK | MB_ICONERROR);
	}
}

// ���������Eyecare model��
// ��ʱ������������ ������ʾʣ��ʱ��
void CPWDChkDlg::OnTimer(UINT nIDEvent)
{
	const int buffer_size = 256;
	char szBuffer[buffer_size+1];
	_tcscpy(szBuffer, "Login System");

	// ��������ڸ�ģʽ��
	if (IsRuninParentModel()) {
		// Ϊʲô������Ƿ��ڸ�ģʽ�£���������˳��أ�
		EndDialog(IDOK);
	} else {
		// ��ȡʱ�䲢���ø�ʽ
		LONG seconds = GetEyecareLeftSeconds();
		if (seconds > 60) {
			_sntprintf(szBuffer, buffer_size, "Rest time : %d min", (int)(seconds/60));
		} else if (seconds > 0){
			_sntprintf(szBuffer, buffer_size, "Rest time : %d second", seconds);
		} else {
			EndDialog(IDOK);
		}
		SetWindowText(szBuffer);
	}

	CDialog::OnTimer(nIDEvent);
}

