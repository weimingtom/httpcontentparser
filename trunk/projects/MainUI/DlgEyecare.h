#pragma once

#include ".\basedlg.h"

// CDlgEyecare �Ի���

class CDlgEyecare : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgEyecare)

public:
	CDlgEyecare(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgEyecare();

// �Ի�������
	enum { IDD = IDD_DLG_EYECARE };

	virtual void OnApply();
	virtual void OnShow();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
