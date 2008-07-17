#pragma once
#include ".\basedlg.h"

// CDlgSearchRule 对话框

class CDlgSearchRule : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgSearchRule)

public:
	CDlgSearchRule(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSearchRule();

// 对话框数据
	enum { IDD = IDD_DLG_SEARCH_RULE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
