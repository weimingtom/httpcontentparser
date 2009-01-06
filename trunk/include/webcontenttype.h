#ifndef _INCLUDE_IMAGE_TYPE_H__
#define _INCLUDE_IMAGE_TYPE_H__



// 类型的使用
// |----|--------------------------------------|
// |指向|          ==-具体类型===              |

#define CONTENT_CHECK_PORN			0x10000000
#define CONTENT_CHECK_NORMAL		0x20000000
#define CONTENT_CHECK_UNKNOWN		0x00000000
#define CONTENT_CHECK_NOTYET		0xFFFFFFFF


#define CONTYPE_HTML	0x00000001
#define CONTYPE_CSS 	0x00000002
#define CONTYPE_JS		0x00000004
#define CONTYPE_XML		0x00000008
#define CONTYPE_GIF		0x00000010
#define CONTYPE_JPG		0x00000020
#define CONTYPE_PNG		0x00000040
#define CONTYPE_BMP		0x00000080
#define CONTYPE_UNKNOWN 0x08000000

#define CONTYPE_FLAG	0xf0000000					// 前四位是 标志位, 在比较类型的时候应该将它取0
#define CONTYPE_PORN    CONTENT_CHECK_PORN			// 所有包含此为的packet为黄色内容
		// 位置内容





#define IMAGE_TYPE_JPEG   CONTYPE_JPG
#define IMAGE_TYPE_GIF	  CONTYPE_GIF
#define IMAGE_TYPE_PNG	  CONTYPE_PNG
#define IMAGE_TYPE_BMP	  CONTYPE_BMP
// so we can use binary test whether this
// type of images should be check or not.


// get relative type's filename ext

#define FILE_EXT_HTML	TEXT("html")
#define FILE_EXT_CSS	TEXT("css")
#define FILE_EXT_JS		TEXT("js")
#define FILE_EXT_XML	TEXT("xml")
#define FILE_EXT_GIF	TEXT("gif")
#define FILE_EXT_JPG	TEXT("jpg")
#define FILE_EXT_BMP	TEXT("bmp")
#define FILE_EXT_PNG	TEXT("png")
inline
const TCHAR * getExt(const int type) {
	if (type == CONTYPE_HTML) {
		return FILE_EXT_HTML;
	} else if (type == CONTYPE_CSS) {
		return FILE_EXT_CSS;
	} else if (type == CONTYPE_JS) {
		return FILE_EXT_JS;
	} else if (type == CONTYPE_XML) {
		return FILE_EXT_XML;
	} else if (type == CONTYPE_GIF) {
		return FILE_EXT_GIF;
	} else if (type == CONTYPE_JPG) {
		return FILE_EXT_JPG;
	} else if (type == CONTYPE_PNG) {
		return FILE_EXT_PNG;
	} else if (type == CONTYPE_BMP) {
		return FILE_EXT_BMP;
	}

	return NULL;
}

inline
bool isImage(const unsigned type) {
	const unsigned actual_type = type & (~CONTYPE_PORN);
	return (( IMAGE_TYPE_GIF == actual_type ) ||
			( IMAGE_TYPE_JPEG == actual_type ) ||
			( IMAGE_TYPE_PNG == actual_type ) ||
			( IMAGE_TYPE_BMP == actual_type )) ? true : false;
}

// 是否是黄色内容
inline
bool isPorn(const unsigned type) {
	return (CONTYPE_PORN & type) ? true : false;	
}

inline
void setPron(unsigned *type) {
	*type |=  (CONTYPE_PORN);
}

inline
void resetPorn(unsigned *type) {
	*type &= (~CONTYPE_PORN);
}


inline
bool isText(const unsigned type) {
	const unsigned actual_type = type & (~CONTYPE_PORN);
	return ((CONTYPE_HTML == actual_type) || (CONTYPE_XML == actual_type)) ? true : false;
}



#endif  // _INCLUDE_IMAGE_TYPE_H__