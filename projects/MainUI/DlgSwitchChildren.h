#ifndef _MAINUI_CDLGSWITCHCHILDREN_H__
#define _MAINUI_CDLGSWITCHCHILDREN_H__

#include ".\popupdialog.h"


// CDlgSwitchChildren dialog
// �˶Ի�������ã����û��رմ��ڵ�ʱ��ѯ���û��Ƿ��л�����ģʽ
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