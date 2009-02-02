#pragma once


// CDlgImageBrowser �Ի���
#include "ThumbCtrl.h"

// class CDlgImageBrowser
// ���ཫ��ʾĳ��Ŀ¼�����е�ͼƬ
class CDlgImageBrowser : public CDialog
{
	DECLARE_DYNAMIC(CDlgImageBrowser)

public:
	CDlgImageBrowser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgImageBrowser();

	// �Ի�������
	enum { IDD = IDD_DLG_IMAGEBROWSER };


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

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();

	// ·��
	CString m_imageDir;
};
