#include "stdafx.h"
#include ".\crypt.h"
#include ".\debug.h"
#include ".\cryptopputiliy.h"

#define KEYLENGTH  0x00800000
#define ENCRYPT_ALGORITHM CALG_RC4 
#define ENCRYPT_BLOCK_SIZE 8


bool EncryptFile(LPTSTR pszSourceFile, 
				   LPTSTR pszDestinationFile, 
				   LPTSTR pszPassword);


namespace yanglei_utility {
bool EncryptFile(LPTSTR pszSourceFile, 
				 LPTSTR pszDestinationFile) {
	return ::EncryptFile(pszSourceFile, pszDestinationFile, PASSWORD);
}
};

bool EncryptFile(
    LPTSTR pszSourceFile, 
    LPTSTR pszDestinationFile, 
    LPTSTR encryptkey)
{ 
    AES_ECB_Encrypt(encryptkey, pszSourceFile, pszDestinationFile);
    return true; 
} // End Encryptfile.

