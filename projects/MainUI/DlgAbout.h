#pragma once
#include ".\basedlg.h"
// CDlgAbout 对话框

class CDlgAbout : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgAbout)

public:
	CDlgAbout(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAbout();

// 对话框数据
	enum { IDD = IDD_DLG_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
