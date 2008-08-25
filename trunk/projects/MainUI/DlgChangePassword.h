#pragma once
#include "afxwin.h"
#include <Guilib1.5\GuiEdit.h> 
#include <Guilib1.5\GuiGroupBox.h>
#include <Guilib1.5\GuiButton.h>

// CDlgChangePassword �Ի���

class CDlgChangePassword : public CDialog
{
	DECLARE_DYNAMIC(CDlgChangePassword)

public:
	CDlgChangePassword(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgChangePassword();

// �Ի�������
	enum { IDD = IDD_CHANGE_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// controls values
	CString m_strOrgin;
	CString m_strNew;
	CString m_strRetype;

	CGuiEdit m_edtOrgin;
	CGuiEdit m_edtNew;
	CGuiEdit m_edtRetry;
	CGuiButton m_btnOk;
	CGuiButton m_btnCancel;
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
