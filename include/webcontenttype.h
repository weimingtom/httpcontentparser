#ifndef _INCLUDE_IMAGE_TYPE_H__
#define _INCLUDE_IMAGE_TYPE_H__



// ���͵�ʹ��
// |----|--------------------------------------|
// |ָ��|          ==-��������===              |

#define CONTYPE_HTML	0x00000001
#define CONTYPE_CSS 	0x00000002
#define CONTYPE_JS		0x00000004
#define CONTYPE_XML		0x00000008
#define CONTYPE_GIF		0x00000010
#define CONTYPE_JPG		0x00000020
#define CONTYPE_PNG		0x00000040
#define CONTYPE_BMP		0x00000080
#define CONTYPE_UNKNOWN 0x08000000

#define CONTYPE_FLAG	0xf0000000			// ǰ��λ�� ��־λ, �ڱȽ����͵�ʱ��Ӧ�ý���ȡ0
#define CONTYPE_PORN    0x10000000			// ���а�����Ϊ��packetΪ��ɫ����
		// λ������


#define IMAGE_TYPE_JPEG   CONTYPE_JPG
#define IMAGE_TYPE_GIF	  CONTYPE_GIF
#define IMAGE_TYPE_PNG	  CONTYPE_PNG
#define IMAGE_TYPE_BMP	  CONTYPE_BMP
// so we can use binary test whether this
// type of images should be check or not.


inline
bool isImage(const unsigned type) {
	const unsigned actual_type = type & (~CONTYPE_PORN);
	return (( IMAGE_TYPE_GIF & actual_type ) ||
			( IMAGE_TYPE_JPEG & actual_type ) ||
			( IMAGE_TYPE_PNG & actual_type ) ||
			( IMAGE_TYPE_BMP & actual_type )) ? true : false;
}

// �Ƿ��ǻ�ɫ����
inline
unsigned isPorn(const unsigned type) {
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
unsigned isText(const unsigned type) {
	const unsigned actual_type = type & (~CONTYPE_PORN);
	return (CONTYPE_HTML & actual_type) || (CONTYPE_XML & actual_type) ? true : false;
}

#endif  // _INCLUDE_IMAGE_TYPE_H__