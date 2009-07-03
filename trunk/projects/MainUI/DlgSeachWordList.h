#ifndef _MAINUI_CDLGSEACHWORDLIST_H__
#define _MAINUI_CDLGSEACHWORDLIST_H__


#include ".\ListView\ListViewCtrlEx.h"
#include ".\popupdialog.h"
#include "afxcmn.h"
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <comdef.h>
#include <searchengine_define.h>
#include <searchkeywordutil.h>

class CECListCtrlEx: public CListCtrlEx
{
  public:
	  const CString GetToolTip(int, int, UINT nFlags, BOOL&) { return "";}
};

// CDlgSeachWordList �Ի���
class CDlgSearchWordList : public CPopupDialog
{
	DECLARE_DYNAMIC(CDlgSearchWordList)

public:
	CDlgSearchWordList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSearchWordList();

protected:

	// ����List contrl�����
	void InitList();

	// ��ʾ
	int showOnList();

	int addItem(const _bstr_t &name, const long times, const long searchengine_type, const long hightime, const long lowtime, const int iIndex);

// �Ի�������
	enum { IDD = IDD_POPDLG_SEACHWORD_HISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	CECListCtrlEx m_list;
	afx_msg void OnBnClickedSearchClear();
	DECLARE_MESSAGE_MAP()
private:
	HICON m_hIcon;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

#endif  // _MAINUI_CDLGSEACHWORDLIST_H__
