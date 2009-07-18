#include "stdafx.h"
#include ".\DriverMngr.h"
#include "ErrorReport.h"
#include <DebugOutput.h>
#include <driver_const.h>
#include <assert.h>
#include <string>

#define  APPCONTROL_SERVICE				TEXT("protectorservice")
#define  APPCONTROL_FILE				TEXT("\\\\.\\PROTECTOR")
#define  APPCONTROL_DRIVER_FILE			TEXT("protector.sys")

//=============================
// ���캯������������
AppController::AppController(CheckProcessCreate * checker) : checker_(checker) {
	dwThreadId = 0;
	exit_thread_ = 0;
	assert (checker != NULL);
}
AppController::~AppController() {
}

int AppController::InstallDriver() {
	int rc = 0;
	rc = InstallService();
	if (rc) {
		goto exit;
	}
exit:
	return rc;
}

int AppController::UninstallDriver()
{
	int rc = 0;

	rc = DeleteService();
	return rc;
}

int  AppController::begin()
{
	int rc = 0;

	rc = InstallDriver(); 

	//create processing thread
	HANDLE hThread = CreateThread(NULL, 0, 
		(LPTHREAD_START_ROUTINE)CheckAppProc,
		(LPVOID)this, 0, &dwThreadId);


	// open device
	// �˴�����������������������
	m_hDevice=CreateFile(APPCONTROL_FILE,GENERIC_READ | GENERIC_WRITE, 0, 0, 
		OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, 0);
	if (INVALID_HANDLE_VALUE == m_hDevice) {
		rc =Family007::ErrorManagement::ERROR_DRIVER_OPEN_DEVICE_FAILED;
		REPORT_WINAPI_ERROR("CreateFile");
		goto exit;
	}

	// ��ȡϵͳ·��
	char SYSTEM_DIR[MAX_PATH];
	GetWindowsDirectory(SYSTEM_DIR, MAX_PATH);

	// ��ʼ��������
	DWORD dw;
	DWORD buffer_init[64];
	// TODO:���ܼ���64Ϊ
	DWORD * addr=(DWORD *)(1+(DWORD)GetProcAddress(GetModuleHandle("ntdll.dll"),"NtCreateSection"));  
	ZeroMemory(buffer_init,sizeof(buffer_init));

	buffer_init[0] = addr[0];                                                                              // ���뺯��NtCreateSection��·��
	buffer_init[1] = (DWORD)exchange_buffer_.get_buffer_addr();         // ���뽻��������������
	buffer_init[2] = (DWORD)&SYSTEM_DIR[0];                                          // ����SystemDir
	DeviceIoControl(m_hDevice,IO_CONTROL_BUFFER_INIT, buffer_init,512, buffer_init, 512, &dw, NULL);

exit:

	return rc;
}

int AppController::end() {
	int rc = 0;

	// �ر�
	CloseHandle(m_hDevice);
	m_hDevice = NULL;

	// ж����������
	UninstallDriver();

	// �����߳�
	exit_thread_ = 1;

	return rc;
}

int AppController::checkpassed(const char * filename) {
	int result = 1;
	_DEBUG_STREAM_TRC_("[DriverMngr] Do you want to run"<<exchange_buffer_.get_filepath());

	// �����д���ڴ�
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
// �߳�
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

		// ���������end������ �˳��߳�
		if (controlloer->exitThread()) {
			break;
		}
	}

	_DEBUG_STREAM_TRC_("[DriverMngr] End Thread Proc");

	return 0;
}

// =======================================
// ������������
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

int AppController::InstallService() {
	int rc = 0;
	SC_HANDLE service_handle = NULL;
	SC_HANDLE serverMan =NULL;

	_DEBUG_STREAM_TRC_("[DriverMngr] Install Service");
	// �ڵ�ǰ·���»�ȡDRIVER��·��
	// ��ȡ���������·��
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

	// ע�����
	//create service
	serverMan=OpenSCManager(0,0,SC_MANAGER_ALL_ACCESS);
	if (NULL == serverMan) {
		rc =Family007::ErrorManagement::ERROR_SMC_OPEN_SCMGR_FAILED;
		REPORT_WINAPI_ERROR("OpenSCManager");
		goto exit;
	}

	// ����Ѿ��򿪣� ���˳�
	// ���״̬��������ڣ�STOP����STOP_PENDING��ı�ΪSTART
	service_handle = OpenService(serverMan, APPCONTROL_SERVICE, SC_MANAGER_ALL_ACCESS);
	if (NULL != service_handle) {
		DWORD dwBytesNeeded;
		SERVICE_STATUS_PROCESS ssp;

		// ��ȡ״̬
		if ( !QueryServiceStatusEx(service_handle, SC_STATUS_PROCESS_INFO,
			(LPBYTE)&ssp,  	sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded ) ) {
				rc = Family007::ErrorManagement::ERROR_SMC_QUERY_STATUX_EX_FAILED;
				REPORT_WINAPI_ERROR("QueryServiceStatusEx");
				goto exit;
			}
	
			// ���״̬���ڣ�����״��
			if (ssp.dwCurrentState == SERVICE_STOPPED || ssp.dwCurrentState== SERVICE_STOP_PENDING) {
				goto start_serv;
			} else {
				// ����״̬��ֱ������
				goto exit;
			}
	}

	// �����Service�ǰ�
	service_handle=CreateService(serverMan, APPCONTROL_SERVICE, 
		APPCONTROL_SERVICE, SERVICE_START | SERVICE_STOP,   SERVICE_KERNEL_DRIVER, 
		SERVICE_DEMAND_START,    SERVICE_ERROR_NORMAL,
		namebuff, 0, 0, 0, 0, 0);
	if (NULL == service_handle) {
		rc = Family007::ErrorManagement::ERROR_SMC_CREATE_SERVICE_FAILED;
		REPORT_WINAPI_ERROR("CreateService");

		if (FALSE == ::DeleteService(service_handle)) {
			rc =Family007::ErrorManagement::ERROR_SMC_DELETE_SERVICE_FAILED;
			REPORT_WINAPI_ERROR("DeleteService");
			goto exit;
		}

		goto exit;
	}

start_serv:
	// ����
	if (FALSE == StartService(service_handle,0,0)) {
		rc = Family007::ErrorManagement::ERROR_SMC_START_SERVICE_FAILED;
		REPORT_WINAPI_ERROR("StartService");
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


// ���ô˺����� ����Ӧ�ùرվ��������ᳬʱ
int AppController::DeleteService() {
	SC_HANDLE schSCManager = NULL;
	SC_HANDLE schService = NULL;
	SERVICE_STATUS_PROCESS ssp;
	DWORD dwStartTime = GetTickCount();
	DWORD dwBytesNeeded;
	const DWORD dwTimeout = 30000; // 30-second time-out
	int rc = 0;

	_DEBUG_STREAM_TRC_("[DriverMngr] Delete Service");

	schSCManager = OpenSCManager(NULL, NULL,   SC_MANAGER_ALL_ACCESS);  
	if (NULL == schSCManager) 
	{
		rc =Family007::ErrorManagement::ERROR_SMC_OPEN_SCMGR_FAILED;
		REPORT_WINAPI_ERROR("OpenSCManager");
		goto exit;
	}

	// ��ȡ���
	schService = OpenService( schSCManager, APPCONTROL_SERVICE,  
		SERVICE_STOP | SERVICE_QUERY_STATUS | SERVICE_ENUMERATE_DEPENDENTS);  
	if (schService == NULL) 	{ 
		rc =Family007::ErrorManagement::ERROR_SMC_OPEN_SERVICE_FAILED;
		REPORT_WINAPI_ERROR("OpenService");
		goto exit;
	}    

	// ��ȡ״̬
	if ( !QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO,
				(LPBYTE)&ssp,  	sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded ) ) {
					rc = Family007::ErrorManagement::ERROR_SMC_QUERY_STATUX_EX_FAILED;
		REPORT_WINAPI_ERROR("QueryServiceStatusEx");
		goto exit;
	}

	// ����Ѿ�ֹͣ��ֱ���˳�
	if ( ssp.dwCurrentState == SERVICE_STOPPED )     {
		goto exit;
	} else {
		// ���û��ֹͣ������ֹͣ
		 SERVICE_STATUS  stat;
		if (FALSE == ControlService(schService,SERVICE_CONTROL_STOP,&stat)) {
			rc =Family007::ErrorManagement::ERROR_SMC_CONTROL_SERVICE_STOP_FAILED;
			REPORT_WINAPI_ERROR("ControlService");
			goto exit;
		}
	}

	// �ȴ�֪��ֹͣ
	while ( ssp.dwCurrentState == SERVICE_STOP_PENDING )   {
        Sleep( ssp.dwWaitHint );
        if ( !QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO,  (LPBYTE)&ssp, 
                 sizeof(SERVICE_STATUS_PROCESS),  &dwBytesNeeded ) )   {
			 rc = Family007::ErrorManagement::ERROR_SMC_QUERY_STATUX_EX_FAILED;
			REPORT_WINAPI_ERROR("QueryServiceStatusEx");
			goto exit;		
        }

		// ����ȴ�����
		if ( GetTickCount() - dwStartTime > dwTimeout ) {
			rc = Family007::ErrorManagement::ERROR_SMC_CONTROL_STOP_TIMEOUT;
			_DEBUG_STREAM_TRC_("[DriverMngr] wait for pending timeout");
			goto exit;
		 }

		_DEBUG_STREAM_TRC_("[DriverMngr] Pending...");
	}

	// ɾ������
	if (FALSE == ::DeleteService(schService)) {
		rc =Family007::ErrorManagement::ERROR_SMC_DELETE_SERVICE_FAILED;
		REPORT_WINAPI_ERROR("DeleteService");
		goto exit;
	}
	
exit:
	if (NULL != schService) {
		CloseServiceHandle (schService);
	}
	if (NULL != schSCManager ) {
		CloseServiceHandle(schSCManager); 
	}

	if (!rc) {
		_DEBUG_STREAM_TRC_("[DriverMngr] Delete Service Success");
	} else {
		_DEBUG_STREAM_TRC_("[DriverMngr] Delete Service failed");
	}
	return rc;
}