#pragma once


// CDlgReboot �Ի���

class CDlgReboot : public CDialog
{
	DECLARE_DYNAMIC(CDlgReboot)

public:
	CDlgReboot(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgReboot();

	virtual BOOL OnInitDialog();
// �Ի�������
	enum { IDD = IDD_DLG_REBOOT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedFinish();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

private:
	COLORREF m_bkColor;
	HBRUSH	  m_bkBrush;
	HICON m_hIcon;
	int m_bRestart;
};
