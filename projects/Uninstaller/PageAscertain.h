#ifndef _UNINSTALL_ASCERTAIN_H__
#define _UNINSTALL_ASCERTAIN_H__

// CPageAscertain 对话框

class CPageAscertain : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageAscertain)

public:
	CPageAscertain();
	virtual ~CPageAscertain();

// 对话框数据
	enum { IDD = IDD_PAGE_ASCERTAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};

#endif  // _UNINSTALL_ASCERTAIN_H__
