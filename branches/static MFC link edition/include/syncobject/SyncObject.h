#ifndef _THREAD_SYNC_SYNCOBJECT_H__
#define _THREAD_SYNC_SYNCOBJECT_H__

#include <string>
#include <map>

namespace SyncObjects {

// 类SyncObject
// 所有的同步对象都集成自它
// 所有的同步对象都有它创建
class SyncObject {
public:
	virtual int Lock() = 0;
	virtual int Unlock() = 0;
	
	const std::string &getType() {
		return type_;
	}

	const std::string &getName() {
		return name_;
	}

	static SyncObject * Create(const std::string &type,
		const std::string &name);
	static void Destroy(const std::string &name);
	static void DestoryAll();

	static const std::string CRITICAL_SECTION;
	static const std::string MULTEX;
	static SyncObject * getSyncObject(const std::string &name);

	~SyncObject();
protected: 
	// 同步对象的类型
	std::string type_;
	// 同步对象的名称
	std::string name_;

	SyncObject(const std::string &name);
private:
	static bool addSyncObject(const std::string &name, SyncObject * object);

	typedef std::map<std::string, SyncObject*> SYNC_OBJECTS_MAP;
	static SYNC_OBJECTS_MAP syncobject_map_;
};

template <class T>
class SingleLock {
public:
	SingleLock(T * sync_object, bool autolock = true) {
		sync_object_ = sync_object;
		locked_ = false;
		if (autolock) {
			lock();
		}
	}
	~SingleLock() {
		unlock();
	}

	void lock() {
		if ( locked_ == false) {
			locked_ = true;
			sync_object_->Lock();
		}
	}

	void unlock() {
		if(locked_ == true) {
			sync_object_->Unlock();
			locked_ = false;
		}
	}

private:
	T *sync_object_;
	bool locked_;
};

}; // namespace 
#endif