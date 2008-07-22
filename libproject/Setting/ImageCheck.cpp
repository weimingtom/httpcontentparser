#include "StdAfx.h"
#include ".\imagecheck.h"
#include ".\dnslist.h"
#include <assert.h>
#include <windows.h>
#include <utility/httppacket.h>


ImageCheck::ImageCheck(void) {
	assert(false);
}

ImageCheck::ImageCheck(const DNSList *dns_list) : dns_list_(dns_list) {
	show_image_ = true;
	check_png_ = true;
	check_jpeg_ = true;
	check_bmp_ = true;
	check_gif_ = true;
	
}

ImageCheck::~ImageCheck(void) {
}

//  «∑Ò”¶∏√ºÏ≤‚Õº∆¨
void ImageCheck::enableShowImage(const bool showed) {
	show_image_ = showed;
}

bool ImageCheck::showImage() const {
	return show_image_;
}

bool ImageCheck::needCheck(const int type) const {
	switch (type) {
		//case HTTP_RESPONSE_HEADER::CO:
		//	check_bmp_ = enable;
		//	break;
		case HTTP_RESPONSE_HEADER::CONTYPE_PNG:
			return check_png_;
		case HTTP_RESPONSE_HEADER::CONTYPE_JPG:
			return check_jpeg_;
		case HTTP_RESPONSE_HEADER::CONTYPE_GIF:
			return check_gif_;
		default:
			assert(false);
			break;
	}
}

void ImageCheck::enableCheck(const int type, const bool enable) {
	switch (type) {
		//case HTTP_RESPONSE_HEADER::CO:
		//	check_bmp_ = enable;
		//	break;
		case HTTP_RESPONSE_HEADER::CONTYPE_PNG:
			check_png_ = enable;
			break;
		case HTTP_RESPONSE_HEADER::CONTYPE_JPG:
			check_jpeg_ = enable;
			break;
		case HTTP_RESPONSE_HEADER::CONTYPE_GIF:
			check_gif_ = enable;
			break;
		default:
			assert(false);
			break;
	}
}
