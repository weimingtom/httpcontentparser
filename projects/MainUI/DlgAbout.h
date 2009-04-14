#pragma once
#include ".\basedlg.h"
#include "afxwin.h"
#include  ".\Guilib1.5\GuiGroupBox.h"
#include ".\HyperLink.h"

// CDlgAbout �Ի���

class CDlgAbout : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgAbout)

public:
	CDlgAbout(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAbout();

// �Ի�������
	enum { IDD = IDD_DLG_ABOUT };

protected:
	virtual int OnApply();
	virtual void OnShow();
	virtual void restoreSetting() {}
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	afx_msg void OnBnClickedRegister();
	DECLARE_MESSAGE_MAP()

	CGuiGroupBox m_staAbout;
	
	CHyperLink m_sWebURL;
	CHyperLink m_sEmail;
	CHyperLink m_sMailList;
public:
	virtual BOOL OnInitDialog();
};
