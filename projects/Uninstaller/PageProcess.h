#ifndef _UNINSTALL_PROCESS_H__
#define _UNINSTALL_PROCESS_H__


// CPageProcess �Ի���

class CPageProcess : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageProcess)

public:
	CPageProcess();
	virtual ~CPageProcess();

// �Ի�������
	enum { IDD = IDD_PAGE_PROCESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};

#endif  // _UNINSTALL_PROCESS_H__