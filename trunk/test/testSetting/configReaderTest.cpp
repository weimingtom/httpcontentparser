#include "StdAfx.h"
#include ".\configreadertest.h"
#include <setting\xmlconfiguration.h> 
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
	//XMLConfiguration config;
	//config.loadConfig();
}

void ConfigReaderTest::TestSaveFile() {
	XMLConfiguration config;
	//config.saveConfig(TEXT("c:\\default.xml"));
	config.loadConfig(TEXT("D:\\workspace\\current_edition\\debug\\config.xml"));
	config.saveConfig(TEXT("c:\\hello.xml"));
}