#include "StdAfx.h"
#include ".\configreadertest.h"
#include <setting\xmlconfiguration.h> 
#include <webcontenttype.h>
#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;


//==========================================


//===========================================
//
void TestReadFromFile() {
	//XMLConfiguration config;
	//config.loadConfig();
}

void TestSaveFile() {
	XMLConfiguration config;
	//config.saveConfig(TEXT("c:\\default.xml"));
	config.loadConfig(TEXT("D:\\workspace\\current_edition\\debug\\config.xml"));
	config.saveConfig(TEXT("c:\\hello.xml"));
}