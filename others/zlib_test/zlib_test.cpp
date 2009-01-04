// zlib_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <zlib\zconf.h>
#include <zlib\zlib.h>
#include <zlib\zutil.h>
#include <iostream>
using namespace std;

#pragma comment(lib, "zlib1.lib")

#define GZIP_BUFFER_SIZE 1024

/* gzip flag byte */
#define ASCII_FLAG   0x01 /* bit 0 set: file probably ascii text */
#define HEAD_CRC     0x02 /* bit 1 set: header CRC present */
#define EXTRA_FIELD  0x04 /* bit 2 set: extra field present */
#define ORIG_NAME    0x08 /* bit 3 set: original file name present */
#define COMMENT      0x10 /* bit 4 set: file comment present */
#define RESERVED     0xE0 /* bits 5..7: reserved */

class GZipUtility {
public:
	void deflateGZip();
private:
	void check_header();
	int get_byte();
	int transparent_;
	z_stream stream_;
	int err_;
	
	Bytef out_buffer[GZIP_BUFFER_SIZE];

	/* gzip magic header */
	static int const gz_magic[2];

};

int const GZipUtility::gz_magic[2] = {0x1f, 0x8b}; 

int GZipUtility::get_byte() {
	stream_.avail_in --;
    stream_.next_in ++;
	return *(stream_.next_in-1);
}
void GZipUtility::check_header()
{
    int method; /* method byte */
    int flags;  /* flags byte */
    uInt len;
    int c;

    /* Peek ahead to check the gzip magic header */
    if (stream_.next_in[0] != gz_magic[0] ||
        stream_.next_in[1] != gz_magic[1]) {
        transparent_ = 1;
        return;
    }
    stream_.avail_in -= 2;
    stream_.next_in += 2;

    /* Check the rest of the gzip header */
    method = get_byte();
    flags = get_byte();
    if (method != Z_DEFLATED || (flags & RESERVED) != 0) {
        err_ = Z_DATA_ERROR;
        return;
    }

    /* Discard time, xflags and OS code: */
    for (len = 0; len < 6; len++) (void)get_byte();

    if ((flags & EXTRA_FIELD) != 0) { /* skip the extra field */
        len  =  (uInt)get_byte();
        len += ((uInt)get_byte())<<8;
        /* len is garbage if EOF but the loop below will quit anyway */
        while (len-- != 0 && get_byte() != EOF) ;
    }
    if ((flags & ORIG_NAME) != 0) { /* skip the original file name */
        while ((c = get_byte()) != 0 && c != EOF) ;
    }
    if ((flags & COMMENT) != 0) {   /* skip the .gz file comment */
        while ((c = get_byte()) != 0 && c != EOF) ;
    }
    if ((flags & HEAD_CRC) != 0) {  /* skip the header crc */
        for (len = 0; len < 2; len++) (void)get_byte();
    }
    err_ = err_ ? Z_DATA_ERROR : Z_OK;
}

void GZipUtility::deflateGZip() {
	// 初始化stream
	int level = Z_DEFAULT_COMPRESSION; /* compression level */
    int strategy = Z_DEFAULT_STRATEGY; /* compression strategy */

	stream_.zalloc = (alloc_func)0;
    stream_.zfree = (free_func)0;
	stream_.opaque = (voidpf)0;
	stream_.next_in  = Z_NULL;
	stream_.next_out  = Z_NULL;
	stream_.avail_in = stream_.avail_out = 0;

	err_ = deflateInit2(&stream_, level, Z_DEFLATED, -MAX_WBITS, DEF_MEM_LEVEL, strategy);

	// 设置缓冲区
	stream_.next_out  = out_buffer;
	stream_.avail_out = GZIP_BUFFER_SIZE;

	// 跳过头部
	check_header();
}

int gzread(gzFile file, voidp buf, unsigned len)
{
    gz_stream *s = (gz_stream*)file;
    Bytef *start = (Bytef*)buf; /* starting point for crc computation */
    Byte  *next_out; /* == stream.next_out but not forced far (for MSDOS) */

    if (s == NULL || s->mode != 'r') return Z_STREAM_ERROR;

    if (s->z_err == Z_DATA_ERROR || s->z_err == Z_ERRNO) return -1;
    if (s->z_err == Z_STREAM_END) return 0;  /* EOF */

    next_out = (Byte*)buf;
    s->stream.next_out = (Bytef*)buf;
    s->stream.avail_out = len;

    if (s->stream.avail_out && s->back != EOF) {
        *next_out++ = s->back;
        s->stream.next_out++;
        s->stream.avail_out--;
        s->back = EOF;
        s->out++;
        start++;
        if (s->last) {
            s->z_err = Z_STREAM_END;
            return 1;
        }
    }

    while (s->stream.avail_out != 0) {

        if (s->transparent) {
            /* Copy first the lookahead bytes: */
            uInt n = s->stream.avail_in;
            if (n > s->stream.avail_out) n = s->stream.avail_out;
            if (n > 0) {
                zmemcpy(s->stream.next_out, s->stream.next_in, n);
                next_out += n;
                s->stream.next_out = next_out;
                s->stream.next_in   += n;
                s->stream.avail_out -= n;
                s->stream.avail_in  -= n;
            }
            if (s->stream.avail_out > 0) {
                s->stream.avail_out -=
                    (uInt)fread(next_out, 1, s->stream.avail_out, s->file);
            }
            len -= s->stream.avail_out;
            s->in  += len;
            s->out += len;
            if (len == 0) s->z_eof = 1;
            return (int)len;
        }
        if (s->stream.avail_in == 0 && !s->z_eof) {

            errno = 0;
            s->stream.avail_in = (uInt)fread(s->inbuf, 1, Z_BUFSIZE, s->file);
            if (s->stream.avail_in == 0) {
                s->z_eof = 1;
                if (ferror(s->file)) {
                    s->z_err = Z_ERRNO;
                    break;
                }
            }
            s->stream.next_in = s->inbuf;
        }
        s->in += s->stream.avail_in;
        s->out += s->stream.avail_out;
        s->z_err = inflate(&(s->stream), Z_NO_FLUSH);
        s->in -= s->stream.avail_in;
        s->out -= s->stream.avail_out;

        if (s->z_err == Z_STREAM_END) {
            /* Check CRC and original size */
            s->crc = crc32(s->crc, start, (uInt)(s->stream.next_out - start));
            start = s->stream.next_out;

            if (getLong(s) != s->crc) {
                s->z_err = Z_DATA_ERROR;
            } else {
                (void)getLong(s);
                /* The uncompressed length returned by above getlong() may be
                 * different from s->out in case of concatenated .gz files.
                 * Check for such files:
                 */
                check_header(s);
                if (s->z_err == Z_OK) {
                    inflateReset(&(s->stream));
                    s->crc = crc32(0L, Z_NULL, 0);
                }
            }
        }
        if (s->z_err != Z_OK || s->z_eof) break;
    }
    s->crc = crc32(s->crc, start, (uInt)(s->stream.next_out - start));

    if (len == s->stream.avail_out &&
        (s->z_err == Z_DATA_ERROR || s->z_err == Z_ERRNO))
        return -1;
    return (int)(len - s->stream.avail_out);
}

int _tmain(int argc, _TCHAR* argv[])
{
	char dest1[10240], dest2[10240];
	const char *p = "hello world";

	int dest_len = 10240;
	compress((Bytef*)dest1, (uLongf*)&dest_len, (Bytef*)p, strlen(p));

	uncompress((Bytef*)dest2, (uLongf*)&dest_len, (Bytef*)dest1, dest_len);

	cout<<dest2<<endl;
	return 0;
}

