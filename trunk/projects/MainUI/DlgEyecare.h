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

	virtual void OnRestore();
	virtual void OnApply();
	virtual void OnShow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
	
	virtual BOOL OnInitDialog();

	void initializeSetting();

	// controls
	CGuiGroupBox m_staAfterEyecareTerminate;
	CGuiGroupBox m_staEyecare;
	CGuiGroupBox m_staPwd;
	CButton m_chkUseSuPwd;
	CButton m_btnResetPwd;
	CButton m_btnSetPwd;
	CEdit m_edtPwd;
	CEdit m_edtRetry;
	CEdit m_edtEnterTime;
	CEdit m_edtRestTime;
	CString m_strRetryPwd;
	CString m_strPassword;
	
	int m_nEnterTime;
	int m_nEyecareTime;
	BOOL m_bUseSUPWD;
public:
	afx_msg void OnBnClickedChkUseSupwd();	
	afx_msg void OnBnClickedBtnReset();
	

	// �������봰�ڵĶԻ���
	void SetPwdEditState();	
	int m_nAfterEyecareTerminate;
};
