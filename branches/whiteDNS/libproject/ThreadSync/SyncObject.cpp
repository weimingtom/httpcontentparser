#include "stdafx.h"
#include "syncobject.h"
#include ".\criticalsection.h"
#include "sysmutex.h"
#include <map>
#include <assert.h>

namespace SyncObjects {
 
namespace {
// 为了避免下面stl代买出现同步问题
class AssitSyncObject {
public:
	AssitSyncObject() {InitializeCriticalSection(&cs_);}
	~AssitSyncObject() {DeleteCriticalSection(&cs_);}

	void Lock() {EnterCriticalSection(&cs_);}
	void Unlock() {LeaveCriticalSection(&cs_);}
private:
	CRITICAL_SECTION cs_;
};
AssitSyncObject s_minsyncObject;
};

// 同步对象的名称
const std::string SyncObject::CRITICAL_SECTION = "SyncObject_CRITICAL_SECTION";
SyncObject::SYNC_OBJECTS_MAP SyncObject::syncobject_map_;
const std::string SyncObject::MULTEX = "SyncObject_Mutex";

SyncObject * SyncObject::getSyncObject(const std::string &name) {
	SingleLock<AssitSyncObject> lock(&s_minsyncObject);

	SYNC_OBJECTS_MAP::iterator iter = syncobject_map_.find(name);
	if (iter == syncobject_map_.end()) {
		return NULL;
	} else {
		return iter->second;
	}
}

bool SyncObject::addSyncObject(const std::string &name, SyncObject * object) {
	SingleLock<AssitSyncObject> lock(&s_minsyncObject);

	assert (getSyncObject(name) == NULL);
	syncobject_map_.insert(std::make_pair(name, object));
	return true;
}

void SyncObject::DestoryAll() {
	SingleLock<AssitSyncObject> lock(&s_minsyncObject);

	SYNC_OBJECTS_MAP::iterator iter = syncobject_map_.begin();
	for (; iter != syncobject_map_.end(); ++iter) {
		delete iter->second;
		iter->second = NULL;
	}
	syncobject_map_.clear(); 
}

void SyncObject::Destroy(const std::string &name) {
	SingleLock<AssitSyncObject> lock(&s_minsyncObject);

	SYNC_OBJECTS_MAP::iterator iter = syncobject_map_.find(name);
	if (iter != syncobject_map_.end()) {
		delete iter->second;
		syncobject_map_.erase(iter);
	}
}

SyncObject * SyncObject::Create(const std::string &type, const std::string &name) {
	SingleLock<AssitSyncObject> lock(&s_minsyncObject);
	
	// 对象是否已经存在
	SyncObject * obj = getSyncObject(name);
	if (obj != NULL) {
		// 如果与预期类型不一致，返回null
		if (obj->getType() != type) {
			return NULL;
		} else {
			return obj;
		}
	} else {
		if (SyncObject::CRITICAL_SECTION == type ) {
			CriticalSection * cs = new CriticalSection(name);
			bool success = addSyncObject(name, cs);
			assert(success == true);
			return cs;
		} else if (SyncObject::MULTEX == type) {
			CSysMutex * mutex = new CSysMutex(name);
			bool success = addSyncObject(name, mutex);
			assert(success == true);
			return mutex;
		} else {
			// 目前尚不支持此类型
			return NULL;
		}
	} 
}
SyncObject::~SyncObject() {
}
SyncObject::SyncObject(const std::string &name) {
	name_ = name;
}
 
};  // namespace
