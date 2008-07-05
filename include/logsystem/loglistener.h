#ifndef _LOGSYSTEM_LOG_LISTENER_H__
#define _LOGSYSTEM_LOG_LISTENER_H__

#include <string>
#include <map>


namespace LogSystem {

// ������������ע��Ϊ��ʹ���е�logListener�ܹ�����ListenerContainer�ļ��
// ���е�logListenerӦ�ò��Ǿ�̬����


// LogListener����ƣ� �����û������Լ�ʵ��һ��Listener,��ֱ�Ӵ���
// �������ִ�����ʽ�������ǲ���ͳһ���ɸ���������ഴ���ķ�ʽ����Ҫ������
// Listener�ĸ����Ծ����ģ�����ʹ���е�Listener����ͳһ�Ĵ�����ʽ������
// FileListener������Ҫ�ƶ��ļ����� ��WindowsListenr������Ҫ�ƶ��ļ����

// ListenerContainer�����
// ����Log����Ϣ�ַ�������Ҫһ������Listener�Ļ��ƣ�����Listener�������
// ListenerContainer����
// ****����һ�������ಢ��ֻ�ܱ�������Ϣ�ַ���LogMsgDispatcher��
// ��LogListenerʹ�ã������಻��ʹ������
// (�����Ѿ��ı�),�κ��û�������ʹ�����ṩ��getListener����****

// 1. ListenerContainer��LogListener���Զ�����
// ÿ���û�ʵ����һ��LogListener�ļ̳��࣬�������Զ�
// �����丸��(LogLIstener)�Ĺ��캯����ListenerContainer���ڴ�ʱ��Listener���뵽
// �����У����κ�һ���̳����ڱ�����ʱ��������丸���������������ʱ�������Զ�
// �Ĵ�ListenerContainer�б��Ƴ���
// *** ListenerContainer�������Զ����������е�LogListener

// �������Զ��ͷŵ�Listener
// ���Ǳ����ܹ��Զ��ͷ�Listener, ����ListenerContainer��һ�����Ǽ���
// ������ǿ�����ListenerContainer����ʱ������������δ�����ٵĶ���
// �����������ٿ��Ը����ж���Ϊ�����ٵ�ָʾ


// **** ������⣺ ����û�ָ��������ͬ����LogListener,
// ��ô�Զ�����ListenerContainer�Ļ��ƽ���ʧ��
// ����Ǻã�������
// Ŀǰֻ�ܲ���assert�ķ�ʽ������!!!
// ��������Ļ������ṩһ�ֻ�ȡͬ��Listener�ķ�ʽ����
// ע�� ���ǹ�����ListenerContainer��һЩ�ӿ�
// ��ListenerContainer������
// 2008-6-7

class LogLayout;
 
// ���е�log�����߶�����̳��Դ���
// �����ṩ��һЩ�����ķ���
class LogListener {
public:
	LogListener(const std::string &name);
	virtual void UpdateMessage(const char *msg, const int len) = 0;
	const std::string& getName() { return name_;}

	virtual ~LogListener();
	LogListener();
private:
	std::string name_;

	// �Ƿ��Զ��ͷ��أ�
	bool bNeedAutoRelease_;
};

// ���ฺ�𱣴����е�Listener
// �κ�һ��Listener�ڱ������ǽ����Զ��ӵ���������
// ���û����ͷ�listenerʱ�����ᱻ�Զ��ͷ�
// listener���û��Լ��������ߴݻ�
class ListenerContainer {
public:
	static ListenerContainer * getInstance();
	LogListener * getListener(const std::string & listener_name);
	~ListenerContainer();
private:
	friend class LogListener;
	// ������������ͨ����LogListener�ڹ��캯�������������е���
	// �û���Ӧ�õ�������������
	bool AddListener(const std::string & listener_name, LogListener *listener);
	void RemoveListener(const std::string &listener_name);

	typedef std::map<std::string, LogListener*> LISTENER_MAP;
	LISTENER_MAP listeners_;

	ListenerContainer();

	static const std::string SYNC_OBJECT_NAME;
};

};

#endif  // _LOGSYSTEM_LOG_LISTENER_H__

