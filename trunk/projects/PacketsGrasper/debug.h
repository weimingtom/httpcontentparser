#ifndef _PACKETS_GRASPER_DEBUG_H__
#define _PACKETS_GRASPER_DEBUG_H__

#include <string>

#ifndef __HIDE_SPI_FUNCTION_CALL__
#define SPI_FUNCTION_CALL(msg) OutputDebugString(msg)
#else
#define SPI_FUNCTION_CALL(msg)
#endif


extern TCHAR 	m_sProcessName[MAX_PATH];


void PrintRecvBuffer(char *buffer, DWORD dwRecv, SOCKET s, const std::string &LOG_NAME);
void PrintReturnCode(int iReturnCode, LPINT lpErrno);
void PrintSocket(SOCKET s, DWORD bytes, TCHAR *sExt);
void PrintProtocolInfo(IN	WSAPROTOCOL_INFOW	*pProtocolInfo, 
	IN	TCHAR				*sPathName);

void DumpBuf(WSABUF *buf, const int count, const std::string &filename);


#ifdef __ENABLE_DUMP_HTTP_REQUEST__
#define DUMP_HTTP_REQUEST(a, b, c)	DumpBuf(a, b, c)
#else
#define DUMP_HTTP_REQUEST(a, b, c)
#endif


#endif  // _PACKETS_GRASPER_DEBUG_H__

