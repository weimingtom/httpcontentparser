#pragma once

#include ".\basedlg.h"
#include "afxwin.h"
// CLev1DlgTools �Ի���

class CLev1DlgTools : public CBaseDlg
{
	DECLARE_DYNAMIC(CLev1DlgTools)

public:
	CLev1DlgTools(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLev1DlgTools();

	virtual std::string getHelpLink() const;

// �Ի�������
	enum { IDD = IDD_LEV1_TOOLS };

	virtual int OnApply();
	virtual void OnShow();
protected:
	virtual void restoreSetting();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
