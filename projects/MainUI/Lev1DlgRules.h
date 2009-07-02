#pragma once


#include ".\basedlg.h"
#include "afxwin.h"


class CLev1DlgRules : public CBaseDlg {
	DECLARE_DYNAMIC(CLev1DlgRules)

public:
	CLev1DlgRules(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLev1DlgRules();

	virtual std::string getHelpLink() const;

// 对话框数据
	enum { IDD = IDD_LEV1_RULE };

	virtual BOOL OnInitDialog();
	virtual int OnApply();
	virtual void OnShow();
protected:
	virtual void restoreSetting();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
