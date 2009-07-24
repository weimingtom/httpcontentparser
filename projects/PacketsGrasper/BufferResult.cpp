#include "StdAfx.h"
#include ".\bufferresult.h"
#include <httpcontentcheck.h>
#include <utility\replacepacket.h>
#include <utility\HTTPPacket.h>
#include <utility\fd_set_utility.h>
#include <map>
#include <string>


//===================================
// class BufferResult
void BufferResult::addResultPair(int code, int result) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	content_check_result_.insert(std::make_pair(code, result));
}
bool BufferResult::getResult(int code, int * result) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	BUFFER_RESULT::iterator iter = content_check_result_.find(code);
	if (content_check_result_.end() == iter) {
		*result = CONTENT_CHECK_NOTYET;
		return false;
	} else {
		*result = iter->second;	// 直接返回结果
		return true;
	}
}
void BufferResult::removeBufferResult(HTTPPacket *packet) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);


	BUFFER_RESULT::iterator iter = content_check_result_.find(packet->getCode());
	if (content_check_result_.end() != iter) {
		content_check_result_.erase(iter);
	} else {
		// assert(false);	
	}
}