#include "StdAfx.h"
#include ".\strutilitytest.h"
#include <utility\strutility.h>
#include <string>
using namespace strutility;

StrUtilityTest::StrUtilityTest(void) {
}

StrUtilityTest::~StrUtilityTest(void) {
}

void StrUtilityTest::Test_extUTF8FromStr() {
	char buffer[512];
	{
		char *p = "%a2%B5%Ca";
		extUTF8FromStr(p, buffer, 512);
		CPPUNIT_ASSERT(0 == strcmp("\xa2\xb5\xca", buffer));
	}

	{
		char *p = "%a2aaaa%B5%Ca";
		CPPUNIT_ASSERT(NULL == extUTF8FromStr(p, buffer, 512));
	}
}
void StrUtilityTest::TestToLower() {
	{
	TCHAR unit[] = TEXT("idosOIJIFSL1");
	const TCHAR * result = TEXT("idosoijifsl1");
	strtolower(unit);
	CPPUNIT_ASSERT (0 == _tcscmp(unit, result));
	}

	{
	TCHAR unit[] = TEXT("hello1");
	const TCHAR * result = TEXT("hello1");
	strtolower(unit);
	CPPUNIT_ASSERT (0 == _tcscmp(unit, result));
	}

}
void StrUtilityTest::TestToUpper() {
	{
	TCHAR unit[] = TEXT("idosOIJIFSL123");
	const TCHAR * result = TEXT("IDOSOIJIFSL123");
	strtoupper(unit);
	CPPUNIT_ASSERT (0 == _tcscmp(unit, result));
	}
	{
	TCHAR unit[] = TEXT("idos.{}OIJIFSL");
	const TCHAR * result = TEXT("IDOS.{}OIJIFSL");
	strtoupper(unit);
	CPPUNIT_ASSERT (0 == _tcscmp(unit, result));
	}
}

void StrUtilityTest::Test_remove_after() {
	{
	TCHAR  unit[] = TEXT("abcdefghijklmn");
	TCHAR * tail = TEXT("b");
	TCHAR * result = "a";
	CPPUNIT_ASSERT (1 == remove_after(unit, tail));
	CPPUNIT_ASSERT (0 == _tcscmp(unit, result));
	}

	{
	TCHAR  unit[] = TEXT("abcdefghijklmn");
	TCHAR * tail = TEXT("c");
	TCHAR * result = "ab";
	CPPUNIT_ASSERT (_tcslen(result) == remove_after(unit, tail));
	CPPUNIT_ASSERT (0 == _tcscmp(unit, result));
	}

	{
	TCHAR  unit[] = TEXT("abcdefghijklmn");
	TCHAR * tail = TEXT("jk");
	TCHAR * result = "abcdefghi";
	CPPUNIT_ASSERT (_tcslen(result)  == remove_after(unit, tail));
	CPPUNIT_ASSERT (0 == _tcscmp(unit, result));
	}

	{
	TCHAR  unit[] = TEXT("abcdefghijklmn");
	TCHAR * tail = TEXT("fghi");
	TCHAR * result = "abcde";
	CPPUNIT_ASSERT (_tcslen(result)  == remove_after(unit, tail));
	CPPUNIT_ASSERT (0 == _tcscmp(unit, result));
	}
}

void StrUtilityTest::TestSplitString() {
	{
	TCHAR * unit1 = TEXT("///////////\\\\\\\\\\\\\\,.//\\");
	std::vector<std::string> vec;
	splitstring(unit1, TEXT("\\.,//"), &vec);
	CPPUNIT_ASSERT (0 == vec.size());
	}

	{
	TCHAR * unit1 = TEXT("....a.b.c.d.e.f....");
	std::vector<std::string> vec;
	splitstring(unit1, TEXT("\\.,//"), &vec);
	CPPUNIT_ASSERT (6 == vec.size());
	CPPUNIT_ASSERT (0 == _tcscmp(vec[0].c_str(), TEXT("a")));
	CPPUNIT_ASSERT (0 == _tcscmp(vec[1].c_str(), TEXT("b")));
	CPPUNIT_ASSERT (0 == _tcscmp(vec[2].c_str(), TEXT("c")));
	CPPUNIT_ASSERT (0 == _tcscmp(vec[3].c_str(), TEXT("d")));
	CPPUNIT_ASSERT (0 == _tcscmp(vec[4].c_str(), TEXT("e")));
	CPPUNIT_ASSERT (0 == _tcscmp(vec[5].c_str(), TEXT("f")));
	}

	{
	TCHAR * unit1 = TEXT("helodiofsdf\\.,//aidjf.iijsod.vdsdo/ijasdf/;iadf");
	std::vector<std::string> vec;
	splitstring(unit1, TEXT("\\.,//"), &vec);
	CPPUNIT_ASSERT (6 == vec.size());
	CPPUNIT_ASSERT (0 == _tcscmp(vec[0].c_str(), TEXT("helodiofsdf")));
	CPPUNIT_ASSERT (0 == _tcscmp(vec[1].c_str(), TEXT("aidjf")));
	CPPUNIT_ASSERT (0 == _tcscmp(vec[2].c_str(), TEXT("iijsod")));
	CPPUNIT_ASSERT (0 == _tcscmp(vec[3].c_str(), TEXT("vdsdo")));
	CPPUNIT_ASSERT (0 == _tcscmp(vec[4].c_str(), TEXT("ijasdf")));
	CPPUNIT_ASSERT (0 == _tcscmp(vec[5].c_str(), TEXT(";iadf")));
	}
}

void StrUtilityTest::Test_extract_string() {
	{
	TCHAR result[1024];
	const TCHAR * src = "hello world";
	const TCHAR * beg = "o";
	CPPUNIT_ASSERT (0 != strutility::extract_string(result, 1024, src, beg, beg, false));
	CPPUNIT_ASSERT (0 == _tcscmp(result, TEXT(" w")));

	CPPUNIT_ASSERT (0 != strutility::extract_string(result, 1024, src, beg, beg, true));
	CPPUNIT_ASSERT (0 == _tcscmp(result, TEXT("o wo")));
	}

	{
	TCHAR result[1024];
	const TCHAR * src = "hhhhhhhhhhhhhhhhh";
	const TCHAR * beg = "h";
	CPPUNIT_ASSERT (0 == strutility::extract_string(result, 1024, src, beg, beg, false));
	CPPUNIT_ASSERT (0 == _tcscmp(result, TEXT("")));

	CPPUNIT_ASSERT (0 != strutility::extract_string(result, 1024, src, beg, beg, true));
	CPPUNIT_ASSERT (0 == _tcscmp(result, TEXT("hh")));
	}
}
// 
void StrUtilityTest::Teststrnstr() {
	{
	TCHAR *str1  = "bbba", *str2 = "a";
	CPPUNIT_ASSERT(NULL == strnstr(str1, str2, 3));
	}

	{
	TCHAR *str1="aaabbb", *str2 = "bbb";
	CPPUNIT_ASSERT(strstr(str1, str2) == strnstr(str1, str2, 6));
	}
}

void StrUtilityTest::TestEndWith() {
	{
	TCHAR *str1 = "aaaa", *str2 = "aa";
	CPPUNIT_ASSERT( true  == beginwith(str1, str2));
	CPPUNIT_ASSERT( false == beginwith(str2, str1));
	CPPUNIT_ASSERT( true  == endwith(str1, str2));
	CPPUNIT_ASSERT( false == endwith(str2, str1));
	}

	{
	TCHAR *str1 = "aaaa", *str2 = "aab";
	CPPUNIT_ASSERT( false  == beginwith(str1, str2));
	CPPUNIT_ASSERT( false == beginwith(str2, str1));
	CPPUNIT_ASSERT( false  == endwith(str1, str2));
	CPPUNIT_ASSERT( false == endwith(str2, str1));
	}

	{
	TCHAR *str1 = "aaaa", *str2 = "kkk";
	CPPUNIT_ASSERT( false  == beginwith(str1, str2));
	CPPUNIT_ASSERT( false == beginwith(str2, str1));
	CPPUNIT_ASSERT( false  == endwith(str1, str2));
	CPPUNIT_ASSERT( false == endwith(str2, str1));
	}

	{
	TCHAR *str1 = "akkk", *str2 = "kkk";
	CPPUNIT_ASSERT( false  == beginwith(str1, str2));
	CPPUNIT_ASSERT( false == beginwith(str2, str1));
	CPPUNIT_ASSERT( true  == endwith(str1, str2));
	CPPUNIT_ASSERT( false == endwith(str2, str1));
	}
}