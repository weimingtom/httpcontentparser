/******************************************************************************

$Author$
  
$Modtime$
$Revision$

Description: Interfaces of the classes "CListCtrlEx" and "CListViewEx"
             (list control and list view with sort icons and
              colored sort column)

$Log$

******************************************************************************/

#pragma once
/*** Declaration of "workhorse" class "CListBase" ****************************/
class CListCtrlHelper;

class CListBase
{
  public:
   CListBase();
  ~CListBase();

  BOOL         ColorSortColumn   (BOOL bEnable = TRUE, INT_PTR nSortColumn = 0);
  virtual void DrawSmallIcon     (CDC* pDC, LVITEM* pItem, LPRECT pRect);
  virtual void DrawStateIcon     (CDC* pDC, LVITEM* pItem, LPRECT pRect);
  virtual void DrawSubItemText   (CDC* pDC, LVITEM* pItem, LVCOLUMN* pColumn,
                                  LPRECT pRect);
  void         EnableColumn      (INT_PTR nColumn, BOOL bEnableIt = TRUE);
  void         EnableColumnHiding(INT_PTR nColumn, BOOL bEnableIt = TRUE);

  void EnableColumnSeparators(BOOL bEnable = TRUE)
  {
    m_bColumnSeparators = bEnable;
  }

  void EnableExplorerStyle();
  void EnableSortIcon     (BOOL bEnable = TRUE, INT_PTR nSortColumn = 0);
  void EnableSubItemTips  (BOOL bEnable = TRUE) {m_bSubItemTips = bEnable;}

  INT_PTR GetColumnCount() const
  {
    return static_cast<INT_PTR>(m_aColumnData.GetSize());
  }

  POSITION GetFirstCheckedItemPosition() const;
  INT_PTR      GetNextCheckedItem         (POSITION& pos) const;
  INT_PTR      GetSortColumn              () const {return m_iSortColumn;}
  BOOL                  GetState  (LPBYTE* ppState, LPUINT pnStateLen) const;
  virtual const CString GetToolTip(INT_PTR /*nItem*/) {return _T("");}

  virtual const CString GetToolTip(INT_PTR /*nItem*/, INT_PTR /*nSubItem*/,
                                   UINT /*nFlags*/, BOOL& /*bAsLabel*/)
  {
    return _T("");
  }

  BOOL IsColumnEnabled(INT_PTR nColumn) const
  {
    return m_aColumnData[nColumn]->m_bEnabled;
  }

  BOOL IsSubItemWidthSufficient(INT_PTR nItem, INT_PTR nSubItem, LPCTSTR pszText);
  BOOL KeepLabelLeft           (BOOL bKeepLeft = true);
  BOOL RestoreState            (LPCTSTR pszSection, LPCTSTR pszEntry);
  BOOL SaveState               (LPCTSTR pszSection, LPCTSTR pszEntry) const;
  void SetSortColumn           (INT_PTR nColumn);
  BOOL SetState                (LPBYTE pState, UINT nStateLen);
  void ShowColumn              (INT_PTR nColumn, BOOL bShowIt = TRUE);

	private:
  enum EXPLORER_STYLE {NONE, XP, VISTA};
  enum VISUAL_STYLE   {Unknown, NotPresent, Present};

  friend class CListCtrlEx;
  friend class CListViewEx;
  friend class CLabelEdit;
  friend class CLabelTipCtrl;

  struct COLUMN_DATA
  {
    COLUMN_DATA(): m_bEnabled      (true),
                   m_bHidingAllowed(false),
                   m_bVisible      (true),
                   m_nWidth        (0),
                   m_nOrder        (0),
                   m_pLVColumn     (0)
    {}

    ~COLUMN_DATA();

    bool      m_bEnabled;
    bool      m_bHidingAllowed;
    bool      m_bVisible;
    INT_PTR       m_nWidth;
    INT_PTR       m_nOrder;
    LVCOLUMN* m_pLVColumn;
  };

  struct ITEM_DATA
  {
     ITEM_DATA(): m_lParam(0) {}
    ~ITEM_DATA();

    LPARAM          m_lParam;
    CArray<LVITEM*> m_apLVItem;
  };

  static INT_PTR CALLBACK CompareFunc          (LPARAM lParam1, LPARAM lParam2,
                                            LPARAM lParamSort);
  void                CreateSortIcons      ();
  void                DrawItem             (LPDRAWITEMSTRUCT lpDrawItemStruct);
  LVCOLUMN*           DupLVColumn          (LVCOLUMN* pLVColumn) const;
  LVITEM*             DupLVItem            (LVITEM* pLVItem) const;
  void                EraseRect            (CDC* pDC, LPRECT pRect);
  bool                GetLabelRect         (INT_PTR nItem, INT_PTR nSubItem, LPRECT pRect);
  LVITEM*             GetLVITEM            (INT_PTR nItem, INT_PTR nSubItem = 0) const;
  INT_PTR                 GetLogicalIndex      (INT_PTR nPhysicalColumn) const;
  INT_PTR                 GetLogicalOrder      (INT_PTR nPhysicalOrder) const;
  INT_PTR                 GetPhysicalIndex     (INT_PTR nColumnIndex) const;
  INT_PTR                 GetPhysicalOrder     (INT_PTR nColumnOrder) const;
  bool                GetStateIconRect     (INT_PTR nItem, LPRECT pRect);
  void                HideColumn           (INT_PTR nColumn);
  INT_PTR                 IndexToOrder         (INT_PTR nIndex);
  void                InitializeSubCtrls   ();
  void                InvalidateNonItemArea();
  void                JustifyFirstColumn   (INT_PTR nFormat);
  BOOL                OnBeginLabelEdit     (NMHDR* pNMHDR);
  LRESULT             OnCancelEditLabel    ();
	BOOL                OnColumnclick        (NMHDR* pNMHDR, LRESULT* pResult);
  BOOL                OnCommand            (WPARAM wParam);
	void                OnContextMenu        (CWnd* pWnd, CPoint point);
	void                OnCustomDraw         (NMHDR* pNMHDR, LRESULT* pResult);
  LRESULT             OnDeleteAllItems     ();
  LRESULT             OnDeleteColumn       (WPARAM wParam);
  LRESULT             OnDeleteItem         (WPARAM wParam);
	void                OnDestroy            ();
  BOOL                OnEndLabelEdit       (NMHDR* pNMHDR);
	BOOL                OnEraseBkgnd         (CDC* pDC);
  LRESULT             OnFindItem           (WPARAM wParam, LPARAM lParam);  
  LRESULT             OnGetColumn          (WPARAM wParam, LPARAM lParam);
  LRESULT             OnGetColumnWidth     (WPARAM wParam);
  LRESULT             OnGetColumnOrderArray(WPARAM wParam, LPARAM lParam);
  BOOL                OnGetdispinfo        (NMHDR* pNMHDR);
  LRESULT             OnGetItem            (LPARAM lParam);
  LRESULT             OnGetItemRect        (WPARAM wParam, LPARAM lParam);
  LRESULT             OnGetItemText        (WPARAM wParam, LPARAM lParam);
  LRESULT             OnGetSubItemRect     (WPARAM wParam, LPARAM lParam);
  INT_PTR                 OnHitTest            (LPARAM lParam);
  void                OnHScroll            ();
  LRESULT             OnInsertColumn       (WPARAM wParam, LPARAM lParam);
  LRESULT             OnInsertItem         (LPARAM lParam);
	void                OnKeyDown            (UINT nChar);
	void                OnKeyUp              (UINT nChar);
	void                OnKillFocus          ();
	void                OnLButtonDblClk      (CPoint point);
	void                OnLButtonDown        (CPoint point);
  void                OnLButtonUp          ();
  LRESULT             OnMouseLeave         ();
  void                OnMouseMove          (CPoint point) ;
  BOOL                OnMouseWheel         (CPoint point);
	BOOL                OnNotify             (LPARAM lParam);
  BOOL                OnODCacheHint        (NMHDR* pNMHDR);
  void                OnPaint              ();
  LRESULT             OnSetBkColor         (LPARAM lParam);
  LRESULT             OnSetBkImage         ();
  LRESULT             OnSetColumn          (WPARAM wParam, LPARAM lParam);
  LRESULT             OnSetColumnOrderArray(WPARAM wParam, LPARAM lParam);
  LRESULT             OnSetColumnWidth     (WPARAM wParam, LPARAM lParam);
  LRESULT             OnSetExtendedStyle   (WPARAM wParam, LPARAM lParam);
	void                OnSetFocus           ();
  LRESULT             OnSetImageList       (WPARAM wParam);
  LRESULT             OnSetItem            (LPARAM lParam);
  LRESULT             OnSetItemText        (WPARAM wParam, LPARAM lParam);
  LRESULT             OnSortItems          (WPARAM wParam, LPARAM lParam);
	void                OnSysColorChange     ();
  INT_PTR                 OrderToIndex         (INT_PTR nOrder);
  void                PrepareHotUnderlining();
  void                RedisplayColumn      (INT_PTR nColumn);
  void                RefreshToolTips      ();
  void                SetHotCursorAndItem  (LPLVHITTESTINFO pInfo);
  void                SetSortIcon          ();

  static UINT          m_winver;
  static VISUAL_STYLE  m_visualStyle;
  static const INT_PTR     m_iFirstColXOff;
  static const INT_PTR     m_iNextColXOff;
  static const INT_PTR     m_iColumnSeparatorWidth;
  INT_PTR                  m_iIconXOff; // offset of icon may vary of
                                    // unknown reason
  HTHEME               m_hTheme;
  CListCtrlHelper*     m_pListCtrl;
  bool                 m_bIsActive;
  bool                 m_bMouseInClientArea;
  bool                 m_bTopMost;
  bool                 m_bFocusSet;
  CArray<COLUMN_DATA*> m_aColumnData;
  INT_PTR                  m_iColumnHidingAllowed;
  BOOL                 m_bColumnSeparators;
  bool                 m_bExplorerStyle;
  BOOL                 m_bSortIconEnabled;
  BOOL                 m_bColorSortColumn;
  COLORREF             m_clrBkColor;
  bool                 m_bBkColorKnown;
  bool                 m_bBkImage;
  CImageList           m_imglstSortIcons;
  CBitmap              m_bmpUpArrow;
  CBitmap              m_bmpDownArrow;
  INT_PTR                  m_iUpArrow;
  INT_PTR                  m_iDownArrow;
  DWORD                m_dwColSortColor;
  INT_PTR                  m_iSortColumn;
  INT_PTR                  m_iFormatOfSubItem0;
  BOOL                 m_bKeepLabelLeft;
  bool                 m_bLocked;
  bool                 m_bControl;
  bool                 m_bIconXOffCalculated;
  bool                 m_bFixedBkColor;
  DWORD                m_dwExtendedStyle;
  INT_PTR                  m_iItemUnderCursor;
  INT_PTR                  m_iHotItem;
  COLORREF             m_dwHotLite;
  HCURSOR              m_hCursorCustom;
  HCURSOR              m_hCursorArrow;
  HCURSOR              m_hCursorHand;
  PFNLVCOMPARE         m_pfnLVCompare;
  LPARAM               m_lParamSort;
  CList<INT_PTR>           m_lstVisibleItemsPreviouslySelected;
  INT_PTR                  m_iItemLastSelected;
  INT_PTR                  m_iFirstCachedItem;
  INT_PTR                  m_iLastCachedItem;
  bool                 m_bAlwaysGetSmallIconRect;
  bool                 m_bIgnoreNextMouseMove;
  bool                 m_bRefreshToolTips;
  BOOL                 m_bSubItemTips;
  bool                 m_bUpdateToolTips;
  CToolTipCtrl*        m_pToolTip;
  CLabelTipCtrl*       m_pLabelTip;
  CString              m_strCurrentToolTip;
  CString              m_strCurrentLabelTip;
  bool                 m_bToolTips;
  bool                 m_bUnfoldLabel;
  BOOL                 m_bLabelUnfolded;
  CLabelEdit*          m_pLabelEdit;                         
  CString              m_strEditedLabel;
  INT_PTR                  m_iItemEdit;
  bool                 m_bLabelEditingCancelled;
  bool                 m_bOnEndLabelEdit;
  bool                 m_bOnGetDispinfo;
  bool                 m_bOnPaint;
  bool                 m_bRepost;

  INT_PTR                  m_iCurrentItem;
  INT_PTR                  m_iCurrentSubItem;
  UINT                 m_fCurrentFlags;
};


/*** Declaration of class "CListCtrlEx" **************************************/
class CListCtrlEx: public CListCtrl, public CListBase
{
  DECLARE_DYNCREATE(CListCtrlEx);

  public:
  CListCtrlEx() {m_pListCtrl = reinterpret_cast<CListCtrlHelper*>(this);}

  virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
  {
    CListBase::DrawItem(lpDrawItemStruct);
  }

  protected:
  // Overrides
	// ClassWizard generated virtual function overrides
	virtual BOOL OnCommand        (WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify         (WPARAM wParam, LPARAM lParam,
                                 LRESULT* pResult);
	virtual void PreSubclassWindow();

	// Generated message map functions
  afx_msg BOOL    OnBeginLabelEdit     (NMHDR* pNMHDR, LRESULT*);
  afx_msg LRESULT OnCancelEditLabel    (WPARAM, LPARAM);
	afx_msg BOOL    OnColumnclick        (NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void    OnContextMenu        (CWnd* pWnd, CPoint point);
  afx_msg INT_PTR     OnCreate             (LPCREATESTRUCT lpCreateStruct);
	afx_msg void    OnCustomDraw         (NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg LRESULT OnDeleteAllItems     (WPARAM, LPARAM);
  afx_msg LRESULT OnDeleteColumn       (WPARAM wParam, LPARAM);
  afx_msg LRESULT OnDeleteItem         (WPARAM wParam, LPARAM);
	afx_msg void    OnDestroy            ();
  afx_msg BOOL    OnEndLabelEdit       (NMHDR* pNMHDR, LRESULT*);
	afx_msg BOOL    OnEraseBkgnd         (CDC* pDC);
  afx_msg LRESULT OnFindItem           (WPARAM wParam, LPARAM lParam);  
  afx_msg LRESULT OnGetColumn          (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnGetColumnOrderArray(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnGetColumnWidth     (WPARAM wParam, LPARAM);
  afx_msg BOOL    OnGetdispinfo        (NMHDR* pNMHDR, LRESULT*);
  afx_msg LRESULT OnGetExtendedStyle   (WPARAM, LPARAM);
  afx_msg LRESULT OnGetItem            (WPARAM, LPARAM lParam);
  afx_msg LRESULT OnGetItemRect        (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnGetItemText        (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnGetSubItemRect     (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnHitTest            (WPARAM, LPARAM lParam);
	afx_msg void    OnHScroll            (UINT nSBCode, UINT nPos,
                                        CScrollBar* pScrollBar);
  afx_msg LRESULT OnInsertColumn       (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnInsertItem         (WPARAM, LPARAM lParam);
	afx_msg void    OnKeyDown            (UINT nChar, UINT nRepCnt,
                                        UINT nFlags);
	afx_msg void    OnKeyUp              (UINT nChar, UINT nRepCnt,
                                        UINT nFlags);
	afx_msg void    OnKillFocus          (CWnd* pNewWnd);
	afx_msg void    OnLButtonDblClk      (UINT nFlags, CPoint point);
	afx_msg void    OnLButtonDown        (UINT nFlags, CPoint point);
	afx_msg void    OnLButtonUp          (UINT nFlags, CPoint point);
  afx_msg LRESULT OnMouseLeave         (WPARAM, LPARAM);
	afx_msg void    OnMouseMove          (UINT, CPoint point);
  afx_msg BOOL    OnMouseWheel         (UINT, short, CPoint pt);
  afx_msg BOOL    OnODCacheHint        (NMHDR* pNMHDR, LRESULT*);
  afx_msg void    OnPaint              ();
  afx_msg LRESULT OnSetBkColor         (WPARAM, LPARAM lParam);
  afx_msg LRESULT OnSetBkImage         (WPARAM, LPARAM);
  afx_msg LRESULT OnSetColumn          (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSetColumnOrderArray(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSetColumnWidth     (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSetExtendedStyle   (WPARAM wParam, LPARAM lParam);
	afx_msg void    OnSetFocus           (CWnd* pOldWnd);
  afx_msg LRESULT OnSetImageList       (WPARAM wParam, LPARAM);
  afx_msg LRESULT OnSetItem            (WPARAM, LPARAM lParam);
  afx_msg LRESULT OnSetItemText        (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSortItems          (WPARAM wParam, LPARAM lParam);
	afx_msg void    OnSysColorChange     ();

	DECLARE_MESSAGE_MAP()
};


/*** Declaration of class "CListViewEx" **************************************/
class CListViewEx: public CListView, public CListBase
{
  DECLARE_DYNCREATE(CListViewEx);

  public:
  CListViewEx()
  {
    m_pListCtrl = reinterpret_cast<CListCtrlHelper*>(&GetListCtrl());
  }

  virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
  {
    CListBase::DrawItem(lpDrawItemStruct);
  }

  protected:
  // Overrides
	// ClassWizard generated virtual function overrides
	virtual BOOL OnCommand      (WPARAM wParam, LPARAM lParam);
  virtual void OnInitialUpdate();
  virtual BOOL OnNotify       (WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	// Generated message map functions
  afx_msg BOOL    OnBeginLabelEdit     (NMHDR* pNMHDR, LRESULT*);
  afx_msg LRESULT OnCancelEditLabel    (WPARAM, LPARAM);
	afx_msg BOOL    OnColumnclick        (NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void    OnContextMenu        (CWnd* pWnd, CPoint point);
	afx_msg void    OnCustomDraw         (NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg LRESULT OnDeleteAllItems     (WPARAM, LPARAM);
  afx_msg LRESULT OnDeleteColumn       (WPARAM wParam, LPARAM);
  afx_msg LRESULT OnDeleteItem         (WPARAM wParam, LPARAM);
	afx_msg void    OnDestroy            ();
  afx_msg BOOL    OnEndLabelEdit       (NMHDR* pNMHDR, LRESULT*);
	afx_msg BOOL    OnEraseBkgnd         (CDC* pDC);
  afx_msg LRESULT OnFindItem           (WPARAM wParam, LPARAM lParam);  
  afx_msg LRESULT OnGetColumn          (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnGetColumnOrderArray(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnGetColumnWidth     (WPARAM wParam, LPARAM);
  afx_msg BOOL    OnGetdispinfo        (NMHDR* pNMHDR, LRESULT*);
  afx_msg LRESULT OnGetExtendedStyle   (WPARAM, LPARAM);
  afx_msg LRESULT OnGetItem            (WPARAM, LPARAM lParam);
  afx_msg LRESULT OnGetItemRect        (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnGetItemText        (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnGetSubItemRect     (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnHitTest            (WPARAM, LPARAM lParam);
	afx_msg void    OnHScroll            (UINT nSBCode, UINT nPos,
                                        CScrollBar* pScrollBar);
  afx_msg LRESULT OnInsertColumn       (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnInsertItem         (WPARAM, LPARAM lParam);
	afx_msg void    OnKeyDown            (UINT nChar, UINT nRepCnt,
                                        UINT nFlags);
	afx_msg void    OnKeyUp              (UINT nChar, UINT nRepCnt,
                                        UINT nFlags);
	afx_msg void    OnKillFocus          (CWnd* pNewWnd);
	afx_msg void    OnLButtonDblClk      (UINT nFlags, CPoint point);
	afx_msg void    OnLButtonDown        (UINT nFlags, CPoint point);
	afx_msg void    OnLButtonUp          (UINT nFlags, CPoint point);
  afx_msg LRESULT OnMouseLeave         (WPARAM, LPARAM);
	afx_msg void    OnMouseMove          (UINT, CPoint point);
  afx_msg BOOL    OnMouseWheel         (UINT, short, CPoint pt);
  afx_msg BOOL    OnODCacheHint        (NMHDR* pNMHDR, LRESULT*);
  afx_msg void    OnPaint              ();
  afx_msg LRESULT OnSetBkColor         (WPARAM, LPARAM);
  afx_msg LRESULT OnSetBkImage         (WPARAM, LPARAM);
  afx_msg LRESULT OnSetColumn          (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSetColumnOrderArray(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSetColumnWidth     (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSetExtendedStyle   (WPARAM wParam, LPARAM lParam);
	afx_msg void    OnSetFocus           (CWnd* pOldWnd);
  afx_msg LRESULT OnSetImageList       (WPARAM wParam, LPARAM);
  afx_msg LRESULT OnSetItem            (WPARAM, LPARAM lParam);
  afx_msg LRESULT OnSetItemText        (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSortItems          (WPARAM wParam, LPARAM lParam);
	afx_msg void    OnSysColorChange     ();

	DECLARE_MESSAGE_MAP()
};
