#ifndef _SOFTWARE_ENCRYPT_BASE_ENCTRYPT_H__
#define _SOFTWARE_ENCRYPT_BASE_ENCTRYPT_H__

// 最简单的软件注册码技术

#include <string>

std::string generateSN();

bool validateSN(const std::string &serialnumber);

#endif  // _SOFTWARE_ENCRYPT_BASE_ENCTRYPT_H__