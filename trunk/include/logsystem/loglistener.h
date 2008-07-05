#ifndef _LOGSYSTEM_LOG_LISTENER_H__
#define _LOGSYSTEM_LOG_LISTENER_H__

#include <string>
#include <map>


namespace LogSystem {

// ××××××注意为了使所有的logListener能够接受ListenerContainer的监控
// 所有的logListener应该不是静态对象


// LogListener的设计， 首先用户必须自己实现一个Listener,并直接创建
// 采用这种创建方式，而不是采用统一的由父类或其他类创建的方式，主要是由于
// Listener的复杂性决定的，我们使所有的Listener具有统一的创建方式，例如
// FileListener可能需要制定文件名， 而WindowsListenr可能需要制定文件句柄

// ListenerContainer的设计
// 整个Log的消息分发机制需要一个保存Listener的机制，保存Listener的类就有
// ListenerContainer负责，
// ****他是一个单件类并且只能被负责消息分发的LogMsgDispatcher类
// 及LogListener使用，其他类不能使用他。
// (此项已经改变),任何用户都可以使用它提供的getListener功能****

// 1. ListenerContainer对LogListener的自动管理
// 每当用户实例化一个LogListener的继承类，他都会自动
// 调用其父类(LogLIstener)的构造函数，ListenerContainer会在此时将Listener加入到
// 到其中，当任何一个继承类在被销毁时都会调用其父类的析构函数，此时，他会自动
// 的从ListenerContainer中被移除。
// *** ListenerContainer并不能自动的销毁所有的LogListener

// 如何设计自动释放的Listener
// 我们必须能够自动释放Listener, 由于ListenerContainer是一个的那件类
// 因此我们可以在ListenerContainer销毁时，销毁所有仍未不销毁的对象
// 或者我们至少可以给出有对象为被销毁的指示


// **** 设计问题： 如果用户指定了两个同名的LogListener,
// 那么自动载入ListenerContainer的机制将会失败
// 如何是好？？？？
// 目前只能采用assert的方式提醒了!!!
// 如果这样的话必须提供一种获取同名Listener的方式啊？
// 注： 我们公开了ListenerContainer的一些接口
// 将ListenerContainer公开？
// 2008-6-7

class LogLayout;
 
// 所有的log接收者都必须继承自此类
// 此类提供了一些基本的服务
class LogListener {
public:
	LogListener(const std::string &name);
	virtual void UpdateMessage(const char *msg, const int len) = 0;
	const std::string& getName() { return name_;}

	virtual ~LogListener();
	LogListener();
private:
	std::string name_;

	// 是否自动释放呢？
	bool bNeedAutoRelease_;
};

// 该类负责保存所有的Listener
// 任何一个Listener在被创建是将被自动加到这个类别当中
// 当用户在释放listener时，他会被自动释放
// listener由用户自己创建或者摧毁
class ListenerContainer {
public:
	static ListenerContainer * getInstance();
	LogListener * getListener(const std::string & listener_name);
	~ListenerContainer();
private:
	friend class LogListener;
	// 以下两个函数通常被LogListener在构造函数和析构函数中调用
	// 用户不应该调用这两个函数
	bool AddListener(const std::string & listener_name, LogListener *listener);
	void RemoveListener(const std::string &listener_name);

	typedef std::map<std::string, LogListener*> LISTENER_MAP;
	LISTENER_MAP listeners_;

	ListenerContainer();

	static const std::string SYNC_OBJECT_NAME;
};

};

#endif  // _LOGSYSTEM_LOG_LISTENER_H__

