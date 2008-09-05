#ifndef _UTILITY_STRUTILITY_H__
#define _UTILITY_STRUTILITY_H__

#include <vector>
#include <string>

// 目前只是用于asic编码， 不能用unidcode

namespace strutility {

void trim_left(TCHAR * str, const TCHAR* trimed);
void trim_right(TCHAR * str, const TCHAR* trimed);
void trim(TCHAR * str, const TCHAR* trimed);

char *strnstr(char *src, char *des, const int len);


// 使用token分割字符床，并将分割的字符串保存在vec当中
// 调用此函数时，不能再使用strtok

// 参数 remove_spes表示 ： 是否去掉分隔符
//void splitstring_token(TCHAR *str, const char *seps, 
//	 std::vector<std::string> &vec, bool remove_spes = false);
//
//void splitstring(TCHAR *str, const char *seps, 
//	 std::vector<std::string> &vec, bool remove_spes = false);
};
#endif