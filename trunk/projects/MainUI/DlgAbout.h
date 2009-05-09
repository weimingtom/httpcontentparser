#pragma once
#include ".\basedlg.h"
#include "afxwin.h"
#include  ".\Guilib1.5\GuiGroupBox.h"
#include ".\HyperLink.h"

// CDlgAbout 对话框

class CDlgAbout : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgAbout)

public:
	CDlgAbout(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAbout();

	virtual std::string getHelpLink() const;

// 对话框数据
	enum { IDD = IDD_DLG_ABOUT };

protected:
	virtual int OnApply();
	virtual void OnShow();
	virtual void restoreSetting() {}
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg void OnBnClickedRegister();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	DECLARE_MESSAGE_MAP()

	CGuiGroupBox m_staAbout;
	
	CHyperLink m_sWebURL;
	CHyperLink m_sEmail;
	CHyperLink m_sMailList;

	CString m_strRegisterInfo;
	CButton m_btnRegistered;
};
