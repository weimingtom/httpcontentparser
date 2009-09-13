#include "StdAfx.h"
#include ".\strutilitytest.h"
#include <utility\strutility.h>
#include <string>
#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;

using namespace strutility;


void Test_utf8ToDBCS() {
	{
		char utf8_with_surrogates[] = "\xe4\xbd\xa0\x61\x62\x63";
		char buffer[1024] = {0};
		utf8ToDBCS(utf8_with_surrogates, buffer, 1024);
 		BOOST_ASSERT(0 == strcmp("Äãabc", buffer));
	}
}
void Test_extUTF8FromStr() {
	char buffer[512];
	{
		char *p = "%a2%B5%Ca";
		extUTF8FromStr(p, buffer, 512);
		BOOST_ASSERT(0 == strcmp("\xa2\xb5\xca", buffer));
	}

	{
		char *p = "%a2abcd%B5%Ca";
		extUTF8FromStr(p, buffer, 512);
		BOOST_ASSERT(0 == strcmp(buffer, "\xa2\x61\x62\x63\x64\xb5\xca"));
	}

	{
		char *p = "abc";
		extUTF8FromStr(p, buffer, 512);
		BOOST_ASSERT(0 == strcmp(buffer, "abc"));
	}
}
void TestToLower() {
	{
	TCHAR unit[] = TEXT("idosOIJIFSL1");
	const TCHAR * result = TEXT("idosoijifsl1");
	strtolower(unit);
	BOOST_ASSERT (0 == _tcscmp(unit, result));
	}

	{
	TCHAR unit[] = TEXT("hello1");
	const TCHAR * result = TEXT("hello1");
	strtolower(unit);
	BOOST_ASSERT (0 == _tcscmp(unit, result));
	}

}
void TestToUpper() {
	{
	TCHAR unit[] = TEXT("idosOIJIFSL123");
	const TCHAR * result = TEXT("IDOSOIJIFSL123");
	strtoupper(unit);
	BOOST_ASSERT (0 == _tcscmp(unit, result));
	}
	{
	TCHAR unit[] = TEXT("idos.{}OIJIFSL");
	const TCHAR * result = TEXT("IDOS.{}OIJIFSL");
	strtoupper(unit);
	BOOST_ASSERT (0 == _tcscmp(unit, result));
	}
}

void Test_remove_after() {
	{
	TCHAR  unit[] = TEXT("abcdefghijklmn");
	TCHAR * tail = TEXT("b");
	TCHAR * result = "a";
	BOOST_ASSERT (1 == remove_after(unit, tail));
	BOOST_ASSERT (0 == _tcscmp(unit, result));
	}

	{
	TCHAR  unit[] = TEXT("abcdefghijklmn");
	TCHAR * tail = TEXT("c");
	TCHAR * result = "ab";
	BOOST_ASSERT (_tcslen(result) == remove_after(unit, tail));
	BOOST_ASSERT (0 == _tcscmp(unit, result));
	}

	{
	TCHAR  unit[] = TEXT("abcdefghijklmn");
	TCHAR * tail = TEXT("jk");
	TCHAR * result = "abcdefghi";
	BOOST_ASSERT (_tcslen(result)  == remove_after(unit, tail));
	BOOST_ASSERT (0 == _tcscmp(unit, result));
	}

	{
	TCHAR  unit[] = TEXT("abcdefghijklmn");
	TCHAR * tail = TEXT("fghi");
	TCHAR * result = "abcde";
	BOOST_ASSERT (_tcslen(result)  == remove_after(unit, tail));
	BOOST_ASSERT (0 == _tcscmp(unit, result));
	}
}

void TestSplitString() {
	{
	TCHAR * unit1 = TEXT("///////////\\\\\\\\\\\\\\,.//\\");
	std::vector<std::string> vec;
	splitstring(unit1, TEXT("\\.,//"), &vec);
	BOOST_ASSERT (0 == vec.size());
	}

	{
	TCHAR * unit1 = TEXT("....a.b.c.d.e.f....");
	std::vector<std::string> vec;
	splitstring(unit1, TEXT("\\.,//"), &vec);
	BOOST_ASSERT (6 == vec.size());
	BOOST_ASSERT (0 == _tcscmp(vec[0].c_str(), TEXT("a")));
	BOOST_ASSERT (0 == _tcscmp(vec[1].c_str(), TEXT("b")));
	BOOST_ASSERT (0 == _tcscmp(vec[2].c_str(), TEXT("c")));
	BOOST_ASSERT (0 == _tcscmp(vec[3].c_str(), TEXT("d")));
	BOOST_ASSERT (0 == _tcscmp(vec[4].c_str(), TEXT("e")));
	BOOST_ASSERT (0 == _tcscmp(vec[5].c_str(), TEXT("f")));
	}

	{
	TCHAR * unit1 = TEXT("helodiofsdf\\.,//aidjf.iijsod.vdsdo/ijasdf/;iadf");
	std::vector<std::string> vec;
	splitstring(unit1, TEXT("\\.,//"), &vec);
	BOOST_ASSERT (6 == vec.size());
	BOOST_ASSERT (0 == _tcscmp(vec[0].c_str(), TEXT("helodiofsdf")));
	BOOST_ASSERT (0 == _tcscmp(vec[1].c_str(), TEXT("aidjf")));
	BOOST_ASSERT (0 == _tcscmp(vec[2].c_str(), TEXT("iijsod")));
	BOOST_ASSERT (0 == _tcscmp(vec[3].c_str(), TEXT("vdsdo")));
	BOOST_ASSERT (0 == _tcscmp(vec[4].c_str(), TEXT("ijasdf")));
	BOOST_ASSERT (0 == _tcscmp(vec[5].c_str(), TEXT(";iadf")));
	}
}

void Test_extract_string() {
	{
	TCHAR result[1024];
	const TCHAR * src = "hello world";
	const TCHAR * beg = "o";
	BOOST_ASSERT (0 != strutility::extract_string(result, 1024, src, beg, beg, false));
	BOOST_ASSERT (0 == _tcscmp(result, TEXT(" w")));

	BOOST_ASSERT (0 != strutility::extract_string(result, 1024, src, beg, beg, true));
	BOOST_ASSERT (0 == _tcscmp(result, TEXT("o wo")));
	}

	{
	TCHAR result[1024];
	const TCHAR * src = "hhhhhhhhhhhhhhhhh";
	const TCHAR * beg = "h";
	BOOST_ASSERT (0 == strutility::extract_string(result, 1024, src, beg, beg, false));
	BOOST_ASSERT (0 == _tcscmp(result, TEXT("")));

	BOOST_ASSERT (0 != strutility::extract_string(result, 1024, src, beg, beg, true));
	BOOST_ASSERT (0 == _tcscmp(result, TEXT("hh")));
	}
}
// 
void Teststrnstr() {
	{
	TCHAR *str1  = "bbba", *str2 = "a";
	BOOST_ASSERT(NULL == strnstr(str1, str2, 3));
	}

	{
	TCHAR *str1="aaabbb", *str2 = "bbb";
	BOOST_ASSERT(strstr(str1, str2) == strnstr(str1, str2, 6));
	}
}

void TestEndWith() {
	{
	TCHAR *str1 = "aaaa", *str2 = "aa";
	BOOST_ASSERT( true  == beginwith(str1, str2));
	BOOST_ASSERT( false == beginwith(str2, str1));
	BOOST_ASSERT( true  == endwith(str1, str2));
	BOOST_ASSERT( false == endwith(str2, str1));
	}

	{
	TCHAR *str1 = "aaaa", *str2 = "aab";
	BOOST_ASSERT( false  == beginwith(str1, str2));
	BOOST_ASSERT( false == beginwith(str2, str1));
	BOOST_ASSERT( false  == endwith(str1, str2));
	BOOST_ASSERT( false == endwith(str2, str1));
	}

	{
	TCHAR *str1 = "aaaa", *str2 = "kkk";
	BOOST_ASSERT( false  == beginwith(str1, str2));
	BOOST_ASSERT( false == beginwith(str2, str1));
	BOOST_ASSERT( false  == endwith(str1, str2));
	BOOST_ASSERT( false == endwith(str2, str1));
	}

	{
	TCHAR *str1 = "akkk", *str2 = "kkk";
	BOOST_ASSERT( false  == beginwith(str1, str2));
	BOOST_ASSERT( false == beginwith(str2, str1));
	BOOST_ASSERT( true  == endwith(str1, str2));
	BOOST_ASSERT( false == endwith(str2, str1));
	}
}