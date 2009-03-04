#ifndef _MAINUI_CDLGPROGRAMCONTROL_H__
#define _MAINUI_CDLGPROGRAMCONTROL_H__

// CDlgProgramControl 对话框

#include ".\basedlg.h"
#include "afxcmn.h"
#include ".\ListView\ListViewCtrlEx.h"

#include <string>
#include <map>

class CProgramList: public CListCtrlEx {
public:
	const CString GetToolTip(int, int, UINT nFlags, BOOL&) { return "";}
};

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

	void addNewFile(const CString &filename);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnSet();

	// 给出提示
	friend class CProgramList; 
protected:
	CProgramList m_list;
public:
	virtual BOOL OnInitDialog();
};



#endif  // _MAINUI_CDLGPROGRAMCONTROL_H__