#ifndef _PACKETS_GRASPER_DEBUG_H__
#define _PACKETS_GRASPER_DEBUG_H__

#include <string>
#include <logutility.h>

extern TCHAR 	m_sProcessName[MAX_PATH];
#ifdef _DEBUG 
 
	inline void ODS(TCHAR * fmt) {
		TCHAR buffer[MAX_PATH];
		if (_tcslen(m_sProcessName) != 0) {
			TCHAR driver[MAX_PATH], dir[MAX_PATH], fname[MAX_PATH], ext[MAX_PATH];
			_splitpath(m_sProcessName, driver, dir, fname, ext);
			_sntprintf(buffer, MAX_PATH, 
				"***PacketsGrasper.dll in process %s.%s ***",
				fname, ext);
		} else {
			_snprintf(buffer, MAX_PATH, "***PacketsGrasper.dll in process??? ***");
		}
		OutputDebugString(buffer);
		OutputDebugString(fmt);	
		OutputDebugString(_T("\n"));
	};

	inline void ODS2(TCHAR *fmt1, TCHAR *fmt2) {
		OutputDebugString(" ***PacketsGrasper.dll*** ");	
		OutputDebugString(fmt1);						
		OutputDebugString(fmt2);					
		OutputDebugString(_T("\n"));				
	}

	
	#define DP1(fmt, var)							\
	{												\
		OutputDebugString(" ***PacketsGrasper.dll*** ");	\
		TCHAR sOut[256];							\
		_stprintf(sOut, fmt, var);					\
		OutputDebugString(sOut);					\
		OutputDebugString(_T("\n"));				\
	}

	inline void DebugStringNoDres(TCHAR *msg) {
		OutputDebugString(msg);
	}
	
#else

	inline void ODS(TCHAR * fmt){}
	inline void ODS2(TCHAR *fmt1, TCHAR *fmt2){}
	#define DP1(fmt, x1)			
	inline void DebugStringNoDres(TCHAR *msg) {}
#endif

void PrintRecvBuffer(char *buffer, DWORD dwRecv, SOCKET s, const std::string &LOG_NAME);
void PrintReturnCode(int iReturnCode, LPINT lpErrno);
void PrintSocket(SOCKET s, DWORD bytes, TCHAR *sExt);
void PrintProtocolInfo(IN	WSAPROTOCOL_INFOW	*pProtocolInfo, 
	IN	TCHAR				*sPathName);

#define RECV_LOG  ("LOG_RECV")
#define RECV_LOG_FILE  ("F:\\project\\net\\recv.log")

// 记录异常发生的LOG及LOG文件
#define EXCEPTION_LOG		("LOG_EXCEPTION")
#define EXCEPTION_LOG_FILE  ("F:\\project\\net\\PGException.log")
void writeException(const char * FunctionName, char * exception_descritpion);

void InitializeLog();
void UninitializeLog();

extern LogUtility				g_logger;

#endif  // _PACKETS_GRASPER_DEBUG_H__

