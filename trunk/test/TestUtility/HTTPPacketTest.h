#ifndef _UTILITY_TEST_HTTPPACKETTEST_H_
#define _UTILITY_TEST_HTTPPACKETTEST_H_

// 不好测试啊！....

// HTTPPacketTest 
void testActuallyPacket();
void testConnectionState();
void testZeorLengthPacket();
void testNoContentHeader();
void testAdd0LengthPacket();	// 添加0长度的包
void testZeroChunk();
void testNoLengthSepecified();
void testNoContentPacket();
void testSeriesPacket();
void testWrongHeader();
void testChunk();
void testAddSinglePacket();
void testAddSeriesPacket();
void testRawPacket();
void testNoContentChunk();


#endif  // _UTILITY_TEST_HTTPPACKETTEST_H_
