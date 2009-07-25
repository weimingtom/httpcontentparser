// FrameButton.cpp : 实现文件
//

#include "stdafx.h"

#include ".\framebutton.h"
#include ".\resource.h"
#include ".\basedlg.h"

// CFrameButton

IMPLEMENT_DYNAMIC(CFrameButton, CButton)
CFrameButton::CFrameButton()
{
	m_bCheckBtn = FALSE;
	m_bPressBtn = FALSE;
	m_bOldTemp  = FALSE;
	m_clrHigh   = ::GetSysColor(COLOR_HIGHLIGHT);
	m_clrCheck  = RGB(0, 170, 170);
	m_bSelected = FALSE;
	m_parentDlg_ = NULL;
}

CFrameButton::~CFrameButton()
{
}


BEGIN_MESSAGE_MAP(CFrameButton, CButton)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CFrameButton 消息处理程序


void CFrameButton::PreSubclassWindow() {
	ModifyStyle(0, BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}

void CFrameButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {
	CDC *pDC         = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect m_rcClient(lpDrawItemStruct->rcItem);
	UINT m_State     = lpDrawItemStruct->itemState;
	CBrush cb;
	CRect m_rcTemp(m_rcClient);
	CPoint pt;
	CSize  m_Csize;
	CString m_szCaption;


	COLORREF m_Over = RGB(255, 193, 111);
	CPen cpOver(PS_SOLID, 1, RGB(255, 193, 111));
	INT_PTR iMode      = pDC->SetBkMode(TRANSPARENT);
	INT_PTR iExtile    = GetButtonStyle();

	// draw frame of checkbox
	pDC->Draw3dRect(m_rcTemp, m_clrHigh, m_clrHigh);
	m_rcTemp.DeflateRect(1, 1);
	DrawOrange(pDC, m_rcTemp);
	m_rcTemp.DeflateRect(1, 1);
	if (lpDrawItemStruct->itemState & ODS_DISABLED)
		pDC->DrawState(pt, m_Csize, m_szCaption, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
	else 
	{	   		
		if (lpDrawItemStruct->itemState & ODS_SELECTED)
		{
			if (m_bOldTemp == TRUE)
				DrawCheck(pDC, m_rcTemp);
		}
		else
		{
			if (m_bCheckBtn == TRUE && m_bPressBtn == FALSE)
				DrawCheck(pDC, m_rcTemp);
			else
			{
				if (m_bOldTemp == TRUE && m_bPressBtn == TRUE)
					DrawCheck(pDC, m_rcTemp);
			}
		}
	}
}

void CFrameButton::DrawOrange(CDC* pDC, CRect m_rcTemp)
{
	if (m_bSelected== TRUE)
	{
		for (INT_PTR i = 0; i < 2; i++)
		{
			COLORREF m_Over = RGB(255, 193+ (i + 10), 111+ (i + 10));
			pDC->Draw3dRect(m_rcTemp, m_Over, m_Over);
			m_rcTemp.DeflateRect(1, 1);
		}
		m_rcTemp.InflateRect(2, 2);
		pDC->SetPixel(m_rcTemp.left + 1, m_rcTemp.top + 2,::GetSysColor(COLOR_3DHIGHLIGHT));
		pDC->SetPixel(m_rcTemp.left + 1, m_rcTemp.top + 3, RGB(255, 220, 185));
		pDC->SetPixel(m_rcTemp.left + 1, m_rcTemp.top + 4, RGB(255, 220, 185));
		pDC->SetPixel(m_rcTemp.left + 1, m_rcTemp.top + 5, RGB(255, 220, 185));
		pDC->SetPixel(m_rcTemp.left + 1, m_rcTemp.top + 6, RGB(255, 220, 185));
		pDC->SetPixel(m_rcTemp.left + 2, m_rcTemp.top, RGB(255, 220, 185));
		pDC->SetPixel(m_rcTemp.left + 3, m_rcTemp.top, RGB(255, 220, 185));
		pDC->SetPixel(m_rcTemp.left + 4, m_rcTemp.top, RGB(255, 220, 185));
		pDC->SetPixel(m_rcTemp.left + 5, m_rcTemp.top, RGB(255, 220, 185));
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top, RGB(254, 225, 158));
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top + 1, RGB(255, 255, 255));
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top + 2, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top + 3, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top + 4, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top + 5, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top + 6, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top + 7, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top + 8, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top + 9, RGB(255, 243, 217));
		
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top, RGB(254, 255, 255));
		pDC->SetPixel(m_rcTemp.left + 1, m_rcTemp.top, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left + 2, m_rcTemp.top, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left + 3, m_rcTemp.top, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left + 4, m_rcTemp.top, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left + 5, m_rcTemp.top, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left + 6, m_rcTemp.top, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left + 7, m_rcTemp.top, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top + 1, RGB(254, 255, 255));
		pDC->SetPixel(m_rcTemp.left + 1, m_rcTemp.top + 1, RGB(254, 220, 139));
		pDC->SetPixel(m_rcTemp.left + 2, m_rcTemp.top + 1, RGB(254, 220, 139));
		pDC->SetPixel(m_rcTemp.left + 3, m_rcTemp.top + 1, RGB(254, 220, 139));
		pDC->SetPixel(m_rcTemp.left + 4, m_rcTemp.top + 1, RGB(254, 220, 139));
		pDC->SetPixel(m_rcTemp.left + 5, m_rcTemp.top + 1, RGB(254, 220, 139));
		pDC->SetPixel(m_rcTemp.left + 6, m_rcTemp.top + 1, RGB(254, 220, 139));
		pDC->SetPixel(m_rcTemp.left + 7, m_rcTemp.top + 1, RGB(254, 220, 139));
	}
	else
	{ 
		CBrush cbSelec;
		cbSelec.CreateSysColorBrush(COLOR_3DHILIGHT);
		pDC->FillRect(m_rcTemp, &cbSelec);
	}
}

void CFrameButton::DrawCheck(CDC* pDC, CRect rect)
{
	// 左上两条线
	rect.DeflateRect(0, 0, 2, 1);
	INT_PTR left = rect.left, top = rect.top;
	INT_PTR right = rect.right, bottom = rect.bottom-1;
	CPen pen(PS_SOLID, 1, RGB(172,222,160));
	pDC->SelectObject(&pen);
	pDC->MoveTo(left, top);
	pDC->LineTo(left, bottom);
	pDC->MoveTo(left, top);
	pDC->LineTo(right, top);
	left ++;top++;

	right--;
	CPen pen2(PS_SOLID, 1, RGB(177,191,72));
	pDC->SelectObject(&pen2);
	pDC->MoveTo(left, top);
	pDC->LineTo(left, bottom);
	pDC->MoveTo(left, top);
	pDC->LineTo(right, top);
	left ++;top++;

	CPen pen3(PS_SOLID, 1, RGB(67,195,63));
	pDC->SelectObject(&pen3);
	pDC->MoveTo(left, top);
	pDC->LineTo(left, bottom);
	pDC->MoveTo(left, top);
	pDC->LineTo(right, top);
	left ++;top++;

	CPen pen4(PS_SOLID, 1, RGB(34,162,32));
	pDC->SelectObject(&pen4);
	pDC->MoveTo(left, top);
	pDC->LineTo(left, bottom);
	pDC->MoveTo(left, top);
	pDC->LineTo(right, top);
	left ++;top++;

	pDC->MoveTo(left, top);
	pDC->LineTo(left, bottom);
	pDC->MoveTo(left, top);
	pDC->LineTo(right, top);
	left ++;top++;

	pDC->MoveTo(left, top);
	pDC->LineTo(left, bottom);
	pDC->MoveTo(left, top);
	pDC->LineTo(right, top);
	left ++;top++;

	pDC->MoveTo(left, top);
	pDC->LineTo(left, bottom);
	pDC->MoveTo(left, top);
	pDC->LineTo(right, top);
	left ++;top++;

	CPen pen5(PS_SOLID, 1, RGB(67,195,63));
	pDC->SelectObject(&pen5);
	pDC->MoveTo(rect.right-1, rect.top+1);
	pDC->LineTo(rect.right-1, rect.bottom);
	pDC->LineTo(rect.left+1, rect.bottom);
	left ++;top++;

	// 右下的框
	CPen pen6(PS_SOLID, 1, RGB(177,191,72));
	pDC->SelectObject(&pen6);
	pDC->MoveTo(rect.right, rect.top+1);
	pDC->LineTo(rect.right, rect.bottom-1);
	pDC->LineTo(rect.left, rect.bottom-1);
}
void CFrameButton::OnTimer(UINT nIDEvent)
{
	CRect m_rect;
	GetClientRect(&m_rect);
	CPoint pt(GetMessagePos());
	ScreenToClient(&pt);
	if (!m_rect.PtInRect(pt))
	{
		m_bPressBtn = TRUE;
		m_bSelected = FALSE;

		Invalidate();
		UpdateWindow();
		KillTimer(1);
	}	
	CButton::OnTimer(nIDEvent);
}

void CFrameButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	CButton::OnLButtonDown(nFlags, point);
	m_bPressBtn = TRUE;
	m_bOldTemp = m_bCheckBtn;
	Invalidate();
	UpdateWindow();
	KillTimer(1);
	SetTimer(1, 10, NULL);

	// 硬编码
	if (m_parentDlg_ != NULL) {
		m_parentDlg_->SetModify(true);
	}
}

void CFrameButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	CButton::OnLButtonUp(nFlags, point);
	CRect m_rect;
	GetClientRect(&m_rect);
	if (m_rect.PtInRect(point))
	{
		if (m_bCheckBtn == TRUE)
			m_bCheckBtn = FALSE;
		else 
			m_bCheckBtn = TRUE;
		m_bOldTemp = m_bCheckBtn;
		m_bPressBtn = FALSE;
		m_bSelected =FALSE;	
		KillTimer(1);
		SetTimer(1, 100, NULL);
		
		Invalidate();
		UpdateWindow();
	}
}

void CFrameButton::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect m_rect;
	GetClientRect(&m_rect);
	if (m_bSelected == TRUE)
		return;
	if (m_rect.PtInRect(point))
	{
		m_bSelected =TRUE;
		Invalidate();
		UpdateWindow();
		SetTimer(1, 100, NULL);
	}
	CButton::OnMouseMove(nFlags, point);
}

BOOL CFrameButton::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return FALSE;
}


INT_PTR CFrameButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}
