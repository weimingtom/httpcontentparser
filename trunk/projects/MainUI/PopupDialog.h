#ifndef _MAINUI_CPOPUPDIALOG_H__
#define _MAINUI_CPOPUPDIALOG_H__

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