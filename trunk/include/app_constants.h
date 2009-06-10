#ifndef _SPI_INSTALLER_SPIDEFINES_H__
#define _SPI_INSTALLER_SPIDEFINES_H__

#include <assert.h>

#define PACKETSGRASPER_DLL_NAME		_T("PacketsGrasper.dll")
#define REG_INSTALL_KEY				_T("SYSTEM\\CurrentControlSet\\Services\\WinSock2\\PacketsCapture_SPI")
#define REG_INSTALL_PATH_ITEM		_T("PathName")
#define	REG_PROTOCOL_CATALOG_KEY	_T("SYSTEM\\CurrentControlSet\\Services\\WinSock2\\Parameters\\Protocol_Catalog9\\Catalog_Entries")
#define REG_PROTOCOL_CATALOG_ITEM	_T("PackedCatalogItem")

// 保存软件安装的注册表信息
#define REG_SOFTWARE_DIR			_T("SOFTWARE\\family007")
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

// 用于防治Service启动多次
#define COM_SERVICE_MUTEX	TEXT("7F6E3389-60CF-4b19-B1BD-BC6258E63BDC")

// 应用程序的名称
#define APPLICATION_MAINUI_NAME	TEXT("MainUI")

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

// 应用程序的常量， 窗口名称 窗口类

#define MAIN_WINDOW_TITLE (TEXT("MainUI"))
#define MAIN_WINDOW_CLASS (TEXT("#32770"))

#define MAIN_WINDOW_PROP_NAME	(TEXT("Unicode_value"))
#define MAIN_WINDOW_PROP_VALUE  7777

// for Eyecare windows
#define EYECARE_MAIN_WND_CLASS (TEXT("Eyecare_main_wnd_class"))
#define EYECARE_MAIN_WND_TITLE (TEXT(""))
#define EYECARE_MUTEX_NAME		TEXT("8EF40F9D-71A7-40d9-A229-599105419DAE")

#define HOME_WEBSITES			TEXT("www.family007.com")

#define WINDIR_INI_FILE_CONTENT TEXT("#the setting of the product\r\n[AutoRun]\r\nvalue=true\r\n")


// 用来存储安装时间，文件没有什么用
#define WINDOWS_FILE_TO_STORE_INSTALLDATE	TEXT("snowman.ini")
#define INSTALL_DIR_DATE_INDICATOR	TEXT("nwist.dll")
#define UNINSTALL_UTILITY		("mvs.exe")

// 在启动LockPC和Eyecare时指定，如果没有指定程序直接退出
#define LAUNCH_PARAM			TEXT("websnowman")

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