/******************************************************************************

$Author$
  
$Modtime$
$Revision$

Description: Implementation of class "CListBase"
             (list control with sort icons and colored sort column)

$Log$

******************************************************************************/

#include "stdafx.h"
#include "ListViewCtrlEx.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*** Theme parts and states not defined in Visual Studio *********************/
#if _MSC_VER < 1500
  enum NEW_LISTITEMSTATES
  {
	  LISS_NORMAL           = 1,
	  LISS_HOT              = 2,
	  LISS_SELECTED         = 3,
	  LISS_DISABLED         = 4,
	  LISS_SELECTEDNOTFOCUS = 5,
	  LISS_HOTSELECTED      = 6
  };
#endif

/*** Definition of class "CListCtrlEx" ***************************************/

#ifndef NDEBUG
  ATL::CTraceCategory ListCtrlEx(_T("ListCtrlEx"), 1);
#endif

IMPLEMENT_DYNCREATE(CListCtrlEx, CListCtrl)

/*** Protected member functions **********************************************/

/*** Label editing will be started *******************************************/
BOOL CListCtrlEx::OnBeginLabelEdit(NMHDR* pNMHDR, LRESULT*)
{
  return CListBase::OnBeginLabelEdit(pNMHDR);
}

/*** Label editing will be cancelled *****************************************/
LRESULT CListCtrlEx::OnCancelEditLabel(WPARAM, LPARAM)
{
  return CListBase::OnCancelEditLabel();
}

/*** A column header has been clicked ****************************************/
BOOL CListCtrlEx::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
  return CListBase::OnColumnclick(pNMHDR, pResult);
}

/*** An item from a menu has been selected ***********************************/
BOOL CListCtrlEx::OnCommand(WPARAM wParam, LPARAM)
{
  return CListBase::OnCommand(wParam);
}

/*** The user has right clicked the mouse ************************************/
void CListCtrlEx::OnContextMenu(CWnd* pWnd, CPoint point) 
{
  CListBase::OnContextMenu(pWnd, point);
}

/*** A list view (sub)item will be drawn *************************************/
void CListCtrlEx::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) 
{
  CListBase::OnCustomDraw(pNMHDR, pResult);
}

/*** All items from a list view control will be removed **********************/
LRESULT CListCtrlEx::OnDeleteAllItems(WPARAM, LPARAM)
{
  return CListBase::OnDeleteAllItems();
}

/*** A column in a list view control will be deleted *************************/
LRESULT CListCtrlEx::OnDeleteColumn(WPARAM wParam, LPARAM)
{
  return CListBase::OnDeleteColumn(wParam);
}

/*** An item from a list view control will be removed ************************/
LRESULT CListCtrlEx::OnDeleteItem(WPARAM wParam, LPARAM)
{
  return CListBase::OnDeleteItem(wParam);
}

/*** The list view control will be destroyed *********************************/
void CListCtrlEx::OnDestroy() 
{
	CListBase::OnDestroy();
}

/*** Label editing will be finished ******************************************/
BOOL CListCtrlEx::OnEndLabelEdit(NMHDR* pNMHDR, LRESULT*)
{
  return CListBase::OnEndLabelEdit(pNMHDR);
}

/*** The background will be erased *******************************************/
BOOL CListCtrlEx::OnEraseBkgnd(CDC* pDC) 
{
  return CListBase::OnEraseBkgnd(pDC);
}

/*** A specific item of a list view control will be searched *****************/
LRESULT CListCtrlEx::OnFindItem(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnFindItem(wParam, lParam);
}

/*** The attributes of a list view control's column will be retrieved ********/
LRESULT CListCtrlEx::OnGetColumn(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnGetColumn(wParam, lParam);
}

/*** The current left-to-right order of columns in a list view control *******/
/*** will be retrieved                                                 *******/
LRESULT CListCtrlEx::OnGetColumnOrderArray(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnGetColumnOrderArray(wParam, lParam);
}

/*** The width of a column in a list view control will be retrieved **********/
LRESULT CListCtrlEx::OnGetColumnWidth(WPARAM wParam, LPARAM)
{
  return CListBase::OnGetColumnWidth(wParam);
}

/*** Information needed to display a list view item **************************/
BOOL CListCtrlEx::OnGetdispinfo(NMHDR* pNMHDR, LRESULT*)
{
  return CListBase::OnGetdispinfo(pNMHDR);
}

/*** The extended list view style will be retrieved **************************/
LRESULT CListCtrlEx::OnGetExtendedStyle(WPARAM, LPARAM)
{
  return m_dwExtendedStyle;
}

/*** Some or all of a list view item's attributes will be retrieved **********/
LRESULT CListCtrlEx::OnGetItem(WPARAM, LPARAM lParam)
{
  return CListBase::OnGetItem(lParam);
}

/*** The rectangle bounding an item will be retrieved ************************/
LRESULT CListCtrlEx::OnGetItemRect(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnGetItemRect(wParam, lParam);
}

/*** The text of a list view item or subitem will be retrieved ***************/
LRESULT CListCtrlEx::OnGetItemText(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnGetItemText(wParam, lParam);
}

/*** The rectangle bounding a subitem will be retrieved **********************/
LRESULT CListCtrlEx::OnGetSubItemRect(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnGetSubItemRect(wParam, lParam);
}

/*** The list-view item at a specified position will be determined ***********/
LRESULT CListCtrlEx::OnHitTest(WPARAM, LPARAM lParam)
{
  return CListBase::OnHitTest(lParam);
}

/*** List control has been scrolled horizontally *****************************/
void CListCtrlEx::OnHScroll(UINT, UINT, CScrollBar*)
{
  CListBase::OnHScroll();
}

/*** A new column in a list-view control will be inserted ********************/
LRESULT CListCtrlEx::OnInsertColumn(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnInsertColumn(wParam, lParam);
}

/*** A new item in a list-view control will be inserted **********************/
LRESULT CListCtrlEx::OnInsertItem(WPARAM, LPARAM lParam)
{
  return CListBase::OnInsertItem(lParam);
}

/*** A key has been pressed  *************************************************/
void CListCtrlEx::OnKeyDown(UINT nChar, UINT, UINT) 
{
  CListBase::OnKeyDown(nChar);
}

/*** A key has been released *************************************************/
void CListCtrlEx::OnKeyUp(UINT nChar, UINT, UINT) 
{
  CListBase::OnKeyUp(nChar);
}

/*** List control loses input focus ******************************************/
void CListCtrlEx::OnKillFocus(CWnd*) 
{
  CListBase::OnKillFocus();
}

/*** The user double-clicks the left mouse button ****************************/
void CListCtrlEx::OnLButtonDblClk(UINT, CPoint point) 
{
  CListBase::OnLButtonDblClk(point);
}

/*** The user presses the left mouse button **********************************/
void CListCtrlEx::OnLButtonDown(UINT, CPoint point) 
{
  CListBase::OnLButtonDown(point);
}

/*** The user releases the left mouse button *********************************/
void CListCtrlEx::OnLButtonUp(UINT, CPoint) 
{
  CListBase::OnLButtonUp();
}

/*** The mouse cursor leaves the client area of this list view control *******/
LRESULT CListCtrlEx::OnMouseLeave(WPARAM, LPARAM)
{
  return CListBase::OnMouseLeave();
}

/*** The mouse has been moved ************************************************/
void CListCtrlEx::OnMouseMove(UINT, CPoint point) 
{
	CListBase::OnMouseMove(point);
}

/*** The mouse wheel has been rotated ****************************************/
BOOL CListCtrlEx::OnMouseWheel(UINT, short, CPoint pt)
{
  return CListBase::OnMouseWheel(pt);
}

/*** Divider in header control has been dragged ******************************/
BOOL CListCtrlEx::OnNotify(WPARAM, LPARAM lParam, LRESULT*)
{
  return CListBase::OnNotify(lParam);
}

/*** The contents of the display area of a virtual list view control have ****/
/*** been changed                                                         ****/
BOOL CListCtrlEx::OnODCacheHint(NMHDR* pNMHDR, LRESULT*)
{
  return CListBase::OnODCacheHint(pNMHDR);
}

/*** Will be called when Windows or an application makes a request to ********/
/*** repaint a portion of the client area of this list view control   ********/
void CListCtrlEx::OnPaint()
{
  CListBase::OnPaint();
}

/*** The background color of the list view control will be set ***************/
LRESULT CListCtrlEx::OnSetBkColor(WPARAM, LPARAM lParam)
{
  return CListBase::OnSetBkColor(lParam);
}

/*** An background image will be set *****************************************/
LRESULT CListCtrlEx::OnSetBkImage(WPARAM, LPARAM)
{
  return CListBase::OnSetBkImage();
}

/*** The attributes of a list view column will be set ************************/
LRESULT CListCtrlEx::OnSetColumn(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSetColumn(wParam, lParam);
}

/*** The left-to-right order of columns in a list view control will be set ***/
LRESULT CListCtrlEx::OnSetColumnOrderArray(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSetColumnOrderArray(wParam, lParam);
}

/*** The width of a column in a list view control will be changed ************/
LRESULT CListCtrlEx::OnSetColumnWidth(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSetColumnWidth(wParam, lParam);
}

/*** The extended list view style will be set ********************************/
LRESULT CListCtrlEx::OnSetExtendedStyle(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSetExtendedStyle(wParam, lParam);
}

/*** List control gains input focus ******************************************/
void CListCtrlEx::OnSetFocus(CWnd*) 
{
  CListBase::OnSetFocus();
}

/*** An image list will be assigned ******************************************/
LRESULT CListCtrlEx::OnSetImageList(WPARAM wParam, LPARAM)
{
  return CListBase::OnSetImageList(wParam);
}

/*** Some or all of a list view item's attributes will be set ****************/
LRESULT CListCtrlEx::OnSetItem(WPARAM, LPARAM lParam)
{
  return CListBase::OnSetItem(lParam);
}

/*** The text of an item or a subitem in a list view control will be changed */
LRESULT CListCtrlEx::OnSetItemText(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSetItemText(wParam, lParam);
}

/*** The items of a list view control will be sorted *************************/
LRESULT CListCtrlEx::OnSortItems(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSortItems(wParam, lParam);
}

/*** System colors have been changed *****************************************/
void CListCtrlEx::OnSysColorChange()
{
  CListBase::OnSysColorChange();
}

/*** Called by the framework to allow other necessary subclassing to occur ***/
/*** before the window is subclassed                                       ***/
void CListCtrlEx::PreSubclassWindow()
{
  InitializeSubCtrls          ();
  CListCtrl::PreSubclassWindow();
}

/*** Table of message handlers ***********************************************/
BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
  ON_MESSAGE          (LVM_CANCELEDITLABEL, OnCancelEditLabel)
  ON_MESSAGE          (LVM_DELETEALLITEMS, OnDeleteAllItems)
  ON_MESSAGE          (LVM_DELETECOLUMN, OnDeleteColumn)
  ON_MESSAGE          (LVM_DELETEITEM, OnDeleteItem)
  ON_MESSAGE          (LVM_FINDITEM, OnFindItem)
  ON_MESSAGE          (LVM_GETCOLUMN, OnGetColumn)
  ON_MESSAGE          (LVM_GETCOLUMNORDERARRAY, OnGetColumnOrderArray)
  ON_MESSAGE          (LVM_GETCOLUMNWIDTH, OnGetColumnWidth)
  ON_MESSAGE          (LVM_GETEXTENDEDLISTVIEWSTYLE , OnGetExtendedStyle)
  ON_MESSAGE          (LVM_GETITEM, OnGetItem)
  ON_MESSAGE          (LVM_GETITEMRECT, OnGetItemRect)
  ON_MESSAGE          (LVM_GETITEMTEXT, OnGetItemText)
  ON_MESSAGE          (LVM_GETSUBITEMRECT, OnGetSubItemRect)
  ON_MESSAGE          (LVM_HITTEST, OnHitTest)
  ON_MESSAGE          (LVM_INSERTCOLUMN, OnInsertColumn)
  ON_MESSAGE          (LVM_INSERTITEM, OnInsertItem)
  ON_MESSAGE          (LVM_SETBKCOLOR, OnSetBkColor)
  ON_MESSAGE          (LVM_SETBKIMAGE, OnSetBkImage)
  ON_MESSAGE          (LVM_SETCOLUMN, OnSetColumn)
  ON_MESSAGE          (LVM_SETCOLUMNORDERARRAY, OnSetColumnOrderArray)
  ON_MESSAGE          (LVM_SETCOLUMNWIDTH, OnSetColumnWidth)
  ON_MESSAGE          (LVM_SETEXTENDEDLISTVIEWSTYLE , OnSetExtendedStyle)
  ON_MESSAGE          (LVM_SETIMAGELIST, OnSetImageList)
  ON_MESSAGE          (LVM_SETITEM, OnSetItem)
  ON_MESSAGE          (LVM_SETITEMTEXT, OnSetItemText)
  ON_MESSAGE          (LVM_SORTITEMS, OnSortItems)
  ON_MESSAGE          (LVM_SUBITEMHITTEST, OnHitTest)
  ON_MESSAGE          (WM_MOUSELEAVE, OnMouseLeave)
  ON_NOTIFY_REFLECT   (NM_CUSTOMDRAW, OnCustomDraw)
  ON_NOTIFY_REFLECT_EX(LVN_BEGINLABELEDIT, OnBeginLabelEdit)
	ON_NOTIFY_REFLECT_EX(LVN_COLUMNCLICK, OnColumnclick)
  ON_NOTIFY_REFLECT_EX(LVN_ENDLABELEDIT, OnEndLabelEdit)
	ON_NOTIFY_REFLECT_EX(LVN_GETDISPINFO, OnGetdispinfo)
  ON_NOTIFY_REFLECT_EX(LVN_ODCACHEHINT, OnODCacheHint)
	ON_WM_CONTEXTMENU   ()
	ON_WM_DESTROY       ()
	ON_WM_ERASEBKGND    ()
	ON_WM_HSCROLL       ()
	ON_WM_KEYDOWN       ()
	ON_WM_KEYUP         ()
	ON_WM_KILLFOCUS     ()
	ON_WM_LBUTTONDBLCLK ()
	ON_WM_LBUTTONDOWN   ()
	ON_WM_LBUTTONUP     ()
	ON_WM_MOUSEMOVE     ()
  ON_WM_MOUSEWHEEL    ()
  ON_WM_PAINT         ()
	ON_WM_SETFOCUS      ()
	ON_WM_SYSCOLORCHANGE()
END_MESSAGE_MAP()


/*** Definition of class "CListViewEx" ***************************************/

IMPLEMENT_DYNCREATE(CListViewEx, CListView)

/*** Protected member functions **********************************************/

/*** Label editing will be started *******************************************/
BOOL CListViewEx::OnBeginLabelEdit(NMHDR* pNMHDR, LRESULT*)
{
  return CListBase::OnBeginLabelEdit(pNMHDR);
}

/*** Label editing will be cancelled *****************************************/
LRESULT CListViewEx::OnCancelEditLabel(WPARAM, LPARAM)
{
  return CListBase::OnCancelEditLabel();
}

/*** A column header has been clicked ****************************************/
BOOL CListViewEx::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
  return CListBase::OnColumnclick(pNMHDR, pResult);
}

/*** An item from a menu has been selected ***********************************/
BOOL CListViewEx::OnCommand(WPARAM wParam, LPARAM)
{
  return CListBase::OnCommand(wParam);
}

/*** The user has right clicked the mouse ************************************/
void CListViewEx::OnContextMenu(CWnd* pWnd, CPoint point) 
{
  CListBase::OnContextMenu(pWnd, point);
}

/*** A list view (sub)item will be drawn *************************************/
void CListViewEx::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) 
{
  CListBase::OnCustomDraw(pNMHDR, pResult);
}

/*** All items from a list view control will be removed **********************/
LRESULT CListViewEx::OnDeleteAllItems(WPARAM, LPARAM)
{
  return CListBase::OnDeleteAllItems();
}

/*** A column in a list view control will be deleted *************************/
LRESULT CListViewEx::OnDeleteColumn(WPARAM wParam, LPARAM)
{
  return CListBase::OnDeleteColumn(wParam);
}

/*** An item from a list view control will be removed ************************/
LRESULT CListViewEx::OnDeleteItem(WPARAM wParam, LPARAM)
{
  return CListBase::OnDeleteItem(wParam);
}

/*** The list view control will be destroyed *********************************/
void CListViewEx::OnDestroy() 
{
	CListBase::OnDestroy();
}

/*** Label editing will be finished ******************************************/
BOOL CListViewEx::OnEndLabelEdit(NMHDR* pNMHDR, LRESULT*)
{
  return CListBase::OnEndLabelEdit(pNMHDR);
}

/*** The background will be erased *******************************************/
BOOL CListViewEx::OnEraseBkgnd(CDC* pDC) 
{
  return CListBase::OnEraseBkgnd(pDC);
}

/*** A specific item of a list view control will be searched *****************/
LRESULT CListViewEx::OnFindItem(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnFindItem(wParam, lParam);
}

/*** The attributes of a list view control's column will be retrieved ********/
LRESULT CListViewEx::OnGetColumn(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnGetColumn(wParam, lParam);
}

/*** The current left-to-right order of columns in a list view control *******/
/*** will be retrieved                                                 *******/
LRESULT CListViewEx::OnGetColumnOrderArray(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnGetColumnOrderArray(wParam, lParam);
}

/*** The width of a column in a list view control will be retrieved **********/
LRESULT CListViewEx::OnGetColumnWidth(WPARAM wParam, LPARAM)
{
  return CListBase::OnGetColumnWidth(wParam);
}

/*** Information needed to display a list view item **************************/
BOOL CListViewEx::OnGetdispinfo(NMHDR* pNMHDR, LRESULT*)
{
  return CListBase::OnGetdispinfo(pNMHDR);
}

/*** The extended list view style will be retrieved **************************/
LRESULT CListViewEx::OnGetExtendedStyle(WPARAM, LPARAM)
{
  return m_dwExtendedStyle;
}

/*** Some or all of a list view item's attributes will be retrieved **********/
LRESULT CListViewEx::OnGetItem(WPARAM, LPARAM lParam)
{
  return CListBase::OnGetItem(lParam);
}

/*** The rectangle bounding an item will be retrieved ************************/
LRESULT CListViewEx::OnGetItemRect(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnGetItemRect(wParam, lParam);
}

/*** The text of a list view item or subitem will be retrieved ***************/
LRESULT CListViewEx::OnGetItemText(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnGetItemText(wParam, lParam);
}

/*** The rectangle bounding a subitem will be retrieved **********************/
LRESULT CListViewEx::OnGetSubItemRect(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnGetSubItemRect(wParam, lParam);
}

/*** The list-view item at a specified position will be determined ***********/
LRESULT CListViewEx::OnHitTest(WPARAM, LPARAM lParam)
{
  return CListBase::OnHitTest(lParam);
}

/*** List control has been scrolled horizontally *****************************/
void CListViewEx::OnHScroll(UINT, UINT, CScrollBar*)
{
  CListBase::OnHScroll();
}

/*** Called by the framework after the view is first attached to the *********/
/*** document, but before the view is initially displayed            *********/
void CListViewEx::OnInitialUpdate()
{
  CListView::OnInitialUpdate();
  InitializeSubCtrls        ();
}

/*** A new column in a list-view control will be inserted ********************/
LRESULT CListViewEx::OnInsertColumn(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnInsertColumn(wParam, lParam);
}

/*** A new item in a list-view control will be inserted **********************/
LRESULT CListViewEx::OnInsertItem(WPARAM, LPARAM lParam)
{
  return CListBase::OnInsertItem(lParam);
}

/*** A key has been pressed  *************************************************/
void CListViewEx::OnKeyDown(UINT nChar, UINT, UINT) 
{
  CListBase::OnKeyDown(nChar);
}

/*** A key has been released *************************************************/
void CListViewEx::OnKeyUp(UINT nChar, UINT, UINT) 
{
  CListBase::OnKeyUp(nChar);
}

/*** List control loses input focus ******************************************/
void CListViewEx::OnKillFocus(CWnd*) 
{
  CListBase::OnKillFocus();
}

/*** The user double-clicks the left mouse button ****************************/
void CListViewEx::OnLButtonDblClk(UINT, CPoint point) 
{
  CListBase::OnLButtonDblClk(point);
}

/*** The user presses the left mouse button **********************************/
void CListViewEx::OnLButtonDown(UINT, CPoint point) 
{
  CListBase::OnLButtonDown(point);
}


/*** The user releases the left mouse button *********************************/
void CListViewEx::OnLButtonUp(UINT, CPoint) 
{
  CListBase::OnLButtonUp();
}

/*** The mouse cursor leaves the client area of this list view control *******/
LRESULT CListViewEx::OnMouseLeave(WPARAM, LPARAM)
{
  return CListBase::OnMouseLeave();
}

/*** The mouse has been moved ************************************************/
void CListViewEx::OnMouseMove(UINT, CPoint point) 
{
	CListBase::OnMouseMove(point);
}

/*** The mouse wheel has been rotated ****************************************/
BOOL CListViewEx::OnMouseWheel(UINT, short, CPoint pt)
{
  return CListBase::OnMouseWheel(pt);
}

/*** Divider in header control has been dragged ******************************/
BOOL CListViewEx::OnNotify(WPARAM, LPARAM lParam, LRESULT*)
{
  return CListBase::OnNotify(lParam);
}

/*** The contents of the display area of a virtual list view control have ****/
/*** been changed                                                         ****/
BOOL CListViewEx::OnODCacheHint(NMHDR* pNMHDR, LRESULT*)
{
  return CListBase::OnODCacheHint(pNMHDR);
}

/*** Will be called when Windows or an application makes a request to ********/
/*** repaint a portion of the client area of this list view control   ********/
void CListViewEx::OnPaint()
{
  CListBase::OnPaint();
}

/*** The background color of the list view control will be set ***************/
LRESULT CListViewEx::OnSetBkColor(WPARAM, LPARAM lParam)
{
  return CListBase::OnSetBkColor(lParam);
}

/*** The background color of the list view control will be set ***************/
LRESULT CListViewEx::OnSetBkImage(WPARAM, LPARAM)
{
  return CListBase::OnSetBkImage();
}

/*** The attributes of a list view column will be set ************************/
LRESULT CListViewEx::OnSetColumn(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSetColumn(wParam, lParam);
}

/*** The left-to-right order of columns in a list view control will be set ***/
LRESULT CListViewEx::OnSetColumnOrderArray(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSetColumnOrderArray(wParam, lParam);
}

/*** The width of a column in a list view control will be changed ************/
LRESULT CListViewEx::OnSetColumnWidth(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSetColumnWidth(wParam, lParam);
}

/*** The extended list view style will be set ********************************/
LRESULT CListViewEx::OnSetExtendedStyle(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSetExtendedStyle(wParam, lParam);
}

/*** List control gains input focus ******************************************/
void CListViewEx::OnSetFocus(CWnd*) 
{
  CListBase::OnSetFocus();
}

/*** An image list will be assigned ******************************************/
LRESULT CListViewEx::OnSetImageList(WPARAM wParam, LPARAM)
{
  return CListBase::OnSetImageList(wParam);
}

/*** Some or all of a list view item's attributes will be set ****************/
LRESULT CListViewEx::OnSetItem(WPARAM, LPARAM lParam)
{
  return CListBase::OnSetItem(lParam);
}

/*** The state of an item in a list view control will be changed *************/
LRESULT CListViewEx::OnSetItemText(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSetItemText(wParam, lParam);
}

/*** The items of a list view control will be sorted *************************/
LRESULT CListViewEx::OnSortItems(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSortItems(wParam, lParam);
}

/*** System colors have been changed *****************************************/
void CListViewEx::OnSysColorChange()
{
  CListBase::OnSysColorChange();
}

/*** Table of message handlers ***********************************************/
BEGIN_MESSAGE_MAP(CListViewEx, CListView)
  ON_MESSAGE          (LVM_CANCELEDITLABEL, OnCancelEditLabel)
  ON_MESSAGE          (LVM_DELETEALLITEMS, OnDeleteAllItems)
  ON_MESSAGE          (LVM_DELETECOLUMN, OnDeleteColumn)
  ON_MESSAGE          (LVM_DELETEITEM, OnDeleteItem)
  ON_MESSAGE          (LVM_FINDITEM, OnFindItem)
  ON_MESSAGE          (LVM_GETCOLUMN, OnGetColumn)
  ON_MESSAGE          (LVM_GETCOLUMNORDERARRAY, OnGetColumnOrderArray)
  ON_MESSAGE          (LVM_GETCOLUMNWIDTH, OnGetColumnWidth)
  ON_MESSAGE          (LVM_GETEXTENDEDLISTVIEWSTYLE , OnGetExtendedStyle)
  ON_MESSAGE          (LVM_GETITEM, OnGetItem)
  ON_MESSAGE          (LVM_GETITEMRECT, OnGetItemRect)
  ON_MESSAGE          (LVM_GETITEMTEXT, OnGetItemText)
  ON_MESSAGE          (LVM_GETSUBITEMRECT, OnGetSubItemRect)
  ON_MESSAGE          (LVM_HITTEST, OnHitTest)
  ON_MESSAGE          (LVM_INSERTCOLUMN, OnInsertColumn)
  ON_MESSAGE          (LVM_INSERTITEM, OnInsertItem)
  ON_MESSAGE          (LVM_SETBKCOLOR, OnSetBkColor)
  ON_MESSAGE          (LVM_SETBKIMAGE, OnSetBkImage)
  ON_MESSAGE          (LVM_SETCOLUMN, OnSetColumn)
  ON_MESSAGE          (LVM_SETCOLUMNORDERARRAY, OnSetColumnOrderArray)
  ON_MESSAGE          (LVM_SETCOLUMNWIDTH, OnSetColumnWidth)
  ON_MESSAGE          (LVM_SETEXTENDEDLISTVIEWSTYLE , OnSetExtendedStyle)
  ON_MESSAGE          (LVM_SETIMAGELIST, OnSetImageList)
  ON_MESSAGE          (LVM_SETITEM, OnSetItem)
  ON_MESSAGE          (LVM_SETITEMTEXT, OnSetItemText)
  ON_MESSAGE          (LVM_SORTITEMS, OnSortItems)
  ON_MESSAGE          (LVM_SUBITEMHITTEST, OnHitTest)
  ON_MESSAGE          (WM_MOUSELEAVE, OnMouseLeave)
  ON_NOTIFY_REFLECT   (NM_CUSTOMDRAW, OnCustomDraw)
  ON_NOTIFY_REFLECT_EX(LVN_BEGINLABELEDIT, OnBeginLabelEdit)
	ON_NOTIFY_REFLECT_EX(LVN_COLUMNCLICK, OnColumnclick)
  ON_NOTIFY_REFLECT_EX(LVN_ENDLABELEDIT, OnEndLabelEdit)
	ON_NOTIFY_REFLECT_EX(LVN_GETDISPINFO, OnGetdispinfo)
  ON_NOTIFY_REFLECT_EX(LVN_ODCACHEHINT, OnODCacheHint)
	ON_WM_CONTEXTMENU   ()
	ON_WM_DESTROY       ()
	ON_WM_ERASEBKGND    ()
	ON_WM_HSCROLL       ()
	ON_WM_KEYDOWN       ()
	ON_WM_KEYUP         ()
	ON_WM_KILLFOCUS     ()
	ON_WM_LBUTTONDBLCLK ()
	ON_WM_LBUTTONDOWN   ()
	ON_WM_LBUTTONUP     ()
	ON_WM_MOUSEMOVE     ()
  ON_WM_MOUSEWHEEL    ()
  ON_WM_PAINT         ()
	ON_WM_SETFOCUS      ()
	ON_WM_SYSCOLORCHANGE()
END_MESSAGE_MAP()


/*** Definition of helper class "CListCtrlHelper" ****************************/
class CListCtrlHelper: public CListCtrl
{
  public:
  LRESULT Default      ();
  LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

/*** Public member functions *************************************************/

/*** Message handlers ********************************************************/
LRESULT CListCtrlHelper::Default()
{
  return __super::Default();
}

LRESULT CListCtrlHelper::DefWindowProc(UINT message, WPARAM wParam,
                                       LPARAM lParam)
{
  return __super::DefWindowProc(message, wParam, lParam);
}

/*** Table of message handlers ***********************************************/
BEGIN_MESSAGE_MAP(CListCtrlHelper, CListCtrl)
END_MESSAGE_MAP()

/*** Definition of helper class "CLabelEdit" *********************************/
class CLabelEdit: public CEdit
{
  public:
  CLabelEdit(CListBase* pListBase): m_pListBase(pListBase) {}

  virtual BOOL PreTranslateMessage(MSG* pMsg);

	protected:
	// Generated message map functions
  afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);

  DECLARE_MESSAGE_MAP()

  private:
  CListBase* m_pListBase;
};

/*** Public member functions *************************************************/

/*** Called before a new message will be dispatched **************************/
BOOL CLabelEdit::PreTranslateMessage(MSG* pMsg)
{
  if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
    m_pListBase->m_bLabelEditingCancelled = true;

  return FALSE;
}

/*** Protected member functions **********************************************/

/*** Called when the size, position, or Z-order is about to change ***********/
void CLabelEdit::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
  __super::OnWindowPosChanging(lpwndpos);

  if (m_pListBase->m_bKeepLabelLeft && m_pListBase->IndexToOrder(0) > 0)
  {
    // position edit control
    CRect rc;
    if (m_pListBase->m_pListCtrl->GetSubItemRect(
          m_pListBase->m_iItemEdit, 0, LVIR_LABEL, rc)) lpwndpos->x = rc.left;
  }
}

/*** Table of message handlers ***********************************************/
BEGIN_MESSAGE_MAP(CLabelEdit, CEdit)
  ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()

/*** Definition of helper class "CLabelTipCtrl" ******************************/
class CLabelTipCtrl: public CToolTipCtrl
{
  public:
  CLabelTipCtrl(CListBase* pListBase):
    m_iYOff             (0),
    m_bSettingsChanged  (false),
    m_pListBase         (pListBase),
    m_bExpandedMargin   (false),
    m_iLastX            (-1),
    m_iLastY            (-1),
    m_bMouseInClientArea(false),
    m_bLabelTipPoppedUp (false),
    m_iCurrentItem      (-1),
    m_iCurrentSubItem   (-1)
  {}

  ~CLabelTipCtrl()
  {
    if (!m_strClassName.IsEmpty())
      UnregisterClass(m_strClassName, AfxGetInstanceHandle());
  }

  BOOL Create(CWnd* pParentWnd);

	protected:
	// Generated message map functions
  afx_msg LRESULT OnMouseLeave       (WPARAM, LPARAM);
	afx_msg void    OnMouseMove        (UINT nFlags, CPoint point);
  afx_msg void    OnTimer            (UINT nIDEvent);
	afx_msg void    OnWindowPosChanging(WINDOWPOS* lpwndpos);

	DECLARE_MESSAGE_MAP()

  private:
  CString    m_strClassName;
  RECT       m_rcMargin;
  int        m_iYOff;
  bool       m_bSettingsChanged;
  CListBase* m_pListBase;
  bool       m_bExpandedMargin;
  int        m_iLastX;
  int        m_iLastY;
  bool       m_bMouseInClientArea;
  bool       m_bLabelTipPoppedUp;
  int        m_iCurrentItem;
  int        m_iCurrentSubItem;
};

/*** Public member functions *************************************************/

/*** Creates the label tip window ********************************************/
BOOL CLabelTipCtrl::Create(CWnd* pwndParent)
{
  // register window class without shadows
  WNDCLASS wndClass;
  if (GetClassInfo(0, TOOLTIPS_CLASS, &wndClass))
  {
    wndClass.style        &= ~CS_DROPSHADOW;
    m_strClassName         =
      wndClass.lpszClassName + CString(_T("_without_shadows"));
    wndClass.lpszClassName = m_strClassName;
    if (!RegisterClass(&wndClass) &&
        GetLastError() != ERROR_CLASS_ALREADY_EXISTS) m_strClassName.Empty();
  }

  if (CWnd::CreateEx(
        m_pListBase->m_visualStyle == CListBase::Present ?
        WS_EX_TRANSPARENT : 0,
        m_strClassName.IsEmpty() ? TOOLTIPS_CLASS : m_strClassName, 0,
        TTS_NOANIMATE | TTS_NOFADE | TTS_NOPREFIX, CW_USEDEFAULT, 0,
        CW_USEDEFAULT, 0, pwndParent->m_hWnd, 0))
  {
    SetOwner    (pwndParent);
    SetFont     (pwndParent->GetFont());
    GetMargin   (&m_rcMargin);        // remember margins
    SetDelayTime(TTDT_INITIAL, 0);
    SetDelayTime(TTDT_RESHOW, 0);
    return TRUE;
  }
  else
    return FALSE;
}

/*** Protected member functions **********************************************/

/*** The mouse cursor leaves the client area of this tooltip control *********/
LRESULT CLabelTipCtrl::OnMouseLeave(WPARAM, LPARAM)
{
  m_bMouseInClientArea = false;

  // Reset current tooltip item if mouse cursor has been moved over the
  // header control
  m_pListBase->m_bLabelUnfolded  = FALSE;
  m_pListBase->m_fCurrentFlags   = 0;
  m_pListBase->m_iCurrentItem    = -1;
  m_pListBase->m_iCurrentSubItem = -1;

  return Default();
}

/*** The mouse has been moved ************************************************/
void CLabelTipCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
  if (!m_bMouseInClientArea)
  {
    m_bMouseInClientArea = true;

    // Fire an event when the mouse cursor leaves the client area of this
    // tooltip control
    TRACKMOUSEEVENT eventTrack = {sizeof(TRACKMOUSEEVENT), TME_LEAVE, m_hWnd};

    _TrackMouseEvent(&eventTrack);
  }

	__super::OnMouseMove(nFlags, point);
}

/*** Called after each timer interval ****************************************/
void CLabelTipCtrl::OnTimer(UINT nIDEvent)
{
#ifndef NDEBUG
  ATLTRACE2(ListCtrlEx, 3, _T("nIDEvent = %u\n"), nIDEvent);
#endif
  if (!m_bLabelTipPoppedUp && nIDEvent == 3)
  {
    m_bLabelTipPoppedUp = true;
    Update();
  }

  // nIDEvent == 6: Expanded label will be faded out. Updating the expanded
  // label prevents any fading effects.
  if (nIDEvent == 6) Update();

  // nIDEvent == 4: Expanded label will be popped off. Ignoring timer event 4
  // prevents hiding of the expanded label.
  if (nIDEvent != 4) __super::OnTimer(nIDEvent);
}

/*** Called when the size, position, or Z-order is about to change ***********/
void CLabelTipCtrl::OnWindowPosChanging(WINDOWPOS* lpwndpos) 
{
#ifndef NDEBUG
  struct
  {
    UINT    uFlags;
    LPCTSTR pszFlags;
  } td[] =
  {
    {SWP_FRAMECHANGED,   _T("SWP_FRAMECHANGED")  },
    {SWP_HIDEWINDOW,     _T("SWP_HIDEWINDOW")    },
    {SWP_NOACTIVATE,     _T("SWP_NOACTIVATE")    },
    {SWP_NOCOPYBITS,     _T("SWP_NOACTIVATE")    },
    {SWP_NOMOVE,         _T("SWP_NOMOVE")        },
    {SWP_NOOWNERZORDER,  _T("SWP_NOOWNERZORDER") },
    {SWP_NOSIZE,         _T("SWP_NOSIZE")        },
    {SWP_NOREDRAW,       _T("SWP_NOREDRAW")      },
    {SWP_NOSENDCHANGING, _T("SWP_NOSENDCHANGING")},
    {SWP_NOZORDER,       _T("SWP_NOZORDER")      },
    {SWP_SHOWWINDOW,     _T("SWP_SHOWWINDOW")    }
  };

  CString strFlags;
  for (int i = 0; i < sizeof td / sizeof td[0]; ++i)
    if (lpwndpos->flags & td[i].uFlags)
    {
      if (!strFlags.IsEmpty()) strFlags += _T(" | ");
      strFlags += td[i].pszFlags;
    }

  ATLTRACE2(
    ListCtrlEx, 2, _T("flags = %s (0x%08X)\n"), strFlags, lpwndpos->flags);
#endif
	__super::OnWindowPosChanging(lpwndpos);

  // If tooltip updates are suspended, restore last remembered position to
  // prevent flickering.
  if (!m_pListBase->m_bUpdateToolTips && m_iLastX != -1 && m_iLastY != -1)
  {
    lpwndpos->x = m_iLastX;
    lpwndpos->y = m_iLastY;
  }
  else
    if (m_pListBase->m_fCurrentFlags   != 0  &&
        m_pListBase->m_iCurrentItem    != -1 &&
        m_pListBase->m_iCurrentSubItem != -1)
    {
      // position unfolded label
      CRect rc;
      if (m_pListBase->m_pListCtrl->GetSubItemRect(
            m_pListBase->m_iCurrentItem, m_pListBase->m_iCurrentSubItem,
            LVIR_LABEL, rc))
      {
        m_pListBase->m_pListCtrl->ClientToScreen(rc);

        lpwndpos->x = rc.left;
        lpwndpos->y = rc.top;
        if ((lpwndpos->flags & (SWP_NOMOVE | SWP_NOSIZE)) == 0)
          if (lpwndpos->cy > rc.Height()+1)
            m_iYOff = lpwndpos->cy - (rc.Height()+1);
          else
            m_iYOff = 0;
        lpwndpos->y -= m_iYOff;

        // remember position
        m_iLastX = lpwndpos->x;
        m_iLastY = lpwndpos->y;

        // adjust margins
        if (m_pListBase->m_iCurrentSubItem                            > 0 &&
            !m_pListBase->m_bKeepLabelLeft                                ||
            m_pListBase->IndexToOrder(m_pListBase->m_iCurrentSubItem) > 0 &&
            m_pListBase->m_bKeepLabelLeft)
        {
          if (!m_bExpandedMargin)
          {
            rc = m_rcMargin;
            rc.left += m_pListBase->m_iNextColXOff - 3;
            rc.right = rc.left;
            SetMargin(rc);
            m_bExpandedMargin = true;
          }
        }
        else
          if (m_bExpandedMargin)
          {
            SetMargin(&m_rcMargin);
            m_bExpandedMargin = false;
          }

        if (lpwndpos->flags & SWP_SHOWWINDOW                  &&
            (m_pListBase->m_iCurrentItem    != m_iCurrentItem ||
             m_pListBase->m_iCurrentSubItem != m_iCurrentSubItem))
        {
          m_bLabelTipPoppedUp = false;
          m_iCurrentItem      = m_pListBase->m_iCurrentItem;
          m_iCurrentSubItem   = m_pListBase->m_iCurrentSubItem;
        }
      }
    }
    else
      if (m_iLastX != -1 && m_iLastY != -1)
      {
        lpwndpos->x = m_iLastX;
        lpwndpos->y = m_iLastY;
      }
}

/*** Table of message handlers ***********************************************/
BEGIN_MESSAGE_MAP(CLabelTipCtrl, CToolTipCtrl)
  ON_MESSAGE             (WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_MOUSEMOVE        ()
  ON_WM_TIMER            ()
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()


/*** Definition of "workhorse" class "CListBase" *****************************/

UINT                    CListBase::m_winver        = 0; // Windows version
CListBase::VISUAL_STYLE CListBase::m_visualStyle   = Unknown; // visual style?
const int               CListBase::m_iFirstColXOff = 2; // x-off of first col
const int               CListBase::m_iNextColXOff  = 6; // x-off of other cols

// Width of column separator (applies only to Vista explorer style)
const int CListBase::m_iColumnSeparatorWidth = 2;

/*** Public member functions *************************************************/

/*** Constructor *************************************************************/
CListBase::CListBase()
{
  // Build equivalent to deprecated global "_win_ver"
  if (m_winver == 0)
  {
    WORD wVersion = LOWORD(GetVersion());
    m_winver = MAKEWORD(HIBYTE(wVersion), LOBYTE(wVersion));
  }

  if (m_visualStyle == Unknown)
  {
    m_visualStyle = NotPresent;

    HINSTANCE hinstDll = LoadLibrary(_T("COMCTL32.DLL"));
	
    if (hinstDll)
    {
      DLLGETVERSIONPROC pDllGetVersion =
        reinterpret_cast<DLLGETVERSIONPROC>(GetProcAddress(hinstDll,
          "DllGetVersion"));

      // Because some DLLs might not implement this function, you must test for
      // it explicitly. Depending on the particular DLL, the lack of a
      // DllGetVersion function can be a useful indicator of the version.
      if (pDllGetVersion)
      {
        DLLVERSIONINFO dvi = {sizeof(DLLVERSIONINFO)};

        if (SUCCEEDED((*pDllGetVersion)(&dvi)) && dvi.dwMajorVersion >= 6)
          m_visualStyle = Present;
      }
      
      FreeLibrary(hinstDll);
    }
  }

  m_iIconXOff               = 4;
  m_hTheme                  = 0;
  m_pListCtrl               = 0;
  m_bIsActive               = false;
  m_bMouseInClientArea      = false;
  m_bTopMost                = false;
  m_bFocusSet               = false;
  m_iColumnHidingAllowed    = 0;
  m_bColumnSeparators       = FALSE;
  m_bExplorerStyle          = false;
  m_bSortIconEnabled        = FALSE;
  m_bColorSortColumn        = FALSE;
  m_bBkColorKnown           = false;
  m_bBkImage                = false;
  m_iSortColumn             = 0;
  m_bKeepLabelLeft          = FALSE;
  m_bLocked                 = false;
  m_bControl                = false;
  m_bIconXOffCalculated     = false;
  m_bFixedBkColor           = false;
  m_dwExtendedStyle         = 0;
  m_iItemUnderCursor        = -1;
  m_iHotItem                = -1;
  m_dwHotLite               =
    m_winver <= 0x0400 ? RGB(0, 0, 128) : GetSysColor(COLOR_HOTLIGHT);
  m_hCursorCustom           = 0;
  m_hCursorArrow            = 0;
  m_hCursorHand             = 0;
  m_iItemLastSelected       = -1;
  m_iFirstCachedItem        = INT_MAX;
  m_iLastCachedItem         = 0;
  m_bAlwaysGetSmallIconRect = false;
  m_bRefreshToolTips        = false;
  m_bSubItemTips            = FALSE;
  m_bUpdateToolTips         = true;
  m_pToolTip                = 0;
  m_pLabelTip               = 0;
  m_bToolTips               = false;
  m_bUnfoldLabel            = false;
  m_bLabelUnfolded          = FALSE;
  m_iItemEdit               = -1;
  m_bOnEndLabelEdit         = false;
  m_bOnGetDispinfo          = false;
  m_bOnPaint                = false;
  m_bRepost                 = false;
  m_fCurrentFlags           = 0;
  m_iCurrentItem            = -1;
  m_iCurrentSubItem         = -1;
  m_pLabelEdit = NULL;
}

/*** Destructor **************************************************************/
CListBase::~CListBase()
{
  delete m_pLabelEdit;
  delete m_pToolTip;
  delete m_pLabelTip;

  // remove remembered column data
  for (INT_PTR i = m_aColumnData.GetUpperBound(); i >= 0; --i)
    delete m_aColumnData[i];

  if (m_winver <= 0x400 && m_hCursorHand) DestroyCursor(m_hCursorHand);

  if (m_hTheme) CloseThemeData(m_hTheme);
}

/*** Enable or disable coloring of sort column *******************************/
#pragma runtime_checks("c", off)  // due to a flaw in the definition of
                                  // Get[R|G|B]Value
BOOL CListBase::ColorSortColumn(BOOL bEnable, int nSortColumn)
{
  if (bEnable == m_bColorSortColumn &&
      (nSortColumn == 0 || nSortColumn == m_iSortColumn)) return bEnable;

  if (bEnable)
  {
    // 256 colors --> don't color sort column
    CDC* pDC    = m_pListCtrl->GetDC();
    bool bColor = pDC->GetDeviceCaps(BITSPIXEL) > 8;

    m_pListCtrl->ReleaseDC(pDC);
    if (!bColor) return m_bColorSortColumn = FALSE;
  }

  if (bEnable != m_bColorSortColumn)
  {
    if (bEnable)
    {
      DWORD dwColNormalColor = m_pListCtrl->GetBkColor();

      // emulate sort column coloring of Windows XP explorer
      UINT nRed   = GetRValue(dwColNormalColor);
      UINT nGreen = GetGValue(dwColNormalColor);
      UINT nBlue  = GetBValue(dwColNormalColor);

      if (nRed > 240 && nGreen > 240 && nBlue > 240)
      {
        nRed   -= 8;
        nGreen -= 8;
        nBlue  -= 8;
      }
      else
      {
        if (nRed   < 232) nRed   += nRed   / 10; else nRed   = 255;
        if (nGreen < 232) nGreen += nGreen / 10; else nGreen = 255;
        if (nBlue  < 232) nBlue  += nBlue  / 10; else nBlue  = 255;
      }
      m_dwColSortColor = RGB(nRed, nGreen, nBlue);
    }
    m_bColorSortColumn = bEnable;
    bEnable            = !bEnable;
  }
  if (nSortColumn != 0) m_iSortColumn = nSortColumn;
  if (m_visualStyle == Present)
    if (m_bColorSortColumn)
      m_pListCtrl->SendMessage(
        LVM_SETSELECTEDCOLUMN, GetPhysicalIndex(abs(m_iSortColumn)-1));
    else
      m_pListCtrl->SendMessage(LVM_SETSELECTEDCOLUMN, 0xFFFFFFFF);
  m_pListCtrl->Invalidate();
  return bEnable;
}
#pragma runtime_checks("c", restore)

/*** Draw small icon *********************************************************/
void CListBase::DrawSmallIcon(CDC* pDC, LVITEM* pItem, LPRECT pRect)
{
  if (pItem->iImage > 0)
  {
    CImageList* pimglst = m_pListCtrl->GetImageList(LVSIL_SMALL);

    if (pimglst)
    {
      IMAGEINFO imgInfo;

      if (pimglst->GetImageInfo(pItem->iImage, &imgInfo))
      {
        pimglst->DrawIndirect(
          pDC, pItem->iImage, CPoint(pRect->left, pRect->top),
          CSize(
            __min(
              pRect->right - pRect->left + 1,
              imgInfo.rcImage.right - imgInfo.rcImage.left),
            __min(
              pRect->bottom - pRect->top + 1,
              imgInfo.rcImage.bottom - imgInfo.rcImage.top)), CPoint(0, 0),
          (!m_hTheme                    &&
           pItem->state & LVIS_SELECTED &&
           m_pListCtrl->GetFocus() == m_pListCtrl ?
           ILD_SELECTED : ILD_NORMAL) | pItem->state & LVIS_OVERLAYMASK,
          SRCCOPY, CLR_NONE);
      }
    }
  }
}

/*** Draw state icon *********************************************************/
void CListBase::DrawStateIcon(CDC* pDC, LVITEM* pItem, LPRECT pRect)
{
  int iImage = (pItem->state & LVIS_STATEIMAGEMASK) >> 12;

  if (iImage > 0)
  {
    CImageList* pimglst = m_pListCtrl->GetImageList(LVSIL_STATE);

    if (pimglst)
    {
      IMAGEINFO imgInfo;

      // image indices are zero-based
      if (pimglst->GetImageInfo(--iImage, &imgInfo))
      {
        long lRectWidth   = pRect->right  - pRect->left + 1L;
        long lRectHeight  = pRect->bottom - pRect->top  + 1L;
        long lImageWidth  = imgInfo.rcImage.right  - imgInfo.rcImage.left;
        long lImageHeight = imgInfo.rcImage.bottom - imgInfo.rcImage.top;
        long lDiffHorz    = lRectWidth  - lImageWidth;
        long lDiffVert    = lRectHeight - lImageHeight;

        // size of state icon to be drawn
        SIZE sz =
        {
          lDiffHorz >= 0 ? lImageWidth  : lRectWidth,
          lDiffVert >= 0 ? lImageHeight : lRectHeight
        };

        // coordinates of state icon's upper left corner
        POINT pt = {pRect->left, pRect->top};
        if (lDiffVert > 2) pt.y += lDiffVert / 2;

        pimglst->DrawIndirect(
          pDC, iImage, pt, sz, CPoint(0, 0),
          !m_hTheme                    &&
          pItem->state & LVIS_SELECTED &&
          m_pListCtrl->GetFocus() == m_pListCtrl ? ILD_SELECTED : ILD_NORMAL,
          SRCCOPY, CLR_NONE);
      }
    }
  }
}

/*** Draw the label of an item or subitem ************************************/
void CListBase::DrawSubItemText(
  CDC* pDC, LVITEM* pItem, LVCOLUMN* pColumn, LPRECT pRect)
{
  if (*pItem->pszText)
    if (pRect->right - pRect->left > 0)
      pDC->DrawText(
        pItem->pszText, -1, pRect,
        (pColumn->fmt & LVCFMT_CENTER ? DT_CENTER :
         pColumn->fmt & LVCFMT_RIGHT  ? DT_RIGHT  : DT_LEFT) |
        DT_END_ELLIPSIS | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER);
}

/*** Enable/disable a column entirely ****************************************/
void CListBase::EnableColumn(int nColumn, BOOL bEnableIt)
{
  ASSERT(nColumn >= 0 && nColumn < m_aColumnData.GetSize());

  if (bEnableIt)
  {
    if (!m_aColumnData[nColumn]->m_bEnabled)
    {
      // Enable column
      m_aColumnData[nColumn]->m_bEnabled = true;
      if (m_aColumnData[nColumn]->m_bVisible)
      {
        // Column was visible before disabling --> show it again
        m_aColumnData[nColumn]->m_bVisible = false;
        RedisplayColumn(nColumn);
      }
    }
  }
  else
    if (m_aColumnData[nColumn]->m_bEnabled)
    {
      // Disable column
      if (m_aColumnData[nColumn]->m_bVisible) HideColumn(nColumn);
      m_aColumnData[nColumn]->m_bEnabled = false;
    }
}

/*** Allow or disallow the hiding of a column ********************************/
void CListBase::EnableColumnHiding(int nColumn, BOOL bEnableIt)
{
  if (nColumn >= 0 && nColumn < m_aColumnData.GetSize())
    if (bEnableIt)
    {
      if (!m_aColumnData[nColumn]->m_bHidingAllowed)
        // The first column is allowed to be hidden only
        // if the list view control is owner-drawn.
        if (nColumn > 0 || m_pListCtrl->GetStyle() & LVS_OWNERDRAWFIXED)
        {
          m_aColumnData[nColumn]->m_bHidingAllowed = true;
          ++m_iColumnHidingAllowed;
        }
    }
    else
      if (m_aColumnData[nColumn]->m_bHidingAllowed)
      {
        ShowColumn(nColumn);    // display column if hidden
        m_aColumnData[nColumn]->m_bHidingAllowed = false;
        --m_iColumnHidingAllowed;
      }

  ASSERT(m_iColumnHidingAllowed >= 0);
}

/*** Enable style of Windows explorer ****************************************/
void CListBase::EnableExplorerStyle()
{
  if (m_winver >= 0x0600 && m_visualStyle == Present && !m_bExplorerStyle)
    if (SetWindowTheme(m_pListCtrl->m_hWnd, L"Explorer", 0) == S_OK)
    {
      m_pListCtrl->SetBkColor(RGB(255, 255, 255));
      if (m_pListCtrl->GetStyle() & LVS_OWNERDRAWFIXED)
        m_hTheme = OpenThemeData(m_pListCtrl->m_hWnd, L"ListView");
      m_bExplorerStyle = true;
    }
}

/*** Enable or disable sort icon *********************************************/
void CListBase::EnableSortIcon(BOOL bEnable, int nSortColumn)
{
  ASSERT(m_pListCtrl->GetHeaderCtrl());

  m_bSortIconEnabled = bEnable;
  if (nSortColumn != 0) m_iSortColumn = nSortColumn;
  if (bEnable && m_visualStyle == NotPresent)
  {
    CreateSortIcons                           ();
    m_pListCtrl->GetHeaderCtrl()->SetImageList(&m_imglstSortIcons);
  }
  SetSortIcon();            // display or hide sort icon
}

/*** Gets the position of the first checked item in the list view control ****/
POSITION CListBase::GetFirstCheckedItemPosition() const
{
  int nItemCount = m_pListCtrl->GetItemCount();

  for (int nItem = 0; nItem < nItemCount; ++nItem)
    if (m_pListCtrl->GetCheck(nItem))
      return reinterpret_cast<POSITION>(static_cast<INT_PTR>(nItem + 1));

  return 0;
}

/*** Gets the index of the next checked item in the list view control ********/
int CListBase::GetNextCheckedItem(POSITION& pos) const
{
  ASSERT(pos);
  
  int nOldPos    = static_cast<int>(reinterpret_cast<INT_PTR>(pos));
  int nItemCount = m_pListCtrl->GetItemCount();

  pos = 0;
  for (int nItem = nOldPos; nItem < nItemCount; ++nItem)
    if (m_pListCtrl->GetCheck(nItem))
    {
      pos = reinterpret_cast<POSITION>(static_cast<INT_PTR>(nItem + 1));
      break;
    }

  return nOldPos - 1;
}
  
/*** Get attributes of this list view control ********************************/
BOOL CListBase::GetState(LPBYTE* ppState, LPUINT pnStateLen) const
{
  int nColumnCount = static_cast<int>(m_aColumnData.GetSize());

  if (nColumnCount > 0 && ppState)
  {
    UINT nStateLen =
      2 * sizeof(int) + nColumnCount * (sizeof(bool) + 2 * sizeof(int));

    *ppState = new BYTE[nStateLen];
    LPBYTE p = *ppState;

    *reinterpret_cast<LPINT>(p) = nColumnCount;
    p                          += sizeof(int);
    *reinterpret_cast<LPINT>(p) = m_iSortColumn;

    for (int nColumn = 0; nColumn < nColumnCount; ++nColumn)
    {
      p                          += sizeof(int);
      *reinterpret_cast<bool*>(p) = m_aColumnData[nColumn]->m_bHidingAllowed ?
                                    m_aColumnData[nColumn]->m_bVisible : true;
      p                          += sizeof(bool);
      *reinterpret_cast<LPINT>(p) = m_aColumnData[nColumn]->m_bEnabled &&
                                    m_aColumnData[nColumn]->m_bVisible   ?
                                    m_pListCtrl->GetColumnWidth(nColumn) :
                                    m_aColumnData[nColumn]->m_nWidth,
      p                          += sizeof(int);
      *reinterpret_cast<LPINT>(p) = m_aColumnData[nColumn]->m_nOrder;
    }

    if (pnStateLen) *pnStateLen = nStateLen;
    return TRUE;
  }
  else
    return FALSE;
}

/*** Is the width of a given subitem sufficient to display "pszText"? ********/
BOOL CListBase::IsSubItemWidthSufficient(
  int nItem, int nSubItem, LPCTSTR pszText)
{
  CRect rc;

  if (m_pListCtrl->GetSubItemRect(nItem, nSubItem, LVIR_LABEL, rc))
    return
      m_aColumnData[nSubItem]->m_bEnabled &&
      m_aColumnData[nSubItem]->m_bVisible ?
        m_pListCtrl->GetStringWidth(pszText) +
        (
          nSubItem               == 0 && !m_bKeepLabelLeft ||
          IndexToOrder(nSubItem) == 0 &&  m_bKeepLabelLeft ?
            m_iFirstColXOff : m_iNextColXOff
        ) + 
        (nSubItem == 0 && (!m_bKeepLabelLeft || IndexToOrder(0) == 0) ?
          m_iFirstColXOff : m_iNextColXOff) <= rc.Width() : FALSE;
  else
    return FALSE;
}

/*** Small icon always should be kept left ***********************************/
BOOL CListBase::KeepLabelLeft(BOOL bKeepLeft)
{
  BOOL bSuccess = TRUE;

  if (bKeepLeft)
    if ((m_pListCtrl->GetStyle() & LVS_OWNERDRAWFIXED) == 0)
    {
      bKeepLeft = FALSE;
      bSuccess  = FALSE;
    }

  if (bSuccess && bKeepLeft != m_bKeepLabelLeft)
  {
    m_bKeepLabelLeft = bKeepLeft;
    m_pListCtrl->Invalidate();
  }
  return bSuccess;
}

/*** Restore attributes of this list view control ****************************/
BOOL CListBase::RestoreState(LPCTSTR pszSection, LPCTSTR pszEntry)
{
  BOOL bSuccess = FALSE;

  if (static_cast<int>(m_aColumnData.GetSize()) > 0)
  {
    LPBYTE pState;
    UINT   nStateLen;

    if (AfxGetApp()->GetProfileBinary(
          pszSection, pszEntry, &pState, &nStateLen))
    {
      bSuccess = SetState(pState, nStateLen);
      delete[] pState;
    }
  }

  return bSuccess;
}

/*** Save attributes of this list view control *******************************/
BOOL CListBase::SaveState(LPCTSTR pszSection, LPCTSTR pszEntry) const
{
  LPBYTE pState;
  UINT   nStateLen;

  if (GetState(&pState, &nStateLen))           // get current state
  {
    BOOL bSuccess =
      AfxGetApp()->WriteProfileBinary(pszSection, pszEntry, pState, nStateLen);

    delete[] pState;
    return bSuccess;
  }
  else
    return FALSE;
}

/*** Set column to be sorted *************************************************/
void CListBase::SetSortColumn(int nColumn)
{
  ASSERT(abs(nColumn) <= m_aColumnData.GetSize());
  if (nColumn != m_iSortColumn)
  {
    bool bColumnChanged = abs(nColumn) != abs(m_iSortColumn);
    m_iSortColumn = nColumn;
    SetSortIcon();
    if (bColumnChanged)
      if (m_visualStyle == Present)
        if (m_iSortColumn != 0)
          m_pListCtrl->SendMessage(
            LVM_SETSELECTEDCOLUMN, GetPhysicalIndex(abs(m_iSortColumn)-1));
        else
        {
          m_pListCtrl->SendMessage(LVM_SETSELECTEDCOLUMN, 0xFFFFFFFF);
          m_pListCtrl->Invalidate ();
        }
      else
        m_pListCtrl->Invalidate();
  }
}

/*** Set attributes of this list view control ********************************/
BOOL CListBase::SetState(LPBYTE pState, UINT nStateLen)
{
  int nColumnCount = static_cast<int>(m_aColumnData.GetSize());

  if (nColumnCount                    > 0                           &&
      nStateLen                        ==
      2*sizeof(int) + nColumnCount * (sizeof(bool) + 2*sizeof(int)) &&
      *reinterpret_cast<LPINT>(pState) == nColumnCount)
  {
    pState += sizeof(int);

    int nColumn = *reinterpret_cast<LPINT>(pState);
    if (abs(nColumn) <= nColumnCount)
      SetSortColumn(nColumn);
    else
      return FALSE;                       // wrong sort column

    for (nColumn = 0; nColumn < nColumnCount; ++nColumn)
    {
      COLUMN_DATA* pColData = m_aColumnData[nColumn];

      // restore display status of column
      pState += sizeof(int);
      bool bVisible = *reinterpret_cast<bool*>(pState);
      if (bVisible != pColData->m_bVisible)
        if (pColData->m_bHidingAllowed || !pColData->m_bVisible)
          ShowColumn(nColumn, bVisible);
      pState += sizeof(bool);

      // restore width of column
      m_pListCtrl->SetColumnWidth(nColumn, *reinterpret_cast<LPINT>(pState));
      pState += sizeof(int);

      // restore column order
      int nOrder = *reinterpret_cast<LPINT>(pState);
      if (nOrder < nColumnCount)
        pColData->m_nOrder = nOrder;
      else
        return FALSE;
    }

    // set column order
    LPINT pnColOrder = new int[nColumnCount];
    for (nColumn = 0; nColumn < nColumnCount; ++nColumn)
      pnColOrder[m_aColumnData[nColumn]->m_nOrder] = nColumn;
    m_pListCtrl->SetColumnOrderArray(nColumnCount, pnColOrder);
    delete[] pnColOrder;
  }

  return TRUE;
}

/*** Show or hide an individual column ***************************************/
void CListBase::ShowColumn(int nColumn, BOOL bShowIt)
{
  ASSERT(nColumn >= 0 && nColumn < m_aColumnData.GetSize());

  if (m_aColumnData[nColumn]->m_bEnabled)
    if (m_aColumnData[nColumn]->m_bHidingAllowed)
      if (bShowIt)
      {
        if (!m_aColumnData[nColumn]->m_bVisible) RedisplayColumn(nColumn);
      }
      else
        if (m_aColumnData[nColumn]->m_bVisible)
        {
          HideColumn(nColumn);
          m_aColumnData[nColumn]->m_bVisible = false;
        }
}

/*** Private member functions ************************************************/

/*** Compare function for sorting of list view control ***********************/
int CALLBACK CListBase::CompareFunc(
  LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
  CListBase* pThis = reinterpret_cast<CListBase*>(lParamSort);

  return
    pThis->m_pfnLVCompare(
      reinterpret_cast<ITEM_DATA*>(lParam1)->m_lParam,
      reinterpret_cast<ITEM_DATA*>(lParam2)->m_lParam, pThis->m_lParamSort);
}

/*** Create image list with sort icons ***************************************/
void CListBase::CreateSortIcons()
{
  if (!m_imglstSortIcons.m_hImageList)
  {
    COLORMAP cm = {RGB(0, 0, 0), GetSysColor(COLOR_GRAYTEXT)};

    m_imglstSortIcons.Create   (9, 5, ILC_COLOR24 | ILC_MASK, 2, 0);
    m_bmpUpArrow.LoadMappedBitmap(IDB_HDRUP, 0, &cm, 1);
    m_iUpArrow = m_imglstSortIcons.Add(&m_bmpUpArrow, RGB(255, 255, 255));
    m_bmpDownArrow.LoadMappedBitmap(IDB_HDRDOWN, 0, &cm, 1);
    m_iDownArrow = m_imglstSortIcons.Add(&m_bmpDownArrow, RGB(255, 255, 255));
  }
}

/*** Draw the entire item (called if window has style LVS_OWNERDRAWFIXED) ****/
void CListBase::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
  LVITEM* pItem = GetLVITEM(lpDrawItemStruct->itemID);

  DWORD  dwStyle           = m_pListCtrl->GetStyle();
	bool   bSelected         = (pItem->state & LVIS_SELECTED) != 0;
  bool   bAlwaysSelected   = bSelected && (dwStyle & LVS_SHOWSELALWAYS) != 0;
  bool   bLVHasFocus       = m_pListCtrl->GetFocus() == m_pListCtrl;
  bool   bItemHasFocus     = pItem->state & LVIS_FOCUSED  && bLVHasFocus;
	bool   bReallySelected   = bSelected && bLVHasFocus;
  bool   bSelectionVisible = bAlwaysSelected || bReallySelected;
  bool   bFullRowSelected  = (m_dwExtendedStyle & LVS_EX_FULLROWSELECT) != 0;
  bool   bItemUnderCursor  = pItem->iItem == m_iItemUnderCursor;
	CDC*   pDC               = CDC::FromHandle(lpDrawItemStruct->hDC);
  CBrush brushHiLite;
  DWORD  dwNormalText      = GetSysColor(COLOR_WINDOWTEXT);
  DWORD  dwHiLiteBk        = 0;
  bool   bHiLite           = false;

  if (!m_hTheme)
	  if (bReallySelected)
	  {
      dwHiLiteBk =
        pItem->iItem == m_iHotItem ?
          m_dwHotLite : GetSysColor(COLOR_HIGHLIGHT);
      brushHiLite.CreateSolidBrush(dwHiLiteBk);
	  }
	  else if (bAlwaysSelected)
    {
      dwHiLiteBk = GetSysColor(COLOR_3DFACE);
      brushHiLite.CreateSolidBrush(dwHiLiteBk);
    }

  CFont* pfontPrev          = 0;
  CFont* pfontHotUnderlined = 0;
  bool   bHotUnderlining    = false;
  if (m_dwExtendedStyle & LVS_EX_TWOCLICKACTIVATE                           &&
      (bSelected || bAlwaysSelected)                                        ||
      (m_dwExtendedStyle & (LVS_EX_UNDERLINEHOT | LVS_EX_ONECLICKACTIVATE)) ==
      (LVS_EX_UNDERLINEHOT | LVS_EX_ONECLICKACTIVATE)                       &&
      pItem->iItem == m_iHotItem)
  {
    CFont*  pFont = m_pListCtrl->GetFont();
    LOGFONT logFont;

    if (pFont->GetLogFont(&logFont))
    {
      logFont.lfUnderline = TRUE;
      pfontHotUnderlined  = new CFont;
      pfontHotUnderlined->CreateFontIndirect(&logFont);
      if (bFullRowSelected) pfontPrev = pDC->SelectObject(pfontHotUnderlined);
      bHotUnderlining = true;
    }
  }

  RECT rcItem;                    // rectangle bounding complete item
  m_pListCtrl->GetItemRect(pItem->iItem, &rcItem, LVIR_BOUNDS);

  CRect rcLabelArea;              // rectangle bounding item label
  m_pListCtrl->GetItemRect(pItem->iItem, rcLabelArea, LVIR_LABEL);

	CRect rcSelection;              // rectangle bounding selection
  if (bFullRowSelected)
  {
	  rcSelection = rcItem;

    if (m_hTheme)
    {
      if (bSelectionVisible || bItemUnderCursor)
      {
        // draw background of selection area
        DrawThemeBackground(
          m_hTheme, pDC->m_hDC, LVP_LISTITEM,
          bItemUnderCursor && bSelectionVisible ? LISS_HOTSELECTED :
          bReallySelected                       ? LISS_SELECTED    :
          bItemUnderCursor                      ? LISS_HOT         :
                                                  LISS_SELECTEDNOTFOCUS,
          rcSelection, 0);
        bHiLite = true;
      }
    }
    else
    {
      if (IndexToOrder(0) == 0 || m_bKeepLabelLeft)
      {
        rcSelection.left = rcLabelArea.left;
        int nWidthOfCol0 =
          static_cast<int>(
            m_pListCtrl->DefWindowProc(LVM_GETCOLUMNWIDTH, OrderToIndex(0), 0));
        if (rcSelection.left > nWidthOfCol0) rcSelection.left = nWidthOfCol0;

        if (bSelectionVisible && rcSelection.left > rcItem.left)
        {
          // fill area left from selection with background color
          RECT rc = rcItem;
          rc.right = rcSelection.left-1;
          EraseRect(pDC, &rc);
        }
      }

      if (bSelectionVisible)
      {
        pDC->FillRect    (rcSelection, &brushHiLite);
        pDC->SetBkColor  (dwHiLiteBk);
        pDC->SetTextColor(
          !m_hTheme && bReallySelected ? GetSysColor(COLOR_HIGHLIGHTTEXT) :
          !m_hTheme && bHotUnderlining ? m_dwHotLite                      :
                                         dwNormalText);
        bHiLite = true;
      }
    }
  }

  LVCOLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH;

  // display all subitems
  int  nIndex;
  RECT rcSubItem = {0, 0, 0, 0};        // rectangle bounding subitem
	for (int nColumn = 0;
       m_pListCtrl->DefWindowProc(
         LVM_GETCOLUMN, nIndex = OrderToIndex(nColumn),
         reinterpret_cast<LPARAM>(&lvc));
       ++nColumn)
  {
    LVITEM* pSubItem = nIndex > 0 ? GetLVITEM(pItem->iItem, nIndex) : pItem;
	  RECT    rcText;                     // output rectangle
    int     iAbsSortColumn = abs(m_iSortColumn) - 1;
    int     iLogicalIndex  = GetLogicalIndex(nIndex);

    // consider column margins
    if (nColumn > 0)
    {
      // move output rectangle over next column
      rcSubItem.left   = rcSubItem.right;
      rcSubItem.right += lvc.cx;
    }
    else
    {
      rcSubItem       = rcItem;
      rcSubItem.right = rcSubItem.left + lvc.cx;
    }

    if (nIndex == 0 && !m_bKeepLabelLeft || nColumn == 0 && m_bKeepLabelLeft)
    {
      if (bHotUnderlining && !bFullRowSelected)
        pfontPrev = pDC->SelectObject(pfontHotUnderlined);
      rcText = rcLabelArea;
      // extra space is only needed if there are icons to be displayed
      if (rcText.left + m_pListCtrl->GetScrollPos(SB_HORZ) > m_iFirstColXOff)
        rcText.left += m_iFirstColXOff;
      rcText.right -= nIndex > 0 ? m_iNextColXOff : m_iFirstColXOff;
    }
    else
    {
      if (bHotUnderlining && !bFullRowSelected && pfontPrev)
      {
        pDC->SelectObject(pfontPrev);
        delete pfontHotUnderlined;
        bHotUnderlining = false;
      }      
      rcText        = rcSubItem;
      rcText.left  += m_iNextColXOff;
      rcText.right -= m_iNextColXOff;

      // take subitem image into consideration
      if (!m_bKeepLabelLeft                        &&
          nIndex > 0                               &&
          m_dwExtendedStyle & LVS_EX_SUBITEMIMAGES &&
          pSubItem->iImage)
      {
        CRect rcIcon;

        if (m_pListCtrl->GetSubItemRect(
              pItem->iItem, iLogicalIndex, LVIR_ICON, rcIcon))
          rcText.left += rcIcon.Width();
      }
    }

    CRect rcLabel;
    if (!GetLabelRect(pItem->iItem, iLogicalIndex, rcLabel))
    {
      rcLabel.left  = rcText.left;
      rcLabel.right = rcText.right;
    }

    if (!bFullRowSelected)
    {
      bHiLite = false;

      if ((bSelectionVisible || bItemHasFocus) &&
          (
            nIndex  == 0 && !m_bKeepLabelLeft && nColumn != 0 ||
            nColumn == 0 && (m_bKeepLabelLeft || nIndex  == 0)
          ))
      {
        // calculate selection area
        RECT rcSubItemSelection = rcSubItem;

        if (!bFullRowSelected)
        {
          if (!m_hTheme)
          {
            rcSubItemSelection = rcLabelArea;

            switch (nIndex == 0 && nColumn == 0 || !m_bKeepLabelLeft ?
                      m_iFormatOfSubItem0 : lvc.fmt & LVCFMT_JUSTIFYMASK)
            {
              case LVCFMT_LEFT:
                rcSubItemSelection.right =
                  rcSubItemSelection.left + rcLabel.Width();
                break;

              case LVCFMT_RIGHT:
                rcSubItemSelection.left =
                  rcSubItemSelection.right - rcLabel.Width();
                break;

              case LVCFMT_CENTER:
              {
                int nSelectionWidth = rcLabel.Width();
                rcSubItemSelection.left  =
                  rcLabelArea.left + (rcLabelArea.Width() - nSelectionWidth) / 2;
                rcSubItemSelection.right =
                  rcSubItemSelection.left + nSelectionWidth;
                break;
              }

              default:
                ASSERT(false);
                break;
            }
            if (rcSubItemSelection.left < rcLabelArea.left)
              rcSubItemSelection.left = rcLabelArea.left;
            if (rcSubItemSelection.right > rcLabelArea.right)
              rcSubItemSelection.right = rcLabelArea.right;
          }

          rcSelection = rcSubItemSelection;
        }

        if (bSelectionVisible)
        {
          if (rcSubItemSelection.left > rcSubItem.left)
          {
            // fill area left from selection with background color
            RECT rc = rcSubItem;
            rc.right = rcSubItemSelection.left-1;
            EraseRect(pDC, &rc);
          }

          // fill selection area with highlight color
          if (m_hTheme)
            DrawThemeBackground(
              m_hTheme, pDC->m_hDC, LVP_LISTITEM,
              bItemUnderCursor && bSelectionVisible ? LISS_HOTSELECTED :
              bReallySelected                       ? LISS_SELECTED    :
              bItemUnderCursor                      ? LISS_HOT         :
                                                      LISS_SELECTEDNOTFOCUS,
              &rcSubItemSelection, 0);
          else
          {
            pDC->FillRect    (&rcSubItemSelection, &brushHiLite);
            pDC->SetBkColor  (dwHiLiteBk);
            pDC->SetTextColor(
              bReallySelected ? GetSysColor(COLOR_HIGHLIGHTTEXT) :
              bHotUnderlining ? m_dwHotLite                      :
                                dwNormalText);
          }

          // fill area right from selection with background color
          if (rcSubItemSelection.right < rcSubItem.right)
          {
            RECT rc = rcSubItem;
            rc.left = rcSubItemSelection.right+1;
            EraseRect(pDC, &rc);
          }

          bHiLite = true;
        }
      }
    }

    if (!bHiLite)
    {
      EraseRect        (pDC, &rcSubItem);
      pDC->SetBkColor  (m_bColorSortColumn                        &&
                        m_iSortColumn != 0                        &&
                        m_aColumnData[iAbsSortColumn]->m_bVisible &&
                        nIndex == GetPhysicalIndex(iAbsSortColumn) ?
                          m_dwColSortColor : m_pListCtrl->GetBkColor());
      pDC->SetTextColor(!m_hTheme && bHotUnderlining ?
                          m_dwHotLite : dwNormalText);
    }

    if (!m_bKeepLabelLeft && nIndex  == 0 ||
         m_bKeepLabelLeft && nColumn == 0)
    {
      RECT rcIcon;

      if (GetStateIconRect(pItem->iItem, &rcIcon))
        DrawStateIcon(pDC, pItem, &rcIcon);
    }

    if (!m_bKeepLabelLeft &&
        (
          nIndex  == 0 ||
          m_dwExtendedStyle & LVS_EX_SUBITEMIMAGES && pSubItem->iImage > 0
        ) ||
        m_bKeepLabelLeft && nColumn == 0)
    {
      CRect rcIcon;

      if (m_pListCtrl->GetSubItemRect(
            pItem->iItem, iLogicalIndex, LVIR_ICON, rcIcon))
      {
        LVITEM*      pLogicalItem;
        NMLVDISPINFO lvDispInfo;

        if (dwStyle & LVS_OWNERDATA)
        {
          lvDispInfo.hdr.hwndFrom  = m_pListCtrl->m_hWnd;
          lvDispInfo.hdr.idFrom    = m_pListCtrl->GetDlgCtrlID();
          lvDispInfo.hdr.code      = LVN_GETDISPINFO;
          lvDispInfo.item.mask     = LVIF_IMAGE;
          lvDispInfo.item.iItem    = pItem->iItem;
          lvDispInfo.item.iSubItem = 0;
          OnGetdispinfo(&lvDispInfo.hdr);
          pLogicalItem = &lvDispInfo.item;
        }
        else
          pLogicalItem =
            reinterpret_cast<ITEM_DATA*>(pItem->lParam)->m_apLVItem[0];

        // take state of the physical item!
        pLogicalItem->state     = pItem->state;
        pLogicalItem->stateMask = pItem->stateMask;

        DrawSmallIcon(pDC, pLogicalItem, rcIcon);

        pLogicalItem->state     = 0;
        pLogicalItem->stateMask = 0;
      }
    }

    pSubItem->iSubItem = GetLogicalIndex(pSubItem->iSubItem);
    lvc.iSubItem       = pSubItem->iSubItem;
    DrawSubItemText(pDC, pSubItem, &lvc, &rcText);

    if (nIndex > 0)
    {
      delete[] pSubItem->pszText;
      delete pSubItem;
    }
  }

  if (bHotUnderlining)
  {
    pDC->SelectObject(pfontPrev);
    delete pfontHotUnderlined;
  }
  delete[] pItem->pszText;
  delete pItem;

  // If item has focus draw focus rectangle
	if (bItemHasFocus)
  {
    pDC->SetTextColor(dwNormalText);
    if (m_hTheme)
      // If visual themes are enabled, draw focus rectangle inside the border
      // of the selection rectangle
      if (rcSelection.Width() > 1 && rcSelection.Height() > 1)
      {
        ++rcSelection.left;
        ++rcSelection.top;
        --rcSelection.right;
        --rcSelection.bottom;
      }
    pDC->DrawFocusRect(&rcSelection);
  }
}

/*** Duplicate column information ********************************************/
LVCOLUMN* CListBase::DupLVColumn(LVCOLUMN* pLVColumn) const
{
  #pragma warning(push)
  #pragma warning(disable:4616 6211)
  LVCOLUMN* pLVColumn2 = new LVCOLUMN(*pLVColumn);

  // mask unnecessary fields
  if (!(pLVColumn2->mask & LVCF_FMT)) pLVColumn2->fmt = 0;
  if (!(pLVColumn2->mask & LVCF_IMAGE)) pLVColumn2->iImage = 0;
  if (!(pLVColumn2->mask & LVCF_ORDER)) pLVColumn2->iOrder = 0;
  if (!(pLVColumn2->mask & LVCF_SUBITEM)) pLVColumn2->iSubItem = 0;
  if (pLVColumn2->mask & LVCF_TEXT)
  {
    ASSERT(pLVColumn2->pszText);
    pLVColumn2->pszText = new TCHAR[_tcslen(pLVColumn->pszText) + 1];
    _tcscpy(pLVColumn2->pszText, pLVColumn->pszText);
  }
  else
    pLVColumn2->pszText = 0;
  if (!(pLVColumn2->mask & LVCF_WIDTH)) pLVColumn2->cx = 0;
  pLVColumn2->cchTextMax = 0;

  return pLVColumn2;
  #pragma warning(pop)
}

/*** Duplicate item information **********************************************/
LVITEM* CListBase::DupLVItem(LVITEM* pLVItem) const
{
  #pragma warning(push)
  #pragma warning(disable:4616 6211)
  LVITEM* pLVItem2 = new LVITEM(*pLVItem);

  // mask unnecessary fields
  if (!(pLVItem2->mask & LVIF_IMAGE)) pLVItem2->iImage = 0;
  if (!(pLVItem2->mask & LVIF_INDENT)) pLVItem2->iIndent = 0;
  if (!(pLVItem2->mask & LVIF_PARAM)) pLVItem2->lParam = 0;
  if (pLVItem2->mask & LVIF_STATE)
    pLVItem2->state &= pLVItem2->stateMask;
  else
  {
    pLVItem2->state     = 0;
    pLVItem2->stateMask = 0;
  }
  if (pLVItem2->mask & LVIF_TEXT)
  {
    ASSERT(pLVItem2->pszText);
    if (pLVItem2->pszText != LPSTR_TEXTCALLBACK)
    {
      pLVItem2->pszText = new TCHAR[_tcslen(pLVItem->pszText) + 1];
      _tcscpy(pLVItem2->pszText, pLVItem->pszText);
    }
  }
  else
    pLVItem2->pszText = 0;
  pLVItem2->iSubItem   = 0;
  pLVItem2->cchTextMax = 0;

  return pLVItem2;
  #pragma warning(pop)
}

/*** Erase rectangular area with background color ****************************/
void CListBase::EraseRect(CDC* pDC, LPRECT pRect)
{
  if (pDC->SaveDC())
  {
    CRgn rgn;

    rgn.CreateRectRgn       (pRect->left, pRect->top,
                             pRect->right, pRect->bottom);
    pDC->SelectClipRgn      (&rgn);
    m_pListCtrl->SendMessage(WM_ERASEBKGND,
                             reinterpret_cast<WPARAM>(pDC->m_hDC));
    pDC->RestoreDC          (-1);
  }
}

/*** Retrieves the bounding rectangle of the label text of an item or ********/
/*** subitem                                                          ********/
bool CListBase::GetLabelRect(int nItem, int nSubItem, LPRECT pRect)
{
  // Determine the rectangle bounding the text selection area
  CRect rcLabel;
  if (m_pListCtrl->GetSubItemRect(nItem, nSubItem, LVIR_LABEL, rcLabel))
  {
    int nWidth =
      m_pListCtrl->GetStringWidth(m_pListCtrl->GetItemText(nItem, nSubItem)) +
      (nSubItem               == 0 && !m_bKeepLabelLeft ||
       IndexToOrder(nSubItem) == 0 &&  m_bKeepLabelLeft ?
       m_iFirstColXOff : m_iNextColXOff) + 
      (nSubItem == 0 && (!m_bKeepLabelLeft || IndexToOrder(0) == 0) ?
       m_iFirstColXOff : m_iNextColXOff);
                         
    if (nWidth < rcLabel.Width())
      switch (m_aColumnData[nSubItem]->m_pLVColumn->fmt & LVCFMT_JUSTIFYMASK)
      {
        case LVCFMT_LEFT:
          rcLabel.right -= rcLabel.Width() - nWidth;
          break;

        case LVCFMT_RIGHT:
          rcLabel.left += rcLabel.Width() - nWidth;
          break;

        case LVCFMT_CENTER:
          rcLabel.left += (rcLabel.Width() - nWidth) / 2;
          rcLabel.right = rcLabel.left + nWidth;
          break;
      }

    *pRect = rcLabel;
    return true;
  }

  return false;
}

/*** Retrieve for a given physical column number the logical column number ***/
int CListBase::GetLogicalIndex(int nPhysicalIndex) const
{
  INT_PTR nColumnCount = m_aColumnData.GetSize();

  for (int i = 0; i < nColumnCount; ++i)
    if (m_aColumnData[i]->m_bEnabled && m_aColumnData[i]->m_bVisible)
    {
      if (i == nPhysicalIndex) return nPhysicalIndex;
    }
    else
      ++nPhysicalIndex;

  ASSERT(false);
  return -1;
}

/*** Retrieve for a given physical column order the logical column order *****/
int CListBase::GetLogicalOrder(int nPhysicalOrder) const
{
  for (int i = 0; i <= nPhysicalOrder; ++i)
    for (INT_PTR j = m_aColumnData.GetUpperBound(); j >= 0; --j)
      if (m_aColumnData[j]->m_nOrder == i)
      {
        if (m_aColumnData[i]->m_bEnabled && m_aColumnData[j]->m_bVisible)
        {
          if (i == nPhysicalOrder) return nPhysicalOrder;
        }
        else
          ++nPhysicalOrder;
        break;
      }

  ASSERT(false);
  return -1;
}

/*** Get all attributes of a given physical item or subitem ******************/
LVITEM* CListBase::GetLVITEM(int nItem, int nSubItem) const
{
  #pragma warning(push)
  #pragma warning(disable:4616 6211)
  LVITEM* pItem = new LVITEM;

  pItem->mask      = LVIF_IMAGE | LVIF_STATE | LVIF_TEXT | LVIF_PARAM;
  pItem->iItem     = nItem;
  pItem->iSubItem  = nSubItem;
  pItem->stateMask = ~0U;

  // enlarge text buffer gradually until it's large enough
  for (int nLen = 128;; nLen += nLen)
  {
    LPTSTR pszText = new TCHAR[nLen];

    pItem->cchTextMax = nLen;
    pItem->pszText    = pszText;
    if (m_pListCtrl->DefWindowProc(
          LVM_GETITEM, 0, reinterpret_cast<LPARAM>(pItem)))
    {
      if (pItem->pszText != pszText)
      {
        // Windows hasn't used our buffer!
        _tcsncpy(pszText, pItem->pszText, nLen-1);
        pszText[nLen-1] = _T('\0');
        pItem->pszText  = pszText;
      }
    }
    else
    {
      delete[] pszText;
      delete pItem;
      return 0;
    }
    if (static_cast<int>(_tcslen(pItem->pszText)) < nLen-1) break;
    delete[] pItem->pszText;
  }

  return pItem;
  #pragma warning(pop)
}

/*** Returns the physical index of a given column index **********************/
int CListBase::GetPhysicalIndex(int nColumnIndex) const
{
  int nIndex = 0;

  for (int i = 0; i < nColumnIndex; ++i)
    if (m_aColumnData[i]->m_bEnabled && m_aColumnData[i]->m_bVisible) ++nIndex;

  return nIndex;
}

/*** Returns the physical order of a given column order **********************/
int CListBase::GetPhysicalOrder(int nColumnOrder) const
{
  int nOrder = 0;

  for (int i = 0; i < nColumnOrder; ++i)
    for (INT_PTR j = m_aColumnData.GetUpperBound(); j >= 0; --j)
      if (m_aColumnData[j]->m_nOrder == i)
      {
        if (m_aColumnData[i]->m_bEnabled && m_aColumnData[j]->m_bVisible)
          ++nOrder;
        break;
      }

  return nOrder;
}

/*** Retrieves the bounding rectangle for the state icon of an item **********/
bool CListBase::GetStateIconRect(int nItem, LPRECT pRect)
{
  bool  bRet = false;
  CRect rcSubItem;

  if (m_pListCtrl->GetSubItemRect(
        nItem, GetLogicalIndex(m_bKeepLabelLeft ? OrderToIndex(0) : 0),
        LVIR_BOUNDS, rcSubItem))
  {
    RECT rcSmallIcon;

    m_bAlwaysGetSmallIconRect = true;
    if (m_pListCtrl->GetItemRect(nItem, &rcSmallIcon, LVIR_ICON))
    {
      *pRect       = rcSubItem;
      pRect->right = rcSmallIcon.left;
      if (rcSmallIcon.right > rcSmallIcon.left) --pRect->right;

      // calculate x-offset of state icon
      if (!m_bIconXOffCalculated)
      {
        CImageList* pImageList = m_pListCtrl->GetImageList(LVSIL_STATE);

        if (pImageList)
        {
          // retrieve width of state icon
          IMAGEINFO ii = {0, 0, 0, 0};

          if (pImageList->GetImageInfo(0, &ii))
          {
            int nXOff =
              pRect->right - (ii.rcImage.right - ii.rcImage.left) -
              pRect->left;

            if (nXOff < 0)
              m_iIconXOff = 0;
            else if (nXOff < 4)
              m_iIconXOff = nXOff;
            else
              m_iIconXOff = 4;
          }
          else
            m_iIconXOff = 4;
        }
        else
          m_iIconXOff = 4;

        m_bIconXOffCalculated = true;
      }

      pRect->left += m_iIconXOff;

      // clip at right column border
      int nWidth = rcSubItem.Width();
      if (pRect->right >= rcSubItem.left + nWidth)
        pRect->right = pRect->left - m_iIconXOff + nWidth - 1;

      bRet = true;
    }
    m_bAlwaysGetSmallIconRect = false;
  }

  return bRet;
}

/*** Hide an individual column ***********************************************/
void CListBase::HideColumn(int nColumn)
{
  ASSERT(nColumn >= 0 && nColumn < m_aColumnData.GetSize());

  // hide column
  int nPhysicalColumn = GetPhysicalIndex(nColumn);

  m_aColumnData[nColumn]->m_nWidth =
    m_pListCtrl->GetColumnWidth(nColumn);
  // hide column coloring, too, if this column was the selected column
  if (m_visualStyle == Present &&
      m_bColorSortColumn       &&
      nColumn       == abs(m_iSortColumn)-1)
    m_pListCtrl->SendMessage(LVM_SETSELECTEDCOLUMN, 0xFFFFFFFF);
  m_pListCtrl->DefWindowProc(LVM_DELETECOLUMN, nPhysicalColumn, 0);
}

/*** Return the order in the header control of a subitem, based on its index */
int CListBase::IndexToOrder(int nIndex)
{
  ASSERT(m_pListCtrl->GetHeaderCtrl());

  HDITEM headerItem = {HDI_ORDER};
  return
    m_pListCtrl->GetHeaderCtrl()->GetItem(nIndex, &headerItem) ?
      headerItem.iOrder : -1;

}

/*** Invalidate client area not covered by list control items ****************/
void CListBase::InvalidateNonItemArea()
{
  int nSortColumn = abs(m_iSortColumn) - 1;

  if (m_bColorSortColumn                     &&
      m_iSortColumn != 0                     &&
      m_aColumnData[nSortColumn]->m_bEnabled &&
      m_aColumnData[nSortColumn]->m_bVisible)
  {
    RECT rcHdrItem;
    ASSERT(m_pListCtrl->GetHeaderCtrl());
    if (m_pListCtrl->GetHeaderCtrl()->GetItemRect(0, &rcHdrItem))
    {
      RECT rcThis;
      m_pListCtrl->GetClientRect(&rcThis);

      RECT rcToBeErased =
      {
        rcThis.left, rcHdrItem.bottom, rcThis.right, rcThis.bottom
      };

      int iItemCount = m_pListCtrl->GetItemCount();
      if (iItemCount > 0)
      {
        // erase area above top item
        ASSERT(m_pListCtrl->GetTopIndex() >= 0);
        RECT rcItem;
        m_pListCtrl->GetItemRect(
          m_pListCtrl->GetTopIndex(), &rcItem, LVIR_BOUNDS);
        rcToBeErased.bottom = rcItem.top;
        m_pListCtrl->InvalidateRect(&rcToBeErased);

        // erase area below bottom item
        m_pListCtrl->GetItemRect(iItemCount - 1, &rcItem, LVIR_BOUNDS);
        if (rcItem.bottom < rcThis.bottom)
        {
          rcToBeErased.top    = rcItem.bottom;
          rcToBeErased.bottom = rcThis.bottom;
        }
        else
          return;
      }

      m_pListCtrl->InvalidateRect(&rcToBeErased);
    }
  }
}

/*** Rejustify first column of listview control to enable a right- ***********/
/*** justified or centerd first column                             ***********/
void CListBase::JustifyFirstColumn(int nFormat)
{
  m_iFormatOfSubItem0 = nFormat;

  if (m_pListCtrl->GetStyle() & LVS_OWNERDRAWFIXED ||
      m_dwExtendedStyle       & LVS_EX_FULLROWSELECT)
  {
    CHeaderCtrl* pHeaderCtrl = m_pListCtrl->GetHeaderCtrl();
    ASSERT(pHeaderCtrl);

	if (pHeaderCtrl)
	{
		HDITEM hdrItem;

		hdrItem.mask = HDI_FORMAT;
		if (pHeaderCtrl->GetItem(0, &hdrItem))
		{
		  hdrItem.fmt =
			hdrItem.fmt & ~HDF_JUSTIFYMASK | nFormat & HDF_JUSTIFYMASK;
		  pHeaderCtrl->SetItem(0, &hdrItem);
		}
	}
  }
}

/*** Label editing will be started *******************************************/
BOOL CListBase::OnBeginLabelEdit(NMHDR* pNMHDR)
{
  NMLVDISPINFO* pNMLVDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);

  m_iItemEdit              = pNMLVDispInfo->item.iItem;
  m_bLabelEditingCancelled = false;
  m_pLabelEdit->SubclassWindow(m_pListCtrl->GetEditControl()->m_hWnd);
  return FALSE;
}

/*** Label editing will be cancelled *****************************************/
LRESULT CListBase::OnCancelEditLabel()
{
  m_bLabelEditingCancelled = true;
  return m_pListCtrl->Default();
}

/*** A column header has been clicked ****************************************/
BOOL CListBase::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMLISTVIEW pNMListView        = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
  int          iPhysicalColumn    = pNMListView->iSubItem;
  bool         bSortColumnChanged = false;

  pNMListView->iSubItem = GetLogicalIndex(iPhysicalColumn);
  if (pNMListView->iSubItem == abs(m_iSortColumn)-1)
    m_iSortColumn = -m_iSortColumn;
  else
  {
    m_iSortColumn      = pNMListView->iSubItem + 1;
    bSortColumnChanged = true;
  }
  SetSortIcon();
  if (bSortColumnChanged && m_visualStyle == Present)
    m_pListCtrl->SendMessage(LVM_SETSELECTEDCOLUMN, iPhysicalColumn);

	*pResult = 0;
  return FALSE;
}

/*** An item in the column selection menu has been selected ******************/
BOOL CListBase::OnCommand(WPARAM wParam)
{
  if (HIWORD(wParam) == 0)
    ShowColumn(static_cast<int>(wParam), !m_aColumnData[wParam]->m_bVisible);
  return TRUE;
}

/*** The user has right clicked the mouse ************************************/
void CListBase::OnContextMenu(CWnd* pWnd, CPoint point)
{
  if (pWnd == m_pListCtrl->GetHeaderCtrl())
  {
    if (m_iColumnHidingAllowed > 0)
    {
      CMenu menu;

      if (menu.CreatePopupMenu())
      {
        for (INT_PTR i = m_aColumnData.GetUpperBound(); i >= 0; --i)
          if (m_aColumnData[i]->m_bEnabled)
            menu.InsertMenu(0,
              MF_BYPOSITION                                              |
              (m_aColumnData[i]->m_bVisible ? MF_CHECKED : MF_UNCHECKED) |
              (m_aColumnData[i]->m_bHidingAllowed ? 0 : MF_GRAYED)       |
              MF_STRING, i, m_aColumnData[i]->m_pLVColumn->pszText);

        CPoint pt(0, 0);
        GetCursorPos       (&pt);
        menu.TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, m_pListCtrl, 0);
      }
    }
  }
  else if (pWnd == m_pListCtrl)
  {
    CWnd* pWndParent = pWnd->GetParent();

    if (pWndParent)
      pWndParent->SendMessage(
        WM_CONTEXTMENU, reinterpret_cast<WPARAM>(pWnd->m_hWnd),
        MAKELPARAM(point.x, point.y));
  }
}

/*** A list view (sub)item will be drawn *************************************/
void CListBase::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) 
{
  // If the list view control uses the Windows Vista Explorer style we have
  // nothing to do
  if (m_bExplorerStyle)
  {
    *pResult = CDRF_DODEFAULT;
    return;
  }

  ASSERT(m_pListCtrl->GetHeaderCtrl());

  NMLVCUSTOMDRAW* pNMLVCustomDraw = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

  switch (pNMLVCustomDraw->nmcd.dwDrawStage)
  {
    case CDDS_PREPAINT:
      *pResult = CDRF_NOTIFYITEMDRAW;
      break;

    case CDDS_ITEMPREPAINT:
      *pResult =
        CDRF_NOTIFYSUBITEMDRAW |
        (m_bBkImage && !(m_dwExtendedStyle & LVS_EX_DOUBLEBUFFER) ?
        CDRF_NOTIFYPOSTPAINT : 0);
      break;

    case CDDS_ITEMPREPAINT | CDDS_SUBITEM:
    {
      int iSortColumn = abs(m_iSortColumn) - 1;

      if (m_bColorSortColumn                     &&
          m_iSortColumn != 0                     &&
          m_aColumnData[iSortColumn]->m_bEnabled &&
          m_aColumnData[iSortColumn]->m_bVisible &&
          pNMLVCustomDraw->iSubItem == GetPhysicalIndex(iSortColumn))
        pNMLVCustomDraw->clrTextBk = m_dwColSortColor;
      else
        pNMLVCustomDraw->clrTextBk = m_pListCtrl->GetBkColor();

      *pResult = CDRF_NEWFONT | CDRF_NOTIFYPOSTPAINT;
      break;
    }

    case CDDS_ITEMPOSTPAINT | CDDS_SUBITEM:
    {
      // special treatment for first subitem:
      // fill empty area left of text label
      int   iItem    = static_cast<int>(pNMLVCustomDraw->nmcd.dwItemSpec);
      int   iSubItem = pNMLVCustomDraw->iSubItem;
      CRect rcItem;
      m_pListCtrl->GetHeaderCtrl()->GetItemRect(iSubItem, rcItem);
      int   iColumnWidth = rcItem.Width();
      int   iLeftX       = rcItem.left - m_pListCtrl->GetScrollPos(SB_HORZ);
      bool  bFirstColumn = rcItem.left == 0;
      bool  bHasFocus    = m_pListCtrl->GetFocus() == m_pListCtrl;
      CDC*  pDC          = CDC::FromHandle(pNMLVCustomDraw->nmcd.hdc);
      CRect rc(rcItem);

      m_bAlwaysGetSmallIconRect = true;
      m_pListCtrl->GetSubItemRect(iItem, iSubItem, LVIR_ICON, rc);
      m_bAlwaysGetSmallIconRect = false;
      if (iSubItem > 0)
        if (  m_dwExtendedStyle & LVS_EX_SUBITEMIMAGES && !bFirstColumn ||
            !(m_dwExtendedStyle & LVS_EX_SUBITEMIMAGES))
          rc.right += m_iIconXOff;
        else if (m_dwExtendedStyle & LVS_EX_SUBITEMIMAGES &&
                 m_visualStyle == Present)
          rc.right += m_iFirstColXOff;

      CBrush brushColColor;
      bool   bFullRowSelect = (m_dwExtendedStyle & LVS_EX_FULLROWSELECT) != 0;

      LVITEM item;
      item.mask      = LVIF_IMAGE | LVIF_STATE;
      item.iItem     = iItem;
      item.iSubItem  = iSubItem;
      item.stateMask =
        LVIS_SELECTED | LVIS_FOCUSED | LVIS_STATEIMAGEMASK | LVIS_OVERLAYMASK;
      m_pListCtrl->GetItem(&item);

      bool bEraseBkgnd = false;

      if (!bFirstColumn                                        &&
          bFullRowSelect                                       &&
          item.state & LVIS_SELECTED                           &&
          bHasFocus                                            &&
          m_dwExtendedStyle & (LVS_EX_UNDERLINEHOT |
            LVS_EX_ONECLICKACTIVATE | LVS_EX_TWOCLICKACTIVATE) &&
          item.iItem == m_pListCtrl->GetHotItem())
        // create brush with hot-tracked color
        brushColColor.CreateSolidBrush(m_dwHotLite);
      else if (!bFirstColumn              &&
               bFullRowSelect             &&
               item.state & LVIS_SELECTED &&
               bHasFocus)
        // create brush with highlight color
        brushColColor.CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
      else if (!bFirstColumn              &&
               bFullRowSelect             &&
               item.state & LVIS_SELECTED &&
               m_pListCtrl->GetStyle() & LVS_SHOWSELALWAYS)
        // create brush with highlight (nonfocus) color
        brushColColor.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
      else
        // fill empty area left of text label
        // by sending a WM_ERASEBKGND message
        bEraseBkgnd = true;

      if (bEraseBkgnd)
      {
        rc.left = iLeftX;
        if (iLeftX > rc.right) rc.right = iLeftX;
        EraseRect(pDC, rc);
      }
      else
      {
        // select new brush and save previous brush
        CBrush* pbrushPrev = pDC->SelectObject(&brushColColor);

        // color area left of text label
        if (iSubItem == 0 ||
            m_dwExtendedStyle & LVS_EX_SUBITEMIMAGES && item.iImage > 0)
          pDC->PatBlt(
            iLeftX, rc.top, __max(rc.left, rc.right) - iLeftX, rc.Height(),
            PATCOPY);

        // restore previous brush
        pDC->SelectObject(pbrushPrev);
      }

      if (iSubItem == 0 && iColumnWidth > m_iIconXOff)
      {
        // draw state icon
        CImageList* pimglst = m_pListCtrl->GetImageList(LVSIL_STATE);
        if (pimglst)
        {
          int iImage = (item.state & LVIS_STATEIMAGEMASK) >> 12;
          if (iImage > 0)
          {
            IMAGEINFO imgInfo;
            // image indices are zero-based
            if (pimglst->GetImageInfo(--iImage, &imgInfo) &&
                GetStateIconRect(item.iItem, rc)          &&
                rc.Width() > 0)
            {
              int  iRcWidth   = rc.Width();
              int  iRcHeight  = rc.Height();
              long lImgWidth  = imgInfo.rcImage.right  - imgInfo.rcImage.left;
              long lImgHeight = imgInfo.rcImage.bottom - imgInfo.rcImage.top;
              long lDiffHorz  = iRcWidth  - lImgWidth;
              long lDiffVert  = iRcHeight - lImgHeight;

              // size of state icon to be drawn
              SIZE sz =
              {
                lDiffHorz >= 0 ? lImgWidth  : iRcWidth,
                lDiffVert >= 0 ? lImgHeight : iRcHeight
              };

              // coordinates of state icon's upper left corner
              POINT pt = {rc.left, rc.top};
              if (lDiffVert > 2) pt.y += lDiffVert / 2;

              pimglst->DrawIndirect(
                pDC, iImage, pt, sz, CPoint(0, 0),
                item.state & LVIS_SELECTED && bHasFocus ?
                  ILD_SELECTED : ILD_NORMAL,
                SRCCOPY, CLR_NONE);
            }
          }
        }
      }

      if (iSubItem == 0 && iColumnWidth > m_iIconXOff ||
          m_dwExtendedStyle & LVS_EX_SUBITEMIMAGES &&
          iSubItem > 0 && iColumnWidth > 0)
      {
        // draw small icon
        CImageList* pimglst = m_pListCtrl->GetImageList(LVSIL_SMALL);
        if (pimglst)
          if (item.iImage > 0)
          {
            IMAGEINFO imgInfo;
            if (pimglst->GetImageInfo(item.iImage, &imgInfo) &&
                m_pListCtrl->GetSubItemRect(iItem, iSubItem, LVIR_ICON, rc))
            {
              int nIconOffset = rc.left - iLeftX;
              if (iColumnWidth > nIconOffset)
                pimglst->DrawIndirect(
                  pDC, item.iImage, rc.TopLeft(),
                  CSize(
                    __min(
                      iColumnWidth - nIconOffset,
                      imgInfo.rcImage.right - imgInfo.rcImage.left),
                    __min(
                      rc.Height(),
                      imgInfo.rcImage.bottom - imgInfo.rcImage.top)),
                  CPoint(0, 0),
                  (item.state & LVIS_SELECTED && bHasFocus ?
                  ILD_SELECTED : ILD_NORMAL) | item.state & LVIS_OVERLAYMASK,
                  SRCCOPY, CLR_NONE);
            }
          }
      }

      *pResult = CDRF_DODEFAULT;
      break;
    }

    case CDDS_ITEMPOSTPAINT:
    {
      // Correct a Windows drawing error which occurs if a background image is
      // set and the style LVS_EX_DOUBLEBUFFER is not applied.
      // The correction works as follows:
      // If a selected item has just been drawn, redraw all visible items which
      // were selected during the previous drawing cycle and aren't selected
      // anymore during this drawing cycle.
      int iItemJustDrawn = static_cast<int>(pNMLVCustomDraw->nmcd.dwItemSpec);

      LVITEM item;
      item.mask      = LVIF_STATE;
      item.iItem     = iItemJustDrawn;
      item.iSubItem  = 0;
      item.stateMask = LVIS_SELECTED;
      m_pListCtrl->GetItem(&item);

      if (item.state & LVIS_SELECTED)
      {
        RECT rcClientArea;
        m_pListCtrl->GetClientRect(&rcClientArea);

        bool bItemJustDrawnFound = false;

        for (POSITION pos =
               m_lstVisibleItemsPreviouslySelected.GetHeadPosition();
             pos;)
        {
          POSITION posCurrent = pos;
          int      iItem      =
            m_lstVisibleItemsPreviouslySelected.GetNext(pos);

          if (iItem != iItemJustDrawn)
          {
            RECT rcItem;
            m_pListCtrl->GetItemRect(iItem, &rcItem, LVIR_BOUNDS);
            if (rcItem.bottom >= rcClientArea.top && 
                rcItem.top    <= rcClientArea.bottom)
            {
              // Item visible
              item.iItem = iItem;
              m_pListCtrl->GetItem(&item);
              if (!(item.state & LVIS_SELECTED))
              {
                // Item not selected anymore
                m_pListCtrl->InvalidateRect                 (&rcItem);
                m_lstVisibleItemsPreviouslySelected.RemoveAt(posCurrent);
              }
            }
            else
              // Item not visible
              m_lstVisibleItemsPreviouslySelected.RemoveAt(posCurrent);
          }
          else
            bItemJustDrawnFound = true;
        }

        if (!bItemJustDrawnFound)
          // Remember selected item just drawn
          m_lstVisibleItemsPreviouslySelected.AddTail(iItemJustDrawn);
      }
      else
        // If the item just been drawn was selected during the previous drawing
        // cycle redraw it.
        for (POSITION pos =
               m_lstVisibleItemsPreviouslySelected.GetHeadPosition();
             pos;)
        {
          POSITION posCurrent = pos;
          int      iItem      =
            m_lstVisibleItemsPreviouslySelected.GetNext(pos);

          if (iItem == iItemJustDrawn)
          {
            RECT rcClientArea;
            m_pListCtrl->GetClientRect(&rcClientArea);
            RECT rcItem;
            m_pListCtrl->GetItemRect(iItem, &rcItem, LVIR_BOUNDS);
            if (rcItem.bottom >= rcClientArea.top && 
                rcItem.top    <= rcClientArea.bottom)
            {
              // Item visible
              item.iItem = iItem;
              m_pListCtrl->GetItem       (&item);
              m_pListCtrl->InvalidateRect(&rcItem);
            }

            m_lstVisibleItemsPreviouslySelected.RemoveAt(posCurrent);
          }
        }

      *pResult = CDRF_DODEFAULT;
      break;
    }

    default:
      *pResult = CDRF_DODEFAULT;
      break;
  }
}

/*** All items will be removed ***********************************************/
LRESULT CListBase::OnDeleteAllItems()
{
  BOOL bSuccess = TRUE;

  if (!(m_pListCtrl->GetStyle() & LVS_OWNERDATA))
    // First remove all item data ..
    for (int nItem =
           static_cast<int>(
             m_pListCtrl->DefWindowProc(LVM_GETITEMCOUNT, 0, 0));
         --nItem >= 0;)
    {
      LVITEM lvItem = {LVIF_PARAM, nItem, 0};

      if (m_pListCtrl->DefWindowProc(LVM_GETITEM, 0,
                                    reinterpret_cast<LPARAM>(&lvItem)))
        delete reinterpret_cast<ITEM_DATA*>(lvItem.lParam);
      else
      {
        ASSERT(false);
        bSuccess = FALSE;
      }
    }

  // ... then remove all items
  m_pListCtrl->Default();

  return bSuccess;
}

/*** A column will be deleted ************************************************/
LRESULT CListBase::OnDeleteColumn(WPARAM wParam)
{
  int     nColumn      = static_cast<int>(wParam);
  INT_PTR nColumnCount = m_aColumnData.GetSize();
  if (nColumn < 0 || nColumn >= nColumnCount) return FALSE;

  LRESULT lResult =
    m_aColumnData[nColumn]->m_bEnabled && m_aColumnData[nColumn]->m_bVisible ?
    m_pListCtrl->DefWindowProc(LVM_DELETECOLUMN, GetPhysicalIndex(nColumn), 0)
      : TRUE;

  if (lResult)
  {
    // adjust column order
    int i;
    for (i = 0; i < nColumnCount; ++i)
      if (m_aColumnData[i]->m_nOrder > m_aColumnData[nColumn]->m_nOrder)
        --m_aColumnData[i]->m_nOrder;

    delete m_aColumnData[nColumn];
    m_aColumnData.RemoveAt(nColumn);

    if (m_iSortColumn)
    {
      // adjust index of sort column
      if (m_iSortColumn < 0)
      {
        if (nColumn < -m_iSortColumn) ++m_iSortColumn;
      }
      else
      {
        if (nColumn < m_iSortColumn) --m_iSortColumn;
      }
      if (abs(m_iSortColumn) == nColumn) m_iSortColumn = 0;
    }

    // delete subitem structures belonging to column
    for (i = static_cast<int>(m_pListCtrl->DefWindowProc(
           LVM_GETITEMCOUNT, 0, 0)); --i >= 0;)
    {
      LVITEM lvItem = {LVIF_PARAM, i, 0};

      if (m_pListCtrl->DefWindowProc(LVM_GETITEM, 0,
                                     reinterpret_cast<LPARAM>(&lvItem)))
      {
        ITEM_DATA* pItemData = reinterpret_cast<ITEM_DATA*>(lvItem.lParam);
        LVITEM*    pLVItem   = pItemData->m_apLVItem[nColumn];

        pItemData->m_apLVItem.RemoveAt(nColumn);
        if (pLVItem)
        {
          delete[] pLVItem->pszText;
          delete pLVItem;
        }
      }
    }
  }

  return lResult;
}

/*** An item will be removed *************************************************/
LRESULT CListBase::OnDeleteItem(WPARAM wParam)
{
  int nItem = static_cast<int>(wParam);
  if (nItem < 0) return FALSE;

  LVITEM lvItem = {LVIF_PARAM, nItem, 0};

  if (m_pListCtrl->DefWindowProc(LVM_GETITEM, 0,
                                 reinterpret_cast<LPARAM>(&lvItem)) &&
      m_pListCtrl->Default())
  {
    // remove administration data
    delete reinterpret_cast<ITEM_DATA*>(lvItem.lParam);
    return TRUE;
  }
  else
    return FALSE;
}

/*** The list view control will be destroyed *********************************/
void CListBase::OnDestroy()
{
  m_pListCtrl->SendMessage(LVM_CANCELEDITLABEL);

  if (!(m_pListCtrl->GetStyle() & LVS_OWNERDATA))
    // delete all items explicitly to ensure
    // that all administration data will be deleted, too
    m_pListCtrl->DeleteAllItems();

  m_pListCtrl->Default();
}

/*** Label editing will be finished ******************************************/
BOOL CListBase::OnEndLabelEdit(NMHDR* pNMHDR)
{
  if (m_bOnEndLabelEdit) return FALSE;

  m_bOnEndLabelEdit = true;

  // notify parent window
  CWnd* pWndParent = m_pListCtrl->GetParent();

  if (pWndParent)
  {
    LVITEM* pItem = &reinterpret_cast<NMLVDISPINFO*>(pNMHDR)->item;

    if (!m_bLabelEditingCancelled)
    {
      m_pLabelEdit->GetWindowText(m_strEditedLabel);
      int iBufLen = __max(m_strEditedLabel.GetLength() + 1, 260);
      pItem->pszText    = m_strEditedLabel.GetBuffer(iBufLen);
      pItem->cchTextMax = iBufLen;
    }
    LRESULT validated =
      pWndParent->SendMessage(
        WM_NOTIFY, m_pListCtrl->GetDlgCtrlID(),
        reinterpret_cast<LPARAM>(pNMHDR));
    if (!m_bLabelEditingCancelled)
    {
      m_strEditedLabel.ReleaseBuffer();
      if (validated)
      {
        pItem->mask = LVIF_TEXT;
        m_pListCtrl->SetItem(pItem);
      }
    }
  }
  m_iItemEdit       = -1;
  m_bOnEndLabelEdit = false;
  return TRUE;
}

/*** The background will be erased *******************************************/
BOOL CListBase::OnEraseBkgnd(CDC* pDC) 
{
  if (m_bColorSortColumn && m_iSortColumn != 0 && m_visualStyle != Present)
  {
    int iAbsSortColumn = abs(m_iSortColumn) - 1;

    if (m_aColumnData[iAbsSortColumn]->m_bEnabled &&
        m_aColumnData[iAbsSortColumn]->m_bVisible)
    {
      CRect rc;
      if (!m_pListCtrl->GetHeaderCtrl()->GetItemRect(
            GetPhysicalIndex(iAbsSortColumn), rc))
        return m_pListCtrl->Default() != 0;

      int nXScrlOff = m_pListCtrl->GetScrollPos(SB_HORZ);
      int nLeftX    = rc.left  - nXScrlOff;
      int nRightX   = rc.right - nXScrlOff;

      pDC->GetClipBox(rc);      // get area to be erased
      if (nLeftX < rc.right && nRightX > rc.left)
      {
        CBrush  brushSortColor(m_dwColSortColor);
        CBrush* pbrushPrev = pDC->SelectObject(&brushSortColor);

        // remember clipping area in rectangular region
        CRgn rgn;
        rgn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);

        // erase area inside sort column with sort color
        if (nLeftX  > rc.left)  rc.left  = nLeftX;
        if (nRightX < rc.right) rc.right = nRightX;
        pDC->PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), PATCOPY);

        // exclude sort column from clipping area
        pDC->ExcludeClipRect(rc);

        // restore previous brush
        pDC->SelectObject(pbrushPrev);

        // erase background w/o sort column
        BOOL bResult = m_pListCtrl->Default() != 0;

        // restore original clipping area
        pDC->SelectClipRgn(&rgn);

        return bResult;
      }
    }
  }

  return m_pListCtrl->Default() != 0;
}

/*** A specific item will be searched ****************************************/
LRESULT CListBase::OnFindItem(WPARAM wParam, LPARAM lParam)
{
  int iStart = static_cast<int>(wParam);
  ASSERT(iStart >= -1);

  const LVFINDINFO* plvfi = reinterpret_cast<const LVFINDINFO*>(lParam);

  if (plvfi->flags & LVFI_PARAM)
  {
    int nItemCount = m_pListCtrl->GetItemCount();

    for (int nItem = iStart; ++nItem < nItemCount;)
    {
      LVITEM lvItem = {LVIF_PARAM, nItem, 0};

      if (m_pListCtrl->DefWindowProc(LVM_GETITEM, 0,
                                     reinterpret_cast<LPARAM>(&lvItem)))
        if (reinterpret_cast<ITEM_DATA*>(lvItem.lParam)->m_lParam ==
            plvfi->lParam) return nItem;
    }

    // wrap around?
    if (iStart >= 0 && plvfi->flags & LVFI_WRAP)
      for (int nItem = 0; nItem <= iStart; ++nItem)
      {
        LVITEM lvItem = {LVIF_PARAM, nItem, 0};

        if (m_pListCtrl->DefWindowProc(LVM_GETITEM, 0,
                                       reinterpret_cast<LPARAM>(&lvItem)))
          if (reinterpret_cast<ITEM_DATA*>(lvItem.lParam)->m_lParam ==
              plvfi->lParam) return nItem;
      }

    return -1;
  }
  else
    return m_pListCtrl->Default();
}

/*** The attributes of a column will be retrieved ****************************/
LRESULT CListBase::OnGetColumn(WPARAM wParam, LPARAM lParam)
{
  int nColumn = static_cast<int>(wParam);
  if (nColumn < 0 || nColumn >= m_aColumnData.GetSize()) return FALSE;

  LVCOLUMN* pLVColumn = reinterpret_cast<LVCOLUMN*>(lParam);

  if (m_aColumnData[nColumn]->m_bEnabled && m_aColumnData[nColumn]->m_bVisible)
  {
    LRESULT lResult = m_pListCtrl->DefWindowProc(LVM_GETCOLUMN,
                                                 GetPhysicalIndex(nColumn),
                                                 lParam);

    if (lResult)
    {
      // adjust index and order
      if (pLVColumn->mask & LVCF_ORDER)
        pLVColumn->iOrder = m_aColumnData[nColumn]->m_nOrder;
      if (pLVColumn->mask & LVCF_SUBITEM) pLVColumn->iSubItem = nColumn;
    }

    return lResult;
  }
  else
  {
    LVCOLUMN* pLVColumnSrc = m_aColumnData[nColumn]->m_pLVColumn;

    // retrieve column attributes from remembered column data
    if (pLVColumn->mask & LVCF_FMT)
      if (pLVColumnSrc->mask & LVCF_FMT)
        pLVColumn->fmt = pLVColumnSrc->fmt;
      else
        pLVColumn->fmt = LVCFMT_LEFT;
    if (pLVColumn->mask & LVCF_IMAGE)
      if (pLVColumnSrc->mask & LVCF_IMAGE)
        pLVColumn->iImage = pLVColumnSrc->iImage;
      else
        pLVColumn->iImage = -1;
    if (pLVColumn->mask & LVCF_ORDER)
      pLVColumn->iOrder = m_aColumnData[nColumn]->m_nOrder;
    if (pLVColumn->mask & LVCF_SUBITEM) pLVColumn->iSubItem = nColumn;
    if (pLVColumn->mask & LVCF_TEXT &&
        pLVColumn->pszText && pLVColumn->cchTextMax > 0)
      if (pLVColumnSrc->mask & LVCF_TEXT)
        if (_tcslen(pLVColumnSrc->pszText) >=
            static_cast<size_t>(pLVColumn->cchTextMax - 1))
        {
          _tcsncpy(pLVColumn->pszText, pLVColumnSrc->pszText,
                   pLVColumn->cchTextMax - 1);
          pLVColumn->pszText[pLVColumn->cchTextMax - 1] = _T('\0');
        }
        else
          _tcscpy(pLVColumn->pszText, pLVColumnSrc->pszText);
      else
        *pLVColumn->pszText = _T('\0');
    if (pLVColumn->mask & LVCF_WIDTH)
      pLVColumn->cx = m_aColumnData[nColumn]->m_nWidth;

    return TRUE;
  }
}

/*** The current left-to-right order of columns will be retrieved ************/
LRESULT CListBase::OnGetColumnOrderArray(WPARAM wParam, LPARAM lParam)
{
  INT_PTR nCount = wParam;
  if (nCount <= 0) return 0;
  INT_PTR nColumnCount = m_aColumnData.GetSize();
  if (nCount > nColumnCount) nCount = nColumnCount;

  LPINT pArray = reinterpret_cast<LPINT>(lParam);

  for (int i = 0; i < nCount; ++i)
    for (int j = 0; j < nColumnCount; ++j)
      if (m_aColumnData[j]->m_nOrder == i) pArray[i] = j;

  return nCount;
}

/*** The width of a column will be retrieved *********************************/
LRESULT CListBase::OnGetColumnWidth(WPARAM wParam)
{
  int nColumn = static_cast<int>(wParam);
  if (nColumn < 0 || nColumn >= m_aColumnData.GetSize()) return 0;

  if (m_aColumnData[nColumn]->m_bEnabled && m_aColumnData[nColumn]->m_bVisible)
    return m_pListCtrl->DefWindowProc(LVM_GETCOLUMNWIDTH,
                                      GetPhysicalIndex(nColumn), 0);
  else
    // invisible column returns 0
    return 0;
}

/*** Information needed to display an item will be requested *****************/
BOOL CListBase::OnGetdispinfo(NMHDR* pNMHDR)
{
  if (m_bOnGetDispinfo) return FALSE;
  m_bOnGetDispinfo = true;

  LVITEM* pLVItem       = &reinterpret_cast<NMLVDISPINFO*>(pNMHDR)->item;
  bool    bNotifyParent = true;

  int iOrigSubItem  = pLVItem->iSubItem;
  pLVItem->iSubItem = GetLogicalIndex(iOrigSubItem);

  LPARAM  origLParam    = pLVItem->lParam;
  LVITEM* pLVItemStored =
    origLParam                                                              ?
    reinterpret_cast<ITEM_DATA*>(origLParam)->m_apLVItem[pLVItem->iSubItem] :
    0;

  if (!(m_pListCtrl->GetStyle() & LVS_OWNERDATA) && pLVItem->mask & LVIF_TEXT)
    if (pLVItemStored                   &&
        pLVItemStored->mask & LVIF_TEXT &&
        pLVItemStored->pszText != LPSTR_TEXTCALLBACK)
    {
      pLVItem->pszText = pLVItemStored->pszText;
      bNotifyParent    = false;
    }

  if (bNotifyParent)
  {
    // notify parent window
    CWnd* pwndParent = m_pListCtrl->GetParent();

    if (pwndParent)
    {
      if (pLVItemStored) pLVItem->lParam = pLVItemStored->lParam;
      pwndParent->SendMessage(WM_NOTIFY, m_pListCtrl->GetDlgCtrlID(),
                              reinterpret_cast<LPARAM>(pNMHDR));
      pLVItem->lParam = origLParam;   // restore original lParam
    }
  }

  // restore original subitem number
  pLVItem->iSubItem = iOrigSubItem;

  m_bOnGetDispinfo = false;
  return TRUE;
}

/*** Some or all of an item's attributes will be retrieved *******************/
LRESULT CListBase::OnGetItem(LPARAM lParam)
{
  LVITEM* pLVItem = reinterpret_cast<LVITEM*>(lParam);
  int     nColumn = pLVItem->iSubItem;

  if (nColumn < 0 || nColumn >= m_aColumnData.GetSize() || pLVItem->iItem < 0)
    return FALSE;

  bool bVisible =
    m_aColumnData[nColumn]->m_bEnabled && m_aColumnData[nColumn]->m_bVisible;
  UINT origMask = pLVItem->mask;

  if (bVisible)
    pLVItem->iSubItem = GetPhysicalIndex(nColumn);
  else
  {
    if (pLVItem->mask & ~LVIF_STATE) pLVItem->mask |= LVIF_PARAM;
    pLVItem->mask    &= LVIF_STATE | LVIF_PARAM;
    pLVItem->iSubItem = 0;
  }

  LRESULT lResult = m_pListCtrl->Default();
  pLVItem->mask     = origMask;
  pLVItem->iSubItem = nColumn;

  if (lResult && (!bVisible || pLVItem->mask != LVIF_STATE))
  {
    ITEM_DATA* pItemData = reinterpret_cast<ITEM_DATA*>(pLVItem->lParam);

    if (pLVItem->mask & LVIF_PARAM) pLVItem->lParam = pItemData->m_lParam;

    // column visible and only lParam (and state) shall be retrieved
    //   --> all has been done!
    if (bVisible) return lResult;

    LVITEM* pLVItemSrc = pItemData->m_apLVItem[nColumn];

    // retrieve item attributes from remembered item data (except state)
    if (pLVItem->mask & LVIF_IMAGE)
      if (pLVItemSrc && pLVItemSrc->mask & LVIF_IMAGE)
        pLVItem->iImage = pLVItemSrc->iImage;
      else
        pLVItem->iImage = 0;
    if (pLVItem->mask & LVIF_INDENT)
      if (pLVItemSrc && pLVItemSrc->mask & LVIF_INDENT)
        pLVItem->iIndent = pLVItemSrc->iIndent;
      else
        pLVItem->iIndent = 0;
    if (pLVItem->mask & LVIF_TEXT &&
        pLVItem->pszText && pLVItem->cchTextMax > 0)
      if (pLVItemSrc && pLVItemSrc->mask & LVIF_TEXT)
        if (_tcslen(pLVItemSrc->pszText) >
            static_cast<size_t>(pLVItem->cchTextMax - 1))
        {
          _tcsncpy(pLVItem->pszText, pLVItemSrc->pszText,
                   pLVItem->cchTextMax - 1);
          pLVItem->pszText[pLVItem->cchTextMax - 1] = _T('\0');
        }
        else
          _tcscpy(pLVItem->pszText, pLVItemSrc->pszText);
      else
        *pLVItem->pszText = _T('\0');
  }

  return lResult;
}

/*** The rectangle bounding an item will be retrieved ************************/
LRESULT CListBase::OnGetItemRect(WPARAM wParam, LPARAM lParam)
{
  CRect* pRc = reinterpret_cast<CRect*>(lParam);

  switch (pRc->left)
  {
    // rectangle bounding whole item
    case LVIR_BOUNDS:
      return m_pListCtrl->Default();

    // rectangle bounding small icon
    case LVIR_ICON:

    // rectangle bounding label
    case LVIR_LABEL:
      if (m_bKeepLabelLeft)
        return
          m_pListCtrl->GetSubItemRect(
            static_cast<int>(wParam), GetLogicalIndex(OrderToIndex(0)),
            pRc->left, *pRc);
      else
        return m_pListCtrl->Default();

    default:
      ASSERT(false);
      break;
  }

  return 0L;
}

/*** The text of an item or subitem will be retrieved ************************/
LRESULT CListBase::OnGetItemText(WPARAM wParam, LPARAM lParam)
{
  INT_PTR nItem   = wParam;
  LVITEM* pLVItem = reinterpret_cast<LVITEM*>(lParam);
  int     nColumn = pLVItem->iSubItem;

  if (nColumn < 0 || nColumn >= m_aColumnData.GetSize() || nItem < 0)
    return FALSE;

  if (m_aColumnData[nColumn]->m_bEnabled && m_aColumnData[nColumn]->m_bVisible)
  {
    pLVItem->iSubItem = GetPhysicalIndex(nColumn);
    LRESULT lResult =
      m_pListCtrl->DefWindowProc(LVM_GETITEMTEXT, wParam, lParam);
    pLVItem->iSubItem = nColumn;

    return lResult;
  }
  else
  {
    if (m_pListCtrl->GetStyle() & LVS_OWNERDATA) return 0;

    LVITEM lvItem = {LVIF_PARAM, static_cast<int>(nItem), 0};

    if (m_pListCtrl->DefWindowProc(
          LVM_GETITEM, 0, reinterpret_cast<LPARAM>(&lvItem)))
    {
      LVITEM* pLVItemSrc =
        reinterpret_cast<ITEM_DATA*>(lvItem.lParam)->m_apLVItem[nColumn];

      // retrieve text from remembered item
      if (pLVItemSrc                   &&
          pLVItemSrc->mask & LVIF_TEXT &&
          pLVItemSrc->pszText          &&
          pLVItem->pszText             &&
          pLVItem->cchTextMax > 0)
        if (_tcslen(pLVItemSrc->pszText) >
            static_cast<size_t>(pLVItem->cchTextMax - 1))
        {
          _tcsncpy(
            pLVItem->pszText, pLVItemSrc->pszText, pLVItem->cchTextMax - 1);
          pLVItem->pszText[pLVItem->cchTextMax - 1] = _T('\0');
          return pLVItem->cchTextMax - 1;
        }
        else
        {
          _tcscpy(pLVItem->pszText, pLVItemSrc->pszText);
          return _tcslen(pLVItem->pszText);
        }
      else
      {
        *pLVItem->pszText = _T('\0');
        return 0;
      }
    }
    else
      return 0;
  }
}

/*** Calculates the bounding rectangle of a subitem **************************/
LRESULT CListBase::OnGetSubItemRect(WPARAM wParam, LPARAM lParam)
{
  CRect* pRc      = reinterpret_cast<CRect*>(lParam);
  int    iSubItem = pRc->top;

  ASSERT(iSubItem >= 0);

  // An invisible subitem has no bounding rectangle
  if (!m_aColumnData[iSubItem]->m_bEnabled ||
      !m_aColumnData[iSubItem]->m_bVisible) return 0L;

  int iItem            = static_cast<int>(wParam);
  int iPhysicalSubItem = GetPhysicalIndex(iSubItem);

  switch (pRc->left)
  {
    // rectangle bounding whole subitem
    case LVIR_BOUNDS:
    {
      pRc->top = iPhysicalSubItem;
      if (m_pListCtrl->Default())
      {
        // adjust width of bounding rectangle because LVM_GETSUBITEMRECT
        // doesn't always produce the correct result
        pRc->right = pRc->left + m_pListCtrl->GetColumnWidth(iSubItem);

        if (iPhysicalSubItem == 0)
        {
          CRect rc(LVIR_LABEL, 0, 0, 0);

          if (m_pListCtrl->DefWindowProc(
                LVM_GETSUBITEMRECT, wParam, reinterpret_cast<LPARAM>(&rc)))
          {
            pRc->right = rc.right;

            int iOrder = IndexToOrder(0);
            if (iOrder > 0)
            {
              // The left edge of subitem 0 is identical with the right edge of
              // the subitem left of subitem 0.
              if (m_pListCtrl->GetSubItemRect(
                    iItem, GetLogicalIndex(OrderToIndex(iOrder - 1)),
                    LVIR_BOUNDS, rc))
              {
                pRc->left = rc.right;
                return 1L;
              }
            }
            else
              return 1L;
          }
        }
        else
          return 1L;
      }
      else
        // in case of error restore original subitem number
        pRc->top = iSubItem;
      break;
    }

    // rectangle bounding small icon
    case LVIR_ICON:
    {
      CRect rcIcon(*pRc);

      rcIcon.top = iPhysicalSubItem;
      if (m_pListCtrl->DefWindowProc(
            LVM_GETSUBITEMRECT, wParam, reinterpret_cast<LPARAM>(&rcIcon)))
      {
        CRect rcSubItem;      // rectangle bounding subitem

        if (m_pListCtrl->GetSubItemRect(
              iItem, iSubItem, LVIR_BOUNDS, rcSubItem))
          if (m_bKeepLabelLeft                    &&
              iSubItem                       >  0 &&
              IndexToOrder(iPhysicalSubItem) == 0)
          {
            CRect rcIcon0(LVIR_ICON, 0, 0, 0);
            CRect rcSubItem0;

            if (m_pListCtrl->DefWindowProc (
                  LVM_GETSUBITEMRECT, wParam,
                  reinterpret_cast<LPARAM>(&rcIcon0)) &&
                m_pListCtrl->GetSubItemRect(iItem, 0, LVIR_BOUNDS, rcSubItem0))
            {
              int nSmallIconXOff = __max(rcIcon0.left - rcSubItem0.left, 4);

              rcIcon.left += nSmallIconXOff;
              rcIcon.right = rcIcon.left + rcIcon0.Width();

              // clip rectangle at right edge if necessary
              INT_PTR nWidth =
                m_pListCtrl->DefWindowProc(
                  LVM_GETCOLUMNWIDTH, iPhysicalSubItem, 0);
              if (nSmallIconXOff + rcIcon.Width() >= nWidth)
                rcIcon.right = rcIcon.left - nSmallIconXOff + nWidth - 1;
              *pRc = rcIcon;
              return 1L;
            }
          }
          else if (iSubItem == 0     ||
                   !m_bKeepLabelLeft &&
                   m_dwExtendedStyle & LVS_EX_SUBITEMIMAGES)
          {
            // Does this subitem have a small icon being displayed?
            LVITEM item = {LVIF_IMAGE, iItem, iPhysicalSubItem};
            if (m_bAlwaysGetSmallIconRect                          ||
                m_pListCtrl->DefWindowProc(
                  LVM_GETITEM, 0, reinterpret_cast<LPARAM>(&item)) &&
                item.iImage > 0)
              // whole icon or part of it visible?
              if (rcIcon.left <= rcSubItem.right)
              {
                // clip rectangle at right edge if necessary
                if (rcIcon.right > rcSubItem.right) rcIcon.right = rcSubItem.right;
                *pRc = rcIcon;
                return 1L;
              }
          }
      }
      break;
    }

    // rectangle bounding label
    case LVIR_LABEL:
    {
      if (iSubItem                       == 0 && !m_bKeepLabelLeft ||
          IndexToOrder(iPhysicalSubItem) == 0 &&  m_bKeepLabelLeft)
      {
        RECT rcLabel = {LVIR_LABEL, 0};// rectangle bounding label of subitem 0

        if (m_pListCtrl->DefWindowProc(
              LVM_GETSUBITEMRECT, wParam, reinterpret_cast<LPARAM>(&rcLabel)))
        {
          CRect rcSubItem0;     // rectangle bounding subitem 0

          if (m_pListCtrl->GetSubItemRect(iItem, 0, LVIR_BOUNDS, rcSubItem0))
          if (IndexToOrder(0) > 0 && m_bKeepLabelLeft)
          {
            if (m_pListCtrl->GetSubItemRect(
                  iItem, GetLogicalIndex(OrderToIndex(0)), LVIR_BOUNDS, *pRc))
            {
              pRc->left += rcLabel.left - rcSubItem0.left;
              return 1L;
            }
          }
          else
          {
            *pRc = rcLabel;
            return 1L;
          }
        }
      }
      else
        if (m_pListCtrl->GetSubItemRect(iItem, iSubItem, LVIR_BOUNDS, *pRc))
        {
          CRect rcIcon;

          if (m_dwExtendedStyle & LVS_EX_SUBITEMIMAGES &&
              m_pListCtrl->GetSubItemRect(iItem, iSubItem, LVIR_ICON, rcIcon))
            pRc->left += rcIcon.Width() + 2;
          return 1L;
        }
      break;
    }

    default:
      ASSERT(false);
      break;
  }

  return 0L;
}

/*** Determines which list view item, if any, is at a specified position *****/
int CListBase::OnHitTest(LPARAM lParam)
{
  if (m_pListCtrl->Default() != -1)
  {
    LPLVHITTESTINFO pHitTestInfo = reinterpret_cast<LPLVHITTESTINFO>(lParam);

    if (pHitTestInfo->iItem >= 0)
      if (pHitTestInfo->flags & LVHT_ONITEM)
      {
        CRect rc;

        // Determine subitem
        for (pHitTestInfo->iSubItem = GetColumnCount() - 1;
             pHitTestInfo->iSubItem >= 0;
             --pHitTestInfo->iSubItem)
          if (m_pListCtrl->GetSubItemRect(
                pHitTestInfo->iItem, pHitTestInfo->iSubItem, LVIR_BOUNDS, rc)
              &&
              rc.PtInRect(pHitTestInfo->pt)) break;

        if (pHitTestInfo->iSubItem == -1)
          pHitTestInfo->flags = LVHT_NOWHERE;
        else if (GetLabelRect(pHitTestInfo->iItem, pHitTestInfo->iSubItem, rc)
                 &&
                 rc.PtInRect(pHitTestInfo->pt))
          pHitTestInfo->flags = LVHT_ONITEMLABEL;
        else if (m_pListCtrl->GetSubItemRect(
                   pHitTestInfo->iItem, pHitTestInfo->iSubItem, LVIR_ICON, rc)
                 &&
                 rc.PtInRect(pHitTestInfo->pt))
          pHitTestInfo->flags = LVHT_ONITEMICON;
        else if (GetStateIconRect(pHitTestInfo->iItem, rc) &&
                 rc.PtInRect(pHitTestInfo->pt))
          pHitTestInfo->flags = LVHT_ONITEMSTATEICON;
        else if (m_pListCtrl->GetItemRect(
                   pHitTestInfo->iItem, rc, LVIR_BOUNDS))
          if (!rc.PtInRect(pHitTestInfo->pt)    ||
              // The small area left from state icon is LVHT_NOWHERE!!!
              rc.left            > -m_iIconXOff &&
              pHitTestInfo->pt.x < __min(m_iIconXOff+rc.left, m_iIconXOff))
            pHitTestInfo->flags = LVHT_NOWHERE;
          else
            pHitTestInfo->flags = LVHT_ONITEM;
        else
          pHitTestInfo->flags = LVHT_ONITEM;
      }
    return pHitTestInfo->iItem;
  }
  else
    return -1;
}

/*** List control has been scrolled horizontally *****************************/
void CListBase::OnHScroll()
{
  m_pListCtrl->Default ();
  InvalidateNonItemArea();
}

/*** A new column will be inserted *******************************************/
LRESULT CListBase::OnInsertColumn(WPARAM wParam, LPARAM lParam)
{
  int     nColumn      = static_cast<int>(wParam);
  INT_PTR nColumnCount = m_aColumnData.GetSize();
  if (nColumn < 0 || nColumn > nColumnCount) return -1;

  LVCOLUMN* pLVColumn = DupLVColumn(reinterpret_cast<LVCOLUMN*>(lParam));

  // adjust column attributes according to the real physical conditions
  pLVColumn->mask &= ~LVCF_SUBITEM;   // mask unnecessary subitem number
  if (pLVColumn->mask & LVCF_ORDER)
  {
    ASSERT(pLVColumn->iOrder >= 0 && pLVColumn->iOrder <= nColumnCount);
    pLVColumn->iOrder = GetPhysicalOrder(pLVColumn->iOrder);
  }

  LRESULT lResult =
    m_pListCtrl->DefWindowProc(LVM_INSERTCOLUMN, GetPhysicalIndex(nColumn),
                               reinterpret_cast<LPARAM>(pLVColumn));

  if (lResult != -1)
  {
    if (nColumn == 0)
      // Rejustify first column of listview control to enable a right-justified
      // or centerd first column
      JustifyFirstColumn(reinterpret_cast<LVCOLUMN*>(lParam)->fmt);

    // create and fill column administration structure
    COLUMN_DATA* pColumnData = new COLUMN_DATA;

    pLVColumn->mask         |= LVCF_WIDTH;
    pLVColumn->cx            = 0;
    pColumnData->m_pLVColumn = pLVColumn;
    pColumnData->m_nOrder    = pLVColumn->mask & LVCF_ORDER ?
                               reinterpret_cast<LVCOLUMN*>(lParam)->iOrder :
                               nColumn;

    // adjust column order
    for (int i = 0; i < nColumnCount; ++i)
      if (m_aColumnData[i]->m_nOrder >= pColumnData->m_nOrder)
        ++m_aColumnData[i]->m_nOrder;

    // store column administration structure
    m_aColumnData.InsertAt(nColumn, pColumnData);

    if (m_iSortColumn)
      // adjust index of sort column
      if (m_iSortColumn < 0)
      {
        if (nColumn < -m_iSortColumn) --m_iSortColumn;
      }
      else
        if (nColumn < m_iSortColumn) ++m_iSortColumn;

    // insert subitem placeholders belonging to column
    for (int i =
           static_cast<int>(
             m_pListCtrl->DefWindowProc(LVM_GETITEMCOUNT, 0, 0));
         --i >= 0;)
    {
      LVITEM lvItem = {LVIF_PARAM, i, 0};

      if (m_pListCtrl->DefWindowProc(
            LVM_GETITEM, 0, reinterpret_cast<LPARAM>(&lvItem)))
        reinterpret_cast<ITEM_DATA*>(lvItem.lParam)->m_apLVItem.InsertAt(
          nColumn, 0, 1);
    }
  }
  else
  {
    delete[] pLVColumn->pszText;
    delete pLVColumn;
  }

  return lResult;
}

/*** A new item will be inserted *********************************************/
LRESULT CListBase::OnInsertItem(LPARAM lParam)
{
  LVITEM* pLVItemSrc = reinterpret_cast<LVITEM*>(lParam);
  if (pLVItemSrc->iItem < 0) return -1;
  LVITEM* pLVItem = DupLVItem(pLVItemSrc);

  // save lParam in administration data
  ITEM_DATA* pItemData = new ITEM_DATA;
  if (pLVItemSrc->mask & LVIF_PARAM) pItemData->m_lParam = pLVItem->lParam;
  // ^administration data is physical lParam
  pLVItem->lParam = reinterpret_cast<LPARAM>(pItemData);
  pLVItem->mask  |= LVIF_PARAM;

  // physical text is always LPSTR_TEXTCALLBACK
  LPTSTR pszOrigText = pLVItem->pszText;
  if (pLVItemSrc->mask    &  LVIF_TEXT          &&
      pLVItemSrc->pszText != LPSTR_TEXTCALLBACK &&
      !(m_pListCtrl->GetStyle() & (LVS_SORTASCENDING | LVS_SORTDESCENDING)))
    pLVItem->pszText = LPSTR_TEXTCALLBACK;
  
  LRESULT lResult =
    m_pListCtrl->DefWindowProc(LVM_INSERTITEM, 0,
                               reinterpret_cast<LPARAM>(pLVItem));

  if (lResult != -1)
  {
    // correct item data
    pLVItem->mask    = pLVItemSrc->mask;
    pLVItem->iItem   = static_cast<int>(lResult);
    pLVItem->pszText = pszOrigText;

    // insert item into administration data for column 0
    pItemData->m_apLVItem.InsertAt(0, pLVItem);

    // insert placeholders for other columns
    INT_PTR nColumnCount = m_aColumnData.GetSize();
    for (int nColumn = 1; nColumn < nColumnCount; ++nColumn)
      pItemData->m_apLVItem.InsertAt(nColumn, 0, 1);

    RefreshToolTips();
  }
  else
  {
    if (pLVItemSrc->pszText != LPSTR_TEXTCALLBACK) delete[] pszOrigText;
    delete pLVItem;
    delete pItemData;
  }

  return lResult;
}

/*** A key has been pressed  *************************************************/
void CListBase::OnKeyDown(UINT nChar) 
{
  switch (nChar)
  {
    // Space
    case VK_SPACE:
    {
      // Space --> toggle checkbox state of all selected items
      int nItem = m_pListCtrl->GetNextItem(-1, LVNI_FOCUSED);

      if (m_dwExtendedStyle & LVS_EX_CHECKBOXES && nItem >= 0)
      {
        BOOL bChecked = !m_pListCtrl->GetCheck(nItem);

        m_pListCtrl->SetCheck(nItem, bChecked);
        for (POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition(); pos;)
          m_pListCtrl->SetCheck(
            m_pListCtrl->GetNextSelectedItem(pos), bChecked);
      }
      else
        m_pListCtrl->Default();
      break;
    }

    // Numpad-Plus
    case VK_ADD:
      // Ctrl-Numpad-Plus --> set optimum width for all columns
      if (m_bControl && m_bKeepLabelLeft && IndexToOrder(0) > 0)
      {
        LVCOLUMN lvc;
	      lvc.mask = LVCF_FMT;

        int iIndex;
      	for (int nColumn = 0;
             m_pListCtrl->DefWindowProc(
               LVM_GETCOLUMN, iIndex = OrderToIndex(nColumn),
               reinterpret_cast<LPARAM>(&lvc));
             ++nColumn)
        {
          int iLogicalIndex = GetLogicalIndex(iIndex);
          int iOptWidth;

          if (iIndex == 0 || nColumn == 0)
          {
            // calculate needed column width
            iOptWidth = 0;
            for (int iItem = m_pListCtrl->GetItemCount(); --iItem >= 0;)
            {
              int iWidth =
                m_pListCtrl->GetStringWidth(
                  m_pListCtrl->GetItemText(iItem, iLogicalIndex));
              if (iWidth > iOptWidth) iOptWidth = iWidth;
            }

            if (iIndex > 0)
            {
              // add space for state icon and small icon
              CRect rcSubItem;
              if (m_pListCtrl->GetSubItemRect(
                    0, iLogicalIndex, LVIR_BOUNDS, rcSubItem))
              {
                CRect rcLabel;
                if (m_pListCtrl->GetSubItemRect(
                      0, iLogicalIndex, LVIR_LABEL, rcLabel))
                  iOptWidth += rcLabel.left - rcSubItem.left;
              }

              // add left offset
              iOptWidth += m_iFirstColXOff;
            }
            else
              // add left offset
              iOptWidth += m_iNextColXOff;

            // add right offset
            iOptWidth += m_iNextColXOff;
          }
          else
            iOptWidth = LVSCW_AUTOSIZE;

          m_pListCtrl->SetColumnWidth(iLogicalIndex, iOptWidth);
        }
      }
      else
        m_pListCtrl->Default();
      break;

    // Ctrl
    case VK_CONTROL:
      if (m_bKeepLabelLeft && IndexToOrder(0) > 0)
        m_bControl = true;
      else
        m_pListCtrl->Default();
      break;

    // All other keys
    default:
      m_pListCtrl->Default();
      break;
  }
}

/*** A key has been released *************************************************/
void CListBase::OnKeyUp(UINT nChar) 
{
	if (nChar == VK_CONTROL) m_bControl = false;
  m_pListCtrl->Default();  

}

/*** List control loses input focus ******************************************/
void CListBase::OnKillFocus() 
{
  m_pListCtrl->Default();

	// manually remove focus state so that custom drawing will function properly
  int nItem = m_pListCtrl->GetNextItem(-1, LVNI_SELECTED);
  if (nItem >= 0) m_pListCtrl->SetItemState(nItem, 0, LVIS_FOCUSED);

  // Reset current tooltip item
  m_bLabelUnfolded  = FALSE;
  m_fCurrentFlags   = 0;
  m_iCurrentItem    = -1;
  m_iCurrentSubItem = -1;
}

/*** The user double-clicks the left mouse button ****************************/
void CListBase::OnLButtonDblClk(CPoint point) 
{
  UINT flags = 0;
  int  nItem = m_pListCtrl->HitTest(point, &flags);

  if (nItem            >= 0                 &&
      m_dwExtendedStyle & LVS_EX_CHECKBOXES &&
      flags            == LVHT_ONITEMSTATEICON)
  {
    BOOL bChecked = !m_pListCtrl->GetCheck(nItem);

    if (m_pListCtrl->GetItemState(nItem, LVIS_SELECTED))
      for (POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition(); pos;)
        m_pListCtrl->SetCheck(
          m_pListCtrl->GetNextSelectedItem(pos), bChecked);
    else
      m_pListCtrl->SetCheck(nItem, bChecked);
  }
  else
    m_pListCtrl->Default();
}

/*** The user presses the left mouse button **********************************/
void CListBase::OnLButtonDown(CPoint point) 
{
  if (m_hCursorCustom) SetCursor(m_hCursorCustom);

  LVHITTESTINFO info  = {{point.x, point.y}};
  int           nItem = m_pListCtrl->SubItemHitTest(&info);

  if (nItem >= 0                            &&
      m_dwExtendedStyle & LVS_EX_CHECKBOXES &&
      info.flags       == LVHT_ONITEMSTATEICON)
  {
    BOOL bChecked = !m_pListCtrl->GetCheck(nItem);

    if (m_pListCtrl->GetItemState(nItem, LVIS_SELECTED))
      for (POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition(); pos;)
        m_pListCtrl->SetCheck(m_pListCtrl->GetNextSelectedItem(pos), bChecked);
    else
      m_pListCtrl->SetCheck(nItem, bChecked);
  }
  else
    m_pListCtrl->Default();

  SetHotCursorAndItem(&info);
}

/*** The user releases the left mouse button *********************************/
void CListBase::OnLButtonUp()
{
  if (m_pListCtrl->GetStyle() & LVS_OWNERDRAWFIXED)
    if (m_hCursorCustom) SetCursor(m_hCursorCustom);

  m_pListCtrl->Default();
}

/*** The mouse cursor leaves the client area of this list view control *******/
LRESULT CListBase::OnMouseLeave()
{
  m_bMouseInClientArea = false;

  POINT pt;
  if (GetCursorPos(&pt))
  {
    // Check whether the mouse cursor is hovering over the client area of this
    // list view control
    m_pListCtrl->ScreenToClient(&pt);
    BOOL bMouseInClientRect = m_pListCtrl->HitTest(pt) != -1;

    if (bMouseInClientRect)
    {
      // Check whether the mouse cursor is hovering over the header control
      CHeaderCtrl* pHdrCtrl = m_pListCtrl->GetHeaderCtrl();
      if (pHdrCtrl)
      {
        CRect rc;
        pHdrCtrl->GetClientRect(rc);
        bMouseInClientRect = !rc.PtInRect(pt);
      }
    }

    if (!bMouseInClientRect)
    {
      // Reset current tooltip item if the mouse cursor has left the client
      // rectangle of this list control
      m_bLabelUnfolded  = FALSE;
      m_fCurrentFlags   = 0;
      m_iCurrentItem    = -1;
      m_iCurrentSubItem = -1;
      m_pLabelTip->Activate(FALSE);
    }
  }

  if (m_dwExtendedStyle &
      (LVS_EX_UNDERLINEHOT | LVS_EX_ONECLICKACTIVATE |
       LVS_EX_TWOCLICKACTIVATE))
  {
    int iOldHotItem;

    if (m_pListCtrl->GetStyle() & LVS_OWNERDRAWFIXED)
    {
      iOldHotItem = m_iHotItem;
      m_iHotItem  = -1;
    }
    else
      iOldHotItem = m_pListCtrl->SetHotItem(-1);

    // Redraw the previous hot item because the list view control doesn't do it
    // always (depending of the position where the mouse cursor has left the
    // client area).
    if (iOldHotItem >= 0)
    {
      RECT rc;
      m_pListCtrl->GetItemRect   (iOldHotItem, &rc, LVIR_BOUNDS);
      m_pListCtrl->InvalidateRect(&rc, FALSE);
    }
  }

  if (m_hTheme && m_pListCtrl->GetStyle() & LVS_OWNERDRAWFIXED)
  {
    if (m_iItemUnderCursor >= 0)
    {
      RECT rc;
      m_pListCtrl->GetItemRect   (m_iItemUnderCursor, &rc, LVIR_BOUNDS);
      m_pListCtrl->InvalidateRect(&rc, FALSE);
    }
    m_iItemUnderCursor = -1;
  }

  return m_pListCtrl->Default();
}

/*** The mouse has been moved ************************************************/
void CListBase::OnMouseMove(CPoint point)
{
  m_bRefreshToolTips = false;

  m_pListCtrl->Default();

  // Set tooltip's WS_EX_TOPMOST style
  if (m_bFocusSet)
  {
    m_bFocusSet = false;
    if ((GetWindowLong(m_pListCtrl->GetTopLevelParent()->m_hWnd, GWL_EXSTYLE) &
        WS_EX_TOPMOST) != 0)
    {
      if (!m_bTopMost)
      {
        m_pLabelTip->SetWindowPos(
          &CWnd::wndTopMost, 0, 0, 0, 0,
          SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
        m_pToolTip->SetWindowPos(
          &CWnd::wndTopMost, 0, 0, 0, 0,
          SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
        m_bTopMost = true;
      }
    }
    else
      if (m_bTopMost)
      {
        m_pLabelTip->SetWindowPos(
          &CWnd::wndNoTopMost, 0, 0, 0, 0,
          SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
        m_pToolTip->SetWindowPos(
          &CWnd::wndNoTopMost, 0, 0, 0, 0,
          SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
        m_bTopMost = false;
      }
  }

  CRect rc;
  m_pListCtrl->GetClientRect(rc);
  if (!rc.PtInRect(point))
  {
#ifndef NDEBUG
      ATLTRACE2(ListCtrlEx, 1, _T("Client area left\n"));
#endif
    // Reset current tooltip item if the mouse cursor has left the client area
    m_bLabelUnfolded  = FALSE;
    m_fCurrentFlags   = 0;
    m_iCurrentItem    = -1;
    m_iCurrentSubItem = -1;
    m_pLabelTip->Activate(FALSE);
    m_pToolTip->Activate (FALSE);
    return;
  }

  if (!m_bMouseInClientArea)
  {
    m_bMouseInClientArea = true;

    // Fire an event when the mouse cursor leaves the client area of this list
    // control
    TRACKMOUSEEVENT eventTrack =
      {sizeof(TRACKMOUSEEVENT), TME_LEAVE, m_pListCtrl->m_hWnd};

    _TrackMouseEvent(&eventTrack);
  }

  LVHITTESTINFO info  = {{point.x, point.y}};
  int           nItem = m_pListCtrl->SubItemHitTest(&info);
  SetHotCursorAndItem(&info);

  // Reset current rooltip item if this application has been deactivated
  if (GetActiveWindow() != 0)
    m_bIsActive = true;
  else
  {
    if (m_bIsActive)
    {
      m_bIsActive       = false;
      m_fCurrentFlags   = 0;
      m_iCurrentItem    = -1;
      m_iCurrentSubItem = -1;
    }
    return;
  }

  if (!m_bUpdateToolTips) return;    // update of tooltips suspended

  if (m_bLabelUnfolded    &&
      info.flags    != 0  &&
      nItem         != -1 &&
      info.iSubItem != -1 &&
      nItem         == m_iCurrentItem)
  {
    // check if cursor over unfolded label
    m_pLabelTip->GetWindowRect(rc);
    CPoint ptScreen(point);
    m_pListCtrl->ClientToScreen(&ptScreen);
    if (rc.PtInRect(ptScreen)) return;
  }

  // valid item?
  if (nItem >= 0 && (m_bSubItemTips && info.iSubItem >= 0 || !m_bSubItemTips))
  {
    bool bItemChanged = nItem != m_iCurrentItem;

    // item or subitem changed?
    if (bItemChanged                       ||
        info.iSubItem != m_iCurrentSubItem ||
        info.flags    != m_fCurrentFlags)
    {
#ifndef NDEBUG
      ATLTRACE2(
        ListCtrlEx, 1, _T("Item = %d, subitem = %d, flags = %s\n"),
        nItem, info.iSubItem,
        info.flags == LVHT_NOWHERE         ? _T("LVHT_NOWHERE")         :
        info.flags == LVHT_ONITEM          ? _T("LVHT_ONITEM")          :
        info.flags == LVHT_ONITEMICON      ? _T("LVHT_ONITEMICON")      :
        info.flags == LVHT_ONITEMLABEL     ? _T("LVHT_ONITEMLABEL")     :
        info.flags == LVHT_ONITEMSTATEICON ? _T("LVHT_ONITEMSTATEICON") :
                                             _T("<unknown>"));
#endif
      m_bLabelUnfolded = FALSE;
      m_strCurrentLabelTip.Empty();

      if (m_bToolTips)
        if (m_bSubItemTips)
        {
          // get tooltip for current subitem
          m_strCurrentToolTip =
            GetToolTip(nItem, info.iSubItem, info.flags, m_bLabelUnfolded);
          if (m_bLabelUnfolded)
          {
            m_strCurrentLabelTip = m_strCurrentToolTip;
            m_strCurrentToolTip.Empty();
          }
        }
        else if (bItemChanged)
        {
          // get tooltip for current item
          m_strCurrentToolTip = GetToolTip(nItem);
        }
      else
        m_strCurrentToolTip.Empty();

      if (m_strCurrentLabelTip.IsEmpty() &&
          m_bUnfoldLabel                 &&
          info.flags == LVHT_ONITEMLABEL)
      {
        // No tooltip displayed as label for subitem
        //   --> check if subitem text fits
        if (m_pListCtrl->GetSubItemRect(nItem, info.iSubItem, LVIR_LABEL, rc))
        {
          m_strCurrentLabelTip =
            m_pListCtrl->GetItemText(nItem, info.iSubItem);
          if (m_pListCtrl->GetStringWidth(m_strCurrentLabelTip) +
              (
                info.iSubItem                                 == 0 &&
                !m_bKeepLabelLeft                                  ||
                IndexToOrder(GetPhysicalIndex(info.iSubItem)) == 0 &&
                m_bKeepLabelLeft ?
                  m_iFirstColXOff : m_iNextColXOff
              ) +
              (
                info.iSubItem == 0 &&
                (!m_bKeepLabelLeft || IndexToOrder(0) == 0) ?
                  m_iFirstColXOff : m_iNextColXOff
              ) +
              (m_bExplorerStyle ? m_iColumnSeparatorWidth : 0) > rc.Width())
            m_bLabelUnfolded = TRUE;
          else
          {
            m_strCurrentLabelTip.Empty();
            m_bLabelUnfolded = FALSE;
          }
        }
      }

      m_iCurrentItem    = info.iItem;
      m_iCurrentSubItem = info.iSubItem;
      m_fCurrentFlags   = info.flags;

      LPMSG pCurMsg = AfxGetCurrentMessage();

      if (m_bLabelUnfolded)
      {
        m_pLabelTip->Activate     (TRUE);
        m_pLabelTip->UpdateTipText(m_strCurrentLabelTip, m_pListCtrl);
        m_pLabelTip->RelayEvent   (pCurMsg);
      }
      else
        m_pLabelTip->Activate(FALSE);

      if ((m_bSubItemTips || bItemChanged) && !m_strCurrentToolTip.IsEmpty())
      {
        m_iCurrentItem = nItem;

        m_pToolTip->Activate(TRUE);
        m_pToolTip->UpdateTipText(m_strCurrentToolTip, m_pListCtrl);
        m_pToolTip->RelayEvent   (pCurMsg);
        if (m_bLabelUnfolded)
        {
          // display tool tip if cursor hovers over expanded label
          m_pToolTip->UpdateTipText(m_strCurrentToolTip, m_pLabelTip);
          MSG msg = *pCurMsg;
          msg.hwnd = m_pLabelTip->m_hWnd;
          m_pToolTip->RelayEvent(&msg);
        }
      }
      else if (m_bSubItemTips || bItemChanged)
      {
        m_iCurrentItem = nItem;
        m_pToolTip->Activate(FALSE);
      }
    }
  }
  else
  {
    if (m_bLabelUnfolded)
    {
      m_bLabelUnfolded = FALSE;
      m_pLabelTip->Activate(FALSE);
    }
    else
      m_pToolTip->Activate(FALSE);

    m_fCurrentFlags   = 0;
    m_iCurrentItem    = -1;
    m_iCurrentSubItem = -1;
  }
}

/*** The mouse wheel has been rotated ****************************************/
BOOL CListBase::OnMouseWheel(CPoint point)
{
  BOOL bRet = m_pListCtrl->Default() != 0;

  CRect rc;
  m_pListCtrl->GetWindowRect(rc);
  // Force WM_MOUSEMOVE message, if the cursor position is inside the client
  // area of the list view control
  if (rc.PtInRect(point))
  {
    m_bRefreshToolTips = true;
    SetCursorPos(point.x, point.y);
  }
  return bRet;
}

/*** Divider in header control has been doubleclicked or dragged *************/
BOOL CListBase::OnNotify(LPARAM lParam) 
{
  BOOL         bRet     = FALSE;
  LPNMHDR      pNMHdr   = reinterpret_cast<LPNMHDR>(lParam);
  CHeaderCtrl* pHdrCtrl = m_pListCtrl->GetHeaderCtrl();

  ASSERT(pHdrCtrl);

  if (pHdrCtrl && pNMHdr->hwndFrom == pHdrCtrl->m_hWnd)
  {
    LPNMHEADER pNMHeader = reinterpret_cast<LPNMHEADER>(pNMHdr);

    switch (pNMHdr->code)
    {
      case HDN_DIVIDERDBLCLICKW:
      case HDN_DIVIDERDBLCLICKA:
        if (m_bKeepLabelLeft &&
            (
              GetLogicalIndex(pNMHeader->iItem)  > 0 &&
              IndexToOrder(pNMHeader->iItem)    == 0 ||
              pNMHeader->iItem                  == 0 &&
              IndexToOrder(pNMHeader->iItem)     > 0
            ))
        {
          // calculate needed column width
          int iFirstItem;
          int iLastItem;
          int iOptWidth       = 0;
          int iLogicalSubItem = GetLogicalIndex(pNMHeader->iItem);

          if (m_pListCtrl->GetStyle() & LVS_OWNERDATA)
          {
            // In a virtual list view control
            // at least the visible items and
            // at most the cached items will be considered.
            int iFirstVisibleItem = m_pListCtrl->GetTopIndex();

            iFirstItem = __min(m_iFirstCachedItem, iFirstVisibleItem);
            iLastItem  =
              __min(
                __max(
                  m_iLastCachedItem,
                  iFirstVisibleItem + m_pListCtrl->GetCountPerPage()),
                m_pListCtrl->GetItemCount() - 1);
          }
          else
          {
            iFirstItem = 0;
            iLastItem  = m_pListCtrl->GetItemCount() - 1;
          }

          for (int iItem = iFirstItem; iItem <= iLastItem; ++iItem)
          {
            int iWidth =
              m_pListCtrl->GetStringWidth(
                m_pListCtrl->GetItemText(iItem, iLogicalSubItem));
            if (iWidth > iOptWidth) iOptWidth = iWidth;
          }

          if (GetLogicalIndex(pNMHeader->iItem) > 0)
          {
            // add space for state icon and small icon
            CRect rcSubItem;
            if (m_pListCtrl->GetSubItemRect(
                  0, iLogicalSubItem, LVIR_BOUNDS, rcSubItem))
            {
              CRect rcLabel;
              if (m_pListCtrl->GetSubItemRect(
                    0, iLogicalSubItem, LVIR_LABEL, rcLabel))
                iOptWidth += rcLabel.left - rcSubItem.left;
            }

            // add left offset
            iOptWidth += m_iFirstColXOff;
          }
          else
            // add left offset
            iOptWidth += m_iNextColXOff;

          // add right offset
          iOptWidth += m_iNextColXOff;

          m_pListCtrl->DefWindowProc(LVM_SETCOLUMNWIDTH, pNMHeader->iItem, iOptWidth);
          bRet = TRUE;
        }
        break;

      case HDN_ENDDRAG:
        bRet = m_pListCtrl->Default() != 0;
        if (pNMHeader->pitem->iOrder >= 0)
        {
          int nColumn = GetLogicalIndex(pNMHeader->iItem);
          int nOrder  = GetLogicalOrder(pNMHeader->pitem->iOrder);

          if (nOrder < m_aColumnData[nColumn]->m_nOrder)
          {
            // adjust column order
            for (INT_PTR i = m_aColumnData.GetUpperBound(); i >= 0; --i)
              if (m_aColumnData[i]->m_nOrder >= nOrder &&
                  m_aColumnData[i]->m_nOrder <
                  m_aColumnData[nColumn]->m_nOrder)
                ++m_aColumnData[i]->m_nOrder;
            m_aColumnData[nColumn]->m_nOrder = nOrder;
          }
          else if (nOrder > m_aColumnData[nColumn]->m_nOrder)
          {
            // adjust column order
            for (INT_PTR i = m_aColumnData.GetUpperBound(); i >= 0; --i)
              if (m_aColumnData[i]->m_nOrder >
                  m_aColumnData[nColumn]->m_nOrder &&
                  m_aColumnData[i]->m_nOrder <= nOrder)
                --m_aColumnData[i]->m_nOrder;
            m_aColumnData[nColumn]->m_nOrder = nOrder;
          }
        }
        break;

      case HDN_ENDTRACKW:
      case HDN_ENDTRACKA:
      case HDN_ITEMCHANGEDW:
      case HDN_ITEMCHANGEDA:
        bRet = m_pListCtrl->Default() != 0;
        if (m_bColorSortColumn) InvalidateNonItemArea();
        break;

      case HDN_ITEMCLICK:
        m_pListCtrl->Default();
        // Suppress further processing of this message to prevent Windows from
        // sending the notification message LVN_COLUMNCLICK a second time!
        // For unknown reasons this is necessary in an Unicode environment
        // only.
        bRet = TRUE;
        break;

      default:
        break;
    }
  }

  return bRet;
}

/*** The contents of the display area of a virtual list view control have ****/
/*** been changed                                                         ****/
BOOL CListBase::OnODCacheHint(NMHDR* pNMHDR)
{
  LPNMLVCACHEHINT pNMLVCacheHint = reinterpret_cast<LPNMLVCACHEHINT>(pNMHDR);

  // remember caching area
  m_iFirstCachedItem = pNMLVCacheHint->iFrom;
  m_iLastCachedItem  = pNMLVCacheHint->iTo;

  return FALSE;
}

/*** Will be called when Windows or an application makes a request to ********/
/*** repaint a portion of the client area of this list view control   ********/
void CListBase::OnPaint()
{
	// first let the control do its default drawing.
	m_pListCtrl->Default();

  if (m_bColumnSeparators && !m_bBkImage)
  {
	  // now get the client rect so we know the line length and when to stop
    RECT rcClient;
	  m_pListCtrl->GetClientRect(&rcClient);

	  CClientDC dc(m_pListCtrl);
    CPen      penSeparator(PS_SOLID, 0, GetSysColor(COLOR_3DFACE));
    // select new pen and save previous pen
    CPen* ppenPrev = dc.SelectObject(&penSeparator);
    
	  // the border of the column is offset by the horz scroll
	  int          iBorderX    = -m_pListCtrl->GetScrollPos(SB_HORZ);
	  CHeaderCtrl* pHeaderCtrl = m_pListCtrl->GetHeaderCtrl();
	  int          iItemCount  = pHeaderCtrl->GetItemCount();

	  for (int iItem = 0; iItem < iItemCount; ++iItem)
	  {
      CRect rcItem;
      pHeaderCtrl->GetItemRect(OrderToIndex(iItem), rcItem);

		  // get the next border
		  iBorderX += rcItem.Width();

		  // if next border is outside client area, break out
		  if (iBorderX >= rcClient.right) break;

		  // Draw the line.
  	  // The bottom of the header corresponds to the top of the line.
		  dc.MoveTo(iBorderX-1, rcItem.bottom);
		  dc.LineTo(iBorderX-1, rcClient.bottom);
	  }

    // restore previous pen
    dc.SelectObject(ppenPrev);
  }
}

/*** The background color of the list view control will be set ***************/
LRESULT CListBase::OnSetBkColor(LPARAM lParam)
{
  if (m_bBkImage)
    if (lParam != CLR_NONE)
    {
      m_clrBkColor    = static_cast<COLORREF>(lParam);
      m_bBkColorKnown = true;
      m_bFixedBkColor = true;
      return TRUE;
    }

  if (m_pListCtrl->Default())
  {
    if (lParam != CLR_NONE)
    {
      m_clrBkColor    = static_cast<COLORREF>(lParam);
      m_bBkColorKnown = true;

      if (m_bColorSortColumn)
      {
        // force recalculation of sort column color
        m_bColorSortColumn = FALSE;
        ColorSortColumn();
      }
    }

    m_bFixedBkColor = true;
    return TRUE;
  }
  else
    return FALSE;
}

/*** An background image will be set *****************************************/
LRESULT CListBase::OnSetBkImage()
{
  m_bBkImage = m_pListCtrl->Default() != 0;
  if (m_bBkImage)
  {
    // Remember the current background color when a background image has been
    // set. Then set the background color to none to correct a drawing error
    // in the common control library < 6.0!
    if (!m_bBkColorKnown)
    {
      m_clrBkColor    = m_pListCtrl->GetBkColor();
      m_bBkColorKnown = true;
    }
    bool bFixedBkColor = m_bFixedBkColor;
    m_pListCtrl->SetBkColor(CLR_NONE);
    m_bFixedBkColor = bFixedBkColor;
  }
  else
    if (m_bBkColorKnown)
    {
      bool bFixedBkColor = m_bFixedBkColor;
      m_pListCtrl->SetBkColor(m_clrBkColor);
      m_bFixedBkColor = bFixedBkColor;
    }

  return m_bBkImage;
}

/*** The attributes of a column will be set **********************************/
LRESULT CListBase::OnSetColumn(WPARAM wParam, LPARAM lParam)
{
  int     nColumn      = static_cast<int>(wParam);
  INT_PTR nColumnCount = m_aColumnData.GetSize();
  if (nColumn < 0 || nColumn >= nColumnCount) return FALSE;

  LVCOLUMN* pLVColumn = DupLVColumn(reinterpret_cast<LVCOLUMN*>(lParam));

  // adjust column attributes according to the real physical conditions
  pLVColumn->mask &= ~LVCF_SUBITEM;   // mask unnecessary subitem number
  if (pLVColumn->mask & LVCF_ORDER)
  {
    ASSERT(pLVColumn->iOrder >= 0 && pLVColumn->iOrder < nColumnCount);
    pLVColumn->iOrder = GetPhysicalOrder(pLVColumn->iOrder);
  }

  LRESULT lResult =
    m_aColumnData[nColumn]->m_bEnabled && m_aColumnData[nColumn]->m_bVisible ?
    m_pListCtrl->DefWindowProc(LVM_SETCOLUMN, GetPhysicalIndex(nColumn),
                               reinterpret_cast<LPARAM>(pLVColumn)) : TRUE;

  if (lResult)
  {
    // update column data
    LVCOLUMN* pLVColumnDst = m_aColumnData[nColumn]->m_pLVColumn;
    if (pLVColumn->mask & LVCF_FMT) pLVColumnDst->fmt = pLVColumn->fmt;
    if (pLVColumn->mask & LVCF_IMAGE) pLVColumnDst->iImage = pLVColumn->iImage;
    if (pLVColumn->mask & LVCF_ORDER)
    {
      int nOrder = reinterpret_cast<LVCOLUMN*>(lParam)->iOrder;

      if (nOrder < m_aColumnData[nColumn]->m_nOrder)
      {
        // adjust column order
        for (int i = 0; i < nColumnCount; ++i)
          if (m_aColumnData[i]->m_nOrder >= nOrder &&
              m_aColumnData[i]->m_nOrder <  m_aColumnData[nColumn]->m_nOrder)
            ++m_aColumnData[i]->m_nOrder;
        m_aColumnData[nColumn]->m_nOrder = nOrder;
      }
      else if (nOrder > m_aColumnData[nColumn]->m_nOrder)
      {
        // adjust column order
        for (int i = 0; i < nColumnCount; ++i)
          if (m_aColumnData[i]->m_nOrder >  m_aColumnData[nColumn]->m_nOrder &&
              m_aColumnData[i]->m_nOrder <= nOrder)
            --m_aColumnData[i]->m_nOrder;
        m_aColumnData[nColumn]->m_nOrder = nOrder;
      }
    }
    if (pLVColumn->mask & LVCF_TEXT && pLVColumn->pszText)
    {
      delete[] pLVColumnDst->pszText;
      pLVColumnDst->pszText = new TCHAR[_tcslen(pLVColumn->pszText)+1];
      _tcscpy(pLVColumnDst->pszText, pLVColumn->pszText);
    }
    pLVColumnDst->mask |= pLVColumn->mask;
  }

  delete[] pLVColumn->pszText;
  delete pLVColumn;

  return lResult;
}

/*** The left-to-right order of columns will be set **************************/
LRESULT CListBase::OnSetColumnOrderArray(WPARAM wParam, LPARAM lParam)
{
  INT_PTR nCount = wParam;
  if (nCount <= 0) return 0;
  INT_PTR nColumnCount = m_aColumnData.GetSize();
  if (nCount > nColumnCount) nCount = nColumnCount;

  LPINT pArraySrc = reinterpret_cast<LPINT>(lParam);
  LPINT pArrayDst = new int[nCount];

  int n = 0;
  for (int i = 0; i < nCount; ++i)
  {
    int nColumn = pArraySrc[i];
    if (nColumn >= nColumnCount)
    {
      // illegal column index
      delete[] pArrayDst;
      return 0;
    }

    if (m_aColumnData[nColumn]->m_bEnabled &&
        m_aColumnData[nColumn]->m_bVisible)
      pArrayDst[n++] = GetPhysicalIndex(nColumn);
  }

  LRESULT lResult =
    m_pListCtrl->DefWindowProc(
      LVM_SETCOLUMNORDERARRAY, n, reinterpret_cast<LPARAM>(pArrayDst));

  delete[] pArrayDst;

  if (lResult)
    // adjust column order
    for (int i = 0; i < nCount; ++i)
    {
      int nColumn = pArraySrc[i];

      if (i < m_aColumnData[nColumn]->m_nOrder)
      {
        for (int j = 0; j < nColumnCount; ++j)
          if (m_aColumnData[j]->m_nOrder >= i &&
              m_aColumnData[j]->m_nOrder <  m_aColumnData[nColumn]->m_nOrder)
            ++m_aColumnData[j]->m_nOrder;
        m_aColumnData[nColumn]->m_nOrder = i;
      }
      else if (i > m_aColumnData[nColumn]->m_nOrder)
      {
        for (int j = 0; j < nColumnCount; ++j)
          if (m_aColumnData[j]->m_nOrder >  m_aColumnData[nColumn]->m_nOrder &&
              m_aColumnData[j]->m_nOrder <= i) --m_aColumnData[j]->m_nOrder;
        m_aColumnData[nColumn]->m_nOrder = i;
      }
    }

  return lResult;
}

/*** The width of a column will be changed ***********************************/
LRESULT CListBase::OnSetColumnWidth(WPARAM wParam, LPARAM lParam)
{
  int nColumn = static_cast<int>(wParam);
  if (nColumn < 0 || nColumn >= m_aColumnData.GetSize()) return FALSE;

  if (m_aColumnData[nColumn]->m_bEnabled && m_aColumnData[nColumn]->m_bVisible)
    return
      m_pListCtrl->DefWindowProc(
        LVM_SETCOLUMNWIDTH, GetPhysicalIndex(nColumn), lParam);
  else
  {
    // remember new column width
    m_aColumnData[nColumn]->m_nWidth = static_cast<int>(lParam);
    return TRUE;
  }
}

/*** The extended list view style will be set ********************************/
LRESULT CListBase::OnSetExtendedStyle(WPARAM wParam, LPARAM lParam)
{
  LRESULT dwResult = m_dwExtendedStyle;
  if (wParam == 0U) wParam = ~0U;
  m_dwExtendedStyle = static_cast<DWORD>(wParam & lParam);

  // Mask all style bits not supported by non-visual common control library
  if (m_visualStyle == NotPresent)
    m_dwExtendedStyle &= ~(LVS_EX_DOUBLEBUFFER | LVS_EX_SIMPLESELECT);

  // Hide the bits LVS_EX_INFOTIP and LVS_EX_LABELTIP from Windows
  DWORD dwExtendedStyle =
    m_dwExtendedStyle & ~(LVS_EX_INFOTIP | LVS_EX_LABELTIP);
  if (wParam & LVS_EX_INFOTIP)
    m_bToolTips = (lParam & LVS_EX_INFOTIP) != 0;
  if (wParam & LVS_EX_LABELTIP)
    m_bUnfoldLabel = (lParam & LVS_EX_LABELTIP) != 0;

  if (m_pListCtrl->GetStyle() & LVS_OWNERDRAWFIXED)
    // Hide the bits LVS_EX_UNDERLINEHOT, LVS_EX_ONECLICKACTIVATE, and
    // LVS_EX_TWOCLICKACTIVATE from Windows
    if (wParam &
        (LVS_EX_UNDERLINEHOT | LVS_EX_ONECLICKACTIVATE |
         LVS_EX_TWOCLICKACTIVATE))
    {
      if (lParam &
          (LVS_EX_UNDERLINEHOT | LVS_EX_ONECLICKACTIVATE |
           LVS_EX_TWOCLICKACTIVATE))
        PrepareHotUnderlining();
      else
        m_hCursorCustom = 0;

      dwExtendedStyle &=
        ~(LVS_EX_UNDERLINEHOT | LVS_EX_ONECLICKACTIVATE |
          LVS_EX_TWOCLICKACTIVATE);
    }
    else
      m_hCursorCustom = 0;
  
  m_pListCtrl->DefWindowProc(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwExtendedStyle);

  return dwResult;
}

/*** List control gains input focus ******************************************/
void CListBase::OnSetFocus() 
{
  m_pListCtrl->Default();

	// manually set focus state so that custom drawing will function properly
  int nItem = m_pListCtrl->GetNextItem(-1, LVNI_SELECTED);
  if (nItem >= 0) m_pListCtrl->SetItemState(nItem, LVIS_FOCUSED, LVIS_FOCUSED);

  m_bFocusSet = true;
}

/*** Assigns an image list to a list control *********************************/
LRESULT CListBase::OnSetImageList(WPARAM wParam)
{
  ASSERT(m_pListCtrl->GetHeaderCtrl());
  ASSERT(wParam != LVSIL_NORMAL);

  LRESULT dwResult = m_pListCtrl->Default();

  if (wParam == LVSIL_SMALL)
  {
    CHeaderCtrl* pHeaderCtrl = m_pListCtrl->GetHeaderCtrl();

    // restore image list with sort icons because default behavior is that the
    // header control shares its image list with the small icon list of the
    // list control
    if (IsWindow(pHeaderCtrl->m_hWnd))
      pHeaderCtrl->SetImageList(&m_imglstSortIcons);
  }

  return dwResult;
}

/*** Some or all of a list view items attributes will be set *****************/
LRESULT CListBase::OnSetItem(LPARAM lParam)
{
  LVITEM* pLVItemSrc = reinterpret_cast<LVITEM*>(lParam);
  int     nColumn    = pLVItemSrc->iSubItem;

  if (nColumn           < 0 || nColumn >= m_aColumnData.GetSize() ||
      pLVItemSrc->iItem < 0) return FALSE;

  LVITEM* pLVItem     = DupLVItem(pLVItemSrc);
  bool    bVisible    =
    m_aColumnData[nColumn]->m_bEnabled && m_aColumnData[nColumn]->m_bVisible;
  LRESULT lResult;
  LPTSTR  pszOrigText = pLVItem->pszText;

  if (bVisible     && pLVItemSrc->mask & ~LVIF_PARAM ||
      nColumn == 0 && pLVItemSrc->mask &  LVIF_STATE)
  {
    // column is visible and other attributes than lParam will be set
    //   or
    // column zero and at least state will be set
    //   --> do it physically
    pLVItem->mask &= ~LVIF_PARAM;
    if (bVisible)
    {
      if (pLVItemSrc->mask    &  LVIF_TEXT          &&
          pLVItemSrc->pszText != LPSTR_TEXTCALLBACK &&
          !(m_pListCtrl->GetStyle() &
          (LVS_SORTASCENDING | LVS_SORTDESCENDING)))
        pLVItem->pszText = LPSTR_TEXTCALLBACK;
    }
    else
      pLVItem->mask &= LVIF_STATE;

    if (pLVItem->mask)
    {
      pLVItem->iSubItem = GetPhysicalIndex(nColumn);
      lResult           =
        m_pListCtrl->DefWindowProc(
          LVM_SETITEM, 0, reinterpret_cast<LPARAM>(pLVItem));
    }
    else
      lResult = TRUE;
  }
  else
    lResult = TRUE;

  if (lResult)
  {
    LVITEM lvItem = {LVIF_PARAM, pLVItemSrc->iItem, 0};

    if (m_pListCtrl->DefWindowProc(
          LVM_GETITEM, 0, reinterpret_cast<LPARAM>(&lvItem)))
    {
      ITEM_DATA* pItemData = reinterpret_cast<ITEM_DATA*>(lvItem.lParam);

      // store lParam in administration data
      if (pLVItemSrc->mask & LVIF_PARAM)
        pItemData->m_lParam = pLVItemSrc->lParam;

      LVITEM* pLVItemDst;
      bool    bInsertItem;
      
      if (pItemData->m_apLVItem.GetSize() > nColumn)
      {
        pLVItemDst  = pItemData->m_apLVItem[nColumn];
        bInsertItem = false;
      }
      else
      {
        pLVItemDst  = 0;
        bInsertItem = true;
      }

      // Does the subitem already exist in the administration data?
      if (pLVItemDst)
      {
        delete pLVItem;

        // update subitem data
        if (pLVItemSrc->mask & LVIF_IMAGE)
          pLVItemDst->iImage = pLVItemSrc->iImage;
        if (pLVItemSrc->mask & LVIF_INDENT)
          pLVItemDst->iIndent = pLVItemSrc->iIndent;
        if (pLVItemSrc->mask & LVIF_TEXT && pszOrigText)
        {
          if (pLVItemDst->mask & LVIF_TEXT &&
              pLVItemDst->pszText != LPSTR_TEXTCALLBACK)
            delete[] pLVItemDst->pszText;
          pLVItemDst->pszText = pszOrigText;
        }
        pLVItemDst->mask |= pLVItemSrc->mask;
      }
      else
      {
        // store subitem administration data
        pLVItem->mask     = pLVItemSrc->mask;
        pLVItem->iSubItem = nColumn;
        pLVItem->pszText  = pszOrigText;
        if (bInsertItem)
          pItemData->m_apLVItem.InsertAt(nColumn, pLVItem);
        else
          pItemData->m_apLVItem[nColumn] = pLVItem;
      }
    }

    RefreshToolTips();
  }
  else
  {
    if (pLVItemSrc->mask    &  LVIF_TEXT &&
        pLVItemSrc->pszText != LPSTR_TEXTCALLBACK) delete[] pszOrigText;
    delete pLVItem;
  }

  return lResult;
}

/*** The text of an item or a subitem will be changed ************************/
LRESULT CListBase::OnSetItemText(WPARAM wParam, LPARAM lParam)
{
  int     nItem     = static_cast<int>(wParam);
  LVITEM  lvItemSrc = *reinterpret_cast<LVITEM*>(lParam);

  if (lvItemSrc.iSubItem <  0                       ||
      lvItemSrc.iSubItem >= m_aColumnData.GetSize() ||
      nItem           <  0) return FALSE;

  lvItemSrc.mask = LVIF_TEXT;
  LVITEM* pLVItem     = DupLVItem(&lvItemSrc);
  LRESULT lResult;
  LPTSTR  pszOrigText = pLVItem->pszText;

  if (m_aColumnData[lvItemSrc.iSubItem]->m_bEnabled &&
      m_aColumnData[lvItemSrc.iSubItem]->m_bVisible)
  {
    if (pszOrigText != LPSTR_TEXTCALLBACK &&
        !(m_pListCtrl->GetStyle() & (LVS_SORTASCENDING | LVS_SORTDESCENDING)))
      pLVItem->pszText = LPSTR_TEXTCALLBACK;
    pLVItem->iSubItem = GetPhysicalIndex(lvItemSrc.iSubItem);
    lResult           =
      m_pListCtrl->DefWindowProc(
        LVM_SETITEMTEXT, wParam, reinterpret_cast<LPARAM>(pLVItem));
  }
  else
    lResult = TRUE;

  if (lResult)
  {
    LVITEM lvItem = {LVIF_PARAM, nItem, 0};

    if (m_pListCtrl->DefWindowProc(
          LVM_GETITEM, 0, reinterpret_cast<LPARAM>(&lvItem)))
    {
      ITEM_DATA* pItemData  = reinterpret_cast<ITEM_DATA*>(lvItem.lParam);
      LVITEM*    pLVItemDst;
      bool       bInsertItem;
      
      if (pItemData->m_apLVItem.GetSize() > lvItemSrc.iSubItem)
      {
        pLVItemDst  = pItemData->m_apLVItem[lvItemSrc.iSubItem];
        bInsertItem = false;
      }
      else
      {
        pLVItemDst  = 0;
        bInsertItem = true;
      }

      // Does the subitem already exist in the administration data?
      if (pLVItemDst)
      {
        delete pLVItem;

        // update subitem text
        if (pszOrigText)
        {
          if (pLVItemDst->mask & LVIF_TEXT &&
              pLVItemDst->pszText != LPSTR_TEXTCALLBACK)
            delete[] pLVItemDst->pszText;
          pLVItemDst->pszText = pszOrigText;
        }
        pLVItemDst->mask |= lvItemSrc.mask;
      }
      else
      {
        // store subitem administration data
        pLVItem->iSubItem = lvItemSrc.iSubItem;
        pLVItem->pszText  = pszOrigText;
        if (bInsertItem)
          pItemData->m_apLVItem.InsertAt(lvItemSrc.iSubItem, pLVItem);
        else
          pItemData->m_apLVItem[lvItemSrc.iSubItem] = pLVItem;
      }
    }

    RefreshToolTips();
  }
  else
  {
    if (lvItemSrc.pszText != LPSTR_TEXTCALLBACK) delete[] pszOrigText;
    delete pLVItem;
  }

  return lResult;
}

/*** The items will be sorted ************************************************/
LRESULT CListBase::OnSortItems(WPARAM wParam, LPARAM lParam)
{
  m_pfnLVCompare    = reinterpret_cast<PFNLVCOMPARE>(lParam);
  m_lParamSort      = wParam;
  m_bUpdateToolTips = false;

  LRESULT lResult =
    m_pListCtrl->DefWindowProc(
      LVM_SORTITEMS, reinterpret_cast<WPARAM>(this),
      reinterpret_cast<LPARAM>(CompareFunc));

  m_bUpdateToolTips = true;
  if (lResult) RefreshToolTips();

  return lResult;
}

/*** System colors have been changed *****************************************/
void CListBase::OnSysColorChange() 
{
  ASSERT(m_pListCtrl->GetHeaderCtrl());

  m_pListCtrl->Default();

  // update background color
  if (!m_bFixedBkColor)
  {
    m_pListCtrl->SetBkColor(GetSysColor(COLOR_WINDOW));
    m_bFixedBkColor = false;
  }

  // update color of sort icons
  if (m_imglstSortIcons.m_hImageList)
  {
    m_imglstSortIcons.DeleteImageList         ();
    m_bmpUpArrow.DeleteObject                 ();
    m_bmpDownArrow.DeleteObject               ();
    CreateSortIcons                           ();
    m_pListCtrl->GetHeaderCtrl()->SetImageList(&m_imglstSortIcons);
    SetSortIcon                               ();
  }

  // force update of column colors
  m_bColorSortColumn = !m_bColorSortColumn;
  ColorSortColumn(!m_bColorSortColumn);
}

/*** Return the index of a subitem, based in its order in the header control */
int CListBase::OrderToIndex(int nOrder)
{
  ASSERT(m_pListCtrl->GetHeaderCtrl());

  return m_pListCtrl->GetHeaderCtrl()->OrderToIndex(nOrder);
}

/*** Prepare resources for hot underlining ***********************************/
void CListBase::PrepareHotUnderlining()
{
  if (!m_hCursorArrow) m_hCursorArrow = LoadCursor(0, IDC_ARROW);
  if (!m_hCursorHand)
    if (m_winver <= 0x0400)
      // Under Windows 95/NT we must create our own cursor
      // to indicate hot items
      m_hCursorHand = LoadCursor(AfxGetResourceHandle(), _T("IDC_HAND"));
    else
      m_hCursorHand = LoadCursor(0, IDC_HAND);
}

/*** Allow other necessary subclassing to occur before the window is *********/
/*** subclassed                                                      *********/
void CListBase::InitializeSubCtrls()
{
  // add window to standard tool tip control
  m_pToolTip = new CToolTipCtrl;
  m_pToolTip->Create (m_pListCtrl);
  m_pToolTip->AddTool(m_pListCtrl, _T(""));

  // create special tool tip control for label expanding
  m_pLabelTip = new CLabelTipCtrl(this);
  m_pLabelTip->Create (m_pListCtrl);
  m_pLabelTip->AddTool(m_pListCtrl, _T(""));
  CToolInfo ti;
  ti.cbSize = sizeof(TOOLINFO);
  if (m_pLabelTip->GetToolInfo(ti, m_pListCtrl))
  {
    ti.uFlags |= TTF_TRANSPARENT;
    m_pLabelTip->SetToolInfo(&ti);
  }

  // create special edit control for label editing
  m_pLabelEdit = new CLabelEdit(this);

  // fire an event when the mouse cursor leaves the client area of this list
  // control
  TRACKMOUSEEVENT eventTrack =
  {
    sizeof(TRACKMOUSEEVENT), TME_LEAVE, m_pListCtrl->m_hWnd
  };

  _TrackMouseEvent(&eventTrack);
}

/*** Redisplay an individual column ******************************************/
void CListBase::RedisplayColumn(int nColumn)
{
  ASSERT(nColumn >= 0 && nColumn < m_aColumnData.GetSize());

  // show column
  bool bNoColumnWasVisible = true;

  for (INT_PTR i = m_aColumnData.GetUpperBound(); i >= 0; --i)
    if (m_aColumnData[i]->m_bVisible)
    {
      bNoColumnWasVisible = false;
      break;
    }

  m_aColumnData[nColumn]->m_bVisible = true;

  int      iPhysicalColumn = GetPhysicalIndex(nColumn);
  LVCOLUMN lvColumn        = *m_aColumnData[nColumn]->m_pLVColumn;

  lvColumn.mask  |= LVCF_ORDER;
  lvColumn.iOrder = GetPhysicalOrder(m_aColumnData[nColumn]->m_nOrder);
  if (m_pListCtrl->DefWindowProc(
        LVM_INSERTCOLUMN, iPhysicalColumn, reinterpret_cast<LPARAM>(&lvColumn))
      != -1)
  {
    if (iPhysicalColumn == 0)
      // rejustify first column of listview control to enable a right-
      // justified or centerd first column
      JustifyFirstColumn(lvColumn.fmt);

    if (m_iSortColumn != 0)
    {
      int  iSortColumn        = abs(m_iSortColumn)-1;
      bool bRecolorSortColumn = false;

      if (iSortColumn == nColumn)
      {
        // restore sort icon
        SetSortIcon();
        bRecolorSortColumn = true;
      }
      else
      {
        iSortColumn        = GetPhysicalIndex(iSortColumn);
        bRecolorSortColumn = iSortColumn > iPhysicalColumn;
      }

      if (m_bColorSortColumn && bRecolorSortColumn && m_visualStyle == Present)
        m_pListCtrl->SendMessage(LVM_SETSELECTEDCOLUMN, iSortColumn);
    }

    if (!(m_pListCtrl->GetStyle() & LVS_OWNERDATA))
    {
      if (iPhysicalColumn > 0)
        for (int nItem = m_pListCtrl->GetItemCount(); --nItem >= 0;)
        {
          LVITEM lvItem = {LVIF_PARAM, nItem, 0};

          if (m_pListCtrl->DefWindowProc(
                LVM_GETITEM, 0, reinterpret_cast<LPARAM>(&lvItem)))
          {
            LVITEM* pLVItem =
              reinterpret_cast<ITEM_DATA*>(
                lvItem.lParam)->m_apLVItem[nColumn];

            pLVItem->iItem    = nItem;
            pLVItem->iSubItem = nColumn;
            m_pListCtrl->SetItem(pLVItem);
          }
        }
    }

    m_pListCtrl->SetColumnWidth(nColumn, m_aColumnData[nColumn]->m_nWidth);
  }
}

/*** Refresh tooltips ********************************************************/
void CListBase::RefreshToolTips()
{
  m_fCurrentFlags   = 0;
  m_iCurrentItem    = -1;
  m_iCurrentSubItem = -1;
  POINT point;
  if (GetCursorPos(&point))
  {
    m_bRefreshToolTips = true;
    SetCursorPos(point.x, point.y);
  }
}

/*** Set cursor if hot-tracking is enabled ***********************************/
void CListBase::SetHotCursorAndItem(LPLVHITTESTINFO pInfo)
{
  if (m_dwExtendedStyle &
      (LVS_EX_UNDERLINEHOT | LVS_EX_ONECLICKACTIVATE |
       LVS_EX_TWOCLICKACTIVATE))
  {
    // determine item under mouse cursor (hot item) and
    // the appropriate mouse cursor
    int iOldHotItem = m_iHotItem;

    m_iHotItem =
      pInfo->iItem >= 0 &&
      (
        m_dwExtendedStyle & LVS_EX_FULLROWSELECT           &&
        pInfo->flags & LVHT_ONITEM & ~LVHT_ONITEMSTATEICON ||
        (
           m_bKeepLabelLeft && IndexToOrder(pInfo->iSubItem) == 0 ||
          !m_bKeepLabelLeft && pInfo->iSubItem               == 0
        )
        &&
        (
          pInfo->flags == LVHT_ONITEMLABEL ||
          pInfo->flags == LVHT_ONITEMICON
        )
      )
      &&
      (
        m_dwExtendedStyle & LVS_EX_TWOCLICKACTIVATE &&
        m_pListCtrl->GetItemState(pInfo->iItem, LVIS_SELECTED) ==
          LVIS_SELECTED                             ||
        m_dwExtendedStyle & LVS_EX_ONECLICKACTIVATE
      ) ? pInfo->iItem : -1;

    if (m_pListCtrl->GetStyle() & LVS_OWNERDRAWFIXED)
    {
      m_hCursorCustom = m_iHotItem != -1 ? m_hCursorHand : m_hCursorArrow;

      if (m_iHotItem != iOldHotItem)
      {
        RECT rc;

        if (iOldHotItem != -1)
        {
          m_pListCtrl->GetItemRect   (iOldHotItem, &rc, LVIR_BOUNDS);
          m_pListCtrl->InvalidateRect(&rc, FALSE);
        }
        if (m_iHotItem != -1)
        {
          m_pListCtrl->GetItemRect   (m_iHotItem, &rc, LVIR_BOUNDS);
          m_pListCtrl->InvalidateRect(&rc, FALSE);
        }
      }

      SetCursor(m_hCursorCustom);
    }
  }

  if (m_hTheme && m_pListCtrl->GetStyle() & LVS_OWNERDRAWFIXED)
  {
    // determine item under mouse cursor
    int iOldItemUnderCursor = m_iItemUnderCursor;

    m_iItemUnderCursor =
      pInfo->iItem >= 0 &&
      (
        m_dwExtendedStyle & LVS_EX_FULLROWSELECT && pInfo->flags & LVHT_ONITEM
        ||
        (
          m_bKeepLabelLeft && IndexToOrder(pInfo->iSubItem) == 0 ||
          !m_bKeepLabelLeft && pInfo->iSubItem               == 0
        )
        &&
        (
          pInfo->flags == LVHT_ONITEMLABEL ||
          pInfo->flags == LVHT_ONITEMICON  ||
          pInfo->flags == LVHT_ONITEMSTATEICON
        )
      ) ? pInfo->iItem : -1;

    if (m_iItemUnderCursor != iOldItemUnderCursor)
    {
      RECT rc;

      if (iOldItemUnderCursor != -1)
      {
        m_pListCtrl->GetItemRect   (iOldItemUnderCursor, &rc, LVIR_BOUNDS);
        m_pListCtrl->InvalidateRect(&rc, FALSE);
      }
      if (m_iItemUnderCursor != -1)
      {
        m_pListCtrl->GetItemRect   (m_iItemUnderCursor, &rc, LVIR_BOUNDS);
        m_pListCtrl->InvalidateRect(&rc, FALSE);
      }
    }
  }
}

/*** Display or hide sort icon on column to be sorted ************************/
void CListBase::SetSortIcon()
{
  CHeaderCtrl* pHeaderCtrl = m_pListCtrl->GetHeaderCtrl();
  ASSERT(pHeaderCtrl);

  for (int col = static_cast<int>(m_aColumnData.GetUpperBound());
       col >= 0;
       --col)
    if (m_aColumnData[col]->m_bEnabled && m_aColumnData[col]->m_bVisible)
    {
      HDITEM hdrItem;
      int    nPhysicalCol = GetPhysicalIndex(col);

      if (m_visualStyle == Present)
      {
        hdrItem.mask = HDI_FORMAT;
        pHeaderCtrl->GetItem(nPhysicalCol, &hdrItem);
        if (m_bSortIconEnabled     &&
            m_iSortColumn     != 0 &&
            m_iSortColumn - 1 == col)
          hdrItem.fmt =
            hdrItem.fmt & HDF_JUSTIFYMASK | HDF_STRING | HDF_SORTUP;
        else if (m_bSortIconEnabled      &&
                  m_iSortColumn     != 0 &&
                 -m_iSortColumn - 1 == col)
          hdrItem.fmt =
            hdrItem.fmt & HDF_JUSTIFYMASK | HDF_STRING | HDF_SORTDOWN;
        else
          hdrItem.fmt = hdrItem.fmt & HDF_JUSTIFYMASK | HDF_STRING;
      }
      else
      {
        hdrItem.mask = HDI_FORMAT | HDI_IMAGE;
        pHeaderCtrl->GetItem(nPhysicalCol, &hdrItem);
        if (m_bSortIconEnabled     &&
            m_iSortColumn     != 0 &&
            m_iSortColumn - 1 == col)
        {
          hdrItem.iImage = m_iUpArrow;
          hdrItem.fmt    =
            hdrItem.fmt & HDF_JUSTIFYMASK |
            HDF_IMAGE | HDF_STRING | HDF_BITMAP_ON_RIGHT;
        }
        else if (m_bSortIconEnabled      &&
                  m_iSortColumn     != 0 &&
                 -m_iSortColumn - 1 == col)
        {
          hdrItem.iImage = m_iDownArrow;
          hdrItem.fmt    =
            hdrItem.fmt & HDF_JUSTIFYMASK |
            HDF_IMAGE | HDF_STRING | HDF_BITMAP_ON_RIGHT;
        }
        else
          hdrItem.fmt = hdrItem.fmt & HDF_JUSTIFYMASK | HDF_STRING;
      }

      pHeaderCtrl->SetItem(nPhysicalCol, &hdrItem);
    }
}

/*** Definition of structure "CListBase::COLUMN_DATA" ************************/

/*** Destructor **************************************************************/
CListBase::COLUMN_DATA::~COLUMN_DATA()
{
  if (m_pLVColumn)
  {
    delete[] m_pLVColumn->pszText;
    delete m_pLVColumn;
  }
}


/*** Definition of structure "CListBase::ITEM_DATA" **************************/

/*** Destructor **************************************************************/
CListBase::ITEM_DATA::~ITEM_DATA()
{
  for (INT_PTR nColumn = m_apLVItem.GetUpperBound(); nColumn >= 0; --nColumn)
  {
    LVITEM* pLVItem = m_apLVItem[nColumn];

    if (pLVItem)
    {
      delete[] pLVItem->pszText;
      delete pLVItem;
    }
  }
}
