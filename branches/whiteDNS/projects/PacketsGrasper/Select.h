#ifndef _PACKETS_GRASPER_SELECT_H__
#define _PACKETS_GRASPER_SELECT_H__

#include <set>
#include <map>
#include <utility\ProtocolPacket.h>
#include <utility\httpPacket.h>
#include <utility\syncutility.h>

const int DEFAULT_SIZE = 4 * 1024;

// 负责保存所有已经完成的Packets
class FinishedPackets {
public:
	HTTPPacket *getFinishedPacket(const SOCKET s);
private:
	typedef std::multimap<SOCKET , HTTPPacket *> FINISHED_PACKETS_MAP;
	FINISHED_PACKETS_MAP packets_;
};
// 对SELECT I/O模型处理的基本想法：
// 在调用select函数时，我们分析所有fd_read_set中的SOCKET
// 将之中与HTTP服务器相连的SOCKET保存起来，指导这个
// SOCKET受到整个包，而后我们整个包进行分析
// 然后将它放入到新的返回的select当中
// 我们在WSPRecv中对包进行处理

// 处理select I\O
// 当select返回时我们应该将可以返回的socket返回，
// 将应该保留的select消息继续保留，之后我们继续接受消息
// 知道消息中包含足够的信息给我们处理


class CSelect {
public:
	CSelect(void);
	~CSelect(void);
public:
	// 此函数应该在closesocket中调用
	void removeSocket(const SOCKET s);
	int analyRecvData(LPWSABUF lpBuffers,  const DWORD bytes_read, const SOCKET s);
	int post_recv(LPWSABUF lpBuffers,  LPDWORD bytes_read, const SOCKET s);
	int pre_select(fd_set *readfds);
	bool isFakeSelect(const SOCKET s) { return fake_select_;}
private:	
	typedef std::map<SOCKET, HTTPPacket*> SOCK_DATA_MAP;
	SOCK_DATA_MAP _sockets_map_;
	void freeAllPackets();
	typedef std::map<SOCKET, int> SOCK_DATA_READ;
	SOCK_DATA_READ sock_data_read_;
	
	// 检查数据是否返回
	int checkData(HTTPPacket *packet, const SOCKET s);

	// 获取与SOCKET相对应的数据包
	HTTPPacket* createSOCKETPacket(const SOCKET s); // 如果不存在则创建
	HTTPPacket* getSOCKETPacket(const SOCKET s);	// 如果不存在返回NULL

	// 检查包内容
	HTTPPacket* checkContent(const SOCKET s);

	// 抓取数据，如果数据不符合要求，则直接释放
	int grasperData(const char * buf, const int len, HTTPPacket *packet);

	// 将数据存储到指定缓冲区当中
	int releaseData(char *buf, const int len, const SOCKET s);

	// 此函数会根据s进行判断，是否学要处理数据
	// 他会返回
	// SELECT_CHECK_NEEDED, SELECT_CHECK_NEEDLESS,或SELECT_CHECK_UNKNOWN
	int needChecker(const SOCKET s);

	// 将获取到的消息存入缓冲区
	int peekMessage(char *buf, const int len, const SOCKET s);

	// 是否需要保存
	bool needStored(HTTPPacket *packet);
public:
	static const REMOVE_SOCKET_ = 0;	// 释放SOCKET

	// CheckDataContent时的返回值
	static const SELECT_CHECK_DENY	= 0; // 
	static const SELECT_CHECK_PASSED = 1;
	static const SELECT_CHECK_NOCHECK = 2;

	static const SELECT_CHECK_NEEDLESS = 0; // 数据不需要被检测
	static const SELECT_CHECK_NEEDED = 1;   // 数据需要被检测
	static const SELECT_CHECK_UNKNOWN = 2;  // 未知

	int addCompletedPacket(const SOCKET s, HTTPPacket *p);
	int removeCompletedPacket(const SOCKET s, HTTPPacket *p);
	HTTPPacket * getCompletedPacket(const SOCKET s);
	void freeAllCompletedPacket();
	typedef std::multimap<SOCKET, HTTPPacket *> COMPLETED_PACKETS;
	COMPLETED_PACKETS completed_packets_;

	yanglei_utility::CAutoCreateCS cs_;

	bool fake_select_;
public:
	void Dump(const SOCKET s);					// Dmp与s相关的所有包
	void Dump(const SOCKET s, HTTPPacket *);	// Dump HTTPPacket, 名称与SOCKET相关
};

#endif  // _PACKETS_GRASPER_SELECT_H__