#include "stdafx.h"
#include ".\DriverMngr.h"
#include "ErrorCode.h"
#include <DebugOutput.h>
#include <driver_const.h>
#include <assert.h>
#include <string>

#define  APPCONTROL_SERVICE				TEXT("protectorservice")
#define  APPCONTROL_FILE				TEXT("\\\\.\\PROTECTOR")
#define  APPCONTROL_DRIVER_FILE			TEXT("protector.sys")

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
	SC_HANDLE service_handle = NULL;
	SC_HANDLE serverMan =NULL;

	_DEBUG_STREAM_TRC_("[DriverMngr] Install Driver");
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
	serverMan=OpenSCManager(0,0,SC_MANAGER_ALL_ACCESS);
	if (NULL == serverMan) {
		rc =Family007::ErrorCode::ERROR_OPEN_SCMGR_FAILED;
		REPORT_FATAL_ERROR_WITH_ERRNO(rc, "OpenSCManager", 
			"OpenSCManager() to open a SCManager", __FUNCTION__);
		_DEBUG_STREAM_TRC_("[DriverMngr] OpenSCManager failed Windows Error : "<<GetLastError());
		goto exit;
	}


	// 如果打开Service是吧
	service_handle=CreateService(serverMan, APPCONTROL_SERVICE, 
		APPCONTROL_SERVICE,
		SERVICE_START | SERVICE_STOP,   SERVICE_KERNEL_DRIVER, 
		SERVICE_DEMAND_START,    SERVICE_ERROR_NORMAL,
		namebuff, 0, 0, 0, 0, 0);
	if (NULL == service_handle) {
		rc = Family007::ErrorCode::ERROR_CREATE_SERVICE_FAILED;
		REPORT_FATAL_ERROR_WITH_ERRNO(rc, "CreateService", 
			"CreateService() failed", __FUNCTION__);
		_DEBUG_STREAM_TRC_("[DriverMngr] CreateService failed Windows Error : "<<GetLastError());
		goto exit;
	}
 

	// 启动
	if (FALSE == StartService(service_handle,0,0)) {
		rc = Family007::ErrorCode::ERROR_START_SERVICE_FAILED;
		REPORT_FATAL_ERROR_WITH_ERRNO(rc, "StartService", 
			"StartService() failed", __FUNCTION__);
		_DEBUG_STREAM_TRC_("[DriverMngr] StartService failed Windows Error : "<<GetLastError());
		goto exit;
	}

	CloseServiceHandle(service_handle);

	_DEBUG_STREAM_TRC_("[DriverMngr] install service"<<namebuff);

exit:
	if (NULL != service_handle) {
		CloseServiceHandle (service_handle);
	}
	if (NULL != serverMan ) {
		CloseServiceHandle(serverMan); 
	}
	return rc;
}

int stopService() {
	return 0;
}
int AppController::UninstallDriver()
{
	_DEBUG_STREAM_TRC_("[DriverMngr] Uninstall Driver");

	int rc = 0;
	SC_HANDLE serverMan = NULL;
	SC_HANDLE servHandle = NULL;
	SERVICE_STATUS_PROCESS ssp;
	DWORD dwBytesNeeded;
	SERVICE_STATUS stat ;

	serverMan=OpenSCManager(0,0,SC_MANAGER_ALL_ACCESS);
	if (NULL == serverMan) {
		rc =Family007::ErrorCode::ERROR_OPEN_SCMGR_FAILED;
		REPORT_FATAL_ERROR_WITH_ERRNO(rc, "OpenSCManager", 
			"OpenSCManager() to open a SCManager", __FUNCTION__);
		_DEBUG_STREAM_TRC_("[DriverMngr] OpenSCManager failed Windows Error : "<<GetLastError());
		goto exit;
	}

	servHandle=OpenService(serverMan, APPCONTROL_SERVICE, SERVICE_ALL_ACCESS);
	if (NULL == serverMan) {
		rc =Family007::ErrorCode::ERROR_OPEN_SERVICE_FAILED;
		REPORT_FATAL_ERROR_WITH_ERRNO(rc, "OpenService", 
			"OpenService() to open a SCManager", __FUNCTION__);
		_DEBUG_STREAM_TRC_("[DriverMngr] OpenService failed Windows Error : "<<GetLastError());
		goto exit;
	}

	if (FALSE == ControlService(servHandle,SERVICE_CONTROL_STOP,&stat)) {
		rc =Family007::ErrorCode::ERROR_CONTROL_SERVICE_FAILED;
		REPORT_FATAL_ERROR_WITH_ERRNO(rc, "ControlService", 
			"call ControlService() to stop server", __FUNCTION__);
		_DEBUG_STREAM_TRC_("[DriverMngr] ControlService failed Windows Error : "<<GetLastError());
		goto exit;

	}

	if (FALSE == DeleteService(servHandle)) {
		rc =Family007::ErrorCode::ERROR_DELETE_SERVICE_FAILED;
		REPORT_FATAL_ERROR_WITH_ERRNO(rc, "DeleteService", 
			"DeleteService() failed", __FUNCTION__);
		_DEBUG_STREAM_TRC_("[DriverMngr] DeleteService failed Windows Error : "<<GetLastError());
		goto exit;
	}

exit:
	if (NULL != servHandle) {
		CloseServiceHandle (servHandle);
	}
	if (NULL != serverMan ) {
		CloseServiceHandle(serverMan); 
	}
	return rc;
}


int  AppController::begin()
{
	int rc = 0;
	// 避免错误，先卸载再加载
	UninstallDriver();
	rc = InstallDriver(); 
	if (!rc) {
		goto exit;
	}

	//create processing thread
	HANDLE hThread = CreateThread(NULL, 0, 
		(LPTHREAD_START_ROUTINE)CheckAppProc,
		(LPVOID)this, 0, &dwThreadId);


	// open device
	// 此处将导致驱动程序真正加载
	m_hDevice=CreateFile(APPCONTROL_FILE,GENERIC_READ | GENERIC_WRITE, 0, 0, 
		OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, 0);
	if (INVALID_HANDLE_VALUE == m_hDevice) {
		rc =Family007::ErrorCode::ERROR_OPEN_DEVICE_FAILED;
		REPORT_FATAL_ERROR_WITH_ERRNO(rc, "CreateFile", 
			"CreateFile() to open a device to load appcontrol driver failed", __FUNCTION__);

		_DEBUG_STREAM_TRC_("[DriverMngr] CreateFile failed Windows Error : "<<GetLastError());

		goto exit;
	}

	// 获取系统路径
	char SYSTEM_DIR[MAX_PATH];
	GetWindowsDirectory(SYSTEM_DIR, MAX_PATH);

	// 初始化缓冲区
	DWORD dw;
	DWORD buffer_init[64];
	// TODO:不能兼容64为
	DWORD * addr=(DWORD *)(1+(DWORD)GetProcAddress(GetModuleHandle("ntdll.dll"),"NtCreateSection"));  
	ZeroMemory(buffer_init,sizeof(buffer_init));

	buffer_init[0] = addr[0];                                                                              // 传入函数NtCreateSection的路径
	buffer_init[1] = (DWORD)exchange_buffer_.get_buffer_addr();         // 传入交换缓冲区的内容
	buffer_init[2] = (DWORD)&SYSTEM_DIR[0];                                          // 传入SystemDir
	DeviceIoControl(m_hDevice,IO_CONTROL_BUFFER_INIT, buffer_init,512, buffer_init, 512, &dw, NULL);

exit:

	return rc;
}

int AppController::end() {
	int rc = 0;

	// 关闭
	CloseHandle(m_hDevice);
	m_hDevice = NULL;

	// 卸载驱动程序
	UninstallDriver();

	// 结束线程
	exit_thread_ = 1;

	return rc;
}

int AppController::checkpassed(const char * filename) {
	int result = 1;
	_DEBUG_STREAM_TRC_("[DriverMngr] Do you want to run"<<exchange_buffer_.get_filepath());

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
	_DEBUG_STREAM_TRC_("[DriverMngr] Begin Thread Proc");
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

	_DEBUG_STREAM_TRC_("[DriverMngr] End Thread Proc");

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
	DWORD status = 0;
	if (passed) {
		result = 1;
	} else {
		result = 0;
	}
	memmove(&(exchange_buffer[ADDR_EXCHANGE_APP_COMP]), &status, 4);
	memmove(&(exchange_buffer[ADDR_EXCHANGE_APP_RESULT]), &result, 4);
}

void AppController::ExchangeBuffer::reset_status() {
}