// MainUIDlg.cpp : 实现文件
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\MainUIDlg.h"
#include ".\mainuidlg.h"
#include ".\DlgImageBrowser.h"
#include ".\dlgprogramcontrol.h"
#include ".\DlgImageBrowser.h"
#include ".\dlgregister.h"
#include ".\services.h"
#include ".\dlgregister.h"
#include ".\globalvariable.h"
#include <app_constants.h>
#include <apputility.h>
#include <comdef.h>
#include <logger_name.h>

#define 	HISTORY_MENU_POS  3

// 在Mainui.cpp中定义，他是一个共享变量
extern HWND share_hwnd;

#define RIGTH_TOP_FONT_NAME			TEXT("MS Shell Dlg")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CALLMESSAGE WM_USER + 0x10

#define ID_TIMER    100
#define TIME_ESCPSE	500


// CMainUIDlg 对话框
CMainUIDlg::CMainUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_curDlg = NULL;
	m_bShown = TRUE;
}

CMainUIDlg::~CMainUIDlg() {
}
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
	ON_WM_KEYDOWN()
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
	ON_WM_TIMER()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_WEBHISTORY_IMAGES, OnWebhistoryImages)
	ON_COMMAND(ID_WEBHISTORY_SEARCHKEYWORD, OnWebhistorySearchkeyword)
	ON_COMMAND(ID_WEBHISTORY_WEBSITES, OnWebhistoryWebsites)
	ON_COMMAND(ID_MAIN_REGISTER, OnMainRegister)
	ON_WM_HELPINFO()
END_MESSAGE_MAP()

// CMainUIDlg 消息处理程序

void CMainUIDlg::OnNMClickTreeNavig(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 获取当前选中的项
	*pResult = 0;
}

void CMainUIDlg::AdjustModelIcon() {
	if (Services::isParentModel() == true) {
		m_sysTray.SetIcon(AfxGetApp()->LoadIcon(IDI_MODEL_PARENT));
	} else {
		m_sysTray.SetIcon(AfxGetApp()->LoadIcon(IDI_MODEL_PROTECTED));
	}
}

// 设置状态
void CMainUIDlg::UpdateUIStateByModel() {
	CMenu *pMenu = m_trayMenu.GetSubMenu(0);
	if (Services::isParentModel() == true) {
		for (UINT i = 0; i < pMenu->GetMenuItemCount(); ++i) {
			const UINT uID = pMenu->GetMenuItemID(i);
			pMenu->EnableMenuItem(uID, MF_ENABLED);
		}

		// 使历史几个菜单项可用
		CMenu* pHistory = pMenu->GetSubMenu(HISTORY_MENU_POS);
		for (UINT i = 0; i < pHistory->GetMenuItemCount(); ++i) {
			const UINT uID = pHistory->GetMenuItemID(i);
			pHistory->EnableMenuItem(uID, MF_ENABLED);
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
				uID == ID_TRAYMENU_DESKTOPIMAGE) {
					pMenu->EnableMenuItem(uID, MF_GRAYED);
				}
		}

		// 使历史几个菜单项不可用
		CMenu* pHistory = pMenu->GetSubMenu(HISTORY_MENU_POS);
		for (UINT i = 0; i < pHistory->GetMenuItemCount(); ++i) {
			const UINT uID = pHistory->GetMenuItemID(i);
			pHistory->EnableMenuItem(uID, MF_GRAYED);
		}

		pMenu->CheckMenuItem(ID_TRAYMENU_MODEL_PARENTS, MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_TRAYMENU_MODEL_CHILDREN, MF_CHECKED);

		// 此外还要隐藏著对话框
		HideMainUI();
	}
}

// 设置托盘的图标
void CMainUIDlg::setupTrayMenu() {
	m_trayMenu.LoadMenu(IDC_MENU_TRAY_PARENT);
	// 设置// system Tray
	m_sysTray.Create(this,10200, CALLMESSAGE, AfxGetApp()->LoadIcon(IDI_MODEL_PROTECTED),_T(""));
	m_sysTray.SetSysMenu(&m_trayMenu);
	AdjustModelIcon();

	// m_trayMenu.ModifyODMenu(0,_T("Register"),  IDB_BITMAP2);
	m_trayMenu.ModifyODMenu(0,_T("Websites"),  IDB_TRAY_HISTORY_WEBSITE);
	// m_trayMenu.ModifyODMenu(0,_T("Web History"),  IDB_BITMAP2);
	m_trayMenu.ModifyODMenu(0,_T("Option"),  IDB_TRAY_OPTION);
	m_trayMenu.ModifyODMenu(0,_T("Lock Computer"),  IDB_TRAY_LOCK); 
	m_trayMenu.ModifyODMenu(0,_T("Desktop Image"),  IDB_TRAY_DESKTOPIMAGE);
	m_trayMenu.ModifyODMenu(0,_T("Change Password"),  IDB_TRAY_KEY);

	// History菜单的图标
	m_trayMenu.ModifyODMenu(0,_T("Web sites"),  IDB_TRAY_HISTORY_WEBSITE);
	m_trayMenu.ModifyODMenu(0,_T("Search Keyword"),  IDB_TRAY_HISTORY_SEARCH);
	m_trayMenu.ModifyODMenu(0,_T("Images"),  IDB_TRAY_DESKTOPIMAGE);
}

BOOL CMainUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	share_hwnd = GetSafeHwnd();

	// 设置一个属性，一边用户在开启新程序时相应
	// 通过获取此属性，便能判断程序是否已经启动
	SetProp(this->GetSafeHwnd(), MAIN_WINDOW_PROP_NAME, (HWND)MAIN_WINDOW_PROP_VALUE);

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

	initDlgs();
	InitTreeNodes();

	setupTrayMenu();

	SetTimer(ID_TIMER, TIME_ESCPSE, NULL);

	// 由于程序刚刚启动，这里不会自动切换到子模式
	HideMainUI(FALSE);
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

void CMainUIDlg::OnTraymenuMainui() {
	CString strMenuItem;
	if (isShown()) {
		strMenuItem.LoadString(IDS_TRAYMENU_HIDEUI);
		HideMainUI();
	} else {
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
	}
}

// 推出按钮
void CMainUIDlg::OnMainExit() {
	::SetWindowPos(GetSafeHwnd(), HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	CDialog::OnOK();
}

void CMainUIDlg::OnMainChangepassword()
{
	m_dlgChangePassword_.DoModal();
}

//====================================
// 模式切换
void CMainUIDlg::OnMainParents()
{
	if (Services::isParentModel() == false) {
		if (IDOK == m_dlgCheckPassword_.DoModal()) {
			ShowMainUI();
		}
	} else {
		ShowMainUI();
	}

	// 调整图标
	AdjustModelIcon();
}
void CMainUIDlg::OnMainChildren()
{
	Services::switchChildModel();
	AdjustModelIcon();
}

// 相应热键消息
LRESULT CMainUIDlg::OnHotKey(WPARAM wParam, LPARAM lParam) {
	int id = (int)wParam;
	if (id == HOTKEY_SHOW_MAINUI) {
		// 如果工作在子模式下， 则不相应
		if (Services::isParentModel() == false)
			return -1;
		if (isShown()) {

			// 使用热键显示及隐藏是，不检测切换
			HideMainUI(FALSE);
		} else {
			ShowMainUI();
		}
	} else if (id == HOTKEY_SHOW_SWITCH_USER) {
		// 如果工作在父模式下
		if (Services::isParentModel() == true) {
			// 切换到孩子模式
			Services::switchChildModel();
		} else {
			// 在孩子模式下， 弹出对话框,如果对话框已经显示， 则直接显示之前的对话框
			if (IDOK == m_dlgCheckPassword_.DoModal()) {
				ShowMainUI();
			} else {
				HideMainUI(FALSE);	// 本身在子模式下，不需要检测
			}
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
	HideMainUI();
}

void CMainUIDlg::OnCancel() {
	HideMainUI();
}

void CMainUIDlg::OnBnClickedOk()
{
	ASSERT (NULL != m_curDlg);
	try {
		if ( -1 == m_curDlg->Apply()) {
			m_curDlg->Restore();
			return;
		}

		m_curDlg->SetModify(false);

		m_dlgSwitchChildren_.DoModal();
		HideMainUI();
	} catch (...) {
		LOGGER_WRITE(MAINUI_LOGGER_ERROR, "FAILED On create HistoryRecord")
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONEXCLAMATION);
	}
}

void CMainUIDlg::OnBnClickedMainCancel()
{
	try {
		HideMainUI();	// 隐藏窗口
		m_curDlg->Restore();	// 恢复设置
		m_curDlg->SetModify(false);
	} catch (...) {
			LOGGER_WRITE(MAINUI_LOGGER_ERROR, "FAILED On create HistoryRecord")
			AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONEXCLAMATION);
		}
	} 

// 按下Apply按钮
void CMainUIDlg::OnBnClickedApply()
{
	ASSERT (NULL != m_curDlg);

	try {
		if ( FAILED_APPLY == m_curDlg->Apply()) {
			m_curDlg->Restore();
			return;
		}

	} catch (...) {
		LOGGER_WRITE(MAINUI_LOGGER_ERROR, "FAILED On create HistoryRecord")
	}

	m_curDlg->SetModify(false);
}

// 设置控件的字体
void CMainUIDlg::setControlsFonts() {
	LOGFONT lf;  
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 14; 
	lf.lfWeight = FW_LIGHT;
	strcpy(lf.lfFaceName, RIGTH_TOP_FONT_NAME);
	m_fontTree.CreateFontIndirect(&lf); 
	GetDlgItem(IDC_TREE_NAVIG)->SetFont(&m_fontTree);

	memset(&lf, 0, sizeof(LOGFONT));
	strcpy(lf.lfFaceName, RIGTH_TOP_FONT_NAME);
	lf.lfWeight = FW_BOLD;
	lf.lfHeight = 18;
	m_fontTitle.CreateFontIndirect(&lf); 
	GetDlgItem(IDC_RIGHT_TITLE)->SetFont(&m_fontTitle);
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

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CMainUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CMainUIDlg::OnMainLockcomputer() {
	// 锁定计算机
	LockComputer();
}

//===================================================
// 设置子对话框
void CMainUIDlg::InitTreeNodes() {
	// m_treeNavigation.DeleteAllItems();
	// 初始化ImageList
	m_imageList.Create(16, 16, ILC_COLOR24 | ILC_MASK, 50, 5);
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_DEFAULT));
	const int INDEX_HOME		= m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_HOME));
	const int INDEX_TIME			= m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_TIME));
	const int INDEX_OPTION	=m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_OPTION));
	m_treeNavigation.SetImageList(&m_imageList, TVSIL_NORMAL);

	CString strRoot;
	strRoot.LoadString(IDS_TREE_ROOT);

	HTREEITEM hRoot = m_treeNavigation.InsertItem(strRoot, TVI_ROOT, TVI_LAST);
	m_treeNavigation.SetItemImage(hRoot, INDEX_HOME, INDEX_HOME);
	m_treeNavigation.SetItemData(hRoot, -1);

	setRulesDlg();
	setToolsDlg();

	HTREEITEM hItem;
	CString strItem;
	// 规则对话框
	strItem.LoadString(IDS_TREE_OPTIONS);
	hItem = m_treeNavigation.InsertItem(strItem, hRoot);
	m_treeNavigation.SetItemImage(hItem, INDEX_OPTION, INDEX_OPTION);
	m_treeNavigation.SetItemData(hItem, IDS_TREE_OPTIONS);

	strItem.LoadString(IDS_TREE_ABOUT);
	hItem = m_treeNavigation.InsertItem(strItem, hRoot);
	m_treeNavigation.SetItemData(hItem, IDS_TREE_ABOUT);

	m_treeNavigation.Expand(hRoot, TVE_EXPAND);
}

void CMainUIDlg::showDlg() {
	try {
		CRect rect;
		CWnd * pWndLeft = GetDlgItem(IDC_POSITION_RIGHT);
		pWndLeft->GetWindowRect(&rect);
		ScreenToClient(&rect);
		m_curDlg->SetWindowPos(&wndTop, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
		m_curDlg->OnShow();
	} catch (...) {
		LOGGER_WRITE(MAINUI_LOGGER_ERROR, "FAILED On create HistoryRecord")
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONEXCLAMATION);
	}
}

// 创建对话框
void CMainUIDlg::initDlgs() {
	try {
		// TODO
		// 如果这里COM注册出现错误可能所有的地方都会弹出对话框
		// 如果能够使用抛出异常的方式就好了， 这样只会产生一个错误对话框
		// 但是也可能导致对话框无法正常显示
		// 只要简单的关闭对话框就行了！
		m_dlgOnlineHour.Create(CDlgOnlineHour::IDD, this);
		m_dlgSearchRule.Create(CDlgSearchRule::IDD, this);
		m_dlgDnsRule.Create(CDlgBlackDNSList::IDD, this);
		m_dlgAbout.Create(CDlgAbout::IDD, this);
		m_lev1Rules.Create(CLev1DlgRules::IDD, this);
		m_dlgOptions.Create(CDlgOptions::IDD, this);
		m_dlgEyecare.Create(CDlgEyecare::IDD, this);
		m_dlgWhiteDNS.Create(CDlgWhiteDNSList::IDD, this);
		m_lev1Tools.Create(CLev1DlgTools::IDD, this);
		m_dlgScreenSaver.Create(CDlgScreenshot::IDD, this);
		m_dlgWebHistory.Create(CDlgWebHistory::IDD, this);
		m_dlgProgramControl.Create(CDlgProgramControl::IDD, this);
		m_curDlg = &m_lev1Rules;
		showDlg();
		
	} catch (...) {
		LOGGER_WRITE(MAINUI_LOGGER_ERROR, "FAILED On create HistoryRecord")
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONEXCLAMATION);
		EndDialog(IDCANCEL);
	}
}

void CMainUIDlg::setToolsDlg() {
	const int INDEX_TOOLS	= m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_TOOLS));
	const int INDEX_APP = m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_APPCONTROL));
	const int INDEX_SCREEN = m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_SCREENSHOT));
	const int INDEX_DISCONNECT = m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_DISCONNECT));
	const int INDEX_EYECARE = m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_EYECARE));

	CString strItem;
	strItem.LoadString(IDS_TREE_LEV1_TOOLS);
	HTREEITEM hItemTools = m_treeNavigation.InsertItem(strItem, m_treeNavigation.GetRootItem());
	m_treeNavigation.SetItemData(hItemTools, IDS_TREE_LEV1_RULES);
	m_treeNavigation.SetItemImage(hItemTools, INDEX_TOOLS, INDEX_TOOLS);

	HTREEITEM hItem;
	// 视力保护
	strItem.LoadString(IDS_TREE_EYECARE);
	hItem = m_treeNavigation.InsertItem(strItem, hItemTools);
	m_treeNavigation.SetItemData(hItem, IDS_TREE_EYECARE);
	m_treeNavigation.SetItemImage(hItem, INDEX_EYECARE, INDEX_EYECARE);

	// 应用程序控制
	strItem.LoadString(IDS_PROGRAM_CONTROL);
	hItem = m_treeNavigation.InsertItem(strItem, hItemTools);
	m_treeNavigation.SetItemData(hItem, IDS_PROGRAM_CONTROL);
	m_treeNavigation.SetItemImage(hItem, INDEX_APP, INDEX_APP);

	// 屏幕记录
	strItem.LoadString(IDS_TREE_SCREEN_SAVE);
	hItem = m_treeNavigation.InsertItem(strItem, hItemTools);
	m_treeNavigation.SetItemData(hItem, IDS_TREE_SCREEN_SAVE);
	m_treeNavigation.SetItemImage(hItem, INDEX_SCREEN, INDEX_SCREEN);

	// 上网时间
	strItem.LoadString(IDS_TREE_ONLINE_HOUR);
	hItem = m_treeNavigation.InsertItem(strItem, hItemTools);
	m_treeNavigation.SetItemData(hItem, IDS_TREE_ONLINE_HOUR);
	m_treeNavigation.SetItemImage(hItem, INDEX_DISCONNECT, INDEX_DISCONNECT);
	
	// 展开
	m_treeNavigation.Expand(hItemTools, TVE_EXPAND );
}

void CMainUIDlg::setRulesDlg() {
	const int INDEX_WEB	= m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_WEB));
	const int INDEX_HISTORY = m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_HISTORY));
	const int INDEX_SEARCH = m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_SEACH));
	const int INDEX_BLACK	= m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_BLACK_DNS));
	const int INDEX_WHITE = m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TREE_WHITE_DNS));

	CString strItem;
	strItem.LoadString(IDS_TREE_LEV1_RULES);
	HTREEITEM hItemRules = m_treeNavigation.InsertItem(strItem, m_treeNavigation.GetRootItem());
	m_treeNavigation.SetItemData(hItemRules, IDS_TREE_LEV1_RULES);
	m_treeNavigation.SetItemImage(hItemRules, INDEX_WEB, INDEX_WEB);

	HTREEITEM hItem;

	// Web 白名单
	strItem.LoadString(IDS_DNS_WHITE_LIST); 
	hItem = m_treeNavigation.InsertItem(strItem, hItemRules);
	m_treeNavigation.SetItemData(hItem, IDS_DNS_WHITE_LIST);
	m_treeNavigation.SetItemImage(hItem, INDEX_WHITE, INDEX_WHITE);
	
	// 黑名单
	strItem.LoadString(IDS_TREE_DNS_RULE); 
	hItem = m_treeNavigation.InsertItem(strItem, hItemRules);
	m_treeNavigation.SetItemData(hItem, IDS_TREE_DNS_RULE);
	setCurDlg(IDS_TREE_DNS_RULE);
	m_treeNavigation.SetItemImage(hItem, INDEX_BLACK, INDEX_BLACK);

	// 搜索规则
	strItem.LoadString(IDS_TREE_SEARCH_RULE); 
	hItem = m_treeNavigation.InsertItem(strItem, hItemRules);
	m_treeNavigation.SetItemData(hItem, IDS_TREE_SEARCH_RULE);
	m_treeNavigation.SetItemImage(hItem, INDEX_SEARCH, INDEX_SEARCH);

	// WebHistory
	strItem.LoadString(IDS_TREE_WEB_HISTORY);
	hItem = m_treeNavigation.InsertItem(strItem, hItemRules);
	m_treeNavigation.SetItemData(hItem, IDS_TREE_WEB_HISTORY);
	m_treeNavigation.SetItemImage(hItem, INDEX_HISTORY, INDEX_HISTORY);

	m_treeNavigation.SelectItem(hItemRules);

	// 展开
	m_treeNavigation.Expand(hItemRules, TVE_EXPAND );
}


void CMainUIDlg::ChangeCurDlg(CBaseDlg *dlg) {
	if (m_curDlg != dlg) {
		m_curDlg = dlg;
	}
}

// 设置当前显示的对话框
void CMainUIDlg::setCurDlg(const DWORD item) {
	if (item == -1)  // 如果是根节点
		return;

	ASSERT (m_curDlg != NULL);
	m_curDlg->ShowWindow(SW_HIDE);
	switch (item) {
		case IDS_TREE_EYECARE:
			ChangeCurDlg(&m_dlgEyecare);
			break;
		case IDS_TREE_LEV1_RULES:
			ChangeCurDlg(&m_lev1Rules);
			break;
		case IDS_DNS_WHITE_LIST:
			ChangeCurDlg(&m_dlgWhiteDNS);
			break;
		case IDS_TREE_DNS_RULE:
			ChangeCurDlg(&m_dlgDnsRule);
			break;
		case IDS_TREE_SEARCH_RULE:
			ChangeCurDlg(&m_dlgSearchRule);
			break;
		case IDS_TREE_ONLINE_HOUR:
			ChangeCurDlg(&m_dlgOnlineHour);
			break;
		case IDS_PROGRAM_CONTROL:
			ChangeCurDlg(&m_dlgProgramControl);
			break;
		case IDS_TREE_ABOUT:
			ChangeCurDlg(&m_dlgAbout);
			break;
		case IDS_TREE_OPTIONS:
			ChangeCurDlg(&m_dlgOptions);
			break;
		case IDS_TREE_LEV1_TOOLS:
			ChangeCurDlg(&m_lev1Tools);
			break;
		case IDS_TREE_SCREEN_SAVE:
			ChangeCurDlg(&m_dlgScreenSaver);
			break;
		case IDS_TREE_WEB_HISTORY:
			ChangeCurDlg(&m_dlgWebHistory);
			break;
		default:
			ASSERT(false);
			break;
	}
	CString strItem;
	strItem.LoadString(item);
	GetDlgItem(IDC_RIGHT_TITLE)->SetWindowText(strItem);

	showDlg();
}

void CMainUIDlg::OnTvnSelchangedTreeNavig(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	// HTREEITEM hItem = m_treeNavigation.GetSelectedItem();
	DWORD itemData = (DWORD)m_treeNavigation.GetItemData(pNMTreeView->itemNew.hItem);

	try {
		// 首先调用
		if (m_curDlg->BeforeChange() == 1) {
			setCurDlg(itemData);
			m_curDlg->AfterChange();
		} else {
			m_curDlg->Restore();
			m_curDlg->SetModify(false);
		}

		*pResult = 0;
	} catch (...) {
		LOGGER_WRITE(MAINUI_LOGGER_ERROR, "FAILED On create HistoryRecord")
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONEXCLAMATION);
	}
}


// 工具函数
// 根据COM设置，在最小化窗口时，切换模式
void CMainUIDlg::SwitchOnClose() {
	// 设置
	try {
		ISnowmanSetting *app = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&app);
		if (FAILED(hr)) {
			LOGGER_WRITE(MAINUI_LOGGER_ERROR, "failed on create snowmansetting")
			return;
		}
		
		// 是否需要切换到模式
		/*app->get_autoSwitchOnClose(&val);
		if (VARIANT_TRUE == val) {
			Services::switchChildModel();
		}*/
	} catch (...) {
		LOGGER_WRITE(MAINUI_LOGGER_ERROR, "CATCH(...)")
	}
}
// 注销热键
void CMainUIDlg::OnDestroy()
{
	UnregisterHotKey(this->GetSafeHwnd(), HOTKEY_SHOW_MAINUI);
	UnregisterHotKey(this->GetSafeHwnd(), HOTKEY_SHOW_SWITCH_USER);
	CDialog::OnDestroy();
}

void CMainUIDlg::ShowMainUI() {
	ShowWindow(SW_SHOW);
	::SetWindowPos(GetSafeHwnd(), CWnd::wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	SetForegroundWindow ();
	m_bShown = TRUE;
}
void CMainUIDlg::HideMainUI(BOOL autoSwitchCheck) {
	ShowWindow(SW_HIDE);
	::SetWindowPos(GetSafeHwnd(), CWnd::wndBottom, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	
	m_bShown = FALSE;

	if (TRUE == autoSwitchCheck) {
		SwitchOnClose();
	}
}


void CMainUIDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	UpdateUIStateByModel();
	CDialog::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
}


void CMainUIDlg::OnTimer(UINT nIDEvent)
{
	// 是否是子状态，如果是则隐藏窗口
	if (isShown() &&Services::isParentModel() == false) {
		HideMainUI(FALSE); // 因为是子模式
	}

	AdjustModelIcon();
	CDialog::OnTimer(nIDEvent);
}

void CMainUIDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// 如果运行于父模式之下
	if (Services::isParentModel() == true) {
		if (!isShown()) {
			ShowMainUI();
		} else {
			// 如果没有显示则激活
			HideMainUI(FALSE);
		}
	}
	CDialog::OnLButtonDblClk(nFlags, point);
}

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

HRESULT CMainUIDlg::get_accHelp(VARIANT varChild, BSTR *pszHelp)
{
	return CDialog::get_accHelp(varChild, pszHelp);
}

void CMainUIDlg::OnMainRegister() {
	m_dlgRegister_.DoModal();
}

BOOL CMainUIDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	if (NULL != m_curDlg) {
		m_curDlg->getHelpLink();
	}
	return TRUE;
}
