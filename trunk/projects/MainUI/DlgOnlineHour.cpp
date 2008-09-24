// DlgOnlineHour.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\DlgOnlineHour.h"
#include ".\basedlg.h"
#include ".\dlgonlinehour.h"
#include ".\resource.h"
#include ".\globalvariable.h"


// CDlgOnlineHour �Ի���
IMPLEMENT_DYNAMIC(CDlgOnlineHour, CDialog)
CDlgOnlineHour::CDlgOnlineHour(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgOnlineHour::IDD, pParent)
	, m_bEnableTimeCheck(FALSE)
{
}

CDlgOnlineHour::~CDlgOnlineHour()
{
}

void CDlgOnlineHour::OnRestore() {

}

void CDlgOnlineHour::OnApply() {
}

void CDlgOnlineHour::OnShow() {
}

void CDlgOnlineHour::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_TIMECTRL, m_chkTimeCtrl);
	DDX_Check(pDX, IDC_CHK_TIMECTRL, m_bEnableTimeCheck);
}

void CDlgOnlineHour::initializeSetting() {
	m_bEnableTimeCheck = g_configuration.getOnlineSetting()->isEnabled();
	UpdateData(FALSE);

	// 
	g_configuration.getOnlineSetting()->enumBlockHour((Enumerator2<int, int>*)this);
}

int CDlgOnlineHour::Enum(const int day, const int hour) {
	cells.check(day, hour);
	return 0;
}

BEGIN_MESSAGE_MAP(CDlgOnlineHour, CDialog)
END_MESSAGE_MAP()


// CDlgOnlineHour ��Ϣ�������

BOOL CDlgOnlineHour::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	CRect rect;
	GetDlgItem(IDC_STA_CELLS)->GetWindowRect(rect);
	cells.Create(NULL, NULL, WS_CHILD, rect, this, IDC_WND_HELLO);
	cells.ShowWindow(SW_SHOW);

	initializeSetting();

	return TRUE;  // return TRUE unless you set the focus to a control
}

