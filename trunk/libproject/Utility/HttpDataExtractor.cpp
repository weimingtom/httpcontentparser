
// file httpdataextractor.cpp
// 此文件实现了一些类能够从HTTP Response包中取出消息的类
// 由于http包含多种传输方式，例如chunk, 还有一些包包含显示
// 的长度， 有一些则没有。
// 本文件中包含的类将根据各种包的不同特点将这些包中的数据
// 提取出来.

#include "stdafx.h"
#include "httpdataextractor.h"
#include <logdebug.h>

namespace {



const char * chunk_token = "\r\n";
const int chunk_token_length = 2;	// 长度后面紧跟的长度
const int chunk_tail_length = 2;	// \r\n的长度....

// 这个结尾代表所有CHUNK的结尾
// 尾部应该是这样，但是前一个\r\n是紧跟0, 后面一个是chunk的结尾
const char * whole_chunk_tail = "0\r\n\r\n";	

class ChunkPacket;

//========================
// 对于长度确定的数据
class FixContent : public HttpDataExtractor {
public:
	FixContent(ProtocolPacket<HTTP_PACKET_SIZE> *data, const HTTP_RESPONSE_HEADER *);
	~FixContent();
	virtual int addBuffer(const char *buf, const int len);
	virtual bool finished() const;
private:
	friend class HttpDataExtractor;
	int expected_length_;		// 与其的大小
	ProtocolPacket<HTTP_PACKET_SIZE> * data_;
	const HTTP_RESPONSE_HEADER * http_header_;
	bool finished_;

	// 禁用
	FixContent(FixContent &) {}
};

// 未指定长度的包
class NoContent : public HttpDataExtractor {
	public:
	NoContent(ProtocolPacket<HTTP_PACKET_SIZE> *data, const HTTP_RESPONSE_HEADER *);
	~NoContent();
	virtual int addBuffer(const char *buf, const int len);
	virtual bool finished() const;
private:
	friend class HttpDataExtractor;
	ProtocolPacket<HTTP_PACKET_SIZE> * data_;
	const HTTP_RESPONSE_HEADER * http_header_;
	bool finished_;
};

// 关闭的包
class CloseConnectionLinkt : public HttpDataExtractor {
	public:
	CloseConnectionLinkt(ProtocolPacket<HTTP_PACKET_SIZE> *data, const HTTP_RESPONSE_HEADER *);
	~CloseConnectionLinkt();
	virtual int addBuffer(const char *buf, const int len);
	virtual bool finished() const;
private:
	friend class HttpDataExtractor;
	ProtocolPacket<HTTP_PACKET_SIZE> * data_;
	const HTTP_RESPONSE_HEADER * http_header_;
	bool finished_;
};


class ChunkPacket : public HttpDataExtractor {
public:
	ChunkPacket(ProtocolPacket<HTTP_PACKET_SIZE> *data, const HTTP_RESPONSE_HEADER *);
	~ChunkPacket();
	// 负责去掉chunk的头部和尾部，并把数据部分放入缓冲区
	virtual int addBuffer(const char *buf, const int len);
	virtual bool finished() const;	// chunk是否已经结束
private:
	int write_to_buffer(const char * buf, const int len);
	bool finished_;
	ProtocolPacket<HTTP_PACKET_SIZE> * data_;
	const HTTP_RESPONSE_HEADER * http_header_;

	// 如果一个IP包不包含一个完整的chunk包
	// 这时候整个包没有全部完成.....
	int cur_need_length_;

	// 禁用
	ChunkPacket(ChunkPacket &) {}
};

// 对于未指定长度的且存在内容的包
class NoSepcifiedLength : public HttpDataExtractor {
public:
	NoSepcifiedLength(ProtocolPacket<HTTP_PACKET_SIZE> *data, const HTTP_RESPONSE_HEADER *);
	~NoSepcifiedLength();
	// 负责去掉chunk的头部和尾部，并把数据部分放入缓冲区
	virtual int addBuffer(const char *buf, const int len);
	virtual bool finished() const;	// chunk是否已经结束
private:
	int write_to_buffer(const char * buf, const int len);
	bool finished_;
	ProtocolPacket<HTTP_PACKET_SIZE> * data_;
	const HTTP_RESPONSE_HEADER * http_header_;

	// 如果一个IP包不包含一个完整的chunk包
	// 这时候整个包没有全部完成.....
	int cur_need_length_;

	// 禁用
	NoSepcifiedLength(NoSepcifiedLength &) {}
};



//============================
// class ChunkPacket
ChunkPacket::ChunkPacket(ProtocolPacket<HTTP_PACKET_SIZE> *data,
	const HTTP_RESPONSE_HEADER *header) : data_(data), http_header_(header) {
	finished_ = false;
	cur_need_length_ = 0;
}

ChunkPacket::~ChunkPacket() {
}

// 按需要的字节数写入到缓冲区中，不过数据不足则全部写入
int ChunkPacket::write_to_buffer(const char * buf, const int len) {
	if (cur_need_length_ == 0)
		return 0;

	// 注意需要的数据中包含\r\n， 
	if (len >= cur_need_length_) {
		// 不写入尾部三个字符
		int written = data_->write(buf, cur_need_length_ - chunk_tail_length);
		cur_need_length_ = 0;
		return written + chunk_tail_length;
	} else {
		int written = data_->write(buf, len);
		cur_need_length_ -= written;
		assert(len == written);
		return written;
	}
}
// 
int ChunkPacket::addBuffer(const char *buf, const int len) {
	assert(finished_ == false);
	// 如果给出的缓冲区长度为0， 直接返回
	if (len == 0) {
		finished_ = true;
		return 0;
	}

	int chunk_head_bytes  = 0;
	// 首先获取长度
	if (cur_need_length_ == 0) {
		const int chunk_data_len = strtol(buf, NULL, 16);
		// 到达了chunk的尾部
		if (chunk_data_len == 0) {
			finished_ = true;
			return static_cast<int>(strlen(whole_chunk_tail));
		}
		// 保存需要读取的长度, 注意还有尾部的三个自己，当然不要将尾部写入到缓冲区里
		cur_need_length_ = chunk_data_len + chunk_tail_length;
		
		// 得到chunk头部的分隔符，从而获取头部的长度
		char * data_header = strstr(buf, chunk_token);
		if (data_header == NULL) throw int(0);
		chunk_head_bytes = data_header + strlen(chunk_token) - buf;
	}

	// 头部数据加上 数据部分
	return write_to_buffer(&(buf[chunk_head_bytes]), len - chunk_head_bytes)
		+ chunk_head_bytes;
}
bool ChunkPacket::finished() const {
	return finished_;
}

//============================
// class FixContent
FixContent::FixContent(ProtocolPacket<HTTP_PACKET_SIZE> *data,
	const HTTP_RESPONSE_HEADER *header) : data_(data), http_header_(header) {
	finished_ = false;
}	

FixContent::~FixContent() {
}

int FixContent::addBuffer(const char *buf, const int len) {
	const int except_len = http_header_->getContentLength();
	assert(http_header_->isChunk() == false);
	assert(finished_ == false);

	// 如果传入了0， 则代表已经完成了
	if (len == 0) {
		finished_ = true;
		return 0;
	}
	// 如果指定了长度
	if (except_len != HTTP_RESPONSE_HEADER::NO_DESIGNATION) {
		const int recv_len = data_->getTotalSize();	// 已经接受到的
		int need_recv = except_len - recv_len;	// 还需要接受多少
		int should_recv = need_recv >= len ? len : need_recv;

		if (need_recv == should_recv)
			finished_ = true;
		return data_->write(buf, should_recv);
	} else {
		assert(false);
		//OutputDebugString("no length designate..........");
		//finished_ = true;
		//return data_->write(buf, len);
		return 0;
	}
}

bool FixContent::finished() const {
	return finished_;
}

//============================
// class FixContent
NoContent::NoContent(ProtocolPacket<HTTP_PACKET_SIZE> *data,
	const HTTP_RESPONSE_HEADER *header) : data_(data), http_header_(header) {
	finished_ = true;
}	

NoContent::~NoContent() {
}

bool NoContent::finished() const {
	return finished_;
}

int NoContent::addBuffer(const char *buf, const int len) {
	return 0;
}

//===========================
// 合适close的包应该是完成的呢？？
CloseConnectionLinkt::CloseConnectionLinkt(ProtocolPacket<HTTP_PACKET_SIZE> *data,
	const HTTP_RESPONSE_HEADER *header) : data_(data), http_header_(header) {
	finished_ = true;
}	

CloseConnectionLinkt::~CloseConnectionLinkt() {
}

bool CloseConnectionLinkt::finished() const {
	return finished_;
}

int CloseConnectionLinkt::addBuffer(const char *buf, const int len) {
	return len;
}


//============================
// class FixContent
NoSepcifiedLength::NoSepcifiedLength(ProtocolPacket<HTTP_PACKET_SIZE> *data,
	const HTTP_RESPONSE_HEADER *header) : data_(data), http_header_(header) {
	finished_ = false;
	transfer_tail_ = true;
}	

NoSepcifiedLength::~NoSepcifiedLength() {
}

bool NoSepcifiedLength::finished() const {
	return finished_;
}

int NoSepcifiedLength::addBuffer(const char *buf, const int len) {
	if (0 == len) {
		finished_ = true;
	}
	return data_->write(buf, len);
}

};

// class HttpDataExtractor members
HttpDataExtractor * HttpDataExtractor::Create(const HTTP_RESPONSE_HEADER *header,
								  ProtocolPacket<HTTP_PACKET_SIZE> *data) {
	if (header == NULL) {
		return (HttpDataExtractor*) new NoContent(data, header);
	}

	assert (data != NULL);

	if (header->isChunk()) {
		return (HttpDataExtractor*)new ChunkPacket(data, header);
	}

	//if (header->getConnectionState() == HTTP_RESPONSE_HEADER::CONNECT_CLOSE) {
	//	return (HttpDataExtractor*) new CloseConnectionLinkt(data, header);
	//}

	// 如果没有content部分
	if (header->existContent() == false) {
		return (HttpDataExtractor*) new NoContent(data, header);
	}

	// 如果没有指定长度
	if (header->getContentLength() == HTTP_RESPONSE_HEADER::NO_DESIGNATION) {
		return (HttpDataExtractor*) new NoSepcifiedLength(data, header);
	} else {
		// 如果指定了长度，且长度为0
		if (header->getContentLength() == 0) {
			return (HttpDataExtractor*) new NoContent(data, header);
		} else {
			return (HttpDataExtractor*) new FixContent(data, header);
		}
	}
}