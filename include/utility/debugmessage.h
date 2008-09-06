#ifndef _UTILITY_DEBUG_MESSAGE_H__
#define _UTILITY_DEBUG_MESSAGE_H__

#ifndef _HIDE_DEBUG_MSG_ 
	#define DEBUG_MESSAGE(fmt) OutputDebugString(fmt)

	inline void ODS(TCHAR * fmt) {
		OutputDebugString(fmt);	
		OutputDebugString(_T("\n"));
	};

	inline void ODS2(TCHAR *fmt1, TCHAR *fmt2) {
		OutputDebugString(fmt1);						
		OutputDebugString(fmt2);					
		OutputDebugString(_T("\n"));				
	}

	
	#define DP1(fmt, var)							\
	{												\
		TCHAR sOut[256];							\
		_stprintf(sOut, fmt, var);					\
		OutputDebugString(sOut);					\
		OutputDebugString(_T("\n"));				\
	}

	#define DebugStringNoDres(msg)			\
		OutputDebugString(msg)				\
	
#else

	inline void ODS(TCHAR * fmt){}
	inline void ODS2(TCHAR *fmt1, TCHAR *fmt2){}
	#define DP1(fmt, x1)			
	#define DebugStringNoDres(msg)
	#define DEBUG_MESSAGE(fmt)
#endif

#endif  // _UTILITY_DEBUG_MESSAGE_H__