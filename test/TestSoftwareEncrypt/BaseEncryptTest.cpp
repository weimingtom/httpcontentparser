#include "StdAfx.h"
#include ".\baseencrypttest.h"
#include <string>

BaseEncryptTest::BaseEncryptTest(void) {
}

BaseEncryptTest::~BaseEncryptTest(void) {
}

void BaseEncryptTest::TestBaseEncry() {
	for (int i = 0; i < 1000; i ++) {
		std::string sn = generateSN();
		CPPUNIT_ASSERT(true == validateSN(sn));
	}
}
