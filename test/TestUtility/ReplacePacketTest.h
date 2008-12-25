#ifndef _TEST_UTILITY_REPLACEPACKET_TEST_H__
#define _TEST_UTILITY_REPLACEPACKET_TEST_H__

#include "stdafx.h"

using namespace CPPUNIT_NS;
class ReplacePacketTest  : public TestFixture {
public:
	ReplacePacketTest(void);
	~ReplacePacketTest(void);

	CPPUNIT_TEST_SUITE(ReplacePacketTest);
	CPPUNIT_TEST(testNewPacket);
	CPPUNIT_TEST_SUITE_END();

private:
	void testNewPacket();
};

#endif  // _TEST_UTILITY_REPLACEPACKET_TEST_H__
