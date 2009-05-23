#ifndef _TESTAPPUTILITY_SHELLEXTTEST_H__
#define _TESTAPPUTILITY_SHELLEXTTEST_H__


#include <cppunit/extensions/HelperMacros.h>

class ShellExtTest  : public CPPUNIT_NS::TestFixture  {
public:
	ShellExtTest(void);
	~ShellExtTest(void);

	CPPUNIT_TEST_SUITE(ShellExtTest);
	CPPUNIT_TEST(testShellExt);
	CPPUNIT_TEST_SUITE_END();
private:
	void testShellExt();

	bool copyhook_installed;
	bool appcontrol_installed;
};

#endif  // _TESTAPPUTILITY_SHELLEXTTEST_H__