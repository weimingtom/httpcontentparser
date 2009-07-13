#pragma once

class CodePage {
public:
	static const int CODEPAGE_GB2312 = 936;
	static const int CODEPAGE_BIG5       = 950;
	static const int CODEPAGE_UTF16   = 1200;
	static const int CODEPAGE_GB18030 = 54936;
	static const int CODEPAGE_UTF8      =  65001;
};

void convert(const char * srcchar, const int srccp, char * destchar, const int buf_size, const int detcp);

