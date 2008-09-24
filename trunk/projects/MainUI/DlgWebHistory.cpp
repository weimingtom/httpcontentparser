// DlgWebHistory.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include ".\DlgWebHistory.h"
#include ".\dlgwebhistory.h"
#include ".\globalvariable.h"
#include <typeconvert.h>
#include <sysutility.h>
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
}

void CDlgWebHistory::ChangeRecordType() {
	try {
		UpdateData(TRUE);
		IWebHistoryRecorder *pWebHistory = NULL;
		CoCreateInstance(CLSID_WebHistoryRecorder, NULL, CLSCTX_ALL, IID_IWebHistoryRecorder, (LPVOID*)&pWebHistory);
		pWebHistory->put_RecordAllImage(convert(m_bAllImage));
		pWebHistory->put_RecordAllPages(convert(m_bAllPages));
		pWebHistory->put_RecordAllWebsite(convert(m_bAllWebsite));
		pWebHistory->put_RecordPornImage(convert(m_bPornImage));
		pWebHistory->put_RecordPronPages(convert(m_bPornPage));
		pWebHistory->put_RecordPornWebsite(convert(m_bPornWebsite));
		pWebHistory->Release();
	} catch (_com_error&) {
		CString str;
		str.LoadString(IDS_ERROR_WEB_SET_FAILED);
		AfxMessageBox(str);
	} catch(...) {
	}
}

void CDlgWebHistory::OnRestore() {

}

void CDlgWebHistory::OnApply() {
	ChangeRecordType();
}
void CDlgWebHistory::OnShow() {
}

void CDlgWebHistory::initializeSetting() {
	m_bPornImage	= g_configuration.getWebHistoryRecordSetting()->recordPornImage();
	m_bPornPage		= g_configuration.getWebHistoryRecordSetting()->recordPornPages();
	m_bPornWebsite	= g_configuration.getWebHistoryRecordSetting()->recordPornWebsite();
	m_bAllImage		= g_configuration.getWebHistoryRecordSetting()->recordAllImage();
	m_bAllPages		= g_configuration.getWebHistoryRecordSetting()->recordAllPages();
	m_bAllWebsite	= g_configuration.getWebHistoryRecordSetting()->recordAllWebsite();
	UpdateData(FALSE);
}
BEGIN_MESSAGE_MAP(CDlgWebHistory, CDialog)
	ON_BN_CLICKED(IDC_BUN_CLEAR_CACHE, OnBnClickedBunClearCache)
	ON_BN_CLICKED(IDC_BTN_EXPORT_WEBSITES, OnBnClickedBtnExportWebsites)
END_MESSAGE_MAP()

// CDlgWebHistory 消息处理程序

void CDlgWebHistory::OnBnClickedBunClearCache() {
	ClearHistory((HMODULE)AfxGetInstanceHandle());
}

BOOL CDlgWebHistory::OnInitDialog()
{
	CBaseDlg::OnInitDialog();
	CString str;

	initializeSetting();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlgWebHistory::OnBnClickedBtnExportWebsites() {
	CString strExt, strDefault;
	strExt.LoadString(IDS_WEB_HISTORY_FILEDLG_EXT);
	strDefault.LoadString(IDS_WEB_HISTORY_FILEDLG_DEFAULT);
	CFileDialog dlg(FALSE, _T("Chart Files (*.xlc)|*.xlc|All Files (*.*)|*.*||"), strDefault);
	if (IDOK == dlg.DoModal()) {
	}
}
