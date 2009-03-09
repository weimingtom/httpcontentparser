#ifndef _MAINUI_CDLGPROGRAMCONTROL_H__
#define _MAINUI_CDLGPROGRAMCONTROL_H__

// CDlgProgramControl 对话框

#include ".\basedlg.h"
#include "afxcmn.h"
#include ".\ListView\ListViewCtrlEx.h"
#include ".\globalvariable.h"
#include <utility\strutility.h>
#include <fileinfo.h>
#include <string>
#include <map>
#include <set>

class CProgramList: public CListCtrlEx {
public:
	const CString GetToolTip(int, int, UINT nFlags, BOOL&);
};

class CDlgProgramControl : public CBaseDlg {
	DECLARE_DYNAMIC(CDlgProgramControl)

public:
	CDlgProgramControl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgProgramControl();

// 对话框数据
	enum { IDD = IDD_DLG_PROGRAM };

public:
	virtual int OnApply();
	virtual void OnShow();
	virtual void restoreSetting();

	int addNewFile(const CFileInfo &fileinfo);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnSet();
	virtual BOOL OnInitDialog();

	// 给出提示
	friend class CProgramList; 
protected:
	CProgramList m_list;
	CImageList	 m_imagelist;

	void resetContent();
	
protected:
	typedef struct _tagItemData {
		strutility::_tstring ProductName;
		strutility::_tstring CompanyName;
		strutility::_tstring Description;
		strutility::_tstring fullPath;

		struct _tagItemData(const TCHAR * name,  const TCHAR * companyName, const TCHAR *descript, const TCHAR * fullPath)
		{
			this->ProductName = name;
			this->CompanyName = companyName;
			this->Description= descript;
			this->fullPath= fullPath;
		}
	}ITEMDATA;

	typedef std::map<strutility::_tstring, ITEMDATA*> DATA_MAP;
	DATA_MAP	listdata_;
	// 移除已路径path相关的数据
	void removeItemData(const CString &path);
	
	// 等待被删除的项与等待被添加的项
	// key保存的是被删除项的路径, 而value是保存的原来所在的list的索引
	typedef std::map<strutility::_tstring, int> MODIFY_ITEMS;
	MODIFY_ITEMS  deleteItems_;
	MODIFY_ITEMS addedItems_;
protected:
	//  执行删除与添加
	void executeDelete(IAppControl *pSetting);
	void executeAdd(IAppControl *pSetting);
public:
	BOOL m_bEnableAppControl;
	afx_msg void OnBnClickedChkEnableAppcontrol();
};



#endif  // _MAINUI_CDLGPROGRAMCONTROL_H__