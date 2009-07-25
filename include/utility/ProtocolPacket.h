#ifndef _UTILITY_PROTOCOL_PACKET_H__
#define _UTILITY_PROTOCOL_PACKET_H__

// ����һЩ����
// 1. ÿ�ζ����ݶ�����β���ֶ��ᴴ��һ���°�
#include <assert.h>
#include <iostream>
#include <fstream>
#include <utility\debugmessage.h>
#include <utility\syncutility.h>

#define DEFAULT_PACKET_BUFFER_SIZE (1024 * 64)

template <INT_PTR BUF_SIZE = DEFAULT_PACKET_BUFFER_SIZE>
class ProtocolPacket { 
public:
	ProtocolPacket();
	~ProtocolPacket();
	
	INT_PTR getTotalSize();

	// �ӵ�ǰ��дָ���λ�ÿ�ʼ��д
	INT_PTR write(const char *buffer, const INT_PTR bufsize);
	INT_PTR read(char *buffer, const INT_PTR bufsize);

	// �ƶ���дָ��
	// ���޸ĵ�ǰָ���ʱ�򲢲���Ҫ�޸ĺ���ģ���Ϊ
	// �û���Զ�޷��Ӵ��������ָ��
	INT_PTR seek_read(const INT_PTR new_pos);
	INT_PTR seek_write(const INT_PTR new_pos);

	INT_PTR achieve(const char *filename);

	
	// ��ȡ���Ա���ȡ�����ݴ�С
	// �����ӵ�ǰ��ָ�뵽λָ��ľ���
	INT_PTR getBytesCanRead();
private:
	// ��ǰ��дָ���λ��
	// ÿһ��дָ���λ�ö������������

	// offsetΪϣ���ƶ��ľ��룬����ֵΪʵ���ƶ��ľ���
	INT_PTR moveReadPointPos(const INT_PTR offset);		// ƫ�ƿ�����ǰ��
	INT_PTR moveWritePointPos(const INT_PTR offset);	//
	INT_PTR movePointer(const INT_PTR offset, INT_PTR & which_pos, ProtocolPacket * &which_packet);
	

	INT_PTR &getCurReadPos() { return header_packets_->pos.cur_read_pos_;}
	void setCurReadPos(INT_PTR new_pos) { header_packets_->pos.cur_read_pos_ = new_pos;}
	INT_PTR &getCurWritePos() { return header_packets_->pos.cur_write_pos_;}
	void setCurWritePos(INT_PTR new_pos) { header_packets_->pos.cur_write_pos_ = new_pos;}

	ProtocolPacket * &getCurReadPacket() {return header_packets_->pos.cur_read_packet_;}
	void setCurReadPacket(ProtocolPacket *packet) { header_packets_->pos.cur_read_packet_ = packet;}
	ProtocolPacket * &getCurWritePacket() {return header_packets_->pos.cur_write_packet_;}
	void setCurWritePacket(ProtocolPacket *packet) { header_packets_->pos.cur_write_packet_ = packet;}

	class Position {
	public:
		INT_PTR cur_read_pos_;
		INT_PTR cur_write_pos_;
		ProtocolPacket * cur_read_packet_;
		ProtocolPacket * cur_write_packet_;
	}pos;

	// ȡ�õ�ǰpacket�У�pos����ָ��
	char * getBufferAddr(const INT_PTR pos);

	// �ú���ֱ����ָ��λ�ÿ�ʼд�����ݣ���
	INT_PTR writeCurPacket(const char * buf, INT_PTR len, INT_PTR pos);
	INT_PTR writeToCurPos(const char * buf, INT_PTR len);
	INT_PTR readFromCurPacket(char * buf, INT_PTR len, INT_PTR pos);
	INT_PTR readFromCurPos(char * buf, INT_PTR len);
	const INT_PTR getPacketBufferSize() const { return BUF_SIZE;}
private:
	// ÿһ��packet���64k
	char buffer_[BUF_SIZE];
	const INT_PTR getPacketBufferSize() { return BUF_SIZE;}

	// �������һ��˫������
	ProtocolPacket<BUF_SIZE> * getNextPacket() { return next_packets_;}
	ProtocolPacket<BUF_SIZE> * getPrePacket() { return pre_packets_;}
	ProtocolPacket<BUF_SIZE> * next_packets_;
	ProtocolPacket<BUF_SIZE> * pre_packets_;
	ProtocolPacket<BUF_SIZE> * header_packets_;

	INT_PTR setReadPoint(const INT_PTR pos, ProtocolPacket *packet);
	INT_PTR setWritePoint(const INT_PTR pos, ProtocolPacket *packet);
	void getReadPoint(INT_PTR &pos, ProtocolPacket* &packet);

	// ���浱ǰ����֮��İ��Ĵ�С
	// ������õ�һ������totol_size_
	// ��ô�����������Ĵ�С
	INT_PTR total_size_;

	// �˹��캯��ֻ�����ڲ�����
	// ��������һ��˫������
	ProtocolPacket(ProtocolPacket*, ProtocolPacket* head);
	
	// ��ʼ������
	void init();
	yanglei_utility::CAutoCreateCS cs_;
};


//====================================
// class ProtocolPacket
template <INT_PTR BUF_SIZE>
ProtocolPacket<BUF_SIZE>::ProtocolPacket() {
	next_packets_ = NULL;
	pre_packets_ = NULL;

	header_packets_ = this;

	init();
	pos.cur_read_pos_ = 0;
	pos.cur_write_pos_= 0;
	pos.cur_read_packet_ = this;
	pos.cur_write_packet_ = this;
}

template <INT_PTR BUF_SIZE>
ProtocolPacket<BUF_SIZE>::ProtocolPacket(ProtocolPacket* pre,
										 ProtocolPacket* head) {
	pre_packets_ = pre;
	header_packets_ = head;
	init();
	pos.cur_read_pos_ = 0;
	pos.cur_write_pos_= 0;
	pos.cur_read_packet_ = NULL;
	pos.cur_write_packet_ = NULL;
}

template <INT_PTR BUF_SIZE>
ProtocolPacket<BUF_SIZE>::~ProtocolPacket() {
	if (next_packets_ != NULL)
		delete next_packets_;
}

template <INT_PTR BUF_SIZE>
void ProtocolPacket<BUF_SIZE>::init() {
	next_packets_ = NULL;
	total_size_ = 0;

	// ������0
	// memcpy(buffer_, 0, sizeof(buffer_));
}

template <INT_PTR BUF_SIZE>
char * ProtocolPacket<BUF_SIZE>::getBufferAddr(const INT_PTR pos) {
	assert(getPacketBufferSize() >= pos);
	return &(buffer_[pos]);
}


//====================================================================

template <INT_PTR BUF_SIZE>
INT_PTR ProtocolPacket<BUF_SIZE>::moveWritePointPos(const INT_PTR offset) {
	return movePointer(offset, getCurWritePos(), getCurWritePacket());
}

template <INT_PTR BUF_SIZE>
INT_PTR ProtocolPacket<BUF_SIZE>::moveReadPointPos(const INT_PTR offset) {
	return movePointer(offset, getCurReadPos(), getCurReadPacket());
}

template <INT_PTR BUF_SIZE>
INT_PTR ProtocolPacket<BUF_SIZE>::movePointer(const INT_PTR off, INT_PTR &which_pos,
											ProtocolPacket * &which_packet) {
	assert(off >= 0);
	INT_PTR offset = off;
	// ����ԭ��λ�ã�����һ����ʧ�ܵ�ʱ�򣬽�ָ��ָ��ִ
	ProtocolPacket * original_packet = which_packet;
	const INT_PTR original_pos = which_pos;
	while(offset != 0) {
		INT_PTR new_pos = offset + which_pos;
		if (new_pos >= getPacketBufferSize()) {
			// ʣ����Ĵ�С
			offset = offset - (getPacketBufferSize() - which_pos);
			which_pos = 0;

			// ��д����ָ������ƶ�
			if (which_packet->getNextPacket() != NULL) {	
				which_packet = which_packet->getNextPacket();
			} else {
				try {
					// ����ռ䲻�����һ������
					// �������ʧ�ܣ���ô�찡�����ⲿ�쳣����
					// ��read��write��������ʧ��
					which_packet->next_packets_ = 
						new ProtocolPacket<BUF_SIZE>(which_packet, header_packets_);
					which_packet = which_packet->getNextPacket();
				} catch (std::bad_alloc &) {
					which_packet = original_packet;
					which_pos = original_pos;
					throw INT_PTR(0);
				}
			}
		} else if (new_pos < 0) { // ֤��offset��С��0��
			assert(false);
		} else {
			// �ڱ������ƶ�
			which_pos = new_pos;
			offset = 0;
		}
	}
	return 0;
}

// ��д����

// �ڵ�ǰ���ƶ���λ�ö�д�� ������ʵ��д��Ĵ�С
template <INT_PTR BUF_SIZE>
INT_PTR ProtocolPacket<BUF_SIZE>::writeCurPacket(const char * buf, INT_PTR len, INT_PTR pos) {
	INT_PTR buf_free = getPacketBufferSize() - pos;

	// ȷ������д������Լ�������հ����������Ҫд��ĳ��ȣ� ��ô����
	// ���ȼ��ɣ��෴ֱ�ӷ��ؿհ�����Ĵ�С
	INT_PTR bytes_written = buf_free > len ? len : buf_free;
	memcpy(getBufferAddr(pos), buf, bytes_written);
	return bytes_written;
}

// ����д������֮�⣬������Ų��ָ�밡��
template <INT_PTR BUF_SIZE>
INT_PTR ProtocolPacket<BUF_SIZE>::writeToCurPos(const char * buf, INT_PTR len) {
	INT_PTR bytes_written = 
		getCurWritePacket()->writeCurPacket(buf, len, getCurWritePos());

	moveWritePointPos(bytes_written);
	assert(bytes_written <= len);
	return bytes_written;
}

//==================================
// ��ȡ�ɶ������ݴ�С
// �����ӵ�ǰ��ָ�뵽βָ��ľ���
template <INT_PTR BUF_SIZE>
INT_PTR ProtocolPacket<BUF_SIZE>::getBytesCanRead() {
	INT_PTR total_read_point_offset = 0;
	ProtocolPacket *packet = header_packets_;
	while (packet != getCurReadPacket()) {
		packet = packet->getNextPacket();
		total_read_point_offset += getPacketBufferSize();
	}
	total_read_point_offset += getCurReadPos();
	return getTotalSize() - total_read_point_offset;
}


//==================
// �ӵ�ǰ����ָ��λ�ö���Ϣ
template <INT_PTR BUF_SIZE>
INT_PTR ProtocolPacket<BUF_SIZE>::readFromCurPacket(char * buf, INT_PTR len, INT_PTR pos) {
	INT_PTR buf_canread = getPacketBufferSize() - pos; // ���Զ���Ĵ�С
	INT_PTR bytes_read = buf_canread > len ? len : buf_canread;  // ʵ�ʿ��Զ���Ĵ�С
	memcpy(buf, getBufferAddr(pos), bytes_read);
	return bytes_read;
}

// �ӵ�ǰλ�ö���Ϣ
// 1. ���ȼ�����Զ�ȡ��������
// 2. ��ȡ��Ϣ
// 3. �ƶ���ָ��
// 3
template <INT_PTR BUF_SIZE>
INT_PTR ProtocolPacket<BUF_SIZE>::readFromCurPos(char * buf, INT_PTR len) {
	INT_PTR bytes_read = 
		getCurReadPacket()->readFromCurPacket(buf, len, getCurReadPos());

	moveReadPointPos(bytes_read);
	assert(bytes_read <= len);
	return bytes_read;
}
template <INT_PTR BUF_SIZE>
INT_PTR ProtocolPacket<BUF_SIZE>::write(const char *buffer, const INT_PTR bufsize) {
	try {
		using namespace yanglei_utility;
		SingleLock<CAutoCreateCS> lock(&cs_);
   
		INT_PTR index = 0;
		while (index < bufsize) {
			INT_PTR wrtten = writeToCurPos(&(buffer[index]), bufsize-index);
			index += wrtten;
		}
  
		// �����ܳ��� 
		total_size_ += bufsize;
		return bufsize;
	} catch (INT_PTR) {
		return 0;
	} catch (...) {
		DEBUG_MESSAGE("ProtocolPacket write exception...");
		return 0;
	}
}

template <INT_PTR BUF_SIZE>
INT_PTR ProtocolPacket<BUF_SIZE>::read(char *buffer, const INT_PTR bufsize) {
	try {
		using namespace yanglei_utility;
		SingleLock<CAutoCreateCS> lock(&cs_);

		// ���̫���ֱ�ӷ�������������
		const INT_PTR canRead = getBytesCanRead();
		INT_PTR toRead = canRead > bufsize ? bufsize : canRead;
		INT_PTR index = 0;
		while (index < toRead) {
			INT_PTR read = readFromCurPos(&(buffer[index]), toRead-index);
			index += read;
		}
		return toRead;
	} catch (INT_PTR) {
		DEBUG_MESSAGE("ProtocolPacket INT_PTR Excpetion");
		return 0;
	} catch (...) {
		DEBUG_MESSAGE("ProtocolPacket read exception...");
		return 0;
	}
}

template <INT_PTR BUF_SIZE>
INT_PTR ProtocolPacket<BUF_SIZE>::achieve(const char *filename) {
	try {
		using namespace yanglei_utility;
		SingleLock<CAutoCreateCS> lock(&cs_);


		// ���浱ǰָ��, �ڽ����󷵻���ǰ��ָ��
		INT_PTR pos;
		ProtocolPacket* packet;
		getReadPoint(pos, packet);
		seek_read(0);
		

		std::fstream file;
		file.open(filename, std::ios::out | std::ios::app | std::ios::binary);
		const INT_PTR bufsize = 1024;
		char buffer[bufsize];
		INT_PTR dwRead = read(buffer, bufsize);
		while(dwRead != 0) {
			file.write(buffer, dwRead);
			// ��ȡ��һ��
			dwRead = read(buffer, bufsize);
		}
		file.close();

		// �ָ���ǰ��ָ��
		setReadPoint(pos, packet);
		
	} catch (...) {
		OutputDebugString("ProtocolPacket achieve exception...");
	}
	return 0;
}

// �ƶ�����ָ��

template <INT_PTR BUF_SIZE> 
INT_PTR ProtocolPacket<BUF_SIZE>::setWritePoint(const INT_PTR pos, ProtocolPacket *packet) {
	setCurWritePacket(packet);
	setCurWritePos(pos);
	return 0;
}
template <INT_PTR BUF_SIZE> 
INT_PTR ProtocolPacket<BUF_SIZE>::setReadPoint(const INT_PTR pos, ProtocolPacket *packet) {
	setCurReadPacket(packet);
	setCurReadPos(pos);
	return 0;
}

template <INT_PTR BUF_SIZE> 
void ProtocolPacket<BUF_SIZE>::getReadPoint(INT_PTR &pos, ProtocolPacket* &packet) {
	pos = getCurReadPos();
	packet = getCurReadPacket();
}

template <INT_PTR BUF_SIZE>
INT_PTR ProtocolPacket<BUF_SIZE>::seek_read(const INT_PTR new_pos) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	// ��ʼ�������ƶ�һ����****
	INT_PTR bytes_read = getPacketBufferSize();
	ProtocolPacket *packet = header_packets_;
	while (bytes_read <= new_pos) {
		bytes_read+= getPacketBufferSize();
		packet = packet->getNextPacket();
	}

	// ����ָ��
	setReadPoint(new_pos % getPacketBufferSize(), packet);
	return bytes_read;
}

// ��ȡ�������Ĵ�С
// ֻ��ͷ����getTotalSize����Ч.
template <INT_PTR BUF_SIZE>
INT_PTR ProtocolPacket<BUF_SIZE>::getTotalSize() {
	return total_size_;
}



template <INT_PTR BUF_SIZE>
INT_PTR ProtocolPacket<BUF_SIZE>::seek_write(const INT_PTR new_pos) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	// ��ʼ�������ƶ�һ����****
	INT_PTR bytes_write = getPacketBufferSize();
	ProtocolPacket *packet = header_packets_;
	while (bytes_write <= new_pos) {
		bytes_write+= getPacketBufferSize();
		packet = packet->getNextPacket();
	}

	// ����ָ��
	setWritePoint(new_pos % getPacketBufferSize(), packet);
	return bytes_write;
}
#endif  // _UTILITY_PROTOCOL_PACKET_H__