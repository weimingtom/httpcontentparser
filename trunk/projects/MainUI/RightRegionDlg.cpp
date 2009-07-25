// RightRegionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mainui.h"
#include "RightRegionDlg.h"
#include ".\rightregiondlg.h"
#include ".\globalvariable.h"
#include <app_constants.h>
#include <softwarestatus.h>
#include <apputility\apputility.h>
#include <comdef.h>
#include <logger\logger.h>

#define RIGTH_TOP_FONT_NAME			TEXT("MS Shell Dlg")

// CRightRegionDlg 对话框

IMPLEMENT_DYNAMIC(CRightRegionDlg, CDialog)
CRightRegionDlg::CRightRegionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRightRegionDlg::IDD, pParent)
{
	m_pParentDlg = NULL;
	m_pImageList = NULL;
	m_idIcon = 0;
}

CRightRegionDlg::~CRightRegionDlg()
{
}

void CRightRegionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRightRegionDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

INT_PTR CRightRegionDlg::initialize(CImageList	*pImageList, CDialog *pParent) {
	ASSERT (NULL != pParent);
	ASSERT(NULL != pImageList); 
	m_pImageList = pImageList;
	m_pParentDlg = pParent;

	this->Create(CRightRegionDlg::IDD, pParent);

	CRect rect;
	CWnd * pWndRight = pParent->GetDlgItem(IDC_STA_FRAME);
	pWndRight->GetWindowRect(&rect);
	ScreenToClient(&rect);
	this->SetWindowPos(&wndTop, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);

	initDlgs();
	setControlsFonts();

	return 0;
}


// CRightRegionDlg 消息处理程序
INT_PTR CRightRegionDlg::OnCancelChange() {
	ASSERT (NULL != m_curDlg);
	m_curDlg->Restore();	// 恢复设置
	m_curDlg->SetModify(false);
	return SUCCESS_ON_APPLY;
}

INT_PTR CRightRegionDlg::OnChangeDlgPage(const INT_PTR itemData) {
	INT_PTR dlgpage = getItemIDS(itemData);
	if (m_curDlg->BeforeChange() == 1) {
		// 如果用户确认修改
		setCurDlg(dlgpage);
		m_curDlg->AfterChange();
		m_idIcon = getItemIcon(itemData);
	} else {
		// 用户取消修改
		m_curDlg->Restore();
		m_curDlg->SetModify(false);
	}
	return SUCCESS_ON_APPLY;
}

INT_PTR CRightRegionDlg::OnApplyChange() {
	ASSERT (NULL != m_curDlg);
	if ( -1 == m_curDlg->Apply()) {
		m_curDlg->Restore();					// 回复设置
		m_curDlg->SetModify(false);	// 是OK, app按钮不可用
		// TODO 给出提示
		return FAILED_ON_APPLY;
	} else {
		m_curDlg->SetModify(false);
		return SUCCESS_ON_APPLY;
	}
}

void CRightRegionDlg::setControlsFonts() {
	LOGFONT lf;  
	memset(&lf, 0, sizeof(LOGFONT));
	strcpy(lf.lfFaceName, RIGTH_TOP_FONT_NAME);
	lf.lfWeight = FW_BOLD;
	lf.lfHeight = 18;
	m_fontTitle.CreateFontIndirect(&lf); 
	GetDlgItem(IDC_PAGE_TITLE)->SetFont(&m_fontTitle);
}

void CRightRegionDlg::drawRightIcon(CDC *pDC) {
	CRect rect;
	CWnd * iconPos = GetDlgItem(IDC_ICON_POS);
	iconPos->GetWindowRect(&rect);
	ScreenToClient(&rect);
	CPoint pt(rect.left, rect.top);
	if (NULL != m_pImageList && m_pImageList->GetImageCount() > m_idIcon) {
		m_pImageList->Draw(pDC, m_idIcon, pt, ILD_NORMAL);
	}
}

void CRightRegionDlg::showDlg() {
	try {
		CRect rect;
		CWnd * pWndLeft = GetDlgItem(IDC_POS_SUBPAGE);
		pWndLeft->GetWindowRect(&rect);
		ScreenToClient(&rect);
		m_curDlg->SetWindowPos(&wndTop, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
		m_curDlg->OnShow();
	} catch (...) {
		__LERR__("FAILED On create HistoryRecord");
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONEXCLAMATION);
	}
}

void CRightRegionDlg::ChangeCurDlg(CBaseDlg *dlg) {
	if (m_curDlg != dlg) {
		m_curDlg = dlg;
	}
}

// 设置当前显示的对话框
void CRightRegionDlg::setCurDlg(const DWORD item) {
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

	setRightTitle(item);

	showDlg();
}

// 创建对话框
void CRightRegionDlg::initDlgs() {
	try {
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
		__LERR__("FAILED On create HistoryRecord");
		AfxMessageBox(IDS_COM_ERRO_COCREATE_FIALED, MB_OK | MB_ICONEXCLAMATION);
		EndDialog(IDCANCEL);
	}
}

void CRightRegionDlg::setRightTitle(const INT_PTR item) {
	CRect rect;
	CWnd * pos = this->GetDlgItem(IDC_PAGE_ICON_POS);
	if (pos != NULL) {
		pos->GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect.InflateRect(5, 5, 5, 5);
		InvalidateRect(&rect, TRUE);
	}

	//设置右侧标题
	CString strItem;
	strItem.LoadString(item);
	GetDlgItem(IDC_PAGE_TITLE)->SetWindowText(strItem);
}

BOOL CRightRegionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CRightRegionDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	drawRightIcon(&dc);
}

WORD CRightRegionDlg::getItemIcon(DWORD data) {
	return HIWORD(data);
}
WORD CRightRegionDlg::getItemIDS(DWORD data) {
	return LOWORD(data);
}
HBRUSH CRightRegionDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
	//pDC->SetBkMode(TRANSPARENT);
 //   return ::GetSysColorBrush( COLOR_WINDOW );
}
