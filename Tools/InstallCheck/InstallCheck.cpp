// InstallCheck.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <comdef.h>
#include <com\comutility.h>
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <shell\shellutility.h>

using namespace std;

void GetCOMPath(TCHAR *path, const int len) {
	AutoInitInScale auto_;
	try {
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


int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Check Websnow Installation status:"<<endl;
	
	cout<<endl<<"--------- Installation path  status---------"<<endl;
	// 获取安装路径
	{
		TCHAR path[MAX_PATH];
		GetInstallPathFromRegistry(path, MAX_PATH);
		cout<<"Install Path In Registry : " << path<<endl;

		GetCOMPath(path, MAX_PATH);
		cout<<"COM Service Location path : "<< path<<endl;
	}
	

	// 检测SPI的安装

	// 检测ShellExt的安装
	cout<<endl<<"---------Shell Extension Installation status---------"<<endl;
	cout<<"Shell Extension CopyHook: Installed : " << ( isInstallAppControl() ? "true" : "false") <<endl;
	cout<< "Shell Extension CopyHook Installed : "<< (isInstallCopyHook() ? "true" : "false" ) <<endl;
	return 0;
}

