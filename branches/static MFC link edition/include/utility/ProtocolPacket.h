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

template <int BUF_SIZE = DEFAULT_PACKET_BUFFER_SIZE>
class ProtocolPacket { 
public:
	ProtocolPacket();
	~ProtocolPacket();
	
	int getTotalSize();

	// �ӵ�ǰ��дָ���λ�ÿ�ʼ��д
	int write(const char *buffer, const int bufsize);
	int read(char *buffer, const int bufsize);

	// �ƶ���дָ��
	// ���޸ĵ�ǰָ���ʱ�򲢲���Ҫ�޸ĺ���ģ���Ϊ
	// �û���Զ�޷��Ӵ��������ָ��
	int seek_read(const int new_pos);
	int seek_write(const int new_pos);

	int achieve(const char *filename);

	
	// ��ȡ���Ա���ȡ�����ݴ�С
	// �����ӵ�ǰ��ָ�뵽λָ��ľ���
	int getBytesCanRead();
private:
	// ��ǰ��дָ���λ��
	// ÿһ��дָ���λ�ö������������

	// offsetΪϣ���ƶ��ľ��룬����ֵΪʵ���ƶ��ľ���
	int moveReadPointPos(const int offset);		// ƫ�ƿ�����ǰ��
	int moveWritePointPos(const int offset);	//
	int movePointer(const int offset, int & which_pos, ProtocolPacket * &which_packet);
	

	int &getCurReadPos() { return header_packets_->pos.cur_read_pos_;}
	void setCurReadPos(int new_pos) { header_packets_->pos.cur_read_pos_ = new_pos;}
	int &getCurWritePos() { return header_packets_->pos.cur_write_pos_;}
	void setCurWritePos(int new_pos) { header_packets_->pos.cur_write_pos_ = new_pos;}

	ProtocolPacket * &getCurReadPacket() {return header_packets_->pos.cur_read_packet_;}
	void setCurReadPacket(ProtocolPacket *packet) { header_packets_->pos.cur_read_packet_ = packet;}
	ProtocolPacket * &getCurWritePacket() {return header_packets_->pos.cur_write_packet_;}
	void setCurWritePacket(ProtocolPacket *packet) { header_packets_->pos.cur_write_packet_ = packet;}

	class Position {
	public:
		int cur_read_pos_;
		int cur_write_pos_;
		ProtocolPacket * cur_read_packet_;
		ProtocolPacket * cur_write_packet_;
	}pos;

	// ȡ�õ�ǰpacket�У�pos����ָ��
	char * getBufferAddr(const int pos);

	// �ú���ֱ����ָ��λ�ÿ�ʼд�����ݣ���
	int writeCurPacket(const char * buf, int len, int pos);
	int writeToCurPos(const char * buf, int len);
	int readFromCurPacket(char * buf, int len, int pos);
	int readFromCurPos(char * buf, int len);
	const int getPacketBufferSize() const { return BUF_SIZE;}
private:
	// ÿһ��packet���64k
	char buffer_[BUF_SIZE];
	const int getPacketBufferSize() { return BUF_SIZE;}

	// �������һ��˫������
	ProtocolPacket<BUF_SIZE> * getNextPacket() { return next_packets_;}
	ProtocolPacket<BUF_SIZE> * getPrePacket() { return pre_packets_;}
	ProtocolPacket<BUF_SIZE> * next_packets_;
	ProtocolPacket<BUF_SIZE> * pre_packets_;
	ProtocolPacket<BUF_SIZE> * header_packets_;

	int setReadPoint(const int pos, ProtocolPacket *packet);
	int setWritePoint(const int pos, ProtocolPacket *packet);
	void getReadPoint(int &pos, ProtocolPacket* &packet);

	// ���浱ǰ����֮��İ��Ĵ�С
	// ������õ�һ������totol_size_
	// ��ô�����������Ĵ�С
	int total_size_;

	// �˹��캯��ֻ�����ڲ�����
	// ��������һ��˫������
	ProtocolPacket(ProtocolPacket*, ProtocolPacket* head);
	
	// ��ʼ������
	void init();
	yanglei_utility::CAutoCreateCS cs_;
};


//====================================
// class ProtocolPacket
template <int BUF_SIZE>
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

template <int BUF_SIZE>
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

template <int BUF_SIZE>
ProtocolPacket<BUF_SIZE>::~ProtocolPacket() {
	if (next_packets_ != NULL)
		delete next_packets_;
}

template <int BUF_SIZE>
void ProtocolPacket<BUF_SIZE>::init() {
	next_packets_ = NULL;
	total_size_ = 0;

	// ������0
	// memcpy(buffer_, 0, sizeof(buffer_));
}

template <int BUF_SIZE>
char * ProtocolPacket<BUF_SIZE>::getBufferAddr(const int pos) {
	assert(getPacketBufferSize() >= pos);
	return &(buffer_[pos]);
}


//====================================================================

template <int BUF_SIZE>
int ProtocolPacket<BUF_SIZE>::moveWritePointPos(const int offset) {
	return movePointer(offset, getCurWritePos(), getCurWritePacket());
}

template <int BUF_SIZE>
int ProtocolPacket<BUF_SIZE>::moveReadPointPos(const int offset) {
	return movePointer(offset, getCurReadPos(), getCurReadPacket());
}

template <int BUF_SIZE>
int ProtocolPacket<BUF_SIZE>::movePointer(const int off, int &which_pos,
											ProtocolPacket * &which_packet) {
	assert(off >= 0);
	int offset = off;
	// ����ԭ��λ�ã�����һ����ʧ�ܵ�ʱ�򣬽�ָ��ָ��ִ
	ProtocolPacket * original_packet = which_packet;
	const int original_pos = which_pos;
	while(offset != 0) {
		int new_pos = offset + which_pos;
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
					throw int(0);
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
template <int BUF_SIZE>
int ProtocolPacket<BUF_SIZE>::writeCurPacket(const char * buf, int len, int pos) {
	int buf_free = getPacketBufferSize() - pos;

	// ȷ������д������Լ�������հ����������Ҫд��ĳ��ȣ� ��ô����
	// ���ȼ��ɣ��෴ֱ�ӷ��ؿհ�����Ĵ�С
	int bytes_written = buf_free > len ? len : buf_free;
	memcpy(getBufferAddr(pos), buf, bytes_written);
	return bytes_written;
}

// ����д������֮�⣬������Ų��ָ�밡��
template <int BUF_SIZE>
int ProtocolPacket<BUF_SIZE>::writeToCurPos(const char * buf, int len) {
	int bytes_written = 
		getCurWritePacket()->writeCurPacket(buf, len, getCurWritePos());

	moveWritePointPos(bytes_written);
	assert(bytes_written <= len);
	return bytes_written;
}

//==================================
// ��ȡ�ɶ������ݴ�С
// �����ӵ�ǰ��ָ�뵽βָ��ľ���
template <int BUF_SIZE>
int ProtocolPacket<BUF_SIZE>::getBytesCanRead() {
	int total_read_point_offset = 0;
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
template <int BUF_SIZE>
int ProtocolPacket<BUF_SIZE>::readFromCurPacket(char * buf, int len, int pos) {
	int buf_canread = getPacketBufferSize() - pos; // ���Զ���Ĵ�С
	int bytes_read = buf_canread > len ? len : buf_canread;  // ʵ�ʿ��Զ���Ĵ�С
	memcpy(buf, getBufferAddr(pos), bytes_read);
	return bytes_read;
}

// �ӵ�ǰλ�ö���Ϣ
// 1. ���ȼ�����Զ�ȡ��������
// 2. ��ȡ��Ϣ
// 3. �ƶ���ָ��
// 3
template <int BUF_SIZE>
int ProtocolPacket<BUF_SIZE>::readFromCurPos(char * buf, int len) {
	int bytes_read = 
		getCurReadPacket()->readFromCurPacket(buf, len, getCurReadPos());

	moveReadPointPos(bytes_read);
	assert(bytes_read <= len);
	return bytes_read;
}
template <int BUF_SIZE>
int ProtocolPacket<BUF_SIZE>::write(const char *buffer, const int bufsize) {
	try {
		using namespace yanglei_utility;
		SingleLock<CAutoCreateCS> lock(&cs_);
   
		int index = 0;
		while (index < bufsize) {
			int wrtten = writeToCurPos(&(buffer[index]), bufsize-index);
			index += wrtten;
		}
  
		// �����ܳ��� 
		total_size_ += bufsize;
		return bufsize;
	} catch (int) {
		return 0;
	} catch (...) {
		DEBUG_MESSAGE("ProtocolPacket write exception...");
		return 0;
	}
}

template <int BUF_SIZE>
int ProtocolPacket<BUF_SIZE>::read(char *buffer, const int bufsize) {
	try {
		using namespace yanglei_utility;
		SingleLock<CAutoCreateCS> lock(&cs_);

		// ���̫���ֱ�ӷ�������������
		const int canRead = getBytesCanRead();
		int toRead = canRead > bufsize ? bufsize : canRead;
		int index = 0;
		while (index < toRead) {
			int read = readFromCurPos(&(buffer[index]), toRead-index);
			index += read;
		}
		return toRead;
	} catch (int) {
		DEBUG_MESSAGE("ProtocolPacket int Excpetion");
		return 0;
	} catch (...) {
		DEBUG_MESSAGE("ProtocolPacket read exception...");
		return 0;
	}
}

template <int BUF_SIZE>
int ProtocolPacket<BUF_SIZE>::achieve(const char *filename) {
	try {
		using namespace yanglei_utility;
		SingleLock<CAutoCreateCS> lock(&cs_);


		// ���浱ǰָ��, �ڽ����󷵻���ǰ��ָ��
		int pos;
		ProtocolPacket* packet;
		getReadPoint(pos, packet);
		seek_read(0);
		

		std::fstream file;
		file.open(filename, std::ios::out | std::ios::app | std::ios::binary);
		const int bufsize = 1024;
		char buffer[bufsize];
		int dwRead = read(buffer, bufsize);
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

template <int BUF_SIZE> 
int ProtocolPacket<BUF_SIZE>::setWritePoint(const int pos, ProtocolPacket *packet) {
	setCurWritePacket(packet);
	setCurWritePos(pos);
	return 0;
}
template <int BUF_SIZE> 
int ProtocolPacket<BUF_SIZE>::setReadPoint(const int pos, ProtocolPacket *packet) {
	setCurReadPacket(packet);
	setCurReadPos(pos);
	return 0;
}

template <int BUF_SIZE> 
void ProtocolPacket<BUF_SIZE>::getReadPoint(int &pos, ProtocolPacket* &packet) {
	pos = getCurReadPos();
	packet = getCurReadPacket();
}

template <int BUF_SIZE>
int ProtocolPacket<BUF_SIZE>::seek_read(const int new_pos) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	// ��ʼ�������ƶ�һ����****
	int bytes_read = getPacketBufferSize();
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
template <int BUF_SIZE>
int ProtocolPacket<BUF_SIZE>::getTotalSize() {
	return total_size_;
}



template <int BUF_SIZE>
int ProtocolPacket<BUF_SIZE>::seek_write(const int new_pos) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	// ��ʼ�������ƶ�һ����****
	int bytes_write = getPacketBufferSize();
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