#ifndef _INCLUDE_IMAGE_TYPE_H__
#define _INCLUDE_IMAGE_TYPE_H__



#define CONTYPE_HTML	0x00000001
#define CONTYPE_CSS 	0x00000002
#define CONTYPE_JS		0x00000004
#define CONTYPE_XML		0x00000008
#define CONTYPE_GIF		0x00000010
#define CONTYPE_JPG		0x00000020
#define CONTYPE_PNG		0x00000040
#define CONTYPE_BMP		0x00000080
#define CONTYPE_UNKNOWN 0x80000000


#define IMAGE_TYPE_JPEG   CONTYPE_JPG
#define IMAGE_TYPE_GIF	  CONTYPE_GIF
#define IMAGE_TYPE_PNG	  CONTYPE_PNG
#define IMAGE_TYPE_BMP	  CONTYPE_BMP
// so we can use binary test whether this
// type of images should be check or not.

#endif  // _INCLUDE_IMAGE_TYPE_H__