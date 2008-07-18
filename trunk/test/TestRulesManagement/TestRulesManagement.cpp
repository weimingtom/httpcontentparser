// TestRulesManagement.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <com\RulesHolder.h>
#include <com\RulesHolder_i.c>
#include <cppunit/extensions/HelperMacros.h>

using namespace CPPUNIT_NS;

class ExeRuleCheckerTest : public TestFixture {
public:
	CPPUNIT_TEST_SUITE(ExeRuleCheckerTest);
	CPPUNIT_TEST(TESTDelIP);
	CPPUNIT_TEST(TESTCheckIP);
	CPPUNIT_TEST(TESTUnCheck);
	CPPUNIT_TEST(TESTremoveDNS);
	CPPUNIT_TEST_SUITE_END();
public:
	virtual void setUp();
	virtual void tearDown();
protected:
	void TESTDelIP();
	void TESTCheckIP();
	void TESTUnCheck();
	void TESTremoveDNS();

	IRulesChecker * pRulesChecker_;
	IRulesSetting * pRulesSetting_;
};

void ExeRuleCheckerTest::TESTDelIP() {
	pRulesSetting_->addFiltederDNS(_bstr_t("www.sina.com"));
	short filtered;
	pRulesSetting_->enableIpCheck(true);
	pRulesChecker_->checkIp(inet_addr("202.205.3.130"), &filtered);
	CPPUNIT_ASSERT(filtered == true);
	pRulesSetting_->removeFilteredDNS(_bstr_t("www.sina.com"));
	pRulesChecker_->checkIp(inet_addr("10.205.3.143"), &filtered);
	CPPUNIT_ASSERT(filtered == false);
}
void ExeRuleCheckerTest::setUp() {
	try {
		HRESULT hResult;
		hResult = CoCreateInstance(CLSID_RulesChecker,
			NULL, CLSCTX_ALL, IID_IRulesChecker,(void**)&pRulesChecker_);
		hResult = CoCreateInstance(CLSID_RulesSetting,
			NULL, CLSCTX_ALL, IID_IRulesSetting,(void**)&pRulesSetting_);
	} catch (_com_error &e) {
		CPPUNIT_FAIL((char*)e.Description());
	} catch (...) {
		CPPUNIT_FAIL(" An unknown error When CreateInstance");
	} 
}
void ExeRuleCheckerTest::tearDown() {
	pRulesSetting_->Release();
	pRulesChecker_->Release();
}

void ExeRuleCheckerTest::TESTUnCheck() {
	pRulesSetting_->addFiltederDNS(_bstr_t("www.sina.com"));
	short filtered;
	pRulesSetting_->enableIpCheck(false);
	pRulesChecker_->checkIp(inet_addr("202.205.3.130"), &filtered);
	CPPUNIT_ASSERT(filtered == false);
	pRulesChecker_->checkIp(inet_addr("10.205.3.143"), &filtered);
	CPPUNIT_ASSERT(filtered == false);
}

void ExeRuleCheckerTest::TESTremoveDNS() {
	_bstr_t dns("www.sina.com");
	pRulesSetting_->addFiltederDNS(dns);
	pRulesSetting_->enableIpCheck(true);

	short filtered;
	pRulesChecker_->checkIp(inet_addr("202.205.3.130"), &filtered);
	CPPUNIT_ASSERT(filtered == true);

	pRulesSetting_->removeFilteredDNS(dns);
	pRulesChecker_->checkIp(inet_addr("202.205.3.130"), &filtered);
	CPPUNIT_ASSERT(filtered == false);

}
void ExeRuleCheckerTest::TESTCheckIP() {
	pRulesSetting_->addFiltederDNS(_bstr_t("www.sina.com"));
	pRulesSetting_->enableIpCheck(true);

	short filtered;
	pRulesChecker_->checkIp(inet_addr("202.205.3.130"), &filtered);
	CPPUNIT_ASSERT(filtered == true);
	pRulesChecker_->checkIp(inet_addr("202.205.3.142"), &filtered);
	CPPUNIT_ASSERT(filtered == true);
	pRulesChecker_->checkIp(inet_addr("202.205.3.143"), &filtered);
	CPPUNIT_ASSERT(filtered == true);
	pRulesChecker_->checkIp(inet_addr("10.205.3.143"), &filtered);
	CPPUNIT_ASSERT(filtered == false);
}


CPPUNIT_TEST_SUITE_REGISTRATION(ExeRuleCheckerTest);


int _tmain(int argc, _TCHAR* argv[]) {
	CoInitializeEx(NULL, 0x0);
	 // Create the event manager and test controller
	CPPUNIT_NS::TestResult controller;

	// Add a listener that colllects test result
	CPPUNIT_NS::TestResultCollector result;
	controller.addListener( &result );        

	// Add a listener that print dots as test run.
	CPPUNIT_NS::BriefTestProgressListener progress;
	controller.addListener( &progress );      

	// Add the top suite to the test runner
	CPPUNIT_NS::TestRunner runner;
	runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
	runner.run( controller );

	// Print test in a compiler compatible format.
	CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() ); 
	outputter.write(); 

	CoUninitialize();
	return result.wasSuccessful() ? 0 : 1;
}

