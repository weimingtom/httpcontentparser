#pragma once
#include "afxwin.h"
#include <string>

#define SUCCESS_APPLY	0
#define FAILED_APPLY		-1

class CBaseDlg : public CDialog {
public:
	CBaseDlg(UINT uTemplate, CWnd *pParent);
	~CBaseDlg(void);

	// �ڸı�Ի���֮ǰӦ�õ��ô˺���
	virtual INT_PTR  BeforeChange();
	INT_PTR  AfterChange();
	
	virtual std::string getHelpLink() const = 0;

	// ȷ���Ի��������Ƿ��иı�
	bool Modified() {
		return changed_;
	}

	// �ָ�����
	INT_PTR Restore();
	INT_PTR Apply();
	virtual void OnShow() = 0;

protected:
	virtual INT_PTR OnApply() = 0;
	virtual void restoreSetting() = 0;
	void OnOK() {}

	virtual void OnCancel() {}

public:
	void SetModify(const bool changed);

private:
	bool changed_;
	CBaseDlg() {changed_ = false;}
protected:
	std::string auther_name_;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
