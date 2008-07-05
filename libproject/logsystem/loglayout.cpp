#include "precomp.h"
#include ".\loglayout.h"
#include <string>
#include <malloc.h>
#include <time.h>

namespace LogSystem {

const char * LogLayout::ALLOC_FAILED_MSG = "Alloc Buffer Failed!";
const std::string LogLayout::LAYOUT_BASIC = "LOGSYSTEM_DEFINE_BASIC";
const std::string LogLayout::LAYOUT_NONE =  "LOGSYSTEM_DEFINE_NONE";

class NoneLogLayout : public LogLayout {
public:
	virtual std::string getFmtMsg(const char *msg) {
		return std::string(msg);
	}
private:
	friend class LogLayout;
	NoneLogLayout() {}
};

namespace {
class BasicLogLayout : public LogLayout {
public:
	virtual std::string getFmtMsg(const char *msg);

private:
	friend class LogLayout;
	BasicLogLayout();
};

BasicLogLayout::BasicLogLayout() {
}

std::string BasicLogLayout::getFmtMsg(const char *msg) {
	time_t t = time(0); 
	char tmp[1024];
	strftime(tmp, sizeof(tmp), "[%Y/%m/%d %H:%M:%S] ",localtime(&t));

	std::string fullMsg = tmp;
	fullMsg.append(msg);
	return fullMsg;
}

};

//===========================================================
// 
 

LogLayout * LogLayout::Create(const std::string &type) {
	if (type == LAYOUT_BASIC) {
		static BasicLogLayout layout;
		return &layout;
	} else if (type == LAYOUT_NONE) {
		static NoneLogLayout layout;
		return &layout;
	} else {
		return NULL;
	}
}

LogLayout::LogLayout() {
	AllocBuffer();
}
LogLayout::~LogLayout() {
	FreeBuffer();
}

inline
int LogLayout::AdjustBuffer() {
	buffer_size_ *= 2;
	buffer_ = (char*)realloc((void*)buffer_, buffer_size_);
	if (buffer_ == NULL) {
		buffer_size_ = 0;
	}
	return buffer_size_;
}
inline 
int LogLayout::AllocBuffer() {
	buffer_ = (char*)malloc(buffer_size_ * sizeof(char));
	if (buffer_ == NULL) {
		buffer_size_ = 0;
	}

	return buffer_size_;
}
inline
int LogLayout::FreeBuffer() {
	if (buffer_ != NULL) {
		free((void*)buffer_);
		buffer_ = NULL;
	}
	return buffer_size_;
}

};
