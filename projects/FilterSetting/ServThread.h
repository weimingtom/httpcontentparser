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
	void   setHotKey(WORD vKey, WORD key, int type);
private:
	void startServer();
	static DWORD TreadProc(LPVOID param);
	ServThread(void);

	DWORD dwThreadId_;
	HANDLE hThread_;
};

#endif  // _FILTER_SETTING_H__