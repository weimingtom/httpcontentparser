#include "stdafx.h"
#include ".\crypt.h"
#include ".\cryptopputiliy.h"

#define KEYLENGTH  0x00800000
#define ENCRYPT_ALGORITHM CALG_RC4 
#define ENCRYPT_BLOCK_SIZE 8


bool DecryptFile(
    LPTSTR pszSourceFile, 
    LPTSTR pszDestinationFile, 
    LPTSTR pszPassword);

namespace yanglei_utility {
bool DecryptFile(LPTSTR pszSourceFile,  LPTSTR pszDestinationFile) {
	return ::DecryptFile(pszSourceFile, pszDestinationFile, PASSWORD);
}
};



bool DecryptFile(
    LPTSTR pszSourceFile, 
    LPTSTR pszDestinationFile, 
    LPTSTR encryptKey)
{ 
	//AES_ECB_Decrypt(encryptKey, pszSourceFile, pszDestinationFile);
    return true;
}


