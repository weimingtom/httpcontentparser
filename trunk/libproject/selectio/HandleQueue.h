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

// ���ฺ������õİ��� �����ڴ��⣬��������
class HandleQueue {
public:
	HandleQueue(void);
	~HandleQueue(void);

	// ��ʼ��
	// �˺����ᴴ��һ���߳�
	void initialize();
	void finialize();

	// ����һ����
	void addPacket(HTTPPacket * packet);

	// ��ȡ���
	bool getResult(HTTPPacket * packet, int * result);

	// ���Ѿ�����
	void packetIntact(const SOCKET s, HTTPPacket *p);

	//=============================
	int addCompletedPacket(const SOCKET s, HTTPPacket *p);
	int removeCompletedPacket(const SOCKET s, HTTPPacket *p);
	HTTPPacket * getCompletedPacket(const SOCKET s);
	void getAllCompleteSOCKET(fd_set *readfds);	// ��ȡ�����Ѿ���ɵ�IO��SOCKET
	HTTPPacket * getSOCKETPacket(const SOCKET s);
	bool isThereUncompletePacket(const SOCKET s);
private:
	HTTPPacket* removeFront();
	int dequeSize();

	std::deque<HTTPPacket *> handle_deque_; // �������
	// �ٽ���
	yanglei_utility::CAutoCreateCS cs_;

	// ��������
	void handlePacket(HTTPPacket *);

	BufferResult result_;			// ������
	HTTPContentHander handler_;		// ������
	SocketPackets socketPackets_;	// �������

	// �߳�id
	DWORD dwThreadId_;
	HANDLE hThread_;

	friend DWORD CALLBACK HandlePacket(LPVOID lParam);
	friend class SelectIOTest;
};
