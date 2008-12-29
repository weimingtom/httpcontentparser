/****************************************************************************
 *																			*		 
 *								GuiToolKit  								*	
 *							 (MFC extension)								*			 
 * Created by Francisco Campos G. www.beyondata.com fcampos@beyondata.com	*
 *--------------------------------------------------------------------------*		   
 *																			*
 * This program is free software; so you are free to use it any of your		*
 * applications (Freeware, Shareware, Commercial), but leave this header	*
 * intact.																	*
 *																			*
 * These files are provided "as is" without warranty of any kind.			*
 *																			*
 *			       GuiToolKit is forever FREE CODE !!!!!					*
 *																			*
 *--------------------------------------------------------------------------*
 * Created by: Francisco Campos G.											*
 * Bug Fixes and improvements : (Add your name)								*
 * -Francisco Campos														*				
 *																			*	
 ****************************************************************************/

#ifndef __GUILIB_H
#define __GUILIB_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Additional MFC headers
#ifndef __AFXTEMPL_H__
	#include <afxtempl.h>
#endif //__AFXTEMPL_H__

#ifndef __AFXPRIV_H__
	#include <afxpriv.h>
#endif //__AFXPRIV_H__

#if _MSC_VER >= 1300
	#include <..\atlmfc\src\mfc\afximpl.h>
#else
	#include <..\src\afximpl.h>
#endif

#define 	GUISTYLE_XP   0x08001 	
#define		GUISTYLE_2003 0x08002
#define		GUISTYLE_2003MENUBTN 0x08021
#define		WIN_NT		  0x08003 	
#define		WIN_2000	0x08004
#define		WIN_XP		0x08005
#define		WIN_95		0x08006
#define		WIN_98		0x08007
#define		WIN_32		0x08008
#define		WIN_ME		0x08009
#define		WIN_95OSR2	0x0800A
#define		WIN_98_SE	0x0800B

#endif //__GUILIB_H


