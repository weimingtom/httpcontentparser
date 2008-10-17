// DlgSearchRule.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgSearchRule.h"
#include "globalvariable.h"
#include ".\dlgsearchrule.h"
#include <com\comutility.h>
#include <typeconvert.h>

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
}

CDlgSearchRule::~CDlgSearchRule()
{
}

int CDlgSearchRule::OnApply() {
	rules.OnApply();
	UpdateData();
	try {
		AutoInitInScale _auto_com_init;
		ISearchRule *seach_rule;
		HRESULT hr = CoCreateInstance(CLSID_SearchRule, NULL, CLSCTX_LOCAL_SERVER, IID_ISearchRule, (LPVOID*)&seach_rule);
		if (FAILED(hr)) {
			//AfxMessageBox(
			return -1;
		}

		seach_rule->enableCheckSeachEngine(_bstr_t("google"), convert(m_bChkGoogle));
		seach_rule->enableCheckSeachEngine(_bstr_t("yahoo"), convert(m_bChkYahoo));
		seach_rule->enableCheckSeachEngine(_bstr_t("baidu"), convert(m_bChkBaidu));
		SafeRelease(seach_rule);
		return 0;

	} catch (_com_error&) {
		//AfxMessageBox(
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
	ListBox.setOnTextChanged(&rules);
	g_configuration.getSearchRule()->enumBlackWord((Enumerator1<std::string>*)this);
	m_bEnableSearchRule = g_configuration.getSearchRule()->isEnabled();

	UpdateData(FALSE);
}

int CDlgSearchRule::Enum(const std::string &words) {
	ListBox.AddItem(words.c_str());
	return 0;
}

void CDlgSearchRule::OnAddItem(const CString &str) {
	AutoInitInScale _auto_com_init;
	ISearchRule *seach_rule;
	HRESULT hr = CoCreateInstance(CLSID_SearchRule, NULL, CLSCTX_LOCAL_SERVER, IID_ISearchRule, (LPVOID*)&seach_rule);
	if (FAILED(hr)) {
		return;
	}

	seach_rule->addBlackSeachword(_bstr_t(str));
	SafeRelease(seach_rule);

	SetModify(TRUE);
}
void CDlgSearchRule::OnDelItem(const CString &str) {
	AutoInitInScale _auto_com_init;
	ISearchRule *seach_rule;
	HRESULT hr = CoCreateInstance(CLSID_SearchRule, NULL, CLSCTX_LOCAL_SERVER, IID_ISearchRule, (LPVOID*)&seach_rule);
	if (FAILED(hr)) {
		return;
	}

	seach_rule->removeBlackSeachWord(_bstr_t(str));
	SafeRelease(seach_rule);

	SetModify(TRUE);
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

	Restore();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
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
