#include "StdAfx.h"
#include ".\ziputilitytest.h"
#include <utility/ZipUtility.h>
#include <zlib/zlib.h>

ZipUtilityTest::ZipUtilityTest(void)
{
}

ZipUtilityTest::~ZipUtilityTest(void)
{
}


void ZipUtilityTest::testZlibUtility() {
	{
	ZipUtility<5> zip, zip2;
	char  source[] = "abcdefghj";
	zip.compress((Bytef*)source, strlen(source));
	// ʹ�ñ�׼����ѹ��
	
	char buffer[1024];
	zip2.uncompress(zip.get_buffer(), zip.get_data_size());
	CPPUNIT_ASSERT(0 == memcmp(zip2.get_buffer(), source, strlen(source)));
	}

	{
	ZipUtility<1024> zip, zip2;
	char  source[] = "abcdefghj";
	zip.compress((Bytef*)source, strlen(source));
	// ʹ�ñ�׼����ѹ��
	
	char buffer[1024];
	zip2.uncompress(zip.get_buffer(), zip.get_data_size());
	CPPUNIT_ASSERT(0 == memcmp(zip2.get_buffer(), source, strlen(source)));
	}

}