#pragma once


// CDlgCheckPassword 对话框
#include "resource.h"

class CDlgCheckPassword : public CDialog
{
	DECLARE_DYNAMIC(CDlgCheckPassword)

public:
	CDlgCheckPassword(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCheckPassword();

// 对话框数据
	enum { IDD = IDD_POPDLG_CHKPASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
