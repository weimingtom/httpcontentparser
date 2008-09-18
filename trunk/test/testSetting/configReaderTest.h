#ifndef _TEST_SETTING_CONFIGREADERTEST_H__
#define _TEST_SETTING_CONFIGREADERTEST_H__

#include <cppunit/extensions/HelperMacros.h>

class ConfigReaderTest  : public CPPUNIT_NS::TestFixture {
public:
	ConfigReaderTest(void);
	~ConfigReaderTest(void);
public:
	CPPUNIT_TEST_SUITE(ConfigReaderTest);
	CPPUNIT_TEST(TestReadFromFile);
	CPPUNIT_TEST(TestSaveFile);
	CPPUNIT_TEST_SUITE_END();

protected:
	void TestReadFromFile();
	void TestSaveFile();
};

#endif  // _TEST_SETTING_CONFIGREADERTEST_H__