#ifndef _UTILITY_TEST_HTTPPACKETTEST_H_
#define _UTILITY_TEST_HTTPPACKETTEST_H_

// ���ò��԰���....

// HTTPPacketTest 
void testActuallyPacket();
void testConnectionState();
void testZeorLengthPacket();
void testNoContentHeader();
void testAdd0LengthPacket();	// ���0���ȵİ�
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
