#include "StdAfx.h"
#include ".\buffercallertest.h"

BufferCallerTest::BufferCallerTest(void)
{
}

BufferCallerTest::~BufferCallerTest(void)
{
}

class TestObject {
public:
	TestObject() {
		cnt = 0;
	}
	void operator()() {
		cnt ++;
	}
public:
	int cnt;
};


void BufferCallerTest::CallTest() {
	{ // TEST 1
	TestObject obj;
	BufferCaller<TestObject, 3> caller;
	
	for (int i = 0; i < 4; i++) {
		caller.Call(obj);
	}

	CPPUNIT_ASSERT(2 == obj.cnt);
	}

	{ // TEST 2
	TestObject obj;
	BufferCaller<TestObject, 3> caller;
	
	for (int i = 0; i < 7; i++) {
		caller.Call(obj);
	}

	CPPUNIT_ASSERT(3 == obj.cnt);
	}
	{ // TEST 3
	TestObject obj;
	BufferCaller<TestObject, 3> caller;
	
	for (int i = 0; i < 8; i++) {
		caller.Call(obj);
	}
	CPPUNIT_ASSERT(3 == obj.cnt);
	}
}