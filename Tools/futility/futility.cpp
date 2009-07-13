// futility.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <AppInstallValidate.h>
#include <apputility.h>
#include <softwareStatus.h>
#include <com\comutility.h>
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <shell\shellutility.h>
#include <crypt.h>
#include <appinstallvalidate.h>
#include <softwareEncrypt\serialNumber.h>
#include <softwareEncrypt\LicenseInfo.h>
#include <softwareEncrypt\baseEncrypt.h>
#include <softwareencrypt\installdate.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <time.h>

using namespace std;
void printUsage();
void printInstallStatus();
void installAllComponent();
void uninstallAllComponent();
void printInstallStatus();
void getconfigfile();
void GetCOMPath(TCHAR *path, const int len) ;
void SetUninstallStatus() ;
void setinstallDate();
void setInvalidateSN();
void setTrialState();

int _tmain(int argc, _TCHAR* argv[])
{
	printUsage();
	int option = 0;
	std::cin>>option;

	switch(option) {
		case 1:
			installAllComponent();
			break;
		case 2:
			uninstallAllComponent();
			break;
		case 3:
			printInstallStatus();
			break;
		case 4:
			getconfigfile();
			break;
		case 5:
			SetUninstallStatus();
			break;
		case 6:
			setInvalidateSN();
			break;
		case 7:
			setInvalidateSN();
			setinstallDate();
		case 8:
			AppUtility::UninstallSPI();
			break;
		case 9:
			AppUtility::UninstallSPI();
			break;
		case 10:
			{
			AppUtility::AppInstallValidate valiedate(VALIDATE_SPI, SNOWMAN_STATUS_REGISTERED);
			valiedate.repair(true);
			break;
			}
	}
	return 0;
}

void setInvalidateSN() {
	string sn = "aaa23infadhf-2u3nfad";
	software_encrypt::internal_utility::storeSN(sn);
}

void setinstallDate() {
	SYSTEMTIME st = {0};
	FILETIME ft = {0};
	cout<<"\tplease input year : ";
	cin>>st.wYear;cout<<endl;
	cout<<"\tplease input month : ";
	cin>>st.wMonth;cout<<endl;
	cout<<"\tplease input days : ";
	cin>>st.wDay;cout<<endl;
	SystemTimeToFileTime(&st, &ft); 
	software_encrypt::internal_utility::setInstallDateFile(ft);
	software_encrypt::internal_utility::setInstallDataOnRegistry(ft);
	software_encrypt::internal_utility::setInstallDateInWin(ft);
}
void printUsage() {
	cout<<"Usage : "<<endl;
	cout<<"\t1. Install all component."<<endl;
	cout<<"\t2. Uninstall all compoment." <<endl;
	cout<<"\t3. get component install directory. "<<endl;
	cout<<"\t4. read the configuration file from encrypt file."<<endl;
	cout<<"\t5. Set app into uninstall model. "<<endl;
	cout<<"\t6. set app into tail model. "<<endl;
	cout<<"\t7. set install date. "<<endl;
	cout<<"\t8. uninstall SPI."<<endl;
	cout<<"\t11. uninstall Ext."<<endl;
	cout<<"\t0. exit"<<endl;
	cout<<"please input you option : ";
}

void SetAppStatus(const int state) {
	AutoInitInScale auto_;
	try {
		ISnowmanSetting * pSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER,
			IID_ISnowmanSetting, (LPVOID*)&pSetting);
		if (FAILED(hr)) {
			return ;
		}

		pSetting->setApplicationStatus(state);
		pSetting->Release();
		pSetting = NULL;
	} catch (_com_error &) {
	}
}

void setTrialState() {
	SetAppStatus(SNOWMAN_STATUS_TRIAL);
}

void SetUninstallStatus() {
	SetAppStatus(SNOWMAN_STATUS_UNINSTALL);
}


void getconfigfile() {
	TCHAR installPath[MAX_PATH], configfile[MAX_PATH];
	TCHAR decryptfile[] = ".\\configg.xml";

	GetCOMPath(installPath, MAX_PATH);
	_sntprintf(configfile, MAX_PATH, "%s\\%s", installPath, "nwist.dll");
	yanglei_utility::DecryptFile((LPTSTR)".\\nwist.dll", decryptfile);
}

void GetCOMPath(TCHAR *path, const int len) {
	AutoInitInScale auto_;
	try {
		memset(path, 0, len * sizeof(TCHAR));
		ISnowmanSetting * pSetting = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER,
			IID_ISnowmanSetting, (LPVOID*)&pSetting);
		if (FAILED(hr)) {
			cout<<"Create snowman FAILED with HRESULT value "<< hr<<endl;
			return ;
		}
		
		BSTR bstr;
		pSetting->GetInstallPath(&bstr);
		pSetting->Release();
		pSetting = NULL;
		_bstr_t bstrpath(bstr);
		_tcsncpy(path, (TCHAR*)bstrpath, len);
	} catch (_com_error & e) {
		cout<<"_com_error exception with Description :  "<< e.Description()<<endl;
	}
}


void printInstallStatus() {
	TCHAR path[MAX_PATH];
	GetCOMPath(path, MAX_PATH);
	cout<<"COM Install Path : "<<path<<endl;

	GetInstallPathFromRegistry(path, MAX_PATH);
	cout<<"Install Path In Registry : " << path<<endl;

	cout<<endl<<"---------Shell Extension Installation status---------"<<endl;
	cout<<"Shell Extension CopyHook: Installed : " << ( isInstallAppControl() ? "true" : "false") <<endl;
	cout<< "Shell Extension CopyHook Installed : "<< (isInstallCopyHook() ? "true" : "false" ) <<endl;
}

void installAllComponent() {
	AppUtility::AppInstallValidate valiedate(VLAIDATE_NONE, SNOWMAN_STATUS_REGISTERED);
	valiedate.repair(true);
}

void uninstallAllComponent() {
	AppUtility::UninstallService();
	AppUtility::UninstallSPI();
}

