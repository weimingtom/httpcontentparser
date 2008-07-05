#include "StdAfx.h"
#include ".\filemapping.h"
#include "exception.h"
#include "returncode.h"
#include <windows.h>

CFileMapping::CFileMapping(const std::string &filemapping_name,
		const std::string &mutex_name, const unsigned int BUFSIZE) {
	syncobject_ = NULL;
	hFileMapping_ = NULL; 

	filemapping_name_ = filemapping_name;
	bufsize_ = BUFSIZE;
}

CFileMapping::~CFileMapping(void) {
}

void * CFileMapping::getFileMappingHandle() {
	if (hFileMapping_ != NULL)
		return hFileMapping_;
	
	void* handle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL,
		PAGE_READWRITE, 0, bufsize_, filemapping_name_.c_str());

	if (handle != NULL) {
		hFileMapping_ = handle;
		return hFileMapping_;
	} else {
		hFileMapping_ = NULL;
		throw yanglei::exception("Create Filemapping failed!");
		return NULL;
	}
}

SyncObjects::SyncObject * CFileMapping::getSyncObject() {
	if (syncobject_ != NULL) {
		syncobject_ = 
			SyncObjects::SyncObject::Create(SyncObjects::SyncObject::MULTEX,
			filemapping_name_.c_str());
		return syncobject_;
	} else {
		return syncobject_;
	}
}

void * CFileMapping::lock() {
	SyncObjects::SingleLock<SyncObjects::SyncObject> locker(getSyncObject());
	
	map_  = (void*)MapViewOfFile((HANDLE)getFileMappingHandle(),
		FILE_MAP_ALL_ACCESS, 0, 0, bufsize_);

	if (NULL == map_) {
		throw yanglei::exception(GetLastError());
	}

	return map_;
}

void * CFileMapping::unlock() {
	SyncObjects::SingleLock<SyncObjects::SyncObject> locker(getSyncObject());
	if (map_ != NULL) {
		UnmapViewOfFile(map_);
	}
	return NULL;
}
unsigned int CFileMapping::getBufsize(void) {
	return bufsize_;
}
