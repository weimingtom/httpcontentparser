#ifndef _MAINUI_CDLGSWITCHCHILDREN_H__
#define _MAINUI_CDLGSWITCHCHILDREN_H__

#include ".\popupdialog.h"


// CDlgSwitchChildren dialog
// 此对话框的作用：当用户关闭窗口的时候，询问用户是否切换到子模式
class CDlgSwitchChildren : public CDialog
{
	DECLARE_DYNAMIC(CDlgSwitchChildren)

public:
	CDlgSwitchChildren(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSwitchChildren();

// Dialog Data
	enum { IDD = IDD_DLG_MIN_MAINUI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	BOOL m_bDontAskmeAgain;
};

#endif  // _MAINUI_CDLGSWITCHCHILDREN_H__