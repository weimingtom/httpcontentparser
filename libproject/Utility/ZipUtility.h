#ifndef _UTILITY_ZIPUTILITY_H__
#define _UTILITY_ZIPUTILITY_H__

#include <zconf.h>
#include <zlib.h>

// class ZipUtility
// ���ฺ���ڶԶ�ջ�Ͻ�ѹ��Zip��ʽ
// ������ӵ��һ���ֶ�ջ�����������ջ��������������ʹ��
// ���Ż�Ӷ��Ϸ���ռ�
template <int STACK_BUFFER_SIZE = 1024>
class ZipUtility {
public:
	ZipUtility(void) {
		heap_buffer_ = NULL;
	}
	~ZipUtility(void) {
		if (NULL != heap_buffer_) {
			delete heap_buffer_;
			heap_buffer_ = NULL;
		}
	}

	const char * unzip() (const char * src, const int size);
private:
	char * buffer_pointer_;

	char stack_buffer_[STACK_BUFFER_SIZE];
	char *heap_buffer_;
};

template <int STACK_BUFFER_SIZE>
const char * ZipUtility<STACK_BUFFER_SIZE>unzip() (const char * src, const int size) {
	return buffer_pointer_;
}


#endif  // _UTILITY_ZIPUTILITY_H__
