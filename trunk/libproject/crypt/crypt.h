#ifndef _CRYPT_CRYPT_H__
#define _CRYPT_CRYPT_H__


namespace yanglei_utility {

// ¼ÓÃÜÎÄ¼þ
bool EncryptFile(LPTSTR pszSourceFile, 
				   LPTSTR pszDestinationFile);

bool DecryptFile( LPTSTR pszSourceFile, LPTSTR pszDestinationFile);

#define PASSWORD "40B3A4B67DC14DE0BDC3-8D519F0AD7B6"

};

#endif  // _CRYPT_CRYPT_H__