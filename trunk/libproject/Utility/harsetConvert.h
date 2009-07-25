#pragma once

class CodePage {
public:
	static const INT_PTR CODEPAGE_GB2312 = 936;
	static const INT_PTR CODEPAGE_BIG5       = 950;
	static const INT_PTR CODEPAGE_UTF16   = 1200;
	static const INT_PTR CODEPAGE_GB18030 = 54936;
	static const INT_PTR CODEPAGE_UTF8      =  65001;
};

void convert(const char * srcchar, const int srccp, char * destchar, const INT_PTR buf_size, const INT_PTR detcp);

