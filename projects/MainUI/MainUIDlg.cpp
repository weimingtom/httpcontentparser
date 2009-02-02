// MainUIDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include ".\MainUI.h"
#include ".\MainUIDlg.h"
#include ".\mainuidlg.h"
#include ".\dlgchangepassword.h"
#include ".\dlgcheckpassword.h"
#include ".\DlgImageBrowser.h"
#include ".\services.h"
#include ".\globalvariable.h"
#include <app_constants.h>
#include <apputility.h>
#include <comdef.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CALLMESSAGE WM_USER + 0x10

#define ID_TIMER    100
#define TIME_ESCPSE	500

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMainUIDlg �Ի���
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
	ON_COMMAND(ID_TRAYMENU_WEBHISTORY, OnToolsWebhistory)
	ON_COMMAND(ID_TRAYMENU_LOCKCOMPUTER, OnMainLockcomputer)
	ON_BN_CLICKED(IDC_MAIN_CANCEL, OnBnClickedMainCancel)
	ON_WM_DESTROY()
	ON_WM_INITMENUPOPUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMainUIDlg ��Ϣ�������

void CMainUIDlg::OnNMClickTreeNavig(NMHDR *pNMHDR, LRESULT *pResult)
{
	// ��ȡ��ǰѡ�е���
	*pResult = 0;
}

// ����״̬
void CMainUIDlg::UpdateUIStateByModel() {
	CMenu *pMenu = m_trayMenu.GetSubMenu(0);
	if (Services::isParentModel() == true) {
		for (UINT i = 0; i < pMenu->GetMenuItemCount(); ++i) {
			const UINT uID = pMenu->GetMenuItemID(i);
			pMenu->EnableMenuItem(uID, MF_ENABLED);
		}

		// ѡ�мҳ�ģʽ
		pMenu->CheckMenuItem(ID_TRAYMENU_MODEL_PARENTS, MF_CHECKED);
		pMenu->CheckMenuItem(ID_TRAYMENU_MODEL_CHILDREN, MF_UNCHECKED);
	} else {
		// ����ں���ģʽ�£��ܶఴť��������
		for (UINT i = 0; i < pMenu->GetMenuItemCount(); ++i) {
			const UINT uID = pMenu->GetMenuItemID(i);
			if (uID == ID_TRAYMENU_MAINUI ||
				uID == ID_TRAYMENU_LOCKCOMPUTER || 
				uID == ID_TRAYMENU_WEBHISTORY ||
				uID == ID_TRAYMENU_DESKTOPIMAGE) {
					pMenu->EnableMenuItem(uID, MF_GRAYED);
				}
		}

		pMenu->CheckMenuItem(ID_TRAYMENU_MODEL_PARENTS, MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_TRAYMENU_MODEL_CHILDREN, MF_CHECKED);

		// ���⻹Ҫ�������Ի���
		HideMainUI();
	}
}

// �������̵�ͼ��
void CMainUIDlg::setupTrayMenu() {
	// system Tray
	m_trayMenu.LoadMenu(IDC_MENU_TRAY_PARENT);
	m_sysTray.Create(this,10200, CALLMESSAGE, AfxGetApp()->LoadIcon(IDR_MAINFRAME),_T("Hola"));
	m_sysTray.SetSysMenu(&m_trayMenu);
}

BOOL CMainUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ����һ�����ԣ�һ���û��ڿ����³���ʱ��Ӧ
	// ͨ����ȡ�����ԣ������жϳ����Ƿ��Ѿ�����
	SetProp(this->GetSafeHwnd(), MAIN_WINDOW_PROP_NAME, (HWND)MAIN_WINDOW_PROP_VALUE);

	// ��������
	setControlsFonts();

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	initDlgs();
	InitTreeNodes();

	setupTrayMenu();

	SetTimer(ID_TIMER, TIME_ESCPSE, NULL);
	HideMainUI();
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}


void CMainUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
		CAboutDlg dlgAbout;
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
			// �����ǰģʽ����parent mode, �����Ի���
			// ʹ�û���������
			CDlgCheckPassword dlg;
			if (IDOK == dlg.DoModal()) {
				strMenuItem.LoadString(IDS_TRAYMENU_SHOWUI);
				ShowMainUI();
			}
		} else {
			// ����û���parent model,��ֱ�ӵ����Ի���
			strMenuItem.LoadString(IDS_TRAYMENU_SHOWUI);
			ShowMainUI();
		}
	}
}

// �Ƴ���ť
void CMainUIDlg::OnMainExit() {
	::SetWindowPos(GetSafeHwnd(), HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	CDialog::OnOK();
}

void CMainUIDlg::OnMainChangepassword()
{
	CDlgChangePassword dlg; 
	dlg.DoModal();
}

//====================================
// ģʽ�л�
void CMainUIDlg::OnMainParents()
{
	if (Services::isParentModel() == false) {
		CDlgCheckPassword dlg;
		if (IDOK == dlg.DoModal()) {
			ShowMainUI();
		}
	} else {
		ShowMainUI();
	}
}
void CMainUIDlg::OnMainChildren()
{
	Services::switchChildModel();
}

// ��Ӧ�ȼ���Ϣ
LRESULT CMainUIDlg::OnHotKey(WPARAM wParam, LPARAM lParam) {
	int id = (int)wParam;
	if (id == HOTKEY_SHOW_MAINUI) {
		// �����������ģʽ�£� ����Ӧ
		if (Services::isParentModel() == false)
			return -1;
		if (isShown()) {
			HideMainUI();
		} else {
			ShowMainUI();
		}
	} else if (id == HOTKEY_SHOW_SWITCH_USER) {
		// ��������ڸ�ģʽ�£�ֱ�ӷ���
		if (Services::isParentModel() == true)
			return -1;

		CDlgCheckPassword dlg;
		if (IDOK == dlg.DoModal()) {
		} else {
			HideMainUI();
		}
	}

	return -1;
}


// �������ߴ���
// ֱ�����г��򼴿̣�����Ӧ���ܹ��Լ���֤����
void CMainUIDlg::OnToolsDesktopimage() {
	TCHAR images[MAX_PATH];
	GetScreenRecordPath(images, MAX_PATH, (HMODULE)AfxGetInstanceHandle());

	CDlgImageBrowser dlg;
	dlg.setImageDir(images);
	dlg.DoModal();
}

void CMainUIDlg::OnToolsWebhistory() {
	TCHAR webimages[MAX_PATH], installpath[MAX_PATH];
	GetInstallPath(installpath, MAX_PATH, (HMODULE)AfxGetInstanceHandle());
	GetImageDirectory(webimages, MAX_PATH, installpath);
	ShellExecute(NULL, TEXT("open"), NULL, NULL, webimages, SW_SHOWNORMAL);
}


// ��Ӧ��ť
void CMainUIDlg::OnOK() {
	HideMainUI();
}

void CMainUIDlg::OnCancel() {
	HideMainUI();
}

void CMainUIDlg::OnBnClickedOk()
{
	ASSERT (NULL != m_curDlg);
	if ( -1 == m_curDlg->Apply()) {
		m_curDlg->Restore();
		return;
	}
	
	m_curDlg->SetModify(false);
	HideMainUI();
}

void CMainUIDlg::OnBnClickedMainCancel()
{
	HideMainUI();	// ���ش���
	m_curDlg->Restore();	// �ָ�����
	m_curDlg->SetModify(false);
}

// ����Apply��ť
void CMainUIDlg::OnBnClickedApply()
{
	ASSERT (NULL != m_curDlg);
	if ( -1 == m_curDlg->Apply()) {
		m_curDlg->Restore();
		return;
	}

	m_curDlg->SetModify(false);
}

// ���ÿؼ�������
void CMainUIDlg::setControlsFonts() {
	LOGFONT lf;  
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 14; 
	lf.lfWeight = FW_LIGHT;
	strcpy(lf.lfFaceName, "����");
	m_fontTree.CreateFontIndirect(&lf); 
	GetDlgItem(IDC_TREE_NAVIG)->SetFont(&m_fontTree);

	memset(&lf, 0, sizeof(LOGFONT));
	strcpy(lf.lfFaceName, "����");
	lf.lfWeight = FW_BOLD;
	lf.lfHeight = 18;
	m_fontTitle.CreateFontIndirect(&lf); 
	GetDlgItem(IDC_RIGHT_TITLE)->SetFont(&m_fontTitle);
}

//==============================================
// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMainUIDlg::OnPaint() 
{
	if (IsIconic()) {
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CMainUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CMainUIDlg::OnMainLockcomputer() {
	// ���������
	LockComputer((HMODULE)AfxGetInstanceHandle());
}

//===================================================
// �����ӶԻ���
void CMainUIDlg::InitTreeNodes() {
	// m_treeNavigation.DeleteAllItems();

	CString strRoot;
	strRoot.LoadString(IDS_TREE_ROOT);

	HTREEITEM hRoot = m_treeNavigation.InsertItem(strRoot, TVI_ROOT, TVI_LAST);
	m_treeNavigation.SetItemData(hRoot, -1);

	setRulesDlg();

	setToolsDlg();

	HTREEITEM hItem;
	CString strItem;
	// ����Ի���
	strItem.LoadString(IDS_TREE_OPTIONS);
	hItem = m_treeNavigation.InsertItem(strItem, hRoot);
	m_treeNavigation.SetItemData(hItem, IDS_TREE_OPTIONS);

	//strItem.LoadString(IDS_TREE_HELP);
	//hItem = m_treeNavigation.InsertItem(strItem, hRoot);
	//m_treeNavigation.SetItemData(hItem, IDS_TREE_HELP);

	strItem.LoadString(IDS_TREE_ABOUT);
	hItem = m_treeNavigation.InsertItem(strItem, hRoot);
	m_treeNavigation.SetItemData(hItem, IDS_TREE_ABOUT);


	m_treeNavigation.Expand(hRoot, TVE_EXPAND);
}

void CMainUIDlg::showDlg() {
	CRect rect;
	CWnd * pWndLeft = GetDlgItem(IDC_POSITION_RIGHT);
	pWndLeft->GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_curDlg->SetWindowPos(&wndTop, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
	m_curDlg->OnShow();
}

// �����Ի���
void CMainUIDlg::initDlgs() {
	m_dlgImageRules.Create(CDlgImageRule::IDD, this);
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
	m_curDlg = &m_lev1Rules;
	
	showDlg();
}

void CMainUIDlg::setToolsDlg() {
	CString strItem;
	strItem.LoadString(IDS_TREE_LEV1_TOOLS);
	HTREEITEM hItemTools = m_treeNavigation.InsertItem(strItem, m_treeNavigation.GetRootItem());
	m_treeNavigation.SetItemData(hItemTools, IDS_TREE_LEV1_RULES);

	HTREEITEM hItem;
	strItem.LoadString(IDS_TREE_EYECARE);
	hItem = m_treeNavigation.InsertItem(strItem, hItemTools);
	m_treeNavigation.SetItemData(hItem, IDS_TREE_EYECARE);

	strItem.LoadString(IDS_TREE_SCREEN_SAVE);
	hItem = m_treeNavigation.InsertItem(strItem, hItemTools);
	m_treeNavigation.SetItemData(hItem, IDS_TREE_SCREEN_SAVE);

	strItem.LoadString(IDS_TREE_ONLINE_HOUR);
	hItem = m_treeNavigation.InsertItem(strItem, hItemTools);
	m_treeNavigation.SetItemData(hItem, IDS_TREE_ONLINE_HOUR);
}

void CMainUIDlg::setRulesDlg() {
	CString strItem;
	strItem.LoadString(IDS_TREE_LEV1_RULES);
	HTREEITEM hItemRules = m_treeNavigation.InsertItem(strItem, m_treeNavigation.GetRootItem());
	m_treeNavigation.SetItemData(hItemRules, IDS_TREE_LEV1_RULES);

	HTREEITEM hItem;
	strItem.LoadString(IDS_TREE_IMAGE_RULE);
	hItem = m_treeNavigation.InsertItem(strItem, hItemRules);
	m_treeNavigation.SetItemData(hItem, IDS_TREE_IMAGE_RULE);

	strItem.LoadString(IDS_DNS_WHITE_LIST); 
	hItem = m_treeNavigation.InsertItem(strItem, hItemRules);
	m_treeNavigation.SetItemData(hItem, IDS_DNS_WHITE_LIST);
	

	strItem.LoadString(IDS_TREE_DNS_RULE); 
	hItem = m_treeNavigation.InsertItem(strItem, hItemRules);
	m_treeNavigation.SetItemData(hItem, IDS_TREE_DNS_RULE);
	setCurDlg(IDS_TREE_DNS_RULE);

	strItem.LoadString(IDS_TREE_SEARCH_RULE); 
	hItem = m_treeNavigation.InsertItem(strItem, hItemRules);
	m_treeNavigation.SetItemData(hItem, IDS_TREE_SEARCH_RULE);

	strItem.LoadString(IDS_TREE_WEB_HISTORY);
	hItem = m_treeNavigation.InsertItem(strItem, hItemRules);
	m_treeNavigation.SetItemData(hItem, IDS_TREE_WEB_HISTORY);

	m_treeNavigation.SelectItem(hItemRules);
}


void CMainUIDlg::ChangeCurDlg(CBaseDlg *dlg) {
	if (m_curDlg != dlg) {
		m_curDlg = dlg;
	}
}

// ���õ�ǰ��ʾ�ĶԻ���
void CMainUIDlg::setCurDlg(const DWORD item) {
	if (item == -1)  // ����Ǹ��ڵ�
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
		case IDS_TREE_IMAGE_RULE:
			ChangeCurDlg(&m_dlgImageRules);
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
		//case IDS_TREE_HELP:
		//	ChangeCurDlg(&m_dlgHelp);
		//	break;
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

	// ���ȵ���
	if (m_curDlg->BeforeChange() == 1) {
		setCurDlg(itemData);
		m_curDlg->AfterChange();
	} else {
		m_curDlg->Restore();
		m_curDlg->SetModify(false);
	}

	*pResult = 0;
}


// ע���ȼ�
void CMainUIDlg::OnDestroy()
{
	UnregisterHotKey(this->GetSafeHwnd(), HOTKEY_SHOW_MAINUI);
	UnregisterHotKey(this->GetSafeHwnd(), HOTKEY_SHOW_SWITCH_USER);
	CDialog::OnDestroy();
}

void CMainUIDlg::ShowMainUI() {
	ShowWindow(SW_SHOW);
	::SetWindowPos(GetSafeHwnd(), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	m_bShown = TRUE;
}
void CMainUIDlg::HideMainUI() {
	ShowWindow(SW_HIDE);
	::SetWindowPos(GetSafeHwnd(), HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	m_bShown = FALSE;
}


void CMainUIDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	UpdateUIStateByModel();
	CDialog::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
}


void CMainUIDlg::OnTimer(UINT nIDEvent)
{
	// �Ƿ�����״̬������������ش���
	if (isShown() &&Services::isParentModel() == false) {
		HideMainUI();
	}
	CDialog::OnTimer(nIDEvent);
}
