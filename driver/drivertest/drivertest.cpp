// drivertest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DriverMngr.h"
#include <DebugOutput.h>

class MyCheck : public CheckProcessCreate {
public:
	MyCheck() {
		a = 0;
	}
	virtual bool enable_process_create(const char * process_path_name) {
		a++;
		if (a % 2== 0) {
			_DEBUG_STREAM_TRC_("MyCheck ===============" << a);
			return true;
		} else {
			_DEBUG_STREAM_TRC_("MyCheck ++++++++++++++" << a);
			return false;
		}
	}
private:
	int a;
}g_checker;

AppController g_controller(&g_checker);

int _tmain(int argc, _TCHAR* argv[])
{
	g_controller.begin();

	int a ;
	std::cin>>a;
	g_controller.end();
	return 0;
}

