#pragma once


// CDlgImageBrowser �Ի���
#include "ThumbCtrl.h"
#include ".\popupdialog.h"

// class CDlgImageBrowser
// ���ཫ��ʾĳ��Ŀ¼�����е�ͼƬ
class CDlgImageBrowser : public CPopupDialog
{
	DECLARE_DYNAMIC(CDlgImageBrowser)

public:
	CDlgImageBrowser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgImageBrowser();

	// �Ի�������
	enum { IDD = IDD_POPDLG_IMAGEBROWSER };


	// ����ͼƬĿ¼
	void setImageDir(const CString &path) {
		m_imageDir = path;
	}

	// �˺��������ȡ·��������·�������controls����
	void initImageControl();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	CThumbCtrl * m_ThumbCtrl;
	DECLARE_MESSAGE_MAP()

	afx_msg INT_PTR OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();

	// ·��
	CString m_imageDir;
	HICON m_hIcon;
};
