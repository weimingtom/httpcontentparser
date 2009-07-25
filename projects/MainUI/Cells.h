#ifndef _MAINUI_CELLS_H__
#define _MAINUI_CELLS_H__

// CCells
#include "FrameButton.h"
#include <Enumerate.h>

class CBaseDlg;

class CCells : public CWnd {
DECLARE_DYNAMIC(CCells)
public:
	CCells();
	virtual ~CCells();

	enum {
		ACCESSABLE = 0,
		UNACCESSABLE
	};

	void setParentDlg(CBaseDlg * mParentDlg) {
		m_parentDlg = mParentDlg;
	}

private:
	CBaseDlg *m_parentDlg;
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	static const INT_PTR Rows = 7;
	static const INT_PTR Column = 24;

	static const INT_PTR ItemWidth = 13;
	static const INT_PTR ItemHeight = 24;
	static const INT_PTR RowHeight  = 25;
	static const INT_PTR MiddleLine_1  = 4;
	static const INT_PTR MiddleLine_2  = 2;
	CFrameButton cells[Rows][Column];
	INT_PTR	access_netword[Rows][Column];
public: 
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName,
		DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

	void check(const INT_PTR row, const INT_PTR col);
	void uncheck(const INT_PTR row, const INT_PTR col);

// enum function
public:
	void StarEnum(Enumerator2<INT_PTR, INT_PTR> *enumerate);
private:
	void prepareForEnum();
};

#endif  // _MAINUI_CELLS_H__

