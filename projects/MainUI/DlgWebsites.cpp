// DlgWebsites.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgWebsites.h"
#include ".\dlgwebsites.h"
#include ".\globalvariable.h"
#include <comdef.h>
#include <com\comutility.h>
#include <utility\timeutility.h>
#include <string>



// CDlgWebsites 对话框

IMPLEMENT_DYNAMIC(CDlgWebsites, CPopupDialog)
CDlgWebsites::CDlgWebsites(CWnd* pParent /*=NULL*/)
	: CPopupDialog(CDlgWebsites::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TREE_SEACH);
}

CDlgWebsites::~CDlgWebsites()
{
}

void CDlgWebsites::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CDlgWebsites, CPopupDialog)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBnClickedClear)
END_MESSAGE_MAP()

int CDlgWebsites::addItem(const _bstr_t &name, const long times, const long hightime, const long lowtime, const int iIndex) {
	TCHAR buffer[1024];
	FILETIME ft;
	ft.dwHighDateTime = hightime;
	ft.dwLowDateTime = lowtime;
	m_list.InsertItem(iIndex, (LPCTSTR)name);

	// 设置搜索次数
	m_list.SetItemText(iIndex, 1, itoa(times, buffer, 10));

	// 设置最后一次搜索时间
	m_list.SetItemText(iIndex, 2, timeutility::USFormatTime(ft, buffer, 1024));
	return 0;
}

int CDlgWebsites::showOnList() {
	try {
		// 清空ListCtrl
		m_list.DeleteAllItems();

		AutoInitInScale _auto;
		
		IWebContentRecord *record = NULL;
		HRESULT hr = CoCreateInstance(CLSID_WebContentRecord, NULL, CLSCTX_LOCAL_SERVER, IID_IWebContentRecord, (LPVOID*)&record);
		if (FAILED(hr)) {
			return -1;
		}

		BSTR cur, next;
		int cnt = 0;
		long times, hightime, lowtime;

		record->GetFirstWebsite((BSTR*)&cur, &times, &hightime, &lowtime);
		while (lowtime != 0 && hightime != 0) {
			addItem(cur, times, hightime, lowtime, cnt);

			// 获取下一个词汇
			record->GetNextWebSite(cur, (BSTR*)&next, &times, &hightime, &lowtime);
			SysFreeString(cur);
			cur = next;
		}

		
	} catch (_com_error &) {
	}
	return 0;
}



// CDlgWebsites 消息处理程序

BOOL CDlgWebsites::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	m_list.SetExtendedStyle(
		LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP |
		LVS_EX_INFOTIP       | LVS_EX_LABELTIP);

	static const struct
	{
		UINT nColHdrId;
		int  nFormat;
		int  nWidth;
	} colData[] =
	{
		{IDS_DLG_WEBSITES,				  LVCFMT_LEFT,  130}, 
		{IDS_DLG_WEBSITE_VISIT_TIMES, LVCFMT_CENTER, 70},
		{IDS_DLG_WEBSITE_VISIT_LATEST_TIME,		  LVCFMT_RIGHT, 130},
	};
	const int nColCount = sizeof colData / sizeof colData[0];

	CString str;
	for (int nColumn = 0; nColumn < nColCount; ++nColumn)
	{
		VERIFY(str.LoadString(colData[nColumn].nColHdrId));
		m_list.InsertColumn(
			nColumn, str, colData[nColumn].nFormat, colData[nColumn].nWidth);
		if (nColumn > 0) m_list.EnableColumnHiding(nColumn, true);
	}

	m_list.EnableSortIcon     (TRUE, 1);
	m_list.ColorSortColumn    (TRUE);
	m_list.KeepLabelLeft      ();
	m_list.EnableSubItemTips  ();

	showOnList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// 从文件中读取网页数据并显示在List当中
void CDlgWebsites::initializeList() {
}
void CDlgWebsites::OnBnClickedClear()
{
	try {
		AutoInitInScale _auto;
		
		IWebContentRecord *record = NULL;
		HRESULT hr = CoCreateInstance(CLSID_WebContentRecord, NULL, CLSCTX_LOCAL_SERVER, IID_IWebContentRecord, (LPVOID*)&record);
		if (FAILED(hr)) {
			return;
		}
		record->clearWebsites();
		record->Release();
		record = NULL;

		showOnList();
	} catch (_com_error &) {
	}
}

