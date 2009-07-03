#ifndef _MAINUI_CDLGPROGRAMCONTROL_H__
#define _MAINUI_CDLGPROGRAMCONTROL_H__

// CDlgProgramControl �Ի���

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
	CDlgProgramControl(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgProgramControl();

	virtual std::string getHelpLink() const;

// �Ի�������
	enum { IDD = IDD_DLG_PROGRAM };

public:
	virtual int OnApply();
	virtual void OnShow();
	virtual void restoreSetting();

	int addNewFile(const CFileInfo &fileinfo);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnSet();
	afx_msg void OnBnClickedChkEnableAppcontrol();
	virtual BOOL OnInitDialog();

	// ������ʾ
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

	// ��·����Ӧ������
	typedef std::map<strutility::_tstring, ITEMDATA*> DATA_MAP;
	DATA_MAP	listdata_;
	// �Ƴ���·��path��ص�����
	void removeItemData(const CString &path);
	
	// �ȴ���ɾ��������ȴ�����ӵ���
	// key������Ǳ�ɾ�����·��, ��value�Ǳ����ԭ�����ڵ�list������
	// �������������
	// �����κ�һ���û�Ҫɾ��������ȴ�addedItems��ɾ��, Ȼ����ӵ�deleteItems.
	// �����κ�һ���û�Ҫ��ӵ�����ȴ�deleteItems��ɾ����Ȼ����ӵ�addedItems����
	// ���û�ִ�в�����ʱ�򣬽�����addedItems�е��������ӣ�
	// ����delete�е���ɾ��
	typedef std::map<strutility::_tstring, int> MODIFY_ITEMS;
	MODIFY_ITEMS  deleteItems_;
	MODIFY_ITEMS addedItems_;

protected:
	void addItem(const std::string &filepath, const int iIndex);
	void deleteItem(const std::string &filepath, const int iIndex);

	void deleteJustFromUI(const int iIndex);

	//  ִ��ɾ�������
	void executeDelete(IAppControl *pSetting);
	void executeAdd(IAppControl *pSetting);


	BOOL m_bEnableAppControl;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};



#endif  // _MAINUI_CDLGPROGRAMCONTROL_H__