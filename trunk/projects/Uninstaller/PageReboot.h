#ifndef _UNINSTALL_REBOOT_H__
#define _UNINSTALL_REBOOT_H__


// CPageReboot �Ի���

class CPageReboot : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageReboot)

public:
	CPageReboot();
	virtual ~CPageReboot();

// �Ի�������
	enum { IDD = IDD_PAGE_REBOOT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};

#endif  // _UNINSTALL_REBOOT_H__