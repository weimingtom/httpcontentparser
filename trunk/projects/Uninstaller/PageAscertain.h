#ifndef _UNINSTALL_ASCERTAIN_H__
#define _UNINSTALL_ASCERTAIN_H__

// CPageAscertain �Ի���

class CPageAscertain : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageAscertain)

public:
	CPageAscertain();
	virtual ~CPageAscertain();

// �Ի�������
	enum { IDD = IDD_PAGE_ASCERTAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};

#endif  // _UNINSTALL_ASCERTAIN_H__
