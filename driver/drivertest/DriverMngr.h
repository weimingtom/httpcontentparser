

class AppController {
public:
	AppController() {
		ZeroMemory(exchange_buffer, sizeof(exchange_buffer));
		dwThreadId = 0;
		exit_thread_ = 0;
	}
	~AppController() {
		end();
	}

	// 安装驱动

public:
	int begin();
	int end();

protected:
	int InstallDriver();
	int UninstallDriver();
protected:
	int getState();
	char * getFilePath() {
		return &(exchange_buffer[8]);
	}

public:
	int checkpassed(const char * filename);
	int checkpassed();
	void resetState();

	// 是否退出线程
	bool exitThread() const { return exit_thread_;}
private:
	HANDLE device;
	DWORD dwThreadId;
	char exchange_buffer[MAX_PATH];
	const static int IO_CONTROL_BUFFER_INIT = 1000;
	friend DWORD CALLBACK CheckAppProc(LPVOID param);

	volatile int exit_thread_;
};
