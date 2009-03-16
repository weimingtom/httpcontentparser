#pragma once
#include "afxcmn.h"
#include ".\ListView\ListViewCtrlEx.h"
#include <websitesUtil.h>
#include <comdef.h>

// CDlgWebsites �Ի���
class CWebsitesList: public CListCtrlEx {
  public:
	  const CString GetToolTip(int, int, UINT nFlags, BOOL&) { return "";}
};

class CDlgWebsites : public CDialog
{
	DECLARE_DYNAMIC(CDlgWebsites)

public:
	CDlgWebsites(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgWebsites();

// �Ի�������
	enum { IDD = IDD_DLG_WEBSITES };

protected:
	int showOnList();
	int addItem(const _bstr_t &name, const long times, const long hightime, const long lowtime, const int iIndex);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
	CWebsitesList m_list;
	

private:
	void initializeList();
public:
	afx_msg void OnBnClickedClear();
};
