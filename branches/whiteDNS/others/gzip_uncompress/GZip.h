#ifndef _ZIP_UTILITY_GZIP_H__
#define _ZIP_UTILITY_GZIP_H__

#include <zlib/zconf.h>
#include <zlib/zlib.h>
#include <assert.h>
#include <utility/BufferOnStackHeap.h>

class GZip {
public:
	GZip(void);
	~GZip(void);

	void uncompress(const char * filename, const char * outputfile);
private:
};

#endif  // _ZIP_UTILITY_GZIP_H__