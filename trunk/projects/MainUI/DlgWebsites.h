#pragma once
#include "afxcmn.h"
#include ".\ListView\ListViewCtrlEx.h"
#include ".\popupdialog.h"
#include <websitesUtil.h>
#include <comdef.h>

// CDlgWebsites 对话框
class CWebsitesList: public CListCtrlEx {
  public:
	  const CString GetToolTip(int, int, UINT nFlags, BOOL&) { return "";}
};

class CDlgWebsites : public CPopupDialog
{
	DECLARE_DYNAMIC(CDlgWebsites)

public:
	CDlgWebsites(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgWebsites();

// 对话框数据
	enum { IDD = IDD_POPDLG_WEBSITES };

protected:
	int showOnList();
	int addItem(const _bstr_t &name, const long times, const long hightime, const long lowtime, const int iIndex);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedClear();
	DECLARE_MESSAGE_MAP()
private:
	CWebsitesList m_list;
	void initializeList();

	HICON m_hIcon;
};
