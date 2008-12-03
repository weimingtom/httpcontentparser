#ifndef _PACKETS_GRASPER_DEBUG_H__
#define _PACKETS_GRASPER_DEBUG_H__

#include <string>
extern TCHAR 	m_sProcessName[MAX_PATH];


void PrintRecvBuffer(char *buffer, DWORD dwRecv, SOCKET s, const std::string &LOG_NAME);
void PrintReturnCode(int iReturnCode, LPINT lpErrno);
void PrintSocket(SOCKET s, DWORD bytes, TCHAR *sExt);
void PrintProtocolInfo(IN	WSAPROTOCOL_INFOW	*pProtocolInfo, 
	IN	TCHAR				*sPathName);

#endif  // _PACKETS_GRASPER_DEBUG_H__

