#ifndef _MAINUI_CDLGREGISTER_H__
#define _MAINUI_CDLGREGISTER_H__

// CDlgRegister 对话框
#include ".\popupdialog.h"

class CDlgRegister : public CPopupDialog {
	DECLARE_DYNAMIC(CDlgRegister)

public:
	CDlgRegister(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgRegister();

// 对话框数据
	enum { IDD = IDD_POPLDG_REGISTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	DECLARE_MESSAGE_MAP()

	CString m_strSN;
};

#endif  // _MAINUI_CDLGREGISTER_H__