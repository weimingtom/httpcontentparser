#pragma once

#include ".\basedlg.h"
// CDlgOnlineHour �Ի���

class CDlgOnlineHour : public CBaseDlg
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
