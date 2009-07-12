#ifndef _APPCONTROLLER_H__
#define _APPCONTROLLER_H__

#include <string>



class AppController {
	class ExchangeBuffer;
public:
	AppController() {
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

public:
	int checkpassed(const char * filename);
	int checkpassed();

	// 是否退出线程
	bool exitThread() const { return exit_thread_;}

	ExchangeBuffer * get_exchange_buffer() {
		return &exchange_buffer_;
	}
private:
	HANDLE device;
	DWORD dwThreadId;
	
	const static int IO_CONTROL_BUFFER_INIT = 1000;
	friend DWORD CALLBACK CheckAppProc(LPVOID param);

	volatile int exit_thread_;

	class ExchangeBuffer {
	public:
		ExchangeBuffer();
		bool need_check();
		std::string get_filepath() ;
		void set_check_result(const bool passed);

		char * get_buffer_addr() {
			return exchange_buffer;
		}

		void reset_status();
	private:
		char exchange_buffer[MAX_PATH * 2];
	};

	ExchangeBuffer exchange_buffer_;
};

#endif  // _APPCONTROLLER_H__
