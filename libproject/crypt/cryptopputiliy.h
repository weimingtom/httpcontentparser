#ifndef _CRYPTOPP_UTILITY_H__
#define _CRYPTOPP_UTILITY_H__

CryptoPP::SecByteBlock HexDecodeString(const char *hex);
void AES_ECB_Encrypt(const char *hexKey, const char *infile, const char *outfile);
void AES_ECB_Decrypt(const char *hexKey, const char *infile, const char *outfile);

#endif  // _CRYPTOPP_UTILITY_H__