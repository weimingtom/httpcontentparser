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



// 特化模板
template <>
class Enumerator1 <int> {
public:
	virtual int Enum(const int data) = 0;
};

template <>
class Enumerator1 <bool> {
public:
	virtual int Enum(const bool data) = 0;
};

template <>
class Enumerator1 <unsigned int> {
public:
	virtual int Enum(const unsigned int data) = 0;
};

template <>
class Enumerator1 <short> {
public:
	virtual int Enum(const short data) = 0;
};

template <>
class Enumerator1 <char> {
public:
	virtual int Enum(const char data) = 0;
};

template <>
class Enumerator1 <long> {
public:
	virtual int Enum(const long data) = 0;
};

// 特化模板2
template <typename T1>
class Enumerator2 <T1, int> {
public:
	virtual int Enum(const T1 &data, const int data2) = 0;
};

template <typename T1>
class Enumerator2 <T1, short> {
public:
	virtual int Enum(const T1 &data, const short data2) = 0;
};

template <typename T1>
class Enumerator2 <T1, long> {
public:
	virtual int Enum(const T1 &data, const long data2) = 0;
};

template <typename T1>
class Enumerator2 <T1, bool> {
public:
	virtual int Enum(const T1 &data, const bool data2) = 0;
};

template <typename T1>
class Enumerator2 <T1, unsigned int> {
public:
	virtual int Enum(const T1 &data, const unsigned int data2) = 0;
};

template <>
class Enumerator2 <int, int> {
public:
	virtual int Enum(const int data, const int data2) = 0;
};

template <>
class Enumerator2 <int, short> {
public:
	virtual int Enum(const int data, const short data2) = 0;
};

template <>
class Enumerator2 <int, bool> {
public:
	virtual int Enum(const int data, const bool data2) = 0;
};

template <>
class Enumerator2 <int, char> {
public:
	virtual int Enum(const int data, const char data2) = 0;
};


template <>
class Enumerator2 <unsigned int, int> {
public:
	virtual int Enum(const int data, const int data2) = 0;
};

template <>
class Enumerator2 <unsigned int, short> {
public:
	virtual int Enum(const int data, const short data2) = 0;
};

template <>
class Enumerator2 <unsigned int, bool> {
public:
	virtual int Enum(const int data, const bool data2) = 0;
};

template <>
class Enumerator2 <unsigned int, char> {
public:
	virtual int Enum(const int data, const char data2) = 0;
};

template <>
class Enumerator2 <long, int> {
public:
	virtual int Enum(const int data, const int data2) = 0;
};

template <>
class Enumerator2 <long, short> {
public:
	virtual int Enum(const int data, const short data2) = 0;
};

template <>
class Enumerator2 <long, bool> {
public:
	virtual int Enum(const int data, const bool data2) = 0;
};

template <>
class Enumerator2 <long, char> {
public:
	virtual int Enum(const int data, const char data2) = 0;
};


template <>
class Enumerator2 <short, short> {
public:
	virtual int Enum(const int data, const short data2) = 0;
};

template <>
class Enumerator2 <short, bool> {
public:
	virtual int Enum(const int data, const bool data2) = 0;
};

template <>
class Enumerator2 <short, char> {
public:
	virtual int Enum(const int data, const char data2) = 0;
};

template <>
class Enumerator2 <bool, bool> {
public:
	virtual int Enum(const int data, const bool data2) = 0;
};

template <>
class Enumerator2 <bool, char> {
public:
	virtual int Enum(const int data, const char data2) = 0;
};

template <>
class Enumerator2 <char, char> {
public:
	virtual int Enum(const int data, const char data2) = 0;
};




#endif  // _SETTING_ENUMERATE_H__