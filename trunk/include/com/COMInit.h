#ifndef _INCLUDE_COM_INITIALIZE_H__
#define _INCLUDE_COM_INITIALIZE_H__

#include <objbase.h>

class AutoInitInScale {
public:
	AutoInitInScale() {CoInitialize(NULL);}
	~AutoInitInScale() {CoUninitialize();}
};

#endif  // _INCLUDE_COM_INITIALIZE_H__