#pragma once
#include ".\basedlg.h"

// CDlgSearchRule �Ի���

class CDlgSearchRule : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgSearchRule)

public:
	CDlgSearchRule(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSearchRule();

// �Ի�������
	enum { IDD = IDD_DLG_SEARCH_RULE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
