// DlgWebHistory.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include ".\DlgWebHistory.h"
#include ".\dlgwebhistory.h"
#include ".\globalvariable.h"
#include <typeconvert.h>
#include <apputility.h>
#include <comdef.h>

// CDlgWebHistory 对话框

IMPLEMENT_DYNAMIC(CDlgWebHistory, CDialog)
CDlgWebHistory::CDlgWebHistory(CWnd* pParent /*=NULL*/)
: CBaseDlg(CDlgWebHistory::IDD, pParent) , m_bPornImage(FALSE)
, m_bPornPage(FALSE)
, m_bPornWebsite(FALSE)
, m_bAllImage(FALSE)
, m_bAllPages(FALSE)
, m_bAllWebsite(FALSE)
, m_strAutoClean(_T(""))
{
}

CDlgWebHistory::~CDlgWebHistory()
{
}

void CDlgWebHistory::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_EXPORT_WEBSITES, m_btnExportWebSiteList);
	DDX_Control(pDX, IDC_BTN_HISTORY, m_btnViewtheHistory);
	DDX_Control(pDX, IDC_BUN_CLEAR_CACHE, m_btnClearCache);
	DDX_Control(pDX, IDC_STA_TOOLS, m_staTools);
	DDX_Control(pDX, IDC_STA_HISTORY, m_staHistory);
	DDX_Control(pDX, IDC_STA_TYPES, m_staTypes);
	DDX_Check(pDX, IDC_CHK_PRON_IMAGE, m_bPornImage);
	DDX_Check(pDX, IDC_CHK_PORN_PAGE, m_bPornPage);
	DDX_Check(pDX, IDC_CHK_PORN_WEBSITES, m_bPornWebsite);
	DDX_Check(pDX, IDC_CHK_ALL_IMAGE, m_bAllImage);
	DDX_Check(pDX, IDC_CHK_ALLPAGES, m_bAllPages);
	DDX_Check(pDX, IDC_CHK_ALLWEBSITES, m_bAllWebsite);
	DDX_Control(pDX, IDC_SLIDER_AUTOCLEAR_TIME, m_sliderWebHistoryAutoClean);
}

void CDlgWebHistory::ChangeRecordType() {
	try {
		UpdateData(TRUE);
		IWebHistoryRecorder *pWebHistory = NULL;
		CoCreateInstance(CLSID_WebHistoryRecorder, NULL, CLSCTX_ALL, IID_IWebHistoryRecorder, (LPVOID*)&pWebHistory);
		pWebHistory->put_RecordAllImage(convert(m_bAllImage));
		pWebHistory->put_RecordAllPages(convert(m_bAllPages));
		pWebHistory->put_RecordAllURLs(convert(m_bAllWebsite));
		pWebHistory->put_RecordPornImage(convert(m_bPornImage));
		pWebHistory->put_RecordPornPages(convert(m_bPornPage));
		pWebHistory->put_RecordPornURLs(convert(m_bPornWebsite));
		pWebHistory->Release();

		g_configuration.getWebHistoryRecordSetting()->recordPornImage(m_bPornImage);
		g_configuration.getWebHistoryRecordSetting()->recordPornPages(m_bPornPage);
		g_configuration.getWebHistoryRecordSetting()->recordPornWebsite(m_bPornWebsite);
		g_configuration.getWebHistoryRecordSetting()->recordAllImage(m_bAllImage);
		g_configuration.getWebHistoryRecordSetting()->recordAllPages(m_bAllPages);
		g_configuration.getWebHistoryRecordSetting()->recordAllWebsite(m_bAllWebsite);
		g_configuration.getWebHistoryRecordAutoClean()->enable(true);
		g_configuration.getWebHistoryRecordAutoClean()->setTimespan(m_sliderWebHistoryAutoClean.GetPos());
	} catch (_com_error&) {
		CString str;
		str.LoadString(IDS_ERROR_WEB_SET_FAILED);
		AfxMessageBox(str);
	} catch(...) {
	}
}

int CDlgWebHistory::OnApply() {
	ChangeRecordType();
	return 0;
}
void CDlgWebHistory::OnShow() {
}

void CDlgWebHistory::updateSta() {
	m_strAutoClean.Format("%d days", m_sliderWebHistoryAutoClean.GetPos());
	GetDlgItem(IDC_STA_WEBHISTORY_AUTOCLEAN)->SetWindowText(m_strAutoClean);
}

void CDlgWebHistory::restoreSetting() {
	m_bPornImage	= g_configuration.getWebHistoryRecordSetting()->pornimages_setting();
	m_bPornPage		= g_configuration.getWebHistoryRecordSetting()->pornpages_setting();
	m_bPornWebsite	= g_configuration.getWebHistoryRecordSetting()->pornwebsites_setting();
	m_bAllImage		= g_configuration.getWebHistoryRecordSetting()->allimages_setting();
	m_bAllPages		= g_configuration.getWebHistoryRecordSetting()->allpages_setting();
	m_bAllWebsite	= g_configuration.getWebHistoryRecordSetting()->allwebsites_setting();

	// auto clean
	m_sliderWebHistoryAutoClean.SetRange(g_configuration.getWebHistoryRecordAutoClean()->getRangeMin(),
	g_configuration.getWebHistoryRecordAutoClean()->getRangeMax());
	m_sliderWebHistoryAutoClean.SetTicFreq(1);
	m_sliderWebHistoryAutoClean.SetPos(g_configuration.getWebHistoryRecordAutoClean()->getTimespan());

	updateSta();
	UpdateData(FALSE);
}
BEGIN_MESSAGE_MAP(CDlgWebHistory, CDialog)
	ON_BN_CLICKED(IDC_BUN_CLEAR_CACHE, OnBnClickedBunClearCache)
	ON_BN_CLICKED(IDC_BTN_HISTORY_PAGES, OnBnClickedBtnHistoryPages)
	ON_BN_CLICKED(IDC_BTN_HISTORY_IMAGE, OnBnClickedBtnHistoryImage)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHK_PRON_IMAGE, OnBnClickedChkPronImage)
	ON_BN_CLICKED(IDC_CHK_PORN_PAGE, OnBnClickedChkPornPage)
	ON_BN_CLICKED(IDC_CHK_PORN_WEBSITES, OnBnClickedChkPornWebsites)
	ON_BN_CLICKED(IDC_CHK_ALL_IMAGE, OnBnClickedChkAllImage)
	ON_BN_CLICKED(IDC_CHK_ALLPAGES, OnBnClickedChkAllpages)
	ON_BN_CLICKED(IDC_CHK_ALLWEBSITES, OnBnClickedChkAllwebsites)
END_MESSAGE_MAP()

// CDlgWebHistory 消息处理程序

void CDlgWebHistory::OnBnClickedBunClearCache() {
	ClearHistory((HMODULE)AfxGetInstanceHandle());
	CString str;
	str.LoadString(IDS_WEB_HISTORY_CLEAR_SUCC);
	AfxMessageBox(str);
}

BOOL CDlgWebHistory::OnInitDialog()
{
	CBaseDlg::OnInitDialog();
	CString str;

	Restore();

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDlgWebHistory::OnBnClickedBtnHistoryPages()
{
	TCHAR webpages[MAX_PATH], installpath[MAX_PATH];
	GetInstallPath(installpath, MAX_PATH, (HMODULE)AfxGetInstanceHandle());
	GetPageDirectory(webpages, MAX_PATH, installpath);
	ShellExecute(NULL, TEXT("open"), NULL, NULL, webpages, SW_SHOWNORMAL);
}

void CDlgWebHistory::OnBnClickedBtnHistoryImage() {
	TCHAR webimages[MAX_PATH], installpath[MAX_PATH];
	GetInstallPath(installpath, MAX_PATH, (HMODULE)AfxGetInstanceHandle());
	GetImageDirectory(webimages, MAX_PATH, installpath);
	ShellExecute(NULL, TEXT("open"), NULL, NULL, webimages, SW_SHOWNORMAL);
}

void CDlgWebHistory::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	if (pScrollBar->GetSafeHwnd() == m_sliderWebHistoryAutoClean.GetSafeHwnd()) {
		updateSta();
		SetModify(TRUE);
	}

	CBaseDlg::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDlgWebHistory::OnBnClickedChkPronImage() {
	SetModify(TRUE);
}

void CDlgWebHistory::OnBnClickedChkPornPage() {
	SetModify(TRUE);
}

void CDlgWebHistory::OnBnClickedChkPornWebsites() {
	SetModify(TRUE);
}

void CDlgWebHistory::OnBnClickedChkAllImage() {
	SetModify(TRUE);
}

void CDlgWebHistory::OnBnClickedChkAllpages() {
	SetModify(TRUE);
}

void CDlgWebHistory::OnBnClickedChkAllwebsites() {
	SetModify(TRUE);
}
