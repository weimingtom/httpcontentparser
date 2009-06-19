#pragma once
#include ".\basedlg.h"
#include "afxwin.h"
#include "afxcmn.h"

// CDlgImageRule 对话框

class CDlgImageRule : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgImageRule)

public:
	CDlgImageRule(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgImageRule();

	virtual std::string getHelpLink() const;

// 对话框数据 
	enum { IDD = IDD_DLG_IMAGERULES };

	virtual int OnApply();
	virtual void OnShow();
protected:
	virtual void restoreSetting();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
protected:
	CButton m_chkJPEG;
	CButton m_chkGIF;
	CButton m_chkBMP;
	CButton m_chkPNG;
	
	CStatic m_staImageCheck;
	CStatic m_staImageSize;
	CStatic m_staImageType;
	CSliderCtrl m_sliderImageCheckDegree;
	CEdit m_editMin;
	CEdit m_editMax;
	CButton m_chkEnableScopeCheck;
	CSpinButtonCtrl m_spinBtnMin;
	CSpinButtonCtrl m_spinBtnMax;

	BOOL m_bCheckGIF;
	BOOL m_bCheckJPEG;
	BOOL m_bCheckBMP;
	BOOL m_bCheckPNG;

	long scope_min_;
	long scope_max_;
public:
	afx_msg void OnBnClickedChkJpeg();
	afx_msg void OnBnClickedChkGif();
	afx_msg void OnBnClickedChkBmp();
	afx_msg void OnBnClickedChkPng();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedChkEnableSizeCheck();
protected:
	// 使相关控件可用
	void enableScopeCheck(bool enabled);
	void ApplyCOMService();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
