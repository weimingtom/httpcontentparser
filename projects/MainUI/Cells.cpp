// Cells.cpp : 实现文件
//

#include "stdafx.h"
#include "Cells.h"
#include ".\cells.h"
#include "resource.h"

// CCells

IMPLEMENT_DYNAMIC(CCells, CWnd)
CCells::CCells()
{
}

CCells::~CCells()
{
}


BEGIN_MESSAGE_MAP(CCells, CWnd)
END_MESSAGE_MAP()



// CCells 消息处理程序
BOOL CCells::PreCreateWindow(CREATESTRUCT& cs) {
	cs.style = WS_CHILD;
	return CWnd::PreCreateWindow(cs);
}

void CCells::check(const int row, const int col) {
	cells[row][col].check();
}

void CCells::uncheck(const int row, const int col) {
	cells[row][col].uncheck();
}
BOOL CCells::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
					const RECT& rectwindows, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	BOOL bResult =  CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rectwindows, pParentWnd, nID, pContext);

	int id = IDC_CELL_BEGIN;
	CRect rect(rectwindows);
	rect.left = 0; rect.top = 0;
	rect.right = rect.left + ItemWidth;
	rect.bottom = rect.top + ItemHeight;
	for (int row = 0; row < Rows; ++row) {
		for (int col = 0; col < Column; ++col) {
			cells[row][col].Create("", WS_CHILD, rect, this, id++);
			cells[row][col].ShowWindow(SW_SHOW);
			rect.left = rect.right;
			rect.right = rect.left + ItemWidth;
		}

		rect.left = 0;
		rect.top += RowHeight;
		rect.bottom = rect.top + ItemHeight;
		rect.right = rect.left + ItemWidth;
	}
	return bResult;
}
