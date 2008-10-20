#ifndef _SPI_INSTALLER_SPIDEFINES_H__
#define _SPI_INSTALLER_SPIDEFINES_H__

#include <assert.h>

#define PACKETSGRASPER_DLL_NAME		_T("PacketsGrasper.dll")
#define REG_INSTALL_KEY				_T("SYSTEM\\CurrentControlSet\\Services\\WinSock2\\PacketsCapture_SPI")
#define REG_INSTALL_PATH_ITEM		_T("PathName")
#define	REG_PROTOCOL_CATALOG_KEY	_T("SYSTEM\\CurrentControlSet\\Services\\WinSock2\\Parameters\\Protocol_Catalog9\\Catalog_Entries")
#define REG_PROTOCOL_CATALOG_ITEM	_T("PackedCatalogItem")

#define MAX_PROTOCOL_CATALOG_LENTH	sizeof(WSAPROTOCOL_INFOW) + MAX_PATH

#define SERVICE_FILENAME			_T("FilterSetting.exe")

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
#define CONFIG_HOTKEY_SWITCHUSER				TEXT("switchuser")

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



#endif // _SPI_INSTALLER_SPIDEFINES_H__