#pragma once
#include "afxwin.h"

class CBaseDlg : public CDialog {
public:
	CBaseDlg(UINT uTemplate, CWnd *pParent);
	~CBaseDlg(void);

	// �ڸı�Ի���֮ǰӦ�õ��ô˺���
	virtual int  BeforeChange();
	int  AfterChange();
	

	// ȷ���Ի��������Ƿ��иı�
	bool Modified() {
		return changed_;
	}

	// �ָ�����
	void Restore();
	void Apply();
	virtual void OnShow() = 0;

protected:
	virtual int OnApply() = 0;
	virtual int restoreSetting() = 0;
	void OnOK() {}
public:
	void SetModify(const bool changed);

private:
	bool changed_;
	CBaseDlg() {changed_ = false;}
};
