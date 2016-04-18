
#ifndef	__UI_DRAW_GENERAL_H__
#define	__UI_DRAW_GENERAL_H__

/*===========================================================================
 * Include file
 *===========================================================================*/ 

#include "GUI_Type.h"
#include "AHC_Common.h"

/*===========================================================================
 * Macor define
 *===========================================================================*/ 

#define NULL_PARAM				(0xFFFFFFFF)

#define POS_PAGEINFO(x, pos)  	(x<=4)?(pos-(x-1)*3):(pos)

/*===========================================================================
 * Structure define
 *===========================================================================*/ 

typedef	void (DRAW_FUNC) (UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);

typedef	void (UI_DRAW_FUNC) (UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);

typedef struct {
#if 0
	int 		m_BlockID;
	int 		m_PosX;
	int 		m_PosY;
	int 		m_Enable;
#else
    UINT16         m_BlockID;
    UINT16         m_PosX;
    UINT16         m_PosY;
    UINT16         m_Enable;
#endif
	DRAW_FUNC*  m_DrawFunc;	
} UI_DARW_SET;

/*===========================================================================
 * Enum define
 *===========================================================================*/ 

typedef enum {

	VIDEO_GUI_MOVIE_RES = 0,
	VIDEO_GUI_UI_MODE,
	VIDEO_GUI_SD_STATE,
	VIDEO_GUI_WB_MODE,
	VIDEO_GUI_BATTERY,
	VIDEO_GUI_SCENE,
	VIDEO_GUI_FLASH,
	VIDEO_GUI_REC_STATE,
	VIDEO_GUI_ZOOM_BAR,
	VIDEO_GUI_EV,
	VIDEO_GUI_REMAIN_TIME,
	VIDEO_GUI_REC_TIME,
	VIDEO_GUI_RTC_TIME,
	VIDEO_GUI_LOCK_FILE,
	VIDEO_GUI_LOCK_NUM,
	VIDEO_GUI_MUTE,
	VIDEO_GUI_REC_POINT,
	VIDEO_GUI_GPS_STATE,
	VIDEO_GUI_VMD_STATE,
	VIDEO_GUI_VTL_STATE,		// VIDEO_REC_TIMELAPSE_EN
	VIDEO_GUI_DRIVER_ID,
	VIDEO_GUI_WIFI,
	VIDEO_GUI_WIFI_SWITCH,
	VIDEO_GUI_LDWS_LINE,
	VIDEO_GUI_FCWS_INFO,
	VIDEO_GUI_MAX,
	AUDIO_GUI_REC_TIME,
	AUDIO_GUI_REC_POINT

} VIDEO_GUI_BLOCK;

typedef enum {

	DSC_GUI_IMAGE_RES = 0,
	DSC_GUI_UI_MODE,
	DSC_GUI_SD_STATE,
	DSC_GUI_WB_MODE,
	DSC_GUI_BATTERY,
	DSC_GUI_SCENE,
	DSC_GUI_FLASH,
	DSC_GUI_SELF_TIMER,
	DSC_GUI_BURST,
	DSC_GUI_ZOOM_BAR,
	DSC_GUI_EV,
	DSC_GUI_REMAIN_NUM,
	DSC_GUI_RTC_TIME,
	DSC_GUI_GPS_STATE,
	DSC_GUI_VMD_STATE,
	DSC_GUI_DRIVER_ID,
	DSC_GUI_MAX

} DSC_GUI_BLOCK;

typedef enum {

	BROWSER_GUI_FILENAME = 0,
	BROWSER_GUI_UI_MODE,
	BROWSER_GUI_SD_STATE,
	BROWSER_GUI_BATTERY,
	BROWSER_GUI_FILE_DATE,
	BROWSER_GUI_MOV_TOTAL_TIME,
	BROWSER_GUI_RESOLUTION,
	BROWSER_GUI_MAX

} BROWSER_GUI_BLOCK;

typedef enum {

	MOVPB_GUI_STATUS = 0,
	MOVPB_GUI_FILE_INDEX,
	MOVPB_GUI_UI_MODE,
	MOVPB_GUI_SD_STATE,
	MOVPB_GUI_BATTERY,
	MOVPB_GUI_VOL_BAR,
	MOVPB_GUI_LOCK_FILE,
	MOVPB_GUI_FILENAME,
	MOVPB_GUI_CUR_TIME,
	MOVPB_GUI_TOTAL_TIME,
	MOVPB_GUI_MAX

} MOVPB_GUI_BLOCK;

typedef enum {

	AUDPB_GUI_STATUS = 0,
	AUDPB_GUI_FILE_INDEX,
	AUDPB_GUI_UI_MODE,
	AUDPB_GUI_SD_STATE,
	AUDPB_GUI_BATTERY,
	AUDPB_GUI_VOL_BAR,
	AUDPB_GUI_LOCK_FILE,
	AUDPB_GUI_FILENAME,
	AUDPB_GUI_CUR_TIME,
	AUDPB_GUI_TOTAL_TIME,
	AUDPB_GUI_MAX

} AUDPB_GUI_BLOCK;

typedef enum {

	JPGPB_GUI_FILE_INDEX = 0,
	JPGPB_GUI_UI_MODE,
	JPGPB_GUI_SD_STATE,
	JPGPB_GUI_BATTERY,
	JPGPB_GUI_LOCK_FILE,
	JPGPB_GUI_FILENAME,
	JPGPB_GUI_FILEDATE,
	JPGPB_GUI_MAX

} JPGPB_GUI_BLOCK;

typedef enum {

	SLIDE_GUI_STATUS = 0,
	SLIDE_GUI_FILE_INDEX,
	SLIDE_GUI_UI_MODE,
	SLIDE_GUI_SD_STATE,
	SLIDE_GUI_BATTERY,
	SLIDE_GUI_LOCK_FILE,
	SLIDE_GUI_CUR_TIME,
	SLIDE_GUI_TOTAL_TIME,
	SLIDE_GUI_MAX

} SLIDE_GUI_BLOCK;

typedef enum {

	TV_GUI_VIDEO_MOVIE_RES = 0,
	TV_GUI_VIDEO_UI_MODE,
	TV_GUI_VIDEO_SD_STATE,
	TV_GUI_VIDEO_WB_MODE,
	TV_GUI_VIDEO_BATTERY,
	TV_GUI_VIDEO_SCENE,
	TV_GUI_VIDEO_FLASH,
	TV_GUI_VIDEO_REC_STATE,
	TV_GUI_VIDEO_ZOOM_BAR,
	TV_GUI_VIDEO_EV,
	TV_GUI_VIDEO_REMAIN_TIME,
	TV_GUI_VIDEO_REC_TIME,
	TV_GUI_VIDEO_RTC_TIME,
	TV_GUI_VIDEO_LOCK_FILE,
	TV_GUI_VIDEO_LOCK_NUM,
	TV_GUI_VIDEO_MUTE,
	TV_GUI_VIDEO_REC_POINT,	
	TV_GUI_VIDEO_GPS_STATE,
	TV_GUI_VIDEO_VMD_STATE,	
	TV_GUI_VIDEO_WIFI,
	TV_GUI_VIDEO_WIFI_SWITCH,
    TV_GUI_VIDEO_GUI_LDWS_LINE,
    TV_GUI_VIDEO_GUI_FCWS_INFO,
    
	TV_GUI_VIDEO_MAX,
	TV_GUI_AUDIO_REC_TIME,
	TV_GUI_AUDIO_REC_POINT	

} TV_VIDEO_GUI_BLOCK;

typedef enum {

	TV_GUI_DSC_IMAGE_RES = 0,
	TV_GUI_DSC_UI_MODE,
	TV_GUI_DSC_SD_STATE,
	TV_GUI_DSC_WB_MODE,
	TV_GUI_DSC_BATTERY,
	TV_GUI_DSC_SCENE,
	TV_GUI_DSC_FLASH,
	TV_GUI_DSC_SELF_TIMER,
	TV_GUI_DSC_BURST,
	TV_GUI_DSC_ZOOM_BAR,
	TV_GUI_DSC_EV,
	TV_GUI_DSC_REMAIN_NUM,
	TV_GUI_DSC_RTC_TIME,
	TV_GUI_DSC_GPS_STATE,
	TV_GUI_DSC_VMD_STATE,	
	TV_GUI_DSC_MAX

} TV_DSC_GUI_BLOCK;

typedef enum {

	TV_GUI_MOVPB_STATUS = 0,
	TV_GUI_MOVPB_FILE_INDEX,
	TV_GUI_MOVPB_UI_MODE,
	TV_GUI_MOVPB_SD_STATE,
	TV_GUI_MOVPB_BATTERY,
	TV_GUI_MOVPB_VOL_BAR,
	TV_GUI_MOVPB_LOCK_FILE,
	TV_GUI_MOVPB_FILENAME,
	TV_GUI_MOVPB_CUR_TIME,
	TV_GUI_MOVPB_TOTAL_TIME,
	TV_GUI_MOVPB_MAX

} TV_MOVPB_GUI_BLOCK;

typedef enum {

	TV_GUI_AUDPB_STATUS = 0,
	TV_GUI_AUDPB_FILE_INDEX,
	TV_GUI_AUDPB_UI_MODE,
	TV_GUI_AUDPB_SD_STATE,
	TV_GUI_AUDPB_BATTERY,
	TV_GUI_AUDPB_VOL_BAR,
	TV_GUI_AUDPB_LOCK_FILE,
	TV_GUI_AUDPB_FILENAME,
	TV_GUI_AUDPB_CUR_TIME,
	TV_GUI_AUDPB_TOTAL_TIME,
	TV_GUI_AUDPB_MAX

} TV_AUDPB_GUI_BLOCK;

typedef enum {

	TV_GUI_JPGPB_FILE_INDEX = 0,
	TV_GUI_JPGPB_UI_MODE,
	TV_GUI_JPGPB_SD_STATE,
	TV_GUI_JPGPB_BATTERY,
	TV_GUI_JPGPB_LOCK_FILE,
	TV_GUI_JPGPB_FILENAME,
	TV_GUI_JPGPB_FILEDATE,	
	TV_GUI_JPGPB_MAX

} TV_JPGPB_GUI_BLOCK;

typedef enum {

	HDMI_GUI_VIDEO_MOVIE_RES = 0,
	HDMI_GUI_VIDEO_UI_MODE,
	HDMI_GUI_VIDEO_SD_STATE,
	HDMI_GUI_VIDEO_WB_MODE,
	HDMI_GUI_VIDEO_BATTERY,
	HDMI_GUI_VIDEO_SCENE,
	HDMI_GUI_VIDEO_FLASH,
	HDMI_GUI_VIDEO_REC_STATE,
	HDMI_GUI_VIDEO_ZOOM_BAR,
	HDMI_GUI_VIDEO_EV,
	HDMI_GUI_VIDEO_REMAIN_TIME,
	HDMI_GUI_VIDEO_REC_TIME,
	HDMI_GUI_VIDEO_RTC_TIME,
	HDMI_GUI_VIDEO_LOCK_FILE,
	HDMI_GUI_VIDEO_LOCK_NUM,
	HDMI_GUI_VIDEO_MUTE,
	HDMI_GUI_VIDEO_REC_POINT,	
	HDMI_GUI_VIDEO_GPS_STATE,
	HDMI_GUI_VIDEO_VMD_STATE,	
	HDMI_GUI_VIDEO_WIFI,
	HDMI_GUI_VIDEO_WIFI_SWITCH,
    HDMI_GUI_VIDEO_GUI_LDWS_LINE,
    HDMI_GUI_VIDEO_GUI_FCWS_INFO,
	HDMI_GUI_VIDEO_MAX,
	HDMI_GUI_AUDIO_REC_TIME,
	HDMI_GUI_AUDIO_REC_POINT	

} HDMI_VIDEO_GUI_BLOCK;

typedef enum {

	HDMI_GUI_DSC_IMAGE_RES = 0,
	HDMI_GUI_DSC_UI_MODE,
	HDMI_GUI_DSC_SD_STATE,
	HDMI_GUI_DSC_WB_MODE,
	HDMI_GUI_DSC_BATTERY,
	HDMI_GUI_DSC_SCENE,
	HDMI_GUI_DSC_FLASH,
	HDMI_GUI_DSC_SELF_TIMER,
	HDMI_GUI_DSC_BURST,
	HDMI_GUI_DSC_ZOOM_BAR,
	HDMI_GUI_DSC_EV,
	HDMI_GUI_DSC_REMAIN_NUM,
	HDMI_GUI_DSC_RTC_TIME,
	HDMI_GUI_DSC_GPS_STATE,
	HDMI_GUI_DSC_VMD_STATE,	
	HDMI_GUI_DSC_MAX

} HDMI_DSC_GUI_BLOCK;

typedef enum {

	HDMI_GUI_MOVPB_STATUS = 0,
	HDMI_GUI_MOVPB_FILE_INDEX,
	HDMI_GUI_MOVPB_UI_MODE,
	HDMI_GUI_MOVPB_SD_STATE,
	HDMI_GUI_MOVPB_BATTERY,
	HDMI_GUI_MOVPB_VOL_BAR,
	HDMI_GUI_MOVPB_LOCK_FILE,
	HDMI_GUI_MOVPB_FILENAME,
	HDMI_GUI_MOVPB_CUR_TIME,
	HDMI_GUI_MOVPB_TOTAL_TIME,
	HDMI_GUI_MOVPB_MAX

} HDMI_MOVPB_GUI_BLOCK;

typedef enum {

	HDMI_GUI_AUDPB_STATUS = 0,
	HDMI_GUI_AUDPB_FILE_INDEX,
	HDMI_GUI_AUDPB_UI_MODE,
	HDMI_GUI_AUDPB_SD_STATE,
	HDMI_GUI_AUDPB_BATTERY,
	HDMI_GUI_AUDPB_VOL_BAR,
	HDMI_GUI_AUDPB_LOCK_FILE,
	HDMI_GUI_AUDPB_FILENAME,
	HDMI_GUI_AUDPB_CUR_TIME,
	HDMI_GUI_AUDPB_TOTAL_TIME,
	HDMI_GUI_AUDPB_MAX

} HDMI_AUDPB_GUI_BLOCK;

typedef enum {

	HDMI_GUI_JPGPB_FILE_INDEX = 0,
	HDMI_GUI_JPGPB_UI_MODE,
	HDMI_GUI_JPGPB_SD_STATE,
	HDMI_GUI_JPGPB_BATTERY,
	HDMI_GUI_JPGPB_LOCK_FILE,
	HDMI_GUI_JPGPB_FILENAME,
	HDMI_GUI_JPGPB_FILEDATE,	
	HDMI_GUI_JPGPB_MAX

} HDMI_JPGPB_GUI_BLOCK;

/*===========================================================================
 * Extern variable
 *===========================================================================*/ 

extern UI_DARW_SET m_VideoDraw[];
extern UI_DARW_SET m_DSCDraw[];
extern UI_DARW_SET m_BrowserDraw[];
extern UI_DARW_SET m_MovPBDraw[];
extern UI_DARW_SET m_AudPBDraw[];
extern UI_DARW_SET m_JpgPBDraw[];
extern UI_DARW_SET m_SlideDraw[];
extern UI_DARW_SET m_TVVideoDraw[];
extern UI_DARW_SET m_TVDSCDraw[];
extern UI_DARW_SET m_TVMovPBDraw[];
extern UI_DARW_SET m_TVAudPBDraw[];
extern UI_DARW_SET m_TVJpgPBDraw[];
extern UI_DARW_SET m_HdmiMovPBDraw[];
extern UI_DARW_SET m_HdmiAudPBDraw[];
extern UI_DARW_SET m_HdmiJpgPBDraw[];

/*===========================================================================
 * Function Prototype
 *===========================================================================*/ 

void UIDrawVideoFuncEx(UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);
void UIDrawDSCFuncEx(UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);
void UIDrawBrowserFuncEx(UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);
void UIDrawMovPBFuncEx(UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);
void UIDrawAudPBFuncEx(UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);
void UIDrawJpgPBFuncEx(UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);
void UIDrawSlideFuncEx(UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);
void UIDrawTV_VideoFuncEx(UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);
void UIDrawTV_DSCFuncEx(UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);
void UIDrawTV_MovPBFuncEx(UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);
void UIDrawTV_AudPBFuncEx(UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);
void UIDrawTV_JpgPBFuncEx(UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);
void UIDrawHdmi_VideoFuncEx(UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);
void UIDrawHdmi_DSCFuncEx(UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);
void UIDrawHdmi_MovPBFuncEx(UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);
void UIDrawHdmi_AudPBFuncEx(UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);
void UIDrawHdmi_JpgPBFuncEx(UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);

#endif	// __UI_DRAW_GENERAL_H__
