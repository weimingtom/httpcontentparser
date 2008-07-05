#ifndef _TESTLOGSYSTEM_LOGTEST_H__
#define _TESTLOGSYSTEM_LOGTEST_H__

#include <cppunit/extensions/HelperMacros.h>
class LogTest : public CPPUNIT_NS::TestFixture {
public: 
	CPPUNIT_TEST_SUITE(LogTest);
	CPPUNIT_TEST(LogCatalogTest);
	CPPUNIT_TEST(RegisterLogTest);
	CPPUNIT_TEST(DeleteListenerTest);
	CPPUNIT_TEST(NoneLayoutTest);
	CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();
protected:
  void LogCatalogTest();
  void RegisterLogTest();
  void DeleteListenerTest();
  void NoneLayoutTest();
};

#endif
