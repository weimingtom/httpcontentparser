#include "StdAfx.h"
#include ".\AppUtilitytest.h"
#include <apputility\apputility.h>
#include <utility\strutility.h>
#include <app_constants.h>
#include <iostream>
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


void testGetMainUIName() {
	TCHAR workdir[MAX_PATH], fullpath[MAX_PATH], expected[MAX_PATH], installpath[MAX_PATH], exefile[MAX_PATH];
	GetModuleFileName(NULL, exefile, MAX_PATH);
	GetFileNameDir(exefile, workdir, MAX_PATH);
	_sntprintf(expected, MAX_PATH, TEXT("%s%s"), workdir, APPLICATION_MAINUI_NAME);
	GetMainUIPath(fullpath, MAX_PATH);

	_tcslwr(expected);
	_tcslwr(fullpath);
	BOOST_CHECK( expected == _tcsstr(expected, fullpath));
	BOOST_CHECK( 0 == _tcscmp(fullpath, expected));

	GetInstallPath(installpath, MAX_PATH);
	GetMainUIPath(fullpath, MAX_PATH);
	_tcslwr(fullpath);
	BOOST_CHECK( expected == _tcsstr(expected, fullpath));
	BOOST_CHECK( 0 == _tcscmp(fullpath, expected));

	std::cout<<"MainUI fullpath: " << fullpath << std::endl;

}
void testGetFileNameDir() {
	const TCHAR * name = TEXT("WAHT.EXE");
	const TCHAR * dir = TEXT("c:\\program files\\hello\\");
	TCHAR fullpath[MAX_PATH], result[MAX_PATH];
	_sntprintf(fullpath, MAX_PATH, "%s%s", dir, name);
	GetFileNameDir(fullpath, result, MAX_PATH);
	_tcslwr(fullpath);
	BOOST_CHECK( 0 == _tcscmp(dir, result));
}

// 保存历史的配置文件
void testGetRecordConfigfile() {
	TCHAR workdir[MAX_PATH], fullpath[MAX_PATH], configfile[MAX_PATH], installpath[MAX_PATH], exefile[MAX_PATH];
	GetModuleFileName(NULL, exefile, MAX_PATH);
	GetFileNameDir(exefile, workdir, MAX_PATH);
	_sntprintf(configfile, MAX_PATH, TEXT("%s%s"), workdir, TEXT("history\\config.xml"));

	GetInstallPath(installpath, MAX_PATH);
	GetRecordConfigfile(fullpath, MAX_PATH);

	_tcslwr(configfile);
	_tcslwr(fullpath);
	BOOST_CHECK( configfile == _tcsstr(configfile, fullpath));
	BOOST_CHECK( 0 == _tcscmp(fullpath, configfile));

	std::cout<<"Record History config : " << fullpath << std::endl;
}

// 保存网页的路径
void testGetPageDirectory() {
	TCHAR workdir[MAX_PATH], fullpath[MAX_PATH], pageseDir[MAX_PATH], installpath[MAX_PATH], exefile[MAX_PATH];
	GetModuleFileName(NULL, exefile, MAX_PATH);
	GetFileNameDir(exefile, workdir, MAX_PATH);
	_sntprintf(pageseDir, MAX_PATH, TEXT("%s%s"), workdir, TEXT("history\\text\\"));

	GetInstallPath(installpath, MAX_PATH);
	GetPageDirectory(fullpath, MAX_PATH);

	BOOST_CHECK( true == strutility::endwith(pageseDir, "\\"));
	_tcslwr(fullpath);
	_tcslwr(pageseDir);
	BOOST_CHECK( pageseDir == _tcsstr(pageseDir, fullpath));
	BOOST_CHECK( 0 == _tcscmp(fullpath, pageseDir));

	std::cout<<"Page directory : " << fullpath << std::endl;
}
// 保存图片的路径
void testGetImageDirectory() {
	TCHAR workdir[MAX_PATH], fullpath[MAX_PATH], imageDir[MAX_PATH], installpath[MAX_PATH], exefile[MAX_PATH];
	GetModuleFileName(NULL, exefile, MAX_PATH);
	GetFileNameDir(exefile, workdir, MAX_PATH);
	_sntprintf(imageDir, MAX_PATH, TEXT("%s%s"), workdir, TEXT("history\\images\\"));

	GetInstallPath(installpath, MAX_PATH);
	GetImageDirectory(fullpath, MAX_PATH);

	_tcslwr(fullpath);
	_tcslwr(imageDir);
	BOOST_CHECK( true == strutility::endwith(imageDir, "\\"));
	BOOST_CHECK( imageDir == _tcsstr(imageDir, fullpath));
	BOOST_CHECK( 0 == _tcscmp(fullpath, imageDir));

	std::cout<<"Image directory : " << fullpath << std::endl;
}

void testGetInstallPath() {
	HMODULE handle = GetModule(TEXT("TestSysutility.exe"));
	TCHAR workdir[MAX_PATH], install_path[MAX_PATH], exefile[MAX_PATH];

	GetModuleFileName(NULL, exefile, MAX_PATH);
	GetFileNameDir(exefile, workdir, MAX_PATH);

	GetInstallPath(install_path, MAX_PATH);

	if (false == strutility::endwith(workdir, "\\")) {
		int len = _tcslen(workdir);
		workdir[len] = '\\';
		workdir[len+1] = '\0';
	}

	BOOST_CHECK( true == strutility::endwith(install_path, "\\"));
	BOOST_CHECK( true == strutility::endwith(workdir, "\\"));
	_tcslwr(workdir);
	_tcslwr(install_path);
	BOOST_CHECK( install_path == _tcsstr(install_path, workdir));

	std::cout<<"Install directory : " << install_path << std::endl;
}

void testGetAppConfigFilename() {
	TCHAR workdir[MAX_PATH], fullpath[MAX_PATH], configfilename[MAX_PATH], exefile[MAX_PATH];
	GetModuleFileName(NULL, exefile, MAX_PATH);
	GetFileNameDir(exefile, workdir, MAX_PATH);
	_sntprintf(configfilename, MAX_PATH, TEXT("%s%s"), workdir, TEXT("nwist.dll"));

	GetAppConfigFilename(fullpath, MAX_PATH);

	_tcslwr(configfilename);
	_tcslwr(fullpath);

	BOOST_CHECK( fullpath == _tcsstr(fullpath, configfilename));
	BOOST_CHECK( 0 == _tcscmp(fullpath, configfilename));

	std::cout<<"App config : " << fullpath << std::endl;
}

void testRegisterOper() {
	//HMODULE handle = GetModule(TEXT("TestSysutility.exe"));
	//BOOL isAuto_run = isAutoRun(handle);
}
