#ifndef _UTILITY_PROTOCOL_PACKET_H__
#define _UTILITY_PROTOCOL_PACKET_H__

// 存在一些问题
// 1. 每次读数据读到结尾部分都会创建一个新包
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

	// 从当前读写指针的位置开始读写
	int write(const char *buffer, const int bufsize);
	int read(char *buffer, const int bufsize);

	// 移动续写指针
	// 在修改当前指针的时候并不需要修改后面的，因为
	// 用户永远无法接触到后面的指针
	int seek_read(const int new_pos);
	int seek_write(const int new_pos);

	int achieve(const char *filename);

	
	// 获取可以被读取的数据大小
	// 即：从当前读指针到位指针的距离
	int getBytesCanRead();

public:
	class iterator {
	private:
		friend class ProtocolPacket;
		int cur_write_pos_;
		ProtocolPacket * cur_read_packet_;
	};
private:
	// 当前读写指针的位置
	// 每一读写指针的位置都有两部分组成

	// offset为希望移动的距离，返回值为实际移动的距离
	int moveReadPointPos(const int offset);		// 偏移可以向前啊
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

	// 取得当前packet中，pos出的指针
	char * getBufferAddr(const int pos);

	// 该函数直接在指定位置开始写入数据！！
	int writeCurPacket(const char * buf, int len, int pos);
	int writeToCurPos(const char * buf, int len);
	int readFromCurPacket(char * buf, int len, int pos);
	int readFromCurPos(char * buf, int len);
	const int getPacketBufferSize() const { return BUF_SIZE;}
private:
	// 每一个packet最多64k
	char buffer_[BUF_SIZE];
	const int getPacketBufferSize() { return BUF_SIZE;}

	// 自身组成一个双线链表
	ProtocolPacket<BUF_SIZE> * getNextPacket() { return next_packets_;}
	ProtocolPacket<BUF_SIZE> * getPrePacket() { return pre_packets_;}
	ProtocolPacket<BUF_SIZE> * next_packets_;
	ProtocolPacket<BUF_SIZE> * pre_packets_;
	ProtocolPacket<BUF_SIZE> * header_packets_;

	// 保存当前包与之后的包的大小
	// 如果调用第一个包的totol_size_
	// 那么就是整个包的大小
	int total_size_;

	// 此构造函数只会在内部调用
	// 用来制造一张双向链表
	ProtocolPacket(ProtocolPacket*, ProtocolPacket* head);
	
	// 初始化变量
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

	// 数据清0
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
	// 保存原有位置，在万一发生失败的时候，将指针指回执
	ProtocolPacket * original_packet = which_packet;
	const int original_pos = which_pos;
	while(offset != 0) {
		int new_pos = offset + which_pos;
		if (new_pos >= getPacketBufferSize()) {
			// 剩余包的大小
			offset = offset - (getPacketBufferSize() - which_pos);
			which_pos = 0;

			// 读写包的指针向后移动
			if (which_packet->getNextPacket() != NULL) {	
				which_packet = which_packet->getNextPacket();
			} else {
				try {
					// 如果空间不足分配一个包；
					// 如果分配失败，怎么办啊？？外部异常处理
					// 在read和write出，返回失败
					which_packet->next_packets_ = 
						new ProtocolPacket<BUF_SIZE>(which_packet, header_packets_);
					which_packet = which_packet->getNextPacket();
				} catch (std::bad_alloc &) {
					which_packet = original_packet;
					which_pos = original_pos;
					throw int(0);
				}
			}
		} else if (new_pos < 0) { // 证明offset是小于0的
			assert(false);
		} else {
			// 在本包内移动
			which_pos = new_pos;
			offset = 0;
		}
	}
	return 0;
}

// 读写函数

// 在当前包制定的位置读写， 并返回实际写入的大小
template <int BUF_SIZE>
int ProtocolPacket<BUF_SIZE>::writeCurPacket(const char * buf, int len, int pos) {
	int buf_free = getPacketBufferSize() - pos;

	// 确定可以写入多少自己，如果空白区域大于需要写入的长度， 那么返回
	// 长度即可，相反直接返回空白区域的大小
	int bytes_written = buf_free > len ? len : buf_free;
	memcpy(getBufferAddr(pos), buf, bytes_written);
	return bytes_written;
}

// 除了写入数据之外，它还会挪动指针啊！
template <int BUF_SIZE>
int ProtocolPacket<BUF_SIZE>::writeToCurPos(const char * buf, int len) {
	int bytes_written = 
		getCurWritePacket()->writeCurPacket(buf, len, getCurWritePos());

	moveWritePointPos(bytes_written);
	assert(bytes_written <= len);
	return bytes_written;
}

//==================================
// 获取可读的数据大小
// 即：从当前读指针到尾指针的距离
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
// 从当前包的指定位置读信息
template <int BUF_SIZE>
int ProtocolPacket<BUF_SIZE>::readFromCurPacket(char * buf, int len, int pos) {
	int buf_canread = getPacketBufferSize() - pos; // 可以读入的大小
	int bytes_read = buf_canread > len ? len : buf_canread;  // 实际可以读入的大小
	memcpy(buf, getBufferAddr(pos), bytes_read);
	return bytes_read;
}

// 从当前位置读信息
// 1. 首先计算可以读取的数据量
// 2. 读取信息
// 3. 移动度指针
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
 
		// 加上总长度
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

		// 如果太大就直接返回整个缓冲区
		const int canRead = getBytesCanRead();
		int toRead = canRead > bufsize ? bufsize : canRead;
		int index = 0;
		while (index < toRead) {
			int read = readFromCurPos(&(buffer[index]), toRead-index);
			index += read;
		}
		return toRead;
	} catch (int) {
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

		std::fstream file;
		file.open(filename, std::ios::out | std::ios::app | std::ios::binary);
		const int bufsize = 1024;
		char buffer[bufsize];
		int dwRead = read(buffer, bufsize);
		while(dwRead != 0) {
			file.write(buffer, dwRead);
			// 读取下一阵
			dwRead = read(buffer, bufsize);
		}
		file.close();
	} catch (...) {
		OutputDebugString("ProtocolPacket achieve exception...");
	}
	return 0;
}
// 移动函数指针
template <int BUF_SIZE>
int ProtocolPacket<BUF_SIZE>::seek_read(const int new_pos) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	// 初始化首先移动一个包****
	int bytes_read = getPacketBufferSize();
	ProtocolPacket *packet = header_packets_;
	while (bytes_read <= new_pos) {
		bytes_read+= getPacketBufferSize();
		packet = packet->getNextPacket();
	}

	// 设置指针
	setCurReadPacket(packet);
	setCurReadPos(new_pos % getPacketBufferSize());
	return bytes_read;
}

// 获取整个包的大小
// 只有头函数getTotalSize才有效.
template <int BUF_SIZE>
int ProtocolPacket<BUF_SIZE>::getTotalSize() {
	return total_size_;
}


template <int BUF_SIZE>
int ProtocolPacket<BUF_SIZE>::seek_write(const int new_pos) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	// 初始化首先移动一个包****
	int bytes_write = getPacketBufferSize();
	ProtocolPacket *packet = header_packets_;
	while (bytes_write <= new_pos) {
		bytes_write+= getPacketBufferSize();
		packet = packet->getNextPacket();
	}

	// 设置指针
	setCurWritePacket(packet);
	setCurWritePos(new_pos % getPacketBufferSize());
	return bytes_write;
}
#endif  // _UTILITY_PROTOCOL_PACKET_H__