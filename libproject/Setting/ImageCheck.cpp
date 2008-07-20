#include "StdAfx.h"
#include ".\imagecheck.h"
#include ".\dnslist.h"
#include <assert.h>


ImageCheck::ImageCheck(void) {
	show_image_ = true;
	check_png_ = true;
	check_jpeg_ = true;
	check_bmp_ = true;
}

ImageCheck::ImageCheck(const DNSList *dns_list) : dns_list_(dns_list) {
	assert(false);
}

ImageCheck::~ImageCheck(void) {
}

//  «∑Ò”¶∏√ºÏ≤‚Õº∆¨
void ImageCheck::checkPNG(const bool checked) {
	check_png_  = checked;
}
void ImageCheck::checkJPEG(const bool checked) {
	check_jpeg_  = checked;
}
void ImageCheck::checkBMP(const bool checked) {
	check_bmp_  = checked;
}

void ImageCheck::enableShowImage(const bool showed) {
	show_image_ = showed;
}

int ImageCheck::checkImage(const std::string &dns) {
	return 0;
}