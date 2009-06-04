#ifndef _UNINSTALL_REBOOT_H__
#define _UNINSTALL_REBOOT_H__


// CPageReboot 对话框

class CPageReboot : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageReboot)

public:
	CPageReboot();
	virtual ~CPageReboot();

// 对话框数据
	enum { IDD = IDD_PAGE_REBOOT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};

#endif  // _UNINSTALL_REBOOT_H__