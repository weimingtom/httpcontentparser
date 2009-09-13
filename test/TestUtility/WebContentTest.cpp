#include "StdAfx.h"
#include ".\webcontenttest.h"
#include <webcontenttype.h>

#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;


void testImageType() {

	// IMAGE_TYPE_GIF
	{
	unsigned type = IMAGE_TYPE_GIF;
	BOOST_ASSERT(true == isImage(type));
	BOOST_ASSERT(false == isText(type));
	BOOST_ASSERT(false == isPorn(type));

	setPron(&type);

	BOOST_ASSERT(true == isImage(type));
	BOOST_ASSERT(false == isText(type));
	BOOST_ASSERT(true == isPorn(type));

	resetPorn(&type);
	BOOST_ASSERT(true == isImage(type));
	BOOST_ASSERT(false == isText(type));
	BOOST_ASSERT(false == isPorn(type));
	}

	// type == IMAGE_TYPE_JPEG
	{
	unsigned type = IMAGE_TYPE_JPEG;
	BOOST_ASSERT(true == isImage(type));
	BOOST_ASSERT(false == isText(type));
	BOOST_ASSERT(false == isPorn(type));

	setPron(&type);

	BOOST_ASSERT(true == isImage(type));
	BOOST_ASSERT(false == isText(type));
	BOOST_ASSERT(true == isPorn(type));

	resetPorn(&type);
	BOOST_ASSERT(true == isImage(type));
	BOOST_ASSERT(false == isText(type));
	BOOST_ASSERT(false == isPorn(type));
	}

	// type == IMAGE_TYPE_PNG
	{
	unsigned type = IMAGE_TYPE_PNG;
	BOOST_ASSERT(true == isImage(type));
	BOOST_ASSERT(false == isText(type));
	BOOST_ASSERT(false == isPorn(type));

	setPron(&type);

	BOOST_ASSERT(true == isImage(type));
	BOOST_ASSERT(false == isText(type));
	BOOST_ASSERT(true == isPorn(type));

	resetPorn(&type);
	BOOST_ASSERT(true == isImage(type));
	BOOST_ASSERT(false == isText(type));
	BOOST_ASSERT(false == isPorn(type));
	}

	// type == IMAGE_TYPE_BMP
	{
	unsigned type = IMAGE_TYPE_BMP;
	BOOST_ASSERT(true == isImage(type));
	BOOST_ASSERT(false == isText(type));
	BOOST_ASSERT(false == isPorn(type));

	setPron(&type);

	BOOST_ASSERT(true == isImage(type));
	BOOST_ASSERT(false == isText(type));
	BOOST_ASSERT(true == isPorn(type));

	resetPorn(&type);
	BOOST_ASSERT(true == isImage(type));
	BOOST_ASSERT(false == isText(type));
	BOOST_ASSERT(false == isPorn(type));
	}
}

void  textOtherTypes() {
	// CONTYPE_CSS
	{
	unsigned type = CONTYPE_CSS;
	BOOST_ASSERT(false == isImage(type));
	BOOST_ASSERT(false == isText(type));
	BOOST_ASSERT(false == isPorn(type));

	setPron(&type);

	BOOST_ASSERT(false == isImage(type));
	BOOST_ASSERT(false == isText(type));
	BOOST_ASSERT(true == isPorn(type));

	resetPorn(&type);
	BOOST_ASSERT(false == isImage(type));
	BOOST_ASSERT(false == isText(type));
	BOOST_ASSERT(false == isPorn(type));
	}
}

void testFFFF() {

	BOOST_ASSERT (false == (isImage(0xFFFFFFFF) || isText(0xFFFFFFF)));
}

void testTextType() {
		// CONTYPE_HTML
	{
	unsigned type = CONTYPE_HTML;
	BOOST_ASSERT(false == isImage(type));
	BOOST_ASSERT(true == isText(type));
	BOOST_ASSERT(false == isPorn(type));

	setPron(&type);

	BOOST_ASSERT(false == isImage(type));
	BOOST_ASSERT(true == isText(type));
	BOOST_ASSERT(true == isPorn(type));

	resetPorn(&type);
	BOOST_ASSERT(false == isImage(type));
	BOOST_ASSERT(true == isText(type));
	BOOST_ASSERT(false == isPorn(type));
	}
}