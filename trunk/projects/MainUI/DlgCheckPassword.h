#pragma once

#include <Guilib1.5\GuiEdit.h> 
#include <Guilib1.5\GuiGroupBox.h>
#include <Guilib1.5\GuiButton.h>
#include "afxwin.h"

// CDlgCheckPassword 对话框

class CDlgCheckPassword : public CDialog
{
	DECLARE_DYNAMIC(CDlgCheckPassword)

public:
	CDlgCheckPassword(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCheckPassword();

// 对话框数据
	enum { IDD = IDD_DLG_CHKPASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGuiEdit m_edtPassword;
	CString m_strPassword;
	CGuiButton m_btnOk;
	CGuiButton m_btnCancel;
	HICON m_hIcon;

public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg HCURSOR OnQueryDragIcon();
};
