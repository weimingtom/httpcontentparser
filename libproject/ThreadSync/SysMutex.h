#ifndef _THREAD_SYNC_SYSMUTEX_H__
#define _THREAD_SYNC_SYSMUTEX_H__


#include "syncobject.h"
#include <string>

namespace SyncObjects {

// �����ṩ��ϵͳȫ�ֵ�ͬ��֧��
// �û�ָ��������Ӧ����һ��UUID,���߿��Բ����ظ����ַ���
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