#pragma once


// CDlgCheckPassword �Ի���
#include "resource.h"

class CDlgCheckPassword : public CDialog
{
	DECLARE_DYNAMIC(CDlgCheckPassword)

public:
	CDlgCheckPassword(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCheckPassword();

// �Ի�������
	enum { IDD = IDD_POPDLG_CHKPASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
