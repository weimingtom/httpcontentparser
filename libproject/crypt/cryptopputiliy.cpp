#include "stdafx.h"


CryptoPP::SecByteBlock HexDecodeString(const char *hex)
{
	CryptoPP::StringSource ss(hex, true, new CryptoPP::HexDecoder);
	CryptoPP::SecByteBlock result((size_t)ss.MaxRetrievable());
	ss.Get(result, result.size());
	return result;
}

void AES_ECB_Encrypt(const char *hexKey, const char *infile, const char *outfile)
{
	using namespace CryptoPP;
	CryptoPP::SecByteBlock key = HexDecodeString(hexKey);
	CryptoPP::ECB_Mode<AES>::Encryption aes(key, key.size());
	FileSource(infile, true, new StreamTransformationFilter(aes, new FileSink(outfile)));
}

void AES_ECB_Decrypt(const char *hexKey, const char *infile, const char *outfile)
{
	using namespace CryptoPP;
	CryptoPP::SecByteBlock key = HexDecodeString(hexKey);
	CryptoPP::ECB_Mode<AES>::Decryption aes(key, key.size());
	FileSource(infile, true, new StreamTransformationFilter(aes, new FileSink(outfile)));
}
