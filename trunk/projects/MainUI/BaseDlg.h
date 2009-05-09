#pragma once
#include "afxwin.h"
#include <string>

#define SUCCESS_APPLY	0
#define FAILED_APPLY		-1

class CBaseDlg : public CDialog {
public:
	CBaseDlg(UINT uTemplate, CWnd *pParent);
	~CBaseDlg(void);

	// 在改变对话框之前应该调用此函数
	virtual int  BeforeChange();
	int  AfterChange();
	
	virtual std::string getHelpLink() const = 0;

	// 确定对话框数据是否有改变
	bool Modified() {
		return changed_;
	}

	// 恢复设置
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
