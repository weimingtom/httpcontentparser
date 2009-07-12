#ifndef _ERROR_CODE_H__
#define _ERROR_CODE_H__

namespace Family007 {

class ErrorCode {
public:
	// error number
	static const int ERROR_SCM_MANAGER = 1000;
	static const int ERROR_OPEN_DEVICE_FAILED = ERROR_SCM_MANAGER;
	static const int ERROR_OPEN_SCMGR_FAILED = ERROR_OPEN_DEVICE_FAILED + 1;
	static const int ERROR_START_SERVICE_FAILED = ERROR_OPEN_SCMGR_FAILED+1;
	static const int ERROR_CREATE_SERVICE_FAILED = ERROR_START_SERVICE_FAILED+1;
	static const int ERROR_OPEN_SERVICE_FAILED = ERROR_CREATE_SERVICE_FAILED+1;
	static const int ERROR_CONTROL_SERVICE_FAILED = ERROR_OPEN_SERVICE_FAILED+1;
	static const int ERROR_DELETE_SERVICE_FAILED = ERROR_CONTROL_SERVICE_FAILED+1;

	// level
	static const int ERROR_LEVEL_FATAL = 0;
	static const int ERROR_LEVEL_EFFECT = 1;
public:
	static void reportError(const int code, 
		const int level, 
		const char * error_msg, 
		const char * detail_msg, 
		const char * function_name) {
		}

		static void reportError(const int code, 
			const int level, 
			const char * error_msg, 
			const char * detail_msg, 
			const int window_error,
			const char * function_name) {
			}
};
};

#define REPORT_FATAL_ERROR_WITH_ERRNO(rc, title, detail, function)  using Family007::ErrorCode;\
		Family007::ErrorCode::reportError(rc, ErrorCode::ERROR_LEVEL_FATAL, \
		title, detail, GetLastError(), __FUNCTION__);


#endif  // _ERROR_CODE_H__