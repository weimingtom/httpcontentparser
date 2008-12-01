// gzip_uncompress.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <utility/BufferOnStackHeap.h>
#include <utility/ZipUtility.h>
#include <zlib/zconf.h>
#include <zlib/zlib.h>
#include <fstream>
#include <iostream>

using namespace std;

#pragma comment(lib, "zlib1.lib")

int _tmain(int argc, _TCHAR* argv[])
{	

	char buffer[1024];
	fstream f2;
	f2.open(".\\uncompress1", std::ios::binary | std::ios::out);

	gzFile  gzfile = gzopen ("compress1", "rb"	);
	int length = 0;
	while (-1 != (length = gzread (gzfile, buffer, 1024))) {
		f2.write(buffer, length);
	}
	gzclose(gzfile);

	f2.close();

	return 0;
}

