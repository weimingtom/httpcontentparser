#pragma once

#include ".\basedlg.h"

// CDlgEyecare 对话框

class CDlgEyecare : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgEyecare)

public:
	CDlgEyecare(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgEyecare();

// 对话框数据
	enum { IDD = IDD_DLG_EYECARE };

	virtual void OnApply();
	virtual void OnShow();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
