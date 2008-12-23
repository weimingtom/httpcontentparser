#ifndef _RULE_MANAGEMENT_GLOBALDATA_H__
#define _RULE_MANAGEMENT_GLOBALDATA_H__

#include <string>
#include <set>
#include <map>
#include <syncobject\SyncObject.h>
#include <utility\FileMapping.h>

// ���ฺ��ͳһ�����������
// �ֳ�ͬ����ʹ�ô����ȵ��߳�ͬ�������е��߳�ͬ������
// CGlobalData����ɡ�
class CGlobalData {
public:
	CGlobalData(void);
	~CGlobalData(void);
public:
	// ��������
	void loadSetting();
	void storeSetting();

	void addDns(const _bstr_t &t);
	void removeDns(const _bstr_t &t);
	bool checkIP(const unsigned int ipaddress) ;
	
	void setIPCheck(const bool checked);
private: 
	
	// Ӧ�ó�������
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

	// ����CheckSetting
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

		// ���²�������FileMapping���Ʊ������
		// 1.����ʹ��GetTickCount()��������ʾ����汾
		// 2.��������ǰ�汾���ڴ��а汾��ͬʱ����������
		// FileMapping�еĹ���
		// �������
		void loadRulesFromFile();		
		void loadRulesFromShareMemory(); 
		DWORD seGlobaltModifyFlags();	// ֪ͨ�����˹����Ѿ��ı�
		DWORD setSelfModifyFlags();		// ������������Ѿ�ͬ��
		bool  rulesModified();			// �����Ƿ�ı�
		bool  rulesInitialize();		// �����Ƿ��Ѿ���ʼ��
		DWORD changed_ticket_;			// ���浱ǰ����ĸ�������
	} checkSetting_;

	CComAutoCriticalSection cs_;
	bool setting_changed_;
};

#endif  // _RULE_MANAGEMENT_GLOBALDATA_H__