// 下列 ifdef 块是创建使从 DLL 导出更简单的
//宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 LOGGER_EXPORTS
// 符号编译的。在使用此 DLL 的
//任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将 
// LOGGER_API 函数视为是从此 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef LOGGER_EXPORTS
#define LOGGER_API __declspec(dllexport)
#else
#define LOGGER_API __declspec(dllimport)
#endif

#include <sstream>
#include <boost/logging/format.hpp>


#define LOGGER_DEBUG_OUTPUT(FMT) { std::stringstream __output_debug_string_stream__;	\
	__output_debug_string_stream__<<FMT;	\
	OutputDebugString(__output_debug_string_stream__.str().c_str());}\


LOGGER_API void set_logger_leve(boost::logging::level::type type);
LOGGER_API void logger_trace(std::stringstream &s);
LOGGER_API void logger_debug(std::stringstream &s);
LOGGER_API void logger_info(std::stringstream &s);
LOGGER_API void logger_error(std::stringstream &s);
LOGGER_API void logger_fatal(std::stringstream &s);
