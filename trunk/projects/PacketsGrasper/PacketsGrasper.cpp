#include "stdafx.h"
#include "selectio.h"
#include "debug.h" 
#include ".\overlapped.h"


#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <serviceUtility.h>
#include <utility\debugmessage.h>
#include <utility\fd_set_utility.h>
#include <utility\HttpPacket.h>
#include <app_constants.h>

#pragma data_seg(".inidata")
	int				m_iRefCount		= 0;
#pragma data_seg()

const int BUF_SIZE = 1024 * 1024;
char global_buffer[BUF_SIZE] = {0};
 

// ������ȫ�ֱ���  
WSPUPCALLTABLE		MainUpCallTable;
CRITICAL_SECTION	gCriticalSection;			// ����α�������
WSPPROC_TABLE		NextProcTable;				// ����30�������ṩ��ָ��
TCHAR				m_sProcessName[MAX_PATH];	// ���浱ǰ��������

CSelectIO g_select;

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
 
//����������������������������������������������������������������������������
// ˽�к���
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

//����������������������������������������������������������������������������
// Winsock 2 �����ṩ�߹��Ӻ���

// WSPSelect������ʵ��
// ���ǲ���Ҫ
int WSPAPI WSPSelect (
  int			nfds,                             
  fd_set FAR *	readfds,                 
  fd_set FAR *	writefds,                
  fd_set FAR *	exceptfds,               
  const struct	timeval FAR * timeout,     
  LPINT			lpErrno                         
) 
{
	DebugStringNoDres(_T("WSPSelect ..."));
	
	// �����White DNS List, ����ҲӦ��ֱ�ӷ��� ;)
	// ֱ�ӷ��أ���������select
	if (g_select.preselect(readfds) == 0) {
		// firefox����NULL
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
	return iRet;
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
	DebugStringNoDres(_T("WSPRecv ..."));
	try {
		// ����ʹ��MSG_PEEKץȡ�ķ�ʽ
		if ((*lpFlags) & MSG_PEEK) {
			return NextProcTable.lpWSPRecv(s, lpBuffers, dwBufferCount
				, lpNumberOfBytesRecvd, lpFlags, lpOverlapped
				, lpCompletionRoutine, lpThreadId, lpErrno);
		}

		if (g_select.prerecv(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd) == 0) {
			return 0;
		}

		int iRet = NextProcTable.lpWSPRecv(s, lpBuffers, dwBufferCount
				, lpNumberOfBytesRecvd, lpFlags, lpOverlapped
				, lpCompletionRoutine, lpThreadId, lpErrno);

		return iRet;
	} catch (...) {
		// writeException("WSPRecv", "unknown");
		return SOCKET_ERROR;
	}
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
	DebugStringNoDres(_T("WSPSocket ..."));
	return NextProcTable.lpWSPSocket(af, type
		, protocol, lpProtocolInfo, g, dwFlags, lpErrno);
}

int WSPAPI WSPCloseSocket(
	SOCKET		s,
	LPINT		lpErrno
) 
{
	DebugStringNoDres(_T("WSPCloseSocket ..."));
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
	DebugStringNoDres(_T("WSPConnect ..."));
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
	DebugStringNoDres(_T("WSPAccept ..."));
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
	OutputDebugString(_T("WSPSend"));

	HTTPRequestPacket packet;
	int item_count = packet.parsePacket(buf, count);

	// ���С��2����ô���Ͳ���һ��HTTP����
	if (item_count < 2) {	
		return NextProcTable.lpWSPSend(s, lpBuffers, dwBufferCount
			, lpNumberOfBytesSent, dwFlags, lpOverlapped
			, lpCompletionRoutine, lpThreadId, lpErrno);
	}
	
	
	// DumpBuf(lpBuffers, dwBufferCount, "c:\\request.txt");
	 // ���IP�Ƿ����������������ͨ��������ֱ�ӷ��ش���
	if (accessNetword() && checkHTTPRequest(&packet)){
		return NextProcTable.lpWSPSend(s, lpBuffers, dwBufferCount
			, lpNumberOfBytesSent, dwFlags, lpOverlapped
			, lpCompletionRoutine, lpThreadId, lpErrno);
	} else {
		*lpErrno = WSAETIMEDOUT;
		return SOCKET_ERROR;
	}
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
	OutputDebugString("WSPSendTo ...");
	// ���IP�Ƿ����������������ͨ��������ֱ�ӷ��ش���
	if (accessNetword() && checkHTTPRequest(lpBuffers, dwBufferCount)){
		return NextProcTable.lpWSPSendTo(s, lpBuffers, dwBufferCount
			, lpNumberOfBytesSent, dwFlags, lpTo, iTolen, lpOverlapped
			, lpCompletionRoutine, lpThreadId, lpErrno);
	} else {
		*lpErrno = WSAETIMEDOUT;
		return SOCKET_ERROR;
	}
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
	DebugStringNoDres(_T("WSPAddressToString ..."));
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
	DebugStringNoDres(_T("WSPAsyncSelect ..."));
	return NextProcTable.lpWSPAsyncSelect(s, hWnd, wMsg, lEvent, lpErrno);
}
 
int WSPAPI WSPBind (
  SOCKET		s,                           
  const struct	sockaddr FAR * name,   
  int			namelen,                        
  LPINT			lpErrno                       
)
{
	DebugStringNoDres(_T("WSPBind ..."));
	return NextProcTable.lpWSPBind(s, name, namelen, lpErrno);
}

int WSPAPI WSPCancelBlockingCall (
  LPINT			lpErrno  
)
{
	DebugStringNoDres(_T("WSPCancelBlockingCall ..."));
	return NextProcTable.lpWSPCancelBlockingCall(lpErrno);
}

int WSPAPI WSPCleanup (
  LPINT			lpErrno  
)
{
	DebugStringNoDres(_T("WSPCleanup ..."));
	return NextProcTable.lpWSPCleanup(lpErrno);
}
 
int WSPAPI WSPDuplicateSocket (
  SOCKET		s,                             
  DWORD			dwProcessId,                    
  LPWSAPROTOCOL_INFOW lpProtocolInfo,   
  LPINT			lpErrno                         
)
{
	DebugStringNoDres(_T("WSPDuplicateSocket ..."));
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
	DebugStringNoDres(_T("WSPEnumNetworkEvents ..."));
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
	DebugStringNoDres(_T("WSPEventSelect ..."));
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
	DebugStringNoDres(_T("WSPGetOverlappedResult ..."));
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
	DebugStringNoDres(_T("WSPGetPeerName ..."));
	return NextProcTable.lpWSPGetPeerName(s, name, namelen, lpErrno);
}

int WSPAPI WSPGetSockName (
  SOCKET		s,                     
  struct		sockaddr FAR * name,   
  LPINT			namelen,                
  LPINT			lpErrno                 
)
{
	DebugStringNoDres(_T("WSPGetSockName ..."));
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
	DebugStringNoDres(_T("WSPGetSockOpt ..."));
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
	DebugStringNoDres(_T("WSPGetQOSByName ..."));
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
	DebugStringNoDres(_T("WSPIoctl ..."));
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
	DebugStringNoDres(_T("WSPJoinLeaf ..."));
	return NextProcTable.lpWSPJoinLeaf(s, name, namelen, lpCallerData
		, lpCalleeData, lpSQOS, lpGQOS, dwFlags, lpErrno);
}

int WSPAPI WSPListen (
  SOCKET		s,      
  int			backlog,   
  LPINT			lpErrno  
)
{
	DebugStringNoDres(_T("WSPListen ..."));
	return NextProcTable.lpWSPListen(s, backlog, lpErrno);
}

int WSPAPI WSPRecvDisconnect (
  SOCKET		s,                           
  LPWSABUF		lpInboundDisconnectData,   
  LPINT			lpErrno                       
)
{
	DebugStringNoDres(_T("WSPRecvDisconnect ..."));
	return NextProcTable.lpWSPRecvDisconnect(s, lpInboundDisconnectData, lpErrno);
}


int WSPAPI WSPSendDisconnect (
  SOCKET		s,                            
  LPWSABUF		lpOutboundDisconnectData,   
  LPINT			lpErrno                        
)
{
	DebugStringNoDres(_T("WSPSendDisconnect ..."));
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
	DebugStringNoDres(_T("WSPSetSockOpt ..."));
	return NextProcTable.lpWSPSetSockOpt(
		s, level, optname, optval, optlen, lpErrno);
}

int WSPAPI WSPShutdown (
  SOCKET		s,      
  int			how,       
  LPINT			lpErrno  
)
{
	DebugStringNoDres(_T("WSPShutdown ..."));
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
	return NextProcTable.lpWSPStringToAddress(AddressString, AddressFamily
		, lpProtocolInfo, lpAddress, lpAddressLength, lpErrno);
}
 
//����������������������������������������������������������������������������
// Dll ��ں���


// ����
BOOL WINAPI DllMain(
	HINSTANCE	hModule, 
    DWORD		ul_reason_for_call, 
    LPVOID		lpReserved
)
{
	if(ul_reason_for_call == DLL_PROCESS_ATTACH) {
		//InitializeLog();
 		GetModuleFileName(NULL, m_sProcessName, MAX_PATH);

		InitializeCriticalSection(&gCriticalSection);
		EnterCriticalSection(&gCriticalSection); 
		{
			m_iRefCount ++; 
			DP1("DllMain Attach Count %d", m_iRefCount);
		} 
		LeaveCriticalSection(&gCriticalSection); 
 
		ODS2(m_sProcessName,_T(" Loading ..."));
	} else if (ul_reason_for_call == DLL_THREAD_ATTACH) {
	} else if (ul_reason_for_call == DLL_THREAD_DETACH) {
	} else if (ul_reason_for_call == DLL_PROCESS_DETACH) { 
		EnterCriticalSection(&gCriticalSection);
		{
			m_iRefCount -- ;
			DP1("DllMain Attach Count %d", m_iRefCount);
		}
		LeaveCriticalSection(&gCriticalSection);

		//UninitializeLog();
		ODS2(m_sProcessName,_T(" Exit ..."));
	}

	return TRUE;
}

//����������������������������������������������������������������������������
// DLL�����ĺ���

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

	g_select.setRecv(NextProcTable.lpWSPRecv);
	LeaveCriticalSection(&gCriticalSection);
	return 0;
}
