// DlgScreenSaver.cpp : 实现文件
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\DlgScreenSaver.h"
#include ".\globalvariable.h"
#include ".\dlgscreensaver.h"
#include <sysutility.h>
#include <typeconvert.h>

// CDlgScreenSaver 对话框

IMPLEMENT_DYNAMIC(CDlgScreenSaver, CDialog)
CDlgScreenSaver::CDlgScreenSaver(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CDlgScreenSaver::IDD, pParent)
	, m_bEnableScreensave(FALSE)
	, m_bEnableAutoclean(FALSE)
	, m_strAutoCleanHours(_T(""))
	, m_strTimespanMins(_T(""))
{
}

CDlgScreenSaver::~CDlgScreenSaver()
{
}

void CDlgScreenSaver::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STA_FUNCTION, m_staFunction);
	DDX_Control(pDX, IDC_STA_TIMESPAN, m_staTimespan);
	DDX_Control(pDX, IDC_STA_AUTOCLEAR, m_staAutoClear);
	DDX_Control(pDX, IDC_SLIDER_SAVE_TIMESPAN, m_sliderSaveTimespan);
	DDX_Control(pDX, IDC_SLIDER_CLEAN_TIMESPAN, m_sliderAutoclearTimespan);
	DDX_Check(pDX, IDC_CHK_SCREENSAVE, m_bEnableScreensave);
	DDX_Check(pDX, IDC_CHK_AUTOCLEAN, m_bEnableAutoclean);
	DDX_Text(pDX, IDC_STA_SCREENSAVE_AUTOCLEN, m_strAutoCleanHours);
	DDX_Text(pDX, IDC_STA_SCREENSAVE_TIMESPAN, m_strTimespanMins);
}

void CDlgScreenSaver::OnRestore() {
	initializeSetting();
}

void CDlgScreenSaver::OnApply() {
	try {
		IScreenSave * screensave = NULL;
		HRESULT hr = CoCreateInstance(CLSID_ScreenSave, NULL, CLSCTX_LOCAL_SERVER, IID_IScreenSave, (LPVOID*)&screensave);
		screensave->enableScreenSave(convert(m_bEnableScreensave));
		screensave->setTimeSpan(m_sliderSaveTimespan.GetPos() * 60);
		// screensave->enable
	} catch (_com_error& ) {
	}
}
void CDlgScreenSaver::OnShow() {
}
 

void CDlgScreenSaver::initializeSetting() {
	m_sliderAutoclearTimespan.SetRangeMax(g_configuration.getScreenSaveAutoClean()->getRangeMax()/ ( 60 * 60 * 24));
	m_sliderAutoclearTimespan.SetRangeMin(g_configuration.getScreenSaveAutoClean()->getRangeMin()/ ( 60 * 60 * 24));
	m_sliderAutoclearTimespan.SetPos(g_configuration.getScreenSaveAutoClean()->getTimespan()/ (60 * 60 * 24));

	m_bEnableScreensave = g_configuration.getScreenSave()->isEnabled();
	m_bEnableAutoclean = g_configuration.getScreenSaveAutoClean()->isEnable();

	// 设置自动存储
	m_sliderSaveTimespan.SetRange(1, 120);
	m_sliderSaveTimespan.SetTicFreq(10);
	int pos = g_configuration.getScreenSave()->getTimeSpan() / 60;
	m_sliderSaveTimespan.SetPos(pos);

	// 设置自动清理
	m_sliderAutoclearTimespan.SetRange(g_configuration.getScreenSaveAutoClean()->getRangeMin(),
		g_configuration.getScreenSaveAutoClean()->getRangeMax());
	m_sliderAutoclearTimespan.SetTicFreq(1);
	m_sliderAutoclearTimespan.SetPos(g_configuration.getScreenSaveAutoClean()->getTimespan());

	setAutoCleanTips();
	setTimespanTips();
}


void CDlgScreenSaver::enableAutoSave() {
	m_sliderSaveTimespan.EnableWindow(m_bEnableScreensave);
}
void CDlgScreenSaver::enableAutoclean() {
	m_sliderAutoclearTimespan.EnableWindow(m_bEnableAutoclean);
}


void CDlgScreenSaver::setAutoCleanTips() {
	m_strAutoCleanHours.Format("%d days", m_sliderAutoclearTimespan.GetPos());
	UpdateData(FALSE);
}

void CDlgScreenSaver::setTimespanTips() {
	m_strTimespanMins.Format("%d Mins", m_sliderSaveTimespan.GetPos());
	UpdateData(FALSE);
}

BEGIN_MESSAGE_MAP(CDlgScreenSaver, CDialog)
	ON_BN_CLICKED(IDC_CHK_SCREENSAVE, OnBnClickedChkScreensave)
	ON_BN_CLICKED(IDC_CHK_AUTOCLEAN, OnBnClickedChkAutoclean)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBnClickedBtnClear)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CDlgScreenSaver 消息处理程序

BOOL CDlgScreenSaver::OnInitDialog() {
	CBaseDlg::OnInitDialog();
	
	initializeSetting();

	enableAutoSave();
	enableAutoclean();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgScreenSaver::OnBnClickedChkScreensave() {
	UpdateData(TRUE);
	enableAutoSave();
}

void CDlgScreenSaver::OnBnClickedChkAutoclean() {
	UpdateData(TRUE);
	enableAutoclean();
}

void CDlgScreenSaver::OnBnClickedBtnClear() {
	ClearScreen((HMODULE)AfxGetInstanceHandle());
	CString str;
	str.LoadString(IDS_SCREEN_RECORD_CLEAR_BUTTON);
	AfxMessageBox(str);
}

void CDlgScreenSaver::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	if (pScrollBar->GetSafeHwnd() == m_sliderSaveTimespan.GetSafeHwnd()) {
		setTimespanTips();
	} else if (pScrollBar->GetSafeHwnd() == m_sliderAutoclearTimespan.GetSafeHwnd()) {
		setAutoCleanTips();
	}
	
	CBaseDlg::OnHScroll(nSBCode, nPos, pScrollBar);	
}
