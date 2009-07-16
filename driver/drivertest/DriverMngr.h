#ifndef _APPCONTROLLER_H__
#define _APPCONTROLLER_H__

#include <string>
#include <driver_const.h>


class CheckProcessCreate {
public:
	virtual bool enable_process_create(const char * process_path_name) = 0;
};

class AppController {
	class ExchangeBuffer;
public:
	AppController(CheckProcessCreate * checker) ;
	~AppController();

	// 安装驱动

public:
	int begin();
	int end();

protected:
	int InstallDriver();
	int UninstallDriver();
	
	int InstallService();
	int DeleteService();
public:
	int checkpassed(const char * filename);
	int checkpassed();

	// 是否退出线程
	bool exitThread() const { return exit_thread_;}

	ExchangeBuffer * get_exchange_buffer() {
		return &exchange_buffer_;
	}

private:
	HANDLE m_hDevice;
	DWORD dwThreadId;
	friend DWORD CALLBACK CheckAppProc(LPVOID param);

	volatile int exit_thread_;

	CheckProcessCreate * checker_;

	// 控制交换缓冲区
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
		char exchange_buffer[EXCHANGE_BUFFER_SIZE];
	};

	ExchangeBuffer exchange_buffer_;

protected:
	AppController();
	AppController(const AppController &);
};

#endif  // _APPCONTROLLER_H__
