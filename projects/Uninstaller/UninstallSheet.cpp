// UninstallSheet.cpp : 实现文件
//

#include "stdafx.h"
#include "Uninstaller.h"
#include "UninstallSheet.h"


// CUninstallSheet

IMPLEMENT_DYNAMIC(CUninstallSheet, CPropertySheet)
CUninstallSheet::CUninstallSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	initialize();
}

CUninstallSheet::CUninstallSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	initialize();
}

CUninstallSheet::~CUninstallSheet()
{
}

void CUninstallSheet::initialize() {
	AddPage(&m_pageAscertain);
	AddPage(&m_pageProcess);
	AddPage(&m_pageReboot);
	SetWizardMode();
}

BEGIN_MESSAGE_MAP(CUninstallSheet, CPropertySheet)
END_MESSAGE_MAP()


// CUninstallSheet 消息处理程序
