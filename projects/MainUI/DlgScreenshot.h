#ifndef _MAINUI_CDLGSCREENSAVER_H__
#define _MAINUI_CDLGSCREENSAVER_H__

#include ".\basedlg.h"
#include "afxwin.h"
#include "afxcmn.h"

// CDlgScreenshot 对话框

class CDlgScreenshot : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgScreenshot)

public:
	CDlgScreenshot(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgScreenshot();

	virtual std::string getHelpLink() const;

// 对话框数据
	enum { IDD = IDD_DLG_SCREENSHOT };

	virtual int OnApply();
	virtual void OnShow();

protected:
	virtual void restoreSetting();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_staFunction;
	CStatic m_staTimespan;
	CStatic m_staAutoClear;
	CSliderCtrl m_sliderSaveTimespan;
	CSliderCtrl m_sliderAutoclearTimespan;
	
	BOOL m_bEnableScreensave;
	BOOL m_bEnableAutoclean;

	CString m_strAutoCleanHours;
	CString m_strTimespanMins;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedChkScreensave();
	afx_msg void OnBnClickedChkAutoclean();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
protected:
	void enableAutoSave();
	void enableAutoclean();

	void setAutoCleanTips();
	void setTimespanTips();
public:
	afx_msg void OnBnClickedViewHistory();
};

#endif  // _MAINUI_CDLGSCREENSAVER_H__