#ifndef _PACKETS_GRASPER_DEBUG_H__
#define _PACKETS_GRASPER_DEBUG_H__

#include <string>
#include <logutility.h>


extern TCHAR 	m_sProcessName[MAX_PATH];


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

void DumpBuf(WSABUF *buf, const int count,const std::string &filename);
void DumpToFile(const char * buf, const int len, const std::string &filename);

#endif  // _PACKETS_GRASPER_DEBUG_H__

