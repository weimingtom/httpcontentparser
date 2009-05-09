#pragma once

#include ".\basedlg.h"
#include "afxwin.h"
// CLev1DlgTools 对话框

class CLev1DlgTools : public CBaseDlg
{
	DECLARE_DYNAMIC(CLev1DlgTools)

public:
	CLev1DlgTools(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLev1DlgTools();

	virtual std::string getHelpLink() const;

// 对话框数据
	enum { IDD = IDD_LEV1_TOOLS };

	virtual int OnApply();
	virtual void OnShow();
protected:
	virtual void restoreSetting();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
