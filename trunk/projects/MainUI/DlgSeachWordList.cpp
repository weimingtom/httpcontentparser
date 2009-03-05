// DlgSeachWordList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include ".\dlgseachwordlist.h"
#include ".\globalvariable.h"
#include <apputility.h>
#include <comdef.h>
#include <com\comutility.h>
#include <utility\timeutility.h>
#include <string>



// CDlgSearchWordList �Ի���

IMPLEMENT_DYNAMIC(CDlgSearchWordList, CDialog)
CDlgSearchWordList::CDlgSearchWordList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSearchWordList::IDD, pParent)
{
}

CDlgSearchWordList::~CDlgSearchWordList()
{
}

void CDlgSearchWordList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SEARCH_WORD, m_list);
}


BEGIN_MESSAGE_MAP(CDlgSearchWordList, CDialog)
END_MESSAGE_MAP()


int CDlgSearchWordList::addItem(const _bstr_t &name, const long times, const long searchengine_type, const long hightime, const long lowtime, const int iIndex) {
	TCHAR buffer[1024];
	FILETIME ft;
	ft.dwHighDateTime = hightime;
	ft.dwLowDateTime = lowtime;
	m_list.InsertItem(iIndex, (LPCTSTR)name);

	// ��ָ��������
	const TCHAR *p = GetSearchEngineName(searchengine_type);
	m_list.SetItemText(iIndex, 1, GetSearchEngineName(searchengine_type));

	// ������������
	m_list.SetItemText(iIndex, 2, itoa(times, buffer, 10));

	// �������һ������ʱ��
	m_list.SetItemText(iIndex, 3, timeutility::USFormatTime(ft, buffer, 1024));
	return 0;
}
int CDlgSearchWordList::showOnList() {
	try {
		AutoInitInScale _auto;
		
		IWebContentRecord *record = NULL;
		HRESULT hr = CoCreateInstance(CLSID_WebContentRecord, NULL, CLSCTX_LOCAL_SERVER, IID_IWebContentRecord, (LPVOID*)&record);
		if (FAILED(hr)) {
			return -1;
		}

		BSTR cur, next;
		int cnt = 0;
		long times, searchengine, hightime, lowtime;

		record->GetFirstSearchKeyword(&cur, &times, &searchengine, &hightime, &lowtime);
		while (hightime != 0 && lowtime != 0) {
			addItem(_bstr_t(cur), times, searchengine, hightime, lowtime, cnt);

			// ��ȡ��һ���ʻ�
			record->GetNextSearchKeyword(cur, &next, &times, &searchengine, &hightime, &lowtime);
			cur = next;
		}
	} catch (_com_error &) {
	}
	return 0;
}

void CDlgSearchWordList::InitList()
{
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
		{IDS_DLG_WEBSITES_NAME,				  LVCFMT_LEFT,  90}, 
		{IDS_DLG_SEACHWORD_SEARCH_ENGINE, LVCFMT_RIGHT, 90},
		{IDS_DLG_SEACHWORD_SEARCH_TIMES, LVCFMT_CENTER, 70},
		{IDS_DLG_SEACHWORD_LAST_TIME,		  LVCFMT_RIGHT, 100},
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
}

// CDlgSearchWordList ��Ϣ��������
BOOL CDlgSearchWordList::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitList();
	
	showOnList();
	
	return TRUE;
}