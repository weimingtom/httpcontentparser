// mvs.cpp : ����Ӧ�ó������ڵ㡣
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

// ���ļ�Ӧ������������
// 1. ���û�ж�س���ִ��֮�� ������������ִ�д˳��� ����ִ��ʱӦ������ȡ���Զ�����ע�����
// 2. �˳������ȿ����ļ����� /tmpĿ¼�£� ���ر�����
// 3. ��/tmp�����ļ�ɾ���ļ���
// Ϊ�������������̣� ������Ҫ����һЩ����
// ���⣬ ����Ӧ�����ж�һ���Ƿ���Ҫж�س��� ����ж�ͨ����ȡ�����ļ����
// ���û�и�ѡ����ֱ���˳��������κ�ͣ����

// �ؼ����⣺����û��������˴��ļ���ô���أ�
// ����ʱӦ��ʹ��ĳЩ��ʩ����Ԥ��
// 1. ���������
// 2. 

// ��ȡ�ļ�����

#define PARAM_TMP TEXT("")

TCHAR install_path[MAX_PATH] = {0};



// �����ļ���ָ��Ŀ¼�� ��ִ�г���
void CopyAndExec(HINSTANCE hInstance) {
	TCHAR newpath[MAX_PATH], dir[MAX_PATH];
	{
		// �����ļ�
		TCHAR name[MAX_PATH], tmp[MAX_PATH], path[MAX_PATH];
		GetModuleFileName((HMODULE)hInstance, path, MAX_PATH);
		GetFileName(path, name, MAX_PATH);
		GetTempPath(MAX_PATH, tmp);
		_sntprintf(newpath, MAX_PATH, "%s//%s", tmp, name);
		CopyFile(path, newpath, FALSE);

		// ��ȡ��װ·��
		GetFileNameDir(path, dir, MAX_PATH);
	}
	
	// ִ�п�����/tmp�µ��ļ�
	TCHAR cmdLine[MAX_PATH *2];
	_sntprintf(cmdLine, MAX_PATH *2, "%s %s%s", newpath, PARAM_TMP, dir);
	WinExec(cmdLine, SW_NORMAL);
}

bool testOnTmp(LPTSTR lpCmdLine) {
	if (_tcsstr(lpCmdLine, PARAM_TMP) == lpCmdLine) {
		// ��cmdline����ȡ����װ·��
		_tcscpy(install_path, &(lpCmdLine[_tcslen(PARAM_TMP)]));
		return true;
	} else {
		return false;
	}
}

void TermCOMService() {
	// ����ж��Servers
	AppUtility::UninstallService();

	// ǿ�ƹر�Service
	
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
	// ͨ��COM��ȡ�Ƿ���Ҫж��, �������ֱ���˳�
	if (false == checkUninstallStatus()) {
		return -1;
	}

	if (testOnTmp(lpCmdLine)) {
		Sleep(4000);
		TermCOMService();

		// ɾ���ļ���
		if (_tcslen(install_path) != 0) {
			DeleteFiles(install_path, "*");
		}
	} else {
		// ������ִ��
		CopyAndExec(hInstance);
	}		
}
