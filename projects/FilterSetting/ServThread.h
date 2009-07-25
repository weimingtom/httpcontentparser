#ifndef _FILTER_SETTING_H__
#define _FILTER_SETTING_H__

// ȫ�̷����̣߳� ��hotkey�� ��ʱ��

class ServThread {
public:
	~ServThread(void);

// ���䲿��
	static ServThread * getInstance();
private:
	static ServThread *pInstance;
public:
	HANDLE getThreadHandle()  { return hThread_;}
	INT_PTR   setHotKey(WORD vKey, WORD key, INT_PTR type);
private:
	void startServer();
	static DWORD_PTR TreadProc(LPVOID param);
	ServThread(void);

	DWORD_PTR dwThreadId_;
	HANDLE hThread_;
	HWND  hwnd_;

	DWORD_PTR m_tickAutoSave;	// �Զ�������Ļ��ʱ����
	DWORD_PTR m_tickEyecare;	// ���������۾���ʱ����

	// hotkey ids;
	void initialize();
	friend LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif  // _FILTER_SETTING_H__