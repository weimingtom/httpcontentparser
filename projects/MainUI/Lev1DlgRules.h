#pragma once


#include ".\basedlg.h"
#include "afxwin.h"


class CLev1DlgRules : public CBaseDlg {
	DECLARE_DYNAMIC(CLev1DlgRules)

public:
	CLev1DlgRules(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLev1DlgRules();

	virtual std::string getHelpLink() const;

// �Ի�������
	enum { IDD = IDD_LEV1_RULE };

	virtual BOOL OnInitDialog();
	virtual int OnApply();
	virtual void OnShow();
protected:
	virtual void restoreSetting();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
