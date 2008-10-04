#include "stdafx.h"
#include "strutility.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

namespace strutility {

void trim_right(TCHAR * str, const TCHAR* trimed) {
	const size_t len = _tcslen(str);
	for (size_t i = len-1; i >=0 && _tcschr(trimed, str[i]); ++i) {
		str[i] = '\0';
	}
}

void trim_left(TCHAR * str, const TCHAR* trimed) {
	const size_t len = _tcslen(str);
	size_t need_to_move;
	for (need_to_move = 0; need_to_move < len &&
			_tcschr(trimed, str[need_to_move]); ++need_to_move) {
		;
	}

	// 先前移动
	for (size_t i = 0; i < len - need_to_move; i++) {
		str[i] = str[i + need_to_move] ;
	}
	
	// 剩余的空间至0
	for (size_t i = 0; i < need_to_move; i++) {
		str[len-i-1] = '\0';
	}
}
void trim(TCHAR * str, TCHAR * trimed) {
	trim_right(str, trimed);
	trim_left(str, trimed);
}


const TCHAR *strnstr(const TCHAR *src, const TCHAR *des, const int len) {
	const int buf_size = 1024 * 24;
	try {
		if (buf_size > len + 1) {
			TCHAR buffer[buf_size] = {0};
			memcpy(buffer, src, len);
			TCHAR *p =  strstr(buffer, des);

			// 如果返回 NULL, 否则计算偏移量
			if (p ==  NULL) return NULL;
			else {
				return (src + (p - buffer));
			}
		} else {
			TCHAR * buffer = new TCHAR[len + 1];
			memcpy(buffer, src, len);
			TCHAR *p =  strstr(buffer, des);

			// 如果返回 NULL, 否则计算偏移量
			if (p ==  NULL) return NULL;
			else {
				return (src + (p - buffer));
			}
		}
	} catch(...) {
		return NULL;
	}
}

bool beginwith(const TCHAR *src, const TCHAR *header) {
	assert (src != NULL);
	assert (header != NULL);
	return  (src == _tcsstr(src, header)) ? true : false;
}

bool endwith(const TCHAR * src, const TCHAR *detail) {
	assert (src != NULL);
	assert (detail != NULL);
	const size_t len1 = strlen(src);
	const size_t len2 = strlen(detail);
	if (len1 < len2) {
		return false;
	} else if (0 != _tcscmp(&(src[len1-len2]), detail)) {
		return false;
	} else {
		return true;
	}
}

//void splitstring_token(TCHAR *str, const TCHAR *seps,
//				 std::vector<std::string> &vec, bool remove_spes) {
//	char * token = _tcstok(str, seps);
//	while( token != NULL )  {
//		// 去掉分隔符
//		if (remove_spes)
//			trim(token, seps);
//
//		vec.push_back(std::string(token));
//		token = _tcstok( NULL, seps );
//	}
//}
//void splitstring(TCHAR *str, const TCHAR *seps, std::vector<std::string> &vec, bool remove_spes) {
//	try {
//		const int len = _tcslen(str);
//	} catch (...) {
//	}
//}
};