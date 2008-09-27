#include "StdAfx.h"
#include ".\strutilitytest.h"
#include <utility\strutility.h>
using namespace strutility;

StrUtilityTest::StrUtilityTest(void) {
}

StrUtilityTest::~StrUtilityTest(void) {
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