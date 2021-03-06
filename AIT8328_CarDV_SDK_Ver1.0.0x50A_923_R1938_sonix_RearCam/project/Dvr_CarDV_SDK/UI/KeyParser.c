
/*===========================================================================
 * Include file
 *===========================================================================*/

#include "AHC_Common.h"
#include "AHC_General.h"
#include "AHC_Message.h"
#include "AHC_Os.h"
#include "AHC_Display.h"
#include "AHC_Audio.h"
#include "AHC_Capture.h"
#include "AHC_Dcf.h"
#include "AHC_Media.h"
#include "AHC_Video.h"
#include "AHC_GUI.h"
#include "AHC_Motor.h"
#include "AHC_Menu.h"
#include "AHC_USB.h"
#include "AHC_Parameter.h"
#include "AHC_General_CarDV.h"
#include "MenuCommon.h"
#include "MenuDrawingFunc.h"
#include "KeyParser.h"
#include "LedControl.h"
#include "IconPosition.h"
#include "dsc_charger.h"

#include "StateCameraFunc.h"
#include "StateVideoFunc.h"
#include "StateBrowserFunc.h"
#include "StateMoviePBFunc.h"
#include "StatePhotoPBFunc.h"
#include "StateSlideShowFunc.h"
#include "StateMSDCFunc.h"
#include "StateHDMIFunc.h"
#include "StateTVFunc.h"
#include "StateNetPlaybackFunc.h"

#if defined(WIFI_PORT) && (WIFI_PORT == 1)
#include "netapp.h"
#include "AHC_Stream.h"
#endif

/*===========================================================================
 * Extern varible
 *===========================================================================*/

extern AHC_BOOL PowerOff_InProcess;
extern AHC_BOOL Deleting_InBrowser;
extern AHC_BOOL Delete_File_Confirm;
extern AHC_BOOL Protecting_InBrowser;
extern AHC_BOOL Protect_File_Confirm;
extern AHC_BOOL UnProtect_File_Confirm;
extern AHC_BOOL bForceSwitchBrowser;
extern AHC_BOOL bForce_PowerOff;
extern UINT8	ssFileType;
extern AHC_BOOL PowerOff_Option;
extern AHC_BOOL bRefreshBrowser;
extern AHC_BOOL m_ubParkingModeRecTrigger;
extern AHC_BOOL gbAhcDbgBrk;
/*===========================================================================
 * Extern function
 *===========================================================================*/

extern AHC_BOOL VideoFunc_RecordStatus(void);
extern AHC_BOOL VideoFunc_GPSPageStatus(void);
extern AHC_BOOL HDMIFunc_IsPreview(void);
extern AHC_BOOL HDMIFunc_IsPlayback(void);
extern AHC_BOOL TVFunc_IsPreview(void);

/*===========================================================================
 * Main Body
 *===========================================================================*/

#if 0
void ________KeyEvent_Function_________(){ruturn;} //dummy
#endif

UINT32 KeyParser_VideoRecEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{
    if((ulEvent != BUTTON_UPDATE_MESSAGE)&&(ulEvent != BUTTON_UPDATE_CHARGE_ICON)&&(ulEvent != BUTTON_GPSGSENSOR_UPDATE)){
    //    printc("[Event:%x,%x,%x]\r\n",ulMsgId, ulEvent, ulParam);
    }

#if defined(WIFI_PORT) && (WIFI_PORT == 1)
    switch( ulMsgId )
    {
	case AHLM_WIRELESS_CONNECT:
        switch( ulEvent )
        {
        case WIRELESS_RECORD:
                    printc("=====> WIRELESS_RECORD\r\n");

            return EVENT_VIDEO_KEY_RECORD;

        case WIRELESS_CAPTURE:
                    printc("=====> WIRELESS_CAPTURE\r\n");
            return EVENT_VIDEO_KEY_CAPTURE;
    #ifdef NET_SYNC_PLAYBACK_MODE    
        case WIRELESS_ENTER_PLAYBACK:
                    printc("=====> WIRELESS_ENTER_PLAYBACK\r\n");
            return EVENT_NET_ENTER_PLAYBACK;
    #endif        
/*
        case WIRELESS_FORMAT_SD0:
            // TBD
            if (MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD)
            {
                if (!AHC_IsSDInserted() || AHC_IsSDWriteProtect())
                {
                    netapp_set_SD0Status(FORMAT_SD_ERROR);
                }
                else
                {
                    netapp_set_SD0Status(FORMAT_SD_DONE);
                }
            }
            break;
*/
        }
        break;
    }
#endif

    switch( ulEvent )
    {
 		case BUTTON_NONE		   :     return EVENT_NONE;
#if (SUPPORT_TOUCH_PANEL)
 		case BUTTON_TOUCH_PRESS    :     return AhcCheckTouchButton( &ulParam,  AHC_FALSE );
 		case BUTTON_TOUCH_MOVE     :     return AhcCheckTouchButton( &ulParam,  AHC_TRUE);
#endif

#if (VIDEO_DIGIT_ZOOM_EN) // Video Recording With Zoom Test
 		case BUTTON_UP_LPRESS	   :
 		case BUTTON_UP_PRESS	   :	 return EVENT_KEY_TELE_PRESS;
 		case BUTTON_UP_LREL		   :
 		case BUTTON_UP_REL		   :	 return EVENT_KEY_TELE_STOP;

 		case BUTTON_DOWN_LPRESS    :
 		case BUTTON_DOWN_PRESS 	   :	 return EVENT_KEY_WIDE_PRESS;
 		case BUTTON_DOWN_LREL 	   :
 		case BUTTON_DOWN_REL 	   :	 return EVENT_KEY_WIDE_STOP;
#endif

 		case BUTTON_SOS_REL	       :	 return (VideoFunc_RecordStatus())?(EVENT_LOCK_VR_FILE):(EVENT_SWITCH_VMD_MODE);
 		case BUTTON_SOS_LPRESS     :	 return EVENT_WIFI_SWITCH_TOGGLE;

  		//GPIO Key
        case BUTTON_SET_PRESS      :	 return EVENT_KEY_SET;

		// Link with KEY_VIDEO_RECORD
  		case BUTTON_REC_REL        :	 return EVENT_VIDEO_KEY_RECORD;
		// Link with KEY_VIDEO_CAPTURE
  		case BUTTON_REC_LPRESS     :   	 return EVENT_VIDEO_KEY_CAPTURE;

		case BUTTON_MENU_REL	   :	 return (VideoFunc_RecordStatus()||uiGetParkingModeEnable())?(EVENT_NONE):(EVENT_KEY_MENU);
		case BUTTON_MENU_LPRESS	   :	 return (VideoFunc_RecordStatus())?(EVENT_NONE):((SUPPORT_PARKINGMODE == PARKINGMODE_NONE) ? EVENT_NONE : EVENT_PARKING_KEY);
        
		case BUTTON_MODE_REL	   :     return (VideoFunc_RecordStatus())?(EVENT_LOCK_VR_FILE):(EVENT_KEY_MODE);
		case BUTTON_MODE_LPRESS	   :     return EVENT_SWITCH_WIFI_STREAMING_MODE;
 		case BUTTON_MUTE_REL       :	 return EVENT_RECORD_MUTE;
 		case BUTTON_MUTE_LPRESS    :	 return EVENT_LCD_POWER_SAVE;
 		case BUTTON_POWER_LPRESS   :	 return EVENT_POWER_OFF;
		case BUTTON_POWER_REL      :     return EVENT_SHOW_GPS_INFO;

        //Device
        case BUTTON_USB_DETECTED   :     return EVENT_USB_DETECT;
        case BUTTON_USB_REMOVED    :     return EVENT_USB_REMOVED;
        case BUTTON_USB_B_DEVICE_DETECTED   : return EVENT_USB_B_DEVICE_DETECT;
        case BUTTON_USB_B_DEVICE_REMOVED    : return EVENT_USB_B_DEVICE_REMOVED;

        case BUTTON_SD_DETECTED    :     return EVENT_SD_DETECT;
        case BUTTON_SD_REMOVED     :     return EVENT_SD_REMOVED;
        case BUTTON_TV_DETECTED    :     return EVENT_TV_DETECT;
        case BUTTON_TV_REMOVED     :     return EVENT_TV_REMOVED;
        case BUTTON_HDMI_DETECTED  :     return EVENT_HDMI_DETECT;
        case BUTTON_HDMI_REMOVED   :     return EVENT_HDMI_REMOVED;
        case BUTTON_DC_CABLE_IN    :	 return EVENT_DC_CABLE_IN;
        case BUTTON_DC_CABLE_OUT   :	 return EVENT_DC_CABLE_OUT;
        
        case BUTTON_CUS_SW1_ON     :	 return EVENT_CUS_SW1_ON;
        case BUTTON_CUS_SW1_OFF    :	 return EVENT_CUS_SW1_OFF;

        case BUTTON_LCD_NORMAL     :     return EVENT_LCD_COVER_NORMAL;
        case BUTTON_LCD_ROTATE     :     return EVENT_LCD_COVER_ROTATE;
        case BUTTON_COVER_OPEN     :     return EVENT_LCD_COVER_OPEN;
        case BUTTON_COVER_CLOSED   :     return EVENT_LCD_COVER_CLOSE;

        #if (EMERGENCY_RECODE_FLOW_TYPE == EMERGENCY_RECODE_SWITCH_FILE)
        case BUTTON_LOCK_FILE_G    :     return EVENT_VR_EMERGENT;
        #else
        case BUTTON_LOCK_FILE_G    :     return EVENT_LOCK_FILE_G;
        #endif

        //Update Message
        case BUTTON_UPDATE_FILE    :     //return EVENT_SLIDESHOW_UPDATE_FILE;
        case BUTTON_BATTERY_DETECTION:
        case BUTTON_UPDATE_MESSAGE :     return EVENT_VIDREC_UPDATE_MESSAGE;
        case BUTTON_GPSGSENSOR_UPDATE :  return EVENT_GPSGSENSOR_UPDATE;

        //Record Callback
        case BUTTON_VRCB_MEDIA_FULL:     return EVENT_VRCB_MEDIA_FULL;
        case BUTTON_VRCB_FILE_FULL :     return EVENT_VRCB_FILE_FULL;
        case BUTTON_VRCB_LONG_TIME_FILE_FULL : 	return EVENT_VRCB_LONG_TIME_FILE_FULL;
        case BUTTON_VRCB_MEDIA_SLOW:     return EVENT_VRCB_MEDIA_SLOW;
        case BUTTON_VRCB_MEDIA_ERROR:    return EVENT_VRCB_MEDIA_ERROR;
        case BUTTON_VRCB_SEAM_LESS :     return EVENT_VRCB_SEAM_LESS;
        case BUTTON_VRCB_MOTION_DTC:     return EVENT_VRCB_MOTION_DTC;
        case BUTTON_VRCB_VR_START  :	 return EVENT_VR_START;
        case BUTTON_VRCB_VR_STOP   :	 return EVENT_VR_STOP;
        case BUTTON_VRCB_VR_POSTPROC:    return EVENT_VR_WRITEINFO;
        case BUTTON_VRCB_EMER_DONE	:	 return EVENT_VRCB_EMER_DONE;
        case BUTTON_CLEAR_WMSG     :     return EVENT_CLEAR_WMSG;
        case BUTTON_VRCB_RECDSTOP_CARDSLOW:     return EVENT_VRCB_RECDSTOP_CARDSLOW;

		#if (POWER_ON_BUTTON_ACTION)
		case BUTTON_POWER_ON_MENU  :     return EVENT_SHOW_FW_VERSION;
		case BUTTON_POWER_ON_MODE  :	 return EVENT_FORMAT_RESET_ALL;
		case BUTTON_POWER_ON_REC   :	 return EVENT_NONE;
		case BUTTON_POWER_ON_PLAY  :     return EVENT_NONE;
		#endif
        case BUTTON_LDWS_START:
            #if (ENABLE_ADAS_LDWS)
            return EVENT_LDWS_START;
            #else
            return EVENT_NONE;
            #endif
        case BUTTON_LDWS_STOP:
            #if (ENABLE_ADAS_LDWS)
            return EVENT_LDWS_STOP;
            #else
            return EVENT_NONE;
            #endif
        case BUTTON_FCWS_START:
            #if (ENABLE_ADAS_FCWS)
            return EVENT_FCWS_START;
            #else
            return EVENT_NONE;
            #endif
        case BUTTON_FCWS_STOP:
            #if (ENABLE_ADAS_FCWS)
            return EVENT_FCWS_STOP;
            #else
            return EVENT_NONE;
            #endif
    #if (UVC_HOST_VIDEO_ENABLE || SUPPORT_DUAL_SNR)
		case BUTTON_FUNC1_PRESS     :
		    return EVENT_VIDEO_KEY_SWAP_PIP;
        break;
    #endif
#if (SUPPORT_DUAL_SNR == 1 && DUALENC_SUPPORT == 1) //For Bitek1603
        case BUTTON_TV_DECODER_SRC_TYPE   : return EVENT_TV_DECODER_SRC_TYPE;
#endif
		default                    :     return EVENT_NONE;
    }
}

UINT32 KeyParser_CaptureEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{
#if defined(WIFI_PORT) && (WIFI_PORT == 1)
    switch( ulMsgId )
    {
	case AHLM_WIRELESS_CONNECT:
        switch( ulEvent )
        {
        case WIRELESS_RECORD:
        case WIRELESS_CAPTURE:
            return EVENT_DSC_KEY_CAPTURE;
    #ifdef NET_SYNC_PLAYBACK_MODE
        case WIRELESS_ENTER_PLAYBACK:
            printc("=====> WIRELESS_ENTER_PLAYBACK\r\n");
            return EVENT_NET_ENTER_PLAYBACK;
        
    #endif
    	}
        break;
    }
#endif

    switch( ulEvent )
    {
        case BUTTON_NONE		   :     return EVENT_NONE;
#if (SUPPORT_TOUCH_PANEL)
        case BUTTON_TOUCH_PRESS    :     return AhcCheckTouchButton( &ulParam,  AHC_FALSE );
        case BUTTON_TOUCH_MOVE     :     return AhcCheckTouchButton( &ulParam,  AHC_TRUE);
#endif

#if (DSC_DIGIT_ZOOM_ENABLE)
 		case BUTTON_UP_PRESS	   :	 return EVENT_KEY_TELE_PRESS;
 		case BUTTON_DOWN_PRESS     :	 return EVENT_KEY_WIDE_PRESS;
 		case BUTTON_UP_REL         :     return EVENT_KEY_TELE_STOP;
        case BUTTON_DOWN_REL       :     return EVENT_KEY_WIDE_STOP;
#else
 		case BUTTON_UP_PRESS	   :	 return EVENT_NONE;
 		case BUTTON_DOWN_PRESS     :	 return EVENT_NONE;
 		case BUTTON_UP_REL         :     return EVENT_NONE;
        case BUTTON_DOWN_REL       :     return EVENT_NONE;
#endif
		// Link with KEY_DSC_CAPTURE
  		case BUTTON_REC_REL        :     return EVENT_DSC_KEY_CAPTURE;

		case BUTTON_MENU_REL       :     return EVENT_KEY_MENU;
		case BUTTON_MODE_REL	   :     return EVENT_KEY_MODE;
// 		case BUTTON_MUTE_REL       :	 return EVENT_NONE;
// 		case BUTTON_MUTE_LPRESS    :	 return EVENT_LCD_POWER_SAVE;
 		case BUTTON_POWER_LPRESS   :	 return EVENT_POWER_OFF;

 		case BUTTON_SOS_REL        :	 return EVENT_SWITCH_VMD_MODE;
 		case BUTTON_SOS_LPRESS     :	 return EVENT_SWITCH_TIME_LAPSE_EN;

 		case BUTTON_SET_PRESS      :	 return EVENT_DSC_KEY_CHANGE_SHOT_MODE;

		//Device
        case BUTTON_USB_DETECTED   :     return EVENT_USB_DETECT;
        case BUTTON_USB_REMOVED    :     return EVENT_USB_REMOVED;
        case BUTTON_USB_B_DEVICE_DETECTED   : return EVENT_USB_B_DEVICE_DETECT;
        case BUTTON_USB_B_DEVICE_REMOVED    : return EVENT_USB_B_DEVICE_REMOVED;
        case BUTTON_SD_DETECTED    :     return EVENT_SD_DETECT;
        case BUTTON_SD_REMOVED     :     return EVENT_SD_REMOVED;
        case BUTTON_TV_DETECTED    :     return EVENT_TV_DETECT;
        case BUTTON_TV_REMOVED     :     return EVENT_TV_REMOVED;
        case BUTTON_HDMI_DETECTED  :     return EVENT_HDMI_DETECT;
        case BUTTON_HDMI_REMOVED   :     return EVENT_HDMI_REMOVED;
        case BUTTON_DC_CABLE_IN    :	 return EVENT_DC_CABLE_IN;
        case BUTTON_DC_CABLE_OUT   :	 return EVENT_DC_CABLE_OUT;

        case BUTTON_LCD_NORMAL     :     return EVENT_LCD_COVER_NORMAL;
        case BUTTON_LCD_ROTATE     :     return EVENT_LCD_COVER_ROTATE;
        case BUTTON_COVER_OPEN     :     return EVENT_LCD_COVER_OPEN;
        case BUTTON_COVER_CLOSED   :     return EVENT_LCD_COVER_CLOSE;

        //Callback
        case BUTTON_VRCB_MOTION_DTC:     return EVENT_VRCB_MOTION_DTC;

        //Update Message
		case BUTTON_BATTERY_DETECTION:
        case BUTTON_UPDATE_MESSAGE :     return EVENT_DSC_KEY_UPDATE_MESSAGE;
        case BUTTON_CLEAR_WMSG     :     return EVENT_CLEAR_WMSG;
#if (SUPPORT_DUAL_SNR == 1 && DUALENC_SUPPORT == 1) //For Bitek1603
        case BUTTON_TV_DECODER_SRC_TYPE   : return EVENT_TV_DECODER_SRC_TYPE;
#endif        
        default                    :     return EVENT_NONE;
    }
}

UINT32 KeyParser_ThumbnailEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{
	
#if defined(WIFI_PORT) && (WIFI_PORT == 1)
    switch( ulMsgId )
    {
	case AHLM_WIRELESS_CONNECT:
        switch( ulEvent )
        {
    	#ifdef NET_SYNC_PLAYBACK_MODE    
        case WIRELESS_ENTER_PLAYBACK:
            printc("=====> WIRELESS_ENTER_PLAYBACK\r\n");
            return EVENT_NET_ENTER_PLAYBACK;
    	#endif   
    	break;     
        }
    break;
    }
#endif

    switch( ulEvent )
    {
        case BUTTON_NONE		   :     return EVENT_NONE;
#if (SUPPORT_TOUCH_PANEL)
        case BUTTON_TOUCH_PRESS    :     return AhcCheckTouchButton( &ulParam,  AHC_FALSE );
        case BUTTON_TOUCH_MOVE     :     return AhcCheckTouchButton( &ulParam,  AHC_TRUE);
#endif

#if (DIR_KEY_TYPE == KEY_TYPE_4KEY)
 		case BUTTON_UP_LPRESS	   :	 return EVENT_KEY_UP;
 		case BUTTON_UP_PRESS	   :	 return EVENT_KEY_UP;
 		case BUTTON_DOWN_LPRESS	   :	 return EVENT_KEY_DOWN;
 		case BUTTON_DOWN_PRESS 	   :	 return EVENT_KEY_DOWN;
#else
 		case BUTTON_UP_LPRESS	   :	 return EVENT_KEY_LEFT;
 		case BUTTON_UP_PRESS	   :	 return EVENT_KEY_LEFT;
 		case BUTTON_DOWN_LPRESS	   :	 return EVENT_KEY_RIGHT;
 		case BUTTON_DOWN_PRESS 	   :	 return EVENT_KEY_RIGHT;
#endif

 		case BUTTON_LEFT_LPRESS	   :	 return EVENT_KEY_LEFT;
 		case BUTTON_LEFT_PRESS	   :	 return EVENT_KEY_LEFT;
 		case BUTTON_RIGHT_LPRESS   :	 return EVENT_KEY_RIGHT;
 		case BUTTON_RIGHT_PRESS	   :	 return EVENT_KEY_RIGHT;

  		//GPIO Key
  		case BUTTON_REC_PRESS      :     return EVENT_THUMBNAIL_KEY_PLAYBACK;
  		case BUTTON_SET_PRESS      :     return EVENT_THUMBNAIL_KEY_PLAYBACK;
		case BUTTON_MENU_REL	   :	 return EVENT_KEY_MENU;
  		case BUTTON_MENU_LPRESS    :	 return EVENT_MOVPB_MODE;
		case BUTTON_MODE_REL	   :     return EVENT_KEY_MODE;
 		case BUTTON_MODE_LPRESS    :	 return EVENT_NONE;
 		case BUTTON_MUTE_REL       :	 return EVENT_NONE;
 		case BUTTON_MUTE_LPRESS    :	 return EVENT_NONE;
 		case BUTTON_POWER_LPRESS   :	 return EVENT_POWER_OFF;

		//Device
        case BUTTON_USB_DETECTED   :     return EVENT_USB_DETECT;
        case BUTTON_USB_REMOVED    :     return EVENT_USB_REMOVED;
        case BUTTON_USB_B_DEVICE_DETECTED   : return EVENT_USB_B_DEVICE_DETECT;
        case BUTTON_USB_B_DEVICE_REMOVED    : return EVENT_USB_B_DEVICE_REMOVED;
        case BUTTON_SD_DETECTED    :     return EVENT_SD_DETECT;
        case BUTTON_SD_REMOVED     :     return EVENT_SD_REMOVED;
        case BUTTON_TV_DETECTED    :     return EVENT_TV_DETECT;
        case BUTTON_TV_REMOVED     :     return EVENT_TV_REMOVED;
        case BUTTON_HDMI_DETECTED  :     return EVENT_HDMI_DETECT;
        case BUTTON_HDMI_REMOVED   :     return EVENT_HDMI_REMOVED;
        case BUTTON_DC_CABLE_IN    :	 return EVENT_DC_CABLE_IN;
        case BUTTON_DC_CABLE_OUT   :	 return EVENT_DC_CABLE_OUT;

        case BUTTON_LCD_NORMAL     :     return EVENT_LCD_COVER_NORMAL;
        case BUTTON_LCD_ROTATE     :     return EVENT_LCD_COVER_ROTATE;
        case BUTTON_COVER_OPEN     :     return EVENT_LCD_COVER_OPEN;
        case BUTTON_COVER_CLOSED   :     return EVENT_LCD_COVER_CLOSE;

        //Update Message
        case BUTTON_UPDATE_FILE    :     return EVENT_SLIDESHOW_UPDATE_FILE;
        case BUTTON_BATTERY_DETECTION:
        case BUTTON_UPDATE_MESSAGE :     return EVENT_THUMBNAIL_UPDATE_MESSAGE;
        case BUTTON_CLEAR_WMSG     :     return EVENT_CLEAR_WMSG;
#if (SUPPORT_DUAL_SNR == 1 && DUALENC_SUPPORT == 1) //For Bitek1603
        case BUTTON_TV_DECODER_SRC_TYPE   : return EVENT_TV_DECODER_SRC_TYPE;
#endif        
        default                    :     return EVENT_NONE;
    }
}

UINT32 KeyParser_JpgPlaybackEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{
#if defined(WIFI_PORT) && (WIFI_PORT == 1)
    switch( ulMsgId )
    {
	case AHLM_WIRELESS_CONNECT:
        switch( ulEvent )
        {
    	#ifdef NET_SYNC_PLAYBACK_MODE    
        case WIRELESS_ENTER_PLAYBACK:
            printc("=====> WIRELESS_ENTER_PLAYBACK\r\n");
            return EVENT_NET_ENTER_PLAYBACK;
        break;
    	#endif        
        }
        break;
    }
#endif

    switch( ulEvent )
    {
        case BUTTON_NONE		   :     return EVENT_NONE;
#if (SUPPORT_TOUCH_PANEL)
        case BUTTON_TOUCH_PRESS    :     return AhcCheckTouchButton( &ulParam,  AHC_FALSE );
        case BUTTON_TOUCH_MOVE     :     return AhcCheckTouchButton( &ulParam,  AHC_TRUE);
#endif

 		case BUTTON_UP_PRESS	   :	 return EVENT_JPGPB_TOUCH_PREV_PRESS;
 		case BUTTON_DOWN_PRESS 	   :	 return EVENT_JPGPB_TOUCH_NEXT_PRESS;
		//case BUTTON_LEFT_PRESS   :	 return EVENT_KEY_UP;
		//case BUTTON_RIGHT_PRESS  :	 return EVENT_KEY_DOWN;
		
  		//GPIO Key
  		case BUTTON_REC_PRESS      :     return EVENT_NONE;
		case BUTTON_MENU_REL	   :	 return EVENT_KEY_MENU;
  		case BUTTON_MENU_LPRESS    :	 return EVENT_NONE;
		case BUTTON_MODE_REL	   :     return EVENT_JPGPB_TOUCH_RETURN;
		case BUTTON_MODE_LPRESS    :	 return EVENT_NONE;
 		case BUTTON_MUTE_REL       :	 return EVENT_NONE;
 		case BUTTON_MUTE_LPRESS    :	 return EVENT_NONE;
 		case BUTTON_POWER_LPRESS   :	 return EVENT_POWER_OFF;

		//Device
        case BUTTON_USB_DETECTED   :     return EVENT_USB_DETECT;
        case BUTTON_USB_REMOVED    :     return EVENT_USB_REMOVED;
        case BUTTON_USB_B_DEVICE_DETECTED   : return EVENT_USB_B_DEVICE_DETECT;
        case BUTTON_USB_B_DEVICE_REMOVED    : return EVENT_USB_B_DEVICE_REMOVED;
        case BUTTON_SD_DETECTED    :     return EVENT_SD_DETECT;
        case BUTTON_SD_REMOVED     :     return EVENT_SD_REMOVED;
        case BUTTON_TV_DETECTED    :     return EVENT_TV_DETECT;
        case BUTTON_TV_REMOVED     :     return EVENT_TV_REMOVED;
        case BUTTON_HDMI_DETECTED  :     return EVENT_HDMI_DETECT;
		case BUTTON_HDMI_REMOVED   :     return EVENT_NONE;
        case BUTTON_DC_CABLE_IN    :	 return EVENT_DC_CABLE_IN;
        case BUTTON_DC_CABLE_OUT   :	 return EVENT_DC_CABLE_OUT;

        case BUTTON_LCD_NORMAL     :     return EVENT_LCD_COVER_NORMAL;
        case BUTTON_LCD_ROTATE     :     return EVENT_LCD_COVER_ROTATE;
        case BUTTON_COVER_OPEN     :     return EVENT_LCD_COVER_OPEN;
        case BUTTON_COVER_CLOSED   :     return EVENT_LCD_COVER_CLOSE;

        //Update Message
        case BUTTON_BATTERY_DETECTION:
        case BUTTON_UPDATE_MESSAGE :     return EVENT_JPGPB_UPDATE_MESSAGE;
        case BUTTON_CLEAR_WMSG     :     return EVENT_CLEAR_WMSG;
#if (SUPPORT_DUAL_SNR == 1 && DUALENC_SUPPORT == 1) //For Bitek1603
        case BUTTON_TV_DECODER_SRC_TYPE   : return EVENT_TV_DECODER_SRC_TYPE;
#endif        
        default                    :     return EVENT_NONE;
    }
}

UINT32 KeyParser_MovPlaybackEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{
	
#if defined(WIFI_PORT) && (WIFI_PORT == 1)
    switch( ulMsgId )
    {
	case AHLM_WIRELESS_CONNECT:
        switch( ulEvent )
        {
    	#ifdef NET_SYNC_PLAYBACK_MODE    
        case WIRELESS_ENTER_PLAYBACK:
            printc("=====> WIRELESS_ENTER_PLAYBACK\r\n");
            return EVENT_NET_ENTER_PLAYBACK;
    	#endif        
        }
        break;
    }
#endif

    switch( ulEvent )
    {
        case BUTTON_NONE		   :     return EVENT_NONE;
#if (SUPPORT_TOUCH_PANEL)
        case BUTTON_TOUCH_PRESS    :     return AhcCheckTouchButton( &ulParam,  AHC_FALSE );
        case BUTTON_TOUCH_MOVE     :     return AhcCheckTouchButton( &ulParam,  AHC_TRUE);
#endif

 		case BUTTON_UP_PRESS	   :	 return EVENT_MOVPB_TOUCH_BKWD_PRESS;
 		case BUTTON_DOWN_PRESS 	   :	 return EVENT_MOVPB_TOUCH_FRWD_PRESS;

  		//GPIO Key
  		case BUTTON_REC_PRESS      :     return EVENT_MOVPB_TOUCH_PLAY_PRESS;
  		case BUTTON_SET_PRESS      :     return EVENT_MOVPB_TOUCH_PLAY_PRESS;
		case BUTTON_MENU_REL	   :	 return EVENT_KEY_MENU;
        case BUTTON_MENU_LPRESS    :	 return EVENT_MOVPB_MODE;
		case BUTTON_MODE_REL	   :     return EVENT_MOVPB_TOUCH_RETURN;
  		case BUTTON_MODE_LPRESS    :	 return EVENT_NONE;
 		case BUTTON_MUTE_REL       :	 return EVENT_NONE;
 		case BUTTON_MUTE_LPRESS    :	 return EVENT_NONE;
 		case BUTTON_POWER_LPRESS   :	 return EVENT_POWER_OFF;

		//Device
        case BUTTON_USB_DETECTED   :     return EVENT_USB_DETECT;
        case BUTTON_USB_REMOVED    :     return EVENT_USB_REMOVED;
        case BUTTON_USB_B_DEVICE_DETECTED   : return EVENT_USB_B_DEVICE_DETECT;
        case BUTTON_USB_B_DEVICE_REMOVED    : return EVENT_USB_B_DEVICE_REMOVED;
        case BUTTON_SD_DETECTED    :     return EVENT_SD_DETECT;
        case BUTTON_SD_REMOVED     :     return EVENT_SD_REMOVED;
        case BUTTON_TV_DETECTED    :     return EVENT_TV_DETECT;
        case BUTTON_TV_REMOVED     :     return EVENT_TV_REMOVED;
		case BUTTON_HDMI_DETECTED  :     return EVENT_HDMI_DETECT;
        case BUTTON_HDMI_REMOVED   :     return EVENT_NONE;
        case BUTTON_DC_CABLE_IN    :	 return EVENT_DC_CABLE_IN;
        case BUTTON_DC_CABLE_OUT   :	 return EVENT_DC_CABLE_OUT;

        case BUTTON_LCD_NORMAL     :     return EVENT_LCD_COVER_NORMAL;
        case BUTTON_LCD_ROTATE     :     return EVENT_LCD_COVER_ROTATE;
        case BUTTON_COVER_OPEN     :     return EVENT_LCD_COVER_OPEN;
        case BUTTON_COVER_CLOSED   :     return EVENT_LCD_COVER_CLOSE;

        //Update Message
        case BUTTON_BATTERY_DETECTION:
        case BUTTON_UPDATE_MESSAGE :     return EVENT_MOVPB_UPDATE_MESSAGE;
        case BUTTON_CLEAR_WMSG     :     return EVENT_CLEAR_WMSG;
        case BUTTON_OSD_HIDE       :     return EVENT_SLIDESHOW_OSD_HIDE;
#if (SUPPORT_DUAL_SNR == 1 && DUALENC_SUPPORT == 1) //For Bitek1603
        case BUTTON_TV_DECODER_SRC_TYPE   : return EVENT_TV_DECODER_SRC_TYPE;
#endif        
        default                    :     return EVENT_NONE;
    }
}

UINT32 KeyParser_AudPlaybackEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{
#if (AUDIO_REC_PLAY_EN)

	UINT32 LCDstatus;

	AHC_GetParam(PARAM_ID_LCD_STATUS,&LCDstatus);

    switch( ulEvent )
    {
    	
    #if defined(WIFI_PORT) && (WIFI_PORT == 1)
		case AHLM_WIRELESS_CONNECT:
        switch( ulEvent )
        {
    	#ifdef NET_SYNC_PLAYBACK_MODE    
        	case WIRELESS_ENTER_PLAYBACK:
            printc("=====> WIRELESS_ENTER_PLAYBACK\r\n");
            return EVENT_NET_ENTER_PLAYBACK;
    	#endif        
    	}
    	break;
    #endif
    
        case BUTTON_NONE		   :     return EVENT_NONE;

		//ADC Key
 		case BUTTON_UP_PRESS	   :	 return EVENT_KEY_UP;
 		case BUTTON_DOWN_PRESS 	   :	 return EVENT_KEY_DOWN;
 		case BUTTON_UP_REL 	   	   :	 return EVENT_KEY_TELE_STOP;
		case BUTTON_DOWN_REL 	   :	 return EVENT_KEY_WIDE_STOP;
 		case BUTTON_LEFT_PRESS     :     return EVENT_MOVPB_TOUCH_BKWD_PRESS;
        case BUTTON_RIGHT_PRESS    :     return EVENT_MOVPB_TOUCH_FRWD_PRESS;
  		case BUTTON_SET_PRESS      :     return EVENT_MOVPB_TOUCH_PLAY_PRESS;

  		//GPIO Key
		case BUTTON_MENU_REL	   :	 return EVENT_KEY_MENU;
		case BUTTON_MODE_REL	   :     return EVENT_NONE;
 		case BUTTON_REC_REL	       :     return EVENT_MOVPB_TOUCH_RETURN;
 		case BUTTON_POWER_LPRESS   :	 return EVENT_POWER_OFF;

		//Device
        case BUTTON_USB_DETECTED   :     return EVENT_USB_DETECT;
        case BUTTON_USB_REMOVED    :     return EVENT_USB_REMOVED;
        case BUTTON_USB_B_DEVICE_DETECTED   : return EVENT_USB_B_DEVICE_DETECT;
        case BUTTON_USB_B_DEVICE_REMOVED    : return EVENT_USB_B_DEVICE_REMOVED;
        case BUTTON_SD_DETECTED    :     return EVENT_SD_DETECT;
        case BUTTON_SD_REMOVED     :     return EVENT_SD_REMOVED;
        case BUTTON_TV_DETECTED    :     return EVENT_TV_DETECT;
        case BUTTON_TV_REMOVED     :     return EVENT_TV_REMOVED;
		case BUTTON_HDMI_DETECTED  :     return EVENT_HDMI_DETECT;
        case BUTTON_HDMI_REMOVED   :     return EVENT_NONE;
        case BUTTON_DC_CABLE_IN    :	 return EVENT_DC_CABLE_IN;
        case BUTTON_DC_CABLE_OUT   :	 return EVENT_DC_CABLE_OUT;

        case BUTTON_LCD_NORMAL     :     return EVENT_LCD_COVER_NORMAL;
        case BUTTON_LCD_ROTATE     :     return EVENT_LCD_COVER_ROTATE;
        case BUTTON_COVER_OPEN     :     return EVENT_LCD_COVER_OPEN;
        case BUTTON_COVER_CLOSED   :     return EVENT_LCD_COVER_CLOSE;

        //Update Message
        case BUTTON_BATTERY_DETECTION:
        case BUTTON_UPDATE_MESSAGE :     return EVENT_MOVPB_UPDATE_MESSAGE;
        case BUTTON_CLEAR_WMSG     :     return EVENT_CLEAR_WMSG;
#if (SUPPORT_DUAL_SNR == 1 && DUALENC_SUPPORT == 1) //For Bitek1603
        case BUTTON_TV_DECODER_SRC_TYPE   : return EVENT_TV_DECODER_SRC_TYPE;
#endif        
        default                    :     return EVENT_NONE;
    }
#endif

    return EVENT_NONE;
}

UINT32 KeyParser_SlideShowEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{
	
#if defined(WIFI_PORT) && (WIFI_PORT == 1)
    switch( ulMsgId )
    {
	case AHLM_WIRELESS_CONNECT:
        switch( ulEvent )
        {
    	#ifdef NET_SYNC_PLAYBACK_MODE    
        case WIRELESS_ENTER_PLAYBACK:
            printc("=====> WIRELESS_ENTER_PLAYBACK\r\n");
            return EVENT_NET_ENTER_PLAYBACK;
    	#endif        
        }
        break;
    }
#endif

#if (SLIDESHOW_EN)

    switch( ulEvent )
    {
        case BUTTON_NONE           :     return EVENT_NONE;

        //ADC Key
 		case BUTTON_UP_PRESS	   :	 return EVENT_SLIDESHOW_TOUCH_PREV_PRESS;
 		case BUTTON_DOWN_PRESS 	   :	 return EVENT_SLIDESHOW_TOUCH_NEXT_PRESS;

  		//GPIO Key
  		case BUTTON_REC_PRESS      :     return EVENT_SLIDESHOW_TOUCH_PLAY_PRESS;
		case BUTTON_MENU_REL	   :	 return EVENT_KEY_MENU;
  		case BUTTON_MENU_LPRESS    :	 return EVENT_NONE;
		case BUTTON_MODE_REL	   :     return EVENT_SLIDESHOW_TOUCH_RETURN;
  		case BUTTON_MODE_LPRESS    :	 return EVENT_NONE;
 		case BUTTON_MUTE_REL       :	 return EVENT_NONE;
 		case BUTTON_MUTE_LPRESS    :	 return EVENT_NONE;
 		case BUTTON_POWER_LPRESS   :	 return EVENT_POWER_OFF;

		//Device
        case BUTTON_USB_DETECTED   :     return EVENT_USB_DETECT;
        case BUTTON_USB_REMOVED    :     return EVENT_USB_REMOVED;
        case BUTTON_USB_B_DEVICE_DETECTED   : return EVENT_USB_B_DEVICE_DETECT;
        case BUTTON_USB_B_DEVICE_REMOVED    : return EVENT_USB_B_DEVICE_REMOVED;
        case BUTTON_SD_DETECTED    :     return EVENT_SD_DETECT;
        case BUTTON_SD_REMOVED     :     return EVENT_SD_REMOVED;
        case BUTTON_TV_DETECTED    :     return EVENT_TV_DETECT;
        case BUTTON_TV_REMOVED     :     return EVENT_TV_REMOVED;
        case BUTTON_HDMI_DETECTED  :     return EVENT_HDMI_DETECT;
        case BUTTON_HDMI_REMOVED   :     return EVENT_NONE;
        case BUTTON_DC_CABLE_IN    :	 return EVENT_DC_CABLE_IN;
        case BUTTON_DC_CABLE_OUT   :	 return EVENT_DC_CABLE_OUT;

        case BUTTON_LCD_NORMAL     :     return EVENT_LCD_COVER_NORMAL;
        case BUTTON_LCD_ROTATE     :     return EVENT_LCD_COVER_ROTATE;
        case BUTTON_COVER_OPEN     :     return EVENT_LCD_COVER_OPEN;
        case BUTTON_COVER_CLOSED   :     return EVENT_LCD_COVER_CLOSE;

        //Update Message
        case BUTTON_OSD_HIDE       :     return EVENT_SLIDESHOW_OSD_HIDE;
        case BUTTON_UPDATE_FILE    :     return EVENT_SLIDESHOW_UPDATE_FILE;
        case BUTTON_BATTERY_DETECTION:
        case BUTTON_UPDATE_MESSAGE :     return EVENT_SLIDESHOW_UPDATE_MESSAGE;
        case BUTTON_CLEAR_WMSG     :     return EVENT_CLEAR_WMSG;
#if (SUPPORT_DUAL_SNR == 1 && DUALENC_SUPPORT == 1) //For Bitek1603
        case BUTTON_TV_DECODER_SRC_TYPE   : return EVENT_TV_DECODER_SRC_TYPE;
#endif        
        default                    :     return EVENT_NONE;
    }
#endif

	return EVENT_NONE;
}

UINT32 KeyParser_HdmiEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{
#if defined(WIFI_PORT) && (WIFI_PORT == 1)
    switch( ulMsgId )
    {
	case AHLM_WIRELESS_CONNECT:
        switch( ulEvent )
        {
        case WIRELESS_RECORD:
            printc("@@@ WIRELESS_RECORD -\r\n");
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				return EVENT_VIDEO_KEY_RECORD;
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
				return EVENT_DSC_KEY_CAPTURE;
				break;

			default:
				return EVENT_NONE;
				break;
			}
			break;

        case WIRELESS_CAPTURE:
            printc("@@@ WIRELESS_CAPTURE -\r\n");
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
                return EVENT_VIDEO_KEY_CAPTURE;
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
				return EVENT_DSC_KEY_CAPTURE;
				break;

			default:
				return EVENT_NONE;
				break;
			}
			break;
    	#ifdef NET_SYNC_PLAYBACK_MODE    
        case WIRELESS_ENTER_PLAYBACK:
            printc("@@@ WIRELESS_ENTER_PLAYBACK -\r\n");
            return EVENT_NET_ENTER_PLAYBACK;
        case WIRELESS_EXIT_PLAYBACK:
            printc("@@@ WIRELESS_EXIT_PLAYBACK -\r\n");
            return EVENT_NET_EXIT_PLAYBACK;
    	#endif        
/*
        case WIRELESS_FORMAT_SD0:
            printc("@@@ WIRELESS_FORMAT_SD0 -\r\n");
            if (MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD)
            {
                if (!AHC_IsSDInserted() || AHC_IsSDWriteProtect())
                {
                    netapp_set_SD0Status(FORMAT_SD_ERROR);
                }
                else
                {
                    netapp_set_SD0Status(FORMAT_SD_DONE);
                }
            }
            break;
*/
        }
        break;
    }
#endif

    switch( ulEvent )
    {
        case BUTTON_NONE           :     return EVENT_NONE;

#if (DIR_KEY_TYPE == KEY_TYPE_4KEY)
        case BUTTON_UP_PRESS	   :	 return EVENT_KEY_UP;
        case BUTTON_UP_LPRESS	   :	 return EVENT_KEY_UP;
        case BUTTON_DOWN_PRESS 	   :	 return EVENT_KEY_DOWN;
        case BUTTON_DOWN_LPRESS	   :	 return EVENT_KEY_DOWN;
        case BUTTON_LEFT_PRESS	   :	 return EVENT_KEY_LEFT;
        case BUTTON_LEFT_LPRESS	   :	 return EVENT_KEY_LEFT;
        case BUTTON_RIGHT_PRESS    :	 return EVENT_KEY_RIGHT;
        case BUTTON_RIGHT_LPRESS   :	 return EVENT_KEY_RIGHT;
#else
		case BUTTON_UP_LPRESS	   :
			switch (HDMIFunc_Status())
			{
				case AHC_HDMI_VIDEO_PREVIEW_STATUS:
				#if (VIDEO_DIGIT_ZOOM_EN == 1)
					return (VideoFunc_RecordStatus())?(EVENT_NONE):(EVENT_KEY_TELE_PRESS);
				#else
					return EVENT_NONE;
				#endif
					break;
				case AHC_HDMI_DSC_PREVIEW_STATUS:
				#if DSC_DIGIT_ZOOM_ENABLE
					return (!IN_MENU())? (EVENT_KEY_TELE_PRESS) : (EVENT_KEY_UP);
				#else
					return (!IN_MENU())? (EVENT_NONE) : (EVENT_KEY_UP);
				#endif
					break;
				case AHC_HDMI_BROWSER_STATUS:
					return EVENT_KEY_LEFT;
					break;
				case AHC_HDMI_MOVIE_PB_STATUS:				
					return (!IN_MENU())? (EVENT_MOVPB_TOUCH_BKWD_PRESS) : (EVENT_KEY_UP);
				case AHC_HDMI_PHOTO_PB_STATUS:				
					return (!IN_MENU())? (EVENT_KEY_LEFT) : (EVENT_KEY_UP);
				case AHC_HDMI_SLIDE_SHOW_STATUS:
					return EVENT_NONE;
				default:
					return EVENT_NONE;
					break;
			}
			break;

		case BUTTON_UP_PRESS	   :
			switch (HDMIFunc_Status())
			{
				case AHC_HDMI_VIDEO_PREVIEW_STATUS:
				#if (VIDEO_DIGIT_ZOOM_EN == 1)
					return (VideoFunc_RecordStatus())?(EVENT_NONE):(EVENT_KEY_TELE_PRESS);
				#else
					return EVENT_KEY_UP;
				#endif
					break;
				case AHC_HDMI_DSC_PREVIEW_STATUS:
				#if DSC_DIGIT_ZOOM_ENABLE
					return (!IN_MENU())? (EVENT_KEY_TELE_PRESS) : (EVENT_KEY_UP);
				#else
					return (!IN_MENU())? (EVENT_NONE) : (EVENT_KEY_UP);
				#endif
					break;
				case AHC_HDMI_BROWSER_STATUS:
					return (!IN_MENU())? (EVENT_KEY_LEFT) : (EVENT_KEY_UP);
					break;
				case AHC_HDMI_MOVIE_PB_STATUS:				
					return (!IN_MENU())? (EVENT_MOVPB_TOUCH_BKWD_PRESS) : (EVENT_KEY_UP);
				case AHC_HDMI_PHOTO_PB_STATUS:				
					return (!IN_MENU())? (EVENT_KEY_LEFT) : (EVENT_KEY_UP);
				case AHC_HDMI_SLIDE_SHOW_STATUS:
					return EVENT_NONE;
				default:
					return EVENT_KEY_UP;
					break;
			}
			break;

		case BUTTON_UP_LREL		   :
			switch (HDMIFunc_Status())
			{
				case AHC_HDMI_VIDEO_PREVIEW_STATUS:
				#if (VIDEO_DIGIT_ZOOM_EN == 1)
					return (VideoFunc_RecordStatus())?(EVENT_VIDEO_KEY_CAPTURE):(EVENT_KEY_TELE_STOP);
				#else
					return EVENT_NONE;
				#endif
					break;
				case AHC_HDMI_DSC_PREVIEW_STATUS:
            	#if DSC_DIGIT_ZOOM_ENABLE
					return (!IN_MENU())? (EVENT_KEY_TELE_STOP) : (EVENT_NONE);
            	#else
					return EVENT_NONE;
            	#endif
					break;
				default:
					return EVENT_NONE;
					break;
			}
			break;

		case BUTTON_UP_REL		   :
			switch (HDMIFunc_Status())
			{
				case AHC_HDMI_VIDEO_PREVIEW_STATUS:
				#if (VIDEO_DIGIT_ZOOM_EN == 1)
					return (VideoFunc_RecordStatus())?(EVENT_NONE):(EVENT_KEY_TELE_STOP);
				#else
					return EVENT_NONE;
				#endif
					break;
				case AHC_HDMI_DSC_PREVIEW_STATUS:
            	#if DSC_DIGIT_ZOOM_ENABLE
					return (!IN_MENU())? (EVENT_KEY_TELE_STOP) : (EVENT_NONE);
            	#else
					return EVENT_NONE;
            	#endif
					break;
				default:
					return EVENT_NONE;
					break;
			}
			break;

		case BUTTON_DOWN_LPRESS    :
			switch (HDMIFunc_Status())
			{
				case AHC_HDMI_VIDEO_PREVIEW_STATUS:
				#if (VIDEO_DIGIT_ZOOM_EN == 1)
					return (VideoFunc_RecordStatus())?(EVENT_NONE):(EVENT_KEY_WIDE_PRESS);
				#else
					return EVENT_NONE;
				#endif
					break;
				case AHC_HDMI_DSC_PREVIEW_STATUS:
            	#if DSC_DIGIT_ZOOM_ENABLE
					return (!IN_MENU())? (EVENT_KEY_WIDE_PRESS) : (EVENT_KEY_DOWN);
           	 	#else
					return (!IN_MENU())? (EVENT_NONE) : (EVENT_KEY_DOWN);
            	#endif
					break;
				case AHC_HDMI_BROWSER_STATUS:
					return (!IN_MENU())? (EVENT_KEY_RIGHT) : (EVENT_KEY_DOWN);
					break;
				case AHC_HDMI_MOVIE_PB_STATUS:				
					return (!IN_MENU())? (EVENT_MOVPB_TOUCH_FRWD_PRESS) : (EVENT_KEY_DOWN);
				case AHC_HDMI_PHOTO_PB_STATUS:				
					return (!IN_MENU())? (EVENT_KEY_RIGHT) : (EVENT_KEY_DOWN);
				case AHC_HDMI_SLIDE_SHOW_STATUS:
					return EVENT_NONE;
				default:
					return EVENT_NONE;
					break;
			}
			break;
		 case BUTTON_DOWN_PRESS 	   :
			switch (HDMIFunc_Status())
			{
				case AHC_HDMI_VIDEO_PREVIEW_STATUS:
				#if (VIDEO_DIGIT_ZOOM_EN == 1)
					return (VideoFunc_RecordStatus())?(EVENT_NONE):(EVENT_KEY_WIDE_PRESS);
				#else
					return EVENT_KEY_DOWN;
				#endif
					break;
				case AHC_HDMI_DSC_PREVIEW_STATUS:
				#if DSC_DIGIT_ZOOM_ENABLE
					return (!IN_MENU())? (EVENT_KEY_WIDE_PRESS) : (EVENT_KEY_DOWN);
				#else
					return (!IN_MENU())? (EVENT_NONE) : (EVENT_KEY_DOWN);
				#endif
					break;
				case AHC_HDMI_BROWSER_STATUS:
					return (!IN_MENU())? (EVENT_KEY_RIGHT) : (EVENT_KEY_DOWN);
					break;
				case AHC_HDMI_MOVIE_PB_STATUS:
					return (!IN_MENU())? (EVENT_MOVPB_TOUCH_FRWD_PRESS) : (EVENT_KEY_DOWN);
				case AHC_HDMI_PHOTO_PB_STATUS:
					return (!IN_MENU())? (EVENT_KEY_RIGHT) : (EVENT_KEY_DOWN);
				case AHC_HDMI_SLIDE_SHOW_STATUS:
					return EVENT_NONE;
				default:
					return EVENT_NONE;
					break;
			}
			break;

		case BUTTON_DOWN_LREL 	   :
		case BUTTON_DOWN_REL 	   :
			switch (HDMIFunc_Status())
			{
				case AHC_HDMI_VIDEO_PREVIEW_STATUS:
				#if (VIDEO_DIGIT_ZOOM_EN == 1)
					return (VideoFunc_RecordStatus())?(EVENT_NONE):(EVENT_KEY_WIDE_STOP);
				#else
					return EVENT_NONE;
				#endif
					break;
				case AHC_HDMI_DSC_PREVIEW_STATUS:
            	#if DSC_DIGIT_ZOOM_ENABLE
					return (!IN_MENU())? (EVENT_KEY_WIDE_STOP) : (EVENT_NONE);
				#else
					return EVENT_NONE;
				#endif
					break;
				default:
					return EVENT_NONE;
					break;
			}
			break;

        //GPIO Key
        case BUTTON_SET_PRESS      :	 return EVENT_HDMI_BROWSER_KEY_PLAYBACK;
        case BUTTON_REC_PRESS      :
			switch (HDMIFunc_Status())
			{
				case AHC_HDMI_BROWSER_STATUS:
					return EVENT_HDMI_BROWSER_KEY_PLAYBACK;
					break;
				case AHC_HDMI_MOVIE_PB_STATUS:
					return (!IN_MENU())? (EVENT_MOVPB_TOUCH_PLAY_PRESS) : (EVENT_KEY_SET);
					break;
				case AHC_HDMI_PHOTO_PB_STATUS:
					return (!IN_MENU())? (EVENT_JPGPB_TOUCH_NEXT_PRESS) : (EVENT_KEY_SET);
					break;
				default:
					return EVENT_HDMI_BROWSER_KEY_PLAYBACK;
					break;
			}
			break;

        case BUTTON_REC_LPRESS      :
            switch (HDMIFunc_Status())
			{
				case AHC_HDMI_VIDEO_PREVIEW_STATUS:
					return EVENT_VIDEO_KEY_CAPTURE;
					break;
				default:
					return EVENT_NONE;
					break;
			}
			break;

        case BUTTON_MENU_REL	   :	 return EVENT_KEY_MENU;
  		case BUTTON_MENU_LPRESS    :	 return EVENT_MOVPB_MODE;
		case BUTTON_MODE_REL	   :	 return EVENT_KEY_MODE;
  		case BUTTON_MODE_LPRESS    :	 return EVENT_NONE;
 		case BUTTON_MUTE_REL       :	 return EVENT_RECORD_MUTE;
 		case BUTTON_MUTE_LPRESS    :	 return EVENT_NONE;
        case BUTTON_POWER_LPRESS   :	 return EVENT_POWER_OFF;
		
#endif//#if (DIR_KEY_TYPE == KEY_TYPE_4KEY)

        //Device
        case BUTTON_USB_DETECTED   :     return EVENT_USB_DETECT;
        case BUTTON_USB_REMOVED    :     return EVENT_USB_REMOVED;
        case BUTTON_USB_B_DEVICE_DETECTED   : return EVENT_USB_B_DEVICE_DETECT;
        case BUTTON_USB_B_DEVICE_REMOVED    : return EVENT_USB_B_DEVICE_REMOVED;
        case BUTTON_SD_DETECTED    :     return EVENT_SD_DETECT;
        case BUTTON_SD_REMOVED     :     return EVENT_SD_REMOVED;
        case BUTTON_TV_DETECTED    :     return EVENT_NONE;
        case BUTTON_TV_REMOVED     :     return EVENT_NONE;
        case BUTTON_HDMI_DETECTED  :     return EVENT_NONE;
        case BUTTON_HDMI_REMOVED   :     return EVENT_HDMI_REMOVED;
        case BUTTON_DC_CABLE_IN    :	 return EVENT_DC_CABLE_IN;
        case BUTTON_DC_CABLE_OUT   :	 return EVENT_DC_CABLE_OUT;

        case BUTTON_LCD_NORMAL     :     return EVENT_LCD_COVER_NORMAL;
        case BUTTON_LCD_ROTATE     :     return EVENT_NONE;
        case BUTTON_COVER_OPEN     :     return EVENT_LCD_COVER_OPEN;
        case BUTTON_COVER_CLOSED   :     return EVENT_LCD_COVER_CLOSE;

        //Record Callback
        case BUTTON_VRCB_MEDIA_FULL:     return EVENT_VRCB_MEDIA_FULL;
        case BUTTON_VRCB_FILE_FULL :     return EVENT_VRCB_FILE_FULL;
        case BUTTON_VRCB_LONG_TIME_FILE_FULL : 	return EVENT_VRCB_LONG_TIME_FILE_FULL;
        case BUTTON_VRCB_MEDIA_SLOW:     return EVENT_VRCB_MEDIA_SLOW;
        case BUTTON_VRCB_MEDIA_ERROR:    return EVENT_VRCB_MEDIA_ERROR;
        case BUTTON_VRCB_SEAM_LESS :     return EVENT_VRCB_SEAM_LESS;
        case BUTTON_VRCB_MOTION_DTC:     return EVENT_VRCB_MOTION_DTC;
        case BUTTON_VRCB_VR_START  :	 return EVENT_VR_START;
        case BUTTON_VRCB_VR_STOP   :	 return EVENT_VR_STOP;
        case BUTTON_VRCB_VR_POSTPROC:    return EVENT_VR_WRITEINFO;

		#if (POWER_ON_BUTTON_ACTION)
		case BUTTON_POWER_ON_MENU  :     return EVENT_SHOW_FW_VERSION;
		case BUTTON_POWER_ON_MODE  :	 return EVENT_FORMAT_RESET_ALL;
		case BUTTON_POWER_ON_REC   :	 return EVENT_NONE;
		case BUTTON_POWER_ON_PLAY  :     return EVENT_NONE;
		#endif

        //Update Message
        case BUTTON_OSD_HIDE       :     return EVENT_SLIDESHOW_OSD_HIDE;
        case BUTTON_UPDATE_FILE    :     return EVENT_SLIDESHOW_UPDATE_FILE;
        case BUTTON_BATTERY_DETECTION:
        case BUTTON_UPDATE_MESSAGE :     return EVENT_MOVPB_UPDATE_MESSAGE;
		case BUTTON_CLEAR_WMSG     :     return EVENT_CLEAR_WMSG;
        case BUTTON_GPSGSENSOR_UPDATE :  return EVENT_GPSGSENSOR_UPDATE;
#if (SUPPORT_DUAL_SNR == 1 && DUALENC_SUPPORT == 1) //For Bitek1603
        case BUTTON_TV_DECODER_SRC_TYPE   : return EVENT_TV_DECODER_SRC_TYPE;
#endif        
        default                    :     return EVENT_NONE;
    }
}

UINT32 KeyParser_TVEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{
#if defined(WIFI_PORT) && (WIFI_PORT == 1)
    switch( ulMsgId )
    {
	case AHLM_WIRELESS_CONNECT:
        switch( ulEvent )
        {
        case WIRELESS_RECORD:
            printc("@@@ WIRELESS_RECORD -\r\n");
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				return EVENT_VIDEO_KEY_RECORD;
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
				return EVENT_DSC_KEY_CAPTURE;
				break;

			default:
				return EVENT_NONE;
				break;
			}
			break;

        case WIRELESS_CAPTURE:
            printc("@@@ WIRELESS_CAPTURE -\r\n");
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
                return EVENT_VIDEO_KEY_CAPTURE;
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
				return EVENT_DSC_KEY_CAPTURE;
				break;

			default:
				return EVENT_NONE;
				break;
			}
			break;
			
    	#ifdef NET_SYNC_PLAYBACK_MODE    
        case WIRELESS_ENTER_PLAYBACK:
            printc("@@@ WIRELESS_ENTER_PLAYBACK -\r\n");
            return EVENT_NET_ENTER_PLAYBACK;
        break;
        case WIRELESS_EXIT_PLAYBACK:
            printc("@@@ WIRELESS_EXIT_PLAYBACK -\r\n");
            return EVENT_NET_EXIT_PLAYBACK;
        break;
    	#endif        
/*
        case WIRELESS_FORMAT_SD0:
            printc("@@@ WIRELESS_FORMAT_SD0 -\r\n");
            if (MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD)
            {
                if (!AHC_IsSDInserted() || AHC_IsSDWriteProtect())
                {
                    netapp_set_SD0Status(FORMAT_SD_ERROR);
                }
                else
                {
                    netapp_set_SD0Status(FORMAT_SD_DONE);
                }
            }
            break;
*/
        }
        break;
    }
#endif

    switch( ulEvent )
    {
        case BUTTON_NONE           :     return EVENT_NONE;

#if (DIR_KEY_TYPE == KEY_TYPE_4KEY)
 		case BUTTON_UP_LPRESS	   :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				#if (VIDEO_DIGIT_ZOOM_EN == 1)
				return (VideoFunc_RecordStatus())?(EVENT_UP):(EVENT_KEY_TELE_PRESS);
				#else
				return EVENT_KEY_UP;
				#endif
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
                #if DSC_DIGIT_ZOOM_ENABLE
				return EVENT_KEY_TELE_PRESS;
				#else
				return EVENT_KEY_UP;
				#endif
				break;

			case AHC_TV_BROWSER_STATUS:
				return EVENT_KEY_UP;
				break;

			case AHC_TV_MOVIE_PB_STATUS:
				return EVENT_KEY_UP;

			case AHC_TV_PHOTO_PB_STATUS:
				return EVENT_KEY_UP;

			case AHC_TV_SLIDE_SHOW_STATUS:
				return EVENT_KEY_UP;

			default:
				return EVENT_KEY_UP;
				break;
			}
			break;

 		case BUTTON_UP_PRESS	   :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				#if (VIDEO_DIGIT_ZOOM_EN == 1)
				return (VideoFunc_RecordStatus())?(EVENT_UP):(EVENT_KEY_TELE_PRESS);
				#else
				return EVENT_KEY_UP;
				#endif
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
                #if DSC_DIGIT_ZOOM_ENABLE
				return EVENT_KEY_TELE_PRESS;
				#else
				return EVENT_KEY_UP;
				#endif
				break;

			case AHC_TV_BROWSER_STATUS:
				return EVENT_KEY_UP;
				break;

			case AHC_TV_MOVIE_PB_STATUS:
				return EVENT_KEY_UP;

			case AHC_TV_PHOTO_PB_STATUS:
				return EVENT_KEY_UP;

			case AHC_TV_SLIDE_SHOW_STATUS:
				return EVENT_KEY_UP;

			default:
				return EVENT_KEY_UP;
				break;
			}
			break;

 		case BUTTON_UP_LREL		   :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				#if (VIDEO_DIGIT_ZOOM_EN == 1)
				return (VideoFunc_RecordStatus())?(EVENT_VIDEO_KEY_CAPTURE):(EVENT_KEY_TELE_STOP);
				#else
				return EVENT_KEY_UP;
				#endif
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
                #if DSC_DIGIT_ZOOM_ENABLE
				return EVENT_KEY_TELE_STOP;
                #else
				return EVENT_KEY_UP;
                #endif
				break;

			default:
				return EVENT_KEY_UP;
				break;
			}
			break;

 		case BUTTON_UP_REL		   :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				#if (VIDEO_DIGIT_ZOOM_EN == 1)
				return (VideoFunc_RecordStatus())?(EVENT_UP):(EVENT_KEY_TELE_STOP);
				#else
				return EVENT_KEY_UP;
				#endif
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
                #if DSC_DIGIT_ZOOM_ENABLE
				return EVENT_KEY_TELE_STOP;
                #else
				return EVENT_KEY_UP;
                #endif
				break;

			default:
				return EVENT_KEY_UP;
				break;
			}
			break;

 		case BUTTON_DOWN_LPRESS    :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				#if (VIDEO_DIGIT_ZOOM_EN == 1)
				return (VideoFunc_RecordStatus())?(EVENT_DOWN):(EVENT_KEY_WIDE_PRESS);
				#else
				return EVENT_KEY_DOWN;
				#endif
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
                #if DSC_DIGIT_ZOOM_ENABLE
				return EVENT_KEY_WIDE_PRESS;
                #else
				return EVENT_KEY_DOWN;
                #endif
				break;

			case AHC_TV_BROWSER_STATUS:
				return EVENT_KEY_DOWN;
				break;

			case AHC_TV_MOVIE_PB_STATUS:
				return EVENT_MOVPB_TOUCH_FRWD_PRESS;

			case AHC_TV_PHOTO_PB_STATUS:
				return EVENT_KEY_DOWN;

			case AHC_TV_SLIDE_SHOW_STATUS:
				return EVENT_KEY_DOWN;

			default:
				return EVENT_KEY_DOWN;
				break;
			}
			break;

 		case BUTTON_DOWN_PRESS 	   :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				#if (VIDEO_DIGIT_ZOOM_EN == 1)
				return (VideoFunc_RecordStatus())?(EVENT_KEY_DOWN):(EVENT_KEY_WIDE_PRESS);
				#else
				return EVENT_KEY_DOWN;
				#endif
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
                #if DSC_DIGIT_ZOOM_ENABLE
				return EVENT_KEY_WIDE_PRESS;
				#else
				return EVENT_KEY_DOWN;
				#endif
				break;

			case AHC_TV_BROWSER_STATUS:
				return EVENT_KEY_DOWN;
				break;

			case AHC_TV_MOVIE_PB_STATUS:
				return EVENT_MOVPB_TOUCH_FRWD_PRESS;

			case AHC_TV_PHOTO_PB_STATUS:
				return EVENT_KEY_DOWN;

			case AHC_TV_SLIDE_SHOW_STATUS:
				return EVENT_KEY_DOWN;

			default:
				return EVENT_KEY_DOWN;
				break;
			}
			break;

 		case BUTTON_DOWN_LREL 	   :
 		case BUTTON_DOWN_REL 	   :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				#if (VIDEO_DIGIT_ZOOM_EN == 1)
				return (VideoFunc_RecordStatus())?(EVENT_KEY_DOWN):(EVENT_KEY_WIDE_STOP);
				#else
				return EVENT_KEY_DOWN;
				#endif
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
                #if DSC_DIGIT_ZOOM_ENABLE
				return EVENT_KEY_WIDE_STOP;
				#else
				return EVENT_KEY_DOWN;
				#endif
				break;

			default:
				return EVENT_KEY_DOWN;
				break;
			}
			break;
#else
 		case BUTTON_UP_LPRESS	   :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				#if (VIDEO_DIGIT_ZOOM_EN == 1)
				return (VideoFunc_RecordStatus())?(EVENT_NONE):(EVENT_KEY_TELE_PRESS);
				#else
				return EVENT_NONE;
				#endif
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
                #if DSC_DIGIT_ZOOM_ENABLE
				return (!IN_MENU())? (EVENT_KEY_TELE_PRESS) : (EVENT_KEY_UP);
				#else
				return (!IN_MENU())? (EVENT_NONE) : (EVENT_KEY_UP);
				#endif
				break;

			case AHC_TV_BROWSER_STATUS:
				return EVENT_KEY_LEFT;
				break;

			case AHC_TV_MOVIE_PB_STATUS:				
				return (!IN_MENU())? (EVENT_MOVPB_TOUCH_BKWD_PRESS) : (EVENT_KEY_UP);
			case AHC_TV_PHOTO_PB_STATUS:				
				return (!IN_MENU())? (EVENT_KEY_LEFT) : (EVENT_KEY_UP);

			case AHC_TV_SLIDE_SHOW_STATUS:
				return EVENT_NONE;

			default:
				return EVENT_NONE;
				break;
			}
			break;

 		case BUTTON_UP_PRESS	   :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				#if (VIDEO_DIGIT_ZOOM_EN == 1)
				return (VideoFunc_RecordStatus())?(EVENT_NONE):(EVENT_KEY_TELE_PRESS);
				#else
				return EVENT_KEY_UP;
				#endif
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
				#if DSC_DIGIT_ZOOM_ENABLE
				return (!IN_MENU())? (EVENT_KEY_TELE_PRESS) : (EVENT_KEY_UP);
				#else
				return (!IN_MENU())? (EVENT_NONE) : (EVENT_KEY_UP);
				#endif

				break;

			case AHC_TV_BROWSER_STATUS:
				return (!IN_MENU())? (EVENT_KEY_LEFT) : (EVENT_KEY_UP);
				break;

			case AHC_TV_MOVIE_PB_STATUS:				
				return (!IN_MENU())? (EVENT_MOVPB_TOUCH_BKWD_PRESS) : (EVENT_KEY_UP);

			case AHC_TV_PHOTO_PB_STATUS:				
				return (!IN_MENU())? (EVENT_KEY_LEFT) : (EVENT_KEY_UP);

			case AHC_TV_SLIDE_SHOW_STATUS:
				return EVENT_NONE;

			default:
				return EVENT_KEY_UP;
				break;
			}
			break;

 		case BUTTON_UP_LREL		   :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				#if (VIDEO_DIGIT_ZOOM_EN == 1)
				return (VideoFunc_RecordStatus())?(EVENT_VIDEO_KEY_CAPTURE):(EVENT_KEY_TELE_STOP);
				#else
				return EVENT_NONE;
				#endif
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
                #if DSC_DIGIT_ZOOM_ENABLE
				return (!IN_MENU())? (EVENT_KEY_TELE_STOP) : (EVENT_NONE);
                #else
				return EVENT_NONE;
                #endif
				break;

			default:
				return EVENT_NONE;
				break;
			}
			break;

 		case BUTTON_UP_REL		   :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				#if (VIDEO_DIGIT_ZOOM_EN == 1)
				return (VideoFunc_RecordStatus())?(EVENT_NONE):(EVENT_KEY_TELE_STOP);
				#else
				return EVENT_NONE;
				#endif
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
                #if DSC_DIGIT_ZOOM_ENABLE
				return (!IN_MENU())? (EVENT_KEY_TELE_STOP) : (EVENT_NONE);
                #else
				return EVENT_NONE;
                #endif
				break;

			default:
				return EVENT_NONE;
				break;
			}
			break;

 		case BUTTON_DOWN_LPRESS    :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				#if (VIDEO_DIGIT_ZOOM_EN == 1)
				return (VideoFunc_RecordStatus())?(EVENT_NONE):(EVENT_KEY_WIDE_PRESS);
				#else
				return EVENT_NONE;
				#endif
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
                #if DSC_DIGIT_ZOOM_ENABLE
				return (!IN_MENU())? (EVENT_KEY_WIDE_PRESS) : (EVENT_KEY_DOWN);
                #else
				return (!IN_MENU())? (EVENT_NONE) : (EVENT_KEY_DOWN);
                #endif
				break;

			case AHC_TV_BROWSER_STATUS:
				return (!IN_MENU())? (EVENT_KEY_RIGHT) : (EVENT_KEY_DOWN);
				break;

			case AHC_TV_MOVIE_PB_STATUS:				
				return (!IN_MENU())? (EVENT_MOVPB_TOUCH_FRWD_PRESS) : (EVENT_KEY_DOWN);

			case AHC_TV_PHOTO_PB_STATUS:				
				return (!IN_MENU())? (EVENT_KEY_RIGHT) : (EVENT_KEY_DOWN);

			case AHC_TV_SLIDE_SHOW_STATUS:
				return EVENT_NONE;

			default:
				return EVENT_NONE;
				break;
			}
			break;

 		case BUTTON_DOWN_PRESS 	   :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				#if (VIDEO_DIGIT_ZOOM_EN == 1)
				return (VideoFunc_RecordStatus())?(EVENT_NONE):(EVENT_KEY_WIDE_PRESS);
				#else
				return EVENT_KEY_DOWN;
				#endif
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
				#if DSC_DIGIT_ZOOM_ENABLE
				return (!IN_MENU())? (EVENT_KEY_WIDE_PRESS) : (EVENT_KEY_DOWN);
				#else
				return (!IN_MENU())? (EVENT_NONE) : (EVENT_KEY_DOWN);
				#endif
				break;

			case AHC_TV_BROWSER_STATUS:
				return (!IN_MENU())? (EVENT_KEY_RIGHT) : (EVENT_KEY_DOWN);
				break;

			case AHC_TV_MOVIE_PB_STATUS:
				return (!IN_MENU())? (EVENT_MOVPB_TOUCH_FRWD_PRESS) : (EVENT_KEY_DOWN);

			case AHC_TV_PHOTO_PB_STATUS:
				return (!IN_MENU())? (EVENT_KEY_RIGHT) : (EVENT_KEY_DOWN);

			case AHC_TV_SLIDE_SHOW_STATUS:
				return EVENT_NONE;

			default:
				return EVENT_NONE;
				break;
			}
			break;

 		case BUTTON_DOWN_LREL 	   :
 		case BUTTON_DOWN_REL 	   :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				#if (VIDEO_DIGIT_ZOOM_EN == 1)
				return (VideoFunc_RecordStatus())?(EVENT_NONE):(EVENT_KEY_WIDE_STOP);
				#else
				return EVENT_NONE;
				#endif
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
                #if DSC_DIGIT_ZOOM_ENABLE
				return (!IN_MENU())? (EVENT_KEY_WIDE_STOP) : (EVENT_NONE);
				#else
				return EVENT_NONE;
				#endif
				break;

			default:
				return EVENT_NONE;
				break;
			}
			break;
#endif

 		case BUTTON_LEFT_LPRESS	   :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				return EVENT_NONE;
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
				return EVENT_NONE;
				break;

			case AHC_TV_BROWSER_STATUS:
				return EVENT_KEY_LEFT;
				break;

			case AHC_TV_MOVIE_PB_STATUS:
				return EVENT_MOVPB_TOUCH_BKWD_PRESS;

			case AHC_TV_PHOTO_PB_STATUS:
				return EVENT_KEY_LEFT;

			case AHC_TV_SLIDE_SHOW_STATUS:
				return EVENT_NONE;

			default:
				return EVENT_NONE;
				break;
			}
			break;

 		case BUTTON_LEFT_PRESS	   :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				return EVENT_KEY_LEFT;
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
				return EVENT_KEY_LEFT;
				break;

			case AHC_TV_BROWSER_STATUS:
				return EVENT_KEY_LEFT;
				break;

			case AHC_TV_MOVIE_PB_STATUS:
				return EVENT_MOVPB_TOUCH_BKWD_PRESS;

			case AHC_TV_PHOTO_PB_STATUS:
				return EVENT_KEY_LEFT;

			case AHC_TV_SLIDE_SHOW_STATUS:
				return EVENT_KEY_LEFT;

			default:
				return EVENT_KEY_LEFT;
				break;
			}
			break;

 		case BUTTON_LEFT_LREL		   :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				return EVENT_KEY_LEFT;
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
				return EVENT_KEY_LEFT;
				break;

			default:
				return EVENT_KEY_LEFT;
				break;
			}
			break;

 		case BUTTON_LEFT_REL		   :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				return EVENT_KEY_LEFT;
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
				return EVENT_KEY_LEFT;
				break;

			default:
				return EVENT_KEY_LEFT;
				break;
			}
			break;

 		case BUTTON_RIGHT_LPRESS    :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				return EVENT_KEY_RIGHT;
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
				return EVENT_KEY_RIGHT;
				break;

			case AHC_TV_BROWSER_STATUS:
				return EVENT_KEY_RIGHT;
				break;

			case AHC_TV_MOVIE_PB_STATUS:
				return EVENT_MOVPB_TOUCH_FRWD_PRESS;

			case AHC_TV_PHOTO_PB_STATUS:
				return EVENT_KEY_RIGHT;

			case AHC_TV_SLIDE_SHOW_STATUS:
				return EVENT_NONE;

			default:
				return EVENT_KEY_RIGHT;
				break;
			}
			break;

 		case BUTTON_RIGHT_PRESS	   :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				return EVENT_KEY_RIGHT;
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
				return EVENT_KEY_RIGHT;
				break;

			case AHC_TV_BROWSER_STATUS:
				return EVENT_KEY_RIGHT;
				break;

			case AHC_TV_MOVIE_PB_STATUS:
				return EVENT_MOVPB_TOUCH_FRWD_PRESS;

			case AHC_TV_PHOTO_PB_STATUS:
				return EVENT_KEY_RIGHT;

			case AHC_TV_SLIDE_SHOW_STATUS:
				return EVENT_KEY_RIGHT;

			default:
				return EVENT_KEY_RIGHT;
				break;
			}
			break;

 		case BUTTON_RIGHT_LREL 	   :
 		case BUTTON_RIGHT_REL 	   :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				return EVENT_KEY_RIGHT;
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
				return EVENT_KEY_RIGHT;
				break;

			default:
				return EVENT_KEY_RIGHT;
				break;
			}
			break;

        case BUTTON_SET_PRESS      :	 return EVENT_THUMBNAIL_KEY_PLAYBACK;

        case BUTTON_REC_PRESS      :
			switch (TVFunc_Status())
			{
			case AHC_TV_BROWSER_STATUS:
				return EVENT_THUMBNAIL_KEY_PLAYBACK;
			break;

			case AHC_TV_MOVIE_PB_STATUS:
				return (!IN_MENU())? (EVENT_MOVPB_TOUCH_PLAY_PRESS) : (EVENT_KEY_SET);
			break;

			case AHC_TV_PHOTO_PB_STATUS:
				return (!IN_MENU())? (EVENT_JPGPB_TOUCH_NEXT_PRESS) : (EVENT_KEY_SET);
			break;

			default:
				return EVENT_NONE;
			break;
			}
			break;
        case BUTTON_REC_LPRESS      :
            switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				return EVENT_VIDEO_KEY_CAPTURE;
			break;
			default:
				return EVENT_NONE;
			break;
			}
			break;

        case BUTTON_REC_REL        :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				return EVENT_VIDEO_KEY_RECORD;
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
				return (!IN_MENU())?(EVENT_DSC_KEY_CAPTURE) : (EVENT_KEY_SET);
				break;

			default:
				return EVENT_NONE;
				break;
			}
			break;

// 		case BUTTON_SOS_PRESS      :	 return EVENT_NONE;
// 		case BUTTON_SOS_LPRESS     :	 return EVENT_NONE;

 		case BUTTON_SOS_REL	       :
 		case BUTTON_SOS_LREL       :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				return (VideoFunc_RecordStatus())?(EVENT_LOCK_VR_FILE):(EVENT_SWITCH_VMD_MODE);
				break;

			case AHC_TV_DSC_PREVIEW_STATUS:
				return EVENT_SWITCH_VMD_MODE;
				break;

			default:
				return EVENT_NONE;
				break;
			}
			break;

        case BUTTON_MENU_PRESS	   :	 return EVENT_NONE;
        case BUTTON_MENU_REL	   :	 
			return ((AHC_TV_VIDEO_PREVIEW_STATUS == TVFunc_Status()) && (VideoFunc_RecordStatus()||uiGetParkingModeEnable()))?(EVENT_NONE):(EVENT_KEY_MENU);
  		case BUTTON_MENU_LPRESS    :	 
			return ((AHC_TV_VIDEO_PREVIEW_STATUS != TVFunc_Status()) || VideoFunc_RecordStatus())?(EVENT_NONE):((SUPPORT_PARKINGMODE == PARKINGMODE_NONE) ? EVENT_NONE : EVENT_PARKING_KEY);

        case BUTTON_MODE_PRESS	   :
	 		switch(TVFunc_Status())
			{
			case AHC_TV_BROWSER_STATUS:
				return EVENT_KEY_MODE;
			break;
			case AHC_TV_MOVIE_PB_STATUS:
				return EVENT_MOVPB_TOUCH_RETURN;
			break;
			case AHC_TV_PHOTO_PB_STATUS:
				return EVENT_JPGPB_TOUCH_RETURN;
			break;

			default:
				return EVENT_KEY_MODE;
			break;
			}
		break;

  		case BUTTON_MODE_LPRESS    :	 return EVENT_NONE;
 		case BUTTON_MUTE_REL       :	 return EVENT_RECORD_MUTE;
 		case BUTTON_MUTE_LPRESS    :	 return EVENT_NONE;
        case BUTTON_POWER_LPRESS   :	 return EVENT_POWER_OFF;
		case BUTTON_MODE_REL	   :	 return (VideoFunc_RecordStatus())?(EVENT_LOCK_VR_FILE):(EVENT_NONE);

        case BUTTON_SET_REL        :
	 		switch(TVFunc_Status())
			{
			case AHC_TV_BROWSER_STATUS:
				return EVENT_THUMBNAIL_KEY_PLAYBACK;
			break;
			case AHC_TV_MOVIE_PB_STATUS:
				return EVENT_MOVPB_TOUCH_PLAY_PRESS;
			break;
			case AHC_TV_PHOTO_PB_STATUS:
				return EVENT_JPGPB_TOUCH_NEXT_PRESS;
			break;
			default:
				return EVENT_NONE;
			break;
			}
		break;

        //Device
        case BUTTON_USB_DETECTED   :     return EVENT_USB_DETECT;
        case BUTTON_USB_REMOVED    :     return EVENT_USB_REMOVED;
        case BUTTON_USB_B_DEVICE_DETECTED   : return EVENT_USB_B_DEVICE_DETECT;
        case BUTTON_USB_B_DEVICE_REMOVED    : return EVENT_USB_B_DEVICE_REMOVED;
        case BUTTON_SD_DETECTED    :     return EVENT_SD_DETECT;
        case BUTTON_SD_REMOVED     :     return EVENT_SD_REMOVED;
        case BUTTON_TV_DETECTED    :     return EVENT_NONE;
        case BUTTON_TV_REMOVED     :     return EVENT_TV_REMOVED;
        case BUTTON_HDMI_DETECTED  :     return EVENT_HDMI_DETECT;
        case BUTTON_HDMI_REMOVED   :     return EVENT_NONE;
        case BUTTON_DC_CABLE_IN    :	 return EVENT_DC_CABLE_IN;
        case BUTTON_DC_CABLE_OUT   :	 return EVENT_DC_CABLE_OUT;

        case BUTTON_LCD_NORMAL     :     return EVENT_LCD_COVER_NORMAL;
        case BUTTON_LCD_ROTATE     :     return EVENT_NONE;
        case BUTTON_COVER_OPEN     :     return EVENT_LCD_COVER_OPEN;
        case BUTTON_COVER_CLOSED   :     return EVENT_LCD_COVER_CLOSE;

        //Record Callback
        case BUTTON_VRCB_MEDIA_FULL:     return EVENT_VRCB_MEDIA_FULL;
        case BUTTON_VRCB_FILE_FULL :     return EVENT_VRCB_FILE_FULL;
        case BUTTON_VRCB_LONG_TIME_FILE_FULL : 	return EVENT_VRCB_LONG_TIME_FILE_FULL;
        case BUTTON_VRCB_MEDIA_SLOW:     return EVENT_VRCB_MEDIA_SLOW;
        case BUTTON_VRCB_MEDIA_ERROR:    return EVENT_VRCB_MEDIA_ERROR;
        case BUTTON_VRCB_SEAM_LESS :     return EVENT_VRCB_SEAM_LESS;
        case BUTTON_VRCB_MOTION_DTC:     return EVENT_VRCB_MOTION_DTC;
        case BUTTON_VRCB_VR_START  :	 return EVENT_VR_START;
        case BUTTON_VRCB_VR_STOP   :	 return EVENT_VR_STOP;
        case BUTTON_VRCB_VR_POSTPROC:    return EVENT_VR_WRITEINFO;
        case BUTTON_VRCB_RECDSTOP_CARDSLOW:     return EVENT_VRCB_RECDSTOP_CARDSLOW;

		#if (POWER_ON_BUTTON_ACTION)
		case BUTTON_POWER_ON_MENU  :     return EVENT_SHOW_FW_VERSION;
		case BUTTON_POWER_ON_MODE  :	 return EVENT_FORMAT_RESET_ALL;
		case BUTTON_POWER_ON_REC   :	 return EVENT_NONE;
		case BUTTON_POWER_ON_PLAY  :     return EVENT_NONE;
		#endif

        //Update Message
        case BUTTON_OSD_HIDE       :     return EVENT_SLIDESHOW_OSD_HIDE;
        case BUTTON_UPDATE_FILE    :     return EVENT_SLIDESHOW_UPDATE_FILE;
        case BUTTON_BATTERY_DETECTION:
        case BUTTON_UPDATE_MESSAGE :
			switch (TVFunc_Status())
			{
			case AHC_TV_VIDEO_PREVIEW_STATUS:
				return EVENT_VIDREC_UPDATE_MESSAGE;

			case AHC_TV_DSC_PREVIEW_STATUS:
				return EVENT_DSC_KEY_UPDATE_MESSAGE;

			case AHC_TV_BROWSER_STATUS:
				return EVENT_THUMBNAIL_UPDATE_MESSAGE;

			case AHC_TV_MOVIE_PB_STATUS:
				return EVENT_MOVPB_UPDATE_MESSAGE;

			case AHC_TV_PHOTO_PB_STATUS:
				return EVENT_JPGPB_UPDATE_MESSAGE;

			case AHC_TV_SLIDE_SHOW_STATUS:
				return EVENT_SLIDESHOW_UPDATE_MESSAGE;
			}

			return EVENT_NONE;
			break;

        case BUTTON_GPSGSENSOR_UPDATE :  return EVENT_GPSGSENSOR_UPDATE;

		case BUTTON_CLEAR_WMSG     :     return EVENT_CLEAR_WMSG;
        #if (EMERGENCY_RECODE_FLOW_TYPE == EMERGENCY_RECODE_SWITCH_FILE)
        case BUTTON_LOCK_FILE_G    :     return EVENT_VR_EMERGENT;
        #else
        case BUTTON_LOCK_FILE_G    :     return EVENT_LOCK_FILE_G;
        #endif
        case BUTTON_VRCB_EMER_DONE :	 return EVENT_VRCB_EMER_DONE;
#if (SUPPORT_DUAL_SNR == 1 && DUALENC_SUPPORT == 1) //For Bitek1603
        case BUTTON_TV_DECODER_SRC_TYPE   : return EVENT_TV_DECODER_SRC_TYPE;
#endif        
        default                    :     return EVENT_NONE;
    }
}

UINT32 KeyParser_MsdcEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{
	
#if defined(WIFI_PORT) && (WIFI_PORT == 1)
    switch( ulMsgId )
    {
	case AHLM_WIRELESS_CONNECT:
        switch( ulEvent )
        {
    	#ifdef NET_SYNC_PLAYBACK_MODE    
        case WIRELESS_ENTER_PLAYBACK:
            printc("=====> WIRELESS_ENTER_PLAYBACK\r\n");
            return EVENT_NET_ENTER_PLAYBACK;
    	#endif        
        }
        break;
    }
#endif

    switch( ulEvent )
    {
        case BUTTON_NONE		   :     return EVENT_NONE;

		//ADC Key
 		case BUTTON_UP_PRESS	   :	 return EVENT_NONE;
 		case BUTTON_DOWN_PRESS 	   :	 return EVENT_NONE;

  		//GPIO Key
  		case BUTTON_REC_PRESS      :     return EVENT_NONE;
		case BUTTON_MENU_REL	   :	 return EVENT_NONE;
  		case BUTTON_MENU_LPRESS    :	 return EVENT_NONE;
		case BUTTON_MODE_REL	   :     return EVENT_NONE;
  		case BUTTON_MODE_LPRESS    :	 return EVENT_NONE;
 		case BUTTON_MUTE_REL       :	 return EVENT_NONE;
 		case BUTTON_MUTE_LPRESS    :	 return EVENT_NONE;
 		case BUTTON_POWER_LPRESS   :	 return EVENT_POWER_OFF;

		//Device
        case BUTTON_USB_DETECTED   :     return EVENT_USB_DETECT;
        case BUTTON_USB_REMOVED    :     return EVENT_USB_REMOVED;
        case BUTTON_USB_B_DEVICE_DETECTED   : return EVENT_USB_B_DEVICE_DETECT;
        case BUTTON_USB_B_DEVICE_REMOVED    : return EVENT_USB_B_DEVICE_REMOVED;
        case BUTTON_SD_DETECTED    :     return EVENT_SD_DETECT;
        case BUTTON_SD_REMOVED     :     return EVENT_SD_REMOVED;
        case BUTTON_TV_DETECTED    :     return EVENT_TV_DETECT;
        case BUTTON_TV_REMOVED     :     return EVENT_TV_REMOVED;
        case BUTTON_DC_CABLE_IN    :	 return EVENT_DC_CABLE_IN;
        case BUTTON_DC_CABLE_OUT   :	 return EVENT_DC_CABLE_OUT;

        case BUTTON_LCD_NORMAL     :     return EVENT_LCD_COVER_NORMAL;
        case BUTTON_LCD_ROTATE     :     return EVENT_LCD_COVER_ROTATE;
        case BUTTON_COVER_OPEN     :     return EVENT_LCD_COVER_OPEN;
        case BUTTON_COVER_CLOSED   :     return EVENT_LCD_COVER_CLOSE;

		//Update Message
        case BUTTON_UPDATE_MESSAGE :     return EVENT_MSDC_UPDATE_MESSAGE;
		case BUTTON_CLEAR_WMSG     :     return EVENT_CLEAR_WMSG;
#if (SUPPORT_DUAL_SNR == 1 && DUALENC_SUPPORT == 1) //For Bitek1603
        case BUTTON_TV_DECODER_SRC_TYPE   : return EVENT_TV_DECODER_SRC_TYPE;
#endif        
        default                    :     return EVENT_NONE;
    }
}

UINT32 KeyParser_NetPlaybackEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{

#if defined(WIFI_PORT) && (WIFI_PORT == 1)
    switch( ulMsgId )
    {
	case AHLM_WIRELESS_CONNECT:
        switch( ulEvent )
        {
        case WIRELESS_RECORD:
        case WIRELESS_CAPTURE:
            return EVENT_DSC_KEY_CAPTURE;
        case WIRELESS_EXIT_PLAYBACK:
            printc("=====> WIRELESS_EXIT_PLAYBACK\r\n");
            return EVENT_NET_EXIT_PLAYBACK;
        }
        break;
    }
#endif

    switch( ulEvent )
    {
        case BUTTON_NONE		   :     return EVENT_NONE;
#if (SUPPORT_TOUCH_PANEL)
        case BUTTON_TOUCH_PRESS    :     return AhcCheckTouchButton( &ulParam,  AHC_FALSE );
        case BUTTON_TOUCH_MOVE     :     return AhcCheckTouchButton( &ulParam,  AHC_TRUE);
#endif

#if (DSC_DIGIT_ZOOM_ENABLE)
 		case BUTTON_UP_PRESS	   :	 return EVENT_KEY_TELE_PRESS;
 		case BUTTON_DOWN_PRESS     :	 return EVENT_KEY_WIDE_PRESS;
 		case BUTTON_UP_REL         :     return EVENT_KEY_TELE_STOP;
        case BUTTON_DOWN_REL       :     return EVENT_KEY_WIDE_STOP;
#else
 		case BUTTON_UP_PRESS	   :	 return EVENT_NONE;
 		case BUTTON_DOWN_PRESS     :	 return EVENT_NONE;
 		case BUTTON_UP_REL         :     return EVENT_NONE;
        case BUTTON_DOWN_REL       :     return EVENT_NONE;
#endif
		// Link with KEY_DSC_CAPTURE
  		case BUTTON_REC_REL        :     return EVENT_DSC_KEY_CAPTURE;

		case BUTTON_MENU_REL       :     return EVENT_KEY_MENU;
		case BUTTON_MODE_REL	   :     return EVENT_KEY_MODE;
// 		case BUTTON_MUTE_REL       :	 return EVENT_NONE;
// 		case BUTTON_MUTE_LPRESS    :	 return EVENT_LCD_POWER_SAVE;
 		case BUTTON_POWER_LPRESS   :	 return EVENT_POWER_OFF;

 		case BUTTON_SOS_REL        :	 return EVENT_SWITCH_VMD_MODE;
 		case BUTTON_SOS_LPRESS     :	 return EVENT_SWITCH_TIME_LAPSE_EN;

 		case BUTTON_SET_PRESS      :	 return EVENT_DSC_KEY_CHANGE_SHOT_MODE;

		//Device
        case BUTTON_USB_DETECTED   :     return EVENT_USB_DETECT;
        case BUTTON_USB_REMOVED    :     return EVENT_USB_REMOVED;
        case BUTTON_USB_B_DEVICE_DETECTED   : return EVENT_USB_B_DEVICE_DETECT;
        case BUTTON_USB_B_DEVICE_REMOVED    : return EVENT_USB_B_DEVICE_REMOVED;
        case BUTTON_SD_DETECTED    :     return EVENT_SD_DETECT;
        case BUTTON_SD_REMOVED     :     return EVENT_SD_REMOVED;
        case BUTTON_TV_DETECTED    :     return EVENT_TV_DETECT;
        case BUTTON_TV_REMOVED     :     return EVENT_TV_REMOVED;
        case BUTTON_HDMI_DETECTED  :     return EVENT_HDMI_DETECT;
        case BUTTON_HDMI_REMOVED   :     return EVENT_HDMI_REMOVED;
        case BUTTON_DC_CABLE_IN    :	 return EVENT_DC_CABLE_IN;
        case BUTTON_DC_CABLE_OUT   :	 return EVENT_DC_CABLE_OUT;

        case BUTTON_LCD_NORMAL     :     return EVENT_LCD_COVER_NORMAL;
        case BUTTON_LCD_ROTATE     :     return EVENT_LCD_COVER_ROTATE;
        case BUTTON_COVER_OPEN     :     return EVENT_LCD_COVER_OPEN;
        case BUTTON_COVER_CLOSED   :     return EVENT_LCD_COVER_CLOSE;

        //Callback
        case BUTTON_VRCB_MOTION_DTC:     return EVENT_VRCB_MOTION_DTC;

        //Update Message
		case BUTTON_BATTERY_DETECTION:
        case BUTTON_UPDATE_MESSAGE :     return EVENT_DSC_KEY_UPDATE_MESSAGE;
        case BUTTON_CLEAR_WMSG     :     return EVENT_CLEAR_WMSG;
#if (SUPPORT_DUAL_SNR == 1 && DUALENC_SUPPORT == 1) //For Bitek1603
        case BUTTON_TV_DECODER_SRC_TYPE   : return EVENT_TV_DECODER_SRC_TYPE;
#endif        
        default                    :     return EVENT_NONE;
    }
}
#if 0
void ________MenuEvent_Function_________(){ruturn;} //dummy
#endif

UINT32 MenuButtonToMenuOp(UINT32 ulEvent ,UINT32 ulPosition)
{
	UINT32 LCDstatus;

	AHC_GetParam(PARAM_ID_LCD_STATUS,&LCDstatus);
	
	#if defined(WIFI_PORT) && (WIFI_PORT == 1)
    switch( ulEvent )
    {
        case WIRELESS_ENTER_PLAYBACK:
            printc("=====> WIRELESS_ENTER_PLAYBACK\r\n");
            return EVENT_NET_ENTER_PLAYBACK;
    }
	#endif

    switch( ulEvent )
    {
   		#if(SUPPORT_TOUCH_PANEL)
        case BUTTON_TOUCH_MOVE     :     return MENU_TOUCH_MOVE;
        case BUTTON_TOUCH_PRESS    :      return AhcCheckTouchButton( &ulPosition,  AHC_FALSE );
        case BUTTON_TOUCH_REL      :     return MENU_TOUCH_RELEASE;    
		#endif

		case BUTTON_VIRTUAL_RESET  :
			return (PowerOff_InProcess)?(MENU_NONE):(MENU_INIT);

		case BUTTON_UP_PRESS       :
		case BUTTON_UP_LPRESS      :
			return (PowerOff_InProcess)?(MENU_NONE):(MENU_UP);

		case BUTTON_DOWN_PRESS     :
		case BUTTON_DOWN_LPRESS    :
			return (PowerOff_InProcess)?(MENU_NONE):(MENU_DOWN);

		case BUTTON_LEFT_PRESS       :
		case BUTTON_LEFT_LPRESS      :
            #if DIR_KEY_TYPE == KEY_TYPE_4KEY
			return (PowerOff_InProcess)?(MENU_NONE):(MENU_LEFT);
			#else
			return (PowerOff_InProcess)?(MENU_NONE):(MENU_DOWN);
			#endif

		case BUTTON_RIGHT_PRESS     :
		case BUTTON_RIGHT_LPRESS    :
            #if DIR_KEY_TYPE == KEY_TYPE_4KEY
			return (PowerOff_InProcess)?(MENU_NONE):(MENU_RIGHT);
			#else
			return (PowerOff_InProcess)?(MENU_NONE):(MENU_UP);
			#endif

		case BUTTON_TV_DETECTED    :     return (PowerOff_InProcess)?(MENU_NONE):(MENU_TV_DETECT);
        
	    case BUTTON_SET_PRESS      :
	    case BUTTON_REC_PRESS      :
			return MENU_NONE;
		case BUTTON_REC_REL	   :
			return (PowerOff_InProcess)?(MENU_NONE):(MENU_OK);

	    case BUTTON_MENU_REL       :
			return (PowerOff_InProcess)?(MENU_NONE):(MENU_MENU);

	    case BUTTON_MODE_REL       :
			return (PowerOff_InProcess)?(MENU_NONE):(MENU_RIGHT);

	    case BUTTON_MUTE_REL       :
			return (PowerOff_InProcess)?(MENU_NONE):(MENU_NONE);

#if (FLIP_CTRL_METHOD & CTRL_BY_KEY) && (KEY_ROTATE_OSD_SNR != BUTTON_ID_UNKNOWN)
	    case KEY_ROTATE_OSD_SNR       :
			return (LCDstatus==0)?(MENU_LCD_ROTATE):(MENU_LCD_NORMAL);
#endif

		case KEY_POWER_OFF      :
			return (PowerOff_InProcess)?(MENU_NONE):(MENU_POWER_OFF);

        //Device
        case BUTTON_DC_CABLE_IN:
        	return MENU_NONE;

        case BUTTON_DC_CABLE_OUT:
			AHC_SetChargerEnable(AHC_FALSE);
			#if (CHARGER_OUT_ACT_OTHER_MODE==ACT_FORCE_POWER_OFF || CHARGER_OUT_ACT_OTHER_MODE==ACT_DELAY_POWER_OFF)
			AHC_SetShutdownByChargerOut(AHC_TRUE);
			#endif
			return MENU_NONE;

        case BUTTON_USB_DETECTED   :
			if (IsAdapter_Connect())
			{

			}
			else
			{
				//StateSwitchMode(UI_MSDC_STATE);
				#if (USB_MODE_SELECT_EN)
    			if (MMPS_USB_NORMAL == MMPS_USB_GetStatus()) {
    			    StateSwitchMode(UI_USBSELECT_MENU_STATE);
    			}
    			else
    			{
    				#ifdef CFG_POWER_ON_ENTER_CAMERA_STATE
    				StateSwitchMode(UI_CAMERA_STATE);
    				#else
    				StateSwitchMode(UI_VIDEO_STATE);
    				#endif
    			}
				#else
				if(MenuSettingConfig()->uiUSBFunction == USB_MSDC)
				{
                	StateSwitchMode(UI_MSDC_STATE);
				}
				else
				{
					StateSwitchMode(UI_PCCAM_STATE);
				}
				#endif
			}
			return MENU_NONE;

        case BUTTON_USB_REMOVED    :

			if((AHC_USB_GetLastStatus() == AHC_USB_NORMAL)) // MSDC mode
			{
				bForce_PowerOff = AHC_TRUE;
				AHC_NormalPowerOffPath();
			}
			else
			{
				AHC_SetChargerEnable(AHC_FALSE);
				#if (CHARGER_OUT_ACT_OTHER_MODE==ACT_FORCE_POWER_OFF || CHARGER_OUT_ACT_OTHER_MODE==ACT_DELAY_POWER_OFF)
				AHC_SetShutdownByChargerOut(AHC_TRUE);
				#endif
			}
			return MENU_NONE;
#if (UVC_HOST_VIDEO_ENABLE)
        case BUTTON_USB_B_DEVICE_DETECTED:
        case BUTTON_USB_B_DEVICE_REMOVED:
			AHC_USB_PauseDetection(0);
			if((AHC_GetCurKeyEventID() == BUTTON_USB_B_DEVICE_DETECTED) ||
				(AHC_GetCurKeyEventID() == BUTTON_USB_B_DEVICE_REMOVED)){
				AHC_SetCurKeyEventID(EVENT_NONE);
			}
			else{
				AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0);
				printc("KeyEventID: BUTTON_USB_B_DEVICE_DETECTED,REMOVED is interrupted.\r\n");
			}  
            break;
#endif
#if (SUPPORT_DUAL_SNR == 1 && DUALENC_SUPPORT == 1) //For Bitek1603
        case BUTTON_TV_DECODER_SRC_TYPE:
            printc("BUTTON_TV_DECODER_SRC_TYPE,%s,%d\r\n", __func__, __LINE__);
            break;        
#endif        
       	case BUTTON_COVER_OPEN	   :
			LedCtrl_LcdBackLight(AHC_TRUE);
			return MENU_NONE;

        case BUTTON_COVER_CLOSED    :
			LedCtrl_LcdBackLight(AHC_FALSE);
			return MENU_NONE;

        case SD_CARD_IN		 	   :

			switch(uiGetLastState())
			{
				case UI_PLAYBACK_STATE:
					PlaybackMode_SDMMC_In();
				break;
				case UI_SLIDESHOW_STATE:
					SlideShowMode_SDMMC_In();
				break;
				default:
					bRefreshBrowser = AHC_TRUE;
					AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect);
				break;
			}

			return MENU_SDMMC_IN;

        case SD_CARD_OUT		   :

			switch(uiGetLastState())
			{
				case UI_PLAYBACK_STATE:
                	PlaybackMode_SDMMC_Out();
				break;
				case UI_SLIDESHOW_STATE:
					SlideShowMode_SDMMC_Out();
				break;
				default:
                	if(AHC_TRUE == AHC_SDMMC_GetMountState())
                    	AHC_DisMountStorageMedia(AHC_MEDIA_MMC);
				break;
			}

            return MENU_SDMMC_OUT;

        case DEVICE_LCD_NOR        :     return MENU_LCD_NORMAL;
        case DEVICE_LCD_INV        :     return MENU_LCD_ROTATE;
        case BUTTON_BATTERY_DETECTION :  return MENU_BATTERY_DETECTION;
        case BUTTON_UPDATE_MESSAGE :	 return MENU_UPDATE_MESSAGE;
        default                    :     return MENU_NONE;
    }

    return MENU_NONE;
}

#if 0
void ________GlobalEvent_Function_________(){ruturn;} //dummy
#endif

AHC_BOOL uiStateProcessGlobalEvent( UINT32 ulMsgId, UINT32* pulEvent , UINT32* pulParam)
{
#ifdef FACTORY_RESET
    if (FACTORY_RESET == *pulEvent) {
    	RestoreFromDefaultSetting();
    	Menu_RenewMenuSetting(AHC_TRUE);
    	Menu_WriteLcdSnrTVHdmiStauts2SF();
    }
#endif

	#if defined(WIFI_PORT) && (WIFI_PORT == 1)
		if(ulMsgId != AHLM_WIRELESS_CONNECT)
		{
			switch(*pulEvent)
			{
			case BUTTON_REC_PRESS       : 	
  			case BUTTON_REC_REL			:
  			case BUTTON_REC_LPRESS		:
			case BUTTON_MENU_REL		:	
			case BUTTON_MENU_LPRESS		:
			case BUTTON_MENU_PRESS		: 
			case BUTTON_MODE_REL		:   
			case BUTTON_MODE_LPRESS		:  
			case BUTTON_MODE_PRESS      :
 			case BUTTON_MUTE_REL		:	
 			case BUTTON_MUTE_LPRESS		:
 			case BUTTON_MUTE_PRESS      :
 			case BUTTON_UP_PRESS        :
 			case BUTTON_DOWN_PRESS		:
			case BUTTON_LEFT_PRESS		:
			case BUTTON_RIGHT_PRESS		:
    	
    		#if defined(LOCK_KEYPAD_UNDER_WIFI_STREAMING)
    		//any non-wireless event must be filter under streaming
			if(AHC_STREAM_OFF != AHC_GetStreamingMode())
				return AHC_FALSE;
			
			#endif
			
			#if defined(NET_SYNC_PLAYBACK_MODE)
			if( uiGetCurrentState() == UI_NET_PLAYBACK_STATE ||
				(uiGetCurrentState() == UI_TVOUT_STATE && TVFunc_Status() == AHC_TV_NET_PLAYBACK_STATUS) ||
				(uiGetCurrentState() == UI_HDMI_STATE && HDMIFunc_Status() == AHC_HDMI_NET_PLAYBACK_STATUS) )
				return AHC_FALSE;
			#endif
			
				break;
			}
		}
	#endif
		
	if (MenuSettingConfig()->uiBeep == BEEP_ON &&
		MenuSettingConfig()->uiVolume != 0)
    {
        if(VideoFunc_RecordStatus()==AHC_TRUE || VideoFunc_PreRecordStatus()==AHC_TRUE)
            goto L_PowerSave;

        switch( *pulEvent )
        {
        #ifdef NET_SYNC_PLAYBACK_MODE
			case WIRELESS_ENTER_PLAYBACK:
					AHC_PlaySoundEffect(AHC_SOUNDEFFECT_BUTTON);
			break;
			case WIRELESS_EXIT_PLAYBACK :
					AHC_PlaySoundEffect(AHC_SOUNDEFFECT_BUTTON);
			break;
		#endif
            case BUTTON_UP_PRESS:
            case BUTTON_DOWN_PRESS:
            case BUTTON_MENU_PRESS:
            case BUTTON_MODE_PRESS:
            case BUTTON_MUTE_PRESS:
            case BUTTON_POWER_PRESS:
            case BUTTON_MENU_LPRESS:
            case BUTTON_MODE_LPRESS:
            case BUTTON_MUTE_LPRESS:
            case BUTTON_POWER_LPRESS:
			case BUTTON_REC_LPRESS:
			case BUTTON_SET_PRESS:
			case BUTTON_SOS_PRESS:
                AHC_PlaySoundEffect(AHC_SOUNDEFFECT_BUTTON);
            break;

            case BUTTON_REC_PRESS:
			#if (USE_SHUTTER_SOUND)
            	if(uiGetCurrentState()!=UI_CAMERA_STATE)
			#endif
               		AHC_PlaySoundEffect(AHC_SOUNDEFFECT_BUTTON);

                if(uiGetCurrentState()==UI_VIDEO_STATE)
                {
                    UINT8 		ubSoundEffectStatus;
                    UINT32 		wait_cnt=0;

                    do{
                        AHC_GetSoundEffectStatus(&ubSoundEffectStatus);
                        AHC_OS_Sleep(100);
                        if((++wait_cnt) > 50){
                            printc("Warning! AHC_PlaySoundEffect is too long\r\n");
                            wait_cnt = 0;
                        }
                    }while((AHC_SOUND_EFFECT_STATUS_STOP != ubSoundEffectStatus) && (AHC_SOUND_EFFECT_STATUS_INVALID != ubSoundEffectStatus));
                }
            break;

            default:
                //NOP
            break;
        }
    }

L_PowerSave:

    if(	(*pulEvent != BUTTON_NONE)              &&
    	(*pulEvent != BUTTON_UPDATE_MESSAGE)    &&
    	(*pulEvent != BUTTON_BATTERY_DETECTION) &&
    	(*pulEvent != BUTTON_HDMI_REMOVED)      &&
    	(*pulEvent != BUTTON_VRCB_MOTION_DTC)   &&
    	(*pulEvent != BUTTON_UPDATE_CHARGE_ICON))
    {
		AutoPowerOffCounterReset();
    }

    if (MenuSettingConfig()->uiLCDPowerSave != LCD_POWER_SAVE_OFF)
   	{
		switch( *pulEvent )
		{
			//Key Event
			case BUTTON_UP_PRESS:
			case BUTTON_UP_LPRESS:
			case BUTTON_DOWN_PRESS:
			case BUTTON_DOWN_LPRESS:
			case BUTTON_LEFT_PRESS:
			case BUTTON_LEFT_LPRESS:
			case BUTTON_RIGHT_PRESS:
			case BUTTON_RIGHT_LPRESS:
			case BUTTON_REC_PRESS:
			case BUTTON_REC_LPRESS:
			case BUTTON_SET_PRESS:
			case BUTTON_SET_LPRESS:
			case BUTTON_MENU_PRESS:
			case BUTTON_MENU_LPRESS:
			case BUTTON_MODE_PRESS:
			case BUTTON_MODE_LPRESS:
			case BUTTON_MUTE_PRESS:
			case BUTTON_MUTE_LPRESS:
			case BUTTON_POWER_PRESS:
			case BUTTON_POWER_LPRESS:
			case BUTTON_SOS_PRESS:
			case BUTTON_SOS_LPRESS:
			    // Just ignore key event
                if (KEY_POWER_OFF == *pulEvent)
                {
    	        	if(!bForce_PowerOff)
    	        	{
    					if(LedCtrl_GetBacklightStatus()==AHC_FALSE)
    					{
    						if(uiGetCurrentState() != UI_HDMI_STATE && uiGetCurrentState() != UI_TVOUT_STATE)
    						{
    							*pulEvent = BUTTON_NONE;
    						}
    	        		}
    	        	}
                }
                else {
    				if (LedCtrl_GetBacklightStatus()==AHC_FALSE)
    				{
    					if(uiGetCurrentState()!=UI_HDMI_STATE && uiGetCurrentState()!=UI_TVOUT_STATE)
    					{
    						*pulEvent = BUTTON_NONE;
    					}
    				}
                }
            break;
                
			case BUTTON_UP_REL:
			case BUTTON_UP_LREL:
			case BUTTON_DOWN_REL:
			case BUTTON_DOWN_LREL:
			case BUTTON_LEFT_REL:
			case BUTTON_LEFT_LREL:
			case BUTTON_RIGHT_REL:
			case BUTTON_RIGHT_LREL:
			case BUTTON_REC_REL:
			case BUTTON_REC_LREL:
			case BUTTON_SET_REL:
			case BUTTON_SET_LREL:
			case BUTTON_MENU_REL:
			case BUTTON_MENU_LREL:
			case BUTTON_MODE_REL:
			case BUTTON_MODE_LREL:
			case BUTTON_MUTE_REL:
			case BUTTON_MUTE_LREL:
			case BUTTON_POWER_REL:
			case BUTTON_POWER_LREL:
			case BUTTON_SOS_REL:
			case BUTTON_SOS_LREL:
                if (KEY_POWER_OFF == *pulEvent)
                {
    	        	if(!bForce_PowerOff)
    	        	{
    		        	LCDPowerSaveCounterReset();
    					if(LedCtrl_GetBacklightStatus()==AHC_FALSE)
    					{
    						if(uiGetCurrentState()!=UI_HDMI_STATE && uiGetCurrentState()!=UI_TVOUT_STATE)
    						{
    							LedCtrl_LcdBackLight(AHC_TRUE);
    							*pulEvent = BUTTON_NONE;
    						}
    	        		}
    	        	}
                }
                else {
    				LCDPowerSaveCounterReset();
    				if(LedCtrl_GetBacklightStatus()==AHC_FALSE)
    				{
    					if(uiGetCurrentState()!=UI_HDMI_STATE && uiGetCurrentState()!=UI_TVOUT_STATE)
    					{
    						LedCtrl_LcdBackLight(AHC_TRUE);
							if((EVENT_VRCB_MOTION_DTC == (*pulParam)) && ((*pulEvent) == KEY_VIDEO_RECORD))
							{
								#if	MDT_REC_ALWAYS_BACKLIGHT_OFF
								printc("@@turn on backlight and start record!\r\n");
								#else
								m_ubParkingModeRecTrigger = AHC_FALSE;
								*pulEvent = BUTTON_NONE;
								#endif
    						}
							else
							{
								*pulEvent = BUTTON_NONE;
							}
    					}
    				}
                }
			break;

			//Device Event
			case BUTTON_USB_DETECTED:
	        case BUTTON_USB_REMOVED:
			case BUTTON_TV_DETECTED:
	        case BUTTON_TV_REMOVED:
			case BUTTON_HDMI_DETECTED:
	        case BUTTON_HDMI_REMOVED:
			case BUTTON_DC_CABLE_IN:
	        case BUTTON_DC_CABLE_OUT:
            case BUTTON_SD_DETECTED:
            case BUTTON_SD_REMOVED:
#if (UVC_HOST_VIDEO_ENABLE)
            case BUTTON_USB_B_DEVICE_DETECTED:
            case BUTTON_USB_B_DEVICE_REMOVED:
#endif
#if (SUPPORT_DUAL_SNR == 1 && DUALENC_SUPPORT == 1) //For Bitek1603
            case BUTTON_TV_DECODER_SRC_TYPE:
#endif        
	        	LCDPowerSaveCounterReset();
				if(LedCtrl_GetBacklightStatus()==AHC_FALSE)
				{
					if(uiGetCurrentState()!=UI_HDMI_STATE && uiGetCurrentState()!=UI_TVOUT_STATE)
					{
						LedCtrl_LcdBackLight(AHC_TRUE);
					}
				}
			break;

			default:
				//NOP
			break;
		}
   	}

#if (POWER_OFF_CONFIRM_PAGE_EN)

	if(PowerOff_InProcess==AHC_TRUE)
	{
		switch( *pulEvent )
		{
			case BUTTON_UP_PRESS:
				PowerOff_Option = CONFIRM_OPT_YES;
				MenuDrawChangeSubItem_PowerOff();
				printc("LEFT: PowerOff_Option YES\r\n");
				*pulEvent = BUTTON_NONE;
			break;

			case BUTTON_DOWN_PRESS:
				PowerOff_Option = CONFIRM_OPT_NO;
				MenuDrawChangeSubItem_PowerOff();
				printc("RIGHT: PowerOff_Option NO\r\n");
				*pulEvent = BUTTON_NONE;
			break;

			case BUTTON_REC_PRESS:
				printc("OK: PowerOff_Option %s\r\n",(PowerOff_Option)?("NO"):("YES"));
				AHC_PowerOff_Option(PowerOff_Option);
				*pulEvent = BUTTON_NONE;
	        break;

	        case KEY_POWER_OFF:
			#if (POWER_OFF_CONFIRM_PAGE_EN)
	        	if(!bForce_PowerOff)
	        		*pulEvent = BUTTON_NONE;
	        #endif
	        break;

	        //Device Event
            case BUTTON_USB_DETECTED:
            case BUTTON_DC_CABLE_IN:
            case BUTTON_SD_DETECTED:
            case BUTTON_SD_REMOVED:
            case BUTTON_TV_DETECTED:
            case BUTTON_TV_REMOVED:
            case BUTTON_HDMI_DETECTED:
            case BUTTON_HDMI_REMOVED:
            case BUTTON_COVER_OPEN:
            case BUTTON_COVER_CLOSED:
            case BUTTON_BATTERY_DETECTION:
            case BUTTON_UPDATE_MESSAGE:
				//NOP
	        break;

	        case BUTTON_DC_CABLE_OUT:
	        case BUTTON_USB_REMOVED:
	        	AHC_SetChargerEnable(AHC_FALSE);
	        	#if (CHARGER_OUT_ACT_OTHER_MODE==ACT_FORCE_POWER_OFF || CHARGER_OUT_ACT_OTHER_MODE==ACT_DELAY_POWER_OFF)
				AHC_SetShutdownByChargerOut(AHC_TRUE);
				#endif
	        break;

	        case BUTTON_LCD_NORMAL:
	        	AHC_DrawMenuRotateEvent(MENU_LCD_NORMAL, NULL);
	        	*pulEvent = BUTTON_NONE;
	        break;

	        case BUTTON_LCD_ROTATE:
	        	AHC_DrawMenuRotateEvent(MENU_LCD_ROTATE, NULL);
	        	*pulEvent = BUTTON_NONE;
	        break;
#if (UVC_HOST_VIDEO_ENABLE)
            case BUTTON_USB_B_DEVICE_DETECTED:
                printc("BUTTON_USB_B_DEVICE_DETECTED,%s,%d\r\n", __func__, __LINE__);
                break;
            case BUTTON_USB_B_DEVICE_REMOVED:
                printc("BUTTON_USB_B_DEVICE_REMOVED,%s,%d\r\n", __func__, __LINE__);
                break;
#endif
#if (SUPPORT_DUAL_SNR == 1 && DUALENC_SUPPORT == 1) //For Bitek1603
            case BUTTON_TV_DECODER_SRC_TYPE:
                printc("BUTTON_TV_DECODER_SRC_TYPE,%s,%d\r\n", __func__, __LINE__);
                break;        
#endif        
	        default:
	        	*pulEvent = BUTTON_NONE;
	        break;
		}
	}
#endif

	if(Deleting_InBrowser || Protecting_InBrowser)
	{
		switch( *pulEvent )
		{
		#if (SUPPORT_TOUCH_PANEL)
			case BUTTON_TOUCH_PRESS:
		#endif
			case BUTTON_UP_PRESS:
			case BUTTON_DOWN_PRESS:
			case BUTTON_REC_PRESS:
			case BUTTON_MENU_REL:
			case BUTTON_SET_PRESS:
			case BUTTON_SET_LPRESS:
				//NOP
			break;

			case BUTTON_MODE_REL:
				if(Delete_File_Confirm || Protect_File_Confirm || UnProtect_File_Confirm)
					*pulEvent = BUTTON_NONE;
			break;

			case KEY_POWER_OFF:
			#if (POWER_OFF_CONFIRM_PAGE_EN)
	        	if(!bForce_PowerOff)
	        		*pulEvent = BUTTON_NONE;
	        #endif
	        break;

			//Device Event
			case BUTTON_USB_DETECTED:
			case BUTTON_DC_CABLE_IN:
			case BUTTON_SD_DETECTED:
			case BUTTON_SD_REMOVED:
			case BUTTON_TV_DETECTED:
			case BUTTON_TV_REMOVED:
			case BUTTON_HDMI_DETECTED:
			case BUTTON_HDMI_REMOVED:
			case BUTTON_COVER_OPEN:
			case BUTTON_COVER_CLOSED:
			case BUTTON_BATTERY_DETECTION:
			case BUTTON_UPDATE_MESSAGE:
				//NOP
				break;

	        case BUTTON_DC_CABLE_OUT:
	        case BUTTON_USB_REMOVED:
	        	AHC_SetChargerEnable(AHC_FALSE);
				#if (CHARGER_OUT_ACT_OTHER_MODE==ACT_FORCE_POWER_OFF || CHARGER_OUT_ACT_OTHER_MODE==ACT_DELAY_POWER_OFF)
				AHC_SetShutdownByChargerOut(AHC_TRUE);
				#endif
	        break;

	        case BUTTON_LCD_NORMAL:
	        	AHC_DrawMenuRotateEvent(MENU_LCD_NORMAL, NULL);
	        	*pulEvent = BUTTON_NONE;
	        break;

	        case BUTTON_LCD_ROTATE:
	        	AHC_DrawMenuRotateEvent(MENU_LCD_ROTATE, NULL);
	        	*pulEvent = BUTTON_NONE;
	        break;
#if (UVC_HOST_VIDEO_ENABLE)
                case BUTTON_USB_B_DEVICE_DETECTED:
                    printc("BUTTON_USB_B_DEVICE_DETECTED,%s,%d\r\n", __func__, __LINE__);
                    break;
                case BUTTON_USB_B_DEVICE_REMOVED:
                    printc("BUTTON_USB_B_DEVICE_REMOVED,%s,%d\r\n", __func__, __LINE__);
                    break;
#endif
#if (SUPPORT_DUAL_SNR == 1 && DUALENC_SUPPORT == 1) //For Bitek1603
                case BUTTON_TV_DECODER_SRC_TYPE:
                    printc("BUTTON_TV_DECODER_SRC_TYPE,%s,%d\r\n", __func__, __LINE__);
                    break;        
#endif        
			default:
				*pulEvent = BUTTON_NONE;
			break;
		}
	}
	
	if(!IN_MENU())
	{
		#if defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_WIFI_ON_UNDER_VIDEO_MODE_ONLY)
		{
			UINT8    wifi_switch_on;

			switch (uiGetCurrentState()) {
			//////////////////////////////////////////////////////////
			case UI_VIDEO_STATE:
				wifi_switch_on = AHC_TRUE;
				break;

			//////////////////////////////////////////////////////////
			#if (TVOUT_ENABLE)
			case UI_TVOUT_STATE:
				#if (TVOUT_PREVIEW_EN)
				if (TVFunc_Status() == AHC_TV_VIDEO_PREVIEW_STATUS)
				{
					wifi_switch_on = AHC_TRUE;
				}
				else
				#endif
				{
					wifi_switch_on = AHC_FALSE;
				}
				break;
			#endif

			#if (HDMI_ENABLE)
			case UI_HDMI_STATE:
				#if (HDMI_PREVIEW_EN)
				if (TVFunc_Status() == AHC_TV_VIDEO_PREVIEW_STATUS)
				{
					wifi_switch_on = AHC_TRUE;
				}
				else
				#endif
				{
					wifi_switch_on = AHC_FALSE;
				}
				break;
			#endif

			//////////////////////////////////////////////////////////
			default:
				wifi_switch_on = AHC_FALSE;
				break;
			}

        	AHC_WiFi_Switch(wifi_switch_on);
		}
		#endif
	}

#if (POWER_ON_BY_GSENSOR_EN) && defined(GSENSOR_INT)
    if(	(*pulEvent == BUTTON_POWER_PRESS)       ||
    	(*pulEvent == BUTTON_MODE_PRESS)        ||
    	(*pulEvent == BUTTON_MENU_PRESS)        ||
    	(*pulEvent == BUTTON_UP_PRESS)          ||
    	(*pulEvent == BUTTON_DOWN_PRESS)        ||
    	(*pulEvent == BUTTON_LEFT_PRESS)        ||
    	(*pulEvent == BUTTON_RIGHT_PRESS)       ||
    	(*pulEvent == BUTTON_REC_PRESS) )
    {
        extern AHC_BOOL	ubGsnrPwrOnActStart;

    	if (AHC_TRUE == ubGsnrPwrOnActStart)
    	{
    	    RTNA_DBG_Str(0, FG_GREEN("Cancel G-Sensor Power-On State, retrun normal VR\r\n"));
    	    ubGsnrPwrOnActStart = AHC_FALSE;
        }
    }
#endif

    if (WMSG_LAYER_WINDOW_ID == OSD_LAYER_WINDOW_ID) {
        // The warning message layer and the OSD layer window is shared.
        if (AHC_WMSG_GetInfo() != WMSG_NONE) {
            if (BUTTON_UPDATE_MESSAGE == *pulEvent) {
                *pulEvent = BUTTON_NONE;
                return AHC_FALSE;
            }
        }
    }

    return AHC_TRUE;
}
