// ThumbCtrl.cpp : implementation file
//

#include "stdafx.h"

#include "ThumbCtrl.h"
#include "resource.h"	// It need a icon to representate default image.
#include <deque>
#include <Gdiplus.h>

using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThreadPool
// This class used to buffer data for thread. The data type is a deque of ListNode.
// This class have two instances, one is pThreadInPool, the other is pThreadOutPool,
// Their behavir is very different. The common part is that they have basic operation
// on buffer, like Get, Insert, Delete, Clear, and they are all in critical section.
//
// The InPool maintained the whole list
// in the listview, and use m_Offset to indicate that from where begin to process. 
// It will be empty only if user called clear method. The delete method is the 
// synchronization with the listview, so it surly could delete one.
//
// The OutPool is different, it only maintain the items processed and was not showed.
// When the OnUpdateImage of main thread was called, it use GetNode(TRUE) to get and
// remove the node after they are shown by list.SetItem(). The delete operation will
// occured only when the item needed be delete is just in this pool.
// 
// The main point of this module is the synchronization between main thread and 
// additional thread. There are three critical section and two event is used just
// for this purpose. The event can ensure the operation could be trigered on time,
// and the critical section ensure that the of check event and make action will be
// simultaneously.

class CThreadPool
{
public:
	struct ListNode{
		int ItemNo;
		CString FileName;
		int ImageNo;
	};

protected:
	std::deque<struct ListNode> Queue;
	CRITICAL_SECTION CriticalSection;

	int m_Offset;
	int m_Type;		// 0: InPool, 1: OutPool;

public:
	BOOL DeleteItem(int nItem);
	void InsertNode(int ItemNo, CString FileName="", int ImageNo=0);
	void AddNode(int ItemNo, int ImageNo);
	struct ListNode GetNextNode(BOOL bRemove);
	void Clear();
	BOOL IsEmpty()	{	return Queue.empty();	}

	CThreadPool(int Type)
	{	
		m_Type = Type;
		m_Offset = 0;
		InitializeCriticalSection( & CriticalSection );
	}

	~CThreadPool()
	{	
		DeleteCriticalSection( & CriticalSection );
	}
};

// Used by In Pool.
void CThreadPool::InsertNode(int ItemNo, CString FileName, int ImageNo)
{
	EnterCriticalSection( & CriticalSection );

	//TRACE("Insert to In pool: %d, %d, %s, Size:%d\n", ItemNo, ImageNo, FileName, Queue.size() );
	struct ListNode node;
	node.ItemNo = ItemNo;
	node.FileName = FileName;
	node.ImageNo = ImageNo;

	if(ItemNo > Queue.size())
		ItemNo = Queue.size();
	std::deque<ListNode>::iterator itor;
	itor = Queue.begin() + ItemNo;
	Queue.insert( itor, node );
	//Queue.push_back( node );

	LeaveCriticalSection( & CriticalSection );
}

// Used by Out pool
void CThreadPool::AddNode(int ItemNo, int ImageNo)
{
	EnterCriticalSection( & CriticalSection );

	//TRACE("Insert to out pool: %d, %d, Size:%d\n", ItemNo, ImageNo, Queue.size() );
	struct ListNode node;
	node.ItemNo = ItemNo;
	node.FileName = "";
	node.ImageNo = ImageNo;

	Queue.push_back( node );

	LeaveCriticalSection( & CriticalSection );
}

void CThreadPool::Clear()
{
	EnterCriticalSection( & CriticalSection );

	//TRACE( "Cleared\n" );
	Queue.clear();
	m_Offset = 0;

	LeaveCriticalSection( & CriticalSection );
}

struct CThreadPool::ListNode CThreadPool::GetNextNode(BOOL bRemove)
{
	EnterCriticalSection( & CriticalSection );

	struct ListNode node;
	if(Queue.size() == 0 || Queue.size() <= m_Offset)
	{
		node.ItemNo = -1;
	}
	else if(bRemove)
	{
		node = Queue.front();
		Queue.pop_front();
	}
	else
	{
		if( m_Offset >= Queue.size() )
			m_Offset = 0;
		node.ItemNo = -1;
		std::deque<ListNode>::iterator itor;
		for(itor = Queue.begin() + m_Offset; itor < Queue.end(); itor++)
			if(itor->ImageNo == 0)
			{
				node = *itor;
				itor->ImageNo = -1;
				node.ItemNo = itor-Queue.begin();
				m_Offset = node.ItemNo;
				break;
			}
		if( node.ItemNo == -1 )
		{
			for(itor = Queue.begin(); itor < Queue.end(); itor++)
			{
				if(itor->ImageNo == 0)
				{
					node = *itor;
					itor->ImageNo = -1;
					node.ItemNo = itor-Queue.begin();
					m_Offset = node.ItemNo;
					break;
				}
			}
		}
	}
	//TRACE("Get node from pool: %d, %d, %s, Size:%d, Off:%d,%d\n", node.ItemNo, node.ImageNo, node.FileName, Queue.size(), m_Offset, bRemove);

	LeaveCriticalSection( & CriticalSection );
	return node;
}


BOOL CThreadPool::DeleteItem(int nItem)
{
	ASSERT( m_Type == 0 || m_Type == 1);
	EnterCriticalSection( & CriticalSection );

	BOOL found = FALSE;
	std::deque<ListNode>::iterator itor;
	if( m_Type == 1 )	// Out Pool
	{
		for(itor=Queue.begin(); itor<Queue.end(); itor++)
		{
			if(itor->ItemNo == nItem)
			{
				found = TRUE;
				Queue.erase(itor);
			}
			else if(itor->ItemNo > nItem)
			{
				itor->ItemNo --;
			}
		}
	}
	else				// In Pool
	{
		ASSERT( nItem < Queue.size() );
		if( nItem < Queue.size() )
		{
			itor = Queue.begin() + nItem;
			Queue.erase(itor);
			if( nItem <= m_Offset)
				m_Offset --;
			found = TRUE;
		}
	}

	LeaveCriticalSection( & CriticalSection );
	return found;
}

/////////////////////////////////////////////////////////////////////////////
// CThumbCtrl

IMPLEMENT_DYNCREATE(CThumbCtrl, CListCtrl)

CThumbCtrl::CThumbCtrl(int ThumbWidth, int ThumbHeight)
{
	m_pThread = NULL;
	m_ThumbWidth = ThumbWidth;
	m_ThumbHeight = ThumbHeight;
	m_Margin = 2;

	pThreadInPool = new CThreadPool(0);		// 0 Specified In Pool
	pThreadOutPool = new CThreadPool(1);	// 1 Specified Out Pool
	if(pThreadInPool == NULL || pThreadOutPool == NULL){
		MessageBox(" Thread buffer alloc failed.", "Error", MB_OK | MB_ICONSTOP );
		return;
	}

	if((m_ExitEvent = CreateEvent(NULL, TRUE, TRUE, NULL)) == NULL){
		MessageBox(" Create event failed\n", "Error", MB_OK | MB_ICONSTOP );
		return;
	}	
	if((m_StopEvent = CreateEvent(NULL, FALSE, FALSE, NULL)) == NULL){
		MessageBox(" Create event failed\n", "Error", MB_OK | MB_ICONSTOP );
		return;
	}

	InitializeCriticalSection( & m_CSSetStop );
	InitializeCriticalSection( & m_CSExitCheck );
	InitializeCriticalSection( & m_CSNeitherInBothPoolSection );
}

CThumbCtrl::~CThumbCtrl()
{
	CloseHandle( m_ExitEvent );
	CloseHandle( m_StopEvent );

	delete pThreadInPool;
	delete pThreadOutPool;

	DeleteCriticalSection( & m_CSSetStop );
	DeleteCriticalSection( & m_CSExitCheck );
	DeleteCriticalSection( & m_CSNeitherInBothPoolSection );
}


BEGIN_MESSAGE_MAP(CThumbCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CThumbCtrl)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(LVN_DELETEITEM, OnDeleteItem)
	ON_NOTIFY_REFLECT(LVN_DELETEALLITEMS, OnDeleteAllItems)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_UPDATE_IMAGEDATA, OnUpdateImageData )
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CThumbCtrl diagnostics

#ifdef _DEBUG
void CThumbCtrl::AssertValid() const
{
	CListCtrl::AssertValid();
}

void CThumbCtrl::Dump(CDumpContext& dc) const
{
	CListCtrl::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CThumbCtrl message handlers

int CThumbCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	ModifyStyle(LVS_TYPEMASK, LVS_ICON | LVS_AUTOARRANGE);

	CClientDC dc(this);
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
	CBrush bkBrush(RGB(192, 192, 192)), *pOldBrush;
	CBitmap Bmp, * pOldBmp;
	Bmp.CreateCompatibleBitmap(&dc, m_ThumbWidth, m_ThumbHeight);
	pOldBmp = memdc.SelectObject(&Bmp);
	pOldBrush = memdc.SelectObject(&bkBrush);
	memdc.PatBlt(0,0,m_ThumbWidth,m_ThumbHeight, PATCOPY);
	memdc.Draw3dRect(0,0,m_ThumbWidth, m_ThumbHeight, RGB(222, 222, 222), RGB(128, 128, 128));
	memdc.DrawIcon((m_ThumbWidth-32)/2, (m_ThumbHeight-32)/2, AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	memdc.SelectObject(pOldBmp);

	m_ImageList.Create(m_ThumbWidth, m_ThumbHeight, ILC_COLOR24 | ILC_MASK, 20, 20);
	m_ImageList.Add(&Bmp, RGB(0,0,0));
	
	m_BackupImageList.Create(&m_ImageList);

	SetImageList(&m_ImageList, LVSIL_NORMAL);

	ListView_SetIconSpacing( m_hWnd, m_ThumbWidth + 10, m_ThumbHeight + 30 );
	
	return 0;
}

// I want transform InsertItem into OnInsertItem in order to provide a united interface
//   with CListCtrl, but when the message occured, I can't get item from list ctrl.
/*void CThumbCtrl::OnInsertItem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	CString FileName, PathName;
	LVITEM item;
	item.iItem = pNMListView->iItem;
	item.iSubItem = 0;
	item.mask = LVIF_TEXT;
	GetListCtrl().GetItem(&item);

	PathName = item.pszText;
	FileName = PathName.Right(PathName.GetLength() - PathName.ReverseFind('\\') - 1);

	item.iImage = 0;
	item.pszText = FileName.GetBuffer(FileName.GetLength() + 1);
	GetListCtrl().SetItem(&item);
	FileName.ReleaseBuffer();

	*pResult = 0;
}*/

int CThumbCtrl::InsertItem(int ItemNo, LPCTSTR lpszFileName)
{
	CString PathName, FileName;

	PathName = lpszFileName;
	FileName = PathName.Right(PathName.GetLength() - PathName.ReverseFind('\\') - 1);

	ItemNo = CListCtrl::InsertItem(ItemNo,FileName, 0);	//Default image index.
	pThreadInPool->InsertNode(ItemNo, PathName);		// Put into pool to wait for processing.

	EnterCriticalSection( & m_CSExitCheck );
	if(WaitForSingleObject(m_ExitEvent, 0) == WAIT_OBJECT_0)
	{
		tagParameter * Parameter = new tagParameter;
		Parameter->hListView = this->m_hWnd;
		Parameter->hImageList = m_ImageList.m_hImageList;
		Parameter->Parent = this;

		m_pThread = AfxBeginThread(ImageRendering, Parameter, THREAD_PRIORITY_BELOW_NORMAL, 0, 0, NULL);
		ResetEvent( m_ExitEvent );		// Indicate the thread begin.
	}
	LeaveCriticalSection( & m_CSExitCheck );

	return ItemNo;
}

void CThumbCtrl::OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	LVITEM item;
	item.iItem = pNMListView->iItem;
	item.iSubItem = 0;
	item.mask = LVIF_IMAGE;
	ASSERT(item.iItem >= 0);

	GetItem(&item);
	EnterCriticalSection( & m_CSNeitherInBothPoolSection );
		pThreadInPool->DeleteItem(item.iItem);
		pThreadOutPool->DeleteItem(item.iItem);
	LeaveCriticalSection( & m_CSNeitherInBothPoolSection );
	*pResult = 0;
}

void CThumbCtrl::OnDeleteAllItems(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	pThreadInPool->Clear();

	KillRenderingThread();

	pThreadOutPool->Clear();

	m_ImageList.DeleteImageList();
	m_ImageList.Create(&m_BackupImageList);

	// Do not sent OnDeleteItem when delete all.
	*pResult = TRUE;
}

void CThumbCtrl::OnDestroy() 
{
	KillRenderingThread();
	if(m_pThread != NULL)
		WaitForSingleObject( m_pThread->m_hThread, INFINITE );
	CListCtrl::OnDestroy();
	
	// TODO: Add your message handler code here
}

//--------------------------------------------------------------------------------------
//	Thread process part.
//--------------------------------------------------------------------------------------

UINT CThumbCtrl::ImageRendering(LPVOID Param)
{
	struct tagParameter * pParameter = (struct tagParameter *)Param;
	CThumbCtrl *Parent = pParameter->Parent;
	CListCtrl *list = (CListCtrl *)CWnd::FromHandle(pParameter->hListView);
	CImageList *ImageList = (CImageList *)CImageList::FromHandle(pParameter->hImageList);
	int Margin = Parent->m_Margin;
	int ThumbWidth = Parent->m_ThumbWidth;
	int ThumbHeight = Parent->m_ThumbHeight;
	delete pParameter;

	CString		PathName, FileName;
	BSTR		bstrPathName;
	int			imgNo, ItemNo;
	Image		* img, * Thumb;
	Rect		ActRect;
	CBitmap		Bmp, * pOldBmp;
	CBrush		bkBrush(RGB(192,192,192)), * pOldBrush;
	CClientDC	cdc(list);
	CDC			memdc;

	memdc.CreateCompatibleDC(&cdc);
	ResetEvent( Parent->m_ExitEvent );		// Indicate the thread begin.

	TRACE0("Begin of Thumbnail thread\n");
	EnterCriticalSection( & Parent->m_CSExitCheck );
	EnterCriticalSection( & Parent->m_CSNeitherInBothPoolSection );
	struct CThreadPool::ListNode node = Parent->pThreadInPool->GetNextNode(FALSE);
	while( node.ItemNo != -1 )		// if InPool is not empty.
	{
		if(WaitForSingleObject(Parent->m_StopEvent, 0) == WAIT_OBJECT_0)
		{
			TRACE0( "  Was stoped\n" );
			break;
		}
		LeaveCriticalSection( & Parent->m_CSExitCheck );
		ItemNo = node.ItemNo;
		PathName = node.FileName;

		bstrPathName = PathName.AllocSysString();
		if(bstrPathName == NULL){
			AfxMessageBox("Alloc sys string failed.", MB_OK | MB_ICONSTOP );
			return 0;
		}
		img = Image::FromFile(bstrPathName);
		::SysFreeString( bstrPathName );
		if( NULL == img ){			// Need more consideration.
			AfxMessageBox(  "Please initialize the Gdiplus." );
			return 0;
		}
		if(img->GetLastStatus() != Ok)
		{
			CString errmsg;
			errmsg.Format("Can't open file %s,\r\n check files please.", PathName);
			AfxMessageBox(errmsg, MB_OK | MB_ICONEXCLAMATION);
			delete img;
			LeaveCriticalSection( & Parent->m_CSNeitherInBothPoolSection );
		}
		else
		{
			Thumb = img->GetThumbnailImage(ThumbWidth - 2*Margin, ThumbHeight - 2*Margin);
			ASSERT(Thumb->GetLastStatus() == Ok);

			VERIFY(Bmp.CreateCompatibleBitmap(&cdc, ThumbWidth, ThumbHeight) != 0);
			pOldBmp = memdc.SelectObject(&Bmp);
			pOldBrush = memdc.SelectObject(&bkBrush);
			memdc.PatBlt(0,0,ThumbWidth,ThumbHeight, PATCOPY);
			memdc.Draw3dRect(0,0,ThumbWidth, ThumbHeight, RGB(222, 222, 222), RGB(128, 128, 128));

			Graphics* graphics;
			graphics = Graphics::FromHDC(memdc.m_hDC);
			ASSERT( img->GetWidth() != 0 && img->GetHeight() != 0 );
			double XRate = (double)img->GetWidth() / (ThumbWidth - 2*Margin);
			double YRate = (double)img->GetHeight() / (ThumbHeight - 2*Margin);
			if(XRate > YRate)
			{
				ActRect.Width = ThumbWidth - 2*Margin;
				ActRect.Height = img->GetHeight() / XRate;
				ActRect.X = Margin;
				ActRect.Y = (ThumbHeight - 2*Margin - ActRect.Height) / 2 + Margin;
			}
			else
			{
				ActRect.Height = ThumbHeight - 2*Margin;
				ActRect.Width = img->GetWidth() / YRate;
				ActRect.X = (ThumbWidth - 2*Margin - ActRect.Width) / 2 + Margin;
				ActRect.Y = Margin;
			}
			graphics->DrawImage(Thumb, ActRect);
			delete graphics;
			delete Thumb;
			delete img;

			memdc.SelectObject(pOldBrush);
			memdc.SelectObject(pOldBmp);

			imgNo = ImageList->Add(&Bmp, RGB(255,255,255));
			Bmp.DeleteObject();
			if(imgNo == -1){
				AfxMessageBox( "Can't add image into the Imaglist.", MB_OK | MB_ICONSTOP );
				return 0;
			}

			Parent->pThreadOutPool->AddNode( ItemNo, imgNo);
			LeaveCriticalSection( & Parent->m_CSNeitherInBothPoolSection );
			list->PostMessage(WM_UPDATE_IMAGEDATA, 0, 0);
		}

		EnterCriticalSection( & Parent->m_CSExitCheck );
		EnterCriticalSection( & Parent->m_CSNeitherInBothPoolSection );
		node = Parent->pThreadInPool->GetNextNode(FALSE);
	}
	LeaveCriticalSection( & Parent->m_CSNeitherInBothPoolSection );

	EnterCriticalSection( & Parent->m_CSSetStop );
		SetEvent(Parent->m_ExitEvent);
		WaitForSingleObject(Parent->m_StopEvent, 0);
	LeaveCriticalSection( & Parent->m_CSSetStop );

	LeaveCriticalSection( & Parent->m_CSExitCheck );
	TRACE0("End of Thumbnail thread\n");

	return 1;
}

void CThumbCtrl::KillRenderingThread()
{
	EnterCriticalSection( & m_CSSetStop );
	if(WaitForSingleObject(m_ExitEvent, 0) != WAIT_OBJECT_0)
	{
		SetEvent(m_StopEvent);
		TRACE0("SetEvent of stop\n");
		LeaveCriticalSection( & m_CSSetStop );

		WaitForSingleObject(m_ExitEvent, INFINITE);
		TRACE0("       The thread is already dead.\n");
	}
	else
		LeaveCriticalSection( & m_CSSetStop );
}

// This message handler used to update the image to the list view. This work
// was assigned to thread, but it may lead to deadlock when killRenderingThread
// because main thread will block to wait thread exit and the thread is calling
// SendMessage to send setitem message to list view, and the main thread is 
// waiting and will not answer the message. So dead locked. 
// So we add a OutPool, and thread process the data and put it to the OutPool and 
// Post a user message to main thread, and used this function to handle that message
// and finish setitem function and clear the OutPool.
LRESULT CThumbCtrl::OnUpdateImageData(WPARAM, LPARAM) 
{
	CThreadPool::ListNode node;
	//CListCtrl & list = GetListCtrl();
	node = pThreadOutPool->GetNextNode(TRUE);
	int res;
	while( node.ItemNo != -1 )
	{
		res = SetItem(node.ItemNo, 0, LVIF_IMAGE, NULL, node.ImageNo, 0, 0, 0);
		ASSERT( res != 0 );
		node = pThreadOutPool->GetNextNode(TRUE);
	}
	return 0;
}

