/****************************************************************************
 *																			*		 
 *								GuiToolKit  								*	
 *							 (MFC extension)								*			 
 * Created by Francisco Campos G. www.beyondata.com fcampos@beyondata.com	*
 *--------------------------------------------------------------------------*		   
 *																			*
 * This program is free software;so you are free to use it any of your		*
 * applications (Freeware, Shareware, Commercial),but leave this header		*
 * intact.																	*
 *																			*
 * These files are provided "as is" without warranty of any kind.			*
 *																			*
 *			       GuiToolKit is forever FREE CODE !!!!!					*
 *																			*
 *--------------------------------------------------------------------------*
 * Created by: Francisco Campos G.											*
 * Bug Fixes and improvements : (Add your name)								*
 * -Francisco Campos														*				
 *																			*	
 ****************************************************************************/

#include "stdafx.h"
#include "GuiListEdit.h"
#include "OnTextChanged.h"
#include "..\resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define  LST_DELETE	555
#define  LST_INSERT 556
#define  LST_UP     557
#define  LST_DOWN   558
#define  LST_LIST	559
#define  DROPBUTTON 560
// CGuiListEdit

IMPLEMENT_DYNAMIC(CGuiListEdit, CStatic)

CGuiListEdit::CGuiListEdit()
{
	m_border=STYLEFRAME;
	m_clrface=GuiDrawLayer::GetRGBColorFace();
	onchanged_ = NULL;
}

CGuiListEdit::~CGuiListEdit()
{
}


BEGIN_MESSAGE_MAP(CGuiListEdit, CStatic)
	ON_COMMAND(LST_DELETE,Delete)
	ON_COMMAND(LST_INSERT,OnInsert)
	ON_COMMAND(LST_UP,Up)
	ON_COMMAND(LST_DOWN,Down)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY(LVN_ENDLABELEDIT, LST_LIST, OnEndlabeleditList)
	ON_NOTIFY(NM_DBLCLK, LST_LIST, OnClickList)
END_MESSAGE_MAP()

// CGuiListEdit message handlers
void CGuiListEdit::Delete()
{
	//solo nos interesa el seleccionado actualmente
	const INT_PTR nItem=m_list->GetNextItem(-1,LVNI_SELECTED);
	OnDelete(GetText(nItem)); // 当被删除时调用，子类可重载
	m_list->DeleteItem(nItem);
}

//当用户点击New时，回被调用
void CGuiListEdit::Insert(CString &itemText)
{
	CRect rc;
	m_list->SetFocus();
	INT_PTR nItem=m_list->GetItemCount();
	nItem=m_list->InsertItem(nItem,_T(""));
	EditItem(nItem, CString(""));
}

void CGuiListEdit::Edit() {
	CRect rc;
	m_list->SetFocus();
	const INT_PTR nItem=m_list->GetNextItem(-1,LVNI_SELECTED);
	CString itemText = GetText(nItem);
	OnBeginEdit(itemText);
	EditItem(nItem, itemText);
}

// 在对应的Items上显示Edit Control, 并显示相应文字以供修改
void CGuiListEdit::EditItem(const INT_PTR nItem, const CString &itemText) {
	CRect rc;
	m_list->SetItemData (nItem, 0);
    m_list->GetItemRect(0,&rc,LVIS_SELECTED | LVIS_FOCUSED);
	CEdit* mEdit=m_list->EditLabel(nItem);
	mEdit->SetWindowText(itemText);
	CSize szBtn=m_toolBtn.GetSizeButton();
	mEdit->SetWindowPos (NULL, -1, -1,
		rc.Width () - 10, rc.Height (),
		SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
}

void CGuiListEdit::OnBeginlabeleditList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

CString CGuiListEdit::GetText(INT_PTR nItem)
{
	if (nItem < 0) return _T("");
	if (nItem > m_list->GetItemCount()) return _T("");
	CString m_szA=m_list->GetItemText(nItem,0);
	return m_szA;
}

INT_PTR CGuiListEdit::GetNumItem()
{
	return m_list->GetItemCount();
}

void CGuiListEdit::OnInsert() {
	Insert(CString(""));
}

bool CGuiListEdit::AddItem(CString szCad) {
	// 首先判断添加啊的内容是否合法
	if (OnAdd(szCad)) {
		INT_PTR nItem=m_list->GetItemCount();
		nItem=m_list->InsertItem(nItem,szCad);
		m_list->SetItemData (nItem, 0);
		return true;
	} else {
		// ASSERT(false);
		return false;
	}
}

void CGuiListEdit::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) {
	INT_PTR nActual=m_list->GetNextItem(-1,LVNI_SELECTED);
	if (nActual == -1) {
		Insert();
	} else {
		Edit();
	}
}

// 在用户结束编辑以后
void CGuiListEdit::OnEndlabeleditList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	LV_ITEM* pItem = &((LV_DISPINFO*)pNMHDR)->item;
	CString itemText=pItem->pszText;
	if (itemText.GetLength() == 0)
		Delete();

	if (!itemText.IsEmpty() && OnEndEdit(itemText)) {
		m_list->SetItemText(pItem->iItem,0,itemText);
	} else {
		// 如果是不符合要求的
		Delete();
	}

	*pResult = 0;
}

void CGuiListEdit::Up()
{
	INT_PTR nActual=m_list->GetNextItem(-1,LVNI_SELECTED);
	if (nActual == -1) return;
	if (nActual > 0)
	{
		CString m_szA=m_list->GetItemText(nActual,0);
		CString m_sz=m_list->GetItemText(nActual-1,0);
		m_list->SetItemText(nActual,0,m_sz);
		m_list->SetItemText(nActual-1,0,m_szA);
		m_list->SetItemState (nActual-1,	LVIS_SELECTED | LVIS_FOCUSED, 
								LVIS_SELECTED | LVIS_FOCUSED);
	}
	m_list->SetFocus();
}

void CGuiListEdit::Down()
{
	INT_PTR nActual=m_list->GetNextItem(-1,LVNI_SELECTED);
	if (nActual == -1) return;

	if (nActual+1 < m_list->GetItemCount())
	{
		CString m_szA=m_list->GetItemText(nActual,0);
		CString m_sz=m_list->GetItemText(nActual+1,0);
		m_list->SetItemText(nActual,0,m_sz);
		m_list->SetItemText(nActual+1,0,m_szA);
		m_list->SetItemState (nActual+1,	LVIS_SELECTED | LVIS_FOCUSED, 
								LVIS_SELECTED | LVIS_FOCUSED);
	}
	m_list->SetFocus();
}


void CGuiListEdit::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0,BS_OWNERDRAW);
	if ( !m_Conta.Create(WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),this,0x9999))
		return ;
	
	m_Conta.AddComponen(&m_MiniTool);
	/*m_toolBtn.Create(_T(""),WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW,CRect(0,0,0,0),this,DROPBUTTON);
	m_toolBtn.SetCaption(_T(" ... "));
	m_toolBtn.SetStyleButton(CGuiNormalButton::STL_SEMIFLAT);
	*/
	
	m_list=(CListCtrl*) m_Conta.AddComponen(RUNTIME_CLASS(CListCtrl),LST_LIST,WS_VISIBLE | WS_CHILD);
	m_MiniTool.SetImageList(IDB_GUI_DOCKBAROFFICE,14,12,RGB(255,0,255));
	m_MiniTool.AddButton(9,LST_DOWN,NULL,_T(""),_T("Item Down"));
	m_MiniTool.AddButton(11,LST_UP,NULL,_T(""),_T("Item Up"));
	m_MiniTool.AddButton(8,LST_DELETE,NULL,_T(""),_T("Delete"));
	m_MiniTool.AddButton(10,LST_INSERT,NULL,_T(""),_T("Insert"));
	m_MiniTool.AutoSize(TRUE);
	m_MiniTool.SetBorder(CGuiMiniTool::STYLEPRESS);
	m_MiniTool.SetCaption(_T("Websites:"),CGuiMiniTool::ALIGN_LEFT);
	m_MiniTool.AlingButtons(CGuiMiniTool::ALIGN_RIGHT);
	m_MiniTool.SetColorCaption(RGB(0,0,0));
	m_list->ModifyStyleEx(0,WS_EX_CLIENTEDGE);
	m_list->ModifyStyle(0,WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_SINGLESEL | 
						LVS_NOCOLUMNHEADER | LVS_EDITLABELS | LVS_SHOWSELALWAYS);
	m_list->SendMessage (LVM_SETEXTENDEDLISTVIEWSTYLE , 0, LVS_EX_FULLROWSELECT);

	m_list->InsertColumn(0,_T(""));
	m_Conta.UsedAllWindow(TRUE);
	//m_MiniTool.SetColor(GuiDrawLayer::GetRGBColorXP());
	
	CStatic::PreSubclassWindow();
}


void CGuiListEdit::SetStyle(Border border)
{
	m_border=border;
}
void CGuiListEdit::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CStatic::OnPaint() for painting messages
	
	CBrush cbr;
	CRect m_rectDraw;
	GetClientRect(&m_rectDraw);
	cbr.CreateSolidBrush(m_clrface);
	dc.FillRect(&m_rectDraw,&cbr);
	if (m_border == STYLE3D)
		dc.Draw3dRect(m_rectDraw,GuiDrawLayer::GetRGBColorBTNHigh(),
			GuiDrawLayer::GetRGBColorShadow());
	if (m_border == STYLEPRESS)
	{
		dc.Draw3dRect(m_rectDraw,GuiDrawLayer::GetRGBColorShadow(),
			GuiDrawLayer::GetRGBColorBTNHigh());
	}
	if (m_border == STYLEFRAME)
	{
		dc.Draw3dRect(m_rectDraw,GuiDrawLayer::GetRGBColorShadow(),
			GuiDrawLayer::GetRGBColorShadow());
	}
	m_Conta.MoveWindow(0,0,m_rectDraw.Width(),m_rectDraw.Height());
	m_list->SetColumnWidth (0, m_rectDraw.Width ()-10);
	
}

INT_PTR CGuiListEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CGuiListEdit::OnSize(UINT nType, INT_PTR cx, INT_PTR cy)
{
	CStatic::OnSize(nType, cx, cy);
	CWnd* pWnd = GetWindow(GW_CHILD);
        if (pWnd != NULL)
        {
            pWnd->MoveWindow(0, 0, cx, cy);
            ASSERT(pWnd->GetWindow(GW_HWNDNEXT) == NULL);
		}
	//m_Conta.MoveWindow(0,0,cx,cy);
	// TODO: Add your message handler code here
}


CListCtrl* CGuiListEdit::GetListCtrl()
{
	return m_list;
} 


//==================================================
void CGuiListEdit::OnDelete(const CString &str) {
	if (onchanged_ != NULL)
		onchanged_->OnDelete(str);
}

void CGuiListEdit::OnBeginEdit(const CString &strOld) {
	if (onchanged_ != NULL)
		onchanged_->OnBeginEdit(strOld);
}

bool CGuiListEdit::OnEndEdit(const CString &strNew) {
	if (onchanged_ != NULL)
		return onchanged_->OnEndEdit(strNew);
	else
		return true;
}

bool CGuiListEdit::OnAdd(const CString &str) {
	if (onchanged_ != NULL)
		return onchanged_->OnAdd(str);
	else
		return true;
} 