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
	::CRITICAL_SECTION cs_;
};

template <class T>
class SingleLock {
public:
	SingleLock(T * sync_object, bool autolock = true) {
		sync_object_ = sync_object;
		if (autolock) {
			lock();
		}
	}
	~SingleLock() {
		unlock();
	}

	void lock() {
		sync_object_->lock();
	}

	void unlock() {
		sync_object_->unlock();
	}

private:
	T *sync_object_;
};
};
#endif  // _UTILITY_SYNC_UTILITY_H__