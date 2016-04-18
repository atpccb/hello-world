
#ifndef _MENU_STATE_WIFI_MENU_H_
#define _MENU_STATE_WIFI_MENU_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "AHC_Common.h"
#include "AHC_Gui.h"

/*===========================================================================
 * Enum define 
 *===========================================================================*/ 

typedef enum {
	ITEMID_WIFI_MODE_1 = 1,
	ITEMID_SUB_WIFI_MODE_AP,
	ITEMID_SUB_WIFI_MODE_STATION,
	ITEMID_WIFI_AP,
    ITEMID_WIFI_AP_SSID,			// 5			
	ITEMID_SUB_WIFI_AP_SSID,
    ITEMID_WIFI_AP_PSWD,
	ITEMID_SUB_WIFI_AP_PSWD,
    ITEMID_WIFI_STATION1,
    ITEMID_WIFI_STATION1_SSID,		//10
	ITEMID_SUB_WIFI_STATION1_SSID,
    ITEMID_WIFI_STATION1_PSWD,
	ITEMID_SUB_WIFI_STATION1_PSWD,
    ITEMID_WIFI_STATION2,
    ITEMID_WIFI_STATION2_SSID,		//15
	ITEMID_SUB_WIFI_STATION2_SSID,
    ITEMID_WIFI_STATION2_PSWD,
	ITEMID_SUB_WIFI_STATION2_PSWD,
    ITEMID_WIFI_STATION3,
    ITEMID_WIFI_STATION3_SSID,		//20
	ITEMID_SUB_WIFI_STATION3_SSID,
    ITEMID_WIFI_STATION3_PSWD,
	ITEMID_SUB_WIFI_STATION3_PSWD,
    ITEMID_WIFI_STATION4,
    ITEMID_WIFI_STATION4_SSID,		//25
	ITEMID_SUB_WIFI_STATION4_SSID,
    ITEMID_WIFI_STATION4_PSWD,
	ITEMID_SUB_WIFI_STATION4_PSWD,
    ITEMID_WIFI_STATION5,
    ITEMID_WIFI_STATION5_SSID,		// 30
	ITEMID_SUB_WIFI_STATION5_SSID,
    ITEMID_WIFI_STATION5_PSWD,
	ITEMID_SUB_WIFI_STATION5_PSWD,  
    ITEMID_WIFI_STATION6,
    ITEMID_WIFI_STATION6_SSID,		//35
	ITEMID_SUB_WIFI_STATION6_SSID,
    ITEMID_WIFI_STATION6_PSWD,
	ITEMID_SUB_WIFI_STATION6_PSWD,
	ITEMID_WIFI_ITEM_END
}WIFIITEMID;


#endif //_MENU_STATE_WIFI_MENU_H_

