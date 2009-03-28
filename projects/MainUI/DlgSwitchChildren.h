#ifndef _MAINUI_CDLGSWITCHCHILDREN_H__
#define _MAINUI_CDLGSWITCHCHILDREN_H__

#include ".\popupdialog.h"


// CDlgSwitchChildren dialog
// �˶Ի�������ã����û��رմ��ڵ�ʱ��ѯ���û��Ƿ��л�����ģʽ
class CDlgSwitchChildren : public CPopupDialog
{
	DECLARE_DYNAMIC(CDlgSwitchChildren)

public:
	CDlgSwitchChildren(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSwitchChildren();

	// Dialog Data
	enum { IDD = IDD_DLG_MIN_MAINUI };

	BOOL switchToChildren() const;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bDontAskmeAgain;
};

#endif  // _MAINUI_CDLGSWITCHCHILDREN_H__