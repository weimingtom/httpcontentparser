#pragma once

#include <deque>
#include <string>
#include <httpcontentcheck.h>
#include <ws2spi.h>
#include <io.h>
#include <utility\replacepacket.h>
#include <utility\HTTPPacket.h>
#include <utility\fd_set_utility.h>
#include <socketpackets.h>
#include ".\bufferresult.h"

class HTTPPacket;

// 此类负责把正好的包， 进行内存检测，并保存结果
class HandleQueue {
public:
	HandleQueue(void);
	~HandleQueue(void);

	// 初始化
	// 此函数会创建一个线程
	void initialize();
	void finialize();

	// 增加一个包
	void addPacket(HTTPPacket * packet);

	// 获取结果
	bool getResult(HTTPPacket * packet, int * result);

	// 包已经完整
	void packetIntact(const SOCKET s, HTTPPacket *p);

	//=============================
	int addCompletedPacket(const SOCKET s, HTTPPacket *p);
	int removeCompletedPacket(const SOCKET s, HTTPPacket *p);
	HTTPPacket * getCompletedPacket(const SOCKET s);
	void getAllCompleteSOCKET(fd_set *readfds);	// 获取所有已经完成的IO的SOCKET
	HTTPPacket * getSOCKETPacket(const SOCKET s);
	bool isThereUncompletePacket(const SOCKET s);
private:
	HTTPPacket* removeFront();
	int dequeSize();

	std::deque<HTTPPacket *> handle_deque_; // 处理队列
	// 临界区
	yanglei_utility::CAutoCreateCS cs_;

	// 处理数据
	void handlePacket(HTTPPacket *);

	BufferResult result_;			// 保存结果
	HTTPContentHander handler_;		// 出来包
	SocketPackets socketPackets_;	// 保存包等

	// 线程id
	DWORD dwThreadId_;
	HANDLE hThread_;

	friend DWORD CALLBACK HandlePacket(LPVOID lParam);
	friend class SelectIOTest;
};
