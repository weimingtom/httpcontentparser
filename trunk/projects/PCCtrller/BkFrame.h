#pragma once

#include "stdafx.h"

class CBkFrame :  public CFrameWnd
{
	DECLARE_DYNAMIC(CBkFrame)

public:
	CBkFrame(void);
	virtual ~CBkFrame(void);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg LRESULT OnShowDlg(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

protected:
	BOOL m_bDlgShown;
public:
	BOOL Create();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
	afx_msg void OnDestroy();
};
