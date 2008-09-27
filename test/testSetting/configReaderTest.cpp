#include "StdAfx.h"
#include ".\configreadertest.h"
#include <xmlconfiguration.h> 
#include <webcontenttype.h>

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
	// config.loadConfig();
}

void ConfigReaderTest::TestSaveFile() {
	XMLConfiguration config;
	// config.initialize();
	// config.save();
}