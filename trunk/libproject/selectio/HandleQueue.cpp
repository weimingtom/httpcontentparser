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
}

void HandleQueue::initialize() {
	DWORD dwThreadId;
	HANDLE hHanlde = CreateThread(NULL, 1, HandlePacket, (LPVOID)this, 0, &dwThreadId);
}

void HandleQueue::finialize() {
	result_.removeAllBufferResult();
}

void HandleQueue::removeCompletePacket(HTTPPacket * packet) {
	return result_.removeBufferResult(packet);
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