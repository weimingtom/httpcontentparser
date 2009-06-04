#ifndef _UNINSTALL_SHEET_H__
#define _UNINSTALL_SHEET_H__


#include ".\PageProcess.h"
#include ".\PageAscertain.h"
#include ".\PageReboot.h"


class CUninstallSheet : public CPropertySheet {
	DECLARE_DYNAMIC(CUninstallSheet)

public:
	CUninstallSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CUninstallSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CUninstallSheet();

protected:
	DECLARE_MESSAGE_MAP()

	CPageAscertain m_pageAscertain;
	CPageProcess m_pageProcess;
	CPageReboot m_pageReboot;

	void initialize();
};

#endif  // _UNINSTALL_SHEET_H__
