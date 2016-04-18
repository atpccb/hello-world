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
* Source file: Icon_HDR
* Dimensions:  28 * 18
* NumColors:   9
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

static GUI_CONST_STORAGE GUI_COLOR ColorsIcon_HDR[] = {
     0xFF00FF,0x000000,0x404040,0x402020
    ,0x406060,0xC0DCC0,0xC0C0C0,0xFFFFFF
    ,0xF0FBFF
};

static GUI_CONST_STORAGE GUI_LOGPALETTE PalIcon_HDR = {
  9,	/* number of entries */
  1, 	/* Has transparency */
  &ColorsIcon_HDR[0]
};

static GUI_CONST_STORAGE unsigned char acIcon_HDR[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x00,
  0x02, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x21,
  0x02, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x21,
  0x02, 0x20, 0x02, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x20, 0x02, 0x21,
  0x02, 0x20, 0x02, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x20, 0x02, 0x20,
  0x02, 0x22, 0x22, 0x27, 0x22, 0x72, 0x77, 0x72, 0x27, 0x77, 0x22, 0x22, 0x22, 0x21,
  0x02, 0x22, 0x22, 0x28, 0x22, 0x82, 0x82, 0x28, 0x27, 0x22, 0x72, 0x22, 0x22, 0x21,
  0x02, 0x20, 0x02, 0x28, 0x22, 0x82, 0x82, 0x28, 0x27, 0x22, 0x72, 0x20, 0x02, 0x21,
  0x03, 0x30, 0x03, 0x35, 0x55, 0x53, 0x53, 0x35, 0x35, 0x55, 0x53, 0x30, 0x03, 0x30,
  0x03, 0x33, 0x33, 0x35, 0x33, 0x53, 0x53, 0x35, 0x35, 0x35, 0x33, 0x33, 0x33, 0x31,
  0x03, 0x33, 0x33, 0x36, 0x33, 0x63, 0x63, 0x36, 0x36, 0x36, 0x33, 0x33, 0x33, 0x31,
  0x03, 0x30, 0x03, 0x36, 0x33, 0x63, 0x66, 0x63, 0x36, 0x33, 0x63, 0x30, 0x03, 0x31,
  0x01, 0x10, 0x01, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x01, 0x10,
  0x01, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
  0x01, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
  0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

GUI_CONST_STORAGE GUI_BITMAP bmIcon_HDR = {
  28, /* XSize */
  18, /* YSize */
  14, /* BytesPerLine */
  4, /* BitsPerPixel */
  acIcon_HDR,  /* Pointer to picture data (indices) */
  &PalIcon_HDR  /* Pointer to palette */
};

/* *** End of file *** */
