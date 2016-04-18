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
* Source file: TV_TimeLapseB
* Dimensions:  24 * 21
* NumColors:   2
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

static GUI_CONST_STORAGE GUI_COLOR ColorsTV_TimeLapseB[] = {
     0x000000,0xFFFFFF
};

static GUI_CONST_STORAGE GUI_LOGPALETTE PalTV_TimeLapseB = {
  2,	/* number of entries */
  0, 	/* No transparency */
  &ColorsTV_TimeLapseB[0]
};

static GUI_CONST_STORAGE unsigned char acTV_TimeLapseB[] = {
  ________, ________, ________,
  ________, ________, ________,
  ________, ________, ________,
  ________, ________, ________,
  ________, ________, ________,
  ____XXXX, XX_X____, ________,
  ___XX__X, __XX____, ________,
  ___X___X, _XXX__XX, XXX_____,
  _____X_X, _____XXX, XXXX____,
  ______XX, ____XXXX, XXXXX___,
  __X____X, ____XXXX, XXXXX___,
  __XX____, ____XXX_, __XXX___,
  ____X___, ____XXX_, __XXX___,
  ____XXXX, X___XXXX, XXXXX___,
  ________, ____XXXX, XXXXX___,
  ________, ________, ________,
  ________, ________, ________,
  ________, ________, ________,
  ________, ________, ________,
  ________, ________, ________,
  ________, ________, ________
};

GUI_CONST_STORAGE GUI_BITMAP bmTV_TimeLapseB = {
  24, /* XSize */
  21, /* YSize */
  3, /* BytesPerLine */
  1, /* BitsPerPixel */
  acTV_TimeLapseB,  /* Pointer to picture data (indices) */
  &PalTV_TimeLapseB  /* Pointer to palette */
};

/* *** End of file *** */
