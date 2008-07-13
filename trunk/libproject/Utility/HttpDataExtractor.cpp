#include "stdafx.h"
#include "httpdataextractor.h"

const char * chunk_token = "\r\n";
const int chunk_token_length = 2;	// ���Ⱥ�������ĳ���
const int chunk_tail_length = 2;	// \r\n�ĳ���....

// �����β��������CHUNK�Ľ�β
// β��Ӧ��������������ǰһ��\r\n�ǽ���0, ����һ����chunk�Ľ�β
const char * whole_chunk_tail = "0\r\n\r\n";	

class ChunkPacket;

//========================
// ���ڳ���ȷ��������
class FixContent : public HttpDataExtractor {
public:
	FixContent(ProtocolPacket<HTTP_PACKET_SIZE> *data, const HTTP_RESPONSE_HEADER *);
	~FixContent();
	virtual int addBuffer(const char *buf, const int len);
	virtual bool finished() const;
private:
	friend class HttpDataExtractor;
	int expected_length_;		// ����Ĵ�С
	ProtocolPacket<HTTP_PACKET_SIZE> * data_;
	const HTTP_RESPONSE_HEADER * http_header_;
	bool finished_;

	// ����
	FixContent(FixContent &) {}
};

// δָ�����ȵİ�
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


class ChunkPacket : public HttpDataExtractor {
public:
	ChunkPacket(ProtocolPacket<HTTP_PACKET_SIZE> *data, const HTTP_RESPONSE_HEADER *);
	~ChunkPacket();
	// ����ȥ��chunk��ͷ����β�����������ݲ��ַ��뻺����
	virtual int addBuffer(const char *buf, const int len);
	virtual bool finished() const;	// chunk�Ƿ��Ѿ�����
private:
	int write_to_buffer(const char * buf, const int len);
	bool finished_;
	ProtocolPacket<HTTP_PACKET_SIZE> * data_;
	const HTTP_RESPONSE_HEADER * http_header_;

	// ���һ��IP��������һ��������chunk��
	// ��ʱ��������û��ȫ�����.....
	int cur_need_length_;

	// ����
	ChunkPacket(ChunkPacket &) {}
};

// ����δָ�����ȵ��Ҵ������ݵİ�
class NoSepcifiedLength : public HttpDataExtractor {
public:
	NoSepcifiedLength(ProtocolPacket<HTTP_PACKET_SIZE> *data, const HTTP_RESPONSE_HEADER *);
	~NoSepcifiedLength();
	// ����ȥ��chunk��ͷ����β�����������ݲ��ַ��뻺����
	virtual int addBuffer(const char *buf, const int len);
	virtual bool finished() const;	// chunk�Ƿ��Ѿ�����
private:
	int write_to_buffer(const char * buf, const int len);
	bool finished_;
	ProtocolPacket<HTTP_PACKET_SIZE> * data_;
	const HTTP_RESPONSE_HEADER * http_header_;

	// ���һ��IP��������һ��������chunk��
	// ��ʱ��������û��ȫ�����.....
	int cur_need_length_;

	// ����
	NoSepcifiedLength(NoSepcifiedLength &) {}
};

HttpDataExtractor * HttpDataExtractor::Create(const HTTP_RESPONSE_HEADER *header,
								  ProtocolPacket<HTTP_PACKET_SIZE> *data) {
	if (header->isChunk()) {
		return (HttpDataExtractor*)new ChunkPacket(data, header);
	} else if (header->existContent() == false) {
		// ���û��content����
		return (HttpDataExtractor*) new NoContent(data, header);
	} else if (header->getContentLength() == HTTP_RESPONSE_HEADER::NO_DESIGNATION) {
		return (HttpDataExtractor*)new NoSepcifiedLength(data, header);
	}else {
		return (HttpDataExtractor*)new FixContent(data, header);
	}
}

//============================
// class ChunkPacket
ChunkPacket::ChunkPacket(ProtocolPacket<HTTP_PACKET_SIZE> *data,
	const HTTP_RESPONSE_HEADER *header) : data_(data), http_header_(header) {
	finished_ = false;
	cur_need_length_ = 0;
}
ChunkPacket::~ChunkPacket() {
}

// ����Ҫ���ֽ���д�뵽�������У��������ݲ�����ȫ��д��
int ChunkPacket::write_to_buffer(const char * buf, const int len) {
	if (cur_need_length_ == 0)
		return 0;

	// ע����Ҫ�������а���\r\n�� 
	if (len >= cur_need_length_) {
		// ��д��β�������ַ�
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
	// ��������Ļ���������Ϊ0�� ֱ�ӷ���
	if (len == 0) {
		finished_ = true;
		return 0;
	}

	int chunk_head_bytes  = 0;
	// ���Ȼ�ȡ����
	if (cur_need_length_ == 0) {
		const int chunk_data_len = strtol(buf, NULL, 16);
		// ������chunk��β��
		if (chunk_data_len == 0) {
			finished_ = true;
			return strlen(whole_chunk_tail);
		}
		// ������Ҫ��ȡ�ĳ���, ע�⻹��β���������Լ�����Ȼ��Ҫ��β��д�뵽��������
		cur_need_length_ = chunk_data_len + chunk_tail_length;
		
		// �õ�chunkͷ���ķָ������Ӷ���ȡͷ���ĳ���
		char * data_header = strstr(buf, chunk_token);
		if (data_header == NULL) throw int(0);
		chunk_head_bytes = data_header + strlen(chunk_token) - buf;
	}

	// ͷ�����ݼ��� ���ݲ���
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

	// ���������0�� ������Ѿ������
	if (len == 0) {
		finished_ = true;
		return 0;
	}
	// ���ָ���˳���
	if (except_len != HTTP_RESPONSE_HEADER::NO_DESIGNATION) {
		const int recv_len = data_->getTotalSize();	// �Ѿ����ܵ���
		int need_recv = except_len - recv_len;	// ����Ҫ���ܶ���
		int should_recv = need_recv >= len ? len : need_recv;

		if (need_recv == should_recv)
			finished_ = true;
		return data_->write(buf, should_recv);
	} else {
		OutputDebugString("no length designate..........");
		// ֻ��һ�����Ļ�	
		finished_ = true;
		return data_->write(buf, len);
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

//============================
// class FixContent
NoSepcifiedLength::NoSepcifiedLength(ProtocolPacket<HTTP_PACKET_SIZE> *data,
	const HTTP_RESPONSE_HEADER *header) : data_(data), http_header_(header) {
	finished_ = false;
}	

NoSepcifiedLength::~NoSepcifiedLength() {
}

bool NoSepcifiedLength::finished() const {
	return finished_;
}

int NoSepcifiedLength::addBuffer(const char *buf, const int len) {
	finished_ = true;
	assert(false);
	return 0;
}