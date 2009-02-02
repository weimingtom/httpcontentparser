#if !defined(AFX_THUMBCTRL_H__E9716C23_539B_4D21_8E6B_04B78D9BE276__INCLUDED_)
#define AFX_THUMBCTRL_H__E9716C23_539B_4D21_8E6B_04B78D9BE276__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThumbView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CThumbCtrl view
#define WM_UPDATE_IMAGEDATA	WM_USER + 100

class CThumbCtrl : public CListCtrl
{
public:
	CThumbCtrl(int ThumbWidth=100, int ThumbHeight=100);           // protected constructor used by dynamic creation
	virtual ~CThumbCtrl();
	DECLARE_DYNCREATE(CThumbCtrl)

// Attributes
public:
	// Thread parameter.
	struct tagParameter{
		HWND hListView;
		HIMAGELIST hImageList;
		CThumbCtrl * Parent;
	};
	class CThreadPool * pThreadInPool, * pThreadOutPool;

// Operations
public:
	int InsertItem(int nItem, LPCTSTR lpszFileName);
	int m_Margin;
	int m_ThumbHeight;
	int m_ThumbWidth;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThumbCtrl)
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	CWinThread * m_pThread;

	HANDLE m_StopEvent;
	HANDLE m_ExitEvent;

	// This critical section ensures that it will not exit when we checking m_StopEvent, so
	// that avoid when we check m_ExitEvent and set m_StopEvent, it exit and left the 
	// m_StopEvent to next loop.
	CRITICAL_SECTION m_CSExitCheck;
	// This critical section ensure the additional thread are not decided to exit when we
	// check m_ExitEvent, so can avoid that we thought it is not exit, but it will exit 
	// right now.
	CRITICAL_SECTION m_CSSetStop;
	CRITICAL_SECTION m_CSNeitherInBothPoolSection;

	static UINT ImageRendering(LPVOID);		// Additional thread
	void KillRenderingThread();

	CImageList m_ImageList;
	CImageList m_BackupImageList;

	//{{AFX_MSG(CThumbCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteAllItems(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg LRESULT OnUpdateImageData(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THUMBCTRL_H__E9716C23_539B_4D21_8E6B_04B78D9BE276__INCLUDED_)
