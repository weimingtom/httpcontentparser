#ifndef _THREAD_SYNC_SYSMUTEX_H__
#define _THREAD_SYNC_SYSMUTEX_H__


#include "syncobject.h"
#include <string>

namespace SyncObjects {

// 此类提供了系统全局的同步支持
// 用户指定的名称应该是一个UUID,或者可以不会重复的字符串
class CSysMutex : public SyncObject {
public:
	~CSysMutex(void);

	virtual int Lock();
	virtual int Unlock();
private:
	friend class SyncObject;
	CSysMutex(const std::string &name);
	HANDLE getMutex();
	HANDLE hMutex_;
};

};

#endif