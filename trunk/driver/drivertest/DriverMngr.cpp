#include "stdafx.h"
#include ".\DriverMngr.h"
#include <DebugOutput.h>
#include "ErrorCode.h"

#define  APPCONTROL_SERVICE				TEXT("protectorservice")
#define  APPCONTROL_FILE						TEXT("\\\\.\\PROTECTOR")
#define  APPCONTROL_DRIVER_FILE		TEXT("protector.sys")

int AppController::InstallDriver()
{
	int rc = 0;
	_DEBUG_STREAM_TRC_("Install Driver");
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
		_DEBUG_STREAM_TRC_("OpenSCManager failed Windows Error : "<<GetLastError());
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
		_DEBUG_STREAM_TRC_("CreateService failed Windows Error : "<<GetLastError());
		goto exit;
	}

	BOOL result = StartService(service_handle,0,0);
	if (!result) {
		rc = Family007::ErrorCode::ERROR_START_SERVICE_FAILED;
		REPORT_FATAL_ERROR_WITH_ERRNO(rc, "StartService", 
			"StartService() failed", __FUNCTION__);
		_DEBUG_STREAM_TRC_("StartService failed Windows Error : "<<GetLastError());
		goto exit;
	}
	CloseServiceHandle(service_handle);

	_DEBUG_STREAM_TRC_("install service %s"<<namebuff);

exit:
	return rc;
}

int AppController::UninstallDriver()
{
	_DEBUG_STREAM_TRC_("Uninstall Driver");

	int rc = 0;

	SC_HANDLE serverMan=OpenSCManager(0,0,SC_MANAGER_ALL_ACCESS);
	if (NULL == serverMan) {
		rc =Family007::ErrorCode::ERROR_OPEN_SCMGR_FAILED;
		REPORT_FATAL_ERROR_WITH_ERRNO(rc, "OpenSCManager", 
			"OpenSCManager() to open a SCManager", __FUNCTION__);
		_DEBUG_STREAM_TRC_("OpenSCManager failed Windows Error : "<<GetLastError());
		goto exit;
	}

	SERVICE_STATUS stat;
	SC_HANDLE servHandle=OpenService(serverMan, APPCONTROL_SERVICE, SERVICE_ALL_ACCESS);
	if (NULL == serverMan) {
		rc =Family007::ErrorCode::ERROR_OPEN_SERVICE_FAILED;
		REPORT_FATAL_ERROR_WITH_ERRNO(rc, "OpenService", 
			"OpenService() to open a SCManager", __FUNCTION__);
		_DEBUG_STREAM_TRC_("OpenService failed Windows Error : "<<GetLastError());
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
	UninstallDriver();
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

		_DEBUG_STREAM_TRC_("CreateFile failed Windows Error : "<<GetLastError());

		goto exit;
	}

	// 获取系统路径
	char SYSTEM_DIR[MAX_PATH];
	GetSystemDirectory(SYSTEM_DIR, MAX_PATH);

	// 初始化缓冲区
	DWORD dw;
	DWORD buffer_init[64];
	DWORD * addr=(DWORD *)(1+(DWORD)GetProcAddress(GetModuleHandle("ntdll.dll"),"NtCreateSection"));
	ZeroMemory(buffer_init,sizeof(buffer_init));
                          
	buffer_init[0] = addr[0];                                                                              // 传入函数NtCreateSection的路径
	buffer_init[1] = (DWORD)&exchange_buffer[0];                                   // 传入交换缓冲区的内容
	buffer_init[2] = (DWORD)&SYSTEM_DIR[0];                                          // 传入SystemDir
	DeviceIoControl(device,IO_CONTROL_BUFFER_INIT, buffer_init,256, buffer_init, 256, &dw, NULL);

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

// 重置状态
void AppController::resetState() {
	int status = 0;
	memmove(exchange_buffer, &(status), 4);
}
int AppController::checkpassed(const char * filename) {
	int result = 1;
	// ask user's permission to run the program
	const int MSG_BUF_LEN = 512;
	char msgbuff[MSG_BUF_LEN];
	_snprintf(msgbuff, MSG_BUF_LEN, "Do you want to run %s", getFilePath());
	_DEBUG_STREAM_TRC_(msgbuff);

	// 将结果写入内存
	memmove(&exchange_buffer[4], &result, 4);
	return result;
}

int AppController::checkpassed() {
	return checkpassed(getFilePath());
}

int AppController::getState() {
	int status;
	memmove(&status, &(exchange_buffer[0]), 4);
	return status;
}


DWORD CALLBACK CheckAppProc(LPVOID param) {
	_DEBUG_STREAM_TRC_("Begin Thread Proc");
	AppController * controlloer = (AppController*)param;
	while(1)
	{
		//if nothing is there, Sleep() 10 ms and check again
		while( ! controlloer->getState()) {
			Sleep(50);
		}

		// if user's reply is positive, add the program to the white list
		int passed = controlloer->checkpassed();
		controlloer->resetState();

		// 如果调用了end函数， 退出线程
		if (controlloer->exitThread()) {
			break;
		}
	}

	_DEBUG_STREAM_TRC_("End Thread Proc");

	return 0;
}