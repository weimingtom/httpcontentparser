#ifndef _SELECTIO_BUFFERRESULT_H__
#define _SELECTIO_BUFFERRESULT_H__

#include <map>
#include <string>
#include <utility\replacepacket.h>
#include <utility\HTTPPacket.h>
#include <utility\fd_set_utility.h>

class HTTPPacket;

// 保存包检测的结果
// 如果一个包在完成接受之后，可能还要分成多个包向上层程序传送
// 这时候会产生一个错误: 这个包的内容会被检测多次， 检测的同时有
// 会被保存多次。 为了修复这个错误，我们缓存一下这个包的结果。
// 这个值应该在handlePacket添加或查询
// 在removePacket时移除
class BufferResult {
public:
	bool getResult(int code, int * result); 
	void addResultPair(int code, int result);
	void removeBufferResult(HTTPPacket *packet);
	void removeAllBufferResult() {content_check_result_.clear();}

private:
	typedef std::map<int, int> BUFFER_RESULT;
	BUFFER_RESULT content_check_result_;

	// 临界区
	yanglei_utility::CAutoCreateCS cs_;
};

#endif  // _SELECTIO_BUFFERRESULT_H__