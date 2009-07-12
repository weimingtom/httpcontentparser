#ifndef _APPCONTROLLER_H__
#define _APPCONTROLLER_H__

#include <string>


class CheckProcessCreate {
public:
	virtual bool enable_process_create(const char * process_path_name) = 0;
};

class AppController {
	class ExchangeBuffer;
public:
	AppController(CheckProcessCreate * checker) ;
	~AppController();

	// ��װ����

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

	// �Ƿ��˳��߳�
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

	CheckProcessCreate * checker_;

	// ���ƽ���������
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

protected:
	AppController();
	AppController(const AppController &);
};

#endif  // _APPCONTROLLER_H__