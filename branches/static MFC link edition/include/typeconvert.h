#ifndef _FILTER_SETTING_UTILITY_H__
#define _FILTER_SETTING_UTILITY_H__

#include <assert.h>

inline
const bool convert(const VARIANT_BOOL vb) {
	if (VARIANT_TRUE == vb) 
		return true;
	else if (VARIANT_FALSE == vb) 
		return false;

	assert(false);
	return false;
}

inline 
const VARIANT_BOOL convert(const bool value) {
	if (true == value) {
		return VARIANT_TRUE;
	} else if (false == value) {
		return VARIANT_FALSE;
	}
	assert(false);
	return VARIANT_FALSE;
}

inline 
const VARIANT_BOOL convert(const BOOL value) {
	if (TRUE == value) {
		return VARIANT_TRUE;
	} else if (FALSE == value) {
		return VARIANT_FALSE;
	}
	assert(false);
	return VARIANT_FALSE;
}

#endif  // _FILTER_SETTING_UTILITY_H__