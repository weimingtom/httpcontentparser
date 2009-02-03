#pragma once
#include "afxcmn.h"


// CDlgWebsites 对话框

class CDlgWebsites : public CDialog
{
	DECLARE_DYNAMIC(CDlgWebsites)

public:
	CDlgWebsites(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgWebsites();

// 对话框数据
	enum { IDD = IDD_DLG_WEBSITES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_list;
	

private:
	void initializeList();
};
