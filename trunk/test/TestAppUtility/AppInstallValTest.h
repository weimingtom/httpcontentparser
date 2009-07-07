#ifndef _SYSUTILITY_APPINSTALLVALTEST_H__
#define _SYSUTILITY_APPINSTALLVALTEST_H__


#include <cppunit/extensions/HelperMacros.h>

class AppInstallValTest  : public CPPUNIT_NS::TestFixture {
public:
	AppInstallValTest(void);
	~AppInstallValTest(void);

public:
	CPPUNIT_TEST_SUITE(AppInstallValTest);
	CPPUNIT_TEST(testRunInSPI);
	CPPUNIT_TEST(testShouldRepair);
	CPPUNIT_TEST(testRunInCOM);
	CPPUNIT_TEST(testRunInNone);
	CPPUNIT_TEST_SUITE_END();
private:
	void testShouldRepair();
	void testRunInCOM();
	void testRunInSPI();
	void testRunInNone();
	void testServieInstall();
};

#endif  // _SYSUTILITY_APPINSTALLVALTEST_H__