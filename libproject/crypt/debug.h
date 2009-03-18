#ifndef _CRYPT_DEBUG_H__
#define _CRYPT_DEBUG_H__


#ifndef _NO_OUTPUT_DEBUG 
	inline void MyHandleError(LPTSTR psz, int nErrorNumber)
	{
		TCHAR buffer[255];
		sprintf(buffer, TEXT("An error occurred in the program. \n"));
		OutputDebugString(buffer);
		sprintf(buffer,  TEXT("%s\n"), psz);
		OutputDebugString(buffer);
		sprintf(buffer, TEXT("Error number %x.\n"), nErrorNumber);
		OutputDebugString(buffer);
	}
#else
inline void MyHandleError(LPTSTR psz, int nErrorNumber) {}
#endif

#endif 