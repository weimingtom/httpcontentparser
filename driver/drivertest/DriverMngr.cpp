#include "stdafx.h"
#include ".\DriverMngr.h"
#include "ErrorCode.h"
#include <DebugOutput.h>
#include <driver_const.h>
#include <assert.h>
#include <string>

#define  APPCONTROL_SERVICE				TEXT("protectorservice")
#define  APPCONTROL_FILE						TEXT("\\\\.\\PROTECTOR")
#define  APPCONTROL_DRIVER_FILE		TEXT("protector.sys")

//=============================
// 构造函数与析构函数
AppController::AppController(CheckProcessCreate * checker) : checker_(checker) {
	dwThreadId = 0;
	exit_thread_ = 0;
	assert (checker != NULL);
}
AppController::~AppController() {
}

int AppController::InstallDriver()
{
	int rc = 0;
	_DEBUG_STREAM_TRC_("[DriverMngr]Install Driver");
	// 在当前路径下获取DRIVER的路径
	// 获取驱动程序的路径
	char namebuff[MAX_PATH]; 
	GetModuleFileName(NULL, namebuff, MAX_PATH);
	DWORD  a=strlen(namebuff);
	while(1)
	{
		if(namebuff[a]=='\\')break;
		a--;
	}
	a++;
	strcpy(&namebuff[a], APPCONTROL_DRIVER_FILE);

	// 注册服务
	//create service
	SC_HANDLE serverMan=OpenSCManager(0,0,SC_MANAGER_ALL_ACCESS);
	if (NULL == serverMan) {
		rc =Family007::ErrorCode::ERROR_OPEN_SCMGR_FAILED;
		REPORT_FATAL_ERROR_WITH_ERRNO(rc, "OpenSCManager", 
			"OpenSCManager() to open a SCManager", __FUNCTION__);
		_DEBUG_STREAM_TRC_("[DriverMngr]OpenSCManager failed Windows Error : "<<GetLastError());
		goto exit;
	}

	SC_HANDLE service_handle=CreateService(serverMan, APPCONTROL_SERVICE, 
					APPCONTROL_SERVICE,
					SERVICE_START | SERVICE_STOP,   SERVICE_KERNEL_DRIVER, 
					SERVICE_DEMAND_START,    SERVICE_ERROR_NORMAL,
					namebuff, 0, 0, 0, 0, 0);
	if (NULL == service_handle) {
		rc = Family007::ErrorCode::ERROR_CREATE_SERVICE_FAILED;
		REPORT_FATAL_ERROR_WITH_ERRNO(rc, "CreateService", 
			"CreateService() failed", __FUNCTION__);
		_DEBUG_STREAM_TRC_("[DriverMngr]CreateService failed Windows Error : "<<GetLastError());
		goto exit;
	}

	BOOL result = StartService(service_handle,0,0);
	if (!result) {
		rc = Family007::ErrorCode::ERROR_START_SERVICE_FAILED;
		REPORT_FATAL_ERROR_WITH_ERRNO(rc, "StartService", 
			"StartService() failed", __FUNCTION__);
		_DEBUG_STREAM_TRC_("[DriverMngr]StartService failed Windows Error : "<<GetLastError());
		goto exit;
	}
	CloseServiceHandle(service_handle);

	_DEBUG_STREAM_TRC_("[DriverMngr]install service %s"<<namebuff);

exit:
	return rc;
}

int AppController::UninstallDriver()
{
	_DEBUG_STREAM_TRC_("[DriverMngr]Uninstall Driver");

	int rc = 0;

	SC_HANDLE serverMan=OpenSCManager(0,0,SC_MANAGER_ALL_ACCESS);
	if (NULL == serverMan) {
		rc =Family007::ErrorCode::ERROR_OPEN_SCMGR_FAILED;
		REPORT_FATAL_ERROR_WITH_ERRNO(rc, "OpenSCManager", 
			"OpenSCManager() to open a SCManager", __FUNCTION__);
		_DEBUG_STREAM_TRC_("[DriverMngr]OpenSCManager failed Windows Error : "<<GetLastError());
		goto exit;
	}

	SERVICE_STATUS stat;
	SC_HANDLE servHandle=OpenService(serverMan, APPCONTROL_SERVICE, SERVICE_ALL_ACCESS);
	if (NULL == serverMan) {
		rc =Family007::ErrorCode::ERROR_OPEN_SERVICE_FAILED;
		REPORT_FATAL_ERROR_WITH_ERRNO(rc, "OpenService", 
			"OpenService() to open a SCManager", __FUNCTION__);
		_DEBUG_STREAM_TRC_("[DriverMngr]OpenService failed Windows Error : "<<GetLastError());
		goto exit;
	}

	ControlService(servHandle,SERVICE_CONTROL_STOP,&stat);   
	DeleteService(servHandle);

exit:
	return rc;
}


int  AppController::begin()
{
	int rc = 0;
	// 避免错误，先卸载再加载
	InstallDriver(); 

	//create processing thread
	HANDLE hThread = CreateThread(NULL, 0, 
		(LPTHREAD_START_ROUTINE)CheckAppProc,
		(LPVOID)this, 0, &dwThreadId);


	// open device
	device=CreateFile(APPCONTROL_FILE,GENERIC_READ | GENERIC_WRITE, 0, 0, 
		OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, 0);
	if (INVALID_HANDLE_VALUE == device) {
		using Family007::ErrorCode;
		rc = ErrorCode::ERROR_OPEN_DEVICE_FAILED;
		Family007::ErrorCode::reportError(rc, ErrorCode::ERROR_LEVEL_FATAL, 
			"CreateFile()", 
			"CreateFile() to open a device to load appcontrol driver failed",
			GetLastError(),
			__FUNCTION__);

		_DEBUG_STREAM_TRC_("[DriverMngr]CreateFile failed Windows Error : "<<GetLastError());

		goto exit;
	}

	// 获取系统路径
	char SYSTEM_DIR[MAX_PATH];
	GetSystemDirectory(SYSTEM_DIR, MAX_PATH);

	// 初始化缓冲区
	DWORD dw;
	DWORD buffer_init[64];
	// TODO:不能兼容64为
	DWORD * addr=(DWORD *)(1+(DWORD)GetProcAddress(GetModuleHandle("ntdll.dll"),"NtCreateSection"));  
	ZeroMemory(buffer_init,sizeof(buffer_init));
                          
	buffer_init[0] = addr[0];                                                                              // 传入函数NtCreateSection的路径
	buffer_init[1] = (DWORD)exchange_buffer_.get_buffer_addr();         // 传入交换缓冲区的内容
	buffer_init[2] = (DWORD)&SYSTEM_DIR[0];                                          // 传入SystemDir
	DeviceIoControl(device,IO_CONTROL_BUFFER_INIT, buffer_init,512, buffer_init, 512, &dw, NULL);

exit:
	if (rc) {
	}
	return rc;
}

int AppController::end() {
	int rc = 0;

	// 卸载驱动程序
	UninstallDriver();

	// 结束线程
	exit_thread_ = 1;

	return rc;
}

int AppController::checkpassed(const char * filename) {
	int result = 1;
	_DEBUG_STREAM_TRC_("[DriverMngr]Do you want to run"<<exchange_buffer_.get_filepath());

	// 将结果写入内存
	assert (NULL != checker_);
	if (NULL != checker_) {
		result = checker_->enable_process_create(filename);
	}

	exchange_buffer_.set_check_result(result);

	return result;
}

int AppController::checkpassed() {
	return checkpassed(exchange_buffer_.get_filepath().c_str());
}

// ==========================================
// 线程
DWORD CALLBACK CheckAppProc(LPVOID param) {
	_DEBUG_STREAM_TRC_("[DriverMngr]Begin Thread Proc");
	AppController * controlloer = (AppController*)param;
	while(1)
	{
		//if nothing is there, Sleep() 10 ms and check again
		while( ! controlloer->get_exchange_buffer()->need_check()) {
			Sleep(50);
		}

		// if user's reply is positive, add the program to the white list
		int passed = controlloer->checkpassed();

		// 如果调用了end函数， 退出线程
		if (controlloer->exitThread()) {
			break;
		}
	}

	_DEBUG_STREAM_TRC_("[DriverMngr]End Thread Proc");

	return 0;
}

// =======================================
// 交换缓冲区类
AppController::ExchangeBuffer::ExchangeBuffer() {
	ZeroMemory(exchange_buffer, sizeof(exchange_buffer));
}

bool AppController::ExchangeBuffer::need_check() {
	int status;
	memmove(&status, &(exchange_buffer[ADDR_EXCHANGE_NOTIFY_APP]), 4);
	return status == 1;
}

std::string  AppController::ExchangeBuffer::get_filepath() {
	assert(need_check());
	return std::string(&(exchange_buffer[ADDR_EXCHANGE_FILEPATH]));
}

void AppController::ExchangeBuffer::set_check_result(const bool passed) {
	DWORD result = 1;
	if (passed) {
		result = 1;
	} else {
		result = 0;
	}
	
	memmove(&result, &(exchange_buffer[ADDR_EXCHANGE_APP_COMP]), 4);
}

void AppController::ExchangeBuffer::reset_status() {
}