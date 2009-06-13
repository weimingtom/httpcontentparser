#ifndef _WSUT_H__
#define _WSUT_H__

#ifdef WSUT_EXPORTS
#define WSUT_API __declspec(dllexport)
#else
#define WSUT_API __declspec(dllimport)
#endif

WSUT_API int CheckProgram(const char * status);
WSUT_API int CheckStatus(const char * status);
WSUT_API int CallUtility(const char * status);

#endif  // 