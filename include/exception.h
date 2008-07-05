#ifndef _GLOBAL_EXCEPTION_H__
#define _GLOBAL_EXCEPTION_H__

#include <string>

namespace yanglei {
class exception {
public:
	exception(const std::string &descritpion) {
		description_ = descritpion;
	}
	exception(const int last_error_code) {
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, 	last_error_code, 0, 
			(LPTSTR) &lpMsgBuf, 0, 	NULL );
		description_ = (char*)lpMsgBuf;
	}
	~exception() {}

	const std::string & getDescritpion() {
		return description_;
	}
private:
	std::string description_;
};
};

#endif