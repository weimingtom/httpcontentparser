#ifndef _SPI_INSTALLER_SPIDEFINES_H__
#define _SPI_INSTALLER_SPIDEFINES_H__

#define PACKETSGRASPER_DLL_NAME		_T("PacketsGrasper.dll")
#define REG_INSTALL_KEY				_T("SYSTEM\\CurrentControlSet\\Services\\WinSock2\\PacketsCapture_SPI")
#define REG_INSTALL_PATH_ITEM		_T("PathName")
#define	REG_PROTOCOL_CATALOG_KEY	_T("SYSTEM\\CurrentControlSet\\Services\\WinSock2\\Parameters\\Protocol_Catalog9\\Catalog_Entries")
#define REG_PROTOCOL_CATALOG_ITEM	_T("PackedCatalogItem")

#define MAX_PROTOCOL_CATALOG_LENTH	sizeof(WSAPROTOCOL_INFOW) + MAX_PATH

#endif // _SPI_INSTALLER_SPIDEFINES_H__