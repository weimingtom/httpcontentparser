#ifndef _MAINUI_CPOPUPDIALOG_H__
#define _MAINUI_CPOPUPDIALOG_H__

// Ϊ�˷�ֹһ���Ի��򱻵�����ˣ����Ϊÿһ�������Ի����ṩ��һ������
// �˸���Ĺ����ǣ��ڵ���֮ǰ���ȼ��Ի����Ƿ��Ѿ��򿪣��������ֱ�Ӽ���
// ���򵯳��Ի���
// ע�⣺Ҫʹ������Ч���뱣֤���ε����Ի���ʹ�õ���һ������
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