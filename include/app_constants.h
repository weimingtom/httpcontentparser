#ifndef _SPI_INSTALLER_SPIDEFINES_H__
#define _SPI_INSTALLER_SPIDEFINES_H__

#include <assert.h>

#define PACKETSGRASPER_DLL_NAME		_T("PacketsGrasper.dll")
#define REG_INSTALL_KEY				_T("SYSTEM\\CurrentControlSet\\Services\\WinSock2\\PacketsCapture_SPI")
#define REG_INSTALL_PATH_ITEM		_T("PathName")
#define	REG_PROTOCOL_CATALOG_KEY	_T("SYSTEM\\CurrentControlSet\\Services\\WinSock2\\Parameters\\Protocol_Catalog9\\Catalog_Entries")
#define REG_PROTOCOL_CATALOG_ITEM	_T("PackedCatalogItem")

// 保存软件安装的注册表信息
#define REG_SOFTWARE_DIR			_T("SOFTWARE\\Family007")
#define REG_SOFTWARE_INSTALLPATH		_T("InstallPath")
#define REG_SOFTWARE_INSTALLDATE		_T("InstallKey")		// 安装日期
#define REG_SOFTWARE_PRODUCTSN		_T("ProductSN")	// 序列号
#define REG_SOFTWARE_TRAIL_DAYES		20

#define MAX_PROTOCOL_CATALOG_LENTH	sizeof(WSAPROTOCOL_INFOW) + MAX_PATH

#define SERVICE_FILENAME			_T("nwrs.exe")

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

// 应用程序的名称
#define APPLICATION_MAINUI_NAME	TEXT("Family007")
#define APPLICATION_MAINUI_EXE_FILE	TEXT("family007.exe")

// 注册表项名称
#define REGISTER_MAINUI_KEY	APPLICATION_MAINUI_NAME


// 热键定义
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

#define HOME_WEBSITES			TEXT("www.family007.com")
#define WEBSITES_BUYNOW			TEXT("www.family007.com")

#define WINDIR_INI_FILE_CONTENT TEXT("#the setting of the product\r\n[AutoRun]\r\nvalue=true\r\n")


// 用来存储安装时间，文件没有什么用
#define WINDOWS_FILE_TO_STORE_INSTALLDATE	TEXT("family007.ini")
#define INSTALL_DIR_DATE_INDICATOR	TEXT("nwist.dll")

// 在启动LockPC和Eyecare时指定，如果没有指定程序直接退出
#define LAUNCH_LOCK_PARAM					TEXT("family007_lockpc")
#define LAUNCH_EYECARE_PARAM			TEXT("family007_eyecare")

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