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

template <INT_PTR BUF_SIZE = DEFAULT_PACKET_BUFFER_SIZE>
class ProtocolPacket { 
public:
	ProtocolPacket();
	~ProtocolPacket();
	
	INT_PTR getTotalSize();

	// 从当前读写指针的位置开始读写
	INT_PTR write(const char *buffer, const INT_PTR bufsize);
	INT_PTR read(char *buffer, const INT_PTR bufsize);

	// 移动续写指针
	// 在修改当前指针的时候并不需要修改后面的，因为
	// 用户永远无法接触到后面的指针
	INT_PTR seek_read(const INT_PTR new_pos);
	INT_PTR seek_write(const INT_PTR new_pos);

	INT_PTR achieve(const char *filename);

	
	// 获取可以被读取的数据大小
	// 即：从当前读指针到位指针的距离
	INT_PTR getBytesCanRead();
private:
	// 当前读写指针的位置
	// 每一读写指针的位置都有两部分组成

	// offset为希望移动的距离，返回值为实际移动的距离
	INT_PTR moveReadPointPos(const INT_PTR offset);		// 偏移可以向前啊
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

	// 取得当前packet中，pos出的指针
	char * getBufferAddr(const INT_PTR pos);

	// 该函数直接在指定位置开始写入数据！！
	INT_PTR writeCurPacket(const char * buf, INT_PTR len, INT_PTR pos);
	INT_PTR writeToCurPos(const char * buf, INT_PTR len);
	INT_PTR readFromCurPacket(char * buf, INT_PTR len, INT_PTR pos);
	INT_PTR readFromCurPos(char * buf, INT_PTR len);
	const INT_PTR getPacketBufferSize() const { return BUF_SIZE;}
private:
	// 每一个packet最多64k
	char buffer_[BUF_SIZE];
	const INT_PTR getPacketBufferSize() { return BUF_SIZE;}

	// 自身组成一个双线链表
	ProtocolPacket<BUF_SIZE> * getNextPacket() { return next_packets_;}
	ProtocolPacket<BUF_SIZE> * getPrePacket() { return pre_packets_;}
	ProtocolPacket<BUF_SIZE> * next_packets_;
	ProtocolPacket<BUF_SIZE> * pre_packets_;
	ProtocolPacket<BUF_SIZE> * header_packets_;

	INT_PTR setReadPoint(const INT_PTR pos, ProtocolPacket *packet);
	INT_PTR setWritePoint(const INT_PTR pos, ProtocolPacket *packet);
	void getReadPoint(INT_PTR &pos, ProtocolPacket* &packet);

	// 保存当前包与之后的包的大小
	// 如果调用第一个包的totol_size_
	// 那么就是整个包的大小
	INT_PTR total_size_;

	// 此构造函数只会在内部调用
	// 用来制造一张双向链表
	ProtocolPacket(ProtocolPacket*, ProtocolPacket* head);
	
	// 初始化变量
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

	// 数据清0
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
	// 保存原有位置，在万一发生失败的时候，将指针指回执
	ProtocolPacket * original_packet = which_packet;
	const INT_PTR original_pos = which_pos;
	while(offset != 0) {
		INT_PTR new_pos = offset + which_pos;
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
					throw INT_PTR(0);
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
template <INT_PTR BUF_SIZE>
INT_PTR ProtocolPacket<BUF_SIZE>::writeCurPacket(const char * buf, INT_PTR len, INT_PTR pos) {
	INT_PTR buf_free = getPacketBufferSize() - pos;

	// 确定可以写入多少自己，如果空白区域大于需要写入的长度， 那么返回
	// 长度即可，相反直接返回空白区域的大小
	INT_PTR bytes_written = buf_free > len ? len : buf_free;
	memcpy(getBufferAddr(pos), buf, bytes_written);
	return bytes_written;
}

// 除了写入数据之外，它还会挪动指针啊！
template <INT_PTR BUF_SIZE>
INT_PTR ProtocolPacket<BUF_SIZE>::writeToCurPos(const char * buf, INT_PTR len) {
	INT_PTR bytes_written = 
		getCurWritePacket()->writeCurPacket(buf, len, getCurWritePos());

	moveWritePointPos(bytes_written);
	assert(bytes_written <= len);
	return bytes_written;
}

//==================================
// 获取可读的数据大小
// 即：从当前读指针到尾指针的距离
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
// 从当前包的指定位置读信息
template <INT_PTR BUF_SIZE>
INT_PTR ProtocolPacket<BUF_SIZE>::readFromCurPacket(char * buf, INT_PTR len, INT_PTR pos) {
	INT_PTR buf_canread = getPacketBufferSize() - pos; // 可以读入的大小
	INT_PTR bytes_read = buf_canread > len ? len : buf_canread;  // 实际可以读入的大小
	memcpy(buf, getBufferAddr(pos), bytes_read);
	return bytes_read;
}

// 从当前位置读信息
// 1. 首先计算可以读取的数据量
// 2. 读取信息
// 3. 移动度指针
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
  
		// 加上总长度 
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

		// 如果太大就直接返回整个缓冲区
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


		// 保存当前指针, 在结束后返回以前的指针
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
			// 读取下一阵
			dwRead = read(buffer, bufsize);
		}
		file.close();

		// 恢复以前的指针
		setReadPoint(pos, packet);
		
	} catch (...) {
		OutputDebugString("ProtocolPacket achieve exception...");
	}
	return 0;
}

// 移动函数指针

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

	// 初始化首先移动一个包****
	INT_PTR bytes_read = getPacketBufferSize();
	ProtocolPacket *packet = header_packets_;
	while (bytes_read <= new_pos) {
		bytes_read+= getPacketBufferSize();
		packet = packet->getNextPacket();
	}

	// 设置指针
	setReadPoint(new_pos % getPacketBufferSize(), packet);
	return bytes_read;
}

// 获取整个包的大小
// 只有头函数getTotalSize才有效.
template <INT_PTR BUF_SIZE>
INT_PTR ProtocolPacket<BUF_SIZE>::getTotalSize() {
	return total_size_;
}



template <INT_PTR BUF_SIZE>
INT_PTR ProtocolPacket<BUF_SIZE>::seek_write(const INT_PTR new_pos) {
	using namespace yanglei_utility;
	SingleLock<CAutoCreateCS> lock(&cs_);

	// 初始化首先移动一个包****
	INT_PTR bytes_write = getPacketBufferSize();
	ProtocolPacket *packet = header_packets_;
	while (bytes_write <= new_pos) {
		bytes_write+= getPacketBufferSize();
		packet = packet->getNextPacket();
	}

	// 设置指针
	setWritePoint(new_pos % getPacketBufferSize(), packet);
	return bytes_write;
}
#endif  // _UTILITY_PROTOCOL_PACKET_H__