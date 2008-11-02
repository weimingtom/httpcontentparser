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

	virtual int OnApply();
	virtual void OnShow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
	
	virtual BOOL OnInitDialog();
	void restoreSetting();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();

	// controls
	CGuiGroupBox m_staAfterTerm;
	CGuiGroupBox m_staEyecare;
	CGuiGroupBox m_staState;
	CEdit m_edtEnterTime;
	CEdit m_edtRestTime;
	CString m_strCurrentState;
	CString m_strTimeLeft;
	int m_nEnterTime;
	int m_nEyecareTime;
public:
	
	// ����Eyecare �������״̬
	void setEyecareTerminatedMode();

	// ����ʱ����
	void setEyecareTimespan();

	void UpdateState();
	
	
	afx_msg void OnBnClickedRadJustResetTimer();
	afx_msg void OnBnClickedRadEnterSuMode();
	afx_msg void OnEnChangeEdtResttime();
	afx_msg void OnEnChangeEdtEntertime();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
