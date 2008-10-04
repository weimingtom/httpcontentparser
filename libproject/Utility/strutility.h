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

const TCHAR *strnstr(const TCHAR *src, const TCHAR *des, const int len);

bool beginwith(const TCHAR *src, const TCHAR *header);
bool endwith(const TCHAR * src, const TCHAR *detail);


// ʹ��token�ָ��ַ����������ָ���ַ���������vec����
// ���ô˺���ʱ��������ʹ��strtok

// ���� remove_spes��ʾ �� �Ƿ�ȥ���ָ���
//void splitstring_token(TCHAR *str, const char *seps, 
//	 std::vector<std::string> &vec, bool remove_spes = false);
//
//void splitstring(TCHAR *str, const char *seps, 
//	 std::vector<std::string> &vec, bool remove_spes = false);
};
#endif