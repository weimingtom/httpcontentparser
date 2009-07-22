// MainUIDlg.cpp : 实现文件
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\MainUIDlg.h"
#include ".\mainuidlg.h"
#include ".\DlgImageBrowser.h"
#include ".\dlgprogramcontrol.h"
#include ".\DlgImageBrowser.h"
#include ".\poptiptrayenddlg.h"
#include ".\dlgregister.h"
#include ".\services.h"
#include ".\dlgregister.h"
#include "PopTipRegDlg.h"
#include ".\poptipregdlg.h"
#include ".\globalvariable.h"
#include <app_constants.h>
#include <softwarestatus.h>
#include <apputility.h>
#include <comdef.h>
#include <logger\logger.h>
#include <definedmsg.h>

// 在Mainui.cpp中定义，他是一个共享变量
extern HWND share_hwnd;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CALLMESSAGE WM_USER + 0x10
const int POS_HISTORY_MENU_ITEM			 = 3;

#define MAX_TOOLTIPS_SHOWTIME		   5000		//  能够出现的最长时间
#define MAX_TOOLTIPS_FREQUENCY		   5000		//  能够出现的最大时间间隔
#define TIMER_ID_HIDE_TOOLTIP				5

#define NAGTREE_FONT_NAME			TEXT("MS Shell Dlg")

// CMainUIDlg 对话框
CMainUIDlg::CMainUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bShown = TRUE;
	dwAppearLastTime_ = GetTickCount();
}

CMainUIDlg::~CMainUIDlg() {
}



// CMainUIDlg 消息处理程序

void CMainUIDlg::OnNMClickTreeNavig(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 获取当前选中的项
	*pResult = 0;
}


BOOL CMainUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置字体
	setControlsFonts();

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_dlgRight.initialize(&m_imageList, this);
	m_dlgRight.OnChangeDlgPage(IDS_TREE_DNS_RULE);
	InitTreeNodes();
	setupTrayMenu();
	
	// 所有实例共享变量，当用户双击程序时，显示该窗口
	share_hwnd = GetSafeHwnd();

	// 设置属性便于查找
	SetProp(this->GetSafeHwnd(), MAIN_WINDOW_PROP_NAME, (HWND)MAIN_WINDOW_PROP_VALUE);

	// 创建Tooltip
	m_traytip.Create(this);
	m_traytip.SetSize(CPPToolTip::PPTTSZ_MARGIN_CX, 4);
	m_traytip.SetSize(CPPToolTip::PPTTSZ_MARGIN_CY, 4);
	m_traytip.SetDelayTime(3000, 500);

	// 由于程序刚刚启动，这里不会自动切换到子模式
	if (Services::isParentModel() == true) {
		BringWindowToTop();
	} else {
		HideMainUI(FALSE);
	}
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}


void CMainUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
		CDlgRegister dlgAbout;
		dlgAbout.DoModal();
	} else if (nID == SC_MINIMIZE) {
		HideMainUI();
	} else {
		CDialog::OnSysCommand(nID, lParam);
	}
}


// 相应热键消息
LRESULT CMainUIDlg::OnHotKey(WPARAM wParam, LPARAM lParam) {
	int id = (int)wParam;
	if (id == HOTKEY_SHOW_MAINUI) {
		if (isShown()) {
			// 使用热键显示及隐藏是，不检测切换
			HideMainUI(FALSE);
		} else {
			OnRequestShowMainUI();
		}
	} else if (id == HOTKEY_SHOW_SWITCH_USER) {
		// 如果工作在父模式下
		if (Services::isParentModel() == true) {
			// 切换到孩子模式
			Services::switchChildModel();
		} else {
			// 之切换模式，不弹出对话框
			m_dlgCheckPassword_.DoModal();
		}
	}

	// 调整图标
	AdjustModelIcon();
	return -1;
}


// 弹出工具窗口
// 直接运行程序即刻，程序应该能够自己验证密码
void CMainUIDlg::OnToolsDesktopimage() {
	TCHAR images[MAX_PATH];
	GetScreenRecordPath(images, MAX_PATH);

	m_dlgImageBrowser_.setImageDir(images);
	m_dlgImageBrowser_.DoModal();
}


// 相应按钮
void CMainUIDlg::OnOK() {
	OnBnClickedMainCancel();
}

void CMainUIDlg::OnCancel() {
	OnBnClickedMainCancel();
}

void CMainUIDlg::OnBnClickedOk()
{	
	
	try {
		if (CRightRegionDlg::SUCCESS_ON_APPLY == m_dlgRight.OnApplyChange()) {
			// TODO Afx
			return;
		}

		if (false == ShowOverTimeMsgBox()) {
			// 如果用户点击注册， 则应该打开相应网页而不是关闭窗口
			return;
		}

		m_dlgSwitchChildren_.DoModal();
		HideMainUI();
	} catch (...) {
		__LERR__("FAILED On create HistoryRecord");
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONEXCLAMATION);
	}
}

void CMainUIDlg::OnBnClickedMainCancel()
{
	try {
		m_dlgRight.OnCancelChange();
		if (false == ShowOverTimeMsgBox()) {
			// 如果用户点击注册， 则应该打开相应网页而不是关闭窗口
			return;
		} else {
			m_dlgSwitchChildren_.DoModal();
			HideMainUI();	// 隐藏窗口
		}
	} catch (...) {
			__LERR__( "FAILED On create HistoryRecord");
			AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONEXCLAMATION);
		}
	} 

// 按下Apply按钮
void CMainUIDlg::OnBnClickedApply()
{
	ShowOverTimeMsgBox();
	m_dlgRight.OnApplyChange();
}

// 设置控件的字体
void CMainUIDlg::setControlsFonts() {
	LOGFONT lf;  
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 14; 
	lf.lfWeight = FW_LIGHT;
	strcpy(lf.lfFaceName, NAGTREE_FONT_NAME);
	m_fontTree.CreateFontIndirect(&lf); 
	GetDlgItem(IDC_TREE_NAVIG)->SetFont(&m_fontTree);

}

//==============================================
// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMainUIDlg::OnPaint() 
{
	if (IsIconic()) {
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	} else {
		if (Services::isParentModel() == false) {
			HideMainUI();
			return;
		} else {
			CDialog::OnPaint();
		}
	}
}


//===================================================
// 初始化左侧导航树
void CMainUIDlg::InitTreeNodes() {
	// m_treeNavigation.DeleteAllItems();
	// 初始化ImageList
	m_imageList.Create(16, 16, ILC_COLOR32 | ILC_MASK, 50, 5);
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_DEFAULT));
	const int INDEX_HOME		= m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_HOME));
	const int INDEX_OPTION	=m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_OPTION));
	const int INDEX_INFORM = m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_INFO));
	m_treeNavigation.SetImageList(&m_imageList, TVSIL_NORMAL);

	CString strRoot;
	/*strRoot.LoadString(IDS_TREE_ROOT);

	HTREEITEM hRoot = m_treeNavigation.InsertItem(strRoot, TVI_ROOT, TVI_LAST);
	m_treeNavigation.SetItemImage(hRoot, INDEX_HOME, INDEX_HOME);
	setItemData(hRoot, -1, INDEX_HOME);*/


	setRulesTreeItems();
	setToolsTreeItems();

	HTREEITEM hItem;
	CString strItem;
	// 规则对话框
	strItem.LoadString(IDS_TREE_OPTIONS);
	hItem = m_treeNavigation.InsertItem(strItem, TVI_ROOT);
	m_treeNavigation.SetItemImage(hItem, INDEX_OPTION, INDEX_OPTION);
	setItemData(hItem, IDS_TREE_OPTIONS, INDEX_OPTION);

	strItem.LoadString(IDS_TREE_ABOUT);
	hItem = m_treeNavigation.InsertItem(strItem, TVI_ROOT);
	m_treeNavigation.SetItemImage(hItem, INDEX_INFORM, INDEX_INFORM);
	setItemData(hItem, IDS_TREE_ABOUT, INDEX_INFORM);

	m_treeNavigation.Expand(TVI_ROOT, TVE_EXPAND);
}




void CMainUIDlg::setToolsTreeItems() {
	const int INDEX_TOOLS	= m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_TOOLS));
	const int INDEX_APP = m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_APPCONTROL));
	const int INDEX_SCREEN = m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_SCREENSHOT));
	const int INDEX_ONLINETIME = m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_ONLINETIME));
	const int INDEX_EYECARE = m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_EYECARE));

	CString strItem;
	strItem.LoadString(IDS_TREE_LEV1_TOOLS);
	HTREEITEM hItemTools = m_treeNavigation.InsertItem(strItem, TVI_ROOT);
	m_treeNavigation.SetItemImage(hItemTools, INDEX_TOOLS, INDEX_TOOLS);
	setItemData(hItemTools, IDS_TREE_LEV1_TOOLS, INDEX_TOOLS);

	HTREEITEM hItem;
	// 视力保护
	strItem.LoadString(IDS_TREE_EYECARE);
	hItem = m_treeNavigation.InsertItem(strItem, hItemTools);
	m_treeNavigation.SetItemImage(hItem, INDEX_EYECARE, INDEX_EYECARE);
	setItemData(hItem, IDS_TREE_EYECARE, INDEX_EYECARE);

	// 应用程序控制
	strItem.LoadString(IDS_PROGRAM_CONTROL);
	hItem = m_treeNavigation.InsertItem(strItem, hItemTools);
	m_treeNavigation.SetItemImage(hItem, INDEX_APP, INDEX_APP);
	setItemData(hItem, IDS_PROGRAM_CONTROL, INDEX_APP);

	// 屏幕记录
	strItem.LoadString(IDS_TREE_SCREEN_SAVE);
	hItem = m_treeNavigation.InsertItem(strItem, hItemTools);
	m_treeNavigation.SetItemImage(hItem, INDEX_SCREEN, INDEX_SCREEN);
	setItemData(hItem, IDS_TREE_SCREEN_SAVE, INDEX_SCREEN);

	// 上网时间
	strItem.LoadString(IDS_TREE_ONLINE_HOUR);
	hItem = m_treeNavigation.InsertItem(strItem, hItemTools);
	m_treeNavigation.SetItemImage(hItem, INDEX_ONLINETIME, INDEX_ONLINETIME);
	setItemData(hItem, IDS_TREE_ONLINE_HOUR, INDEX_ONLINETIME);
	
	// 展开
	m_treeNavigation.Expand(hItemTools, TVE_EXPAND );
}

void CMainUIDlg::setRulesTreeItems() {
	const int INDEX_WEB	= m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_WEB));
	const int INDEX_HISTORY = m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_HISTORY));
	const int INDEX_SEARCH = m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_SEACH));
	const int INDEX_BLACK	= m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_BLACK_DNS));
	const int INDEX_WHITE = m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_WHITE_DNS));

	CString strItem;
	strItem.LoadString(IDS_TREE_LEV1_RULES);
	HTREEITEM hItemRules = m_treeNavigation.InsertItem(strItem, m_treeNavigation.GetRootItem());
	m_treeNavigation.SetItemImage(hItemRules, INDEX_WEB, INDEX_WEB);
	setItemData(hItemRules, IDS_TREE_LEV1_RULES, INDEX_WEB);

	HTREEITEM hItem;

	// Web 白名单
	strItem.LoadString(IDS_DNS_WHITE_LIST); 
	hItem = m_treeNavigation.InsertItem(strItem, hItemRules);
	m_treeNavigation.SetItemImage(hItem, INDEX_WHITE, INDEX_WHITE);
	setItemData(hItem, IDS_DNS_WHITE_LIST, INDEX_WHITE);
	
	// 黑名单
	strItem.LoadString(IDS_TREE_DNS_RULE); 
	hItem = m_treeNavigation.InsertItem(strItem, hItemRules);
	m_treeNavigation.SetItemImage(hItem, INDEX_BLACK, INDEX_BLACK);
	setItemData(hItem, IDS_TREE_DNS_RULE, INDEX_BLACK);
	m_treeNavigation.SelectItem(hItemRules);

	// 搜索规则
	strItem.LoadString(IDS_TREE_SEARCH_RULE); 
	hItem = m_treeNavigation.InsertItem(strItem, hItemRules);
	m_treeNavigation.SetItemImage(hItem, INDEX_SEARCH, INDEX_SEARCH);
	setItemData(hItem, IDS_TREE_SEARCH_RULE, INDEX_SEARCH);

	// WebHistory
	strItem.LoadString(IDS_TREE_WEB_HISTORY);
	hItem = m_treeNavigation.InsertItem(strItem, hItemRules);
	m_treeNavigation.SetItemImage(hItem, INDEX_HISTORY, INDEX_HISTORY);
	setItemData(hItem, IDS_TREE_WEB_HISTORY, INDEX_HISTORY);

	// 展开
	m_treeNavigation.Expand(hItemRules, TVE_EXPAND );
}

void CMainUIDlg::setItemData(HTREEITEM hItem, WORD ids, WORD idi) {
	m_treeNavigation.SetItemData(hItem, MAKELPARAM(ids, idi));
}

void CMainUIDlg::OnTvnSelchangedTreeNavig(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	HTREEITEM hItem = m_treeNavigation.GetSelectedItem();
	DWORD itemData = m_treeNavigation.GetItemData(hItem);

	try {
		// 首先调用
		m_dlgRight.OnChangeDlgPage(itemData);

		*pResult = 0;
	} catch (...) {
		__LERR__("FAILED On create HistoryRecord");
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONEXCLAMATION);
	}
}


// 工具函数
// 根据COM设置，在最小化窗口时，切换模式
void CMainUIDlg::SwitchOnClose() {
	if (true == Services::autoSwithOnClose()) {
		Services::switchChildModel();
	}
}
// 注销热键
void CMainUIDlg::OnDestroy()
{
	UnregisterHotKey(this->GetSafeHwnd(), HOTKEY_SHOW_MAINUI);
	UnregisterHotKey(this->GetSafeHwnd(), HOTKEY_SHOW_SWITCH_USER);
	CDialog::OnDestroy();
}

// 如果程序工作在孩子模式则提示输入密码
// 否则直接弹出对话框
void CMainUIDlg::OnRequestShowMainUI() {
	CString strMenuItem;
	if (Services::isParentModel() == false) {
		// 如果当前模式不是parent mode, 弹出对话框
		// 使用户输入密码
		if (IDOK == m_dlgCheckPassword_.DoModal()) {
			strMenuItem.LoadString(IDS_TRAYMENU_SHOWUI);
			ShowMainUI();
		}
	} else {
		// 如果用户是parent model,则直接弹出对话框
		strMenuItem.LoadString(IDS_TRAYMENU_SHOWUI);
		ShowMainUI();
	}

		// 调整图标
	AdjustModelIcon();
}
void CMainUIDlg::ShowMainUI() {
	// 显示注册提示
	ShowRegTipDlg();

	ShowWindow(SW_SHOW);
	::SetWindowPos(GetSafeHwnd(), CWnd::wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	SetForegroundWindow ();
	m_bShown = TRUE;

	AdjustModelIcon();
}
void CMainUIDlg::HideMainUI(BOOL autoSwitchCheck) {
		
	ShowWindow(SW_HIDE);
	::SetWindowPos(GetSafeHwnd(), CWnd::wndBottom, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	
	m_bShown = FALSE;

	if (TRUE == autoSwitchCheck) {
		SwitchOnClose();
	}

	AdjustModelIcon();
}

// 设置状态
void CMainUIDlg::UpdateUIStateByModel() {
	CMenu *pMenu = m_trayMenu.GetSubMenu(0);
	if (Services::isParentModel() == true) {
		for (UINT i = 0; i < pMenu->GetMenuItemCount(); ++i) {
			const UINT uID = pMenu->GetMenuItemID(i);
			pMenu->EnableMenuItem(uID, MF_ENABLED);
		}
		
		// 选中家长模式
		pMenu->CheckMenuItem(ID_TRAYMENU_MODEL_PARENTS, MF_CHECKED);
		pMenu->CheckMenuItem(ID_TRAYMENU_MODEL_CHILDREN, MF_UNCHECKED);
	} else {
		// 如果在孩子模式下，很多按钮将不可用
		for (UINT i = 0; i < pMenu->GetMenuItemCount(); ++i) {
			const UINT uID = pMenu->GetMenuItemID(i);
			if (uID == ID_TRAYMENU_MAINUI ||
				uID == ID_TRAYMENU_LOCKCOMPUTER || 
				uID == ID_TRAYMENU_DESKTOPIMAGE  ||
				uID == ID_WEBHISTORY_WEBSITES_VISITED  ||
				uID == ID_WEBHISTORY_SEARCHKEYWORD ) {
					pMenu->EnableMenuItem(uID, MF_GRAYED);
				}
		}

		// 使历史几个菜单项不可用
		pMenu->CheckMenuItem(ID_TRAYMENU_MODEL_PARENTS, MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_TRAYMENU_MODEL_CHILDREN, MF_CHECKED);

		// 此外还要隐藏著对话框
		HideMainUI(FALSE);
	}
}

// 设置托盘的图标
void CMainUIDlg::setupTrayMenu() {
	const int SYSTRAY_ID = 1;
	CNewMenu::SetMenuDrawMode(CNewMenu::STYLE_XP_2003);
	m_trayMenu.LoadMenu(IDC_MENU_TRAY_PARENT);

	// 设置// system Tray
	m_sysTray.Create(this,SYSTRAY_ID, CALLMESSAGE, AfxGetApp()->LoadIcon(IDI_MODEL_PROTECTED),_T(""));
	m_sysTray.SetSysMenu(&m_trayMenu);
	AdjustModelIcon();

	// m_trayMenu.ModifyODMenu(0,_T("Register"),  IDB_BITMAP2);
	m_trayMenu.ModifyODMenu(0,_T("Websites Visited"),  IDB_TRAY_HISTORY_WEBSITE);
	//m_trayMenu.ModifyODMenu(0,_T("Web History"),  IDB_TRAY_HOMEPAGE);
	m_trayMenu.ModifyODMenu(0,_T("Home Page"),  IDB_TRAY_HOMEPAGE);
	m_trayMenu.ModifyODMenu(0,_T("Option"),  IDB_TRAY_OPTION);
	m_trayMenu.ModifyODMenu(0,_T("Lock Computer"),  IDB_TRAY_LOCK); 
	m_trayMenu.ModifyODMenu(0,_T("Desktop Image"),  IDB_TRAY_DESKTOPIMAGE);
	m_trayMenu.ModifyODMenu(0,_T("Change Password"),  IDB_TRAY_KEY);

	// History菜单的图标
	m_trayMenu.ModifyODMenu(0,_T("Web sites"),  IDB_TRAY_HISTORY_WEBSITE);
	m_trayMenu.ModifyODMenu(0,_T("Search Keyword"),  IDB_TRAY_HISTORY_SEARCH);
	m_trayMenu.ModifyODMenu(0,_T("Images"),  IDB_TRAY_DESKTOPIMAGE);


	if (! Services::showRegisterMenuItem()) {
		m_trayMenu.RemoveMenu(ID_MAIN_REGISTER, MF_BYCOMMAND);
	}

	// 用于获取sysTray的位置
	m_tray_pos.InitializePositionTracking(this->GetSafeHwnd(),SYSTRAY_ID);
}

void CMainUIDlg::OnMainLockcomputer() {
	// 锁定计算机
	LockComputer();
}


void CMainUIDlg::OnTraymenuMainui() {
	CString strMenuItem;
	if (isShown()) {
		strMenuItem.LoadString(IDS_TRAYMENU_HIDEUI);
		HideMainUI();
	} else {
		OnRequestShowMainUI();
	}
}

// 推出按钮
void CMainUIDlg::OnMainExit() {
	::SetWindowPos(GetSafeHwnd(), HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	CDialog::OnOK();
}

// 改变密码
void CMainUIDlg::OnMainChangepassword()
{
	m_dlgChangePassword_.DoModal();
}

void CMainUIDlg::OnMainParents()
{
	OnRequestShowMainUI();
}
void CMainUIDlg::OnMainChildren()
{
	Services::switchChildModel();
	AdjustModelIcon();
	HideMainUI();
}

void CMainUIDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	UpdateUIStateByModel();
	CDialog::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
}


void CMainUIDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// 如果运行于父模式之下
	if (Services::isParentModel() == true) {
		if (!isShown()) {
			OnRequestShowMainUI();
		} else {
			// 如果没有显示则激活
			HideMainUI(FALSE);
		}
	} else {
		// 如果在子模式下，想要弹出对话框学要输入密码
		OnRequestShowMainUI();
	}

	CDialog::OnLButtonDblClk(nFlags, point);
}

// 显示工具对话框
void CMainUIDlg::OnWebhistoryImages()
{
	TCHAR webimages[MAX_PATH];
	GetImageDirectory(webimages, MAX_PATH);

	m_dlgImageBrowser_.setImageDir(webimages);
	m_dlgImageBrowser_.DoModal();
}

void CMainUIDlg::OnWebhistorySearchkeyword()
{
	m_dlgSearchKeyword_.DoModal();
}

void CMainUIDlg::OnWebhistoryWebsites()
{
	m_dlgWebsites_.DoModal();
}

void CMainUIDlg::OnTraymenuBuyonline()
{
	ShellExecute(NULL, "open", WEBSITES_BUYNOW, NULL, NULL, SW_NORMAL);
}

void CMainUIDlg::OnTraymenuHomepage()
{
	ShellExecute(NULL, "open", HOME_WEBSITES, NULL, NULL, SW_NORMAL);
}

// 调整托盘图标
void CMainUIDlg::AdjustModelIcon() {
	if (Services::isParentModel() == true) {
		m_sysTray.SetIcon(AfxGetApp()->LoadIcon(IDI_MODEL_PARENT));
	} else {
		m_sysTray.SetIcon(AfxGetApp()->LoadIcon(IDI_MODEL_PROTECTED));
	}
}


// 获取帮助
HRESULT CMainUIDlg::get_accHelp(VARIANT varChild, BSTR *pszHelp)
{
	return CDialog::get_accHelp(varChild, pszHelp);
}

LRESULT CMainUIDlg::OnShowServerMsg(WPARAM wParam, LPARAM lParam) {
	return -1;
}

BOOL CMainUIDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	if (pCopyDataStruct->dwData == WM_SHOW_MSG_TOOLTIP) {
		// 保证它不会出现的太频繁
		if (GetTickCount() - dwAppearLastTime_ > MAX_TOOLTIPS_FREQUENCY) {
			CPoint ptIcon;
			BOOL bIconFound = m_tray_pos.GetTrayIconPosition(ptIcon);
			if (bIconFound == -1)
				return TRUE;

			m_tray_pos.RestoreTrayIcon(AfxGetApp()->LoadIcon(IDI_MODEL_PROTECTED));
			CString tooltips;
			tooltips.Format("<table><tr>"
							"<td><icon idres=128></td>"
							"<td>"
								"<right><a><icon idres=158 width=16 height=16 style=g hotstyle></a></right>"
								"<br><center><h2>Familly 007</h2><br><hr color=blue></center><br>"
								"Some of your operation is blocked by family007. <br>"
								"<b>Detail</b><br>     %s  <br>   "
							"</td>"
							"</tr></table>", pCopyDataStruct->lpData);
			
			m_traytip.ShowHelpTooltip(&ptIcon, tooltips);
			dwAppearLastTime_ = GetTickCount();

			KillTimer(TIMER_ID_HIDE_TOOLTIP);
			SetTimer(TIMER_ID_HIDE_TOOLTIP, MAX_TOOLTIPS_SHOWTIME, NULL);
			return TRUE;
		}
	}

	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}

BOOL CMainUIDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	/*if (NULL != m_curDlg) {
		m_curDlg->getHelpLink();
	}*/
	return TRUE;
}

// 显示提示对话框
void CMainUIDlg::OnMainRegister() {
	m_dlgRegister_.DoModal();
}


void CMainUIDlg::ShowRegTipDlg() {
	LONG status = Services::getAppStatus();
	if (SNOWMAN_STATUS_REGISTERED != status) {
		CPopTipRegDlg dlg;
		if (dlg.shouldShow()) {
			dlg.DoModal();
		}
	}
}
bool CMainUIDlg::ShowOverTimeMsgBox() {
	LONG status = Services::getAppStatus();
	if (SNOWMAN_STATUS_OVERTIME == status) {
		CPopTipTrayendDlg dlg;
		UINT result = dlg.DoModal();
		if (ID_BTN_BESN == result) {
			m_dlgRight.OnChangeDlgPage(IDS_TREE_ABOUT);
			return false;
		} else if (ID_BTN_BUYNOW== result) {
			ShellExecute(NULL, "open", WEBSITES_BUYNOW, NULL, NULL, SW_NORMAL);
			return true;
		} else {
			return true;
		}
	} else {
		return true;
	}
}

//===============================
// mfc
void CMainUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_NAVIG, m_treeNavigation);
	DDX_Control(pDX, IDC_STA_FRAME, m_staFunFrame);
}

BEGIN_MESSAGE_MAP(CMainUIDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_CLICK, IDC_TREE_NAVIG, OnNMClickTreeNavig)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_NAVIG, OnTvnSelchangedTreeNavig)
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_MAIN_OK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_MAIN_APPLY, OnBnClickedApply)
	ON_COMMAND(ID_TRAYMENU_CHANGEPASSWORD, OnMainChangepassword)
	ON_COMMAND(ID_TRAYMENU_MAINUI, OnTraymenuMainui)
	ON_COMMAND(ID_TRAYMENU_EXIT, OnMainExit)
	ON_COMMAND(ID_TRAYMENU_MODEL_PARENTS, OnMainParents)
	ON_COMMAND(ID_TRAYMENU_MODEL_CHILDREN, OnMainChildren)
	ON_COMMAND(ID_TRAYMENU_DESKTOPIMAGE, OnToolsDesktopimage)
	ON_COMMAND(ID_TRAYMENU_LOCKCOMPUTER, OnMainLockcomputer)
	ON_BN_CLICKED(IDC_MAIN_CANCEL, OnBnClickedMainCancel)
	ON_WM_DESTROY()
	ON_WM_INITMENUPOPUP()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_WEBHISTORY_IMAGES, OnWebhistoryImages)
	ON_COMMAND(ID_WEBHISTORY_SEARCHKEYWORD, OnWebhistorySearchkeyword)
	ON_COMMAND(ID_WEBHISTORY_WEBSITES_VISITED, OnWebhistoryWebsites)
	ON_COMMAND(ID_MAIN_REGISTER, OnMainRegister)
	ON_MESSAGE(WM_SHOW_MSG_TOOLTIP, OnShowServerMsg)
	ON_WM_HELPINFO()
	ON_WM_COPYDATA()
	ON_WM_TIMER()
	ON_COMMAND(ID_TRAYMENU_BUYONLINE, OnTraymenuBuyonline)
	ON_COMMAND(ID_TRAYMENU_HOMEPAGE, OnTraymenuHomepage)
END_MESSAGE_MAP()

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CMainUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CMainUIDlg::PreTranslateMessage(MSG* pMsg)
{
	m_traytip.RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}


void CMainUIDlg::OnTimer(UINT nIDEvent)
{
	if (TIMER_ID_HIDE_TOOLTIP == nIDEvent) {
		m_traytip.HideTooltip();
		KillTimer(TIMER_ID_HIDE_TOOLTIP);
		return;
	}
	CDialog::OnTimer(nIDEvent);
}
