// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
//��ı�׼�������� DLL �е������ļ��������������϶���� LOGGER_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
//�κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ 
// LOGGER_API ������Ϊ�ǴӴ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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
