#ifndef _FILTER_SETTING_H__
#define _FILTER_SETTING_H__

// 全程服务线程， 如hotkey， 定时等

class ServThread {
public:
	~ServThread(void);

// 单间部分
	static ServThread * getInstance();
private:
	static ServThread *pInstance;
public:
	HANDLE getThreadHandle()  { return hThread_;}
	int   setHotKey(WORD vKey, WORD key, int type);
private:
	void startServer();
	static DWORD TreadProc(LPVOID param);
	ServThread(void);

	DWORD dwThreadId_;
	HANDLE hThread_;
	HWND  hwnd_;

	DWORD m_tickAutoSave;	// 自动保存屏幕的时间间隔
	DWORD m_tickEyecare;	// 启动保护眼睛的时间间隔

	// hotkey ids;
	void initialize();
	friend LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif  // _FILTER_SETTING_H__