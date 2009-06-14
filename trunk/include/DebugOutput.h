#ifndef _DEBUG_OUTPUT_H__
#define _DEBUG_OUTPUT_H__

#include <strstream>

#ifdef  ___OUPUT_DEBUG_STRING___

#define _INIT_FILESCOPT_OSTRSTREAM_	namespace { std::ostrstream __output_debug_string_stream__;};
#define _INIT_OUTPUT_OSTRSTREAM_ std::ostrstream __output_debug_string_stream__;
#define _DEBUG_STREAM_DBG_	__output_debug_string_stream__<<"[DBG] "
#define _DEBUG_STREAM_TRC_	__output_debug_string_stream__<<"[TRC] "
#define _OUTPUT_FMT_STRING_	 __output_debug_string_stream__<<std::endl; OutputDebugString(__output_debug_string_stream__.str());

#else
#define _INIT_FILESCOPT_OSTRSTREAM
#define _INIT_OUTPUT_OSTRSTREAM_ 
#define _DEBUG_STREAM_DBG	
#define _DEBUG_STREAM_TRC_
#define _OUTPUT_FMT_STRING_
#endif 
#endif  // _DEBUG_OUTPUT_H__