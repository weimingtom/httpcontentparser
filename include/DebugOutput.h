#ifndef _DEBUG_OUTPUT_H__
#define _DEBUG_OUTPUT_H__

#include <sstream>

#ifdef  ___OUPUT_DEBUG_STRING___
#define ODS(STR) OutputDebugString(STR)
#else
#define ODS(STR)
#endif

#define _INIT_FILESCOPT_OSTRSTREAM_	namespace { std::stringstream __output_debug_string_stream__;};
#define _INIT_OUTPUT_OSTRSTREAM_ std::stringstream __output_debug_string_stream__;
#define _DEBUG_STREAM_DBG_	__output_debug_string_stream__<<"[DBG] "
#define _DEBUG_STREAM_TRC_	__output_debug_string_stream__<<"[TRC] "
#define _OUTPUT_FMT_STRING_	ODS(__output_debug_string_stream__.str().c_str()); __output_debug_string_stream__.str("");

#endif  // _DEBUG_OUTPUT_H__