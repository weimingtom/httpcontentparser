#pragma once
#include ".\basedlg.h"
#include "afxwin.h"
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

	DECLARE_MESSAGE_MAP()
public:
	CGuiGroupBox m_staAbout;
};
