#pragma once
#include "afxcmn.h"


// CDlgWebsites �Ի���

class CDlgWebsites : public CDialog
{
	DECLARE_DYNAMIC(CDlgWebsites)

public:
	CDlgWebsites(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgWebsites();

// �Ի�������
	enum { IDD = IDD_DLG_WEBSITES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_list;
	

private:
	void initializeList();
};
