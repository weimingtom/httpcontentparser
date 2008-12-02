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
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
private:
	bool checkOriginalPassword();
	bool validate();
	void resetFileds();
private:
	// �˾�̬�������ڱ�ʶ�Ի����Ƿ��
	// ��OninitiDialog��OnDestory��ʹ��
	// ʹ��int���ͣ��������ڴ򿪵Ļ�����ÿ�ε���OnInitialize-1, ����OnDestory�ͼ���
	// ��ʵ��boolean�ǲ��е�.
	static int static_dlg_show_cnt;
};