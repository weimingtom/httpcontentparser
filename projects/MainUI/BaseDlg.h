#pragma once
#include "afxwin.h"

class CBaseDlg : public CDialog {
public:
	CBaseDlg(UINT uTemplate, CWnd *pParent);
	~CBaseDlg(void);

	// �ڸı�Ի���֮ǰӦ�õ��ô˺���
	virtual int  BeforeChange();

	// ȷ���Ի��������Ƿ��иı�
	bool Modified() {
		return changed_;
	}

	// �ָ�����
	virtual void OnRestore() = 0;
	virtual void OnApply() = 0;
	virtual void OnShow() = 0;
	void OnOK() {}
private:

	void SetModify(const bool changed) {
		changed_ = changed;
	}

	bool changed_;
	CBaseDlg() {changed_ = false;}
};
