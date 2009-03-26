#ifndef _MAINUI_CPOPUPDIALOG_H__
#define _MAINUI_CPOPUPDIALOG_H__

// 为了防止一个对话框被弹出多此，因此为每一个弹出对话框提供了一个父类
// 此父类的功能是，在弹出之前首先检测对话框是否已经打开，如果打开则直接激活
// 否则弹出对话框
// 注意：要使此类生效必须保证两次弹出对话框使用的是一个变量
class CPopupDialog : public CDialog {
public:
	CPopupDialog(int, CWnd* pParent);
	~CPopupDialog(void);

public:
	virtual INT_PTR DoModal();

	bool isOpen() const { return m_bOpened_;}

private:
	bool m_bOpened_;
};

#endif  // _MAINUI_CPOPUPDIALOG_H__