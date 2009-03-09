// DlgScreenSaver.cpp : 实现文件
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\DlgScreenshot.h"
#include ".\globalvariable.h"
#include ".\dlgscreenshot.h"
#include ".\DlgImageBrowser.h"
#include <apputility.h>
#include <typeconvert.h>

#define MAX_AUTO_CLEAR_SPAN	30
#define MIN_AUTO_CLEAR_SPAN	1

#define MAX_SCREEN_SNAPSHOT	120
#define MIN_SCREEN_SNAPSHOT	1

// CDlgScreenshot 对话框

IMPLEMENT_DYNAMIC(CDlgScreenshot, CDialog)
CDlgScreenshot::CDlgScreenshot(CWnd* pParent /*=NULL*/)
: CBaseDlg(CDlgScreenshot::IDD, pParent)
, m_bEnableScreensave(FALSE)
, m_bEnableAutoclean(FALSE)
, m_strAutoCleanHours(_T(""))
, m_strTimespanMins(_T(""))
{
}

CDlgScreenshot::~CDlgScreenshot()
{
}

void CDlgScreenshot::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STA_FUNCTION, m_staFunction);
	DDX_Control(pDX, IDC_STA_TIMESPAN, m_staTimespan);
	DDX_Control(pDX, IDC_STA_AUTOCLEAR, m_staAutoClear);
	DDX_Control(pDX, IDC_SLIDER_SAVE_TIMESPAN, m_sliderSaveTimespan);
	DDX_Control(pDX, IDC_SLIDER_CLEAN_TIMESPAN, m_sliderAutoclearTimespan);
	DDX_Check(pDX, IDC_CHK_SCREENSAVE, m_bEnableScreensave);
	DDX_Check(pDX, IDC_CHK_AUTOCLEAN, m_bEnableAutoclean);
}

int CDlgScreenshot::OnApply() {
	try {
		IScreenSave * screensave = NULL;
		HRESULT hr = CoCreateInstance(CLSID_ScreenSave, NULL, CLSCTX_LOCAL_SERVER, IID_IScreenSave, (LPVOID*)&screensave);
		if(FAILED(hr)) {
			AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
			return -1;
		}
		screensave->enableScreenSave(convert(m_bEnableScreensave));
		screensave->setTimeSpan(m_sliderSaveTimespan.GetPos() * 60);
		screensave->setAutoClearTimespan(m_sliderAutoclearTimespan.GetPos());
		screensave->put_AutocleanEnabled(convert(m_bEnableAutoclean));
		return 0;
	} catch (... ) {
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
		return -1;
	}
}
void CDlgScreenshot::OnShow() {
}


void CDlgScreenshot::restoreSetting() {
	try {
		IScreenSave * screensave = NULL;
		HRESULT hr = CoCreateInstance(CLSID_ScreenSave, NULL, CLSCTX_LOCAL_SERVER, IID_IScreenSave, (LPVOID*)&screensave);
		if(FAILED(hr)) {
			AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
			return;
		}

		VARIANT_BOOL enabled;
		screensave->isSettingEnabled(&enabled);
		m_bEnableScreensave = convert(enabled);

		screensave->isAutoClearEnabled(&enabled);
		m_bEnableAutoclean = convert(enabled);

		// 设置自动存储
		LONG secs;
		screensave->getTimeSpan(&secs);
		m_sliderSaveTimespan.SetRange(MIN_SCREEN_SNAPSHOT, MAX_SCREEN_SNAPSHOT);
		m_sliderSaveTimespan.SetTicFreq(10);
		int pos = secs / 60;
		m_sliderSaveTimespan.SetPos(pos);

		// 设置自动清理
		LONG days;
		screensave->getAutoClearSpan(&days);
		m_sliderAutoclearTimespan.SetRange(MIN_AUTO_CLEAR_SPAN, MAX_AUTO_CLEAR_SPAN);
		m_sliderAutoclearTimespan.SetTicFreq(1);
		m_sliderAutoclearTimespan.SetPos(days);

		screensave->isAutoClearEnabled(&enabled);
		CheckDlgButton(IDC_CHK_AUTOCLEAN, convert(enabled)? BST_CHECKED : BST_UNCHECKED);

		setAutoCleanTips();
		setTimespanTips();
	} catch (...) {
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
	}
}


void CDlgScreenshot::enableAutoSave() {
	m_sliderSaveTimespan.EnableWindow(m_bEnableScreensave);
}
void CDlgScreenshot::enableAutoclean() {
	m_sliderAutoclearTimespan.EnableWindow(m_bEnableAutoclean);
}


void CDlgScreenshot::setAutoCleanTips() {
	m_strAutoCleanHours.Format("%d days", m_sliderAutoclearTimespan.GetPos());
	GetDlgItem(IDC_STA_SCREENSAVE_AUTOCLEN)->SetWindowText(m_strAutoCleanHours);
}

void CDlgScreenshot::setTimespanTips() {
	m_strTimespanMins.Format("%d Mins", m_sliderSaveTimespan.GetPos());
	GetDlgItem(IDC_STA_SCREENSAVE_TIMESPAN)->SetWindowText(m_strTimespanMins);
}

BEGIN_MESSAGE_MAP(CDlgScreenshot, CDialog)
	ON_BN_CLICKED(IDC_CHK_SCREENSAVE, OnBnClickedChkScreensave)
	ON_BN_CLICKED(IDC_CHK_AUTOCLEAN, OnBnClickedChkAutoclean)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBnClickedBtnClear)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_VIEW_HISTORY, OnBnClickedViewHistory)
END_MESSAGE_MAP()


// CDlgScreenshot 消息处理程序

BOOL CDlgScreenshot::OnInitDialog() {
	CBaseDlg::OnInitDialog();

	Restore();

	enableAutoSave();
	enableAutoclean();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgScreenshot::OnBnClickedChkScreensave() {
	UpdateData(TRUE);
	enableAutoSave();
	SetModify(TRUE);
}

void CDlgScreenshot::OnBnClickedChkAutoclean() {
	UpdateData(TRUE);
	enableAutoclean();
	SetModify(TRUE);
}

void CDlgScreenshot::OnBnClickedBtnClear() {
	ClearScreen((HMODULE)AfxGetInstanceHandle());
	CString str;
	str.LoadString(IDS_SCREEN_RECORD_CLEAR_BUTTON);
	AfxMessageBox(str);
}

void CDlgScreenshot::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	if (pScrollBar->GetSafeHwnd() == m_sliderSaveTimespan.GetSafeHwnd()) {
		setTimespanTips();
		SetModify(TRUE);
	} else if (pScrollBar->GetSafeHwnd() == m_sliderAutoclearTimespan.GetSafeHwnd()) {
		setAutoCleanTips();
		SetModify(TRUE);
	}

	CBaseDlg::OnHScroll(nSBCode, nPos, pScrollBar);	
}

void CDlgScreenshot::OnBnClickedViewHistory()
{
	TCHAR images[MAX_PATH];
	GetScreenRecordPath(images, MAX_PATH, (HMODULE)AfxGetInstanceHandle());

	CDlgImageBrowser dlg;
	dlg.setImageDir(images);
	dlg.DoModal();
}
