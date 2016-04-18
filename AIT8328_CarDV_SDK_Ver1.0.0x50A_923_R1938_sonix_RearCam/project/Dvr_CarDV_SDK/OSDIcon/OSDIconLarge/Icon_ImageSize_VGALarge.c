/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
*                           www.segger.com                           *
**********************************************************************
*
* C-file generated by
*
*        �C/GUI-BitmapConvert V5.04.
*        Compiled Jan  8 2010, 16:46:31
*          (c) 2002-2005  Micrium, Inc.
  www.micrium.com

  (c) 1998-2005  Segger
  Microcontroller Systeme GmbH
  www.segger.com
*
**********************************************************************
*
* Source file: Icon_ImageSize_VGA
* Dimensions:  24 * 32
* NumColors:   3
*
**********************************************************************
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

/*   Palette
The following are the entries of the palette table.
Every entry is a 32-bit value (of which 24 bits are actually used)
the lower   8 bits represent the Red component,
the middle  8 bits represent the Green component,
the highest 8 bits (of the 24 bits used) represent the Blue component
as follows:   0xBBGGRR
*/

static GUI_CONST_STORAGE GUI_COLOR ColorsIcon_ImageSize_VGA[] = {
     0xFF00FF,0x030303,0xFFFFFF
};

static GUI_CONST_STORAGE GUI_LOGPALETTE PalIcon_ImageSize_VGA = {
  3,	/* number of entries */
  1, 	/* Has transparency */
  &ColorsIcon_ImageSize_VGA[0]
};

static GUI_CONST_STORAGE unsigned char acIcon_ImageSize_VGA[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x05, 0x55, 0x55, 0x55, 0x55, 0x54,
  0x06, 0xAA, 0xAA, 0xAA, 0xAA, 0xA4,
  0x06, 0xAA, 0xAA, 0xAA, 0xAA, 0xA4,
  0x06, 0x95, 0x55, 0x55, 0x55, 0xA4,
  0x06, 0x90, 0x00, 0x00, 0x01, 0xA4,
  0x06, 0x90, 0x00, 0x00, 0x01, 0xA4,
  0x06, 0x90, 0x00, 0x00, 0x01, 0xA4,
  0x06, 0x90, 0x00, 0x00, 0x01, 0xA4,
  0x06, 0x90, 0x00, 0x00, 0x01, 0xA4,
  0x05, 0x50, 0x00, 0x00, 0x01, 0x54,
  0x15, 0x55, 0x55, 0x55, 0x55, 0x50,
  0x1A, 0x5A, 0x5A, 0xA9, 0x56, 0x90,
  0x1A, 0x5A, 0x5A, 0xA9, 0x56, 0x90,
  0x1A, 0x5A, 0x69, 0x55, 0x5A, 0x94,
  0x1A, 0x5A, 0x69, 0x55, 0x5A, 0xA4,
  0x1A, 0x59, 0x69, 0x55, 0x5A, 0x64,
  0x1A, 0x59, 0x69, 0x55, 0x59, 0x64,
  0x1A, 0x69, 0x69, 0xA9, 0x69, 0x64,
  0x16, 0x69, 0x69, 0xA9, 0x69, 0x64,
  0x06, 0x69, 0x69, 0x69, 0x6A, 0xA4,
  0x06, 0x65, 0x69, 0x69, 0xAA, 0xA4,
  0x06, 0xA5, 0x69, 0x69, 0xA5, 0x65,
  0x06, 0xA5, 0x69, 0x69, 0xA5, 0x69,
  0x05, 0xA5, 0x6A, 0xA9, 0xA5, 0x69,
  0x01, 0x95, 0x5A, 0xA5, 0xA5, 0x69,
  0x01, 0x55, 0x55, 0x55, 0x55, 0x55,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

GUI_CONST_STORAGE GUI_BITMAP bmIcon_ImageSize_VGA = {
  24, /* XSize */
  32, /* YSize */
  6, /* BytesPerLine */
  2, /* BitsPerPixel */
  acIcon_ImageSize_VGA,  /* Pointer to picture data (indices) */
  &PalIcon_ImageSize_VGA  /* Pointer to palette */
};

/* *** End of file *** */
