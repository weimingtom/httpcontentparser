#include "StdAfx.h"
#include ".\webcontenttest.h"
#include <webcontenttype.h>

WebContentTest::WebContentTest(void) {
}

WebContentTest::~WebContentTest(void) {
}

void WebContentTest::testImageType() {

	// IMAGE_TYPE_GIF
	{
	unsigned type = IMAGE_TYPE_GIF;
	CPPUNIT_ASSERT(true == isImage(type));
	CPPUNIT_ASSERT(false == isText(type));
	CPPUNIT_ASSERT(false == isPorn(type));

	setPron(&type);

	CPPUNIT_ASSERT(true == isImage(type));
	CPPUNIT_ASSERT(false == isText(type));
	CPPUNIT_ASSERT(true == isPorn(type));

	resetPorn(&type);
	CPPUNIT_ASSERT(true == isImage(type));
	CPPUNIT_ASSERT(false == isText(type));
	CPPUNIT_ASSERT(false == isPorn(type));
	}

	// type == IMAGE_TYPE_JPEG
	{
	unsigned type = IMAGE_TYPE_JPEG;
	CPPUNIT_ASSERT(true == isImage(type));
	CPPUNIT_ASSERT(false == isText(type));
	CPPUNIT_ASSERT(false == isPorn(type));

	setPron(&type);

	CPPUNIT_ASSERT(true == isImage(type));
	CPPUNIT_ASSERT(false == isText(type));
	CPPUNIT_ASSERT(true == isPorn(type));

	resetPorn(&type);
	CPPUNIT_ASSERT(true == isImage(type));
	CPPUNIT_ASSERT(false == isText(type));
	CPPUNIT_ASSERT(false == isPorn(type));
	}

	// type == IMAGE_TYPE_PNG
	{
	unsigned type = IMAGE_TYPE_PNG;
	CPPUNIT_ASSERT(true == isImage(type));
	CPPUNIT_ASSERT(false == isText(type));
	CPPUNIT_ASSERT(false == isPorn(type));

	setPron(&type);

	CPPUNIT_ASSERT(true == isImage(type));
	CPPUNIT_ASSERT(false == isText(type));
	CPPUNIT_ASSERT(true == isPorn(type));

	resetPorn(&type);
	CPPUNIT_ASSERT(true == isImage(type));
	CPPUNIT_ASSERT(false == isText(type));
	CPPUNIT_ASSERT(false == isPorn(type));
	}

	// type == IMAGE_TYPE_BMP
	{
	unsigned type = IMAGE_TYPE_BMP;
	CPPUNIT_ASSERT(true == isImage(type));
	CPPUNIT_ASSERT(false == isText(type));
	CPPUNIT_ASSERT(false == isPorn(type));

	setPron(&type);

	CPPUNIT_ASSERT(true == isImage(type));
	CPPUNIT_ASSERT(false == isText(type));
	CPPUNIT_ASSERT(true == isPorn(type));

	resetPorn(&type);
	CPPUNIT_ASSERT(true == isImage(type));
	CPPUNIT_ASSERT(false == isText(type));
	CPPUNIT_ASSERT(false == isPorn(type));
	}
}

void  WebContentTest::textOtherTypes() {
	// CONTYPE_CSS
	{
	unsigned type = CONTYPE_CSS;
	CPPUNIT_ASSERT(false == isImage(type));
	CPPUNIT_ASSERT(false == isText(type));
	CPPUNIT_ASSERT(false == isPorn(type));

	setPron(&type);

	CPPUNIT_ASSERT(false == isImage(type));
	CPPUNIT_ASSERT(false == isText(type));
	CPPUNIT_ASSERT(true == isPorn(type));

	resetPorn(&type);
	CPPUNIT_ASSERT(false == isImage(type));
	CPPUNIT_ASSERT(false == isText(type));
	CPPUNIT_ASSERT(false == isPorn(type));
	}
}

void WebContentTest::testTextType() {
		// CONTYPE_HTML
	{
	unsigned type = CONTYPE_HTML;
	CPPUNIT_ASSERT(false == isImage(type));
	CPPUNIT_ASSERT(true == isText(type));
	CPPUNIT_ASSERT(false == isPorn(type));

	setPron(&type);

	CPPUNIT_ASSERT(false == isImage(type));
	CPPUNIT_ASSERT(true == isText(type));
	CPPUNIT_ASSERT(true == isPorn(type));

	resetPorn(&type);
	CPPUNIT_ASSERT(false == isImage(type));
	CPPUNIT_ASSERT(true == isText(type));
	CPPUNIT_ASSERT(false == isPorn(type));
	}
}