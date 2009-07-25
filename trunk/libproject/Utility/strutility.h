#ifndef _UTILITY_STRUTILITY_H__
#define _UTILITY_STRUTILITY_H__

#include <vector>
#include <string>

// Ŀǰֻ������asic���룬 ������unidcode

namespace strutility {

#ifndef UNICODE
typedef std::string _tstring;
#else
typedef std::wstring _tstring;
#endif

void trim_left(TCHAR * str, const TCHAR* trimed);
void trim_right(TCHAR * str, const TCHAR* trimed);
void trim(TCHAR * str, const TCHAR* trimed);

INT_PTR remove_after(TCHAR * name, const TCHAR * tail);

// ��%ea%ad֮���UTF8ת��ȡ
char* extUTF8FromStr(const char * src, char * buffer, const INT_PTR len);

char * utf8ToDBCS(const char *utf8, char * buffer, const INT_PTR len);

// ��ȥһ����beginΪ��ͷ����endΪ��β���ַ���
// ����: src = "hello world"; begin = "o" end="o" contain = false
// result = "w"
// ����: src = "hello world"; begin = "o" end="o" contain = true
// result="wow"
INT_PTR extract_string(TCHAR *result, const INT_PTR buf_size, const TCHAR * src, const TCHAR *begin, const TCHAR *end, bool contain=false);

const TCHAR *strnstr(const TCHAR *src, const TCHAR *des, const INT_PTR len);

bool beginwith(const TCHAR *src, const TCHAR *header);
bool endwith(const TCHAR * src, const TCHAR *detail);

void strtolower(TCHAR * src);
void strtoupper(TCHAR * src);

// �ַ��Ƿ����char_set����
inline
bool isin(const TCHAR c, const TCHAR * char_set) {
	TCHAR sub[2] = {0};
	sub[0] = c;
	if (NULL != _tcsstr(char_set, sub)) {
		return true;
	} else {
		return false;
	}
}
// ���� remove_spes��ʾ �� �Ƿ�ȥ���ָ���
INT_PTR splitstring(const TCHAR *str, const char *seps, std::vector<_tstring> *vec);
};

#endif