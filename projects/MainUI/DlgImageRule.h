#pragma once
#include ".\basedlg.h"
#include "afxwin.h"
// CDlgImageRule 对话框

class CDlgImageRule : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgImageRule)

public:
	CDlgImageRule(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgImageRule();

// 对话框数据
	enum { IDD = IDD_DLG_IMAGERULES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_chkImage;
	CButton m_chkShowImage;
	CButton m_chkJPEG;
	CButton m_chkGIF;
	CButton m_chkBMP;
	CButton m_chkPNG;
};
