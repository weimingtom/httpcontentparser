#include "stdafx.h"
#include <stdio.h>
#include <io.h>
#include <DebugOutput.h>

CryptoPP::SecByteBlock HexDecodeString(const char *hex)
{
	CryptoPP::StringSource ss(hex, true, new CryptoPP::HexDecoder);
	CryptoPP::SecByteBlock result((size_t)ss.MaxRetrievable());
	ss.Get(result, result.size());
	return result;
}

void AES_ECB_Encrypt(const char *hexKey, const char *infile, const char *outfile)
{
	_DEBUG_STREAM_TRC_("[Cryptopp]  [" <<__FUNCTION__<<"] Input Files"<< infile<<" Output files : "<< outfile);
	try {
		if (access(infile, 0) == -1) {
			_DEBUG_STREAM_TRC_("[Cryptopp]  [" <<__FUNCTION__<<"] File "<< infile<< " not exists!");
			return;
		}

		using namespace CryptoPP;
		CryptoPP::SecByteBlock key = HexDecodeString(hexKey);
		CryptoPP::ECB_Mode<AES>::Encryption aes(key, key.size());
		FileSource(infile, true, new CryptoPP::StreamTransformationFilter(aes, new FileSink(outfile)));
	} catch (...) {
		_DEBUG_STREAM_TRC_("[Cryptopp]  [" <<"Unknown exception!");
	}
}

void AES_ECB_Decrypt(const char *hexKey, const char *infile, const char *outfile)
{
	_DEBUG_STREAM_TRC_("[Cryptopp]  [" <<__FUNCTION__<<"] Input Files"<< infile<<" Output files : "<< outfile);
	try {
		if (access(infile, 0) == -1) {
			_DEBUG_STREAM_TRC_("[Cryptopp]  [" <<__FUNCTION__<<"] File "<< infile<< " not exists!");
			return;
		}

		using namespace CryptoPP;
		CryptoPP::SecByteBlock key = HexDecodeString(hexKey);
		CryptoPP::ECB_Mode<AES>::Decryption aes(key, key.size());
		FileSource(infile, true, new StreamTransformationFilter(aes, new FileSink(outfile)));
	} catch(...) {
		_DEBUG_STREAM_TRC_("[Cryptopp]  [" <<"Unknown exception!");
	}
}
