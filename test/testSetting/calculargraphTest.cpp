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
	int x = calculargraph.getRemainTimeMS();
	CPPUNIT_ASSERT(calculargraph.trySwitch() == true);
	CPPUNIT_ASSERT(calculargraph.getCurrentState() == 1);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);

	calculargraph.setRemainTime(1);
	Sleep(1200);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == true);
	CPPUNIT_ASSERT(calculargraph.getCurrentState() == 2);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);
}

void CalculargraphTest::TestSetASmallerTime() {
	Calculagraph calculargraph;
	calculargraph.setTimespan(10);
	calculargraph.initialize();

	calculargraph.setTimespan(1);
	CPPUNIT_ASSERT(calculargraph.getRemainTime() > 0);
}
void CalculargraphTest::TestSetTimeEscape() {
	Calculagraph calculargraph;
	calculargraph.setTimespan(5);
	calculargraph.initialize();

	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);
	calculargraph.setTimeEscape(6);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == true);
}

// 多个状态的计时器
void CalculargraphTest::testMultiStopTimer() {
	const int type = 3;
	MultiCalculagraph<type> calculargraph;
	calculargraph.setTimespan(3, 0);
	calculargraph.setTimespan(4, 1);
	calculargraph.setTimespan(1, 2);
	calculargraph.initialize(0);

	
	CPPUNIT_ASSERT(calculargraph.getCurrentState() == 0);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);

	// 停止
	Sleep(1300);
	int x3= calculargraph.getRemainTime();
	calculargraph.stop();
	int escape1 = calculargraph.getRemainTimeMS();
	Sleep(600);
	int escape2 = calculargraph.getRemainTimeMS();
	CPPUNIT_ASSERT(0 != escape1);
	CPPUNIT_ASSERT(0 != escape2);
	CPPUNIT_ASSERT(escape1 == escape2);

	// 重新开始
	calculargraph.restart();

	CPPUNIT_ASSERT(calculargraph.getCurrentState() == 0);
	int x1 = calculargraph.getRemainTimeMS();
	Sleep(1800);
	int x2 = calculargraph.getRemainTimeMS();
	CPPUNIT_ASSERT(calculargraph.trySwitch() == true);
	CPPUNIT_ASSERT(calculargraph.getCurrentState() == 1);

	// 开始计时器
	calculargraph.stop();
	escape1 = calculargraph.getRemainTime();
	Sleep(1002);	// 这里的时间被略去了
	CPPUNIT_ASSERT(0 != escape1);
	CPPUNIT_ASSERT(0 != escape2);
	escape2 = calculargraph.getRemainTime();
	CPPUNIT_ASSERT(escape1 == escape2);

	// 重新开始
	calculargraph.restart();

	CPPUNIT_ASSERT(calculargraph.getCurrentState() == 1);
	Sleep(2900);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);
	Sleep(1200);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == true);
	CPPUNIT_ASSERT(calculargraph.getCurrentState() == 2);
}

// 测试停止计时器
void CalculargraphTest::testCalarStopTimer() {
	Calculagraph calculargraph;
	calculargraph.setTimespan(2);
	calculargraph.initialize();
	
	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);
	CPPUNIT_ASSERT(calculargraph.isStopped() == false);
	Sleep(1500);
	calculargraph.stop();
	int escape1 = calculargraph.getTimeEscape();
	Sleep(1050);
	int escape2 = calculargraph.getTimeEscape();
	CPPUNIT_ASSERT(escape1 == escape2);
	calculargraph.restart();
	Sleep(2050);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == true);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);
	Sleep(2200);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == true);
}

void CalculargraphTest::TestCulargraph() {
	Calculagraph calculargraph;
	calculargraph.setTimespan(1);
	calculargraph.initialize();
	int x = calculargraph.getRemainTimeMS();
	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);
	Sleep(1050);
	x = calculargraph.getRemainTimeMS();
	CPPUNIT_ASSERT(calculargraph.trySwitch() == true);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);
	Sleep(1050);
	x = calculargraph.getRemainTimeMS();
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

	Sleep(1200);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == true);
	CPPUNIT_ASSERT(calculargraph.getCurrentState() == 0);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);

	Sleep(2200);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == true);
	CPPUNIT_ASSERT(calculargraph.getCurrentState() == 1);
	CPPUNIT_ASSERT(calculargraph.trySwitch() == false);
}