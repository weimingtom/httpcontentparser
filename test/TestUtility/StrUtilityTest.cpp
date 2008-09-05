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
	char *str1  = "bbba", *str2 = "a";
	CPPUNIT_ASSERT(NULL == strnstr(str1, str2, 3));
	}

	{
	char *str1="aaabbb", *str2 = "bbb";
	CPPUNIT_ASSERT(strstr(str1, str2) == strnstr(str1, str2, 6));
	}
}