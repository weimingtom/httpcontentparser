#ifndef _SPI_INSTALLER_SPIDEFINES_H__
#define _SPI_INSTALLER_SPIDEFINES_H__

#include <assert.h>

#define PACKETSGRASPER_DLL_NAME		_T("PacketsGrasper.dll")
#define REG_INSTALL_KEY				_T("SYSTEM\\CurrentControlSet\\Services\\WinSock2\\PacketsCapture_SPI")
#define REG_INSTALL_PATH_ITEM		_T("PathName")
#define	REG_PROTOCOL_CATALOG_KEY	_T("SYSTEM\\CurrentControlSet\\Services\\WinSock2\\Parameters\\Protocol_Catalog9\\Catalog_Entries")
#define REG_PROTOCOL_CATALOG_ITEM	_T("PackedCatalogItem")

// ���������װ��ע�����Ϣ
#define REG_SOFTWARE_DIR			_T("SOFTWARE\\Family007")
#define REG_SOFTWARE_INSTALLPATH		_T("InstallPath")
#define REG_SOFTWARE_INSTALLDATE		_T("InstallKey")		// ��װ����
#define REG_SOFTWARE_PRODUCTSN		_T("ProductSN")	// ���к�
#define REG_SOFTWARE_TRAIL_DAYES		20

#define MAX_PROTOCOL_CATALOG_LENTH	sizeof(WSAPROTOCOL_INFOW) + MAX_PATH

#define SERVICE_FILENAME			_T("nwrs.exe")

#define DEFAULT_INIT_PASSWORD		_T("I&lns*31_MaEi(c")

#define PACKETSFILTERED_INSTALL_SUCC			0
#define	PACKETSFILTERED_FILE_NOT_FOUND			-800
#define PACKETSFILTERED_NOT_INSTALL				-801
#define PACKETSFILTERED_ALREADY_INSTALL			-802
#define PACKETSFILTERED_OPEN_REG_FAILED			-803
#define PACKETSFILTERED_SAVE_PATH_FAILED		-804
#define PACKETSFILTERED_READ_VALUE_FAILED		-805
#define PACKETSFILTERED_CREATE_ITEM_FAILED		-806
#define PACKETSFILTERED_SET_VALUE_FAILED		-807
#define PACKETSFILTERED_REG_DELETE_FAILED		-808

// Ӧ�ó��������
#define APPLICATION_MAINUI_NAME	TEXT("Family007")
#define APPLICATION_MAINUI_EXE_FILE	TEXT("family007.exe")

// ע���������
#define REGISTER_MAINUI_KEY	APPLICATION_MAINUI_NAME


// �ȼ�����
#define HOTKEY_LANUCH_MAINUI	100
#define	HOTKEY_SHOW_MAINUI		200
#define HOTKEY_SHOW_SWITCH_USER	300

#define CONFIG_HOTKEY_LAUNCH					TEXT("launch")
#define CONFIG_HOTKEY_SHOWUI					TEXT("showui")
#define CONFIG_HOTKEY_SWITCHUSER		TEXT("switchuser")

inline
TCHAR * getHotkeyname(const int type) {
	switch (type) {
		case HOTKEY_SHOW_MAINUI:
			return CONFIG_HOTKEY_SHOWUI;
		case HOTKEY_SHOW_SWITCH_USER:
			return CONFIG_HOTKEY_SWITCHUSER;
		case HOTKEY_LANUCH_MAINUI:
			return CONFIG_HOTKEY_LAUNCH;
		default:
			assert(false);
			return TEXT("");
	}
}

// Ӧ�ó���ĳ����� �������� ������

#define MAIN_WINDOW_PROP_NAME	(TEXT("Unicode_value"))
#define MAIN_WINDOW_PROP_VALUE  7777

#define HOME_WEBSITES			TEXT("www.family007.com")
#define WEBSITES_BUYNOW			TEXT("www.family007.com")

#define WINDIR_INI_FILE_CONTENT TEXT("#the setting of the product\r\n[AutoRun]\r\nvalue=true\r\n")


// �����洢��װʱ�䣬�ļ�û��ʲô��
#define WINDOWS_FILE_TO_STORE_INSTALLDATE	TEXT("snowman.ini")
#define INSTALL_DIR_DATE_INDICATOR	TEXT("nwist.dll")
#define UNINSTALL_UTILITY		("mvs.exe")

// ������LockPC��Eyecareʱָ�������û��ָ������ֱ���˳�
#define LAUNCH_LOCK_PARAM					TEXT("websnowman_lockpc")
#define LAUNCH_EYECARE_PARAM			TEXT("websnowman_eyecare")

// Author Name
#define ANOTHER_GENERIC		TEXT("#generic")	// generic
#define ANOTHER_WWL			TEXT("#wwl")	// white web list
#define ANOTHER_BWL				TEXT("#bwl")	// black web list
#define ANOTHER_BSL				TEXT("#bsl")		// black search list
#define ANOTHER_WH				TEXT("#wh")		// Web History
#define ANOTHER_EP					TEXT("#ep")		// eyelight protect
#define ANOTHER_AC				TEXT("#ac")		// app control
#define ANOTHER_SS					TEXT("#ss")		// screen snapshot
#define ANOTHER_IT					TEXT("#it")		// internet time
#define ANOTHER_OP				TEXT("#op")		// options
#define ANOTHER_ABOUT		TEXT("#about")		// about

#endif // _SPI_INSTALLER_SPIDEFINES_H__