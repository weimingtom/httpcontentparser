#include "StdAfx.h"
#include ".\logtest.h"
#include "syncobject\syncobject.h"
#include <logsystem\logcatalog.h>
#include <logsystem\loglayout.h> 
#include <logsystem\loglistener.h>
#include <logsystem\logger.h>
#include <string>
#include <map>
 
using namespace LogSystem;
using namespace CPPUNIT_NS;

class MyListener : public LogListener {
public:
	MyListener(const std::string &name) : LogListener(name){}
	~MyListener() {}
	virtual void UpdateMessage(const char *msg, const int len) {
		msg_ = msg;
	}

	void resetMsg() { msg_ = "";}
	const std::string &getMessage() { return msg_;}
private:
	std::string msg_;
};

void LogTest::LogCatalogTest() {
	std::string name1 = "hello1", name2 = "hello2";
	Logger *log1 = LogSystem::LogCatalog::getInstance()->createLogger(name1);
	Logger *log2 = LogSystem::LogCatalog::getInstance()->createLogger(name1);
	CPPUNIT_ASSERT(log1 == log2);
}

void LogTest::NoneLayoutTest() {
	LogLayout *layout = LogLayout::Create(LogLayout::LAYOUT_NONE);
	char str[] = "hello world";
	std::string strresult = str;
	CPPUNIT_ASSERT(layout->getFmtMsg(str) == strresult);
}

void LogTest::DeleteListenerTest() {
	const std::string listenername1 = "listener1";
	const std::string loggername = "logger1";
	const std::string log_message = "log_message1";
	LogLayout *layout = LogLayout::Create(LogLayout::LAYOUT_NONE);
	MyListener *listener1 = new MyListener(listenername1);

	Logger *log1 = LogSystem::LogCatalog::getInstance()->createLogger(loggername);
	log1->AddListener(listener1);
	log1->write(log_message.c_str(), log_message.length());
	CPPUNIT_ASSERT(listener1->getMessage() == log_message);

	delete listener1;
	listener1 = NULL;
	log1->write(log_message.c_str(), log_message.length());
}

void LogTest::RegisterLogTest() {
	const std::string loggername = "logger1";
	const std::string listenername1 = "listener1", listenername2 = "listener2";
	const std::string log_message = "log_message1";

	// 创建LogLayout, Listener和log, 并用log发送消息，查看是否受到
	LogLayout *layout = LogLayout::Create(LogLayout::LAYOUT_NONE);
	MyListener listener1(listenername1);
	Logger *log1 = LogSystem::LogCatalog::getInstance()->createLogger(loggername);
	log1->AddListener(&listener1);
	log1->write(log_message.c_str(), log_message.length());
	CPPUNIT_ASSERT(listener1.getMessage() == log_message);

	// 创建第二个Listener
	const std::string message2 = "logmesssage2";
	MyListener listener2(listenername2);
	log1->AddListener(&listener2);
	log1->write(message2.c_str(), message2.length());  // 再次发送消息
	CPPUNIT_ASSERT(listener1.getMessage() == message2);
	CPPUNIT_ASSERT(listener2.getMessage() == message2);

	// 注销listener1
	const std::string message3 = "message3";
	const std::string none_message = "";
	listener1.resetMsg();
	CPPUNIT_ASSERT(none_message ==  listener1.getMessage());
	log1->RemoveListener(&listener1);
	log1->write(message3.c_str(), message3.length());
	CPPUNIT_ASSERT(none_message ==  listener1.getMessage()); //listener1 应该收不到消息
	CPPUNIT_ASSERT(message3		==  listener2.getMessage()); 

	// 再注销一个
	listener1.resetMsg();
	listener2.resetMsg();
	CPPUNIT_ASSERT(none_message ==  listener1.getMessage());
	CPPUNIT_ASSERT(none_message ==  listener2.getMessage());
	log1->RemoveListener(&listener2);
	log1->write(message3.c_str(), message3.length());
	CPPUNIT_ASSERT(none_message ==  listener1.getMessage());
	CPPUNIT_ASSERT(none_message ==  listener2.getMessage());
}

void LogTest::setUp() {
}
void LogTest::tearDown() {
	LogSystem::LogCatalog::getInstance()->DestroyAll();
}
