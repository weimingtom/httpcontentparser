#pragma once

#include ".\basedlg.h"
#include ".\Cells.h"
#include <afxwin.h>
#include <Guilib1.5\GuiCheckBox.h>
#include <Enumerate.h>
// CDlgOnlineHour �Ի���

class CDlgOnlineHour : public CBaseDlg, Enumerator2<int, int>
{
	DECLARE_DYNAMIC(CDlgOnlineHour)

public:
	CDlgOnlineHour(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgOnlineHour();

// �Ի�������
	enum { IDD = IDD_DLG_ONLINE_RULE };

	virtual void OnApply();
	virtual void OnShow();

protected:
	CCells cells;
	CButton m_chkTimeCtrl;

	virtual void restoreSetting();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	BOOL m_bEnableTimeCheck;

	// Enum the accessNetword hour
protected:
	virtual int Enum(const int day, const int hour);
public:
	afx_msg void OnBnClickedChkTimectrl();
};
