#ifndef _UTILITY_DEBUG_MESSAGE_H__
#define _UTILITY_DEBUG_MESSAGE_H__

#ifndef _HIDE_DEBUG_MSG_ 
#define DEBUG_MESSAGE(fmt) OutputDebugString(fmt)
#else
#define DEBUG_MESSAGE(fmt)
#endif

#endif  // _UTILITY_DEBUG_MESSAGE_H__