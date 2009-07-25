#include "stdafx.h"
#include "strutility.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <vector>
#include <windows.h>
#include <utf8\utf8.h>

namespace strutility {

void strtolower(TCHAR * src) {
	const int len = static_cast<int>(_tcslen(src));
	for (int i = 0; i < len; ++i) {
		if (isupper(src[i])) {
			src[i] = _tolower(src[i]);
		}
	}
}
void strtoupper(TCHAR * src) {
	const int len = static_cast<int>(_tcslen(src));
	for (int i = 0; i < len; ++i) {
		if (islower(src[i])) {
			src[i] = _toupper(src[i]);
		}
	}
}
// ȥ��tail֮���
int remove_after(TCHAR * name, const TCHAR * tail) {
	const TCHAR * p = _tcsstr(name, tail);
	if (NULL != p) {
		const int pos = p - name;
		name[pos] = '\0';
		return pos;
	} else {
		return 0;
	}
}

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

	// ��ǰ�ƶ�
	for (size_t i = 0; i < len - need_to_move; i++) {
		str[i] = str[i + need_to_move] ;
	}
	
	// ʣ��Ŀռ���0
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

			// ������� NULL, �������ƫ����
			if (p ==  NULL) return NULL;
			else {
				return (src + (p - buffer));
			}
		} else {
			TCHAR * buffer = new TCHAR[len + 1];
			memcpy(buffer, src, len);
			TCHAR *p =  strstr(buffer, des);

			// ������� NULL, �������ƫ����
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

	const TCHAR * p = src, *q = header;
	while (1) {
		// ����Ӵ���ĸ������
		if (*p == '\0' && *q != '\0')
			return false;

		// ���Խ���
		if (*q == '\0') 
			return true;

		// �����ͬ��ֱ�ӷ���
		if (*p != *q)
			return false;

		// ����1
		p++;
		q++;
	}
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

namespace {
int charToValue(char c) {
	if (c>='A' && c<='F') {
		return 10 + c - 'A';
	} else if (c >='a' && c<='f') {
		return 10 + c - 'a';
	} else if (c >='0' && c<='9') {
		return c - '0';
	} else {
		assert (false);
		return '0';
	}
}
};

char * utf8ToDBCS(const char *utf8, char * buffer, const int len) {
	using namespace std;
	using namespace utf8;

	// ����UTF16������
	int cnt = 0;
	const int utf8len = strlen(utf8);
	unsigned short * utf16buffer = new unsigned short[utf8len];
	memset(utf16buffer, 0, sizeof(unsigned short) * utf8len);

	// ת����ΪUTF16
	vector <unsigned short> utf16result;
	utf8to16(utf8, utf8 +utf8len, back_inserter(utf16result));
	vector <unsigned short>::iterator iter  = utf16result.begin();
	for (; iter != utf16result.end(); ++iter) {
		utf16buffer[cnt++] = *iter;
	}
	
	
	WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, utf16buffer, -1, buffer, len,  NULL, (LPBOOL)&cnt);
	delete utf16buffer;

	return buffer;
}

char* extUTF8FromStr(const char * src, char * buffer, const int buflen) {
	int cnt = 0;
	int index = 0;
	const int len = strlen(src);
	

	while(cnt < len && index < buflen) {
		if (src[cnt] == '%') {
			// �������������ַ���Ȼ��ʮ����������
			assert (src[cnt+1] != NULL  && src[cnt+2] != NULL);
			if (src[cnt+1] == NULL  || src[cnt+2] == NULL) {
				return NULL;
			}

			char high = charToValue(src[cnt+1]) << 4;
			char low = charToValue(src[cnt+2]);;
			buffer[index++] = high + low;
			cnt+=3;
		} else {
			buffer[index++] = src[cnt++];
		}
	}
	buffer[index] = '\0';
	return buffer;
}

// ���ļ��Ŀ�ͷ��β��ȡ�м䣬 
// containָ���Ƿ������ͷ����β
int extract_string(TCHAR *result, const int buf_size, const TCHAR * src, const TCHAR *begin, const TCHAR *end, bool contain) {
	memset(result, 0, sizeof(TCHAR) * buf_size);
	const TCHAR * src_beg = _tcsstr(src, begin);
	// ����޷��ҵ���ͷ
	if (NULL == src_beg) 
		return 0;
	// ����Ѿ����˽�β
	if (src_beg[strlen(begin)] == NULL)
		return 0;

	// �ӿ�ͷ�����
	const TCHAR * src_end = _tcsstr(src_beg + _tcslen(begin), end);
	// ���δ�ҵ�
	if (NULL == src_end) 
		return 0;

	// ��������
	const TCHAR * copy_beg = contain ? src_beg: src_beg + _tcslen(begin);
	const TCHAR * copy_end = contain ? src_end + _tcslen(end) : src_end;
	int size = (int)(copy_end - copy_beg > buf_size ? buf_size : copy_end - copy_beg);
	memcpy(result, copy_beg, size * sizeof(TCHAR));
	return (int)_tcslen(result);
}

int splitstring(const TCHAR *str, const TCHAR *seps, std::vector<_tstring> * vec) {
	try {
		assert (NULL != vec);
		// ��ȡ����
		const int bufsize  = (int)_tcslen(str) + 1;
		
		// ���仺����
		TCHAR * buffer = new TCHAR[bufsize];
		const TCHAR * beg = str, *end = beg+1;
		while (NULL != *beg) {
			if (isin(*beg, seps) == true) {
				beg++;
				end = beg + 1;
			} else if (isin(*end, seps) == false && NULL != *end) {
				end++;
			} else {
				memset(buffer, 0, sizeof(TCHAR) * bufsize);
				memcpy(buffer, beg, (end - beg) * sizeof(TCHAR));
				vec->push_back(buffer);
				beg = end;
				end = beg +1;
			}
		}

		delete[] buffer;
		return (int)vec->size();
	} catch (...) {
		return 0;
	}
}

};