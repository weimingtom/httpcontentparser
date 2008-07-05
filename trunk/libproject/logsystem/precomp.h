#ifndef _LOG_SYSTEM_PRECOMP_H__
#define _LOG_SYSTEM_PRECOMP_H__

#include <tchar.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>

#include "syncobject\SyncObject.h"

#ifdef _DEBUG
#	pragma comment(lib, "ThreadSyncd.lib")
#else 
#	pragma comment(lib, "ThreadSync.lib")
#endif

#endif  // _LOG_SYSTEM_PRECOMP_H__