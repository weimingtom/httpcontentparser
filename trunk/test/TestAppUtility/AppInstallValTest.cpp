#include "StdAfx.h"
#include ".\appinstallvaltest.h"
#include <apputility\AppinstallValidate.h>
#include <app_constants.h>
#include <softwareStatus.h>
#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;

namespace {
using namespace std;
HMODULE GetModule(const TCHAR * exefilename) {
	HANDLE hProcessSnap;
	HANDLE hProcess;
	PROCESSENTRY32 pe32;
	DWORD dwPriorityClass;


	hProcessSnap  = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if( hProcessSnap  == INVALID_HANDLE_VALUE ) {
		cout<< "CreateToolhelp32Snapshot (of processes)"<<endl;
		return((HMODULE)INVALID_HANDLE_VALUE);
	}

	pe32.dwSize = sizeof( PROCESSENTRY32 );
	if( !Process32First( hProcessSnap, &pe32 ) ) {
		cout<<  "Process32First" <<endl; // Show cause of failure
		CloseHandle( hProcessSnap );    // Must clean up the
		//   snapshot object!
		return((HMODULE)INVALID_HANDLE_VALUE);
	}

	do {
		if (0 == _strcmpi(pe32.szExeFile, exefilename)) {
			// Retrieve the priority class.
			dwPriorityClass = 0;
			hProcess = OpenProcess(
				PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID );
			if( hProcess == NULL ) {
				cout<<"OpenProcess"<<endl;
				return (HMODULE)INVALID_HANDLE_VALUE;
			} else {
				HMODULE hModule;
				DWORD dwNeeded;
				EnumProcessModules(hProcess, &hModule, sizeof(hModule), &dwNeeded);
				CloseHandle(hProcessSnap);
				CloseHandle(hProcess);
				return hModule;
			}
		}

	} while( Process32Next( hProcessSnap, &pe32 ) );

	return (HMODULE)INVALID_HANDLE_VALUE;
}
};

void testRunInCOM() {
	AppUtility::AppInstallValidate t1(VALIDATE_COM, SNOWMAN_STATUS_REGISTERED);
	t1.repair();
	// 这里失败是因为COM文件也不存在，也返回了错误
	BOOST_CHECK(t1.getErrorCode()  == PACKETSFILTERED_FILE_NOT_FOUND);
}
void testRunInSPI() {
	AppUtility::AppInstallValidate t1(VALIDATE_SPI, SNOWMAN_STATUS_REGISTERED);
	t1.repair();
	BOOST_CHECK(t1.getErrorCode() == F_COM_FILE_NOT_FOUND);
}
void testRunInNone() {
}

void testServieInstall() {
}

void testShouldRepair() {
	AppUtility::AppInstallValidate t1(VALIDATE_COM, SNOWMAN_STATUS_REGISTERED);

	BOOST_CHECK(t1.shouldRepairCOM() == false);
	BOOST_CHECK(t1.shouldRepairRegistry() == true);
	BOOST_CHECK(t1.shouldRepairSPI() == true);

	AppUtility::AppInstallValidate t2(VALIDATE_SPI, SNOWMAN_STATUS_REGISTERED);
	BOOST_CHECK(t2.shouldRepairCOM() == true);
	BOOST_CHECK(t2.shouldRepairRegistry() == false);
	BOOST_CHECK(t2.shouldRepairSPI() == false);

	AppUtility::AppInstallValidate t3(VLAIDATE_NONE, SNOWMAN_STATUS_REGISTERED);
	BOOST_CHECK(t3.shouldRepairCOM() == true);
	BOOST_CHECK(t3.shouldRepairRegistry() == true);
	BOOST_CHECK(t3.shouldRepairSPI() == true);
}