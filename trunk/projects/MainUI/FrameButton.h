#pragma once


// CFrameButton

class CFrameButton : public CButton {
	DECLARE_DYNAMIC(CFrameButton)

public:
	CFrameButton();
	virtual ~CFrameButton();
public:
	void DrawCheck(CDC* pDC, CRect m_rcTemp);	
	void DrawOrange(CDC* pDC, CRect m_rcTemp);	
	
	void check() {
		m_bCheckBtn = TRUE;
		m_bOldTemp = TRUE;
	}

	void uncheck() {
		m_bCheckBtn = FALSE;
		m_bOldTemp = FALSE;
	}
public:
	BOOL         m_bCheckBtn;
	BOOL         m_bPressBtn;
	BOOL         m_bOldTemp;
	COLORREF     m_clrHigh;
	COLORREF     m_clrCheck;
	BOOL         m_bSelected;
	
protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
public:
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


