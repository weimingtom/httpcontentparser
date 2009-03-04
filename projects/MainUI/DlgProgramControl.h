#ifndef _MAINUI_CDLGPROGRAMCONTROL_H__
#define _MAINUI_CDLGPROGRAMCONTROL_H__

// CDlgProgramControl 对话框

#include ".\basedlg.h"

class CDlgProgramControl : public CBaseDlg {
	DECLARE_DYNAMIC(CDlgProgramControl)

public:
	CDlgProgramControl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgProgramControl();

// 对话框数据
	enum { IDD = IDD_DLG_PROGRAM };

public:
		virtual int OnApply();
		virtual void OnShow();
		virtual void restoreSetting();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnSet();
};

#endif  // _MAINUI_CDLGPROGRAMCONTROL_H__