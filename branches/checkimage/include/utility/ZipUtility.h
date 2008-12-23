#ifndef _UTILITY_ZIPUTILITY_H__
#define _UTILITY_ZIPUTILITY_H__

#include <zlib/zconf.h>
#include <zlib/zlib.h>

// class ZipUtility
// ���ฺ���ڶԶ�ջ�Ͻ�ѹ��Zip��ʽ
// ������ӵ��һ���ֶ�ջ�����������ջ��������������ʹ��
// ���Ż�Ӷ��Ϸ���ռ�
template <int STACK_BUFFER_SIZE = 1024>
class ZipUtility {
public:
	ZipUtility(void) {
		heap_buffer_ = NULL;
		have_ = 0;
		buffer_size_ = STACK_BUFFER_SIZE;

		buffer_pointer_ = stack_buffer_;
	}
	~ZipUtility(void) {
		if (NULL != heap_buffer_) {
			delete heap_buffer_;
			heap_buffer_ = NULL;
		}
	}

public:
	int infloate_size(Bytef *src, const int size);
	int uncompress(Bytef * src, const int size);
	int compress(Bytef *src, const int size, const int level = Z_DEFAULT_COMPRESSION);

	// ������
	int get_buffer_size() const { return buffer_size_;}
	int get_inflate_size() const { return have_;}
	int get_data_size() const { return have_;}
	Bytef * get_buffer() { return buffer_pointer_;}
	
private:
	Bytef * buffer_pointer_;

	// buffer_pointer_������ʹ��STACK�ϵĻ���
	// ��������ã��Ż��ڶ��Ϸ�������
	Bytef stack_buffer_[STACK_BUFFER_SIZE];
	Bytef *heap_buffer_;
	int buffer_size_;
	int have_;

private:
	// ���·��仺����
	int realloc_buffer() {
		const int new_buffer_size = get_buffer_size() * 2;
		Bytef * new_buffer = new Bytef[new_buffer_size];
		memcpy(new_buffer, get_buffer(), get_buffer_size());

		// �ͷŻ���ȥ(�������ջ������)
		if (get_buffer_size() > STACK_BUFFER_SIZE) {
			delete[] get_buffer();
		}

		// ��ֵָ��
		buffer_pointer_ = new_buffer;
		buffer_size_ = new_buffer_size;

		return get_buffer_size();
	}
};

// ѹ��
template <int STACK_BUFFER_SIZE>
int ZipUtility<STACK_BUFFER_SIZE>::compress(Bytef *src, const int size, const int level) {
	int ret, flush = Z_FINISH;
	z_stream strm;

	/* allocate deflate state */
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	ret = deflateInit(&strm, level);
	if (ret != Z_OK)
		return ret;

	strm.avail_in = size;
	strm.next_in = src;

	/* run deflate() on input until output buffer not full, finish
	compression if all of source has been read in */
	have_ = 0;
	do {
		strm.avail_out = get_buffer_size() - get_data_size();
		strm.next_out = get_buffer() + get_data_size();
		ret = deflate(&strm, flush);    /* no bad return value */
		assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
		have_ += get_buffer_size() - get_data_size() - strm.avail_out;
		
		// ����������þ�������Ҫ���·��仺����
		if (get_buffer_size() == have_) {
			realloc_buffer();
		}

	} while (strm.avail_out == 0);

    /* clean up and return */
    (void)deflateEnd(&strm);
    return Z_OK;

}

// ��ȡ��ѹ����Ĵ�С
template <int STACK_BUFFER_SIZE>
int ZipUtility<STACK_BUFFER_SIZE>::infloate_size(Bytef * src, const int size) {
	have_ = 0; // ���Դ�СΪ0
	int ret;
    z_stream strm;

	if (size == 0)
		return Z_OK;

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK)
        return ret;

	// ��ʼ��
	strm.avail_in = size;
	strm.next_in = src;

	
	do {
		strm.avail_out = get_buffer_size() - get_data_size();
		strm.next_out = get_buffer() + get_data_size();

		// ���Ӵ�С
		have_ += STACK_BUFFER_SIZE - strm.avail_out;
	} while (strm.avail_out == 0);

	// ����
	(void)inflateEnd(&strm);

	*infloat = strm.total_out;
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

// ��ѹ��
template <int STACK_BUFFER_SIZE>
int ZipUtility<STACK_BUFFER_SIZE>::uncompress(Bytef * src, const int size) {
	have_ = 0;
	int ret;
    z_stream strm;

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;

	if (size == 0) 
		return Z_OK;


    ret = inflateInit(&strm);
    if (ret != Z_OK)
        return ret;

	// ��ʼ��ѹ��
	strm.avail_in = size;
	strm.next_in = src;

	
	/* run inflate() on input until output buffer not full */
	do {
		strm.avail_out = get_buffer_size() - get_data_size();
		strm.next_out = get_buffer() + get_data_size();

		// ��ѹ��
		ret = inflate(&strm, Z_NO_FLUSH);

		assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
		switch (ret) {
			case Z_NEED_DICT:
				ret = Z_DATA_ERROR;     /* and fall through */
			case Z_DATA_ERROR:
			case Z_MEM_ERROR:
				(void)inflateEnd(&strm);
				return ret;
		}

		// ��ѹ������������ݴ�С
		have_ += get_buffer_size() - get_data_size() - strm.avail_out;

		// ����������þ�������Ҫ���·��仺����
		if (get_buffer_size() == have_) {
			realloc_buffer();
		}
	} while (strm.avail_out == 0);

    /* clean up and return */
    (void)inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}


#endif  // _UTILITY_ZIPUTILITY_H__
