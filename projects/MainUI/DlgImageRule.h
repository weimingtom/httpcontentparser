#pragma once
#include ".\basedlg.h"
#include "afxwin.h"
// CDlgImageRule �Ի���

class CDlgImageRule : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgImageRule)

public:
	CDlgImageRule(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgImageRule();

// �Ի�������
	enum { IDD = IDD_DLG_IMAGERULES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CButton m_chkImage;
	CButton m_chkShowImage;
	CButton m_chkJPEG;
	CButton m_chkGIF;
	CButton m_chkBMP;
	CButton m_chkPNG;
};
