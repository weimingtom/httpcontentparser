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
	INT_PTR   setHotKey(WORD vKey, WORD key, INT_PTR type);
private:
	void startServer();
	static DWORD_PTR TreadProc(LPVOID param);
	ServThread(void);

	DWORD_PTR dwThreadId_;
	HANDLE hThread_;
	HWND  hwnd_;

	DWORD_PTR m_tickAutoSave;	// 自动保存屏幕的时间间隔
	DWORD_PTR m_tickEyecare;	// 启动保护眼睛的时间间隔

	// hotkey ids;
	void initialize();
	friend LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif  // _FILTER_SETTING_H__