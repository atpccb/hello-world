/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "Customer_Config.h"
#include "config_fw.h"

#include "dsc_key.h"
#include "AHC_Message.h"
#include "AHC_Menu.h"
#include "AHC_General.h"
#include "AHC_Parameter.h"
#include "AHC_Warningmsg.h"
#include "AHC_Media.h"
#include "AHC_Display.h"
#include "AHC_OS.h"
#include "AHC_General.h"
#include "AHC_Video.h"
#include "AHC_FS.h"
#include "AHC_Config_SDK.h"
#include "AHC_USB.h"
#if (UVC_HOST_VIDEO_ENABLE )
#include "AHC_USBHost.h"
#endif
#include "AHC_GSensor.h"
#include "AHC_PMU.h"
#include "AHC_SARADC.h"
#include "dsc_charger.h"
#include "UartShell.h"
#include "mmpf_timer.h"
#include "mmps_vidplay.h"
#include "mmps_3gprecd.h"
#include "mmph_hif.h"
#include "mmpf_pio.h"
#include "mmpf_i2cm.h"
#include "mmpf_rtc.h"
#include "mmpf_SARADC.h"
#include "mmpf_saradc.h"
#include "MenuSetting.h"
#include "StateHDMIfunc.h"
#include "StateTVfunc.h"
#include "StateVideoFunc.h"
#include "LedControl.h"
#include "PMUCtrl.h"
#include "MediaPlaybackCtrl.h"
#include "lib_retina.h"
#include "Mmpf_system.h" //For task monitor //CarDV...

#if (SUPPORT_GSENSOR) 
#include "GSensor_ctrl.h"
#endif
#if (SUPPORT_IR_CONVERTER)
#include "IR_Ctrl.h"
#endif
#if (SUPPORT_TOUCH_PANEL) 
#include "AHC_TouchPanel.h"
#endif
#if (GPS_CONNECT_ENABLE)
#include "GPS_ctl.h"
#endif

// for NETWORK
#if defined(WIFI_PORT) && (WIFI_PORT == 1)
#include "wlan.h"
#include "netapp.h"
#endif

// For CDV
#define	CDV_KEYPAD_FLAG		0x00000001
#define	CDV_TIME_FLAG		0x00000002
#if (UPDATE_UI_USE_MULTI_TASK)
#define	CDV_UI_FLAG			0x00000004
#endif

AHC_BOOL VideoFunc_LockFileEnabled(void);

/*===========================================================================
 * Global varible : ADC Key
 *===========================================================================*/

#if(ADC_KEY_EN==1) 

SADCBUTTON sADCButton[] =
{
#if 1	
    {KEY_PRESS_UP, 		KEY_REL_UP, 	KEY_LPRESS_UP, 		KEY_LREL_UP,		ADC_KEY_VOLT_U, 		ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_U, 		ADC_STATE_ID_D,			0, KEYFLAG_UP,		"ADC_UP"},
    {KEY_PRESS_DOWN, 	KEY_REL_DOWN, 	KEY_LPRESS_DOWN, 	KEY_LREL_DOWN ,		ADC_KEY_VOLT_D, 		ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_D, 		ADC_STATE_ID_U,			0, KEYFLAG_DOWN,	"ADC_DOWN"},
    {KEY_PRESS_LEFT, 	KEY_REL_LEFT, 	KEY_LPRESS_LEFT, 	KEY_LREL_LEFT ,		ADC_KEY_VOLT_L, 		ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_L, 		ADC_STATE_ID_R,			0, KEYFLAG_LEFT,	"ADC_LEFT"},
    {KEY_PRESS_RIGHT, 	KEY_REL_RIGHT, 	KEY_LPRESS_RIGHT, 	KEY_LREL_RIGHT,		ADC_KEY_VOLT_R, 		ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_R, 		ADC_STATE_ID_L,			0, KEYFLAG_RIGHT,	"ADC_RIGHT"},
    {KEY_PRESS_OK, 		KEY_REL_OK, 	KEY_LPRESS_OK, 		KEY_LREL_OK, 		ADC_KEY_VOLT_ENTER, 	ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_ENTER,	ADC_STATE_ID_INVALID, 	0, KEYFLAG_OK,		"ADC_ENTER"},
	#if (MORE_ADC_KEY==1)
    {KEY_PRESS_REC, 	KEY_REL_REC, 	KEY_LPRESS_REC, 	KEY_LREL_REC,		ADC_KEY_VOLT_REC, 		ADC_KEY_VOLT_MARGIN_REC, ADC_STATE_ID_REC, 		ADC_STATE_ID_INVALID,	0, KEYFLAG_REC,		"ADC_REC"},
    {KEY_PRESS_MENU, 	KEY_REL_MENU, 	KEY_LPRESS_MENU, 	KEY_LREL_MENU,		ADC_KEY_VOLT_MENU, 		ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_MENU, 	ADC_STATE_ID_INVALID,	0, KEYFLAG_MENU,	"ADC_MENU"},
    {KEY_PRESS_PLAY, 	KEY_REL_PLAY, 	KEY_LPRESS_PLAY, 	KEY_LREL_PLAY,		ADC_KEY_VOLT_PLAY, 		ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_PLAY, 	ADC_STATE_ID_INVALID,	0, KEYFLAG_PLAY,	"ADC_PLAY"},
    {KEY_PRESS_MODE, 	KEY_REL_MODE, 	KEY_LPRESS_MODE, 	KEY_LREL_MODE,		ADC_KEY_VOLT_MODE, 		ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_MODE, 	ADC_STATE_ID_INVALID,	0, KEYFLAG_MODE,	"ADC_MODE"},
    {KEY_PRESS_SOS, 	KEY_REL_SOS, 	KEY_LPRESS_SOS, 	KEY_LREL_SOS, 		ADC_KEY_VOLT_SOS, 		ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_SOS,		ADC_STATE_ID_INVALID, 	0, KEYFLAG_SOS,		"ADC_SOS"},
    {KEY_PRESS_MUTE, 	KEY_REL_MUTE, 	KEY_LPRESS_MUTE, 	KEY_LREL_MUTE, 		ADC_KEY_VOLT_MUTE, 		ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_MUTE,		ADC_STATE_ID_INVALID, 	0, KEYFLAG_MUTE,	"ADC_MUTE"},
    {KEY_PRESS_CAPTURE, KEY_REL_CAPTURE,KEY_LPRESS_CAPTURE, KEY_LREL_CAPTURE, 	ADC_KEY_VOLT_CAPTURE, 	ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_CAPTURE,	ADC_STATE_ID_INVALID, 	0, KEYFLAG_CAPTURE,	"ADC_CAPTURE"},
    {KEY_PRESS_FUNC1, 	KEY_REL_FUNC1, 	KEY_LPRESS_FUNC1, 	KEY_LREL_FUNC1, 	ADC_KEY_VOLT_FUNC1, 	ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_FUNC1,	ADC_STATE_ID_INVALID, 	0, KEYFLAG_FUNC1,	"ADC_FUNC1"},
    {KEY_PRESS_FUNC2, 	KEY_REL_FUNC2, 	KEY_LPRESS_FUNC2, 	KEY_LREL_FUNC2, 	ADC_KEY_VOLT_FUNC2, 	ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_FUNC2,	ADC_STATE_ID_INVALID, 	0, KEYFLAG_FUNC2,	"ADC_FUNC2"},
    {KEY_PRESS_FUNC3, 	KEY_REL_FUNC3, 	KEY_LPRESS_FUNC3, 	KEY_LREL_FUNC3, 	ADC_KEY_VOLT_FUNC3, 	ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_FUNC2,	ADC_STATE_ID_INVALID, 	0, KEYFLAG_FUNC3,	"ADC_FUNC3"},    
	#endif
#else //For BiTeck TV Decoder testing
    {KEY_PRESS_UP, 		KEY_REL_UP, 	KEY_LPRESS_UP, 		KEY_LREL_UP,		ADC_KEY_VOLT_U, 		ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_U, 		ADC_STATE_ID_D,			0, KEYFLAG_UP,		"ADC_UP"},
    {KEY_PRESS_DOWN, 	KEY_REL_DOWN, 	KEY_LPRESS_DOWN, 	KEY_LREL_DOWN ,		ADC_KEY_VOLT_D, 		ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_D, 		ADC_STATE_ID_U,			0, KEYFLAG_DOWN,	"ADC_DOWN"},
    {KEY_PRESS_LEFT, 	KEY_REL_LEFT, 	KEY_LPRESS_LEFT, 	KEY_LREL_LEFT ,		ADC_KEY_VOLT_L, 		ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_L, 		ADC_STATE_ID_INVALID,	0, KEYFLAG_LEFT,	"ADC_LEFT"},
    {KEY_PRESS_RIGHT, 	KEY_REL_RIGHT, 	KEY_LPRESS_RIGHT, 	KEY_LREL_RIGHT,		ADC_KEY_VOLT_R, 		ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_R, 		ADC_STATE_ID_INVALID,	0, KEYFLAG_RIGHT,	"ADC_RIGHT"},
    {KEY_PRESS_OK, 		KEY_REL_OK, 	KEY_LPRESS_OK, 		KEY_LREL_OK, 		ADC_KEY_VOLT_ENTER, 	ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_ENTER,	ADC_STATE_ID_INVALID, 	0, KEYFLAG_OK,		"ADC_ENTER"},
    {KEY_PRESS_REC, 	KEY_REL_REC, 	KEY_LPRESS_REC, 	KEY_LREL_REC,		ADC_KEY_VOLT_REC, 		ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_REC, 		ADC_STATE_ID_REC,	    0, KEYFLAG_REC,		"ADC_REC"},
    {KEY_PRESS_MENU, 	KEY_REL_MENU, 	KEY_LPRESS_MENU, 	KEY_LREL_MENU,		ADC_KEY_VOLT_MENU, 		ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_MENU, 	ADC_STATE_ID_MENU,	    0, KEYFLAG_MENU,	"ADC_MENU"},
    {KEY_PRESS_PLAY, 	KEY_REL_PLAY, 	KEY_LPRESS_PLAY, 	KEY_LREL_PLAY,		ADC_KEY_VOLT_PLAY, 		ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_PLAY, 	ADC_STATE_ID_INVALID,	0, KEYFLAG_PLAY,	"ADC_PLAY"},
    {KEY_PRESS_MODE, 	KEY_REL_MODE, 	KEY_LPRESS_MODE, 	KEY_LREL_MODE,		ADC_KEY_VOLT_MODE, 		ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_MODE, 	ADC_STATE_ID_MODE,	    0, KEYFLAG_MODE,	"ADC_MODE"},
    {KEY_PRESS_SOS, 	KEY_REL_SOS, 	KEY_LPRESS_SOS, 	KEY_LREL_SOS, 		ADC_KEY_VOLT_SOS, 		ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_SOS,		ADC_STATE_ID_INVALID, 	0, KEYFLAG_SOS,		"ADC_SOS"},
    {KEY_PRESS_MUTE, 	KEY_REL_MUTE, 	KEY_LPRESS_MUTE, 	KEY_LREL_MUTE, 		ADC_KEY_VOLT_MUTE, 		ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_MUTE,		ADC_STATE_ID_INVALID, 	0, KEYFLAG_MUTE,	"ADC_MUTE"},
    {KEY_PRESS_CAPTURE, KEY_REL_CAPTURE,KEY_LPRESS_CAPTURE, KEY_LREL_CAPTURE, 	ADC_KEY_VOLT_CAPTURE, 	ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_CAPTURE,	ADC_STATE_ID_INVALID, 	0, KEYFLAG_CAPTURE,	"ADC_CAPTURE"},
    {KEY_PRESS_FUNC1, 	KEY_REL_FUNC1, 	KEY_LPRESS_FUNC1, 	KEY_LREL_FUNC1, 	ADC_KEY_VOLT_FUNC1, 	ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_FUNC1,	ADC_STATE_ID_INVALID, 	0, KEYFLAG_FUNC1,	"ADC_FUNC1"},
    {KEY_PRESS_FUNC2, 	KEY_REL_FUNC2, 	KEY_LPRESS_FUNC2, 	KEY_LREL_FUNC2, 	ADC_KEY_VOLT_FUNC2, 	ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_FUNC2,	ADC_STATE_ID_INVALID, 	0, KEYFLAG_FUNC2,	"ADC_FUNC2"},
    {KEY_PRESS_FUNC3, 	KEY_REL_FUNC3, 	KEY_LPRESS_FUNC3, 	KEY_LREL_FUNC3, 	ADC_KEY_VOLT_FUNC3, 	ADC_KEY_VOLT_MARGIN, ADC_STATE_ID_FUNC2,	ADC_STATE_ID_INVALID, 	0, KEYFLAG_FUNC3,	"ADC_FUNC3"},    
#endif
};

static MMP_ULONG	gNumOfADCKey 	    = sizeof(sADCButton) / sizeof(SADCBUTTON);
static MMP_UBYTE 	gADCKeyStatus 	    = ADCPRESS_MAX;
static MMP_USHORT 	gADCKeyPressCnt     = 0;
static MMP_UBYTE	gADCKeyLongPress 	= MMP_FALSE;
#endif		// #if(ADC_KEY_EN==1) 

/*===========================================================================
 * Global varible : Battery Measure
 *===========================================================================*/

static MMP_ULONG 	uBatteryDetectCounter 	= 0;
static MMP_ULONG 	uVoltageLevelSum	   	= 0; 
static MMP_UBYTE 	uSkipDetectNum   		= (0xFF - 0x04); 

/*===========================================================================
 * Global variable : IR Key
 *===========================================================================*/

#if(IR_KEY_EN==1) 
#ifndef	_OEM_IR_KEY_
/* In case OEM_IR_KEY enabled in Config_xxx.h, the sIRButton is defined in Oem_Key_xxx.c
 */
SIRBUTTON sIRButton[] =
{
//   iPressId            iReleaseId          iLongPressId        iLongReleaseId      ulKeyValue          ubKeyStateId            ubKeyPairId    ubKeyCount ubPressStatus ubkeyname
    {KEY_PRESS_UP, 		KEY_REL_UP, 		KEY_LPRESS_UP, 		KEY_LREL_UP,		IR_VALUE_U, 		IR_STATE_ID_U, 			IR_STATE_ID_D,			0,			0,	"IR_UP"},
    {KEY_PRESS_DOWN, 	KEY_REL_DOWN, 		KEY_LPRESS_DOWN, 	KEY_LREL_DOWN,		IR_VALUE_D, 		IR_STATE_ID_D, 			IR_STATE_ID_U,			0,			0,	"IR_DOWN"},
    {KEY_PRESS_LEFT, 	KEY_REL_LEFT, 		KEY_LPRESS_LEFT, 	KEY_LREL_LEFT,		IR_VALUE_L, 		IR_STATE_ID_L, 			IR_STATE_ID_R,			0,			0,	"IR_LEFT"},
    {KEY_PRESS_RIGHT, 	KEY_REL_RIGHT, 		KEY_LPRESS_RIGHT, 	KEY_LREL_RIGHT,		IR_VALUE_R, 		IR_STATE_ID_R, 			IR_STATE_ID_L,			0,			0,	"IR_RIGHT"},
    {KEY_PRESS_OK, 		KEY_REL_OK, 		KEY_LPRESS_OK, 		KEY_LREL_OK, 		IR_VALUE_ENTER, 	IR_STATE_ID_ENTER,		IR_STATE_ID_INVALID, 	0,			0,	"IR_ENTER"},
    {KEY_PRESS_REC, 	KEY_REL_REC, 		KEY_LPRESS_REC, 	KEY_LREL_REC,		IR_VALUE_REC, 		IR_STATE_ID_REC, 		IR_STATE_ID_INVALID,	0,			0,	"IR_REC"},
    {KEY_PRESS_MENU, 	KEY_REL_MENU, 		KEY_LPRESS_MENU, 	KEY_LREL_MENU,		IR_VALUE_MENU, 		IR_STATE_ID_MENU,		IR_STATE_ID_INVALID,	0,			0,	"IR_MENU"},
    {KEY_PRESS_PLAY, 	KEY_REL_PLAY, 		KEY_LPRESS_PLAY, 	KEY_LREL_PLAY,		IR_VALUE_PLAY, 		IR_STATE_ID_PLAY,		IR_STATE_ID_INVALID,	0,			0,	"IR_PLAY"},
    {KEY_PRESS_MODE, 	KEY_REL_MODE, 		KEY_LPRESS_MODE, 	KEY_LREL_MODE,		IR_VALUE_MODE, 		IR_STATE_ID_MODE, 		IR_STATE_ID_INVALID,	0,			0,	"IR_MODE"},
    {KEY_PRESS_SOS, 	KEY_REL_SOS, 		KEY_LPRESS_SOS, 	KEY_LREL_SOS, 		IR_VALUE_SOS, 		IR_STATE_ID_SOS,		IR_STATE_ID_INVALID, 	0,			0,	"IR_SOS"},
    {KEY_PRESS_MUTE, 	KEY_REL_MUTE, 		KEY_LPRESS_MUTE, 	KEY_LREL_MUTE, 		IR_VALUE_MUTE,		IR_STATE_ID_MUTE,		IR_STATE_ID_INVALID, 	0,			0,	"IR_MUTE"},
	{KEY_PRESS_CAPTURE, KEY_REL_CAPTURE, 	KEY_LPRESS_CAPTURE, KEY_LREL_CAPTURE, 	IR_VALUE_CAPTURE,	IR_STATE_ID_CAPTURE,	IR_STATE_ID_INVALID, 	0,			0,	"IR_CAPTURE"},
	{KEY_PRESS_TELE, 	KEY_REL_TELE, 		KEY_LPRESS_TELE, 	KEY_LREL_TELE, 		IR_VALUE_TELE,		IR_STATE_ID_TELE,		IR_STATE_ID_INVALID, 	0,			0,	"IR_ZOOMIN"},
	{KEY_PRESS_WIDE, 	KEY_REL_WIDE, 		KEY_LPRESS_WIDE, 	KEY_LREL_WIDE, 		IR_VALUE_WIDE,		IR_STATE_ID_WIDE,		IR_STATE_ID_INVALID, 	0,			0,	"IR_ZOOMOUT"},
	{KEY_PRESS_FUNC1, 	KEY_REL_FUNC1, 		KEY_LPRESS_FUNC1, 	KEY_LREL_FUNC1, 	IR_VALUE_FUNC1,		IR_STATE_ID_FUNC1,		IR_STATE_ID_INVALID, 	0,			0,	"IR_FUNC1"},
	{KEY_PRESS_FUNC2, 	KEY_REL_FUNC2, 		KEY_LPRESS_FUNC2, 	KEY_LREL_FUNC2, 	IR_VALUE_FUNC2,		IR_STATE_ID_FUNC2,		IR_STATE_ID_INVALID, 	0,			0,	"IR_FUNC2"},
	{KEY_PRESS_FUNC3, 	KEY_REL_FUNC3, 		KEY_LPRESS_FUNC3, 	KEY_LREL_FUNC3, 	IR_VALUE_FUNC3,		IR_STATE_ID_FUNC3,		IR_STATE_ID_INVALID, 	0,			0,	"IR_FUNC3"},
	{KEY_PRESS_POWER, 	KEY_REL_POWER,		KEY_LPRESS_POWER, 	KEY_LREL_POWER, 	IR_VALUE_POWER,		IR_STATE_ID_POWER,		IR_STATE_ID_INVALID, 	0,			0,	"IR_POWER"},
};

#define	NUM_IR_KEY	(sizeof(sIRButton) / sizeof(SIRBUTTON))

#else
// Declare in Oem_Key_xxx.c
extern SIRBUTTON sIRButton[];
extern int			_irNumKey;
#define	NUM_IR_KEY	_irNumKey
#endif
#endif

/*===========================================================================
 * Global variable : GPIO Key/Device
 *===========================================================================*/

#define	INVALID_KV		        	(0xFF)

SGPIOBUTTON sButton[] =
{
//	iPressId			iReleaseId			iLongPressId		iLongReleaseId		piopin		ulKeyLastTime	ulContinuousTime		ulPressLevel			ulKeyLastValue			ulKeyCount	ubKeyStateId	ubKeyPairId			ulKeyFlag			ubkeyname[16]	ubLPRepeatTime															ubkeyname	ubLPRepeatEn
//																										ulDebounceTime																			ubLongPress																ubLPRepeatEn
    {KEY_PRESS_REC, 	KEY_REL_REC, 		KEY_LPRESS_REC, 	KEY_LREL_REC,		KEY_GPIO_REC, 		0, 30, KEY_LPRESS_TIME_REC, 	KEY_PRESSLEVEL_REC,  	KEY_PRESSLEVEL_REC^1,  		0, 0, 	GPIOID_REC,   	KEY_GPIO_ID_INVALID, KEYFLAG_REC, 		"REC",		0,	0},
    {KEY_PRESS_MENU, 	KEY_REL_MENU, 		KEY_LPRESS_MENU, 	KEY_LREL_MENU,		KEY_GPIO_MENU, 		0, 30, KEY_LPRESS_TIME_MENU, 	KEY_PRESSLEVEL_MENU, 	KEY_PRESSLEVEL_MENU^1, 		0, 0, 	GPIOID_MENU,  	KEY_GPIO_ID_INVALID, KEYFLAG_MENU, 		"MENU",		0,	0},
    {KEY_PRESS_PLAY, 	KEY_REL_PLAY, 		KEY_LPRESS_PLAY, 	KEY_LREL_PLAY,		KEY_GPIO_PLAY, 		0, 30, KEY_LPRESS_TIME_PLAY, 	KEY_PRESSLEVEL_PLAY, 	KEY_PRESSLEVEL_PLAY^1, 		0, 0, 	GPIOID_PLAY,  	KEY_GPIO_ID_INVALID, KEYFLAG_PLAY,		"PLAY",		0,	0},
    {KEY_PRESS_MODE, 	KEY_REL_MODE, 		KEY_LPRESS_MODE, 	KEY_LREL_MODE,		KEY_GPIO_MODE, 		0, 30, KEY_LPRESS_TIME_MODE, 	KEY_PRESSLEVEL_MODE, 	KEY_PRESSLEVEL_MODE^1, 		0, 0, 	GPIOID_MODE,  	KEY_GPIO_ID_INVALID, KEYFLAG_MODE,		"MODE",		0,	0},
    {KEY_PRESS_POWER, 	KEY_REL_POWER, 		KEY_LPRESS_POWER, 	KEY_LREL_POWER, 	KEY_GPIO_POWER, 	0, 30, KEY_LPRESS_TIME_POWER, 	KEY_PRESSLEVEL_POWER, 	KEY_PRESSLEVEL_POWER^1, 	0, 0,	GPIOID_POWER, 	KEY_GPIO_ID_INVALID, KEYFLAG_POWER,		"POWER",	1,	1},

#if (MORE_GPIO_KEY==1)
    {KEY_PRESS_UP, 		KEY_REL_UP, 		KEY_LPRESS_UP, 		KEY_LREL_UP,		KEY_GPIO_UP, 		0, 30, KEY_LPRESS_TIME_UP,		KEY_PRESSLEVEL_UP, 		KEY_PRESSLEVEL_UP^1, 		0, 0, 	GPIOID_UP,    	GPIOID_DOWN, 	 	 KEYFLAG_UP,		"UP",		1,	1},
    {KEY_PRESS_DOWN, 	KEY_REL_DOWN, 		KEY_LPRESS_DOWN, 	KEY_LREL_DOWN,		KEY_GPIO_DOWN, 		0, 30, KEY_LPRESS_TIME_DOWN, 	KEY_PRESSLEVEL_DOWN, 	KEY_PRESSLEVEL_DOWN^1, 		0, 0, 	GPIOID_DOWN,  	GPIOID_UP,      	 KEYFLAG_DOWN,		"DOWN",		1,	1},
    {KEY_PRESS_LEFT, 	KEY_REL_LEFT, 		KEY_LPRESS_LEFT, 	KEY_LREL_LEFT,		KEY_GPIO_LEFT, 		0, 30, KEY_LPRESS_TIME_LEFT, 	KEY_PRESSLEVEL_LEFT, 	KEY_PRESSLEVEL_LEFT^1, 		0, 0, 	GPIOID_LEFT, 	GPIOID_RIGHT,   	 KEYFLAG_LEFT,		"LEFT",		1,	1},
    {KEY_PRESS_RIGHT, 	KEY_REL_RIGHT, 		KEY_LPRESS_RIGHT, 	KEY_LREL_RIGHT,		KEY_GPIO_RIGHT, 	0, 30, KEY_LPRESS_TIME_RIGHT, 	KEY_PRESSLEVEL_RIGHT, 	KEY_PRESSLEVEL_RIGHT^1, 	0, 0, 	GPIOID_RIGHT, 	GPIOID_LEFT,    	 KEYFLAG_RIGHT,		"RIGHT",	1,	1},
    {KEY_PRESS_OK, 		KEY_REL_OK, 		KEY_LPRESS_OK, 		KEY_LREL_OK,		KEY_GPIO_OK, 		0, 30, KEY_LPRESS_TIME_OK,		KEY_PRESSLEVEL_OK, 		KEY_PRESSLEVEL_OK^1, 		0, 0, 	GPIOID_OK,    	KEY_GPIO_ID_INVALID, KEYFLAG_OK,		"OK",		0,	0},
	{KEY_PRESS_SOS, 	KEY_REL_SOS, 		KEY_LPRESS_SOS, 	KEY_LREL_SOS,		KEY_GPIO_SOS, 		0, 30, KEY_LPRESS_TIME_SOS, 	KEY_PRESSLEVEL_SOS, 	KEY_PRESSLEVEL_SOS^1, 		0, 0, 	GPIOID_SOS, 	KEY_GPIO_ID_INVALID, KEYFLAG_SOS,		"SOS",		0,	0},
	{KEY_PRESS_MUTE, 	KEY_REL_MUTE, 		KEY_LPRESS_MUTE, 	KEY_LREL_MUTE,		KEY_GPIO_MUTE, 		0, 30, KEY_LPRESS_TIME_MUTE, 	KEY_PRESSLEVEL_MUTE, 	KEY_PRESSLEVEL_MUTE^1, 		0, 0, 	GPIOID_MUTE, 	KEY_GPIO_ID_INVALID, KEYFLAG_MUTE,		"MUTE",		0,	0},
    {KEY_PRESS_CAPTURE, KEY_REL_CAPTURE, 	KEY_LPRESS_CAPTURE, KEY_LREL_CAPTURE,	KEY_GPIO_CAPTURE, 	0, 30, KEY_LPRESS_TIME_CAPTURE, KEY_PRESSLEVEL_CAPTURE, KEY_PRESSLEVEL_CAPTURE^1,	0, 0, 	GPIOID_CAPTURE, KEY_GPIO_ID_INVALID, KEYFLAG_CAPTURE,	"CAPTURE",	0,	0},
    {KEY_PRESS_FUNC1, 	KEY_REL_FUNC1, 		KEY_LPRESS_FUNC1, 	KEY_LREL_FUNC1,		KEY_GPIO_FUNC1, 	0, 30, KEY_LPRESS_TIME_FUNC1, 	KEY_PRESSLEVEL_FUNC1, 	KEY_PRESSLEVEL_FUNC1^1, 	0, 0, 	GPIOID_FUNC1, 	KEY_GPIO_ID_INVALID, KEYFLAG_FUNC1,		"FUNC1",	0,	0},
    {KEY_PRESS_FUNC2, 	KEY_REL_FUNC2, 		KEY_LPRESS_FUNC2, 	KEY_LREL_FUNC2,		KEY_GPIO_FUNC2, 	0, 30, KEY_LPRESS_TIME_FUNC2, 	KEY_PRESSLEVEL_FUNC2, 	KEY_PRESSLEVEL_FUNC2^1, 	0, 0, 	GPIOID_FUNC2, 	KEY_GPIO_ID_INVALID, KEYFLAG_FUNC2,		"FUNC2",	0,	0},
    {KEY_PRESS_FUNC3, 	KEY_REL_FUNC3, 		KEY_LPRESS_FUNC3, 	KEY_LREL_FUNC3,		KEY_GPIO_FUNC3, 	0, 30, KEY_LPRESS_TIME_FUNC3, 	KEY_PRESSLEVEL_FUNC3, 	KEY_PRESSLEVEL_FUNC3^1, 	0, 0, 	GPIOID_FUNC3, 	KEY_GPIO_ID_INVALID, KEYFLAG_FUNC3,		"FUNC3",	0,	0},
#endif
#if (SUPPORT_TOUCH_PANEL && defined(TOUCH_PANEL_INT_GPIO))
    #if (DSC_TOUCH_PANEL != TOUCH_PANEL_FT6X36)
	{TOUCH_PANEL_PRESS, TOUCH_PANEL_REL,    TOUCH_PANEL_MOVE,   TOUCH_PANEL_REL, TOUCH_PANEL_INT_GPIO,  0, 120,                  100,   KEY_PRESSLEVEL_TOUCH,   KEY_PRESSLEVEL_TOUCH^1, 	0, 0, 	GPIOID_TOUCH, 	KEY_GPIO_ID_INVALID, KEYFLAG_DUMMY,     "TOUCH",	0,	0}
    #endif
#endif
};

SGPIOBUTTON sDeviceStatus[] =
{
   //                                                                                                       ulContinuousTime   ulKeyLastValue     ubKeyStateId  
   //                                                                                                  ulDebounceTime;      ulPressLevel;      ubLongPress; 
   //iPressId;           iReleaseId;         iLongPressId;  iLongReleaseId; piopin;                 ulKeyLastTime;                          ubKeyCount;             ubKeyPairId;         ulKeyFlag      ubkeyname[16]
#if (DETECT_SD_BY_TIMER==0) 
    {SD_CARD_IN	 	,  	 SD_CARD_OUT, 	   	 KEYPAD_NONE,	KEYPAD_NONE, 	DEVICE_GPIO_SD_PLUG, 	0, 200, 4294967295LL, 	0, INVALID_KV,	0, 0, DEVID_SDMMC, 		KEY_GPIO_ID_INVALID, KEYFLAG_DUMMY, "SDMMC"},
#endif

#ifdef CFG_CUS_BUTTON_LCD_COVER //may be defined in config_xxx.h
    CFG_BUTTON_CUS_LCD_COVER,
#else
    {DEVICE_LCD_OPEN, 	 DEVICE_LCD_COVERED, KEYPAD_NONE, 	KEYPAD_NONE, 	DEVICE_GPIO_LCD_COV, 	0, 200, 1200, 			0, INVALID_KV,  0, 0, DEVID_LCDCOV, 	KEY_GPIO_ID_INVALID, KEYFLAG_DUMMY,	"LCD COVER"},
#endif

    {DEVICE_LCD_INV, 	 DEVICE_LCD_NOR, 	 KEYPAD_NONE, 	KEYPAD_NONE, 	DEVICE_GPIO_LCD_INV, 	0, 200, 1200, 			0, INVALID_KV, 	0, 0, DEVID_LCDINV, 	KEY_GPIO_ID_INVALID, KEYFLAG_DUMMY,	"LCD ROTATE"},
	// All of Devices Initialized, send DEVICES_READY to Turn ON LCD backlight
	// The event sent only once.
	{DEVICES_READY,		 DEVICES_READY,		 KEYPAD_NONE, 	KEYPAD_NONE, 	MMP_GPIO_MAX,		    0, 200, 1200, 			0, INVALID_KV, 	0, 0, DEVID_LCDINV, 	KEY_GPIO_ID_INVALID, KEYFLAG_DUMMY,	"DEVICE READY"},  
	//

    {DC_CABLE_IN, 	 	 DC_CABLE_OUT, 		 KEYPAD_NONE, 	KEYPAD_NONE, 	DEVICE_GPIO_DC_INPUT, 	0, 200, 4294967295LL, 	DEVICE_GPIO_DC_INPUT_LEVEL, !DEVICE_GPIO_DC_INPUT_LEVEL,		0, 0, DEVID_DC_CABLE, 	KEY_GPIO_ID_INVALID, KEYFLAG_DUMMY,	"DC CABLE"}, 

#if defined(DEVICE_GPIO_CUS_SW1) && (DEVICE_GPIO_CUS_SW1 != MMP_GPIO_MAX)
    {CUS_SW1_ON,         CUS_SW1_OFF,        KEYPAD_NONE, 	KEYPAD_NONE, 	DEVICE_GPIO_CUS_SW1, 	0, 200, 4294967295LL, 	DEVICE_GPIO_CUS_SW1_ON, 1, 			0, 0, DEVID_CUS_SW1, 	KEY_GPIO_ID_INVALID, KEYFLAG_DUMMY,	"CUS SW1"}, 
#endif

#if defined(DEVICE_GPIO_CUS_SW2) && (DEVICE_GPIO_CUS_SW2 != MMP_GPIO_MAX)
    {CUS_SW2_ON,         CUS_SW2_OFF,        KEYPAD_NONE, 	KEYPAD_NONE, 	DEVICE_GPIO_CUS_SW2, 	0, 200, 4294967295LL, 	DEVICE_GPIO_CUS_SW2_ON, 1, 			0, 0, DEVID_CUS_SW2, 	KEY_GPIO_ID_INVALID, KEYFLAG_DUMMY,	"CUS SW2"}, 
#endif

};

static MMP_ULONG	gNumOfGPIOKey = sizeof(sButton) / sizeof(SGPIOBUTTON);
static MMP_ULONG	gNumOfDevice  = sizeof(sDeviceStatus) / sizeof(SGPIOBUTTON);
static MMP_ULONG   	gKeyEvent 	  = KEYPAD_NONE;
static MMP_ULONG	gComboKey	  = KEYFLAG_DUMMY;

#if (UVC_HOST_VIDEO_ENABLE )
static AHC_BOOL gbRearState = AHC_FALSE;
#endif

/*===========================================================================
 * Global variable
 *===========================================================================*/ 

#define SPEAKER_OFF_TIME                (5)     // SEC
#define POWER_SETTING_COUNTER_5MIN 		(2380)
#define TICKS_PER_SECOND				(1000) 
#define TICKS_PER_MINUTE				(60 * 1000) 

static MMP_BOOL  	UITaskReady				 = MMP_FALSE;
static MMP_ULONG 	gAutoPowerOffCounter 	 = 0;
static MMP_ULONG 	gVideoPowerOffCounter    = 0; 
static MMP_ULONG 	gLCDPowerSaveCounter  	 = 0;

#if (CHARGE_FULL_NOTIFY)
AHC_BOOL			bChargeFull				 = AHC_FALSE;
#endif

#if (NO_CARD_POWER_OFF_EN)
AHC_BOOL			gbNoCardPowerOff     	 = AHC_FALSE;
#endif

#if (SUPPORT_GSENSOR && POWER_ON_BY_GSENSOR_EN)
AHC_BOOL    ubGsnrPwrOnActStart     = AHC_FALSE;
AHC_BOOL    ubGsnrPwrOnFirstREC     = AHC_TRUE;
#endif

UINT8 ubSDMMCLeftSpaceLevel = 0;

#if (TASK_MONITOR_ENABLE)
MMPF_TASK_MONITOR gsTaskMonitorUIKey;
MMPF_TASK_MONITOR gsTaskMonitorRealIDUIKey;
#endif

/*===========================================================================
 * Extern variable
 *===========================================================================*/ 

extern AHC_BOOL 		PowerOff_InProcess; 
extern AHC_BOOL 		bForce_PowerOff;
extern AHC_BOOL			gAHC_InitialDone;  
extern MMPF_OS_FLAGID   CDV_UI_Flag;
//extern TMHOOK 			gTmKeypadHook;	// TY Miao - TBD
#ifdef CFG_LCD_POWER_SAVE_WHEN_MOTION //may be defined in config_xxx.h, typically 10*10000
extern AHC_BOOL			m_ubMotionDtcEn;
#endif

/*===========================================================================
 * Local function
 *===========================================================================*/ 

void SetKeyPadEvent(MMP_ULONG keyevent);
void SDMMCTimerOpen(void);

/*===========================================================================
 * Extern function
 *===========================================================================*/ 

extern AHC_BOOL AHC_IsUsbBooting(void);
extern AHC_BOOL AHC_IsDCInBooting(void);
extern UINT8 	AHC_WaitForSystemReady(void);
extern void 	SlideString(void);
extern void 	SlideSubMenu(void);
extern int		RemoveMenu_GsensorSensitivity(void);
#ifdef SLIDE_MENU
extern UINT8	IsSlidingMenu(void);
#endif
extern AHC_BOOL ubUIInitDone(void);
extern MMP_BOOL EDOGCtrl_IsInitial(void);
extern void EDOGCtrl_RestoesPOItoFile_Manual(void);
#if (EDOG_ENABLE)
extern void EDOGCtrl_Handler(MMP_HANDLE *h);

extern MMP_BOOL EDOGCtrl_SetSpeedLvl(MMP_ULONG);
extern MMP_BOOL EDOGCtrl_SetSpeedDist(MMP_ULONG);

extern MMP_BOOL EDOGCtrl_SetCheckAngleEn(MMP_BOOL);
extern MMP_BOOL EDOGCtrl_SetSearchAngleErr(MMP_UBYTE);
extern MMP_BOOL EDOGCtrl_SetSearchAngle(MMP_USHORT);
extern MMP_BOOL EDOGCtrl_SetSearchXAngle(MMP_USHORT);
extern MMP_BOOL EDOGCtrl_SetPoiDataType(MMP_UBYTE);
extern MMP_BOOL EDOGCtrl_EnAddSpeedCamPOI(MMP_UBYTE);
#endif
/*===========================================================================
 * Main body
 *===========================================================================*/ 

#ifdef CFG_KEY_DO_COVER_ACTION //may be defined in config_xxx.h
void doCoverAction(SGPIOBUTTON *sb, MMP_UBYTE kv, MMP_ULONG tm)
{
	if (kv == sb->ulPressLevel)
		SetKeyPadEvent(sb->iPressId);	// Close Cover
	else 
		SetKeyPadEvent(sb->iReleaseId);	// Open Cover

	printc("Cover %s\r\n", (kv == sb->ulPressLevel)? "Closed" : "Opened"); 
	sb->ulKeyLastValue = kv;
	sb->ulKeyLastTime  = tm;
}
#endif

#if 0
void _____ComboKey_Function_________(){ruturn;} //dummy
#endif

void SetComboKey(int key)
{

	gComboKey |= key;

}

void ClearComboKey(int key)
{
	gComboKey &= ~(key);
}

void PollingComboKey(void)
{
#if (COMBO_KEY_EN==1)

	if(gComboKey == KEYFLAG_DUMMY)
		return;

	switch(gComboKey)
	{
		case COMBO_KEY_FLAGSET1:
			printc(">>>>COMBO_KEY_FLAGSET1\r\n");
			if(COMBO_KEY_FLAGSET1!=KEYFLAG_DUMMY) 
				AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_COMBO_SET1, 0);

		break;	
		case COMBO_KEY_FLAGSET2:
			printc(">>>>COMBO_KEY_FLAGSET2\r\n");
			if(COMBO_KEY_FLAGSET2!=KEYFLAG_DUMMY) 
				AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_COMBO_SET2, 0);
		break;	
		default:
		break;
	}
#endif	
}

#if 0
void _____PowerSave_Function_________(){ruturn;} //dummy
#endif

void AutoPowerOffCounterReset(void)
{
	MMP_ULONG	t;

#if (SUPPORT_GSENSOR && POWER_ON_BY_GSENSOR_EN)
	if(ubGsnrPwrOnActStart)
	{
		gAutoPowerOffCounter = POWER_ON_GSNR_IDLE_TIME * TICKS_PER_SECOND;
	}
	else
#endif
	{
		switch(MenuSettingConfig()->uiAutoPowerOff)
		{
		#if (MENU_GENERAL_AUTO_POWEROFF_30SEC_EN)
			case AUTO_POWER_OFF_30SEC:
				gAutoPowerOffCounter = (30*1000);
			break;
		#endif	
        #if (MENU_GENERAL_AUTO_POWEROFF_15SEC_EN)
			case AUTO_POWER_OFF_15SEC:
				gAutoPowerOffCounter = (15*1000);
			break;
		#endif
		#if (MENU_GENERAL_AUTO_POWEROFF_1MIN_EN)
			case AUTO_POWER_OFF_1MIN:
				gAutoPowerOffCounter = TICKS_PER_MINUTE;
			break;
		#endif
		#if (MENU_GENERAL_AUTO_POWEROFF_2MIN_EN)	
			case AUTO_POWER_OFF_2MINS:
				gAutoPowerOffCounter = 2 * TICKS_PER_MINUTE;	
			break;
		#endif
		#if (MENU_GENERAL_AUTO_POWEROFF_3MIN_EN)
			case AUTO_POWER_OFF_3MINS:
				gAutoPowerOffCounter = 3 * TICKS_PER_MINUTE;
			break;
		#endif
		#if (MENU_GENERAL_AUTO_POWEROFF_5MIN_EN)	
			case AUTO_POWER_OFF_5MINS:
				gAutoPowerOffCounter = 5 * TICKS_PER_MINUTE;
			break;
		#endif	
			default:
				gAutoPowerOffCounter = 0;
				return;
			break;
		}
	}
	
#if (NO_CARD_POWER_OFF_EN)
    if (gbNoCardPowerOff)
    {		
		#ifdef CFG_POWER_CUS_AUTO_OFF_TIME //may be defined in config_xxx.h
		printc("NO SD and %d sec power off\r\n", CFG_POWER_CUS_AUTO_OFF_TIME / 1000);
		gAutoPowerOffCounter = CFG_POWER_CUS_AUTO_OFF_TIME;
		#else
		RTNA_DBG_Str(0, "NO SD and 10 sec power off\r\n");
		gAutoPowerOffCounter = (10*1000);
    	#endif
    }
#endif
	
	MMPF_OS_GetTime(&t);
	gAutoPowerOffCounter += t;
	
	if (0 == gAutoPowerOffCounter) {
		// overflow
		gAutoPowerOffCounter++;
	}
}

void LCDPowerSaveCounterReset(void)
{
	MMP_ULONG	t;

    #ifdef CFG_LCD_POWER_SAVE_WHEN_MOTION //may be defined in config_xxx.h, typically 10*10000
	if(m_ubMotionDtcEn && uiGetCurrentState()==UI_VIDEO_STATE)
	{
		gLCDPowerSaveCounter = CFG_LCD_POWER_SAVE_WHEN_MOTION;
	}
	else
	#endif
	{
		switch(MenuSettingConfig()->uiLCDPowerSave)
		{
		#if (MENU_GENERAL_LCD_POWER_SAVE_1MIN_EN)
			case LCD_POWER_SAVE_1MIN:
				gLCDPowerSaveCounter = TICKS_PER_MINUTE;
			break;
		#endif
		#if (MENU_GENERAL_LCD_POWER_SAVE_3MIN_EN)	
			case LCD_POWER_SAVE_3MIN:
				gLCDPowerSaveCounter = 3 * TICKS_PER_MINUTE;
			break;
		#endif	
			default:
				gLCDPowerSaveCounter = 0;
				return;
			break;
		}
	}

	MMPF_OS_GetTime(&t);
	gLCDPowerSaveCounter += t;
}

void VideoPowerOffCounterReset(void)
{
	UINT32	p;
	
	p = AHC_GetVideoPowerOffTime();

	MMPF_OS_GetTime(&gVideoPowerOffCounter);
	
	#ifdef OFF_TIME_DURING_LOCK
    {
    	if(VideoFunc_LockFileEnabled())
    	{
    		gVideoPowerOffCounter += (OFF_TIME_DURING_LOCK * TICKS_PER_SECOND);
    	}
    	else
    	{
    		gVideoPowerOffCounter += (p * TICKS_PER_SECOND);
    	}
    }
	#else
	gVideoPowerOffCounter += (p * TICKS_PER_SECOND);
	#endif
}

void PowerSavingModeDetection(UINT32 tick)
{
	UINT8		cur_state;	
	
	cur_state = uiGetCurrentState();
    
    if (cur_state==UI_MSDC_STATE || cur_state==UI_PCCAM_STATE ||
        #if defined(CFG_POWER_TV_NO_SAVING)     //may be defined in config_xxx.h
        cur_state==UI_TVOUT_STATE ||
        #endif
        #if defined(CFG_POWER_HDMI_NO_SAVING)   //may be defined in config_xxx.h
        cur_state==UI_HDMI_STATE ||
        #endif
        0)
    {
		AutoPowerOffCounterReset();
		return;
	}
	else if(VideoFunc_RecordStatus()==AHC_TRUE)
	{
		AutoPowerOffCounterReset();
		return;
	}	
    else if(cur_state==UI_PLAYBACK_STATE && (MOV_STATE_PLAY == GetMovConfig()->iState || MOV_STATE_FF == GetMovConfig()->iState) )
    {
		AutoPowerOffCounterReset();
		return;
	}
	else if(cur_state==UI_SLIDESHOW_STATE)
	{
		AutoPowerOffCounterReset();
		return;
	}

	if (gAutoPowerOffCounter != 0)
	{
		INT32 time_diff = (INT32) (tick - gAutoPowerOffCounter);

		// 21600000(ms): avoid overflow case, set system tolerance 6-HR
		// need modify it when UI setting except to 6-HR
		if ((time_diff >= 0) && (time_diff < 21600000)) {
			RTNA_DBG_Str(0, BG_RED("\r\n!!! Entering Power saving mode\r\n"));
			bForce_PowerOff = AHC_TRUE;
			SetKeyPadEvent(KEY_POWER_OFF);
			gAutoPowerOffCounter = 0; // Never enter again
		}
	}
}

void LCDPowerSaveDetection(UINT32 tick)
{
#ifdef CFG_SURPRESS_POWER_SAVE_WHEN_PLAYING //may be defined in config_xxx.h
    if(uiGetCurrentState()==UI_PLAYBACK_STATE && (MOV_STATE_PLAY == GetMovConfig()->iState || MOV_STATE_FF == GetMovConfig()->iState) )
    {
		LCDPowerSaveCounterReset();
		return;
	}
#endif
#ifdef CFG_SURPRESS_POWER_SAVE_WHEN_SLIDESHOW //may be defined in config_xxx.h
	if(uiGetCurrentState()==UI_SLIDESHOW_STATE)
	{
		LCDPowerSaveCounterReset();
		return;
	}
#endif

#if (UVC_HOST_VIDEO_ENABLE )
    if (gLCDPowerSaveCounter != 0 && gbRearState == AHC_FALSE) 
#else
	if (gLCDPowerSaveCounter != 0)
#endif
	{
		if ((int)(tick - gLCDPowerSaveCounter) >= 0) 
		{
			gLCDPowerSaveCounter = 0;
			
			if(LedCtrl_GetBacklightStatus())
				LedCtrl_LcdBackLight(AHC_FALSE);
		}
	}
#if (UVC_HOST_VIDEO_ENABLE )
	else if(gbRearState == AHC_TRUE)
	{
		LCDPowerSaveCounterReset();
	}
#endif
}

void VideoPowerOnOffDetection(UINT32 tick)
{
    UINT8 ubBootupWithCharger = 0;
	static AHC_BOOL bPoweroff = AHC_FALSE; 
    
    if(AHC_TRUE == AHC_GetShutdownByChargerOut())    
    {
		#if (RESET_POWER_CNT_DURING_LOCK)
    	{
    		if(VideoFunc_LockFileEnabled())
    		{
    			VideoPowerOffCounterReset();
    			return;
    		}
    	}
		#endif
		
		#if (CHARGER_OUT_ACT_OTHER_MODE==ACT_FORCE_POWER_OFF)
		if(!VideoFunc_RecordStatus())
		{
			tick = gVideoPowerOffCounter+1;
		}
		#endif
		#if (CHARGER_OUT_ACT_VIDEO_REC==ACT_FORCE_POWER_OFF)
		if(VideoFunc_RecordStatus())
		{
			tick = gVideoPowerOffCounter+1;
		}
		#endif		

    	if (gVideoPowerOffCounter == 0)
    		return;

    	tick = tick - gVideoPowerOffCounter;

        if ((int)tick > 0 && bPoweroff==AHC_FALSE)
        {
        	bPoweroff = AHC_TRUE;
            RTNA_DBG_Str(0, FG_RED("!!! Auto Power off\r\n"));
            bForce_PowerOff = AHC_TRUE;
		#ifdef CFG_MENU_SETTING_BY_CUSTOMER_CARD
             AHC_SetMode(AHC_MODE_IDLE);
             AHC_NormalPowerOffPath();
		#endif
            AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, KEY_POWER_OFF, 0);
        }
    }
    else if((ubBootupWithCharger = AHC_GetRecordByChargerIn()) > 0)
    {
        AHC_SetRecordByChargerIn(--ubBootupWithCharger);

        if(!ubBootupWithCharger)
        {
            AHC_BOOL sendVideoRecord = AHC_FALSE;

			if (uiGetCurrentState() == UI_STATE_UNSUPPORTED) {
				// Delay more time
				AHC_SetRecordByChargerIn(3);
			}
			else if (uiGetCurrentState() == UI_VIDEO_STATE) {
                sendVideoRecord = AHC_TRUE;
            }
#if (TVOUT_PREVIEW_EN)
            else if ((uiGetCurrentState() == UI_TVOUT_STATE) && \
                     (AHC_TV_VIDEO_PREVIEW_STATUS == TVFunc_Status())) {
                    sendVideoRecord = AHC_TRUE;
            }
#endif
#if (HDMI_PREVIEW_EN)
            else if ((uiGetCurrentState() == UI_HDMI_STATE) && \
                     (AHC_HDMI_VIDEO_PREVIEW_STATUS == HDMIFunc_Status())) {
                    sendVideoRecord = AHC_TRUE;
            }
#endif

            if (AHC_TRUE == sendVideoRecord)
            {
                SetKeyPadEvent(KEY_VIDEO_RECORD);
                VideoPowerOffCounterReset();

                if (AHC_GetShutdownByChargerOut() == AHC_TRUE)
                    AHC_SetShutdownByChargerOut(AHC_FALSE);
                
    			#if ((SUPPORT_GSENSOR && POWER_ON_BY_GSENSOR_EN) && (GSNR_PWRON_MOVIE_SHAKED_ACT == GSNR_PWRON_MOVIE_LOCKED))
    			if ((AHC_GetBootingSrc() & PWR_ON_BY_GSENSOR) == PWR_ON_BY_GSENSOR)
    			{
				    extern AHC_BOOL ubGsnrPwrOnFirstREC;
                    extern AHC_BOOL m_ubGsnrIsObjMove;
                    
				    if (AHC_TRUE == ubGsnrPwrOnFirstREC) {
					    m_ubGsnrIsObjMove = AHC_TRUE;
					    //ubGsnrPwrOnFirstREC = AHC_FALSE;
					}
    			}
			    #endif
            }
        }
    }
}

void SpeakerPowerDetection(void)
{
    static MMP_ULONG ulpreDetectTime = 0;
    MMP_ULONG ulcurDetectTime;

    if (AHC_FALSE == AHC_IsSpeakerEnable()) {
        ulpreDetectTime = MMPF_RTC_GetTime_InSeconds();
        return;    
    }

    ulcurDetectTime = MMPF_RTC_GetTime_InSeconds();

    if (ulcurDetectTime >= ulpreDetectTime) {
        ulcurDetectTime -= ulpreDetectTime;
    }
    else {
        ulcurDetectTime = ((MMP_ULONG) -1) - ulpreDetectTime + ulcurDetectTime;
    }

    if (ulcurDetectTime < SPEAKER_OFF_TIME)
        return;

    ulpreDetectTime = MMPF_RTC_GetTime_InSeconds();
    
    {
        UINT8 ubSoundStatus = 0;

        AHC_GetSoundEffectStatus(&ubSoundStatus);
        
        if((AHC_SOUND_EFFECT_STATUS_STOP == ubSoundStatus) || (AHC_SOUND_EFFECT_STATUS_INVALID == ubSoundStatus))
        {    
            if (AHC_GetAhcSysMode() != AHC_MODE_PLAYBACK) {
                AHC_SpeakerEnable(SPEAKER_ENABLE_GPIO, AHC_FALSE);
                printc("!!! Speaker turn-off by %s\r\n", __func__);
            }
        }
    }
}

#if 0
void _____SDMMC_Function_________(){ruturn;} //dummy
#endif


#if (DETECT_SD_BY_TIMER==1)
 
extern MMP_BOOL bFirstTimeGetFreeSpace;

void SDMMCTimerHandler(void)
{
#if (DETECT_SD_BY_TIMER==1)
    MMP_UBYTE bSD_Inserted = AHC_FALSE;
    
    static MMP_ULONG bCardDetCnt = 1, bCardRemoveCnt = 1;

    if(!gAHC_InitialDone)
        return;
  
    bSD_Inserted = AHC_IsSDInserted();
    
    if ((bSD_Inserted == AHC_TRUE) && (AHC_SDMMC_GetState() == SDMMC_OUT)) 
    {
        bCardDetCnt = (bCardDetCnt + 1) & 0x3f;
        bCardRemoveCnt = 1;
        
        if(0 == bCardDetCnt)
        {
            AHC_SDMMC_SetState(SDMMC_IN);
			bFirstTimeGetFreeSpace = MMP_TRUE;
            printc("\r\n+++SD_CARD_IN+++\r\n");
            SetKeyPadEvent(SD_CARD_IN);
        }
    }
    else if ((bSD_Inserted == AHC_FALSE) && (AHC_SDMMC_GetState() == SDMMC_IN))
    {
        bCardRemoveCnt = (bCardRemoveCnt + 1) & 0x05;
        bCardDetCnt = 1;
        
        if(0 ==bCardRemoveCnt)
        {
            AHC_SDMMC_SetState(SDMMC_OUT);
            bFirstTimeGetFreeSpace = MMP_TRUE;
            printc("\r\n+++SD_CARD_OUT+++\r\n");
            SetKeyPadEvent(SD_CARD_OUT);
        }
    }
    else
    {
        bCardRemoveCnt = 1;
        bCardDetCnt = 1;
    }

    #ifdef CFG_NOSD_POWEROFF
	{
		static MMP_UBYTE  bPoweroff = AHC_FALSE;
		bSD_Inserted = AHC_IsSDInserted();

		if (!bSD_Inserted && !bPoweroff)
		{
			//AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, KEY_POWER_OFF, 0);
			SetKeyPadEvent(BUTTON_FUNC1_LPRESS);
			printc("KEY_POWER_OFF %d\r\n");
			bPoweroff = AHC_TRUE;
		}
	}
    #endif
#endif
}

void SDMMCTimerHandlerForOs(void *tmr, void *arg)
{
    #if ((DETECT_SD_BY_TIMER==1) && (DETECT_SD_BY_OS_TIMER == 1))
    SDMMCTimerHandler();
    #endif
}

#if ((DETECT_SD_BY_TIMER==1) && (DETECT_SD_BY_OS_TIMER == 1))
static AHC_OS_TMRID ulSDMMC_TMRID = 0xFF;
#endif

void SDMMCTimerOpen(void)
{
#if (DETECT_SD_BY_TIMER==1)
    #if (DETECT_SD_BY_OS_TIMER == 1)
    ulSDMMC_TMRID = AHC_OS_StartTimer(40, MMPF_OS_TMR_OPT_PERIODIC, &SDMMCTimerHandlerForOs, NULL);
    #else
    MMPF_TIMER_ATTR TimerAttribute;
    
	TimerAttribute.TimePrecision = MMPF_TIMER_MILLI_SEC;
	TimerAttribute.ulTimeUnits   = 40;
	TimerAttribute.Func          = SDMMCTimerHandler;
	TimerAttribute.bIntMode      = MMPF_TIMER_PERIODIC;
    MMPF_Timer_Start(MMPF_TIMER_2, &TimerAttribute);
    #endif
#endif
}

void SDMMCTimerClose(void)
{
#if (DETECT_SD_BY_TIMER==1)
    #if (DETECT_SD_BY_OS_TIMER == 1)
    if (ulSDMMC_TMRID < 0xFE) {
        AHC_OS_StopTimer(ulSDMMC_TMRID, MMPF_OS_TMR_OPT_PERIODIC);
        ulSDMMC_TMRID = 0xFF;
    }
    #else
	MMPF_Timer_Stop(MMPF_TIMER_2);
    #endif
#endif
}

UINT8 SDMMCSpaceCalculation(void)
{
	UINT64 ulFreeByte,ulTotalByte,ulAvailableByte;	
 	
 	AHC_FS_GetStorageFreeSpace(AHC_MEDIA_MMC, &ulFreeByte);
	AHC_FS_GetTotalSpace("SD:\\", sizeof("SD:\\"), &ulTotalByte);
	ulAvailableByte = (ulFreeByte*100) / ulTotalByte;
	if((ulAvailableByte/25)>=3)
	{
		ubSDMMCLeftSpaceLevel = 4;
	}
	else if((ulAvailableByte/25)>=2)
	{
		ubSDMMCLeftSpaceLevel = 3;
	}
	else if((ulAvailableByte/25)>=1)
	{
		ubSDMMCLeftSpaceLevel = 2;
	}
	else
		ubSDMMCLeftSpaceLevel = 1;

	if(ulFreeByte==0)
		AHC_BuzzerAlert(4, 1, 100);
		
	return ubSDMMCLeftSpaceLevel;
}

#endif

#if 0
void _____KeyPad_Device_Function_________(){ruturn;} //dummy
#endif

void InitButtonGpio(MMP_GPIO_PIN piopin, GpioCallBackFunc* CallBackFunc)
{
	if(piopin == MMP_GPIO_MAX)
		return;
		
    MMPF_PIO_EnableOutputMode(piopin, MMP_FALSE, MMP_TRUE);

    if (CallBackFunc) {
        MMPF_PIO_EnableTrigMode(piopin, GPIO_H2L_EDGE_TRIG, MMP_TRUE, MMP_TRUE);
        MMPF_PIO_EnableTrigMode(piopin, GPIO_L2H_EDGE_TRIG, MMP_TRUE, MMP_TRUE);
        MMPF_PIO_EnableInterrupt(piopin, MMP_TRUE, 0, (GpioCallBackFunc *) CallBackFunc, MMP_TRUE);
    }
    else
        MMPF_PIO_EnableInterrupt(piopin, MMP_FALSE, 0, (GpioCallBackFunc *) NULL, MMP_TRUE);    
}

void InitKeyPad(void)
{
    int i;

    //e.g. #define CFG_CUS_KEYPAD_INIT 	AHC_ConfigGPIOPad(KEY_LED_MUTE,PAD_PULL_HIGH | PAD_E8_CURRENT);//*((char*)(0x80009D21)) = 0x44;
    #ifdef CFG_CUS_KEYPAD_INIT //may be defined in config_xxx.h
    CFG_CUS_KEYPAD_INIT
    #endif

#if (SUPPORT_GSENSOR)
    #if (POWER_ON_BY_GSENSOR_EN) && defined(GSENSOR_INT)
	if ((AHC_GetBootingSrc() & PWR_ON_BY_GSENSOR) == PWR_ON_BY_GSENSOR)
	{
		if(	GSNR_PWRON_ACT == GSNR_PWRON_IDLE && \
			(GSNR_PWRON_REC_BY && GSNR_PWRON_REC_BY_KEY))
			ubGsnrPwrOnActStart = AHC_FALSE;
		else if(GSNR_PWRON_ACT == GSNR_PWRON_REC_AUTO)
			ubGsnrPwrOnActStart = AHC_TRUE;
			
		printc(FG_BLUE("Power On by Gsensor\r\n"));
    }
    #endif

	if (AHC_Gsensor_IOControl(GSNR_CMD_RESET, NULL) != AHC_TRUE) {
		//No GSensor in device
	    #ifndef CFG_MENU_ALWAYS_KEEP_GSENSOR_SENSITIVITY //may be defined in config_xxx.h
		RemoveMenu_GsensorSensitivity();
		#endif
	} else {
		AHC_Gsensor_IOControl(GSNR_CMD_CALIBRATION, NULL);
		//Set which axis into ground to use it to detect kit position
		AHC_Gsensor_IOControl(GSNR_CMD_SET_GROUND_AXIS, (MMP_UBYTE*)GSNR_GROUND_AXIS);
        Menu_SetGsensorSensitivity(MenuSettingConfig()->uiGsensorSensitivity);
	}
#endif//SUPPORT_GSENSOR

#if defined(TV_OUT_DETECT_GPIO)
    InitButtonGpio(TV_OUT_DETECT_GPIO, NULL);
#endif

#if (SUPPORT_TOUCH_PANEL)
    AHC_TouchPanel_Init();
    #if defined(TOUCH_PANEL_USE_INTR_MODE)&&(TOUCH_PANEL_USE_INTR_MODE)
    //#warning    touchpanel use interrupt mode
    #else
    #if defined(TOUCH_PANEL_INT_GPIO)
    if (TOUCH_PANEL_INT_GPIO != MMP_GPIO_MAX)
        MMPS_PIO_PadConfig(TOUCH_PANEL_INT_GPIO, 0x24);//Set CGPIO20 PU for HDK C version
    #endif
    #endif
#endif

#ifdef CFG_CUS_GPIO_CONFIG
	CFG_CUS_GPIO_CONFIG();
#endif

    for( i=0; i<gNumOfDevice; i++ )
    {
        InitButtonGpio( sDeviceStatus[i].piopin, NULL);

#if defined(DEVICE_GPIO_DC_INPUT)
        if (DEVICE_GPIO_DC_INPUT != MMP_GPIO_MAX) {
            if((DEVICE_GPIO_DC_INPUT == sDeviceStatus[i].piopin) && AHC_IsDCInBooting())
            {
                printc("Force DEVICE_GPIO_DC_INPUT as plug in status\r\n");
                sDeviceStatus[i].ulKeyLastValue = DEVICE_GPIO_DC_INPUT_LEVEL;       //Force it as plug in status.
            }
        }
#endif
    }

    for( i=0; i<gNumOfGPIOKey; i++ )
    { 
        InitButtonGpio( sButton[i].piopin, NULL );
    }

#if (DETECT_SD_BY_TIMER==1)
    SDMMCTimerOpen();
#endif
}

MMP_ERR GetKeyPadEvent(MMP_ULONG *keyevent)
{
    *keyevent = gKeyEvent;
    gKeyEvent = KEYPAD_NONE;
    
    return MMP_ERR_NONE;
}

void SetKeyPadEvent(MMP_ULONG keyevent)
{
	gKeyEvent = keyevent;
	MMPF_OS_SetFlags(CDV_UI_Flag, CDV_KEYPAD_FLAG, MMPF_OS_FLAG_SET);
}

void SetUITimeEvent(void)
{
	MMPF_OS_SetFlags(CDV_UI_Flag, CDV_TIME_FLAG, MMPF_OS_FLAG_SET);
}

#if (UPDATE_UI_USE_MULTI_TASK)
void SetUIUpdateEvent(void)
{
	MMPF_OS_SetFlags(CDV_UI_Flag, CDV_UI_FLAG, MMPF_OS_FLAG_SET);
}
#endif

AHC_BOOL HDMI_Cable_Detection(void)
{
    UINT8			CurrentState;
    AHC_BOOL		IsConnect;
    static UINT8 	TempState 	= UI_STATE_UNSUPPORTED;
    static AHC_BOOL firsttime 	= AHC_TRUE;
    static AHC_BOOL HdmiCableIn = AHC_TRUE;
    
    #if (!HDMI_ENABLE)
	return AHC_FALSE;
	#endif
    
    CurrentState = uiGetCurrentState(); 
    IsConnect 	 = AHC_IsHdmiConnect();

    if(TempState != CurrentState) {
        firsttime = AHC_TRUE;
        TempState = CurrentState;
    }
    
    if((!firsttime) && (HdmiCableIn == IsConnect)) {
        // HDMI status is not change
        return AHC_FALSE;
    }

    firsttime = AHC_FALSE;

#ifdef CFG_ENABLE_HDMI_HPD
	// ++ HDMI HPD
	if (IsConnect == AHC_TRUE) {
	// -- HDMI HPD
#else
    if(((CurrentState != UI_HDMI_STATE) && (CurrentState != UI_MSDC_STATE) && (CurrentState != UI_PCCAM_STATE) && (CurrentState != UI_STATE_UNSUPPORTED)) && IsConnect == AHC_TRUE){
#endif
        //HDMI cable in
        RTNA_DBG_Str(0, "@@@ HDMI_CABLE_IN\r\n");
        SetKeyPadEvent(HDMI_CABLE_IN);

#ifdef CFG_ENABLE_HDMI_HPD
		// ++ HDMI HPD
		HdmiCableIn = AHC_TRUE;
		AHC_LockHdmiConnectionStatus(AHC_TRUE, AHC_TRUE);
		// -- HDMI HPD
#else
		HdmiCableIn = IsConnect;
#endif
		
        return AHC_TRUE;
    }    
#ifdef CFG_ENABLE_HDMI_HPD
	// ++ HDMI HPD
	else {
	// -- HDMI HPD
#else
    else if(((CurrentState == UI_CAMERA_STATE)      || (CurrentState == UI_VIDEO_STATE)  		|| (CurrentState == UI_PLAYBACK_STATE)    || 
             (CurrentState == UI_SLIDESHOW_STATE)   || (CurrentState == UI_HDMI_STATE)   		|| (CurrentState == UI_CAMERA_MENU_STATE) || 
             (CurrentState == UI_VIDEO_MENU_STATE)  || (CurrentState == UI_PLAYBACK_MENU_STATE) || (CurrentState == UI_CLOCK_SETTING_STATE)) 
           && IsConnect == AHC_FALSE){
#endif
        //HDMI cable out 
#ifdef CFG_ENABLE_HDMI_HPD
		// ++ HDMI HPD
		HdmiCableIn = AHC_FALSE;
		AHC_LockHdmiConnectionStatus(AHC_TRUE, AHC_FALSE);
		// -- HDMI HPD
#else
		HdmiCableIn = IsConnect;
#endif

        RTNA_DBG_Str(0, "@@@ HDMI_CABLE_OUT\r\n");
        SetKeyPadEvent(HDMI_CABLE_OUT);
    } 

    return AHC_FALSE;
}

AHC_BOOL TV_Cable_Detection(void)
{
    UINT8 			CurrentState;
    AHC_BOOL 		IsConnect;
    static UINT8 	TempState = UI_STATE_UNSUPPORTED;
    static AHC_BOOL firsttime = AHC_TRUE;
    static AHC_BOOL TvCableIn = AHC_TRUE;
    
    #ifdef TV_ONLY
	return AHC_TRUE;
	#endif
    
    CurrentState = uiGetCurrentState();
    IsConnect 	 = AHC_IsTVConnectEx(); 

    if(TempState != CurrentState) {
        firsttime = AHC_TRUE;
        TempState = CurrentState;
    }
    
    if((!firsttime) && (TvCableIn == IsConnect)) {
        return AHC_FALSE;
    }

    firsttime = AHC_FALSE;
    TvCableIn = IsConnect;

#ifdef CFG_ENABLE_TV_HPD
	// ++ TV HPD
	if (IsConnect == AHC_TRUE) {
	// -- TV HPD
#else
    if(((CurrentState != UI_MSDC_STATE) && (CurrentState != UI_PCCAM_STATE) && (CurrentState != UI_STATE_UNSUPPORTED)) && IsConnect == AHC_TRUE){
#endif
        //TV cable in   
        RTNA_DBG_Str(0, "@@@ TV_CABLE_IN\r\n");
        SetKeyPadEvent(TV_CABLE_IN);

#ifdef CFG_ENABLE_TV_HPD
		// ++ TV HPD
		AHC_LockTVConnectionStatus(AHC_TRUE, AHC_TRUE);
		// -- TV HPD
#endif
        return AHC_TRUE;
    }
#ifdef CFG_ENABLE_TV_HPD
	// ++ TV HPD
    else {
	// -- TV HPD
#else
    else if(((CurrentState == UI_CAMERA_STATE)      || (CurrentState == UI_VIDEO_STATE) 		|| (CurrentState == UI_PLAYBACK_STATE)	  || 
             (CurrentState == UI_SLIDESHOW_STATE)   || (CurrentState == UI_TVOUT_STATE) 		|| (CurrentState == UI_CAMERA_MENU_STATE) || 
             (CurrentState == UI_VIDEO_MENU_STATE)  || (CurrentState == UI_PLAYBACK_MENU_STATE) || (CurrentState == UI_CLOCK_SETTING_STATE)) 
           && IsConnect == AHC_FALSE){
#endif
        //TV cable out
        RTNA_DBG_Str(0, "@@@ TV_CABLE_OUT\r\n");
        SetKeyPadEvent(TV_CABLE_OUT);

#ifdef CFG_ENABLE_TV_HPD
		// ++ TV HPD
		AHC_LockTVConnectionStatus(AHC_TRUE, AHC_FALSE);
		// -- TV HPD
#endif
        return AHC_FALSE;
    }  

    return AHC_FALSE;
}

void GPIO_Key_Detection(void)
{
    MMP_ULONG 	i, ulNow;
	UINT32		uiLCDstatus;
	    
    if (!AHC_KeyUIWorking())
    	return;
    	
    MMPF_OS_GetTime(&ulNow);   
    
    AHC_GetParam(PARAM_ID_LCD_STATUS, &uiLCDstatus);
    
    for( i=0; i<gNumOfGPIOKey ; i++ )
    {
		MMP_UBYTE tempValue = 0;
		MMP_UBYTE ubKeyId   = i;

		if(sButton[i].piopin == MMP_GPIO_MAX)
			continue;

		MMPF_PIO_GetData(sButton[i].piopin, &tempValue);

#if (HALL_SNR_FLIP_SELECT & FLIP_OSD) || (KEY_FLIP_SELECT & FLIP_OSD) || (KEYPAD_ROTATE_EN==1)
		ubKeyId = (!uiLCDstatus)?(i):(sButton[i].ubKeyPairId);
#endif		
		if(ubKeyId == KEY_GPIO_ID_INVALID)
			ubKeyId = i;
		
		// Continuous key
		if( sButton[ubKeyId].ulContinuousTime	!=	0								&&
			sButton[ubKeyId].ulKeyLastValue		==	sButton[ubKeyId].ulPressLevel	&&
			sButton[ubKeyId].ulKeyLastValue		==	tempValue )
		{
			if( ulNow - sButton[ubKeyId].ulKeyLastTime > sButton[ubKeyId].ulContinuousTime )
			{
				sButton[ubKeyId].ubLongPress 		= 1;
                sButton[ubKeyId].ulKeyLastValue 	= tempValue;
                sButton[ubKeyId].ulKeyLastTime  	= ulNow;
                sButton[ubKeyId].ulKeyCount++;
                    
				if(KEY_LPRESS_POWER == sButton[ubKeyId].iLongPressId)
				{
					if(sButton[ubKeyId].ulKeyCount==POWER_KEY_LONG_PRESS_CNT)
					{
			        	#if defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_WIFI_STREAMING_DISABLE_REC_KEY)
			        	if ((AHC_STREAM_OFF != AHC_GetStreamingMode()) && 
							#if (POWER_OFF_CONFIRM_PAGE_EN)
							(PowerOff_InProcess == AHC_FALSE) &&
							#endif
			                (KEY_VIDEO_RECORD == sButton[ubKeyId].iLongPressId))
						{
							continue;
						}
						#endif
							
						SetKeyPadEvent(sButton[ubKeyId].iLongPressId);
						printc("Long Press Key %s\r\n",sButton[ubKeyId].ubkeyname);	
					}
					else if (sButton[ubKeyId].ubLPRepeatEn && sButton[ubKeyId].ubLPRepeatTime) {
						if (POWER_KEY_LONG_PRESS_CNT < sButton[ubKeyId].ulKeyCount) {
							if (0 == ((sButton[ubKeyId].ulKeyCount - POWER_KEY_LONG_PRESS_CNT) % (POWER_KEY_LONG_PRESS_CNT * sButton[ubKeyId].ubLPRepeatTime))) {
					        	#if defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_WIFI_STREAMING_DISABLE_REC_KEY)
					        	if ((AHC_STREAM_OFF != AHC_GetStreamingMode()) && 
									#if (POWER_OFF_CONFIRM_PAGE_EN)
									(PowerOff_InProcess == AHC_FALSE) &&
									#endif
						        	(KEY_VIDEO_RECORD == sButton[ubKeyId].iLongPressId))
						        {
									continue;
								}
								#endif
							
								SetKeyPadEvent(sButton[ubKeyId].iLongPressId);
								printc("Repeat Long Press Key %s\r\n", sButton[ubKeyId].ubkeyname);	
							}
						}
					} 	                    		
				}
				else
				{
					if(sButton[ubKeyId].ulKeyCount==OTHER_KEY_LONG_PRESS_CNT)
					{
			        	#if defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_WIFI_STREAMING_DISABLE_REC_KEY)
			        	if ((AHC_STREAM_OFF != AHC_GetStreamingMode()) && 
							#if (POWER_OFF_CONFIRM_PAGE_EN)
							(PowerOff_InProcess == AHC_FALSE) &&
							#endif
			        	    (KEY_VIDEO_RECORD == sButton[ubKeyId].iLongPressId))
			        	{
							continue;
						}
						#endif
							
						SetKeyPadEvent(sButton[ubKeyId].iLongPressId);
						AHC_SetButtonStatus(sButton[ubKeyId].iLongPressId);
						SetComboKey(sButton[ubKeyId].ulKeyFlag << 16);
						printc("Long Press Key %s\r\n",sButton[ubKeyId].ubkeyname);
					}	 						
					else if (sButton[ubKeyId].ubLPRepeatEn && sButton[ubKeyId].ubLPRepeatTime) {
						if (OTHER_KEY_LONG_PRESS_CNT < sButton[ubKeyId].ulKeyCount) {
							if (0 == (sButton[ubKeyId].ulKeyCount % OTHER_KEY_LONG_PRESS_CNT)) {
					        	#if defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_WIFI_STREAMING_DISABLE_REC_KEY)
					        	if ((AHC_STREAM_OFF != AHC_GetStreamingMode()) && 
									#if (POWER_OFF_CONFIRM_PAGE_EN)
									(PowerOff_InProcess == AHC_FALSE) &&
									#endif
					        	    (KEY_VIDEO_RECORD == sButton[ubKeyId].iLongPressId))
					        	{
									continue;
								}
								#endif
									
								SetKeyPadEvent(sButton[ubKeyId].iLongPressId);
								printc("Repeat Long Press Key %s\r\n", sButton[ubKeyId].ubkeyname);	
							}
						}
					} 	                    		
				}
            }
            //break;
		}
		else if( tempValue != sButton[ubKeyId].ulKeyLastValue &&      // Check if the key is lost
				 ulNow - sButton[ubKeyId].ulKeyLastTime > sButton[ubKeyId].ulDebounceTime )
		{
			// If state change
			if( tempValue == sButton[ubKeyId].ulPressLevel )
			{
	        	#if defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_WIFI_STREAMING_DISABLE_REC_KEY)
	        	if ((AHC_STREAM_OFF != AHC_GetStreamingMode()) && 
					#if (POWER_OFF_CONFIRM_PAGE_EN)
					(PowerOff_InProcess == AHC_FALSE) &&
					#endif
	        		(KEY_VIDEO_RECORD == sButton[ubKeyId].iPressId))
	        	{
					continue;
				}
				#endif
					
				sButton[ubKeyId].ubLongPress = 0;
				SetKeyPadEvent(sButton[ubKeyId].iPressId);          	
				AHC_SetButtonStatus(sButton[ubKeyId].iPressId);
				SetComboKey(sButton[ubKeyId].ulKeyFlag);      	
				printc("Press Key %s\r\n",sButton[ubKeyId].ubkeyname);                    
			}
			else
			{
				if ((!sButton[ubKeyId].ubLongPress) ||
				    ((KEY_LPRESS_POWER == sButton[ubKeyId].iLongPressId) && (POWER_KEY_LONG_PRESS_CNT > sButton[ubKeyId].ulKeyCount)) ||
					((KEY_LPRESS_POWER != sButton[ubKeyId].iLongPressId) && (OTHER_KEY_LONG_PRESS_CNT > sButton[ubKeyId].ulKeyCount)))
				{
		        	#if defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_WIFI_STREAMING_DISABLE_REC_KEY)
		        	if ((AHC_STREAM_OFF != AHC_GetStreamingMode()) && 
						#if (POWER_OFF_CONFIRM_PAGE_EN)
						(PowerOff_InProcess == AHC_FALSE) &&
						#endif
			        	(KEY_VIDEO_RECORD == sButton[ubKeyId].iReleaseId))
			        {
						continue;
					}
					#endif
						
					SetKeyPadEvent(sButton[ubKeyId].iReleaseId);
					ClearComboKey(sButton[ubKeyId].ulKeyFlag);	
					printc("Release Key %s\r\n",sButton[ubKeyId].ubkeyname);
				}
				else
				{
		        	#if defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_WIFI_STREAMING_DISABLE_REC_KEY)
		        	if ((AHC_STREAM_OFF != AHC_GetStreamingMode()) && 
						#if (POWER_OFF_CONFIRM_PAGE_EN)
						(PowerOff_InProcess == AHC_FALSE) &&
						#endif
		        		(KEY_VIDEO_RECORD == sButton[ubKeyId].iLongReleaseId))
		        	{
						continue;
					}
					#endif
						
					sButton[ubKeyId].ubLongPress = 0;
					SetKeyPadEvent(sButton[ubKeyId].iLongReleaseId);	
					ClearComboKey(sButton[ubKeyId].ulKeyFlag << 16);
					printc("Release Long Key %s\r\n",sButton[ubKeyId].ubkeyname);
				}
						
				sButton[ubKeyId].ulKeyCount = 0;
			}
			
			sButton[ubKeyId].ulKeyLastValue = tempValue;
			sButton[ubKeyId].ulKeyLastTime  = ulNow;
            //break;
        }
    }

	if (gTmKeypadHook)
		(TMHOOK)gTmKeypadHook();
		
#ifdef CFG_KEY_MEASURE_ADX2003 //may be defined in config_dv178.h
	// Clear ADX2003 power key status
	ADX2003_Measure_Power_Key();
#endif
}

void IR_Key_Detection(void)
{
#if (SUPPORT_IR_CONVERTER)
	MMP_UBYTE	ubKeyId;
	MMP_UBYTE 	i;
	int			ir_code;
	MMP_ULONG	uiLCDstatus;
	static int	int_cnt = 0;
	static int	pre_ubKeyId = -1;
	static int	idle_cnt = 0;
		
    if (!AHC_KeyUIWorking())
    	return;
    	
	AHC_GetParam(PARAM_ID_LCD_STATUS, &uiLCDstatus);
	ir_code = IR_CheckInterruptGpio();
	
	if ((ir_code != 0) && ((ir_code >> 16) != 0xff)) {
		printc("GOT IR 0x%08x, \r\n", ir_code);
		int_cnt++;
		idle_cnt = 0;

		for(i=0; i<NUM_IR_KEY; i++) {
			ubKeyId = (!uiLCDstatus)?(i):(sIRButton[i].ubKeyPairId);

			if(ubKeyId == IR_STATE_ID_INVALID)
				ubKeyId = i;

			if (sIRButton[ubKeyId].ulKeyValue == (unsigned short)ir_code /* little endian */) {
				if (pre_ubKeyId != ubKeyId) {
					if (pre_ubKeyId != -1) {
						printc("1. IR RELEASE - %s\r\n", sIRButton[(MMP_UBYTE) pre_ubKeyId].ubkeyname);
						SetKeyPadEvent(sIRButton[pre_ubKeyId].iReleaseId);
					}

					SetKeyPadEvent(sIRButton[ubKeyId].iPressId);
					pre_ubKeyId = ubKeyId;
					printc("IR Key Press %s Sent %d\r\n", sIRButton[ubKeyId].ubkeyname, sIRButton[ubKeyId].iPressId);
					int_cnt = 1;
				}
				else
				{ 
					if (int_cnt == 1) {
						if (pre_ubKeyId != -1) {
							printc("2. IR RELEASE - %s\r\n", sIRButton[(MMP_UBYTE) pre_ubKeyId].ubkeyname);
							SetKeyPadEvent(sIRButton[pre_ubKeyId].iReleaseId);
						}

						SetKeyPadEvent(sIRButton[ubKeyId].iPressId);
						pre_ubKeyId = ubKeyId;
						printc("IR Key Press %s Sent %d\r\n", sIRButton[ubKeyId].ubkeyname, sIRButton[ubKeyId].iPressId);
					}
					else if ((int_cnt % 10) == 0)
					{
						SetKeyPadEvent(sIRButton[ubKeyId].iLongPressId);
						printc("IR Key LongPress %s Sent %d\r\n", sIRButton[ubKeyId].ubkeyname, sIRButton[ubKeyId].iLongPressId);
					}
				}
			}
		}
	} 
	else {
		if (int_cnt != 0)
		{
			if ((pre_ubKeyId != -1) && (idle_cnt > 4))
			{
				printc("3. IR RELEASE - %s\r\n", sIRButton[pre_ubKeyId].ubkeyname);
				SetKeyPadEvent(sIRButton[pre_ubKeyId].iReleaseId);

				pre_ubKeyId = -1;
				idle_cnt = 0;
				int_cnt = 0;
			}
			else	
				idle_cnt++;		
		}
	}
#endif
}


//PC/adaptor plugs in/out.
void USB_Cable_In(UINT8 in)
{
    //case USB_CABLE_IN:
    if(in){
        VideoPowerOffCounterReset();

        if(AHC_GetShutdownByChargerOut()==AHC_TRUE)
            AHC_SetShutdownByChargerOut(AHC_FALSE);

        SetKeyPadEvent(USB_CABLE_IN);
    }
    else{
        SetKeyPadEvent(USB_CABLE_OUT);
    }
}

void USB_BDevice_In(UINT8 in)
{
    AHC_USB_PauseDetection(1);
    
    if(in){
        AHC_SetCurKeyEventID(BUTTON_USB_B_DEVICE_DETECTED);
        AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_USB_B_DEVICE_DETECTED, 0);
    }
    else{
        AHC_SetCurKeyEventID(BUTTON_USB_B_DEVICE_REMOVED);
        AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_USB_B_DEVICE_REMOVED, 0);
    }
}


void Device_Detection(void)
{
    UINT32 		i;
    MMP_ULONG 	ulNow;
    UINT32		uiLCDstatus;
    static MMP_UBYTE ubDetectCnt=0;

    if(!gAHC_InitialDone)
        return;

    ubDetectCnt = (ubDetectCnt+1)%5;
    
    if(ubDetectCnt>0)
        return;
    
    MMPF_OS_GetTime(&ulNow);   
    AHC_GetParam(PARAM_ID_LCD_STATUS,&uiLCDstatus);
    
    for( i=0; i<gNumOfDevice; i++ )
    {
        MMP_UBYTE tempValue = 0;
        
		if(sDeviceStatus[i].piopin == MMP_GPIO_MAX) {
		    if (sDeviceStatus[i].iPressId == DEVICES_READY) {
		    	sDeviceStatus[i].iPressId = 0;
		    	// Send an event after ALL of devices initialized
		    	SetKeyPadEvent(DEVICES_READY);
		    }
			continue;
		}
        
        MMPS_PIO_GetData( sDeviceStatus[i].piopin, &tempValue);

        if( sDeviceStatus[i].ulKeyLastValue == tempValue )
        {
            //NOP.  Keep the current status.
            sDeviceStatus[i].ulKeyLastTime = ulNow;
        }
        else if ( (ulNow - sDeviceStatus[i].ulKeyLastTime) > sDeviceStatus[i].ulDebounceTime )
        {
            // If state change
            #ifdef CFG_KEY_DO_COVER_ACTION //may be defined in config_xxx.h
            if (sDeviceStatus[i].iPressId == DEVICE_LCD_COVERED) {
            	doCoverAction(&sDeviceStatus[i], tempValue, ulNow);
            	continue;
            }
			#endif
            
            if( tempValue == sDeviceStatus[i].ulPressLevel )
            {
            	switch(sDeviceStatus[i].iPressId)
            	{
            		case DC_CABLE_IN:
            			VideoPowerOffCounterReset();
            			
            			if(AHC_GetShutdownByChargerOut()==AHC_TRUE)
            				AHC_SetShutdownByChargerOut(AHC_FALSE);

            			SetKeyPadEvent(sDeviceStatus[i].iPressId);
            		break;

            		#if (FLIP_CTRL_METHOD & CTRL_BY_HALL_SNR) 
            		case DEVICE_LCD_INV:
            			AHC_SetRotateSrc(SRC_HALL_SNR);
            			if(MenuSettingConfig()->uiLCDRotate==LCD_ROTATE_ON)
            				SetKeyPadEvent(DEVICE_LCD_NOR);
            			else
            				SetKeyPadEvent(DEVICE_LCD_INV);
            		break;
            		#endif
            		
            		default:
            			SetKeyPadEvent(sDeviceStatus[i].iPressId);
            		break;
            	}
            	
                printc("@@@ Device %s is plugged in\r\n",sDeviceStatus[i].ubkeyname);
            }
            else
            {
            	switch(sDeviceStatus[i].iReleaseId)
            	{
            		#if (FLIP_CTRL_METHOD & CTRL_BY_HALL_SNR) 
            		case DEVICE_LCD_NOR :
            			AHC_SetRotateSrc(SRC_HALL_SNR);
	            		if(MenuSettingConfig()->uiLCDRotate==LCD_ROTATE_ON)
	            			SetKeyPadEvent(DEVICE_LCD_INV);
	            		else
	            			SetKeyPadEvent(DEVICE_LCD_NOR);
	            	break;
	            	#endif
	            	
	            	default:
	            		SetKeyPadEvent(sDeviceStatus[i].iReleaseId);
	            	break;
            	}
               
                printc("@@@ Device %s is plugged out\r\n",sDeviceStatus[i].ubkeyname);                    
            }

            sDeviceStatus[i].ulKeyLastValue = tempValue;
            sDeviceStatus[i].ulKeyLastTime  = ulNow;
        }
    }
}

void ADC_AUX1_Detection_Once(void)
{	
#if (BATTERY_DETECTION_EN)
	MMP_UBYTE i = 0;
	MMP_ULONG ulVoltageLevelSum	   	 = 0;
	MMP_ULONG ulBatteryDetectCounter = 0;

    if(!gAHC_InitialDone)
        return;
    
	for (i = 0; i < 4; i++)
	{
        MMP_ULONG ulLevel = 0;
        MMP_UBYTE ubSource = 0;

        AHC_PMUCtrl_ADC_Measure_Key(&ulLevel, &ubSource, BATTERY_DETECT_ADC_CHANNEL);
        ulVoltageLevelSum += ulLevel * REAL_BAT_VOLTAGE_RATIO_M / REAL_BAT_VOLTAGE_RATIO_N;
        ulBatteryDetectCounter++;
        MMPF_OS_Sleep_MS(10);
	}
	
	if (ulBatteryDetectCounter >= 4)
	{	  
		ulVoltageLevelSum /= ulBatteryDetectCounter;

		if(ulVoltageLevelSum > BATT_FULL_LEVEL)
			MenuSettingConfig()->uiBatteryVoltage = BATTERY_VOLTAGE_FULL;
		else if((ulVoltageLevelSum > BATT_LEVEL_2) && (ulVoltageLevelSum <= BATT_FULL_LEVEL))
			MenuSettingConfig()->uiBatteryVoltage = BATTERY_VOLTAGE_LEVEL_2;
		else if((ulVoltageLevelSum > BATT_LEVEL_1) && (ulVoltageLevelSum <= BATT_LEVEL_2))
			MenuSettingConfig()->uiBatteryVoltage = BATTERY_VOLTAGE_LEVEL_1;
		else if((ulVoltageLevelSum > BATT_LEVEL_0) && (ulVoltageLevelSum <= BATT_LEVEL_1))
			MenuSettingConfig()->uiBatteryVoltage = BATTERY_VOLTAGE_LEVEL_0;
		else if((ulVoltageLevelSum <= BATT_LEVEL_0)) 
			MenuSettingConfig()->uiBatteryVoltage = BATTERY_VOLTAGE_EMPTY;	

		SetKeyPadEvent(BUTTON_BATTERY_DETECTION);
	}
#else
	MenuSettingConfig()->uiBatteryVoltage = BATTERY_VOLTAGE_FULL;
#endif
}

void ADC_AUX1_Detection(void)
{	
    MMP_UBYTE battery_level_temp = 0;

    if(!gAHC_InitialDone)
        return;

// do not controlled by BATTERY_DETECTION_EN
// Just test SAR-ADC function
#if (ENABLE_BATTERY_DET_DEBUG)
    {
        static skipMonitorTimes = BATTERY_DETECT_PERIOD >> 1;
        static preBatteryVoltage = 0;
        UINT32 level = 0;
        UINT8 source;

        if(skipMonitorTimes > 0xF0)
        {
            skipMonitorTimes++;
        }
        else if (skipMonitorTimes > 0)
        {
            skipMonitorTimes--;
            return;
        }
        else
        {
            skipMonitorTimes = BATTERY_DETECT_PERIOD >> 1;
        }

        AHC_PMUCtrl_ADC_Measure_Key(&level, &source, BATTERY_DETECT_ADC_CHANNEL);
        level = level * REAL_BAT_VOLTAGE_RATIO_M / REAL_BAT_VOLTAGE_RATIO_N;
        
        if (preBatteryVoltage != level) {
            printc("Monitor Battery Level = %d\r\n", level);
            preBatteryVoltage = level;
        }
    }
#endif

#if (BATTERY_DETECTION_EN == 0)
    return;
#endif

#ifdef CFG_DRAW_ALWAYS_FULL_CHARGE_ICON
	if (AHC_TRUE == AHC_GetChargerStatus()) {
		uVoltageLevelSum = BATTERY_VOLTAGE_FULL;
		MenuSettingConfig()->uiBatteryVoltage = BATTERY_VOLTAGE_FULL;
		uBatteryDetectCounter = 0;
        uSkipDetectNum = 0;
		#if (OSD_SHOW_BATTERY_STATUS==1)
		AHC_SetChargingID(3);
		#endif
		
		return;
	}
#elif (CHARGE_FULL_NOTIFY==0)
    if(AHC_TRUE == AHC_GetChargerStatus())
    {
        uSkipDetectNum = 0;
        MenuSettingConfig()->uiBatteryVoltage = BATTERY_VOLTAGE_CHARGING; //TBD
        return;
    }
#endif

    if(uSkipDetectNum > 0xF0)
    {    
        uSkipDetectNum++;
    }
    else if(uSkipDetectNum > 0)
    {
        uSkipDetectNum--;
        return;
    }
    else
    {    
        uSkipDetectNum = BATTERY_DETECT_PERIOD;
    }

#if (CHARGE_FULL_NOTIFY)

    if(AHC_TRUE == AHC_GetChargerStatus() || UI_MSDC_STATE == uiGetCurrentState() || UI_PCCAM_STATE == uiGetCurrentState())
    {
        MenuSettingConfig()->uiBatteryVoltage = BATTERY_VOLTAGE_CHARGING; //TBD

		{
			MMP_UBYTE ubChargeStatus = !CHARGE_FULL_STATUS;
			
            #ifdef GPIO_CHARGE_STATUS
            if (GPIO_CHARGE_STATUS != MMP_GPIO_MAX) {
                AHC_ConfigGPIOPad(GPIO_CHARGE_STATUS, PAD_OUT_DRIVING(0) | PAD_SCHMITT_TRIG | PAD_PULL_UP);
                AHC_ConfigGPIO(GPIO_CHARGE_STATUS, MMP_FALSE);
                AHC_GetGPIO(GPIO_CHARGE_STATUS, &ubChargeStatus);
            }
			#endif
			
			if(ubChargeStatus != CHARGE_FULL_STATUS)
			{
				bChargeFull = AHC_FALSE;
				#if OSD_SHOW_BATTERY_STATUS
				AHC_EnableChargingIcon(AHC_TRUE);
				#endif
			}
			else
			{	
				if(!bChargeFull)
				{
					printc(FG_GREEN("CHARGING COMPLETE\r\n"));

					#ifdef CHARGE_FULL_LED
					/* When USB plug out to OFF it? */
					LedCtrl_ButtonLed(CHARGE_FULL_LED, AHC_TRUE);
					#endif
					#if (OSD_SHOW_BATTERY_STATUS==1)
					AHC_SetChargingID(3);
					#endif
					
					#if (OSD_SHOW_BATTERY_STATUS==0)
					bChargeFull = AHC_TRUE;
					#else
					/*
					if(AHC_FALSE==AHC_DrawChargingIcon())//Return AHC_FALSE means not use task to drawing charging icons. 
					{
						MenuSettingConfig()->uiBatteryVoltage = BATTERY_VOLTAGE_FULL;
						SetKeyPadEvent(BUTTON_BATTERY_DETECTION);
					}
					*/
					bChargeFull = AHC_TRUE;
					AHC_EnableChargingIcon(AHC_FALSE);
					#endif
				}
			}
		}

        return;
    }
#endif

    {
        UINT32 level = 0;
        UINT8 source;

        AHC_PMUCtrl_ADC_Measure_Key(&level, &source, BATTERY_DETECT_ADC_CHANNEL);
        level = level * REAL_BAT_VOLTAGE_RATIO_M / REAL_BAT_VOLTAGE_RATIO_N;
        battery_level_temp = MenuSettingConfig()->uiBatteryVoltage;

        if ((MenuSettingConfig()->uiBatteryVoltage == BATTERY_VOLTAGE_EMPTY) ||
            (MenuSettingConfig()->uiBatteryVoltage == BATTERY_VOLTAGE_LEVEL_0))
        {
            uBatteryDetectCounter += 2;
            uVoltageLevelSum += 2*level;
            
        }
        else
        {
            uBatteryDetectCounter++;
            uVoltageLevelSum += level;
        }

        //uVoltageLevelSum += level;
        
        if (uBatteryDetectCounter >= 4)
        {
            uVoltageLevelSum = uVoltageLevelSum / uBatteryDetectCounter;

            if(uVoltageLevelSum > BATT_FULL_LEVEL)
                MenuSettingConfig()->uiBatteryVoltage = BATTERY_VOLTAGE_FULL;
            else if((uVoltageLevelSum > BATT_LEVEL_2) && (uVoltageLevelSum <= BATT_FULL_LEVEL))
                MenuSettingConfig()->uiBatteryVoltage = BATTERY_VOLTAGE_LEVEL_2;
            else if((uVoltageLevelSum > BATT_LEVEL_1) && (uVoltageLevelSum <= BATT_LEVEL_2))
                MenuSettingConfig()->uiBatteryVoltage = BATTERY_VOLTAGE_LEVEL_1;
            else if((uVoltageLevelSum > BATT_LEVEL_0) && (uVoltageLevelSum <= BATT_LEVEL_1))
                MenuSettingConfig()->uiBatteryVoltage = BATTERY_VOLTAGE_LEVEL_0;
            else if((uVoltageLevelSum <= BATT_LEVEL_0)) 
            {
                RTNA_DBG_Str(0, "\r\n--W-- Low Battery !!!\r\n \
                                 --W-- Low Battery !!!\r\n \
                                 --W-- Low Battery !!!\r\n\r\n");

#ifdef CFG_POWER_CUS_EMPTY_BATTERY_FUNC //may be defined in config_xxx.h
                CFG_POWER_CUS_EMPTY_BATTERY_FUNC();
#else
				#ifdef CFG_BATTERY_EMPTY_IMMEDIATE_POWER_OFF
				// Do not check MenuSettingConfig()->uiBatteryVoltage
				#else
                if(MenuSettingConfig()->uiBatteryVoltage == BATTERY_VOLTAGE_EMPTY)
                #endif
                {
                	extern void uiBlockEvent(int arg);

					// Stop video record ASAP
					if (VideoFunc_RecordStatus())
					{
						StateVideoRecMode_StopRecordingProc(EVENT_VIDEO_KEY_RECORD);
						AHC_WaitVideoWriteFileFinish();
					}

					uiBlockEvent(1);	// In Power Off progress, not to service any message any more.
				    RTNA_DBG_Str(0, "\r\nSystem will be shutdown ...\r\n");

					// Waiting for UI idle - In DSC Capture will cause system dead lock
					while (0 == AHC_KeyUIWorking()) {
						AHC_OS_SleepMs(100);
						RTNA_DBG_Str(0, "z");
					}

                	AHC_WMSG_Draw(AHC_TRUE, WMSG_GOTO_POWER_OFF, BATTERY_LOW_WARNNING_TIME);
                	AHC_OS_SleepMs(CFG_BATTERY_EMPTY_WARNING_DELAY_TIME);

					// Waiting for UI idle - In DSC Capture will cause system dead lock
					while (0 == AHC_KeyUIWorking()) {
						AHC_OS_SleepMs(100);
						RTNA_DBG_Str(0, "z");
					}
						
    				// printc("BATTERY_VOLTAGE_EMPTY. Turn off system.\r\n");
                    // Call Power Off directly, because to send a POWER OFF message may not be serviced!
                    // when there are some messages are waiting in queue!!
                    AHC_NormalPowerOffPathEx(AHC_TRUE, AHC_TRUE, AHC_TRUE);
                    //SetKeyPadEvent(KEY_POWER_OFF);
                }

                MenuSettingConfig()->uiBatteryVoltage = BATTERY_VOLTAGE_EMPTY;
#endif
            }

#ifdef CFG_CUS_BAT_SHOW_BY_LED_FUNC
			CFG_CUS_BAT_SHOW_BY_LED_FUNC();
#endif

#if (ENABLE_BATTERY_DET_DEBUG)
		    printc("\r\nMenuSettingConfig()->uiBatteryVoltage = %d\r\n", MenuSettingConfig()->uiBatteryVoltage);
		    printc("Average Battery Level = %d\r\n\r\n", uVoltageLevelSum);
#endif
            
            if((MenuSettingConfig()->uiBatteryVoltage != BATTERY_VOLTAGE_EMPTY) && (battery_level_temp != MenuSettingConfig()->uiBatteryVoltage))
            {
                SetKeyPadEvent(BUTTON_BATTERY_DETECTION);
            }

			uVoltageLevelSum = 0;
			uBatteryDetectCounter = 0;
        }
    } 
}

void ADC_AUX2_Detection(void)
{
#if (ADC_KEY_EN==1)

    MMP_USHORT 	saradc_data = 0;
	UINT32		uiLCDstatus;
	MMP_UBYTE 	i, ubOutRegionCnt = 0;
	
    if (!AHC_KeyUIWorking())
    	return;

    AHC_SARADC_ReadData(ADC_KEY_SARADC_CHANNEL, &saradc_data);

    //Print below to check ADC key voltage, ex: ADC_KEY_VOLT_REC
    //printc("ADC voltage = %d\r\n", saradc_data);
    
    AHC_GetParam(PARAM_ID_LCD_STATUS, &uiLCDstatus);

	for(i=0; i<gNumOfADCKey; i++)
	{
		MMP_ULONG UpBound  = sADCButton[i].ulKeyVolt + sADCButton[i].ulKeyMargin;
		MMP_ULONG LowBound = sADCButton[i].ulKeyVolt - sADCButton[i].ulKeyMargin;
		MMP_UBYTE ubKeyId  = i;
        
		if (sADCButton[i].ubKeyStateId == ADCPRESS_NONE)
		{
			ubOutRegionCnt++;
			continue;
	    }
	        
		if(sADCButton[i].ulKeyVolt < sADCButton[i].ulKeyMargin)
			LowBound = 0;
        
		if ( saradc_data <= UpBound && saradc_data >= LowBound )
		{  
        
#if (HALL_SNR_FLIP_SELECT & FLIP_OSD) || (KEY_FLIP_SELECT & FLIP_OSD) || (KEYPAD_ROTATE_EN==1)      
			if(gADCKeyLongPress==AHC_FALSE)
				ubKeyId = (!uiLCDstatus)?(i):(sADCButton[i].ubKeyPairId);
			else
				ubKeyId	= gADCKeyStatus;
#endif        
        
			if(ubKeyId == ADC_STATE_ID_INVALID)
				ubKeyId = i;

#if (DIR_KEY_CYCLIC_LPRESS_EN)
			if(sADCButton[ubKeyId].ubKeyStateId <= ADCPRESS_R && //For Direction Key
			   sADCButton[ubKeyId].ubKeyStateId >= ADCPRESS_U)
			{
				if((gADCKeyStatus != sADCButton[ubKeyId].ubKeyStateId) || 
				  ((gADCKeyStatus == sADCButton[ubKeyId].ubKeyStateId) && (gADCKeyPressCnt == 0)) )
				{
					gADCKeyStatus 	= sADCButton[ubKeyId].ubKeyStateId;
					gADCKeyPressCnt = 0;
					printc("ADC Press %s %d\r\n",sADCButton[ubKeyId].ubkeyname, sADCButton[ubKeyId].ubKeyCount);
					SetKeyPadEvent(sADCButton[ubKeyId].iPressId);
					AHC_SetButtonStatus(sADCButton[ubKeyId].iPressId);
					SetComboKey(sADCButton[ubKeyId].ulKeyFlag);
		        }
		        
				if((gADCKeyStatus == sADCButton[ubKeyId].ubKeyStateId) 	&&
					(ADC_KEY_LONG_PRESS_CNT*2==sADCButton[ubKeyId].ubKeyCount) )
				{
					gADCKeyLongPress = MMP_TRUE;
					printc("ADC LPress %s %d\r\n",sADCButton[ubKeyId].ubkeyname, sADCButton[ubKeyId].ubKeyCount);
					SetKeyPadEvent(sADCButton[ubKeyId].iLongPressId);
					AHC_SetButtonStatus(sADCButton[ubKeyId].iLongPressId);
					SetComboKey(sADCButton[ubKeyId].ulKeyFlag << 16);
				}
			}
			else
#endif			
			{
				if(gADCKeyStatus != sADCButton[ubKeyId].ubKeyStateId)
				{
					gADCKeyStatus 	= sADCButton[ubKeyId].ubKeyStateId;
					gADCKeyPressCnt = 0;
					printc("ADC Press %s %d\r\n",sADCButton[ubKeyId].ubkeyname, sADCButton[ubKeyId].ubKeyCount);
					SetKeyPadEvent(sADCButton[ubKeyId].iPressId);
					AHC_SetButtonStatus(sADCButton[ubKeyId].iPressId);
					SetComboKey(sADCButton[ubKeyId].ulKeyFlag);
		        }
				else if((gADCKeyStatus == sADCButton[ubKeyId].ubKeyStateId) 	&&
						(ADC_KEY_LONG_PRESS_CNT*2==sADCButton[ubKeyId].ubKeyCount) )
				{
					gADCKeyStatus 	 = sADCButton[ubKeyId].ubKeyStateId;
					gADCKeyLongPress = MMP_TRUE;
					printc("ADC LPress %s %d\r\n",sADCButton[ubKeyId].ubkeyname, sADCButton[ubKeyId].ubKeyCount);
					SetKeyPadEvent(sADCButton[ubKeyId].iLongPressId);
					AHC_SetButtonStatus(sADCButton[ubKeyId].iLongPressId);
					SetComboKey(sADCButton[ubKeyId].ulKeyFlag << 16);
				}
			}
	
			gADCKeyPressCnt = (gADCKeyPressCnt + 1) % ADC_KEY_LONG_PRESS_CNT;  
			sADCButton[ubKeyId].ubKeyCount++;
            break;
		}
		else
		{
			ubOutRegionCnt++;
		}
	}

	if(ubOutRegionCnt==gNumOfADCKey && gADCKeyStatus!=ADCPRESS_MAX && gADCKeyStatus!=ADCPRESS_NONE)
	{
		printc("ADC Release %s\r\n",sADCButton[gADCKeyStatus].ubkeyname);
		
		if(gADCKeyLongPress)
		{
			SetKeyPadEvent(sADCButton[gADCKeyStatus].iLongReleaseId);
			ClearComboKey(sADCButton[gADCKeyStatus].ulKeyFlag << 16);
		}
		else
		{		
			SetKeyPadEvent(sADCButton[gADCKeyStatus].iReleaseId);
			ClearComboKey(sADCButton[gADCKeyStatus].ulKeyFlag);
		}
		
		sADCButton[gADCKeyStatus].ubKeyCount = 0;
		gADCKeyStatus 		= ADCPRESS_NONE;
		gADCKeyPressCnt		= 0;
		gADCKeyLongPress 	= MMP_FALSE;
		ubOutRegionCnt		= 0;
    }    
        
#endif    	
}

void ADC_BatteryTemperature_Detection(void)
{
#ifdef CFG_MONITOR_BATTERY_TEMPERATURE
    static MMP_ULONG uBatteryTempDetectCounter = 0;
    static MMP_ULONG uTempVoltageLevelSum = 0;
    static MMP_UBYTE uSkipTempDetectNum = (0xFF - 0x04);
    MMP_USHORT saradc_data = 0;

    if(!gAHC_InitialDone)
        return;

    if (uSkipTempDetectNum > 0xF0)
    {    
        uSkipTempDetectNum++;
    }
    else if (uSkipTempDetectNum > 0)
    {
        uSkipTempDetectNum--;

        return;
    }
    else
    {    
        uSkipTempDetectNum = BATTERY_DETECT_PERIOD;
    }

    AHC_SARADC_ReadData(TEMPERATURE_SARADC_CHANNEL, &saradc_data);
	
    uBatteryTempDetectCounter++;
    uTempVoltageLevelSum += saradc_data;

    if (uBatteryTempDetectCounter >= 4)
    {
        uTempVoltageLevelSum = uTempVoltageLevelSum / uBatteryTempDetectCounter;

        #if (ENABLE_BATTERY_TEMP_DEBUG) 
        printc("Battery Temperature Level = %d\r\n", uTempVoltageLevelSum);
        #endif
        
        #ifdef GPIO_CHARGE_ENABLE
        if (GPIO_CHARGE_ENABLE != MMP_GPIO_MAX) {
            AHC_ConfigGPIOPad(GPIO_CHARGE_ENABLE, PAD_OUT_DRIVING(0));
            AHC_ConfigGPIO(GPIO_CHARGE_ENABLE, AHC_TRUE); 

            if (uTempVoltageLevelSum < BATTERY_HIGH_TEMP_LEVEL) {
                RTNA_DBG_Str(0, "--W-- Battery Temperature is too high !!!\r\n");
                RTNA_DBG_Str(0, "--W-- Shutdown battery charger !!!\r\n");
            	AHC_SetGPIO(GPIO_CHARGE_ENABLE, (0 == GPIO_CHARGE_ENABLE_LEVEL) ? 1 : 0);
            }
            else {
            	AHC_SetGPIO(GPIO_CHARGE_ENABLE, (0 == GPIO_CHARGE_ENABLE_LEVEL) ? 0 : 1);
            }
        }
        #endif
        
		uTempVoltageLevelSum = 0;
		uBatteryTempDetectCounter = 0;
    }
#endif
}

void UpdateVideoCurrentTimeStamp(void);
void UIKeyTask(void)
{
    MMP_ULONG      ulKeyEvent;
    MMPF_OS_FLAGS  flags;
	MMPF_OS_FLAGS  waitflags;
    MMP_ULONG      ulNow;

#if (KEYPAD_DETECT_METHOD == KEYPAD_DETECT_TASK)
    UITaskReady = MMP_TRUE;
#endif

#if (TASK_MONITOR_ENABLE)
    memcpy(&gsTaskMonitorUIKey.TaskName[0], __func__, TASK_MONITOR_MAXTASKNAMELEN);
    gsTaskMonitorUIKey.sTaskMonitorStates = MMPF_TASK_MONITOR_STATES_WAITING;
    gsTaskMonitorUIKey.ulExecTime = 0;
    memset((void *)gsTaskMonitorUIKey.ParaArray, 0x0, sizeof(gsTaskMonitorUIKey.ParaArray)); 
    gsTaskMonitorUIKey.ulParaLength = 0;    
    gsTaskMonitorUIKey.pTimeoutCB = (TASK_MONITOR_TimeoutCallback *)NULL;       
    MMPF_TaskMonitor_RegisterTask(&gsTaskMonitorUIKey);
#endif

	waitflags = CDV_KEYPAD_FLAG | CDV_TIME_FLAG;
	#if (UPDATE_UI_USE_MULTI_TASK)
	waitflags |= CDV_UI_FLAG;
	#endif
	
    while(1){
        MMPF_OS_WaitFlags(CDV_UI_Flag, waitflags, 
        MMPF_OS_FLAG_WAIT_SET_ANY|MMPF_OS_FLAG_CONSUME, 0, &flags);

#if (TASK_MONITOR_ENABLE)
        MMPF_OS_GetTime(&gsTaskMonitorUIKey.ulExecTime);
        gsTaskMonitorUIKey.sTaskMonitorStates = MMPF_TASK_MONITOR_STATES_RUNNING;    
        *(MMP_ULONG *)(gsTaskMonitorUIKey.ParaArray) = (MMP_ULONG)flags;
        gsTaskMonitorUIKey.ulParaLength = sizeof(MMP_ULONG); 
#endif

        if (flags & CDV_TIME_FLAG) {
            // The KeyTask priority is higher then NETWORK to update Video Time Stamp for better performance.
            UpdateVideoCurrentTimeStamp();
        }

		#if (UPDATE_UI_USE_MULTI_TASK)
        if (flags & CDV_UI_FLAG) {
            DrawStateVideoRecUpdate(EVENT_VIDREC_UPDATE_MESSAGE);
        }		
		#endif

        if (flags & CDV_KEYPAD_FLAG) {
            MMPF_OS_GetTime(&ulNow);

            GetKeyPadEvent(&ulKeyEvent);

#if (SUPPORT_TOUCH_PANEL)
            if(ulKeyEvent == TOUCH_PANEL_PRESS || ulKeyEvent == TOUCH_PANEL_REL)
            {
                UINT32	dir;
                MMP_UBYTE	finger;
                MMP_ERR status;

                AHC_GetParam(PARAM_ID_LCD_STATUS, &dir);
                status = AHC_TouchPanel_CheckUpdate(&ulKeyEvent, &ulNow, dir, &finger);
                /*if(finger  == FINGER_NONE) {
                    printc("Skip This KeyEvent [%d]\r\n", ulKeyEvent);
					ulKeyEvent = KEYPAD_NONE;
                }*/
            }
#endif

            if( ulKeyEvent != KEYPAD_NONE ) {
                AHC_SendAHLMessage(AHLM_GPIO_BUTTON_NOTIFICATION, ulKeyEvent, ulNow);
            }
        }

#if (TASK_MONITOR_ENABLE)
        gsTaskMonitorUIKey.sTaskMonitorStates = MMPF_TASK_MONITOR_STATES_WAITING;
#endif
    }
}

extern MMPF_OS_FLAGID   	UartCtrlFlag;
extern AHC_BOOL blockRealIDUIKeyTask;

#if (EDOG_ENABLE == 1)
extern MMP_HANDLE        *hGps;
//Eog I/O wrap functions.
//====================================
#include "EDOG_ctl.h"

EDOG_ERR EDOGIO_FS_OPEN_Wrap(char *pFileName, char *pMode, unsigned int *ulFileID)
{
    AHC_ERR sRet = AHC_ERR_NONE;
    
    sRet = AHC_FS_FileOpen(pFileName, AHC_StrLen(pFileName), pMode, AHC_StrLen(pMode), ulFileID);
    if(sRet != AHC_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); return EDOG_ERR_FS_FAIL;}   
    return EDOG_ERR_NONE;
}

EDOG_ERR EDOGIO_FS_CLOSE_Wrap(unsigned int ulFileID)
{
    AHC_ERR sRet = AHC_ERR_NONE;

    sRet = AHC_FS_FileClose(ulFileID);
    if(sRet != AHC_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); return EDOG_ERR_FS_FAIL;}   
    return EDOG_ERR_NONE;    
}

EDOG_ERR EDOGIO_FS_READ_Wrap(unsigned int ulFileID, unsigned char *pData, unsigned int NumBytes, unsigned int *read_count)
{
    AHC_ERR sRet = AHC_ERR_NONE;

    sRet = AHC_FS_FileRead(ulFileID, pData, NumBytes, read_count);
    if(sRet != AHC_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); return EDOG_ERR_FS_FAIL;}   
    return EDOG_ERR_NONE;    
}

EDOG_ERR EDOGIO_FS_WRITE_Wrap(unsigned int ulFileID, unsigned char *pData, unsigned int NumBytes, unsigned int *write_count)
{
    AHC_ERR sRet = AHC_ERR_NONE;

    sRet = AHC_FS_FileWrite(ulFileID, pData, NumBytes, write_count);
    if(sRet != AHC_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); return EDOG_ERR_FS_FAIL;}   
    return EDOG_ERR_NONE;    
}

EDOG_ERR EDOGIO_FS_SEEK_Wrap(unsigned int ulFileID, long long llOffset, int lOrigin)
{
    AHC_ERR sRet = AHC_ERR_NONE;

    //Note 
    //EDOG_FS_SEEK_SET -> AHC_FS_SEEK_SET
    //EDOG_FS_SEEK_CUR -> AHC_FS_SEEK_CUR
    //EDOG_FS_SEEK_END -> AHC_FS_SEEK_END
    sRet = AHC_FS_FileSeek(ulFileID, llOffset, lOrigin);
    if(sRet != AHC_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); return EDOG_ERR_FS_FAIL;}   
    return EDOG_ERR_NONE;    
}

EDOG_ERR EDOGIO_FS_GetFileSize_Wrap(unsigned int ulFileID, unsigned int *ulFileSize)
{
    AHC_ERR sRet = AHC_ERR_NONE;

    sRet = AHC_FS_FileGetSize(ulFileID, ulFileSize);
    if(sRet != AHC_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); return EDOG_ERR_FS_FAIL;}   
    return EDOG_ERR_NONE;    
}

//pEDOGNmeaInfo EDOGIO_GPS_GetInfor_Wrap(void)
//{
//    //If customer's GPS format is not matched with pEDOGNmeaInfo, convert data here!    
//    return (pEDOGNmeaInfo)GPS_Information();
//}

EDOG_BOOL EDOGIO_GPS_IsAttached_Wrap(void)
{
    if(AHC_TRUE == AHC_GPS_Module_Attached()){
        return EDOG_TRUE;
    }
    return EDOG_FALSE;
}

void EDOGIO_LED_LcdBacklight_Wrap(AHC_BOOL bOn)
{
    LedCtrl_LcdBackLight(bOn);
}

EDOG_BOOL EDOGIO_LED_GetBacklightStatus_Wrap(void)
{
    if(AHC_TRUE == LedCtrl_GetBacklightStatus()){
        return EDOG_TRUE;
    }
    return EDOG_FALSE;
}

#if (SUPPORT_GPS == 1)
EDOG_BOOL EDOGIO_GPS_IsValidValue_Wrap(void)
{
    if(AHC_TRUE == GPSCtrl_GPS_IsValidValue())
    {
        return EDOG_TRUE;
    }
    return EDOG_FALSE;
}

void EDOGIO_RTC_GetTime_Wrap(EDOG_RTC_TIME *sEdogRTC_Time)
{
    //If customer's RTC format is not matched with EDOG_RTC_TIME, convert data here!    
    AHC_RTC_GetTime((AHC_RTC_TIME *)sEdogRTC_Time);
}

double EDOGIO_GPS_Dmm2Degree_DBL_Wrap(double dblLatLonDmm)
{
    return GpsDmmToDegree_double(dblLatLonDmm);
}

double EDOGIO_GPS_Degree2Dmm_DBL_Wrap(double dblLatLonDmm)
{
    return DegreeToGpsDmm_double(dblLatLonDmm);
}

float EDOGIO_GPS_Dmm2Degree_Float_Wrap(float dflLatLonDmm)
{
    return GpsDmmToDegree_float(dflLatLonDmm);
}

float EDOGIO_GPS_Degree2Dmm_Float_Wrap(float dflLatLonDmm)
{
    return DegreeToGpsDmm_float(dflLatLonDmm);
}
#endif //#if (SUPPORT_GPS == 1)
#endif //#if (EDOG_ENABLE == 1)

void RealIDUIKeyTask(void)
{
	MMP_UBYTE uCount;
#if (GPS_CONNECT_ENABLE)
	MMP_ULONG uCountForGPSTask = 0;
#endif

	AHC_WaitForBootComplete();

	/*
	 * Start to devices detect earlier to make all of devices initialized earlier,
	 * to make shorter period of lcd black
	 */
	Device_Detection();

    if(UITaskReady == MMP_TRUE)
    //if(gAHC_InitialDone == AHC_TRUE)
    {
#if (EDOG_ENABLE)
        EDOGCtrl_Register_IOFunctions(EDOGIO_FUNC_ENUM_PRINTF, (void *)printc);
                
        EDOGCtrl_Register_IOFunctions(EDOGIO_FUNC_ENUM_FS_OPEN, (void *)EDOGIO_FS_OPEN_Wrap);
        EDOGCtrl_Register_IOFunctions(EDOGIO_FUNC_ENUM_FS_CLOSE, (void *)EDOGIO_FS_CLOSE_Wrap);
        EDOGCtrl_Register_IOFunctions(EDOGIO_FUNC_ENUM_FS_READ, (void *)EDOGIO_FS_READ_Wrap);
        EDOGCtrl_Register_IOFunctions(EDOGIO_FUNC_ENUM_FS_WRITE, (void *)EDOGIO_FS_WRITE_Wrap);
        EDOGCtrl_Register_IOFunctions(EDOGIO_FUNC_ENUM_FS_SEEK, (void *)EDOGIO_FS_SEEK_Wrap);
        EDOGCtrl_Register_IOFunctions(EDOGIO_FUNC_ENUM_FS_GET_FILESIZE, (void *)EDOGIO_FS_GetFileSize_Wrap);
            
        //EDOGCtrl_Register_IOFunctions(EDOGIO_FUNC_ENUM_GPS_GETINFORMATION, (void *)EDOGIO_GPS_GetInfor_Wrap);
        EDOGCtrl_Register_IOFunctions(EDOGIO_FUNC_ENUM_GPS_ISATTACHED, (void *)EDOGIO_GPS_IsAttached_Wrap);
        EDOGCtrl_Register_IOFunctions(EDOGIO_FUNC_ENUM_LED_CTRL_LCDBACKLIGHT, (void *)EDOGIO_LED_LcdBacklight_Wrap);  
        EDOGCtrl_Register_IOFunctions(EDOGIO_FUNC_ENUM_LED_CTRL_BACKLIGHT_STATUS, (void *)EDOGIO_LED_GetBacklightStatus_Wrap);          
#if (SUPPORT_GPS == 1)
        EDOGCtrl_Register_IOFunctions(EDOGIO_FUNC_ENUM_GPS_ISVALIDVALUE, (void *)EDOGIO_GPS_IsValidValue_Wrap);
        EDOGCtrl_Register_IOFunctions(EDOGIO_FUNC_ENUM_GPS_DMM2DEGREE_DBL, (void *)EDOGIO_GPS_Dmm2Degree_DBL_Wrap);
        EDOGCtrl_Register_IOFunctions(EDOGIO_FUNC_ENUM_GPS_DEGREE2DMM_DBL, (void *)EDOGIO_GPS_Degree2Dmm_DBL_Wrap);
        EDOGCtrl_Register_IOFunctions(EDOGIO_FUNC_ENUM_GPS_DMM2DEGREE_FLOAT, (void *)EDOGIO_GPS_Dmm2Degree_Float_Wrap);
        EDOGCtrl_Register_IOFunctions(EDOGIO_FUNC_ENUM_GPS_DEGREE2DMM_FLOAT, (void *)EDOGIO_GPS_Degree2Dmm_Float_Wrap);
        EDOGCtrl_Register_IOFunctions(EDOGIO_FUNC_ENUM_RTC_GETTIME, EDOGIO_RTC_GetTime_Wrap);
#endif //#if (SUPPORT_GPS == 1)    
        EDOGCtrl_SetBaseName("SF:1:\\DB");
        EDOGCtrl_SetExtName(".bin");        
        EDOGCtrl_SetDistMethod(DIST_METHOD_GBL_CIRCLE_DIST);
        EDOGCtrl_SetPoiDataType(1); //1:for China, 0:for other  
        #if (C005_MANUALLY_ADD_SPEEDCAM_POI)
        EDOGCtrl_EnAddSpeedCamPOI(1);        
        #endif               
        //[Notice] Patent issue!!        
		#if 1
        EDOGCtrl_SetSpeedLvl(0);
        EDOGCtrl_SetSpeedDist(1000);
		#else
        //[Notice] +++ Patent issue!!
        //[Notice] --- Patent issue!!
		#endif
#endif //#if (EDOG_ENABLE)

#if (TASK_MONITOR_ENABLE)
        memcpy(&gsTaskMonitorRealIDUIKey.TaskName[0], __func__, TASK_MONITOR_MAXTASKNAMELEN);
        gsTaskMonitorRealIDUIKey.sTaskMonitorStates = MMPF_TASK_MONITOR_STATES_WAITING;
        gsTaskMonitorRealIDUIKey.ulExecTime = 0;
        memset((void *)gsTaskMonitorRealIDUIKey.ParaArray, 0x0, sizeof(gsTaskMonitorRealIDUIKey.ParaArray)); 
        gsTaskMonitorRealIDUIKey.ulParaLength = 0;    
        gsTaskMonitorRealIDUIKey.pTimeoutCB = (TASK_MONITOR_TimeoutCallback *)NULL;       
        MMPF_TaskMonitor_RegisterTask(&gsTaskMonitorRealIDUIKey);
#endif
    
        while(1)
        {
            uCount++;

#if (TASK_MONITOR_ENABLE)
            MMPF_OS_GetTime(&gsTaskMonitorRealIDUIKey.ulExecTime);
            gsTaskMonitorRealIDUIKey.sTaskMonitorStates = MMPF_TASK_MONITOR_STATES_RUNNING;    
            *(gsTaskMonitorRealIDUIKey.ParaArray) = uCount;
            gsTaskMonitorRealIDUIKey.ulParaLength = sizeof(MMP_UBYTE); 
#endif            
            
#if (GPS_CONNECT_ENABLE)
#if (GPS_CONFIG_NMEA_FILE == 0)
            if ((uCountForGPSTask++ % 5) == 0)
#else
            if ((uCountForGPSTask++ % 6) == 0)
#endif
            {
                MMPF_OS_SetFlags(UartCtrlFlag, GPS_FLAG_GETGPSPACK, MMPF_OS_FLAG_SET);
            }
#endif

            if (AHC_FALSE == blockRealIDUIKeyTask) {
                switch (uCount)
                {
                    default:
#ifdef CFG_KEY_SPEED_UP_AUX_DETECTION //may be defined in config_xxx.h
                        ADC_AUX1_Detection();
                        uCount = 0;
                    break;
#else
                        uCount = 1;     // Enter case 1 directly when the case of default is NOP.
#endif

                    case 1:
#ifdef SLIDE_MENU	//Fix OSD Collapses when pressing MENU button during Slide Menu is moving.
                        if (IsSlidingMenu()==0)
#endif
                        {
#ifdef CFG_BLOCK_KEY_EVENT_BEFORE_UI_INIT_DONE
                            if (ubUIInitDone())
#endif
                            {
                                GPIO_Key_Detection();
                                IR_Key_Detection();
                                PollingComboKey();
                            }
                        }

#ifdef SLIDE_STRING
                        SlideString();
#endif
                        break; 

                    case 2:
                        Device_Detection();

#if(SUPPORT_GSENSOR)
                        AHC_Gsensor_Polling(MOVE_BY_ACCELERATION);
#endif

#ifdef CFG_KEY_SPEED_UP_AUX_DETECTION //may be defined in config_xxx.h
                        // Customer ask to do more once to speed up detection cycle
                        ADC_AUX1_Detection();
#endif

#if (SUPPORT_GPS && defined(GPS_STATUS_LED))
                        if (GPSCtrl_ModuleConnected()) 
                        {
                            static int	_ledcnt = 0;

                            if (GPS_IsValidValue_NMEA0183()) {
                                LedCtrl_ButtonLed(GPS_STATUS_LED, _ledcnt & 0x04);
                            } else {
                                LedCtrl_ButtonLed(GPS_STATUS_LED, _ledcnt & 0x01);
                            }
                            _ledcnt++;
                        } 
                        else 
                        {
                            LedCtrl_ButtonLed(GPS_STATUS_LED, AHC_TRUE);
                        }
#endif
                        break;

                    case 3:
#ifdef SLIDE_MENU	//Fix OSD Collapses when pressing MENU button during Slide Menu is moving.
                        if(IsSlidingMenu()==0)
#endif
                        {
                            ADC_AUX2_Detection();
#if(SUPPORT_GSENSOR)
                            AHC_Gsensor_Polling(Z_AXIS_GRAVITY_CAHNGE);
#endif
                        }
                        break;

                    case 4:
                        ADC_AUX1_Detection();
                        ADC_BatteryTemperature_Detection();

#ifdef SLIDE_STRING
                        SlideString();
#endif
#ifdef SLIDE_MENU
                        SlideSubMenu();
#endif
                        break;

                    case 5:
                    {
                        UINT32		curtick;
						static UINT32           tickcount = 0;
                        MMP_BOOL ubActive;
#if (ADX2015_EN)
                        ADX2015_IsrHandler(0);
#endif

                        if(HDMI_Cable_Detection() == AHC_FALSE) {
                            TV_Cable_Detection();
                        }

                        MMPF_OS_GetTime(&curtick);
                        PowerSavingModeDetection(curtick);
                        LCDPowerSaveDetection(curtick);
                        VideoPowerOnOffDetection(curtick);
                        SpeakerPowerDetection();

						#if (EDOG_ENABLE)
	                    {
	                        static UINT8 ubEdogCount = 0;
	                        ubEdogCount += 1;
	                        if(ubEdogCount == 5) {
	                            if(uiGetCurrentState() != UI_SD_UPDATE_STATE && /*uiGetCurrentState() != UI_SYS_CALIBRATION_STATE &&*/ uiGetCurrentState() != UI_MSDC_STATE) {
	                            	EDOGCtrl_Handler(hGps);
	                            }
	                            ubEdogCount = 0;
	                        }
	                    }
	                    #endif

                        #if (UVC_HOST_VIDEO_ENABLE )
                        MMPD_Display_GetWinActive(REAR_CAM_WINDOW_ID, &ubActive );
                        if(( tickcount > 10 )&&(AHC_HostUVCVideoIsEnabled())&&ubActive)
                        {
                        	UINT16 Width;
							UINT16 Height;
                           AHC_Display_GetWidthHdight(&Width, &Height);
                           #if (SUPPORT_SONIX_UVC_ISO_MODE==1) 
                           if(gbRearState == AHC_FALSE && AHC_TRUE ==  AHC_HostUVCSonixReverseGearDetection())
						   #else	
                           if(gbRearState == AHC_FALSE && AHC_TRUE ==  AHC_HostUVC_GetReversingGearStatus())
                           #endif
                            {
                                gbRearState = AHC_TRUE;
                            //    DrawRearCamReverseLine(AHC_TRUE);
                                AHC_HostUVCVideoSetWinAttribute(REAR_CAM_WINDOW_ID, Width, Height, 0, 0, MMP_SCAL_FITMODE_OPTIMAL, 0); 
								if(!LedCtrl_GetBacklightStatus())
									LedCtrl_LcdBackLight(AHC_TRUE);

                            }
						    #if (SUPPORT_SONIX_UVC_ISO_MODE==1) 
                            else if(gbRearState == AHC_TRUE && AHC_FALSE  ==  AHC_HostUVCSonixReverseGearDetection())
							#else	
							else if(gbRearState == AHC_TRUE && AHC_FALSE  ==  AHC_HostUVC_GetReversingGearStatus())
							#endif	
                            {
                                gbRearState = AHC_FALSE;
                          //      DrawRearCamReverseLine(AHC_FALSE);
                                #if (TVOUT_PREVIEW_EN||HDMI_PREVIEW_EN)
                                if(AHC_IsTVConnectEx()||AHC_IsHdmiConnect()){
                                    AHC_HostUVCVideoSetWinAttribute(REAR_CAM_WINDOW_ID, Width/2, Height/2, Width/2, Height/2, MMP_SCAL_FITMODE_OPTIMAL, 0); 
                                }
                                else
                                #endif
                                {
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0) 
                                    AHC_HostUVCVideoSetWinAttribute(REAR_CAM_WINDOW_ID, Width/2, Height/2, Width/2, Height/2, MMP_SCAL_FITMODE_OPTIMAL, 0); 
						#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90)
                                    AHC_HostUVCVideoSetWinAttribute(REAR_CAM_WINDOW_ID, Width/2, Height/2, 0, 0, MMP_SCAL_FITMODE_OPTIMAL, 0); 
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
                                    AHC_HostUVCVideoSetWinAttribute(REAR_CAM_WINDOW_ID, Width/2, Height/2, Width/2, 0, MMP_SCAL_FITMODE_OPTIMAL, 0); 
#endif                                
                                }
                                 #if (SUPPORT_SONIX_UVC_ISO_MODE==0)
                                 MMPD_Display_SetWinActive(REAR_CAM_WINDOW_ID, MMP_TRUE); 
                                 #endif
                            }
                            tickcount = 0;
                        }
                        else if(!AHC_HostUVCVideoIsEnabled()&&gbRearState)
                        	 gbRearState = AHC_FALSE;

                        tickcount++;
                        #endif
                        break;
                    }
                }
            }
#if (TASK_MONITOR_ENABLE)
            gsTaskMonitorRealIDUIKey.sTaskMonitorStates = MMPF_TASK_MONITOR_STATES_WAITING;        
#endif
            MMPF_OS_Sleep_MS(10);
        }
    }
}

void NotifyUSB_HwStatus(int sts)
{
	switch(sts)
	{
		case 0: /* SUSPEND */
			#ifdef CFG_KEY_NOTIFY_CABLE_OUT //may be defined in config_xxx.h
			SetKeyPadEvent(USB_CABLE_OUT);
			#endif	
		break;
		
		case 1: /* RESET */
			// Resend USB Cable In to check variable usIsAdapter of USB ISR
			SetKeyPadEvent(USB_CABLE_IN);
		break;
		
		default:
		break;
	}
}

/*
 * Enable_SD_Power 0: PowerOff, not 0: PowerOn SD
 * NOTE: Don't call the function in ISR, GPIOs are protected by OS, they cannot been written
 */
int Enable_SD_Power(int bEnable)
{
	return bEnable;
/* have to review more, it may cause SD not to work!*/
//#ifdef	DEVICE_GPIO_SD_POWER
#if 0

    AHC_ConfigGPIO(DEVICE_GPIO_SD_POWER, AHC_TRUE);

	if (bEnable) {
	    // LOW to turn on SD power
		/*
		AHC_ConfigGPIO(CONFIG_PIO_REG_GPIO54, AHC_TRUE);
		AHC_ConfigGPIO(CONFIG_PIO_REG_GPIO55, AHC_TRUE);
		AHC_ConfigGPIO(CONFIG_PIO_REG_GPIO56, AHC_TRUE);
		AHC_ConfigGPIO(CONFIG_PIO_REG_GPIO57, AHC_TRUE);
		AHC_ConfigGPIO(CONFIG_PIO_REG_GPIO58, AHC_TRUE);
		*/
	    AHC_SetGPIO(DEVICE_GPIO_SD_POWER, AHC_FALSE);
	} else {
	    // HIGH to turn off SD power
	    AHC_SetGPIO(DEVICE_GPIO_SD_POWER, AHC_TRUE);
	}
#endif
	return bEnable;
}
