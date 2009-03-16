#ifndef _MAINUI_CDLGSEACHWORDLIST_H__
#define _MAINUI_CDLGSEACHWORDLIST_H__


#include ".\ListView\ListViewCtrlEx.h"
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
class CDlgSearchWordList : public CDialog
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
	enum { IDD = IDD_DLG_SEACHWORD_HISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CECListCtrlEx m_list;
	afx_msg void OnBnClickedSearchClear();
};

#endif  // _MAINUI_CDLGSEACHWORDLIST_H__
