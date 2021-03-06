#ifndef _DEBUG_OUTPUT_H__
#define _DEBUG_OUTPUT_H__

#include <sstream>

#ifdef UNICODE
typedef  std::wstringstream     STRINGSTREAM;
#else
typedef  std::stringstream     STRINGSTREAM;
#endif

#ifdef  ___OUPUT_DEBUG_STRING___
	#define _DEBUG_STREAM_OUTPUT_(TITLE, FMT) { STRINGSTREAM __output_debug_string_stream__;	\
		__output_debug_string_stream__<<TITLE<<FMT;	\
		OutputDebugString(__output_debug_string_stream__.str().c_str());}\

	#define _DEBUG_STREAM_DBG_(FMT)	_DEBUG_STREAM_OUTPUT_("[DEG]", FMT)
	#define _DEBUG_STREAM_TRC_(FMT)		_DEBUG_STREAM_OUTPUT_("[TRC]", FMT)

#else
	#define _DEBUG_STREAM_DBG_(FMT)	
	#define _DEBUG_STREAM_TRC_(FMT)	
#endif 

#endif  // _DEBUG_OUTPUT_H__