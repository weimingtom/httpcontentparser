// mvs.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "mvs.h"
#include <stdio.h>
#include <stdlib.h>
#include <AppInstallValidate.h>
#include <apputility.h>
#include <com\comutility.h>
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>
#include <softwareStatus.h>

// 此文件应该又两个作用
// 1. 当用户卸载程序执行之后， 在重新启动后执行此程序， 程序执行时应该首先取消自动启动注册表项
// 2. 此程序首先拷贝文件到， /tmp目录下， 并关闭自身
// 3. 在/tmp下载文件删除文件。
// 为了区别整个过程， 我们需要出入一些参数
// 此外， 程序还应该在判断一次是否需要卸载程序， 这个判断通过读取配置文件完成
// 如果没有该选项则直接退出，不做任何停留。

// 关键问题：如果用户错误点击了此文件怎么办呢？
// 启动时应该使用某些措施进行预防
// 1. 传入参数？
// 2. 

// 获取文件名称

#define PARAM_TMP TEXT("")

TCHAR install_path[MAX_PATH] = {0};



// 拷贝文件到指定目录， 并执行程序
void CopyAndExec(HINSTANCE hInstance) {
	TCHAR newpath[MAX_PATH], dir[MAX_PATH];
	{
		// 拷贝文件
		TCHAR name[MAX_PATH], tmp[MAX_PATH], path[MAX_PATH];
		GetModuleFileName((HMODULE)hInstance, path, MAX_PATH);
		GetFileName(path, name, MAX_PATH);
		GetTempPath(MAX_PATH, tmp);
		_sntprintf(newpath, MAX_PATH, "%s//%s", tmp, name);
		CopyFile(path, newpath, FALSE);

		// 获取安装路径
		GetFileNameDir(path, dir, MAX_PATH);
	}
	
	// 执行拷贝到/tmp下的文件
	TCHAR cmdLine[MAX_PATH *2];
	_sntprintf(cmdLine, MAX_PATH *2, "%s %s%s", newpath, PARAM_TMP, dir);
	WinExec(cmdLine, SW_NORMAL);
}

bool testOnTmp(LPTSTR lpCmdLine) {
	if (_tcsstr(lpCmdLine, PARAM_TMP) == lpCmdLine) {
		// 从cmdline中提取出安装路径
		_tcscpy(install_path, &(lpCmdLine[_tcslen(PARAM_TMP)]));
		return true;
	} else {
		return false;
	}
}

void TermCOMService() {
	// 首先卸载Servers
	AppUtility::UninstallService();

	// 强制关闭Service
	
}

bool checkUninstallStatus() {
	AutoInitInScale _auto_scale_;
	ISnowmanSetting * pSetting = NULL;
	HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER,
		IID_ISnowmanSetting, (LPVOID*)&pSetting);
	if (FAILED(hr)) {
		return false;
	}

	LONG status;
	pSetting->getApplicationStatus(&status);
	pSetting->Release();

	if (SNOWMAN_STATUS_UNINSTALL == status) {
		return true;
	} else {
		return false;
	}
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	// 通过COM获取是否需要卸载, 如果不是直接退出
	if (false == checkUninstallStatus()) {
		return -1;
	}

	if (testOnTmp(lpCmdLine)) {
		Sleep(4000);
		TermCOMService();

		// 删除文件架
		if (_tcslen(install_path) != 0) {
			DeleteFiles(install_path, "*");
		}
	} else {
		// 拷贝并执行
		CopyAndExec(hInstance);
	}		
}
