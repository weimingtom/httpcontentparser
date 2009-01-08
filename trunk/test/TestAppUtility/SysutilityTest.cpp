#include "StdAfx.h"
#include ".\sysutilitytest.h"
#include <apputility.h>
#include <utility\strutility.h>
#include <app_constants.h>
#include <iostream>


SysutilityTest::SysutilityTest(void) {
}

SysutilityTest::~SysutilityTest(void) {
}

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


void SysutilityTest::testGetMainUIName() {
	HMODULE handle = GetModule(TEXT("TestSysutility.exe"));
	TCHAR workdir[MAX_PATH], fullpath[MAX_PATH], expected[MAX_PATH], installpath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, workdir);
	_sntprintf(expected, MAX_PATH, TEXT("%s\\%s"), workdir, APPLICATION_MAINUI_NAME);
	GetMainUIPath(fullpath, MAX_PATH, handle);

	_tcslwr(expected);
	_tcslwr(fullpath);
	CPPUNIT_ASSERT( expected == _tcsstr(expected, fullpath));
	CPPUNIT_ASSERT( 0 == _tcscmp(fullpath, expected));

	GetInstallPath(installpath, MAX_PATH, handle);
	GetMainUIPath(fullpath, MAX_PATH, installpath);
	_tcslwr(fullpath);
	CPPUNIT_ASSERT( expected == _tcsstr(expected, fullpath));
	CPPUNIT_ASSERT( 0 == _tcscmp(fullpath, expected));

	std::cout<<"MainUI fullpath: " << fullpath << std::endl;

}
void SysutilityTest::testGetFileNameDir() {
	const TCHAR * name = TEXT("WAHT.EXE");
	const TCHAR * dir = TEXT("c:\\program files\\hello\\");
	TCHAR fullpath[MAX_PATH], result[MAX_PATH];
	_sntprintf(fullpath, MAX_PATH, "%s%s", dir, name);
	GetFileNameDir(fullpath, result, MAX_PATH);
	_tcslwr(fullpath);
	CPPUNIT_ASSERT( 0 == _tcscmp(dir, result));
}

// ������ʷ�������ļ�
void SysutilityTest::testGetRecordConfigfile() {
	HMODULE handle = GetModule(TEXT("TestSysutility.exe"));
	TCHAR workdir[MAX_PATH], fullpath[MAX_PATH], configfile[MAX_PATH], installpath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, workdir);
	_sntprintf(configfile, MAX_PATH, TEXT("%s\\%s"), workdir, TEXT("history\\config.xml"));

	GetInstallPath(installpath, MAX_PATH, handle);
	GetRecordConfigfile(fullpath, MAX_PATH, installpath);

	_tcslwr(configfile);
	_tcslwr(fullpath);
	CPPUNIT_ASSERT( configfile == _tcsstr(configfile, fullpath));
	CPPUNIT_ASSERT( 0 == _tcscmp(fullpath, configfile));

	std::cout<<"Record History config : " << fullpath << std::endl;
}

// ������ҳ��·��
void SysutilityTest::testGetPageDirectory() {
	HMODULE handle = GetModule(TEXT("TestSysutility.exe"));
	TCHAR workdir[MAX_PATH], fullpath[MAX_PATH], pageseDir[MAX_PATH], installpath[MAX_PATH];;
	GetCurrentDirectory(MAX_PATH, workdir);
	_sntprintf(pageseDir, MAX_PATH, TEXT("%s\\%s"), workdir, TEXT("history\\text\\"));

	GetInstallPath(installpath, MAX_PATH, handle);
	GetPageDirectory(fullpath, MAX_PATH, installpath);

	CPPUNIT_ASSERT( true == strutility::endwith(pageseDir, "\\"));
	_tcslwr(fullpath);
	_tcslwr(pageseDir);
	CPPUNIT_ASSERT( pageseDir == _tcsstr(pageseDir, fullpath));
	CPPUNIT_ASSERT( 0 == _tcscmp(fullpath, pageseDir));

	std::cout<<"Page directory : " << fullpath << std::endl;
}
// ����ͼƬ��·��
void SysutilityTest::testGetImageDirectory() {
	HMODULE handle = GetModule(TEXT("TestSysutility.exe"));
	TCHAR workdir[MAX_PATH], fullpath[MAX_PATH], imageDir[MAX_PATH], installpath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, workdir);
	_sntprintf(imageDir, MAX_PATH, TEXT("%s\\%s"), workdir, TEXT("history\\images\\"));

	GetInstallPath(installpath, MAX_PATH, handle);
	GetImageDirectory(fullpath, MAX_PATH, installpath);

	_tcslwr(fullpath);
	_tcslwr(imageDir);
	CPPUNIT_ASSERT( true == strutility::endwith(imageDir, "\\"));
	CPPUNIT_ASSERT( imageDir == _tcsstr(imageDir, fullpath));
	CPPUNIT_ASSERT( 0 == _tcscmp(fullpath, imageDir));

	std::cout<<"Image directory : " << fullpath << std::endl;
}

void SysutilityTest::testGetInstallPath() {
	HMODULE handle = GetModule(TEXT("TestSysutility.exe"));
	TCHAR workdir[MAX_PATH], install_path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, workdir);
	GetInstallPath(install_path, MAX_PATH, handle);

	if (false == strutility::endwith(workdir, "\\")) {
		int len = _tcslen(workdir);
		workdir[len] = '\\';
		workdir[len+1] = '\0';
	}

	CPPUNIT_ASSERT( true == strutility::endwith(install_path, "\\"));
	CPPUNIT_ASSERT( true == strutility::endwith(workdir, "\\"));
	_tcslwr(workdir);
	_tcslwr(install_path);
	CPPUNIT_ASSERT( install_path == _tcsstr(install_path, workdir));

	std::cout<<"Install directory : " << install_path << std::endl;
}

void SysutilityTest::testGetAppConfigFilename() {
	HMODULE handle = GetModule(TEXT("TestSysutility.exe"));
	TCHAR workdir[MAX_PATH], fullpath[MAX_PATH], configfilename[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, workdir);
	_sntprintf(configfilename, MAX_PATH, TEXT("%s\\%s"), workdir, TEXT("config.xml"));

	GetAppConfigFilename(fullpath, MAX_PATH, handle);

	_tcslwr(workdir);
	_tcslwr(fullpath);

	CPPUNIT_ASSERT( fullpath == _tcsstr(fullpath, workdir));
	CPPUNIT_ASSERT( 0 == _tcscmp(fullpath, configfilename));

	std::cout<<"App config : " << fullpath << std::endl;
}

void SysutilityTest::testRegisterOper() {
	//HMODULE handle = GetModule(TEXT("TestSysutility.exe"));
	//BOOL isAuto_run = isAutoRun(handle);
}