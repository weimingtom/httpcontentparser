#include "StdAfx.h"
#include ".\configreadertest.h"
#include <xmlconfiguration.h> 

using namespace CPPUNIT_NS;

//==========================================
// constructor and deconstructor
ConfigReaderTest::ConfigReaderTest(void) {
}
ConfigReaderTest::~ConfigReaderTest(void) {
}

//===========================================
//
void ConfigReaderTest::TestReadFromFile() {
	XMLConfiguration config;
	config.initialize();
}

void ConfigReaderTest::TestSaveFile() {
	XMLConfiguration config;
	config.save();
}