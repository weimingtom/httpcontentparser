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
	}
	~ZipUtility(void) {
		if (NULL != heap_buffer_) {
			delete heap_buffer_;
			heap_buffer_ = NULL;
		}
	}

	int infloate_size(const char *src, const int size int *infloat);
	int unzip(const char * src, const int size, int *infatesize);
private:
	char * buffer_pointer_;

	char stack_buffer_[STACK_BUFFER_SIZE];
	char *heap_buffer_;
};


template <int STACK_BUFFER_SIZE>
const char * ZipUtility<STACK_BUFFER_SIZE>::infloate_size(const char * src, const int size, int *infloat) {
	int ret;
    z_stream strm;

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK)
        return ret;

    /* decompress until deflate stream ends or end of file */
    do {
        strm.avail_in = size;
        strm.next_in = src;

        /* run inflate() on input until output buffer not full */
        do {
            strm.avail_out = STACK_BUFFER_SIZE;
            strm.next_out = stack_buffer_;
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
        } while (strm.avail_out == 0);

        /* done when inflate() says it's done */
    } while (ret != Z_STREAM_END);

    /* clean up and return */
    (void)inflateEnd(&strm);

	*infloat = strm.total_out;
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

template <int STACK_BUFFER_SIZE>
int ZipUtility<STACK_BUFFER_SIZE>::unzip(const char * src, const int size, int *infatesize) {
	int ret;
    z_stream strm;

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK)
        return ret;

    /* decompress until deflate stream ends or end of file */
    do {
        strm.avail_in = size;
        if (strm.avail_in == 0)
            break;
        strm.next_in = src;

        /* run inflate() on input until output buffer not full */
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
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
        } while (strm.avail_out == 0);

        /* done when inflate() says it's done */
    } while (ret != Z_STREAM_END);

    /* clean up and return */
    (void)inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}


#endif  // _UTILITY_ZIPUTILITY_H__
