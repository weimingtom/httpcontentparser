#include "stdafx.h"
#include "selectio.h"
#include "debug.h" 
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <dnsmap.h>
#include <string>
#include <serviceUtility.h>
#include <utility\debugmessage.h>
#include <utility\fd_set_utility.h>
#include <utility\HttpPacket.h>
#include <utility\HTTPRequestPacket.h>
#include <utility\dns.h>
#include <logdebug.h>
#include <app_constants.h>
#include <AppinstallValidate.h>
#include <softwareStatus.h>
#include <DebugOutput.h>
#include ".\log.h"

#pragma data_seg(".inidata")
	int				m_iRefCount		= 0;
#pragma data_seg()

const int BUF_SIZE = 1024 * 1024;
char global_buffer[BUF_SIZE] = {0};

// 进程内全局变量  
WSPUPCALLTABLE		MainUpCallTable;
CRITICAL_SECTION	gCriticalSection;			// 代码段保护变量
WSPPROC_TABLE		NextProcTable;				// 保存30个服务提供者指针
TCHAR				m_sProcessName[MAX_PATH];	// 保存当前进程名称

#define __OUTPUT_DEBUG_CALL__	  _DEBUG_STREAM_TRC_("[PacketGrasper Fucntion Trace] "<<__FUNCTION__);
#define PACKETGRASPER_TRC(FMT)	_DEBUG_STREAM_TRC_("[PacketGrasper] "<< FMT);

//CSelectIO g_select;

//ProgressCheck progress_check;


void ShowAllSOCKET(const char *buf, fd_set *readfds) {
	if (readfds == NULL) return;

	char buffer[10240];
	strncpy(buffer, buf, 10240); 

	if (readfds->fd_count == 0) {
		_snprintf(buffer, 10240, "%s No Socket", buffer);
	}

	for (unsigned int i = 0; i < readfds->fd_count; ++i) {
		_snprintf(buffer, 10240, "%s %d", buffer, readfds->fd_array[i]);
	}
	OutputDebugString(buffer);
}
 
//——————————————————————————————————————
// 私有函数
void GetRightEntryIdItem(
	IN	WSAPROTOCOL_INFOW	*pProtocolInfo, 
	OUT	TCHAR				*sItem
)
{
	if(pProtocolInfo->ProtocolChain.ChainLen <= 1)
		_stprintf(sItem, _T("%u"), pProtocolInfo->dwCatalogEntryId);
	else
		_stprintf(sItem, _T("%u"), pProtocolInfo->ProtocolChain
			.ChainEntries[pProtocolInfo->ProtocolChain.ChainLen - 1]);
}
 
BOOL GetHookProvider(
	IN	WSAPROTOCOL_INFOW	*pProtocolInfo,
	OUT	TCHAR				*sPathName
)
{
	TCHAR sItem[21];
	GetRightEntryIdItem(pProtocolInfo, sItem);

	HKEY	hSubkey;
	DWORD	ulDateLenth	= MAX_PATH;
	TCHAR	sTemp[MAX_PATH];

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE
		, REG_INSTALL_KEY, 0, KEY_ALL_ACCESS, &hSubkey) != ERROR_SUCCESS)
		return FALSE;
	if (RegQueryValueEx(hSubkey, sItem, 0, NULL, (BYTE*)sTemp, &ulDateLenth)
		|| ExpandEnvironmentStrings(sTemp, sPathName, ulDateLenth) == 0)
		return FALSE;
	if(sPathName[0] == '\0' && sTemp[0] != '\0')
		_tcscpy(sPathName, sTemp);
	RegCloseKey(hSubkey);

	return TRUE;
}

//——————————————————————————————————————
// Winsock 2 服务提供者钩子函数

// WSPSelect函数的实现
// 我们不需要
int WSPAPI WSPSelect (
  int			nfds,                             
  fd_set FAR *	readfds,                 
  fd_set FAR *	writefds,                
  fd_set FAR *	exceptfds,               
  const struct	timeval FAR * timeout,     
  LPINT			lpErrno                         
) 
{
	__OUTPUT_DEBUG_CALL__;

	// 如果应用程序是一个不应该被拦截的应用程序
	//if (progress_check.isEnabled())
	return NextProcTable.lpWSPSelect(nfds, 
				readfds, writefds, exceptfds, timeout, lpErrno);

	// 如果在White DNS List, 我们也应该直接返回 ;)
	// 直接返回，自身填入select
	/*int result = g_select.preselect(readfds);
	if (0 == result) {
		// firefox都是NULL
		// 为何要清空？
		// 清空也没事情，最多延缓写操作以及异常操作
		if (writefds != NULL)
			FD_ZERO(writefds);
		if (exceptfds != NULL)
			FD_ZERO(exceptfds);
		if (lpErrno != NULL)
			*lpErrno = 0;
		return readfds->fd_count;
	} 

	int iRet = NextProcTable.lpWSPSelect(nfds, 
				readfds, writefds, exceptfds, timeout, lpErrno); 

	g_select.postselect(readfds); 
	return iRet;*/
} 

int WSPAPI WSPRecv(
	SOCKET			s,
	LPWSABUF		lpBuffers,
	DWORD			dwBufferCount,
	LPDWORD			lpNumberOfBytesRecvd,
	LPDWORD			lpFlags,
	LPWSAOVERLAPPED	lpOverlapped,
	LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
	LPWSATHREADID	lpThreadId, 
	LPINT			lpErrno
)
{
	__OUTPUT_DEBUG_CALL__;
	__AUTO_FUNCTION_SCOPE_TRACE__;
	return NextProcTable.lpWSPRecv(s, lpBuffers, dwBufferCount
				, lpNumberOfBytesRecvd, lpFlags, lpOverlapped
				, lpCompletionRoutine, lpThreadId, lpErrno);

	// 如果应用程序是一个不应该被拦截的应用程序
	//if (progress_check.isEnabled())
	//	return NextProcTable.lpWSPRecv(s, lpBuffers, dwBufferCount
	//			, lpNumberOfBytesRecvd, lpFlags, lpOverlapped
	//			, lpCompletionRoutine, lpThreadId, lpErrno);

	//char buffer[1024];
	//sprintf(buffer, "WSPRecv %d", s);
	//OutputDebugString(buffer);
	/*try { 
		// 对于使用MSG_PEEK抓取的方式
		if ((*lpFlags) & MSG_PEEK) {
			return NextProcTable.lpWSPRecv(s, lpBuffers, dwBufferCount
				, lpNumberOfBytesRecvd, lpFlags, lpOverlapped
				, lpCompletionRoutine, lpThreadId, lpErrno);
		}
		
		const int result = g_select.prerecv(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd);
		if (result == 0) {
			// 如果受到了包，就直接返回
			return 0; 
		}

		int iRet = NextProcTable.lpWSPRecv(s, lpBuffers, dwBufferCount
				, lpNumberOfBytesRecvd, lpFlags, lpOverlapped
				, lpCompletionRoutine, lpThreadId, lpErrno);
 
		return iRet;
	} catch (...) { 
		return SOCKET_ERROR; 
	}*/
}


//=======================================================================
SOCKET WSPAPI WSPSocket(
	int			af,                               
	int			type,                             
	int			protocol,                         
	LPWSAPROTOCOL_INFOW lpProtocolInfo,   
	GROUP		g,                              
	DWORD		dwFlags,                        
	LPINT		lpErrno
)
{
	__OUTPUT_DEBUG_CALL__
	return NextProcTable.lpWSPSocket(af, type
		, protocol, lpProtocolInfo, g, dwFlags, lpErrno);
}

int WSPAPI WSPCloseSocket(
	SOCKET		s,
	LPINT		lpErrno
) 
{ 
	__OUTPUT_DEBUG_CALL__
	//g_select.onCloseSocket(s);
	//char buffer[1024];
	//sprintf(buffer, "CloseSocket %d", s);
	//OutputDebugString(buffer);
	return NextProcTable.lpWSPCloseSocket(s, lpErrno);
}

int WSPAPI WSPConnect(
	SOCKET			s,
	const struct	sockaddr FAR * name,
	int				namelen,
	LPWSABUF		lpCallerData,
	LPWSABUF		lpCalleeData,
	LPQOS			lpSQOS,
	LPQOS			lpGQOS,
	LPINT			lpErrno
)
{
	__OUTPUT_DEBUG_CALL__;
	__AUTO_FUNCTION_SCOPE_TRACE__;

	// 修复
	// 注意hModule不能传NULL,  应该如果传NULL，
	// 应为NULL则获取到的线程为调用者线程的exe
	static bool repaired = false;
	if (!repaired) {
		CoInitialize(NULL);
		// 获取应用程序状态
		LONG app_status = SNOWMAN_STATUS_TRIAL;
		try {
			ISnowmanSetting * pSetting = NULL;
			HRESULT hr = CoCreateInstance(CLSID_SnowmanSetting, NULL, CLSCTX_LOCAL_SERVER, IID_ISnowmanSetting, (LPVOID*)&pSetting);
			if (SUCCEEDED(hr)) {
				pSetting->getApplicationStatus(&app_status);
			} else {
				PACKETGRASPER_TRC("["<<__FUNCTION__<<"] FAILED On Create snowman with HRESULT VALUE " <<std::hex<<hr);  
			}
		} catch (...) {
			PACKETGRASPER_TRC("["<<__FUNCTION__<<"] catch...");  
		}


		repaired = true;
		AppUtility::AppInstallValidate validator(VALIDATE_SPI, app_status);
		//validator.repair((HMODULE)hModule);
		CoUninitialize();
	}

	return NextProcTable.lpWSPConnect(s, name, namelen, lpCallerData
		, lpCalleeData, lpSQOS, lpGQOS, lpErrno);
}

SOCKET WSPAPI WSPAccept(
	SOCKET			s,
	struct sockaddr FAR *addr,
	LPINT			addrlen,
	LPCONDITIONPROC	lpfnCondition,
	DWORD			dwCallbackData,
	LPINT			lpErrno
)
{
	__OUTPUT_DEBUG_CALL__
	return NextProcTable.lpWSPAccept(s, addr, addrlen, lpfnCondition
		, dwCallbackData, lpErrno);
}

int WSPAPI WSPSend(
	SOCKET			s,
	LPWSABUF		lpBuffers,
	DWORD			dwBufferCount, 
	LPDWORD			lpNumberOfBytesSent,
	DWORD			dwFlags,
	LPWSAOVERLAPPED	lpOverlapped,
	LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
	LPWSATHREADID	lpThreadId,
	LPINT			lpErrno
)
{
	__OUTPUT_DEBUG_CALL__;
	__AUTO_FUNCTION_SCOPE_TRACE__;

	HTTPRequestPacket packet;

	int item_count = packet.parsePacket(lpBuffers, dwBufferCount);
	if (item_count < 2) {
		PACKETGRASPER_TRC("NOT A HTTP Request ");
		goto return_dir;
	}

	
	// 将DNS保存在DNS MAP当中
	char host[MAX_PATH], oper[MAX_PATH];
	packet.getHost(host, MAX_PATH);
	packet.getGET(oper, MAX_PATH);
	//g_select.addDNS(s, host);

	//sprintf(host, "D:\\req\\%d.log", s);
	//DumpBuf(lpBuffers, dwBufferCount, host);

	// 检查IP是否正常，如果可以则通过，否则直接返回错误
	LTRC_<<"Send HTTP Request to " << host;
	if (packet.openPage() == true) {
		if (accessNetword() && checkHTTPRequest(&packet)){
			PACKETGRASPER_TRC("HTTP Request passed"); 			 
			goto return_dir;
		} else {
			PACKETGRASPER_TRC("HTTP Request Blocked"); 			 
			*lpErrno = WSAETIMEDOUT;
			return SOCKET_ERROR;
		}
	} else {
		PACKETGRASPER_TRC("Don't open page");
	}

return_dir:
	return NextProcTable.lpWSPSend(s, lpBuffers, dwBufferCount
			, lpNumberOfBytesSent, dwFlags, lpOverlapped
			, lpCompletionRoutine, lpThreadId, lpErrno);
}
 
int WSPAPI WSPSendTo(
	SOCKET			s,
	LPWSABUF		lpBuffers,
	DWORD			dwBufferCount,
	LPDWORD			lpNumberOfBytesSent,
	DWORD			dwFlags,
	const struct sockaddr FAR * lpTo,
	int				iTolen,
	LPWSAOVERLAPPED	lpOverlapped,
	LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
	LPWSATHREADID	lpThreadId,
	LPINT			lpErrno
)
{
	__OUTPUT_DEBUG_CALL__

	return NextProcTable.lpWSPSendTo(s, lpBuffers, dwBufferCount
				, lpNumberOfBytesSent, dwFlags, lpTo, iTolen, lpOverlapped
				, lpCompletionRoutine, lpThreadId, lpErrno);
}

int WSPAPI WSPRecvFrom (
	SOCKET			s,
	LPWSABUF		lpBuffers,
	DWORD			dwBufferCount,
	LPDWORD			lpNumberOfBytesRecvd,
	LPDWORD			lpFlags,
	struct sockaddr FAR * lpFrom,
	LPINT			lpFromlen,
	LPWSAOVERLAPPED lpOverlapped,
	LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
	LPWSATHREADID	lpThreadId,
	LPINT			lpErrno
)
{
	__OUTPUT_DEBUG_CALL__
	int iRet = NextProcTable.lpWSPRecvFrom(s, lpBuffers, dwBufferCount
		, lpNumberOfBytesRecvd, lpFlags, lpFrom, lpFromlen
		, lpOverlapped, lpCompletionRoutine, lpThreadId, lpErrno);

	return iRet;
}

int WSPAPI WSPAddressToString (
  LPSOCKADDR	lpsaAddress,            
  DWORD			dwAddressLength,             
  LPWSAPROTOCOL_INFOW lpProtocolInfo,   
  LPWSTR		lpszAddressString,          
  LPDWORD		lpdwAddressStringLength,   
  LPINT			lpErrno                      
)
{
	__OUTPUT_DEBUG_CALL__
	return NextProcTable.lpWSPAddressToString(lpsaAddress
		, dwAddressLength, lpProtocolInfo
		, lpszAddressString, lpdwAddressStringLength, lpErrno);
}

int WSPAPI WSPAsyncSelect (
  SOCKET		s,            
  HWND			hWnd,           
  unsigned int	wMsg,   
  long			lEvent,         
  LPINT			lpErrno        
)
{
	__OUTPUT_DEBUG_CALL__
	return NextProcTable.lpWSPAsyncSelect(s, hWnd, wMsg, lEvent, lpErrno);
}
 
int WSPAPI WSPBind (
  SOCKET		s,                           
  const struct	sockaddr FAR * name,   
  int			namelen,                        
  LPINT			lpErrno                       
)
{
	__OUTPUT_DEBUG_CALL__
	return NextProcTable.lpWSPBind(s, name, namelen, lpErrno);
}

int WSPAPI WSPCancelBlockingCall (
  LPINT			lpErrno  
)
{
	__OUTPUT_DEBUG_CALL__
	return NextProcTable.lpWSPCancelBlockingCall(lpErrno);
}

int WSPAPI WSPCleanup (
  LPINT			lpErrno  
)
{
	__OUTPUT_DEBUG_CALL__
	return NextProcTable.lpWSPCleanup(lpErrno);
}
 
int WSPAPI WSPDuplicateSocket (
  SOCKET		s,                             
  DWORD			dwProcessId,                    
  LPWSAPROTOCOL_INFOW lpProtocolInfo,   
  LPINT			lpErrno                         
)
{
	__OUTPUT_DEBUG_CALL__

	return NextProcTable.lpWSPDuplicateSocket(
		s, dwProcessId, lpProtocolInfo, lpErrno);
}

int WSPAPI WSPEnumNetworkEvents (
  SOCKET		s,                             
  WSAEVENT		hEventObject,                
  LPWSANETWORKEVENTS lpNetworkEvents,   
  LPINT			lpErrno                         
)
{
	__OUTPUT_DEBUG_CALL__
	return NextProcTable.lpWSPEnumNetworkEvents(
		s, hEventObject, lpNetworkEvents, lpErrno);
}

int WSPAPI WSPEventSelect (
  SOCKET		s,              
  WSAEVENT		hEventObject,   
  long			lNetworkEvents,   
  LPINT			lpErrno          
)
{
	__OUTPUT_DEBUG_CALL__
	return NextProcTable.lpWSPEventSelect(
		s, hEventObject, lNetworkEvents, lpErrno);
}

BOOL WSPAPI WSPGetOverlappedResult (
  SOCKET		s,                       
  LPWSAOVERLAPPED lpOverlapped,   
  LPDWORD		lpcbTransfer,           
  BOOL			fWait,                     
  LPDWORD		lpdwFlags,              
  LPINT			lpErrno                   
)
{
	__OUTPUT_DEBUG_CALL__
	return NextProcTable.lpWSPGetOverlappedResult(s, lpOverlapped
		, lpcbTransfer, fWait, lpdwFlags, lpErrno);
}

int WSPAPI WSPGetPeerName (
  SOCKET		s,                     
  struct		sockaddr FAR * name,   
  LPINT			namelen,                
  LPINT			lpErrno                  
)
{
	__OUTPUT_DEBUG_CALL__
	return NextProcTable.lpWSPGetPeerName(s, name, namelen, lpErrno);
}

int WSPAPI WSPGetSockName (
  SOCKET		s,                     
  struct		sockaddr FAR * name,   
  LPINT			namelen,                
  LPINT			lpErrno                 
)
{
	__OUTPUT_DEBUG_CALL__
	return NextProcTable.lpWSPGetSockName(s, name, namelen, lpErrno);
}

int WSPAPI WSPGetSockOpt (
  SOCKET		s,            
  int			level,           
  int			optname,         
  char FAR *	optval,   
  LPINT			optlen,        
  LPINT			lpErrno        
) 
{
	__OUTPUT_DEBUG_CALL__
	return NextProcTable.lpWSPGetSockOpt(
		s, level, optname, optval, optlen, lpErrno);
}

BOOL WSPAPI WSPGetQOSByName (
  SOCKET		s,             
  LPWSABUF		lpQOSName,   
  LPQOS			lpQOS,          
  LPINT			lpErrno         
)
{
	__OUTPUT_DEBUG_CALL__
	return NextProcTable.lpWSPGetQOSByName(s, lpQOSName, lpQOS, lpErrno);
}

int WSPAPI WSPIoctl (
  SOCKET		s,                                                
  DWORD			dwIoControlCode,                                   
  LPVOID		lpvInBuffer,                                      
  DWORD			cbInBuffer,                                        
  LPVOID		lpvOutBuffer,                                     
  DWORD			cbOutBuffer,                 
  LPDWORD		lpcbBytesReturned,                            
  LPWSAOVERLAPPED lpOverlapped,                            
  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,  
  LPWSATHREADID lpThreadId,                                
  LPINT			lpErrno                                            
)
{
	__OUTPUT_DEBUG_CALL__
	return NextProcTable.lpWSPIoctl(s, dwIoControlCode, lpvInBuffer
		, cbInBuffer, lpvOutBuffer, cbOutBuffer, lpcbBytesReturned
		, lpOverlapped, lpCompletionRoutine, lpThreadId, lpErrno);
}

SOCKET WSPAPI WSPJoinLeaf (
  SOCKET		s,                           
  const struct	sockaddr FAR * name,   
  int			namelen,                        
  LPWSABUF		lpCallerData,              
  LPWSABUF		lpCalleeData,              
  LPQOS			lpSQOS,                       
  LPQOS			lpGQOS,                       
  DWORD			dwFlags,                      
  LPINT			lpErrno                      
)
{
	__OUTPUT_DEBUG_CALL__
	return NextProcTable.lpWSPJoinLeaf(s, name, namelen, lpCallerData
		, lpCalleeData, lpSQOS, lpGQOS, dwFlags, lpErrno);
}

int WSPAPI WSPListen (
  SOCKET		s,      
  int			backlog,   
  LPINT			lpErrno  
)
{
	__OUTPUT_DEBUG_CALL__
	return NextProcTable.lpWSPListen(s, backlog, lpErrno);
}

int WSPAPI WSPRecvDisconnect (
  SOCKET		s,                           
  LPWSABUF		lpInboundDisconnectData,   
  LPINT			lpErrno                       
)
{
	__OUTPUT_DEBUG_CALL__
	return NextProcTable.lpWSPRecvDisconnect(s, lpInboundDisconnectData, lpErrno);
}


int WSPAPI WSPSendDisconnect (
  SOCKET		s,                            
  LPWSABUF		lpOutboundDisconnectData,   
  LPINT			lpErrno                        
)
{
	__OUTPUT_DEBUG_CALL__
	return NextProcTable.lpWSPSendDisconnect(
		s, lpOutboundDisconnectData, lpErrno);
}

int WSPAPI WSPSetSockOpt (
  SOCKET		s,                  
  int			level,                 
  int			optname,               
  const char FAR * optval,   
  int			optlen,                
  LPINT			lpErrno              
)
{
	__OUTPUT_DEBUG_CALL__
	return NextProcTable.lpWSPSetSockOpt(
		s, level, optname, optval, optlen, lpErrno);
}

int WSPAPI WSPShutdown (
  SOCKET		s,      
  int			how,       
  LPINT			lpErrno  
)
{
	__OUTPUT_DEBUG_CALL__
	return NextProcTable.lpWSPShutdown(s, how, lpErrno);
}

int WSPAPI WSPStringToAddress (
  LPWSTR		AddressString,                 
  INT			AddressFamily,                    
  LPWSAPROTOCOL_INFOW lpProtocolInfo,   
  LPSOCKADDR	lpAddress,                 
  LPINT			lpAddressLength,                
  LPINT			lpErrno                         
)
{ 
	__OUTPUT_DEBUG_CALL__
	return NextProcTable.lpWSPStringToAddress(AddressString, AddressFamily
		, lpProtocolInfo, lpAddress, lpAddressLength, lpErrno);
}
 
//——————————————————————————————————————
// Dll 入口函数


// 对于
BOOL WINAPI DllMain(
	HINSTANCE	hModule, 
    DWORD		ul_reason_for_call, 
    LPVOID		lpReserved
)
{
	if(ul_reason_for_call == DLL_PROCESS_ATTACH) {
		init_logger(hModule);
 		GetModuleFileName(NULL, m_sProcessName, MAX_PATH);
		PACKETGRASPER_TRC("New Process Load : "<<m_sProcessName);  

		InitializeCriticalSection(&gCriticalSection);
		EnterCriticalSection(&gCriticalSection); 
		{
			m_iRefCount ++; 
			PACKETGRASPER_TRC("DllMain Attach Count "<< m_iRefCount);  
		} 
		LeaveCriticalSection(&gCriticalSection);
	} else if (ul_reason_for_call == DLL_THREAD_ATTACH) {
	} else if (ul_reason_for_call == DLL_THREAD_DETACH) {
	} else if (ul_reason_for_call == DLL_PROCESS_DETACH) { 
		EnterCriticalSection(&gCriticalSection);
		{
			m_iRefCount -- ;
			PACKETGRASPER_TRC("DllMain Attach Count "<< m_iRefCount);  
		}
		LeaveCriticalSection(&gCriticalSection);

		//g_select.finalize();

		//UninitializeLog();
		ODS2(m_sProcessName,_T(" Exit ..."));
	}

	return TRUE;
}

//——————————————————————————————————————
// DLL导出的函数

int WSPAPI WSPStartup(
	WORD				wVersionRequested,
	LPWSPDATA			lpWSPData,
	LPWSAPROTOCOL_INFOW	lpProtocolInfo,
	WSPUPCALLTABLE		upcallTable,
	LPWSPPROC_TABLE		lpProcTable
)
{
	TCHAR				sLibraryPath[512];
    LPWSPSTARTUP        WSPStartupFunc      = NULL;
	HMODULE				hLibraryHandle		= NULL;
    INT                 ErrorCode           = 0; 

	if (!GetHookProvider(lpProtocolInfo, sLibraryPath)
		|| (hLibraryHandle = LoadLibrary(sLibraryPath)) == NULL
		|| (WSPStartupFunc = (LPWSPSTARTUP)GetProcAddress(
			hLibraryHandle, "WSPStartup")) == NULL
		)
		return WSAEPROVIDERFAILEDINIT;

	PrintProtocolInfo(lpProtocolInfo, sLibraryPath);

	if ((ErrorCode = WSPStartupFunc(wVersionRequested, lpWSPData
		, lpProtocolInfo, upcallTable, lpProcTable)) != ERROR_SUCCESS)
		return ErrorCode;
	
	EnterCriticalSection(&gCriticalSection);

	MainUpCallTable = upcallTable;

	NextProcTable = *lpProcTable;

	lpProcTable->lpWSPSocket				= WSPSocket;
	lpProcTable->lpWSPCloseSocket			= WSPCloseSocket;
	lpProcTable->lpWSPConnect				= WSPConnect;
	lpProcTable->lpWSPAccept				= WSPAccept;
	lpProcTable->lpWSPSend					= WSPSend;
	lpProcTable->lpWSPSendTo				= WSPSendTo;
	lpProcTable->lpWSPRecv					= WSPRecv;
	lpProcTable->lpWSPRecvFrom				= WSPRecvFrom;

	lpProcTable->lpWSPAddressToString		= WSPAddressToString;
	lpProcTable->lpWSPAsyncSelect 			= WSPAsyncSelect;
	lpProcTable->lpWSPBind 					= WSPBind;
	lpProcTable->lpWSPCancelBlockingCall 	= WSPCancelBlockingCall;
	lpProcTable->lpWSPCleanup 				= WSPCleanup;
	lpProcTable->lpWSPDuplicateSocket  		= WSPDuplicateSocket;
	lpProcTable->lpWSPEnumNetworkEvents 	= WSPEnumNetworkEvents;
	lpProcTable->lpWSPEventSelect 			= WSPEventSelect;
	lpProcTable->lpWSPGetOverlappedResult 	= WSPGetOverlappedResult;
	lpProcTable->lpWSPGetPeerName 			= WSPGetPeerName;
	lpProcTable->lpWSPGetQOSByName 			= WSPGetQOSByName;
	lpProcTable->lpWSPGetSockName 			= WSPGetSockName;
	lpProcTable->lpWSPGetSockOpt 			= WSPGetSockOpt;
	lpProcTable->lpWSPIoctl 				= WSPIoctl;
	lpProcTable->lpWSPJoinLeaf 				= WSPJoinLeaf;
	lpProcTable->lpWSPListen 				= WSPListen;
	lpProcTable->lpWSPRecvDisconnect 		= WSPRecvDisconnect;
	lpProcTable->lpWSPSelect 				= WSPSelect;
	lpProcTable->lpWSPSendDisconnect 		= WSPSendDisconnect;
	lpProcTable->lpWSPSetSockOpt 			= WSPSetSockOpt;
	lpProcTable->lpWSPShutdown 				= WSPShutdown;
	lpProcTable->lpWSPStringToAddress 		= WSPStringToAddress;

	//g_select.setRecv(NextProcTable.lpWSPRecv);
	LeaveCriticalSection(&gCriticalSection);
	return 0;
}
