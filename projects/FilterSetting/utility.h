#ifndef _FILTER_SETTING_UTILITY_H__
#define _FILTER_SETTING_UTILITY_H__

inline
const bool convert(const VARIANT_BOOL vb) {
	if (VARIANT_TRUE == vb) return true;
	else return false;
}


#endif  // _FILTER_SETTING_UTILITY_H__