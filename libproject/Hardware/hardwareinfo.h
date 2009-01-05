#ifndef _HARDWARE_HARDWARE_INFO_H__
#define _HARDWARE_HARDWARE_INFO_H__

UINT GetCPUID(BYTE * info, UINT bufLen);
UINT GetBIOSInof(BYTE * szSystemInfo, UINT uSystemInfoLen);
UINT GetHarddiskSeria(BYTE * info, UINT bufLen);
UINT GetMAC(BYTE * szSystemInfo, UINT uSystemInfoLen);

#endif  // _HARDWARE_HARDWARE_INFO_H__