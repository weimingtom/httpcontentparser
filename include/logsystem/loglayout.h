#ifndef _LOGSYSTEM_LOG_LAYOUT_H__
#define _LOGSYSTEM_LOG_LAYOUT_H__

// LogLayout 可应用模式
// 使用静态方式的方法当然可以节省内存，但却不能使用Decroate模式啦！

namespace LogSystem {
class LogLayout {
public:
	static const std::string LAYOUT_BASIC;
	static const std::string LAYOUT_NONE;
	static const std::string LAYOUT_MODULENAME;
	static LogLayout * Create(const std::string &type);

	virtual std::string getFmtMsg(const char *msg) = 0;
	virtual ~LogLayout();
protected:
	LogLayout();

protected:
	inline int AdjustBuffer();
	inline int AllocBuffer();
	inline int FreeBuffer(); 

	static const char * ALLOC_FAILED_MSG;
private:
	int buffer_size_;
	char *buffer_;
};

};

#endif 
