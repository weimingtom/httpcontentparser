#include "stdafx.h"
#include "httpcontentcheck.h"
#include <webcontenttype.h>
#include <utility/httppacket.h>
#include <sysutility.h>
#include <com\FilterSetting_i.c>
#include <com\FilterSetting.h>



///////////////////////////////////////////////////////
// class ImageHandler
//=========================
// constructor and deconstructor
ImageHandler::ImageHandler() {
}

ImageHandler::~ImageHandler() {
}

//=================================
// member functions
void ImageHandler::handle(HTTPPacket *packet)  {
}

// ±£´æÍ¼Æ¬ÄÚÈÝ
void ImageHandler::saveContent(HTTPPacket * packet) {
}

///////////////////////////////////////////////////////
// class TextContentHander
//===================================
TextContentHander::TextContentHander() {
}

TextContentHander::~TextContentHander() {
}


//=================================
// member functions
int TextContentHander::handle(HTTPPacket *packet) {
	if (false == isTextPacket(packet)) 
		return 0;


	return 1;
}

bool TextContentHander::isTextPacket(HTTPPacket *packet) {
	if ((packet->getContentType() & CONTYPE_XML)  || 
		(packet->getContentType() & CONTYPE_HTML) ) {
		return true;
	} else { 
		return false;
	}
}