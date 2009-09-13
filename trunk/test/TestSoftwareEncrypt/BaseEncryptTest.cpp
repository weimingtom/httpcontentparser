#include "StdAfx.h"
#include ".\baseencrypttest.h"
#include <string>
#include <boost\test\test_tools.hpp>

using namespace boost::unit_test;

void TestBaseEncry() {
	for (int i = 0; i < 1000; i ++) {
		std::string sn = generateSN();
		BOOST_CHECK(true == validateSN(sn));
	}
}
