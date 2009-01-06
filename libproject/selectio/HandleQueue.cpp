#include "StdAfx.h"
#include ".\handlequeue.h"
#include <windows.h>

#define WM_NEW_PACKET (WM_USER + 0x0002)
HandleQueue::HandleQueue(void)
{
}

HandleQueue::~HandleQueue(void)
{
}


HTTPPacket* HandleQueue::removeFront() {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	if (handle_deque_.size() > 0) {
		HTTPPacket * packet = handle_deque_.front();
		handle_deque_.pop_front();
		return packet;
	} else {
		return NULL;
	}
}

int HandleQueue::dequeSize() {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	return (int)handle_deque_.size();
}


void HandleQueue::addPacket(HTTPPacket * packet) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);
	handle_deque_.push_back(packet);

	PostThreadMessage(dwThreadId_, WM_NEW_PACKET, 0, 0);
}

void HandleQueue::initialize() {
	hThread_ = CreateThread(NULL, 1, HandlePacket, (LPVOID)this, 0, &dwThreadId_);
	if (NULL == hThread_) {
		//TODO: 记录
	}
}

void HandleQueue::finialize() {
	result_.removeAllBufferResult();
	socketPackets_.clearAllPackets();
	socketPackets_.freeAllCompletedPacket();

	TerminateThread(hThread_, 0);
}

bool HandleQueue::getResult(HTTPPacket * packet, int * result) {
	assert (NULL != result);
	return result_.getResult(packet->getCode(), result);
}

// 不理包， 并保存结果
void HandleQueue::handlePacket(HTTPPacket *packet) {
	int result;
	// 首先查找是否已经被处理过了
	if (false == result_.getResult(packet->getCode(), &result)) {
		result =  handler_.handleContent(packet);
		result_.addResultPair(packet->getCode(), result);
	}
}

void HandleQueue::packetIntact(const SOCKET s, HTTPPacket *p) {
	socketPackets_.removePacket(s, p);
	socketPackets_.addCompletedPacket(s, p);
	addPacket(p);
}
//=========================================

int HandleQueue::removeCompletedPacket(const SOCKET s, HTTPPacket *p) {
	result_.removeBufferResult(p);
	return socketPackets_.removeCompletedPacket(s, p);
}
HTTPPacket * HandleQueue::getCompletedPacket(const SOCKET s) {
	return socketPackets_.getCompletedPacket(s);
}
void HandleQueue::getAllCompleteSOCKET(fd_set *readfds) {
	return socketPackets_.getAllCompleteSOCKET(readfds, this);
}

HTTPPacket * HandleQueue::getSOCKETPacket(const SOCKET s) {
	return socketPackets_.getSOCKETPacket(s);
}

bool HandleQueue::isThereUncompletePacket(const SOCKET s) {
	return socketPackets_.isThereUncompletePacket(s);
}

// 处理数据的线程
DWORD CALLBACK HandlePacket(LPVOID lParam) {
	HandleQueue * queue = (HandleQueue*)lParam;
	MSG msg = {0};

	while (::GetMessage(&msg, 0, NULL, NULL)) {
		switch(msg.message) {
			case WM_NEW_PACKET:
				// 处理数据包
				while (queue->dequeSize() != 0) {
					queue->handlePacket(queue->removeFront());
				}
				break;
			default:
				break;
		}
	}

	return 0;
}