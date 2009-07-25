#pragma once
#include ".\basedlg.h"
#include ".\Guilib1.5\GuiListEdit.h"
#include ".\Guilib1.5\GuiDropDownEdit.h"
#include <Enumerate.h>
#include <string>
#include "afxwin.h"
#include ".\ContentList.h"

// CDlgSearchRule �Ի���
class CDlgSearchRule : public CBaseDlg, RuleChanged {
	DECLARE_DYNAMIC(CDlgSearchRule)

public:
	CDlgSearchRule(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSearchRule();

	virtual std::string getHelpLink() const;

// �Ի�������
	enum { IDD = IDD_DLG_SEARCH_RULE };

	virtual INT_PTR OnApply();
	virtual void OnShow();

	virtual BOOL OnInitDialog();
protected:
	// ��ʼ����ʼ����
	virtual void restoreSetting();

	CGuiListEdit ListBox;
	CButton m_chkEnableSearchChk;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()

	// control variable
	BOOL m_bEnableSearchRule;
	BOOL m_bChkGoogle;
	BOOL m_bChkYahoo;
	BOOL m_bChkBaidu;
public:
	virtual void OnAddItem(const CString &str);
	virtual void OnDelItem(const CString &str);
	virtual bool ValidateItem(const CString & str, CString &output);
	RulesList  rules;
	afx_msg void OnBnClickedChkEnableSearch();
	afx_msg void OnBnClickedChkGoogle();
	afx_msg void OnBnClickedChkYahoo();
	afx_msg void OnBnClickedChkBaidu();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
