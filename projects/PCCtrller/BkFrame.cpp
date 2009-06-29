#include "stdafx.h"
#include ".\bkframe.h"
#include ".\PWDChkDlg.h"
#include <logger\logger.h>
#include <logger\loggerlevel.h>
#include "lockutility.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CLASSNAME_BKGRD		TEXT("BKGRDFAM")

#define WM_MY_SHOWLDG		(WM_USER + 0x101)

// CMainFrame

IMPLEMENT_DYNAMIC(CBkFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CBkFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_MESSAGE(WM_MY_SHOWLDG, OnShowDlg)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


CBkFrame::CBkFrame(void)
{
	m_bDlgShown = FALSE;
}

CBkFrame::~CBkFrame(void)
{
}

BOOL CBkFrame::Create() {
	CRect rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 100;
	rect.bottom = 200;
	const DWORD style = WS_VISIBLE | WS_MAXIMIZE | WS_POPUP ;
	return CreateEx(WS_EX_TOPMOST, NULL , NULL, style,  rect, NULL, NULL);
}

int CBkFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	LockScreen();
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	else {
		return 0;
	}
}



#ifdef _DEBUG
void CBkFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CBkFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

LRESULT CBkFrame::OnShowDlg(WPARAM wParam, LPARAM lParam) {
	if (FALSE == m_bDlgShown) {
		m_bDlgShown = TRUE;
		CPWDChkDlg dlg;
		dlg.DoModal();

		// 关闭
		DestroyWindow();
	}
	return -1;
}

BOOL CBkFrame::OnEraseBkgnd(CDC* pDC)
{
	CBrush backBrush(RGB(0, 78, 152));
    CBrush* pOldBrush = pDC->SelectObject(&backBrush);
    CRect rect;
    pDC->GetClipBox(&rect);     // 擦掉所要画的区域
    pDC->PatBlt(rect.left, rect.top, rect.Width(), 
    rect.Height(), PATCOPY);
    pDC->SelectObject(pOldBrush);
    return TRUE;
}

void CBkFrame::OnSize(UINT nType, int cx, int cy)
{
	PostMessage(WM_MY_SHOWLDG, 0, 0);
	CFrameWnd::OnSize(nType, cx, cy);
}

void CBkFrame::OnDestroy()
{
	CFrameWnd::OnDestroy();
	UnlockScreen();
}
