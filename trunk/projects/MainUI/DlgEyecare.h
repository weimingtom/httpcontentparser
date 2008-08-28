#pragma once

#include ".\basedlg.h"
#include <Guilib1.5\GuiCheckBox.h>
#include <Guilib1.5\GuiGroupBox.h>
#include <Guilib1.5\GuiEdit.h>
#include <Guilib1.5\GuiButton.h>
#include <Guilib1.5\GuiEdit.h>
#include "afxwin.h"
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
	
	virtual BOOL OnInitDialog();

	// controls
	CGuiGroupBox m_staEyecare;
	CGuiGroupBox m_staPwd;
	CGuiCheckBox m_chkUseSuPwd;
	CGuiButton m_btnResetPwd;
	CGuiButton m_btnSetPwd;
	CGuiEdit m_edtPwd;
	CGuiEdit m_edtRetry;
	CGuiEdit m_edtEnterTime;
	CGuiEdit m_edtRestTime;
	CString m_strRetryPwd;
	CString m_strPassword;
public:
	afx_msg void OnBnClickedChkUseSupwd();	
	afx_msg void OnBnClickedBtnReset();
	int m_nEntertainTime;
	int m_nRestTime;
};
