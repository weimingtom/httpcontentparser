#ifndef _UTILITY_FILEMAPPING_H__
#define _UTILITY_FILEMAPPING_H__

#include <string>
#include <windows.h>

// �����ṩ��FileMapping�Ļ���֧�֣����ṩ���߳�ͬ����֧�֡�
class CFileMapping {
public:
	CFileMapping(const std::string &filemapping_name,
		const std::string &mutex_name, const unsigned int BUFSIZE = 4 * 1024);
	~CFileMapping(void);

	void * lock();
	void * unlock();
private:
	void * getFileMappingHandle(); 
	SyncObjects::SyncObject * getSyncObject();
	CFileMapping(void);

	// ͬ������
	SyncObjects::SyncObject * syncobject_;
	void *  hFileMapping_;

	std::string filemapping_name_;
	unsigned int bufsize_;
	void * map_;
public:
	unsigned int getBufsize(void);
};

#endif  // _UTILITY_FILEMAPPING_H__