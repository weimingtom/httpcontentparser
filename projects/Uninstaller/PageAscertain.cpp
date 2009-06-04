// PageAscertain.cpp : 实现文件
//

#include "stdafx.h"
#include "Uninstaller.h"
#include "PageAscertain.h"


// CPageAscertain 对话框

IMPLEMENT_DYNAMIC(CPageAscertain, CPropertyPage)
CPageAscertain::CPageAscertain()
	: CPropertyPage(CPageAscertain::IDD)
{
	GetDlgItem(ID_PREV_PANE)->EnableWindow(FALSE);
}

CPageAscertain::~CPageAscertain()
{
}

void CPageAscertain::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageAscertain, CPropertyPage)
END_MESSAGE_MAP()


// CPageAscertain 消息处理程序
