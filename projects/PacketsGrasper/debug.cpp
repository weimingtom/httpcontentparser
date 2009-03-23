#include "stdafx.h"
#include "debug.h"
#include <utility\syncutility.h>
#include <utility\debugmessage.h>
#include <fstream>
#include <string>
#include <exception>
#include <assert.h>
#include <comdef.h>
#include <stdlib.h>

#ifdef _SHOW_DETAIL
void PrintSocket(SOCKET s, DWORD bytes, TCHAR *sExt)
{
	SOCKADDR_IN local_addr, remote_addr;
	int local_addr_len	= sizeof(local_addr);
	int remote_addr_len = sizeof(remote_addr);
	getsockname(s, (SOCKADDR*)&local_addr, &local_addr_len);
 
	getpeername(s, (SOCKADDR*)&remote_addr, &remote_addr_len);

	const int bufsize = 2048;
	TCHAR sTemp[bufsize];
	_snprintf(sTemp, bufsize, "    Socket %u %s\n", s, sExt);
	OutputDebugString(sTemp);
	_snprintf(sTemp, bufsize, "    %u.%u.%u.%u:%u -> %u.%u.%u.%u:%u transfered %u bytes\n"
		, local_addr.sin_addr.S_un.S_un_b.s_b1
		, local_addr.sin_addr.S_un.S_un_b.s_b2
		, local_addr.sin_addr.S_un.S_un_b.s_b3
		, local_addr.sin_addr.S_un.S_un_b.s_b4
		, ntohs(local_addr.sin_port)
		, remote_addr.sin_addr.S_un.S_un_b.s_b1
		, remote_addr.sin_addr.S_un.S_un_b.s_b2
		, remote_addr.sin_addr.S_un.S_un_b.s_b3
		, remote_addr.sin_addr.S_un.S_un_b.s_b4
		, ntohs(remote_addr.sin_port)
		, bytes
		);
	OutputDebugString(sTemp);
}

void PrintReturnCode(int iReturnCode, LPINT lpErrno)
{
	const int bufsize = 2048;
	TCHAR sOutput[bufsize];
	LPCTSTR errorMsg = NULL, tmp = NULL;
	switch(iReturnCode)
	{
	case SOCKET_ERROR:
		errorMsg = "SOCKET_ERROR";
		break;
	case 0:
		errorMsg = "SOCKET_SUCCESS";
		break;
	default:
		errorMsg = "OTHER";
		break;
	}
	switch(*lpErrno)
	{
	case WSA_IO_PENDING:
		tmp = "WSA_IO_PENDING";
		break;
	default:
		tmp = "OTHER";
		break; 
	}
	_snprintf(sOutput, bufsize, "    ReturnCode: %s(%d); *lpErrno: %s(%d)\n"
		, errorMsg, iReturnCode, tmp, *lpErrno);
	OutputDebugString(sOutput);
}
 
void PrintProtocolInfo(
	IN	WSAPROTOCOL_INFOW	*pProtocolInfo, 
	IN	TCHAR				*sPathName
)
{
	const int bufsize = 2048;
	TCHAR sTemp[bufsize];

	OutputDebugString("  ProtocolInfo:\n");
	
	_sntprintf(sTemp, bufsize, "    LibraryPath: %s\n", sPathName);
	OutputDebugString(sTemp);

	_sntprintf(sTemp, bufsize, "    dwServiceFlags1: 0x%08X; %d\n"
		, pProtocolInfo->dwServiceFlags1
		, pProtocolInfo->dwServiceFlags1
		);
	OutputDebugString(sTemp);

	_sntprintf(sTemp, bufsize, "    dwServiceFlags2: 0x%08X; %d\n"
		, pProtocolInfo->dwServiceFlags2
		, pProtocolInfo->dwServiceFlags2
		);
	OutputDebugString(sTemp);

	_sntprintf(sTemp, bufsize, "    dwServiceFlags3: 0x%08X; %d\n"
		, pProtocolInfo->dwServiceFlags3
		, pProtocolInfo->dwServiceFlags3
		);
	OutputDebugString(sTemp);

	_sntprintf(sTemp, bufsize, "    dwServiceFlags4: 0x%08X; %d\n"
		, pProtocolInfo->dwServiceFlags4
		, pProtocolInfo->dwServiceFlags4
		);
	OutputDebugString(sTemp);

	_sntprintf(sTemp, bufsize, "    dwProviderFlags: 0x%08X; %d\n"
		, pProtocolInfo->dwProviderFlags
		, pProtocolInfo->dwProviderFlags
		);
	OutputDebugString(sTemp);

	_sntprintf(sTemp, bufsize, "    ProviderId: %08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X\n"
		, pProtocolInfo->ProviderId.Data1
		, pProtocolInfo->ProviderId.Data2
		, pProtocolInfo->ProviderId.Data3
		, pProtocolInfo->ProviderId.Data4[0]
		, pProtocolInfo->ProviderId.Data4[1]
		, pProtocolInfo->ProviderId.Data4[2]
		, pProtocolInfo->ProviderId.Data4[3]
		, pProtocolInfo->ProviderId.Data4[4]
		, pProtocolInfo->ProviderId.Data4[5]
		, pProtocolInfo->ProviderId.Data4[6]
		, pProtocolInfo->ProviderId.Data4[7]
		);
	OutputDebugString(sTemp);

	_sntprintf(sTemp, bufsize, "    dwCatalogEntryId: 0x%08X; %d\n"
		, pProtocolInfo->dwCatalogEntryId
		, pProtocolInfo->dwCatalogEntryId
		);
	OutputDebugString(sTemp);

	_sntprintf(sTemp, bufsize, "    ProtocolChain.ChainLen: 0x%08X; %d\n"
		, pProtocolInfo->ProtocolChain.ChainLen
		, pProtocolInfo->ProtocolChain.ChainLen
		);
	OutputDebugString(sTemp);


	sTemp[0] = '\0';
	memset(sTemp, 0, sizeof(sTemp));
	OutputDebugString("    ProtocolChain.ChainEntries: ");
	for(int i = 0; i < MAX_PROTOCOL_CHAIN; i++)
	{
		TCHAR s[bufsize];
		if(i == MAX_PROTOCOL_CHAIN - 1)
			_sntprintf(s, bufsize,"0x%08X\n", pProtocolInfo->ProtocolChain.ChainEntries[i]);
		else
			_sntprintf(s, bufsize,"0x%08X->", pProtocolInfo->ProtocolChain.ChainEntries[i]);
		
		_tcsncat(sTemp, s, bufsize);
	}
	OutputDebugString(sTemp);

	_sntprintf(sTemp, bufsize, "    iVersion: 0x%08X; %d\n"
		, pProtocolInfo->iVersion
		, pProtocolInfo->iVersion
		);
	OutputDebugString(sTemp);

	_sntprintf(sTemp, bufsize, "    iAddressFamily: 0x%08X; %d\n"
		, pProtocolInfo->iAddressFamily
		, pProtocolInfo->iAddressFamily
		);
	OutputDebugString(sTemp);

	_sntprintf(sTemp, bufsize, "    iMaxSockAddr: 0x%08X; %d\n"
		, pProtocolInfo->iMaxSockAddr
		, pProtocolInfo->iMaxSockAddr
		);
	OutputDebugString(sTemp);

	_sntprintf(sTemp, bufsize, "    iMinSockAddr: 0x%08X; %d\n"
		, pProtocolInfo->iMinSockAddr
		, pProtocolInfo->iMinSockAddr
		);
	OutputDebugString(sTemp);

	_sntprintf(sTemp, bufsize, "    iSocketType: 0x%08X; %d\n"
		, pProtocolInfo->iSocketType
		, pProtocolInfo->iSocketType
		);
	OutputDebugString(sTemp);

	_sntprintf(sTemp, bufsize, "    iProtocol: 0x%08X; %d\n"
		, pProtocolInfo->iProtocol
		, pProtocolInfo->iProtocol
		);
	OutputDebugString(sTemp);

	_sntprintf(sTemp, bufsize, "    iProtocolMaxOffset: 0x%08X; %d\n"
		, pProtocolInfo->iProtocolMaxOffset
		, pProtocolInfo->iProtocolMaxOffset
		);
	OutputDebugString(sTemp);

	_sntprintf(sTemp, bufsize, "    iNetworkByteOrder: 0x%08X; %d\n"
		, pProtocolInfo->iNetworkByteOrder
		, pProtocolInfo->iNetworkByteOrder
		);
	OutputDebugString(sTemp);

	_sntprintf(sTemp, bufsize, "    iSecurityScheme: 0x%08X; %d\n"
		, pProtocolInfo->iSecurityScheme
		, pProtocolInfo->iSecurityScheme
		);
	OutputDebugString(sTemp);

	_sntprintf(sTemp, bufsize, "    dwMessageSize: 0x%08X; %d\n"
		, pProtocolInfo->dwMessageSize
		, pProtocolInfo->dwMessageSize
		);
	OutputDebugString(sTemp);

	_sntprintf(sTemp, bufsize, "    dwProviderReserved: 0x%08X; %d\n"
		, pProtocolInfo->dwProviderReserved
		, pProtocolInfo->dwProviderReserved
		);
	OutputDebugString(sTemp);

	_tcsncpy(sTemp, (TCHAR*)_bstr_t(pProtocolInfo->szProtocol), bufsize);
	OutputDebugString("    szProtocol: ");
	OutputDebugString(sTemp);
	OutputDebugString("\n"); 
}
void PrintRecvBuffer(char *recv_buf, DWORD dwRecv, SOCKET s, const std::string &LOG_NAME) {
	try {
		const int BUF_SIZE = 1024;
		TCHAR buf[BUF_SIZE];
		_sntprintf(buf, BUF_SIZE, 
			"=================Recv bytes : %d, socket: %d=============\n", dwRecv, s);
		OutputDebugString("PrintRecvBuffer"); 
	} catch(...) {
	}
}

#else
void PrintRecvBuffer(char *recv_buf, DWORD dwRecv, SOCKET s, const std::string &LOG_NAME) {}
void PrintReturnCode(int iReturnCode, LPINT lpErrno){}
void PrintSocket(SOCKET s, DWORD bytes, TCHAR *sExt){}
void PrintProtocolInfo(
	IN	WSAPROTOCOL_INFOW	*pProtocolInfo, 
	IN	TCHAR				*sPathName
	) {
	};
#endif

void DumpBuf(WSABUF *buf, const int count, const std::string &filename) {
	using namespace std;
	try {
		// 打开文件
		fstream out;
		out.open(filename.c_str(), std::ios::out | std::ios::app | std::ios::binary);

		// 写入缓冲区
		assert (buf != NULL);
		for (int i = 0; i < count; ++i) {
			out.write(buf[i].buf, buf[i].len);
		}
		
		// 关闭文件
		out.clear();
	} catch(exception&) {
	}
}

// 将字符串写入文件
void DumpToFile(const char * buf, const int len, const std::string &filename) {
	using namespace yanglei_utility;
	using namespace std;
	static yanglei_utility::CAutoCreateCS cs_;
	SingleLock<CAutoCreateCS> lock(&cs_);

	try {
		fstream out;
		out.open(filename.c_str(), std::ios::out | std::ios::app | std::ios::binary);
		out.write(buf, len);
		out.clear();
	} catch(exception&) {
	}
}