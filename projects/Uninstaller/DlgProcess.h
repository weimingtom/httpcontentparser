#pragma once
#include "afxcmn.h"


// CDlgProcess �Ի���

class CDlgProcess : public CDialog
{
	DECLARE_DYNAMIC(CDlgProcess)

public:
	CDlgProcess(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgProcess();

// �Ի�������
	enum { IDD = IDD_DLG_PROCESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

private:
	HICON m_hIcon;
	CProgressCtrl m_process;

	friend UINT __cdecl Process( LPVOID pParam );
};
