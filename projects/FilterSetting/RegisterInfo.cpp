#include "StdAfx.h"
#include ".\registerinfo.h"
#include ".\globalvariable.h"
#include <utility\timeutility.h>
#include <time.h>

RegisterInfo::RegisterInfo(void)
{
}

RegisterInfo::~RegisterInfo(void)
{
}

void RegisterInfo::initialize() {
	getInstallTime();
}


bool RegisterInfo::registerSoft(const std::string & register_info) {
	return false;
}

bool RegisterInfo::trialEdition() {
	return false;
}

// 获取安装时间
void RegisterInfo::getInstallTime() {
		// 获取时间
	using namespace timeutility;
	tm t = timeutility::tmfromstring(g_configuration.getInstallDate()->getInstallDate().c_str());
	CTime config_time(_mktime64(&t));

	// 获取文件的创建时间
	TCHAR path[MAX_PATH];
	FILETIME create_time = {0}, LastAccessTime, modify_time;
	GetModuleFileName((HMODULE)g_hInstance, path, MAX_PATH);
	HANDLE hFile = CreateFile(path, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_DELETE,
		NULL, OPEN_ALWAYS, FILE_FLAG_BACKUP_SEMANTICS, NULL);
	if (INVALID_HANDLE_VALUE == hFile) {
		install_date = config_time;
		goto finished;
	}
	GetFileTime(hFile, &create_time, &LastAccessTime, &modify_time);
	CloseHandle(hFile);
	CTime createtime(create_time);

	if (createtime > config_time)
		install_date = createtime;
	else 
		install_date = config_time;
finished:
	g_configuration.getInstallDate()->setInstallDate((LPCTSTR)install_date.Format("%Y-%M-%D %h:%m:%s"));
}

bool RegisterInfo::trial_ended() {
	CTime now;
	now.GetCurrentTime();

	CTimeSpan ts = now - install_date;
	if (ts.GetDays() > 30) {
		return true;
	} else {
		return false;
	}
}