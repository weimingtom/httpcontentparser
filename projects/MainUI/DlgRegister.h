#ifndef _MAINUI_CDLGREGISTER_H__
#define _MAINUI_CDLGREGISTER_H__

// CDlgRegister �Ի���

class CDlgRegister : public CDialog
{
	DECLARE_DYNAMIC(CDlgRegister)

public:
	CDlgRegister(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgRegister();

// �Ի�������
	enum { IDD = IDD_DLG_REGISTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	DECLARE_MESSAGE_MAP()
};

#endif  // _MAINUI_CDLGREGISTER_H__