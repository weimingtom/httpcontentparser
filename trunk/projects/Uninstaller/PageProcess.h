#ifndef _UNINSTALL_PROCESS_H__
#define _UNINSTALL_PROCESS_H__


// CPageProcess 对话框

class CPageProcess : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageProcess)

public:
	CPageProcess();
	virtual ~CPageProcess();

// 对话框数据
	enum { IDD = IDD_PAGE_PROCESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};

#endif  // _UNINSTALL_PROCESS_H__