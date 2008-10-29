#ifndef _UTILITY_BUFFERONSTACKHEAP_H__
#define _UTILITY_BUFFERONSTACKHEAP_H__

template <int STACK_LIMIT = 1024>
class BufferOnStackHeap {
public:
	BufferOnStackHeap(const int size) {
		if (size > STACK_LIMIT) {
			heap_buffer_ = new char[size];
			buffer_size_ = size;
			effective_buffer_  = heap_buffer_;
		}
	}
	BufferOnStackHeap() {
		heap_buffer_ = NULL;
		effective_buffer_  = stack_buffer_;
		buffer_size_ = STACK_LIMIT;
	}
	~BufferOnStackHeap() {
		if (NULL != heap_buffer_) {
			delete heap_buffer_;
		}
	}

	// ���·����ڴ�
	int realloc() {
		// ����������
		heap_buffer_ = new char[get_buffer_size() * 2];
		set_buffer_size(get_buffer_size() * 2);
		// ��������
		memcpy(heap_buffer_, effective_buffer_, STACK_LIMIT);

		// ɾ��֮ǰ�Ļ�����
		if (effective_buffer_ != stack_buffer_) {
			delete effective_buffer_;
		}

		// �޸�ʵ�ʻ�����
		effective_buffer_ = heap_buffer_;
	}
	int get_buffer_size() { return buffer_size_;}
	char * get_buffer() {return effective_buffer_;}

private:
	// ָ��ʵ�ʵĻ���������Stack����Heap��
	char * effective_buffer_;
	
	// ���滺�����Ĵ�С 
	int buffer_size_;

	// stack buffer
	char stack_buffer_[STACK_LIMIT];

	// ��սָ��
	char *heap_buffer_;
};

#endif  // _UTILITY_BUFFERONSTACKHEAP_H__