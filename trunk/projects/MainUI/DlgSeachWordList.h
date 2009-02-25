#ifndef _MAINUI_CDLGSEACHWORDLIST_H__
#define _MAINUI_CDLGSEACHWORDLIST_H__


#include ".\ListView\ListViewCtrlEx.h"
#include "afxcmn.h"
#include <map>
#include <string>
#include <iostream>
#include <fstream>

class CECListCtrlEx: public CListCtrlEx
{
  public:
	  const CString GetToolTip(int, int, UINT nFlags, BOOL&) { return "";}
};

// CDlgSeachWordList �Ի���
class CDlgSeachWordList : public CDialog
{
	DECLARE_DYNAMIC(CDlgSeachWordList)

public:
	CDlgSeachWordList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSeachWordList();

protected:

	// ����List contrl�����
	void InitList();
	
	void getSeachWords();
	
	typedef struct
	{
		std::string last_seachtime;
		std::string seach_engine;
	}ITEM_DATA;

	typedef std::map<std::string, ITEM_DATA> DATA_PAIR;

	int showOnList(const DATA_PAIR &items);
	int parseFile(DATA_PAIR &items);
	int parseString(std::string &key, std::string &seachengine, std::string & last_time, const std::string &line);

// �Ի�������
	enum { IDD = IDD_DLG_SEACHWORD_HISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CECListCtrlEx m_list;
};

#endif  // _MAINUI_CDLGSEACHWORDLIST_H__
