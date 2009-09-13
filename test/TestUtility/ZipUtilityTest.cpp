#include "StdAfx.h"
#include ".\ziputilitytest.h"
#include <utility/ZipUtility.h>
#include <zlib/zlib.h>

#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;


void testZlibUtility() {
	{
	ZipUtility<5> zip, zip2;
	char  source[] = "abcdefghj";
	zip.compress((Bytef*)source, (int)strlen(source));
	// 使用标准方法压缩
	
	zip2.uncompress(zip.get_buffer(), zip.get_data_size());
	BOOST_ASSERT(0 == memcmp(zip2.get_buffer(), source, (int)strlen(source)));
	}

	{
	ZipUtility<1024> zip, zip2;
	char  source[] = "abcdefghj";
	zip.compress((Bytef*)source, (int)strlen(source));
	// 使用标准方法压缩
	
	zip2.uncompress(zip.get_buffer(), zip.get_data_size());
	BOOST_ASSERT(0 == memcmp(zip2.get_buffer(), source, (int)strlen(source)));
	}

}