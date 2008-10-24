#pragma once
#include "afxwin.h"
#include <Guilib1.5\GuiEdit.h> 
#include <Guilib1.5\GuiGroupBox.h>
#include <Guilib1.5\GuiButton.h>

// CDlgChangePassword 对话框

class CDlgChangePassword : public CDialog
{
	DECLARE_DYNAMIC(CDlgChangePassword)

public:
	CDlgChangePassword(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgChangePassword();

// 对话框数据
	enum { IDD = IDD_CHANGE_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// controls values
	CString m_strOrgin;
	CString m_strNew;
	CString m_strRetype;

	CEdit m_edtOrgin;
	CEdit m_edtNew;
	CEdit m_edtRetry;
	CButton m_btnOk;
	CButton m_btnCancel;
	HICON m_hIcon;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

private:
	bool checkOriginalPassword();
	bool validate();
	void resetFileds();
public:
	afx_msg HCURSOR OnQueryDragIcon();
};
