#include "stdafx.h"
#include "strutility.h"
#include <stdlib.h>
#include <stdio.h>

namespace strutility {

void trim_right(TCHAR * str, const TCHAR* trimed) {
	const int len = _tcslen(str);
	for (int i = len-1; i >=0 && _tcschr(trimed, str[i]); ++i) {
		str[i] = '\0';
	}
}

void trim_left(TCHAR * str, const TCHAR* trimed) {
	const int len = _tcslen(str);
	int need_to_move;
	for (need_to_move = 0; need_to_move < len &&
			_tcschr(trimed, str[need_to_move]); ++need_to_move) {
		;
	}

	// 先前移动
	for (int i = 0; i < len - need_to_move; i++) {
		str[i] = str[i + need_to_move] ;
	}
	
	// 剩余的空间至0
	for (int i = 0; i < need_to_move; i++) {
		str[len-i-1] = '\0';
	}
}
void trim(TCHAR * str, TCHAR * trimed) {
	trim_right(str, trimed);
	trim_left(str, trimed);
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