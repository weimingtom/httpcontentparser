#ifndef _MAINUI_CDLGSWITCHCHILDREN_H__
#define _MAINUI_CDLGSWITCHCHILDREN_H__

#include ".\popupdialog.h"
#include ".\resource.h"


// CDlgSwitchChildren dialog
// 此对话框的作用：当用户关闭窗口的时候，询问用户是否切换到子模式
class CDlgSwitchChildren : public CPopupDialog
{
	DECLARE_DYNAMIC(CDlgSwitchChildren)

public:
	CDlgSwitchChildren(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSwitchChildren();

	// Dialog Data
	enum { IDD = IDD_POPDLG_MIN_MAINUI };

	BOOL switchToChildren() const;

private:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	DECLARE_MESSAGE_MAP()

	void putParameterToCOM(const bool autoswitchOnClose);
private:
	BOOL m_bDontAskmeAgain;
};

#endif  // _MAINUI_CDLGSWITCHCHILDREN_H__