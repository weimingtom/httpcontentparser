#pragma once
#include "afxcmn.h"
#include ".\ListView\ListViewCtrlEx.h"
#include ".\popupdialog.h"
#include <websitesUtil.h>
#include <comdef.h>

// CDlgWebsites �Ի���
class CWebsitesList: public CListCtrlEx {
  public:
	  const CString GetToolTip(INT_PTR, INT_PTR, UINT nFlags, BOOL&) { return "";}
};

class CDlgWebsites : public CPopupDialog
{
	DECLARE_DYNAMIC(CDlgWebsites)

public:
	CDlgWebsites(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgWebsites();

// �Ի�������
	enum { IDD = IDD_POPDLG_WEBSITES };

protected:
	INT_PTR showOnList();
	INT_PTR addItem(const _bstr_t &name, const long times, const long hightime, const long lowtime, const INT_PTR iIndex);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedClear();
	DECLARE_MESSAGE_MAP()
private:
	CWebsitesList m_list;
	void initializeList();

	HICON m_hIcon;
};
