#pragma once
#include "afxcmn.h"


// CDlgProcess 对话框

class CDlgProcess : public CDialog
{
	DECLARE_DYNAMIC(CDlgProcess)

public:
	CDlgProcess(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgProcess();

// 对话框数据
	enum { IDD = IDD_DLG_PROCESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

private:
	HICON m_hIcon;
	CProgressCtrl m_process;

	friend UINT __cdecl Process( LPVOID pParam );
};
