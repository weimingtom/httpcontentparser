#ifndef _MAINUI_CDLGPROGRAMCONTROL_H__
#define _MAINUI_CDLGPROGRAMCONTROL_H__

// CDlgProgramControl �Ի���

#include ".\basedlg.h"

class CDlgProgramControl : public CBaseDlg {
	DECLARE_DYNAMIC(CDlgProgramControl)

public:
	CDlgProgramControl(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgProgramControl();

// �Ի�������
	enum { IDD = IDD_DLG_PROGRAM };

public:
		virtual int OnApply();
		virtual void OnShow();
		virtual void restoreSetting();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnSet();
};

#endif  // _MAINUI_CDLGPROGRAMCONTROL_H__