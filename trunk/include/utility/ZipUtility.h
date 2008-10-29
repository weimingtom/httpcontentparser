#ifndef _UTILITY_ZIPUTILITY_H__
#define _UTILITY_ZIPUTILITY_H__

#include <zlib/zconf.h>
#include <zlib/zlib.h>

// class ZipUtility
// 此类负责在对堆栈上解压缩Zip格式
// 首先它拥有一部分堆栈缓冲区，如果栈缓冲区不能满足使用
// 它才会从堆上分配空间
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

	// 缓冲区
	int get_buffer_size() const { return buffer_size_;}
	int get_inflate_size() const { return have_;}
	int get_data_size() const { return have_;}
	Bytef * get_buffer() { return buffer_pointer_;}
	
private:
	Bytef * buffer_pointer_;

	// buffer_pointer_会首先使用STACK上的缓冲
	// 如果不够用，才会在堆上分配内容
	Bytef stack_buffer_[STACK_BUFFER_SIZE];
	Bytef *heap_buffer_;
	int buffer_size_;
	int have_;

private:
	// 重新分配缓冲区
	int realloc_buffer() {
		const int new_buffer_size = get_buffer_size() * 2;
		Bytef * new_buffer = new Bytef[new_buffer_size];
		memcpy(new_buffer, get_buffer(), get_buffer_size());

		// 释放缓存去(如果不是栈缓冲区)
		if (get_buffer_size() > STACK_BUFFER_SIZE) {
			delete[] get_buffer();
		}

		// 充值指针
		buffer_pointer_ = new_buffer;
		buffer_size_ = new_buffer_size;

		return get_buffer_size();
	}
};

// 压缩
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
		
		// 如果缓冲区用尽，就需要重新分配缓冲区
		if (get_buffer_size() == have_) {
			realloc_buffer();
		}

	} while (strm.avail_out == 0);

    /* clean up and return */
    (void)deflateEnd(&strm);
    return Z_OK;

}

// 获取解压缩后的大小
template <int STACK_BUFFER_SIZE>
int ZipUtility<STACK_BUFFER_SIZE>::infloate_size(Bytef * src, const int size) {
	have_ = 0; // 初试大小为0
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

	// 初始化
	strm.avail_in = size;
	strm.next_in = src;

	
	do {
		strm.avail_out = get_buffer_size() - get_data_size();
		strm.next_out = get_buffer() + get_data_size();

		// 增加大小
		have_ += STACK_BUFFER_SIZE - strm.avail_out;
	} while (strm.avail_out == 0);

	// 销毁
	(void)inflateEnd(&strm);

	*infloat = strm.total_out;
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

// 解压缩
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

	// 开始解压缩
	strm.avail_in = size;
	strm.next_in = src;

	
	/* run inflate() on input until output buffer not full */
	do {
		strm.avail_out = get_buffer_size() - get_data_size();
		strm.next_out = get_buffer() + get_data_size();

		// 解压缩
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

		// 解压缩所处理的数据大小
		have_ += get_buffer_size() - get_data_size() - strm.avail_out;

		// 如果缓冲区用尽，就需要重新分配缓冲区
		if (get_buffer_size() == have_) {
			realloc_buffer();
		}
	} while (strm.avail_out == 0);

    /* clean up and return */
    (void)inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}


#endif  // _UTILITY_ZIPUTILITY_H__
