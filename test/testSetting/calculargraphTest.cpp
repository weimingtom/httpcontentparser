#include "StdAfx.h"
#include ".\calculargraphtest.h"
#include <setting\calculagraph.h>
#include <iostream>
#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;
using namespace std;



void TestForceswitch() {
	const int type = 2;
	MultiCalculagraph<type> calculargraph;
	calculargraph.setTimespan(2, 0);
	calculargraph.setTimespan(2, 1);
	calculargraph.initialize(0);

	calculargraph.setRemainTime(-1);
	BOOST_CHECK(true == calculargraph.trySwitch());
	BOOST_CHECK(1 == calculargraph.getCurrentState());
	BOOST_CHECK(1000 <= calculargraph.getRemainTimeMS());
	calculargraph.forceSwitch(0);
	BOOST_CHECK(0 == calculargraph.getCurrentState());
	BOOST_CHECK(1000 <= calculargraph.getRemainTimeMS());

}

void testMulitSetTimeLeft() {
	const int type = 3;
	MultiCalculagraph<type> calculargraph;
	calculargraph.setTimespan(1, 0);
	calculargraph.setTimespan(15, 1);
	calculargraph.setTimespan(1, 2);
	calculargraph.initialize(0);

	BOOST_CHECK(calculargraph.getCurrentState() == 0);
	BOOST_CHECK(calculargraph.trySwitch() == false);
	Sleep(1200);
	int x = calculargraph.getRemainTimeMS();
	BOOST_CHECK(calculargraph.trySwitch() == true);
	BOOST_CHECK(calculargraph.getCurrentState() == 1);
	BOOST_CHECK(calculargraph.trySwitch() == false);

	calculargraph.setRemainTime(1);
	Sleep(1200);
	BOOST_CHECK(calculargraph.trySwitch() == true);
	BOOST_CHECK(calculargraph.getCurrentState() == 2);
	BOOST_CHECK(calculargraph.trySwitch() == false);
}

void TestSetASmallerTime() {
	Calculagraph calculargraph;
	calculargraph.setTimespan(10);
	calculargraph.initialize();

	calculargraph.setTimespan(1);
	BOOST_CHECK(calculargraph.getRemainTime() > 0);
}
void TestSetTimeEscape() {
	Calculagraph calculargraph;
	calculargraph.setTimespan(5);
	calculargraph.initialize();

	BOOST_CHECK(calculargraph.trySwitch() == false);
	calculargraph.setTimeEscape(6);
	BOOST_CHECK(calculargraph.trySwitch() == true);
}

// 多个状态的计时器
void testMultiStopTimer() {
	const int type = 3;
	MultiCalculagraph<type> calculargraph;
	calculargraph.setTimespan(3, 0);
	calculargraph.setTimespan(4, 1);
	calculargraph.setTimespan(1, 2);
	calculargraph.initialize(0);

	
	BOOST_CHECK(calculargraph.getCurrentState() == 0);
	BOOST_CHECK(calculargraph.trySwitch() == false);

	// 停止
	Sleep(1300);
	int x3= calculargraph.getRemainTime();
	calculargraph.stop();
	int escape1 = calculargraph.getRemainTimeMS();
	Sleep(600);
	int escape2 = calculargraph.getRemainTimeMS();
	BOOST_CHECK(0 != escape1);
	BOOST_CHECK(0 != escape2);
	BOOST_CHECK(escape1 == escape2);

	// 重新开始
	calculargraph.restart();

	BOOST_CHECK(calculargraph.getCurrentState() == 0);
	int x1 = calculargraph.getRemainTimeMS();
	Sleep(1800);
	int x2 = calculargraph.getRemainTimeMS();
	BOOST_CHECK(calculargraph.trySwitch() == true);
	BOOST_CHECK(calculargraph.getCurrentState() == 1);

	// 开始计时器
	calculargraph.stop();
	escape1 = calculargraph.getRemainTime();
	Sleep(1002);	// 这里的时间被略去了
	BOOST_CHECK(0 != escape1);
	BOOST_CHECK(0 != escape2);
	escape2 = calculargraph.getRemainTime();
	BOOST_CHECK(escape1 == escape2);

	// 重新开始
	calculargraph.restart();

	BOOST_CHECK(calculargraph.getCurrentState() == 1);
	Sleep(2900);
	BOOST_CHECK(calculargraph.trySwitch() == false);
	Sleep(1200);
	BOOST_CHECK(calculargraph.trySwitch() == true);
	BOOST_CHECK(calculargraph.getCurrentState() == 2);
}

// 测试停止计时器
void testCalarStopTimer() {
	Calculagraph calculargraph;
	calculargraph.setTimespan(2);
	calculargraph.initialize();
	
	BOOST_CHECK(calculargraph.trySwitch() == false);
	BOOST_CHECK(calculargraph.isStopped() == false);
	Sleep(1500);
	calculargraph.stop();
	int escape1 = calculargraph.getTimeEscape();
	Sleep(1050);
	int escape2 = calculargraph.getTimeEscape();
	BOOST_CHECK(escape1 == escape2);
	calculargraph.restart();
	Sleep(2050);
	BOOST_CHECK(calculargraph.trySwitch() == true);
	BOOST_CHECK(calculargraph.trySwitch() == false);
	Sleep(2200);
	BOOST_CHECK(calculargraph.trySwitch() == true);
}

void TestCulargraph() {
	Calculagraph calculargraph;
	calculargraph.setTimespan(1);
	calculargraph.initialize();
	int x = calculargraph.getRemainTimeMS();
	BOOST_CHECK(calculargraph.trySwitch() == false);
	Sleep(1050);
	x = calculargraph.getRemainTimeMS();
	BOOST_CHECK(calculargraph.trySwitch() == true);
	BOOST_CHECK(calculargraph.trySwitch() == false);
	Sleep(1050);
	x = calculargraph.getRemainTimeMS();
	BOOST_CHECK(calculargraph.trySwitch() == true);
	BOOST_CHECK(calculargraph.trySwitch() == false);
}

void TestMultiCalculargraph() {
	const int type = 3;
	MultiCalculagraph<type> calculargraph;
	calculargraph.setTimespan(1, 0);
	calculargraph.setTimespan(2, 1);
	calculargraph.setTimespan(1, 2);
	calculargraph.initialize(0);

	BOOST_CHECK(calculargraph.getCurrentState() == 0);
	BOOST_CHECK(calculargraph.trySwitch() == false);
	Sleep(1200);
	BOOST_CHECK(calculargraph.trySwitch() == true);
	BOOST_CHECK(calculargraph.getCurrentState() == 1);
	BOOST_CHECK(calculargraph.trySwitch() == false);

	Sleep(2200);
	BOOST_CHECK(calculargraph.trySwitch() == true);
	BOOST_CHECK(calculargraph.getCurrentState() == 2);
	BOOST_CHECK(calculargraph.trySwitch() == false);

	Sleep(1200);
	BOOST_CHECK(calculargraph.trySwitch() == true);
	BOOST_CHECK(calculargraph.getCurrentState() == 0);
	BOOST_CHECK(calculargraph.trySwitch() == false);

	Sleep(2200);
	BOOST_CHECK(calculargraph.trySwitch() == true);
	BOOST_CHECK(calculargraph.getCurrentState() == 1);
	BOOST_CHECK(calculargraph.trySwitch() == false);
}