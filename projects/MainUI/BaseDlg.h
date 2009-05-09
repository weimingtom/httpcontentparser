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
	virtual int  BeforeChange();
	int  AfterChange();
	
	virtual std::string getHelpLink() const = 0;

	// ȷ���Ի��������Ƿ��иı�
	bool Modified() {
		return changed_;
	}

	// �ָ�����
	int Restore();
	int Apply();
	virtual void OnShow() = 0;

protected:
	virtual int OnApply() = 0;
	virtual void restoreSetting() = 0;
	void OnOK() {}

	virtual void OnCancel() {}
public:
	void SetModify(const bool changed);

private:
	bool changed_;
	CBaseDlg() {changed_ = false;}
};
