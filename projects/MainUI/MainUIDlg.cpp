// MainUIDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "MainUIDlg.h"
#include ".\mainuidlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMainUIDlg 对话框

namespace {
enum {
	INDEX_IMAGE_RULE,
	INDEX_DNS_RULE,
	INDEX_SEARCH_RULE,
	INDEX_ONLINE_HOUR,
	INDEX_HELP,
	INDEX_ABOUT
};
const DWORD INDEX[] = {
	INDEX_IMAGE_RULE,
	INDEX_DNS_RULE,
	INDEX_SEARCH_RULE,
	INDEX_ONLINE_HOUR,
	INDEX_HELP,
	INDEX_ABOUT
};
};

CMainUIDlg::CMainUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_curDlg = NULL;
}

void CMainUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_NAVIG, m_treeNavigation);
}

BEGIN_MESSAGE_MAP(CMainUIDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_CLICK, IDC_TREE_NAVIG, OnNMClickTreeNavig)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_NAVIG, OnTvnSelchangedTreeNavig)
END_MESSAGE_MAP()


void CMainUIDlg::InitTreeNodes() {
	// m_treeNavigation.DeleteAllItems();

	CString strRoot;
	strRoot.LoadString(IDS_TREE_ROOT);

	HTREEITEM hRoot = m_treeNavigation.InsertItem(strRoot, TVI_ROOT, TVI_LAST);
	m_treeNavigation.SetItemData(hRoot, -1);


	HTREEITEM hItem;
	CString strItem;
	// 注意顺序有关系的
	strItem.LoadString(IDS_TREE_IMAGE_RULE);
	hItem = m_treeNavigation.InsertItem(strItem, hRoot);
	m_treeNavigation.SetItemData(hItem, INDEX_IMAGE_RULE);
	m_treeNavigation.SelectItem(hItem);

	strItem.LoadString(IDS_TREE_DNS_RULE); 
	hItem = m_treeNavigation.InsertItem(strItem, hRoot);
	m_treeNavigation.SetItemData(hItem, INDEX_DNS_RULE);

	strItem.LoadString(IDS_TREE_SEARCH_RULE); 
	hItem = m_treeNavigation.InsertItem(strItem, hRoot);
	m_treeNavigation.SetItemData(hItem, INDEX_SEARCH_RULE);

	strItem.LoadString(IDS_TREE_ONLINE_HOUR);
	hItem = m_treeNavigation.InsertItem(strItem, hRoot);
	m_treeNavigation.SetItemData(hItem, INDEX_ONLINE_HOUR);

	strItem.LoadString(IDS_TREE_HELP);
	hItem = m_treeNavigation.InsertItem(strItem, hRoot);
	m_treeNavigation.SetItemData(hItem, INDEX_HELP);

	strItem.LoadString(IDS_TREE_ABOUT);
	hItem = m_treeNavigation.InsertItem(strItem, hRoot);
	m_treeNavigation.SetItemData(hItem, INDEX_ABOUT);


	m_treeNavigation.Expand(hRoot, TVE_EXPAND);
}

void CMainUIDlg::showDlg() {
	CRect rect;
	CWnd * pWndLeft = GetDlgItem(IDC_POSITION_RIGHT);
	pWndLeft->GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_curDlg->SetWindowPos(&wndTop, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
}
void CMainUIDlg::initDlgs() {
	m_dlgImageRules.Create(CDlgImageRule::IDD, this);
	m_dlgHelp.Create(CDlgHelp::IDD, this);
	m_dlgOnlineHour.Create(CDlgOnlineHour::IDD, this);
	m_dlgSearchRule.Create(CDlgSearchRule::IDD, this);
	m_dlgDnsRule.Create(CDlgDNSRule::IDD, this);
	m_dlgAbout.Create(CDlgAbout::IDD, this);

	m_curDlg = &m_dlgImageRules;
	showDlg();
}
void CMainUIDlg::setCurDlg(const DWORD item) {
	if (item == -1)  // 如果是根节点
		return;

	ASSERT (m_curDlg != NULL);
	m_curDlg->ShowWindow(SW_HIDE);
	switch (item) {
		case INDEX_IMAGE_RULE:
			m_curDlg = &m_dlgImageRules;
			break;
		case INDEX_DNS_RULE:
			m_curDlg = &m_dlgDnsRule;
			break;
		case INDEX_SEARCH_RULE:
			m_curDlg = &m_dlgSearchRule;
			break;
		case INDEX_ONLINE_HOUR:
			m_curDlg = &m_dlgOnlineHour;
			break;
		case INDEX_HELP:
			m_curDlg = &m_dlgHelp;
			break;
		case INDEX_ABOUT:
			m_curDlg = &m_dlgAbout;
			break;
		default:
			ASSERT(false);
			break;
	}
	showDlg();
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

	// 将\“关于...\”菜单项添加到系统菜单中。

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
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CMainUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMainUIDlg::OnPaint() 
{
	if (IsIconic())
	{
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
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CMainUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMainUIDlg::OnTvnSelchangedTreeNavig(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	// HTREEITEM hItem = m_treeNavigation.GetSelectedItem();
	DWORD itemData = m_treeNavigation.GetItemData(pNMTreeView->itemNew.hItem);
	setCurDlg(itemData);

	*pResult = 0;
}
