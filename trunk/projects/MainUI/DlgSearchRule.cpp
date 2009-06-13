// DlgSearchRule.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgSearchRule.h"
#include "globalvariable.h"
#include ".\dlgsearchrule.h"
#include <com\comutility.h>
#include <typeconvert.h>
#include ".\logger_def.h"

// CDlgSearchRule 对话框

IMPLEMENT_DYNAMIC(CDlgSearchRule, CDialog)
CDlgSearchRule::CDlgSearchRule(CWnd* pParent /*=NULL*/)
: CBaseDlg(CDlgSearchRule::IDD, pParent)
, rules(this, this)
, m_bEnableSearchRule(TRUE)
, m_bChkGoogle(FALSE)
, m_bChkYahoo(FALSE)
, m_bChkBaidu(FALSE)
{
	auther_name_ = ANOTHER_BSL;
}

CDlgSearchRule::~CDlgSearchRule()
{
}

std::string CDlgSearchRule::getHelpLink() const {
	return "";
}


int CDlgSearchRule::OnApply() {
	rules.Apply();
	UpdateData();
	try {
		AutoInitInScale _auto_com_init;
		ISearchRule *seach_rule;
		HRESULT hr = CoCreateInstance(CLSID_SearchRule, NULL, CLSCTX_LOCAL_SERVER, IID_ISearchRule, (LPVOID*)&seach_rule);
		if (FAILED(hr)) {
			LOGGER_WRITE_COM_FAILED(MAINUI_LOGGER, "Create SearchRule", hr);
			AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
			return -1;
		}

		seach_rule->enableCheckSeachEngine(_bstr_t("google"), convert(m_bChkGoogle));
		seach_rule->enableCheckSeachEngine(_bstr_t("yahoo"), convert(m_bChkYahoo));
		seach_rule->enableCheckSeachEngine(_bstr_t("baidu"), convert(m_bChkBaidu));
		SafeRelease(seach_rule);

		return 0;
	} catch (_com_error&) {
		LOGGER_WRITE(MAINUI_LOGGER, "CATCH(_com_error)");
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
		return -1;
	}
}

void CDlgSearchRule::OnShow() {
	ListBox.SetFocus();
	ListBox.ShowWindow(SW_SHOW);
	ListBox.UpdateWindow();
}


void CDlgSearchRule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEARCH_LIST, ListBox);
	DDX_Control(pDX, IDC_CHK_ENABLE_SEARCH, m_chkEnableSearchChk);
	DDX_Check(pDX, IDC_CHK_ENABLE_SEARCH, m_bEnableSearchRule);
	DDX_Check(pDX, IDC_CHK_GOOGLE, m_bChkGoogle);
	DDX_Check(pDX, IDC_CHK_YAHOO, m_bChkYahoo);
	DDX_Check(pDX, IDC_CHK_BAIDU, m_bChkBaidu);
}

void CDlgSearchRule::restoreSetting() {
	rules.Reset();
	ListBox.GetListCtrl()->DeleteAllItems();

	try {
		AutoInitInScale _auto_com_init;
		ISearchRule *seach_rule;
		HRESULT hr = CoCreateInstance(CLSID_SearchRule, NULL, CLSCTX_LOCAL_SERVER, IID_ISearchRule, (LPVOID*)&seach_rule);
		if (FAILED(hr)) {
			LOGGER_WRITE_COM_FAILED(MAINUI_LOGGER, "Create SearchRule", hr);
			throw int(SNOWMAN_ERROR_COM_INIT_FAILED);
		}

		BSTR cur, next;
		seach_rule->getFirstSearchWord(&cur);
		while (_bstr_t(cur).length() != 0) {
			ListBox.AddItem((TCHAR*)_bstr_t(cur));
			seach_rule->getNextSearchWord(cur, &next);
			SysFreeString(cur); 
			cur = next;
		}

		VARIANT_BOOL isEnabled;
		seach_rule->isSettingEnabled(_bstr_t(TEXT("google")), &isEnabled);
		m_bChkGoogle = convert(isEnabled);

		seach_rule->isSettingEnabled(_bstr_t(TEXT("yahoo")), &isEnabled);
		m_bChkYahoo = convert(isEnabled);

		seach_rule->isSettingEnabled(_bstr_t(TEXT("baidu")), &isEnabled);
		m_bChkBaidu = convert(isEnabled);

		UpdateData(FALSE);
	} catch (...) {
		LOGGER_WRITE(MAINUI_LOGGER, "CATCH(...)");
		throw int(SNOWMAN_ERROR_COM_INIT_FAILED);
	}
}

void CDlgSearchRule::OnAddItem(const CString &str) {
	try {
		AutoInitInScale _auto_com_init;
		ISearchRule *seach_rule;
		HRESULT hr = CoCreateInstance(CLSID_SearchRule, NULL, CLSCTX_LOCAL_SERVER, IID_ISearchRule, (LPVOID*)&seach_rule);
		if (FAILED(hr)) {
			LOGGER_WRITE_COM_FAILED(MAINUI_LOGGER, "Create searchRule", hr)
			AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONERROR);
			return;
		}

		seach_rule->addBlackSeachword(_bstr_t(str));
		SafeRelease(seach_rule);

		// 修改界面
		SetModify(TRUE);
	} catch(...) {
		LOGGER_WRITE(MAINUI_LOGGER, "CATCH(...)");
	}
}
void CDlgSearchRule::OnDelItem(const CString &str) {
	try {
		AutoInitInScale _auto_com_init;
		ISearchRule *seach_rule;
		HRESULT hr = CoCreateInstance(CLSID_SearchRule, NULL, CLSCTX_LOCAL_SERVER, IID_ISearchRule, (LPVOID*)&seach_rule);
		if (FAILED(hr)) {
			LOGGER_WRITE_COM_FAILED(MAINUI_LOGGER, "Create searchRule", hr)
			return;
		}

		seach_rule->removeBlackSeachWord(_bstr_t(str));
		SafeRelease(seach_rule);

		// 修改界面
		SetModify(TRUE);
	} catch (...) {
		LOGGER_WRITE(MAINUI_LOGGER, "CATCH(...)");
	}
}
bool CDlgSearchRule::ValidateItem(const CString & str, CString &output) {
	output = str;
	return true;
}

BEGIN_MESSAGE_MAP(CDlgSearchRule, CDialog)
	ON_BN_CLICKED(IDC_CHK_ENABLE_SEARCH, OnBnClickedChkEnableSearch)
	ON_BN_CLICKED(IDC_CHK_GOOGLE, OnBnClickedChkGoogle)
	ON_BN_CLICKED(IDC_CHK_YAHOO, OnBnClickedChkYahoo)
	ON_BN_CLICKED(IDC_CHK_BAIDU, OnBnClickedChkBaidu)
END_MESSAGE_MAP()


// CDlgSearchRule 消息处理程序

BOOL CDlgSearchRule::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

	ListBox.setOnTextChanged(&rules);
	Restore();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlgSearchRule::OnBnClickedChkEnableSearch()
{
	SetModify(TRUE);
}

void CDlgSearchRule::OnBnClickedChkGoogle()
{
	SetModify(TRUE);
}

void CDlgSearchRule::OnBnClickedChkYahoo()
{
	SetModify(TRUE);
}

void CDlgSearchRule::OnBnClickedChkBaidu()
{
	SetModify(TRUE);
}
