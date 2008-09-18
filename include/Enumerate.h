#ifndef _SETTING_ENUMERATE_H__
#define _SETTING_ENUMERATE_H__

template <typename T>
class Enumerator1 {
public:
	virtual int Enum(const T& data) = 0;
};

template <typename T1, typename T2>
class Enumerator2 {
public:
	virtual int Enum(const T1 &data1, const T2& data2) = 0;
};

#endif  // _SETTING_ENUMERATE_H__