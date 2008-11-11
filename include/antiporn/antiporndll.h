#ifndef ANTIPORNDLL_HFILE
#define ANTIPORNDLL_HFILE

#ifdef ANTIPORNDLL_EXPORTS
#define ANTIPORNDLL_API __declspec(dllexport)
#else
#define ANTIPORNDLL_API __declspec(dllimport)
#endif

class PornDetectorBase {
public:
	// Detect porn from a raw RGB image in memory. NOTE: RGB, NOT BGR!
	virtual bool Detection(const uint8 *pixels, const int width, const int height, double *output_score) = 0;

	// Detect porn from a image filename. return false is NOT porn.
	virtual bool Detection(const char *filename, double *output_score) = 0;
};

ANTIPORNDLL_API bool CreateObject(PornDetectorBase** pObject);
ANTIPORNDLL_API void DeleteObject();

/* ----- We use OPENCV to read image files, the image formats opencv supports include: ----- */
/*
    * Windows: BMP, DIB£»
    * JPEG: JPEG, JPG, JPE
    * PNG
    * PBM, PGM, PPM
    * Sun rasters: SR, RAS
    * TIFF: TIFF TIF;
    * OpenEXR HDR: EXR
	* JPEG 2000: jp2 
*/

/* -----  OPENCV not supports the formats: ----- */
/* 
    * GIF
    * PSD
    * PCX
    * DXF
    * CDR 
	* TGA
	* EXIF
	* FPX
	* SVG
	* PCD
	* UFO
	* EPS
*/
/* ************************************************************************ 
If OPENCV doesn't supports the format, you need to read image using other image package, and call:
"bool AntiPorn_Detection(const uint8 *pixels, const int width, const int height, double *output_score)"
This function detects porn from a RGB image in memory. NOTE: RGB, NOT BGR! 
   ************************************************************************ */

#endif