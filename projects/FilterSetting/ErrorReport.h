#ifndef _ERROR_CODE_H__
#define _ERROR_CODE_H__

#include <string>

namespace Family007 {

	class ErrorManagement {
	public:
		// error number
		enum {
			ERROR_SMC_OPEN_SCMGR_FAILED ,
			ERROR_SMC_OPEN_SERVICE_FAILED ,
			ERROR_SMC_START_SERVICE_FAILED,
			ERROR_SMC_CREATE_SERVICE_FAILED,
			ERROR_SMC_CONTROL_SERVICE_STOP_FAILED ,
			ERROR_SMC_CONTROL_STOP_TIMEOUT ,
			ERROR_SMC_DELETE_SERVICE_FAILED ,
			ERROR_SMC_QUERY_STATUX_EX_FAILED,
			ERROR_DRIVER_OPEN_DEVICE_FAILED ,
		};

		// level
		enum {
		ERROR_LEVEL_FATAL,
		ERROR_LEVEL_EFFECT
		};

	public:
		static void reportError(const char * winapi, const char  *function);
		static void reportError(const INT_PTR appcode, const char  *function);
	private:
		static std::string genErrMsg(const INT_PTR appcode);
	};
};

#define REPORT_WINAPI_ERROR(APINAME)  Family007::ErrorManagement::reportError(APINAME, __FUNCTION__);
#define REPORT_FAMILY007_ERROR(ERRORCODE)  Family007::ErrorManagement::reportError(ERRORCODE, __FUNCTION__);

#endif  // _ERROR_CODE_H__