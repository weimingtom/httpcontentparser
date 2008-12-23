#ifndef _RULE_MANAGEMENT_GLOBALDATA_H__
#define _RULE_MANAGEMENT_GLOBALDATA_H__

#include <string>
#include <set>
#include <map>
#include <syncobject\SyncObject.h>
#include <utility\FileMapping.h>

// 该类负责统一管理规则数据
// 现成同步，使用粗粒度的线程同步，所有的线程同步都在
// CGlobalData中完成。
class CGlobalData {
public:
	CGlobalData(void);
	~CGlobalData(void);
public:
	// 载入数据
	void loadSetting();
	void storeSetting();

	void addDns(const _bstr_t &t);
	void removeDns(const _bstr_t &t);
	bool checkIP(const unsigned int ipaddress) ;
	
	void setIPCheck(const bool checked);
private: 
	
	// 应用程序设置
	class AppSetting { 
	private:
		friend class CGlobalData;
		void loadSetting();
		void storeSetting();
		void enableIpCheck(bool enable);
		bool shouldCheckIp() const;

		AppSetting();
	private:
		// member variables;
		bool bIpCheck_;
	} appSetting_;

	// 控制CheckSetting
	class CheckSetting {
	private:
		friend class CGlobalData;
		CheckSetting();
		~CheckSetting();

		void loadSetting();
		void storeSetting();

		bool checkIP(const unsigned int ipaddress);
		bool checkIP(const char * ipaddress) ;

		void addDns(const _bstr_t &t);
		void addip(const unsigned int ip, const unsigned int port);
		void removeDns(const _bstr_t &t);

		typedef std::set<_bstr_t> DNS_SET;
		typedef std::set<unsigned int> IP_SET;
		DNS_SET dnss_;
		IP_SET  ips_;

		// 以下参数运用FileMapping机制保存规则
		// 1.我们使用GetTickCount()函数，表示规则版本
		// 2.当发觉当前版本与内存中版本不同时，重新载入
		// FileMapping中的规则。
		// 载入规则
		void loadRulesFromFile();		
		void loadRulesFromShareMemory(); 
		DWORD seGlobaltModifyFlags();	// 通知所有人规则已经改变
		DWORD setSelfModifyFlags();		// 告诉自身规则已经同步
		bool  rulesModified();			// 规则是否改变
		bool  rulesInitialize();		// 规则是否已经初始化
		DWORD changed_ticket_;			// 保存当前规则的跟新日期
	} checkSetting_;

	CComAutoCriticalSection cs_;
	bool setting_changed_;
};

#endif  // _RULE_MANAGEMENT_GLOBALDATA_H__