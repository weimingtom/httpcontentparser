#include "stdafx.h"
#include "./errorreport.h"
#include <sstream>
#include <DebugOutput.h>

namespace Family007{

static std::string genErrMsg(const int appcode) {
	std::stringstream s;
	return s.str();
}

void ErrorManagement::reportError(const char * winapi, const char  *function) {
	std::stringstream strError;
	strError<<"[Family007] Call WinAPI " <<winapi<<" Failed.(WinLastError : "<<GetLastError()<<")";

	_DEBUG_STREAM_TRC_(strError.str().c_str());
}

void ErrorManagement::reportError(const int appcode, const char  *function) {
}
};