// PageProcess.cpp : 实现文件
//

#include "stdafx.h"
#include "Uninstaller.h"
#include "PageProcess.h"


// CPageProcess 对话框

IMPLEMENT_DYNAMIC(CPageProcess, CPropertyPage)
CPageProcess::CPageProcess()
	: CPropertyPage(CPageProcess::IDD)
{
}

CPageProcess::~CPageProcess()
{
}

void CPageProcess::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageProcess, CPropertyPage)
END_MESSAGE_MAP()


// CPageProcess 消息处理程序
