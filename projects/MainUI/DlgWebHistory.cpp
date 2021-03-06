// DlgWebHistory.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include ".\DlgWebHistory.h"
#include ".\dlgwebhistory.h"
#include ".\globalvariable.h"
#include ".\dlgimagebrowser.h"
#include ".\dlgseachwordlist.h"
#include ".\dlgwebsites.h"
#include <typeconvert.h>
#include <apputility\apputility.h>
#include <comdef.h>
#include <logger\logger.h>

#define MAX_AUTO_CLEAR_SPAN	30
#define MIN_AUTO_CLEAR_SPAN	1


// CDlgWebHistory 对话框

IMPLEMENT_DYNAMIC(CDlgWebHistory, CDialog)
CDlgWebHistory::CDlgWebHistory(CWnd* pParent /*=NULL*/)
: CBaseDlg(CDlgWebHistory::IDD, pParent) 
, m_bAllImage(FALSE)
, m_bAllPages(FALSE)
, m_bAllWebsite(FALSE)
, m_strAutoClean(_T(""))
, m_bSearchWord(FALSE)
{
	auther_name_ = ANOTHER_WH;
}

CDlgWebHistory::~CDlgWebHistory()
{
}

std::string CDlgWebHistory::getHelpLink() const {
	return "";
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
	DDX_Check(pDX, IDC_CHK_ALL_IMAGE, m_bAllImage);
	DDX_Check(pDX, IDC_CHK_ALLPAGES, m_bAllPages);
	DDX_Check(pDX, IDC_CHK_ALLWEBSITES, m_bAllWebsite);
	DDX_Control(pDX, IDC_SLIDER_AUTOCLEAR_TIME, m_sliderWebHistoryAutoClean);
	DDX_Check(pDX, IDC_CHK_SEARCH_KEYWORD, m_bSearchWord);
}

void CDlgWebHistory::ChangeRecordType() {
	try {
		UpdateData(TRUE);
		IWebHistoryRecorder *pWebHistory = NULL;
		HRESULT hr = CoCreateInstance(CLSID_WebHistoryRecorder, NULL, CLSCTX_ALL, IID_IWebHistoryRecorder, (LPVOID*)&pWebHistory);
		if (FAILED(hr)) {
			__LERR__("Create historyRecord with HRESULT value"<<std::hex<<hr);
			AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
			return;
		}

		pWebHistory->put_RecordAllImage(convert(m_bAllImage));
		pWebHistory->put_RecordAllPages(convert(m_bAllPages));
		pWebHistory->put_RecordAllURLs(convert(m_bAllWebsite));
		pWebHistory->put_RecordSeachKeyword(convert(m_bSearchWord));
		pWebHistory->setAutoClearTimespan(m_sliderWebHistoryAutoClean.GetPos());
		pWebHistory->Release();
	} catch (_com_error& e) {
		__LERR__("_com_error exception with Description " << (TCHAR*)e.Description());
		AfxMessageBox(IDS_ERROR_WEB_SET_FAILED, MB_OK | MB_ICONERROR);
	} catch(...) {
		__LERR__("CATCH(...)");
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
	}
}

INT_PTR CDlgWebHistory::OnApply() {
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
	try {
		IWebHistoryRecorder *pWebHistory = NULL;
		HRESULT hr = CoCreateInstance(CLSID_WebHistoryRecorder, NULL, CLSCTX_ALL, IID_IWebHistoryRecorder, (LPVOID*)&pWebHistory);
		if (FAILED(hr)) {
			__LERR__("Create historyRecord with HRESULT value "<<hr);
			throw INT_PTR(SNOWMAN_ERROR_COM_INIT_FAILED);
		}

		VARIANT_BOOL isEnabled;
		pWebHistory->isSettingRecordAllImages(&isEnabled);
		m_bAllImage = convert(isEnabled);
		pWebHistory->isSettingRecordAllPages(&isEnabled);
		m_bAllPages = convert(isEnabled);
		pWebHistory->isSettingRecordAllWebsites(&isEnabled);
		m_bAllWebsite = convert(isEnabled);
		pWebHistory->isSettingRecordSearchWord(&isEnabled);
		m_bSearchWord = convert(isEnabled);

		// auto clean
		LONG timspan;
		pWebHistory->getAutoClearTimespan(&timspan);
		m_sliderWebHistoryAutoClean.SetRange(MIN_AUTO_CLEAR_SPAN, MAX_AUTO_CLEAR_SPAN);
		m_sliderWebHistoryAutoClean.SetTicFreq(1);
		m_sliderWebHistoryAutoClean.SetPos(timspan);

		updateSta();
		UpdateData(FALSE);
	} catch(...) {
		__LERR__( "CATCH(_com_error)");
		throw INT_PTR(SNOWMAN_ERROR_COM_INIT_FAILED);
	}
}
BEGIN_MESSAGE_MAP(CDlgWebHistory, CDialog)
	ON_BN_CLICKED(IDC_BUN_CLEAR_CACHE, OnBnClickedBunClearCache)
	ON_BN_CLICKED(IDC_BTN_HISTORY_PAGES, OnBnClickedBtnHistoryPages)
	ON_BN_CLICKED(IDC_BTN_HISTORY_IMAGE, OnBnClickedBtnHistoryImage)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHK_ALL_IMAGE, OnBnClickedChkAllImage)
	ON_BN_CLICKED(IDC_CHK_ALLPAGES, OnBnClickedChkAllpages)
	ON_BN_CLICKED(IDC_CHK_ALLWEBSITES, OnBnClickedChkAllwebsites)
	ON_BN_CLICKED(IDC_BTN_HISTORY_SEACHWORD, OnBnClickedBtnHistorySeachword)
	ON_BN_CLICKED(IDC_CHK_SEARCH_KEYWORD, OnBnClickedChkSearchKeyword)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CDlgWebHistory 消息处理程序

void CDlgWebHistory::OnBnClickedBunClearCache() {
	try {
		IWebContentRecord *pWebContent = NULL;
		HRESULT hr = CoCreateInstance(CLSID_WebContentRecord, NULL, CLSCTX_ALL, IID_IWebContentRecord, (LPVOID*)&pWebContent);
		if (FAILED(hr)) {
			__LERR__("Create historyRecord with HRSULT value " << hr);
			AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
			return;
		}

		pWebContent->clearAll();

		CString str;
		str.LoadString(IDS_WEB_HISTORY_CLEAR_SUCC);
		AfxMessageBox(str);
	} catch (...) {
		__LERR__( "CATCH(...)");
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
		return;
	}
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
	CDlgWebsites dlg;
	dlg.DoModal();
}

void CDlgWebHistory::OnBnClickedBtnHistoryImage() {
	TCHAR webimages[MAX_PATH];
	GetImageDirectory(webimages, MAX_PATH);

	CDlgImageBrowser dlg;
	dlg.setImageDir(webimages);
	dlg.DoModal();
}

void CDlgWebHistory::OnBnClickedBtnHistorySeachword()
{
	CDlgSearchWordList dlg;
	dlg.DoModal();
}

void CDlgWebHistory::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	if (pScrollBar->GetSafeHwnd() == m_sliderWebHistoryAutoClean.GetSafeHwnd()) {
		updateSta();
		SetModify(TRUE);
	}

	CBaseDlg::OnHScroll(nSBCode, nPos, pScrollBar);
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

void CDlgWebHistory::OnBnClickedChkSearchKeyword()
{
	SetModify(TRUE);
}

HBRUSH CDlgWebHistory::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return CBaseDlg::OnCtlColor(pDC, pWnd, nCtlColor);
}
