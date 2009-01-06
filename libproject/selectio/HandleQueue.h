#pragma once

#include <deque>
#include <string>
#include <httpcontentcheck.h>
#include <ws2spi.h>
#include <io.h>
#include <utility\replacepacket.h>
#include <utility\HTTPPacket.h>
#include <utility\fd_set_utility.h>
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
	void removeCompletePacket(HTTPPacket * packet);
private:
	HTTPPacket* removeFront();
	int dequeSize();

	std::deque<HTTPPacket *> handle_deque_; // �������
	// �ٽ���
	yanglei_utility::CAutoCreateCS cs_;

	// ��������
	void handlePacket(HTTPPacket *);

	BufferResult result_;		// ������
	HTTPContentHander handler_;	// ������

	friend DWORD CALLBACK HandlePacket(LPVOID lParam);
};
