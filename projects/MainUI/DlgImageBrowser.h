#pragma once


// CDlgImageBrowser 对话框
#include "ThumbCtrl.h"
#include ".\popupdialog.h"

// class CDlgImageBrowser
// 此类将显示某个目录下所有的图片
class CDlgImageBrowser : public CPopupDialog
{
	DECLARE_DYNAMIC(CDlgImageBrowser)

public:
	CDlgImageBrowser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgImageBrowser();

	// 对话框数据
	enum { IDD = IDD_POPDLG_IMAGEBROWSER };


	// 设置图片目录
	void setImageDir(const CString &path) {
		m_imageDir = path;
	}

	// 此函数负责获取路径，并将路径存放在controls当中
	void initImageControl();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	CThumbCtrl * m_ThumbCtrl;
	DECLARE_MESSAGE_MAP()

	afx_msg INT_PTR OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();

	// 路径
	CString m_imageDir;
	HICON m_hIcon;
};
