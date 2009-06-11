// DlgReboot.cpp : 实现文件
//

#include "stdafx.h"
#include "Uninstaller.h"
#include "DlgReboot.h"
#include ".\dlgreboot.h"


// CDlgReboot 对话框

IMPLEMENT_DYNAMIC(CDlgReboot, CDialog)
CDlgReboot::CDlgReboot(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgReboot::IDD, pParent)
	, m_bRestart(0)
{
	m_bkColor = RGB(255, 255, 255);
	m_bkBrush = CreateSolidBrush(m_bkColor);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CDlgReboot::~CDlgReboot()
{
}

void CDlgReboot::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgReboot, CDialog)
	ON_BN_CLICKED(IDC_BTN_FINISH, OnBnClickedFinish)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDlgReboot 消息处理程序

void CDlgReboot::OnBnClickedFinish()
{
	UpdateData(TRUE);
	if (m_bRestart == 0) {
		ExitWindowsEx(EWX_REBOOT , 0);
	}

	EndDialog(IDOK);
}

HBRUSH CDlgReboot::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_RADIO_RESTART || pWnd->GetDlgCtrlID() == IDC_RAD_LATER) {
		pDC->SetBkColor(m_bkColor);
		return m_bkBrush;
	} 
	return hbr;
}

BOOL CDlgReboot::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	return TRUE;  
}

