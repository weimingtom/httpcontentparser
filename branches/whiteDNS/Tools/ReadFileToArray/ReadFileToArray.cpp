// ReadFileToArray.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;
#define IBUFSIZE 1024

void hexdump(const string& filename)
{
    fstream ifile(filename.c_str(),
        ios_base::in | ios_base::binary);
    char *ibuff = new char[IBUFSIZE];
    char *obuff = new char[(IBUFSIZE*2)+1];
    int i;

    if(!ifile.is_open())
    {
        cout << "Cannot Open " << filename.c_str()
             << " for reading\n";
        return;
    }
    if(!ibuff || !obuff)
    {
        cout << "Cannot Allocate buffers\n";
        ifile.close();
        return;
    }

    while(!ifile.eof())
    {
        memset(obuff,0,(IBUFSIZE*2)+1);
        memset(ibuff,0,IBUFSIZE);
        ifile.read(ibuff,IBUFSIZE);

        // corner case where file is exactly a multiple of
        // 16 bytes in length
        if(ibuff[0] == 0 && ifile.eof())
            break;

        for(i = 0; i < IBUFSIZE; i++)
        {
            if(ibuff[i] >= ' ')
                obuff[i] = ibuff[i];
            else
                obuff[i] = '.';

            cout << setfill('0') << setw(2) << hex
                 << (int)ibuff[i] << ' ';
        }
        cout << "  " << obuff << endl;
    }
    ifile.close();
}

int main(int argc, char* argv[])
{
	const char * filename = ".\\data\\none.JPG";
	const char * outputfile = ".\\data\\output.txt";
	// hexdump(filename);

	ifstream infile(filename, ios::in|ios::binary);
	fstream f(outputfile, ios::out);

	unsigned char c;
	char buffer[1024];
	f.write("= { ", 4);
	int cnt = 0;
	while(infile.read((char*)&c, 1)) {
		sprintf(buffer, "0x%02X", c);
		f.write(buffer, strlen(buffer));
		f.write(", ", 2);
		cnt++;
	}
	f.write("};", 2);

	cout<<" bytes num : " << cnt << endl;
	return 0;
}

