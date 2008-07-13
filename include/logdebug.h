#ifndef _INCLUDE_LOG_DEBUG_H__
#define _INCLUDE_LOG_DEBUG_H__

#ifdef _DEBUG

inline 
void OutputDebugInfo(const char * str) {
	OutputDebugString(str);
}

inline
void WriteLog(const char * filename, const SOCKET s, const char * str) {
	std::fstream file;
	file.open(filename, std::ios::out | std::ios::app | std::ios::binary);
	file.write(str, strlen(str));
	file.close();
}

inline
void WriteLog(const char *filename, const SOCKET s,  const char * data, const int len) {
	char buffer[1024];
	std::fstream file;
	file.open(filename, std::ios::out | std::ios::app | std::ios::binary);

	// 收到日期
	sprintf(buffer, "\r\n===========[%d : %d==========]\r\n", s, GetTickCount());
	file.write(buffer, strlen(buffer));
	file.write(data, len);
	sprintf(buffer, "\r\nlength : %d\r\n", len);
	file.write(buffer, strlen(buffer));
	file.close();
}

#else 

inline 
void OutputDebugInfo(const char * str) {
}


inline
void WriteLog(const char * filename, const SOCKET s, const char * str);

inline
void WriteLog(const char *filename, const SOCKET s,  const char * data, const int len);

#endif


#endif  // _INCLUDE_LOG_DEBUG_H__