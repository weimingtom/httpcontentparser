#include "stdafx.h"
#include "debug.h"
#include "logutility.h"
#include <utility\syncutility.h>
#include <utility\debugmessage.h>
#include <exception>
#ifdef _SHOW_DETAIL

void PrintSocket(SOCKET s, DWORD bytes, TCHAR *sExt)
{
	SOCKADDR_IN local_addr, remote_addr;
	int local_addr_len	= sizeof(local_addr);
	int remote_addr_len = sizeof(remote_addr);
	getsockname(s, (SOCKADDR*)&local_addr, &local_addr_len);
 
	getpeername(s, (SOCKADDR*)&remote_addr, &remote_addr_len);

	CString sTemp;
	sTemp.Format("    Socket %u %s\n", s, sExt);
	OutputDebugString(sTemp);
	sTemp.Format("    %u.%u.%u.%u:%u -> %u.%u.%u.%u:%u transfered %u bytes\n"
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
	CString sOutput , sTemp, sTemp1;
	switch(iReturnCode)
	{
	case SOCKET_ERROR:
		sTemp = "SOCKET_ERROR";
		break;
	case 0:
		sTemp = "SOCKET_SUCCESS";
		break;
	default:
		sTemp = "OTHER";
		break;
	}
	switch(*lpErrno)
	{
	case WSA_IO_PENDING:
		sTemp1 = "WSA_IO_PENDING";
		break;
	default:
		sTemp1 = "OTHER";
		break; 
	}
	sOutput.Format("    ReturnCode: %s(%d); *lpErrno: %s(%d)\n"
		, sTemp, iReturnCode, sTemp1, *lpErrno);
	OutputDebugString(sOutput);
}
 
void PrintProtocolInfo(
	IN	WSAPROTOCOL_INFOW	*pProtocolInfo, 
	IN	TCHAR				*sPathName
)
{
	OutputDebugString("  ProtocolInfo:\n");
	CString sTemp, sOutput;
	sTemp.Format("    LibraryPath: %s\n", sPathName);
	OutputDebugString(sTemp);

	sTemp.Format("    dwServiceFlags1: 0x%08X; %d\n"
		, pProtocolInfo->dwServiceFlags1
		, pProtocolInfo->dwServiceFlags1
		);
	OutputDebugString(sTemp);

	sTemp.Format("    dwServiceFlags2: 0x%08X; %d\n"
		, pProtocolInfo->dwServiceFlags2
		, pProtocolInfo->dwServiceFlags2
		);
	OutputDebugString(sTemp);

	sTemp.Format("    dwServiceFlags3: 0x%08X; %d\n"
		, pProtocolInfo->dwServiceFlags3
		, pProtocolInfo->dwServiceFlags3
		);
	OutputDebugString(sTemp);

	sTemp.Format("    dwServiceFlags4: 0x%08X; %d\n"
		, pProtocolInfo->dwServiceFlags4
		, pProtocolInfo->dwServiceFlags4
		);
	OutputDebugString(sTemp);

	sTemp.Format("    dwProviderFlags: 0x%08X; %d\n"
		, pProtocolInfo->dwProviderFlags
		, pProtocolInfo->dwProviderFlags
		);
	OutputDebugString(sTemp);

	sTemp.Format("    ProviderId: %08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X\n"
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

	sTemp.Format("    dwCatalogEntryId: 0x%08X; %d\n"
		, pProtocolInfo->dwCatalogEntryId
		, pProtocolInfo->dwCatalogEntryId
		);
	OutputDebugString(sTemp);

	sTemp.Format("    ProtocolChain.ChainLen: 0x%08X; %d\n"
		, pProtocolInfo->ProtocolChain.ChainLen
		, pProtocolInfo->ProtocolChain.ChainLen
		);
	OutputDebugString(sTemp);

	sTemp.Empty();
	OutputDebugString("    ProtocolChain.ChainEntries: ");
	for(int i = 0; i < MAX_PROTOCOL_CHAIN; i++)
	{
		CString s = "";
		if(i == MAX_PROTOCOL_CHAIN - 1)
			s.Format("0x%08X\n", pProtocolInfo->ProtocolChain.ChainEntries[i]);
		else
			s.Format("0x%08X->", pProtocolInfo->ProtocolChain.ChainEntries[i]);
		sTemp += s;
	}
	OutputDebugString(sTemp);

	sTemp.Format("    iVersion: 0x%08X; %d\n"
		, pProtocolInfo->iVersion
		, pProtocolInfo->iVersion
		);
	OutputDebugString(sTemp);

	sTemp.Format("    iAddressFamily: 0x%08X; %d\n"
		, pProtocolInfo->iAddressFamily
		, pProtocolInfo->iAddressFamily
		);
	OutputDebugString(sTemp);

	sTemp.Format("    iMaxSockAddr: 0x%08X; %d\n"
		, pProtocolInfo->iMaxSockAddr
		, pProtocolInfo->iMaxSockAddr
		);
	OutputDebugString(sTemp);

	sTemp.Format("    iMinSockAddr: 0x%08X; %d\n"
		, pProtocolInfo->iMinSockAddr
		, pProtocolInfo->iMinSockAddr
		);
	OutputDebugString(sTemp);

	sTemp.Format("    iSocketType: 0x%08X; %d\n"
		, pProtocolInfo->iSocketType
		, pProtocolInfo->iSocketType
		);
	OutputDebugString(sTemp);

	sTemp.Format("    iProtocol: 0x%08X; %d\n"
		, pProtocolInfo->iProtocol
		, pProtocolInfo->iProtocol
		);
	OutputDebugString(sTemp);

	sTemp.Format("    iProtocolMaxOffset: 0x%08X; %d\n"
		, pProtocolInfo->iProtocolMaxOffset
		, pProtocolInfo->iProtocolMaxOffset
		);
	OutputDebugString(sTemp);

	sTemp.Format("    iNetworkByteOrder: 0x%08X; %d\n"
		, pProtocolInfo->iNetworkByteOrder
		, pProtocolInfo->iNetworkByteOrder
		);
	OutputDebugString(sTemp);

	sTemp.Format("    iSecurityScheme: 0x%08X; %d\n"
		, pProtocolInfo->iSecurityScheme
		, pProtocolInfo->iSecurityScheme
		);
	OutputDebugString(sTemp);

	sTemp.Format("    dwMessageSize: 0x%08X; %d\n"
		, pProtocolInfo->dwMessageSize
		, pProtocolInfo->dwMessageSize
		);
	OutputDebugString(sTemp);

	sTemp.Format("    dwProviderReserved: 0x%08X; %d\n"
		, pProtocolInfo->dwProviderReserved
		, pProtocolInfo->dwProviderReserved
		);
	OutputDebugString(sTemp);

	sTemp = pProtocolInfo->szProtocol;
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
		ODS("PrintRecvBuffer"); 
		g_logger.beginWrite(RECV_LOG);
		g_logger.write(buf, _tcslen(buf), RECV_LOG);
		g_logger.write(recv_buf, dwRecv, RECV_LOG);
		//g_logger.endWrite(RECV_LOG);
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

 
LogUtility	g_logger;
 
void InitializeLog() {
	g_logger.InitLogger(RECV_LOG, RECV_LOG_FILE);
	g_logger.InitLogger(EXCEPTION_LOG, EXCEPTION_LOG_FILE);
}
void UninitializeLog() {
	g_logger.destroyAll();
}

void writeException(const char * func_name, char * exception_descritpion) {
	using namespace yanglei_utility;
	static yanglei_utility::CAutoCreateCS cs_;
	SingleLock<CAutoCreateCS> lock(&cs_);

	char buffer[1024];
	_snprintf(buffer, 1024, "\nException Occor in %s, Description : %s\n", 
		func_name, exception_descritpion);
	g_logger.beginWrite(EXCEPTION_LOG);
	g_logger.write(buffer, _tcslen(buffer), EXCEPTION_LOG);
	g_logger.endWrite(EXCEPTION_LOG);
}

void DumpBuf(WSABUF *buf, const int count, const std::string &filename) {
	using namespace std;
	try {
		// 打开文件
		fstream out;
		out.open(filename.c_str(), std::ios::out | std::ios::app);

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
		out.open(filename.c_str(), std::ios::out | std::ios::app);
		out.write(buf, len);
		out.clear();
	} catch(exception&) {
	}
}