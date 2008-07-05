#pragma once
#include "syncobject.h"
#include <string>

namespace SyncObjects {

class CriticalSection : public SyncObject
{
public:
	~CriticalSection(void);

	virtual int Lock();
	virtual int Unlock();
private:
	CriticalSection(const std::string &name);
	// CriticalSection(void);
	friend class SyncObject;

	::CRITICAL_SECTION cs_;
};

};
