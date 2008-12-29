#pragma once


#include ".\basedlg.h"
#include "afxwin.h"

#include  ".\Guilib1.5\GuiGroupBox.h"


class CLev1DlgRules : public CBaseDlg {
	DECLARE_DYNAMIC(CLev1DlgRules)

public:
	CLev1DlgRules(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLev1DlgRules();

// 对话框数据
	enum { IDD = IDD_LEV1_RULE };

	
	virtual int OnApply();
	virtual void OnShow();
protected:
	virtual void restoreSetting();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_strComment;
	CEdit m_edit;
	CGuiGroupBox m_staComment;
};
