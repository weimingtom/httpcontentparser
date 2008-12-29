#pragma once


// CCells
#include "FrameButton.h"
#include <Enumerate.h>

class CCells : public CWnd {
DECLARE_DYNAMIC(CCells)
public:
	CCells();
	virtual ~CCells();

	enum {
		ACCESSABLE = 0,
		UNACCESSABLE
	};
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	static const int Rows = 7;
	static const int Column = 24;

	static const int ItemWidth = 13;
	static const int ItemHeight = 24;
	static const int RowHeight  = 25;
	CFrameButton cells[Rows][Column];
	int	access_netword[Rows][Column];
public: 
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName,
		DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

	void check(const int row, const int col);
	void uncheck(const int row, const int col);

// enum function
public:
	void StarEnum(Enumerator2<int, int> *enumerate);
private:
	void prepareForEnum();
};


