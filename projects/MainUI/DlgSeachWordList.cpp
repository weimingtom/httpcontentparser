// DlgSeachWordList.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include ".\dlgseachwordlist.h"
#include <apputility.h>



// CDlgSeachWordList 对话框

IMPLEMENT_DYNAMIC(CDlgSeachWordList, CDialog)
CDlgSeachWordList::CDlgSeachWordList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSeachWordList::IDD, pParent)
{
}

CDlgSeachWordList::~CDlgSeachWordList()
{
}

void CDlgSeachWordList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SEARCH_WORD, m_list);
}


BEGIN_MESSAGE_MAP(CDlgSeachWordList, CDialog)
END_MESSAGE_MAP()


namespace {
// 此为另外一个线程执行的过程
// 他负责将词汇从文件中读取出来并显示到界面上
UINT getSeachWords( LPVOID pParam )
{
	return 0;
}



}

int CDlgSeachWordList::showOnList(const DATA_PAIR &items) {
	int cnt = 0;
	DATA_PAIR::const_iterator iter = items.begin();
	for(; iter != items.end(); ++iter)
	{	
		m_list.InsertItem(cnt, iter->first.c_str());
		m_list.SetItemText(cnt, 1, iter->second.seach_engine.c_str());
		m_list.SetItemText(cnt, 2, iter->second.last_seachtime.c_str());
		cnt ++;
	}

	return 0;
}

int CDlgSeachWordList::parseFile(DATA_PAIR &items) {
	try
	{
		using namespace std;
		TCHAR filename[MAX_PATH];
		GetSeachWordFile(filename, MAX_PATH);

		ifstream  file(filename);

		if (file.is_open())
		{
			const int BUF_SIZE = 1024;
			TCHAR line[BUF_SIZE];
			string key;
			ITEM_DATA data;

			while (file.good())
			{
				file.getline(line, BUF_SIZE);
				if (-1 != parseString(key, data.seach_engine, data.last_seachtime, line))
				{
					items.insert(make_pair(key, data));
				}
			}
		}

		file.close();
	}
	catch(...)
	{
	}

	return 0;
}

int CDlgSeachWordList::parseString(std::string &key, std::string &seachengine, std::string & last_time, const std::string &line) {
	int iIndex = line.find('&');
	if (-1 != iIndex)
	{
		int newSeperator = line.find('&', iIndex + 1);
		if (-1 != newSeperator)
		{
			key = line.substr(0, iIndex );
			seachengine = line.substr(iIndex + 1, newSeperator - iIndex -1);
			last_time = line.substr(newSeperator + 1, line.length());
			return 1;
		} else {
			return -1;
		}

	} else {
		return -1;
	}
}

// 从文件中读取词汇，并插入到列表当中
// 注意由于开始使用词汇排序，因此需要按顺序插入
void CDlgSeachWordList::getSeachWords()
{
	DATA_PAIR items;
	parseFile(items);
	showOnList(items);
}

void CDlgSeachWordList::InitList()
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
		{IDS_DLG_SEACHWORD,				  LVCFMT_LEFT,  90}, 
		{IDS_DLG_SEACHWORD_SEARCH_ENGINE, LVCFMT_RIGHT, 90},
		{IDS_DLG_SEACHWORD_TIME,		  LVCFMT_RIGHT, 100},
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

// CDlgSeachWordList 消息处理程序
BOOL CDlgSeachWordList::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitList();
	
	getSeachWords();
	
	return TRUE;
}
