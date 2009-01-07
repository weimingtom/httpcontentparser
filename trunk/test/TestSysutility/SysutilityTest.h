#ifndef _TESTUTILITY_SYSUTILITYTEST_H__
#define _TESTUTILITY_SYSUTILITYTEST_H__


#include <cppunit/extensions/HelperMacros.h>

class SysutilityTest : public CPPUNIT_NS::TestFixture {
public:
	SysutilityTest(void);
	~SysutilityTest(void);
public:
	CPPUNIT_TEST_SUITE(SysutilityTest);
	CPPUNIT_TEST(testGetMainUIName);
	CPPUNIT_TEST(testGetInstallPath);
	CPPUNIT_TEST(testGetAppConfigFilename);
	CPPUNIT_TEST(testGetImageDirectory);
	CPPUNIT_TEST(testGetPageDirectory);
	CPPUNIT_TEST(testGetRecordConfigfile);
	CPPUNIT_TEST(testGetFileNameDir);
	CPPUNIT_TEST(testRegisterOper);
	CPPUNIT_TEST_SUITE_END();
protected:
	void testGetMainUIName();
	void testGetInstallPath();
	void testGetAppConfigFilename();
	void testGetImageDirectory();
	void testGetPageDirectory();
	void testGetRecordConfigfile();
	void testGetFileNameDir();
	void testRegisterOper();
};

#endif  // _TESTUTILITY_SYSUTILITYTEST_H__