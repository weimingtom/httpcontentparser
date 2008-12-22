#ifndef _UTILITY_SYNC_UTILITY_H__
#define _UTILITY_SYNC_UTILITY_H__

namespace yanglei_utility {
class CAutoCreateCS {
public:
	CAutoCreateCS();
	~CAutoCreateCS();

	void lock();
	void unlock();
private:
	bool locked_;
	::CRITICAL_SECTION cs_;
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
			sync_object_->lock();
		}
	}

	void unlock() {
		if(locked_ == true) {
			sync_object_->unlock();
			locked_ = false;
		}
	}

private:
	T *sync_object_;
	bool locked_;
};
};
#endif  // _UTILITY_SYNC_UTILITY_H__