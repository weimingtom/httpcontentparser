#include "precomp.h"
#include ".\loglistener.h"
#include ".\logger.h"
#include ".\logmsgdispatcher.h"
#include <vector>
#include <map>
#include <string>
#include <assert.h>

namespace LogSystem {

const std::string ListenerContainer::SYNC_OBJECT_NAME = "LogSystem::ListenerContainer";

LogListener::LogListener(const std::string &name) : name_(name) {
	// 没创建一个LogLIstener,都会被自动加入进来
	bool result = ListenerContainer::getInstance()->AddListener(name, this);
	// 如果出现同名的LogListener给出提示
	assert(result == true);

	bNeedAutoRelease_ = true;
}

LogListener::~LogListener() {
	if (bNeedAutoRelease_ == true)
		ListenerContainer::getInstance()->RemoveListener(name_);
}


//========================================
// class 
ListenerContainer * ListenerContainer::getInstance() {
	using namespace SyncObjects;
	SingleLock<SyncObject> locker(SyncObject::Create(SyncObject::CRITICAL_SECTION, 
		ListenerContainer::SYNC_OBJECT_NAME));

	static ListenerContainer container;
	return &container;
}

ListenerContainer::ListenerContainer() {
}

ListenerContainer::~ListenerContainer() {
	using namespace SyncObjects;
	//SingleLock<SyncObject> locker(SyncObject::Create(SyncObject::CRITICAL_SECTION, 
	//	ListenerContainer::SYNC_OBJECT_NAME));
	
	//LISTENER_MAP::iterator iter = listeners_.begin();
	//for (; iter != listeners_.end(); ++iter) {
	//	if(iter->second != NULL) 
	//		delete iter->second;
	//} 
	//listeners_.clear();
	//
	//locker.unlock();
	SyncObject::Destroy(ListenerContainer::SYNC_OBJECT_NAME);
}

LogListener * ListenerContainer::getListener(const std::string & listener_name) {
	using namespace SyncObjects;
	SingleLock<SyncObject> locker(SyncObject::Create(SyncObject::CRITICAL_SECTION, 
		ListenerContainer::SYNC_OBJECT_NAME));

	LISTENER_MAP::iterator iter = listeners_.find(listener_name);
	if (iter == listeners_.end()) {
		return NULL;
	} else {
		return iter->second;
	}
}

bool ListenerContainer::AddListener(const std::string & listener_name, LogListener *listener) {
	using namespace SyncObjects;
	SingleLock<SyncObject> locker(SyncObject::Create(SyncObject::CRITICAL_SECTION, 
		ListenerContainer::SYNC_OBJECT_NAME));

	LISTENER_MAP::iterator iter = listeners_.find(listener_name);
	if (iter != listeners_.end()) {
		return false;
	} else {
		listeners_.insert(make_pair(listener_name, listener));
		return true;
	}
}

void ListenerContainer::RemoveListener(const std::string &listener_name) {
	using namespace SyncObjects;
	SingleLock<SyncObject> locker(SyncObject::Create(SyncObject::CRITICAL_SECTION, 
		ListenerContainer::SYNC_OBJECT_NAME));

	LISTENER_MAP::iterator iter = listeners_.find(listener_name);
	if (iter != listeners_.end())
		listeners_.erase(iter);	
}

};
