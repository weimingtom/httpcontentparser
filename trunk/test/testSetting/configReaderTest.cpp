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
	config.initialize();
}

void ConfigReaderTest::TestSaveFile() {
	XMLConfiguration config;
	config.black_url_set.addDNS("hello");
	config.black_url_set.addDNS("hello");
	config.white_url_set.addDNS("sine");
	config.white_url_set.addDNS("google");

	config.search_rule.addBlackSearchWord("hello1");
	config.search_rule.addBlackSearchWord("hello2");
	config.search_rule.addBlackSearchWord("hello3");

	config.search_rule.addSearchHost("search1");
	config.search_rule.addSearchHost("search2");
	config.search_rule.addSearchHost("search3");
	config.search_rule.enableCheck("search1", true);
	config.search_rule.enableCheck("search2", false);
	config.search_rule.enableCheck("search3", true);

	config.content_check_.enableCheck(IMAGE_TYPE_JPEG, false);
	config.content_check_.enableCheck(IMAGE_TYPE_GIF, true);
	config.content_check_.enableCheck(IMAGE_TYPE_BMP, false);
	config.content_check_.enableCheck(IMAGE_TYPE_PNG, false);
	bool a = config.content_check_.needCheck(IMAGE_TYPE_JPEG);

	config.online_setting.enableOnlineHour(true);
	config.online_setting.setHour(6, 1, false);
	config.online_setting.setHour(1, 3, true);
	config.online_setting.setHour(2, 12, false);
	config.online_setting.setHour(3, 0, false);
	config.online_setting.setHour(0, 22, false);
	config.online_setting.setHour(6, 23, false);
	config.online_setting.setHour(6, 8, true);
	config.save();
}