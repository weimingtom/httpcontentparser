// Cells.cpp : 实现文件
//

#include "stdafx.h"
#include "Cells.h"
#include ".\cells.h"
#include "resource.h"
#include ".\basedlg.h"

// CCells

IMPLEMENT_DYNAMIC(CCells, CWnd)
CCells::CCells() {
	memset(access_netword, 0, sizeof(access_netword));
	m_parentDlg = NULL;
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

void CCells::check(const INT_PTR row, const INT_PTR col) {
	cells[row][col].check();
	access_netword[row][col] = UNACCESSABLE;
}

void CCells::uncheck(const INT_PTR row, const INT_PTR col) {
	cells[row][col].uncheck();
	access_netword[row][col] = ACCESSABLE;
}
BOOL CCells::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
					const RECT& rectwindows, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	BOOL bResult =  CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rectwindows, pParentWnd, nID, pContext);

	INT_PTR id = IDC_CELL_BEGIN;
	CRect rect(rectwindows);
	rect.left = 0; rect.top = 0;
	rect.right = rect.left + ItemWidth;
	rect.bottom = rect.top + ItemHeight;
	for (INT_PTR row = 0; row < Rows; ++row) {
		for (INT_PTR col = 0; col < Column; ++col) {
			cells[row][col].Create("", WS_CHILD, rect, this, id++);
			cells[row][col].ShowWindow(SW_SHOW);
			cells[row][col].setParentDlg(m_parentDlg);

			rect.left = rect.right;
			if (col  == 11) {
				rect.left += MiddleLine_1;
			} else if (col == 5 || col == 17) {
				rect.left += MiddleLine_2;
			}
			rect.right = rect.left + ItemWidth;
		}

		rect.left = 0;
		rect.top += RowHeight;
		rect.bottom = rect.top + ItemHeight;
		rect.right = rect.left + ItemWidth;
	}
	return bResult;
}

void  CCells::prepareForEnum() {
	for (INT_PTR row = 0; row < Rows; ++row) {
		for (INT_PTR col = 0; col < Column; ++col) {
			if (cells[row][col].isChecked() == true) {
				access_netword[row][col] = UNACCESSABLE;
			} else {
				access_netword[row][col] = ACCESSABLE;
			}
		}
	}
}

void CCells::StarEnum(Enumerator2<INT_PTR, INT_PTR> *enumerate) {
	prepareForEnum();

	for (INT_PTR i = 0; i < Rows; ++i) {
		for (INT_PTR j = 0; j < Column; ++j) {
			if (access_netword[i][j] == UNACCESSABLE) {
				enumerate->Enum(i, j);
			}
		}
	}
}
