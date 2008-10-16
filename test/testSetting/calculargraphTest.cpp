#include "StdAfx.h"
#include ".\calculargraphtest.h"
#include <calculagraph.h>

CalculargraphTest::CalculargraphTest(void) {
}

CalculargraphTest::~CalculargraphTest(void) {
}
void CalculargraphTest::testMulitSetTimeLeft() {
	const int type = 3;
	MultiCalculagraph<type> calculargraph;
	calculargraph.setTimespan(1, 0);
	calculargraph.setTimespan(15, 1);
	calculargraph.setTimespan(1, 2);
	calculargraph.initialize(0);

	CPPUNIT_ASSERT(calculargraph.getCurrentState() == 0);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);
	Sleep(1200);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == true);
	CPPUNIT_ASSERT(calculargraph.getCurrentState() == 1);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);

	calculargraph.setRemainTime(1);
	Sleep(1200);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == true);
	CPPUNIT_ASSERT(calculargraph.getCurrentState() == 2);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);
}
void CalculargraphTest::TestSetTimeEscape() {
	Calculagraph calculargraph;
	calculargraph.setTimespan(5);
	calculargraph.initialize();

	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);
	calculargraph.setTimeEscape(6);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == true);

}
void CalculargraphTest::TestCulargraph() {
	Calculagraph calculargraph;
	calculargraph.setTimespan(1);
	calculargraph.initialize();

	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);
	Sleep(1200);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == true);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);
	Sleep(1300);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == true);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);
}

void CalculargraphTest::TestMultiCalculargraph() {
	const int type = 3;
	MultiCalculagraph<type> calculargraph;
	calculargraph.setTimespan(1, 0);
	calculargraph.setTimespan(2, 1);
	calculargraph.setTimespan(1, 2);
	calculargraph.initialize(0);

	CPPUNIT_ASSERT(calculargraph.getCurrentState() == 0);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);
	Sleep(1200);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == true);
	CPPUNIT_ASSERT(calculargraph.getCurrentState() == 1);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);

	Sleep(2200);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == true);
	CPPUNIT_ASSERT(calculargraph.getCurrentState() == 2);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);

	Sleep(2200);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == true);
	CPPUNIT_ASSERT(calculargraph.getCurrentState() == 0);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);

	Sleep(2200);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == true);
	CPPUNIT_ASSERT(calculargraph.getCurrentState() == 1);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);
}