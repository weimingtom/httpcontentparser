#ifndef _CRYPT_CRYPT_H__
#define _CRYPT_CRYPT_H__

// ¼ÓÃÜÎÄ¼þ
bool EncryptFile(LPTSTR pszSourceFile, 
				   LPTSTR pszDestinationFile);

bool DecryptFile( LPTSTR pszSourceFile, LPTSTR pszDestinationFile);

#define PASSWORD "40B3A4B6-7DC1-4DE0-BDC3-8D519F0AD7B6"

#endif  // _CRYPT_CRYPT_H__