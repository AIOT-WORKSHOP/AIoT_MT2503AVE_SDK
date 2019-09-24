# 1 "temp/res/Bluetooth.c"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "temp/res/Bluetooth.c"




# 1 "../../mmi/inc/mmi_features.h" 1
# 69 "../../mmi/inc/mmi_features.h"
# 1 "../../mmi/inc/MMI_features_switch.h" 1
# 67 "../../mmi/inc/MMI_features_switch.h"
# 1 "../../mmi/inc/MMI_features_type.h" 1
# 68 "../../mmi/inc/MMI_features_switch.h" 2
# 70 "../../mmi/inc/mmi_features.h" 2
# 6 "temp/res/Bluetooth.c" 2

# 1 "../customerinc/custresdef.h" 1
# 207 "../customerinc/custresdef.h"
# 1 "../../mmi/inc/MMI_features.h" 1
# 208 "../customerinc/custresdef.h" 2
# 8 "temp/res/Bluetooth.c" 2
# 17 "temp/res/Bluetooth.c"
<?xml version="1.0" encoding="UTF-8"?>



<APP id="APP_BLUETOOTH"
# 33 "temp/res/Bluetooth.c"
    name = "STR_BT_MENU_TITLE"


    >




    <!--Include Area-->

    <INCLUDE file="ConnectivityResDef.h"/>
    <INCLUDE file="GlobalResDef.h"/>
    <INCLUDE file="MainMenuDef.h"/>
    <INCLUDE file="mmi_rp_app_mainmenu_def.h"/>

    <!-- MMI CACHE DATA -->
    <CACHEDATA type="byte" id="NVRAM_BT_RECEIVE_DRIVE" restore_flag="TRUE">
        <DEFAULT_VALUE> [0xFF] </DEFAULT_VALUE>
        <DESCRIPTION> Bluetooth Storage </DESCRIPTION>
    </CACHEDATA>

    <CACHEDATA type="byte" id="NVRAM_BT_RECEIVE_DRIVE_ASK" restore_flag="TRUE">
        <DEFAULT_VALUE> [0x00] </DEFAULT_VALUE>
        <DESCRIPTION> Bluetooth Storage </DESCRIPTION>
    </CACHEDATA>

    <CACHEDATA type="byte" id="NVRAM_BT_POWER_STATUS" restore_flag="TRUE">



        <DEFAULT_VALUE> [0x00] </DEFAULT_VALUE>

        <DESCRIPTION> Bluetooth setting </DESCRIPTION>
    </CACHEDATA>
# 97 "temp/res/Bluetooth.c"
    <TIMER id="BT_LP2_TESTING_TIMER"/>
    <TIMER id="BT_LP2_DELAY_TIMER"/>
    <TIMER id="BT_MMI_MAP_CONNECT_TIMER"/>
    <TIMER id="BT_AUTHORIZE_SCREEN_OPP_TIMER"/>
    <TIMER id="BT_AUTHORIZE_SCREEN_FTP_TIMER"/>
    <TIMER id="BT_AUTHORIZE_SCREEN_BIP_TIMER"/>
    <TIMER id="BT_AUTHORIZE_HID_TIMER"/>
    <TIMER id="BT_AUTHORIZE_SCREEN_HFP_TIMER"/>
    <TIMER id="BT_AUTHORIZE_SCREEN_HSP_TIMER"/>
    <TIMER id="BT_AUTHORIZE_SCREEN_SPP_TIMER"/>
    <TIMER id="BT_AUTHORIZE_SCREEN_DUN_TIMER"/>
    <TIMER id="BT_AUTHORIZE_SCREEN_FAX_TIMER"/>
    <TIMER id="BT_AUTHORIZE_SCREEN_SIMAP_TIMER"/>
    <TIMER id="BT_AUTHORIZE_SCREEN_PBAP_TIMER"/>
    <TIMER id="BT_AUTHORIZE_SCREEN_SYNC_TIMER"/>
    <TIMER id="BT_SEND_DUMMY_TIMER"/>
    <TIMER id="BT_PROG_UPDATE_TIMER"/>





    <!-- ASM Config -->




    <!-- FLIGHT MODE CALLBACK -->
    <RECEIVER id="EVT_ID_SRV_MODE_SWITCH_SWITCH_OTHER_NOTIFY" proc="mmi_bt_switch_flight_mode"/>
    <RECEIVER id="EVT_ID_SRV_MODE_SWITCH_FINISH_NOTIFY" proc="mmi_bt_switch_flight_mode"/>

    <!-- BT BOX acl timeout disconnect notify -->
# 141 "temp/res/Bluetooth.c"
    <!-----------------------------------------------------String Resource Area----------------------------------------------------->

    <STRING id="STR_BT_MENU_TITLE"/>
# 163 "temp/res/Bluetooth.c"
    <STRING id="STR_BT_POWER"/>
    <STRING id="STR_BT_SWITCHING"/>


    <STRING id="STR_BT_RELEASE_ALL_CONN"/>
    <STRING id="STR_BT_RELEASE_DEV_CONN"/>
    <STRING id="STR_BT_RELEASING"/>

    <STRING id="STR_BT_SCH_AUD_DEV"/>


    <STRING id="STR_BT_SCH_ALL_DEV"/>
    <STRING id="STR_BT_SCH_RESULT"/>






    <STRING id="STR_BT_INQUIRY_STOPPING"/>
    <STRING id="STR_BT_DEVICE_BEING_CONNECTED"/>
    <STRING id="STR_BT_ENTER_PASSCODE"/>
    <STRING id="STR_BT_PAIR_REQ"/>
    <STRING id="STR_BT_PAIR_FAILED"/>
    <STRING id="STR_BT_START_PAIRING"/>
# 198 "temp/res/Bluetooth.c"
    <STRING id="STR_BT_CONNECT_CONFIRM"/>


    <STRING id="STR_BT_ACCEPT_CONNECT_FROM"/>
    <STRING id="STR_BT_REACH_MAX_PAIR_NUM"/>

    <STRING id="STR_BT_REFRESHING"/>




    <STRING id="STR_BT_CONN_FAILED"/>


    <STRING id="STR_BT_MYDEVICE"/>
# 230 "temp/res/Bluetooth.c"
    <STRING id="STR_BT_MYDEV_OPT_SUP_SER"/>



    <STRING id="STR_BT_DEV_SET_VIS"/>
# 245 "temp/res/Bluetooth.c"
    <STRING id="STR_BT_DEV_SET_NAME"/>
    <STRING id="STR_BT_DEV_SET_AUDIO_PATH"/>

    <STRING id="STR_BT_DEV_SET_AUDIO_PATH_PHONE"/>
    <STRING id="STR_BT_DEV_SET_AUDIO_PATH_HF"/>







    <STRING id="STR_BT_DEV_SET_DEV_ADDR"/>

    <STRING id="STR_BT_ABOUT"/>
    <STRING id="STR_BT_BD_NAME"/>
    <STRING id="STR_BT_SERVICE"/>
    <STRING id="STR_BT_CONN_SERVICE"/>
    <STRING id="STR_BT_NO_SERVICE"/>
    <STRING id="STR_BT_BD_ADDR"/>
# 378 "temp/res/Bluetooth.c"
    <STRING id="STR_BT_PROF_UNKNOWN"/>
    <STRING id="STR_BT_NOT_READY"/>







    <STRING id="STR_BT_NO_SUPPORTED_PROFILE"/>

    <STRING id="STR_BT_PWR_ON_CNF"/>
    <STRING id="STR_BT_POWER_ON_IN_FLIGHT_MODE_CNF"/>

    <STRING id="STR_BT_DISCONN_ALL_CONN_CNF"/>

    <STRING id="STR_BT_DISCONN_ALL_CONN"/>
    <STRING id="STR_BT_DISCONN_DEV_CONN_CNF"/>
    <STRING id="STR_BT_DISCONN_DEV_CONN"/>
    <STRING id="STR_BT_DISCONN_AUD_DEV_CONN_CNF"/>
# 409 "temp/res/Bluetooth.c"
    <STRING id="STR_BT_PAIRED_DEV_FULL"/>
    <STRING id="STR_BT_PROHIBIT_VIS_BY_A2DP"/>
    <STRING id="STR_BT_OPERATION_NOT_ALLOWED_DIS_HFP_FIRST"/>


    <STRING id="STR_BT_PROHIBIT_BY_SIMAP"/>
# 438 "temp/res/Bluetooth.c"
    <STRING id="STR_BT_16_DIGITS_PASSKEY"/>



    <STRING id="STR_BT_INPUT_PASSCODE"/>
    <STRING id="STR_BT_NUMERIC_COMPARISON"/>
    <STRING id="STR_BT_ACCEPT_PAIRING"/>
    <STRING id="STR_BT_FROM"/>



    <STRING id="STR_BT_QUESTION_MARK"/>
# 875 "temp/res/Bluetooth.c"
                <STRING id="STR_BT_CONN_SINGLE_CONNECTING"/>
    <STRING id="STR_BT_SERVICE_UNAVAILABLE"/>
# 886 "temp/res/Bluetooth.c"
    <!-----------------------------------------------------Image Resource Area------------------------------------------------------>
# 908 "temp/res/Bluetooth.c"
    <IMAGE id="IMG_BT_MENU_TITLE" >"..\\\\..\\\\Customer\\\\Images\\\\PLUTO128X32""\\\\MainLCD\\\\Bluetooth\\\\SB_BT.bmp"</IMAGE>

    <IMAGE id="IMG_BT_SCH_TITLE" >"..\\\\..\\\\Customer\\\\Images\\\\PLUTO128X32""\\\\MainLCD\\\\Bluetooth\\\\OBT_Search"</IMAGE>
    <IMAGE id="IMG_BT_DEV_PRT" >"..\\\\..\\\\Customer\\\\Images\\\\PLUTO128X32""\\\\MainLCD\\\\Bluetooth\\\\OBT_print.png"</IMAGE>
    <IMAGE id="IMG_BT_DEV_LAP" >"..\\\\..\\\\Customer\\\\Images\\\\PLUTO128X32""\\\\MainLCD\\\\Bluetooth\\\\OBT_LAP.png"</IMAGE>

    <IMAGE id="IMG_BT_DEV_MOB" >"..\\\\..\\\\Customer\\\\Images\\\\PLUTO128X32""\\\\MainLCD\\\\Bluetooth\\\\OBT_MOB.png"</IMAGE>
    <IMAGE id="IMG_BT_DEV_EAR" >"..\\\\..\\\\Customer\\\\Images\\\\PLUTO128X32""\\\\MainLCD\\\\Bluetooth\\\\OBT_EAR.png"</IMAGE>
    <IMAGE id="IMG_BT_DEV_OTHER" >"..\\\\..\\\\Customer\\\\Images\\\\PLUTO128X32""\\\\MainLCD\\\\Bluetooth\\\\OBT_other.png"</IMAGE>



        <IMAGE id="IMG_BT_CONNECTION_DATA" >"..\\\\..\\\\Customer\\\\Images\\\\PLUTO128X32""\\\\MainLCD\\\\Bluetooth\\\\Data_channel.bmp"</IMAGE>
# 1320 "temp/res/Bluetooth.c"
    <!------------------------------------------------------Menu Resource Area------------------------------------------------------>


    <MENUITEM id="MENU_CONN_BT_POWER" str="STR_BT_POWER" img="IMG_BT_POWER"/>






    <MENUITEM id="MENU_CONN_BT_SCH_AUDIO_DEV" str="STR_BT_SCH_AUD_DEV" img="IMG_BT_SCH_AUD_DEV"/>


    <MENUITEM id="MENU_CONN_BT_MYDEV" str="STR_BT_MYDEVICE" img="IMG_BT_MYDEV"/>





    <MENUITEM id="MENU_CONN_BT_SET_NAME" str="STR_BT_DEV_SET_NAME" img="IMG_BT_SET_NAME"/>


    <MENUITEM id="MENU_CONN_BT_SET_AUDIO_PATH_PHONE" str="STR_BT_DEV_SET_AUDIO_PATH_PHONE" img="IMG_BT_SET_AUDIO_PATH_PHONE"/>

    <MENUITEM id="MENU_CONN_BT_SET_AUDIO_PATH_HF" str="STR_BT_DEV_SET_AUDIO_PATH_HF" img="IMG_BT_SET_AUDIO_PATH_HF"/>





    <MENUITEM id="MENU_CONN_BT_SET_DEV_ADDR" str="STR_BT_DEV_SET_DEV_ADDR" img="IMG_BT_SET_DEV_ADDR"/>

    <MENUITEM id="MENU_CONN_BT_SET_STORAGE" str="STR_GLOBAL_STORAGE" img="IMG_BT_SET_STORAGE"/>







    <MENU id="MENU_CONN_BT_SET_AUDIO_PATH" type="APP_SUB" str="STR_BT_DEV_SET_AUDIO_PATH" img="IMG_BT_SET_AUDIO_PATH">

        <MENUITEM_ID>MENU_CONN_BT_SET_AUDIO_PATH_PHONE</MENUITEM_ID>
        <MENUITEM_ID>MENU_CONN_BT_SET_AUDIO_PATH_HF</MENUITEM_ID>
    </MENU>
# 1382 "temp/res/Bluetooth.c"
    <STRING id="STR_ID_FAILED_SHARE_AS_DILAER_CONNED"/>
# 1425 "temp/res/Bluetooth.c"
    <MENU id="MENU_CONN_BT_SET_VIS" str="STR_BT_DEV_SET_VIS" img="IMG_BT_SET_VIS"></MENU>
# 1441 "temp/res/Bluetooth.c"
    <MENU id="MENU_CONN_BT_SET" type="APP_SUB" str="STR_GLOBAL_ADVANCED" img="IMG_BT_SET">

        <MENUITEM_ID>MENU_CONN_BT_SET_AUTH</MENUITEM_ID>
        <MENUITEM_ID>MENU_CONN_BT_SET_AUDIO_PATH</MENUITEM_ID>



        <MENUITEM_ID>MENU_CONN_BT_SET_SHARING</MENUITEM_ID>
        <MENUITEM_ID>MENU_CONN_BT_SET_PERMISSION</MENUITEM_ID>
        <MENUITEM_ID>MENU_CONN_BT_SET_IMAGE_FOLDER</MENUITEM_ID>
        <MENUITEM_ID>MENU_CONN_BT_REMOTE_CONTROL</MENUITEM_ID>
        <MENUITEM_ID>MENU_CONN_BT_SET_SIMAP</MENUITEM_ID>
        <MENUITEM_ID>MENU_CONN_BT_SET_DEV_ADDR</MENUITEM_ID>
    </MENU>
# 1467 "temp/res/Bluetooth.c"
    <MENU id="MENU_CONN_BT_MAIN" type="APP_SUB" str="STR_GLOBAL_BLUETOOTH" img="IMG_BT_MENU_TITLE" highlight="mmi_bt_main_hilight_handler"
      shortcut="ON" shortcut_img="IMG_BT_MENU_TITLE" launch="mmi_bt_entry_main_menu">



        <MENUITEM_ID>MENU_CONN_BT_POWER</MENUITEM_ID>
        <MENUITEM_ID>MENU_CONN_BT_SET_VIS</MENUITEM_ID>

        <MENUITEM_ID>MENU_CONN_BT_MYDEV</MENUITEM_ID>


        <MENUITEM_ID>MENU_CONN_BT_SCH_AUDIO_DEV</MENUITEM_ID>
        <MENUITEM_ID>MENU_CONN_BT_SET_NAME</MENUITEM_ID>
        <MENUITEM_ID>MENU_CONN_BT_SET</MENUITEM_ID>



        <MENUITEM_ID>MENU_CONN_BT_ABOUT</MENUITEM_ID>
# 1502 "temp/res/Bluetooth.c"
    </MENU>
# 1646 "temp/res/Bluetooth.c"
    <!------------------------------------------------------Screen Resource Area------------------------------------------------------>
    <SCREEN id="SCR_EXTDEV_BT_BEGIN"/>
    <SCREEN id="GRP_ID_BT_CM"/>
    <SCREEN id="GRP_ID_BT_CM_POWER_ON_CNF"/>
    <SCREEN id="GRP_ID_BT_CM_SELECT_DEVICE"/>
        <SCREEN id="GRP_ID_BT_CM_INQUIRY_DEVICE"/>
    <SCREEN id="GRP_ID_BT_CM_PROGRESS"/>
    <SCREEN id="GRP_ID_BT_CM_PASSKEY_INPUT"/>
    <SCREEN id="GRP_ID_BT_CM_SECURITY_CNF"/>
    <SCREEN id="GRP_ID_BT_CM_PASSKEY_NOTIFY"/>
    <SCREEN id="GRP_ID_BT_CM_AUTH"/>
    <SCREEN id="GRP_ID_BT_CM_BLOCK_CNF"/>
    <SCREEN id="GRP_ID_BT_CM_CONNECT_ACCEPT_CNF_HFP"/>
    <SCREEN id="GRP_ID_BT_CM_CONNECT_ACCEPT_CNF_HSP"/>
    <SCREEN id="GRP_ID_BT_CM_CONNECT_ACCEPT_CNF_BIP"/>
    <SCREEN id="GRP_ID_BT_CM_CONNECT_ACCEPT_CNF_FTP"/>
    <SCREEN id="GRP_ID_BT_CM_CONNECT_ACCEPT_CNF_OPP"/>
    <SCREEN id="GRP_ID_BT_CM_CONNECT_ACCEPT_CNF_SPP"/>
    <SCREEN id="GRP_ID_BT_CM_CONNECT_ACCEPT_CNF_DUN"/>
    <SCREEN id="GRP_ID_BT_CM_CONNECT_ACCEPT_CNF_FAX"/>
    <SCREEN id="GRP_ID_BT_CM_CONNECT_ACCEPT_CNF_PBAP"/>
    <SCREEN id="GRP_ID_BT_CM_CONNECT_ACCEPT_CNF_HID"/>
    <SCREEN id="GRP_ID_BT_CM_CONNECT_ACCEPT_CNF_SYNC"/>
    <SCREEN id="GRP_ID_BT_CM_CONNECT_ACCEPT_CNF_SAP"/>
    <SCREEN id="GRP_ID_BT_PBAPC_AUTHENTICATE"/>
    <SCREEN id="GRP_ID_BT_AUTO_CONNECT"/>

    <SCREEN id="SCR_BT_MAIN"/>
    <SCREEN id="SCR_BT_POWER_ON_CNF"/>
    <SCREEN id="SCR_BT_RELEASE_DEV_CONN_CNF"/>
    <SCREEN id="SCR_BT_RELEASE_ALL_CONN_CNF"/>
    <SCREEN id="SCR_BT_RELEASE_AUD_CONN_CNF"/>
    <SCREEN id="SCR_BT_POWER_PRO"/>
    <SCREEN id="SCR_BT_REL_ALL_CONN_PRO"/>
    <SCREEN id="SCR_BT_REL_DEV_CONN_PRO"/>
    <SCREEN id="SCR_BT_REL_PROFILE_CONN_PRO"/>
    <SCREEN id="SCR_BT_SWITCH_LIMIT_DISCOVER_MODE"/>
    <SCREEN id="SCR_BT_LIMIT_DISCOVER_MODE"/>

    <SCREEN id="SCR_BT_SCH_PRO"/>
    <SCREEN id="SCR_BT_SCH_DISCONNECT_SCO"/>
    <SCREEN id="SCR_BT_SCH_RES"/>
    <SCREEN id="SCR_BT_SCH_CANCEL_PRO"/>
    <SCREEN id="SCR_BT_BOND"/>
    <SCREEN id="SCR_BT_REFREAH_PROFILE"/>
    <SCREEN id="SCR_BT_PIN_INPUT"/>
    <SCREEN id="SCR_PBAPC_PASSWORD"/>
    <SCREEN id="SCR_BT_PAIR_PRO"/>
    <SCREEN id="SCR_BT_AUTH_CONFIRM"/>
    <SCREEN id="SCR_BT_CONNECT_CNF"/>
    <SCREEN id="SCR_BT_CONNECTING"/>
    <SCREEN id="SCR_BT_CONNECT_ACCEPT_CNF_HFP"/>
    <SCREEN id="SCR_BT_CONNECT_ACCEPT_CNF_HSP"/>
    <SCREEN id="SCR_BT_CONNECT_ACCEPT_CNF_BIP"/>
    <SCREEN id="SCR_BT_CONNECT_ACCEPT_CNF_FTP"/>
    <SCREEN id="SCR_BT_CONNECT_ACCEPT_CNF_OPP"/>
    <SCREEN id="SCR_BT_CONNECT_ACCEPT_CNF_SPP"/>
    <SCREEN id="SCR_BT_CONNECT_ACCEPT_CNF_DUN"/>
    <SCREEN id="SCR_BT_CONNECT_ACCEPT_CNF_FAX"/>
    <SCREEN id="SCR_BT_CONNECT_ACCEPT_CNF_PBAP"/>
    <SCREEN id="SCR_BT_CONNECT_ACCEPT_CNF_HID"/>
    <SCREEN id="SCR_BT_CONNECT_ACCEPT_CNF_SYNC"/>
    <SCREEN id="SCR_BT_CONNECT_ACCEPT_CNF_SAP"/>
    <SCREEN id="SCR_BT_NUMERIC_CONFIRM"/>
    <SCREEN id="SCR_BT_PASSKEY_NOTIFY"/>
    <SCREEN id="SCR_BT_UNBLOCKING"/>
    <SCREEN id="SCR_BT_DEVICE_BLOCK_CNF"/>

    <SCREEN id="SCR_BT_REMOTE_CTRL_POWER_CONFIRM"/>
    <SCREEN id="SCR_BT_REMOTE_CTRL_CONN_AUTH"/>
    <SCREEN id="SCR_BT_REMOTE_CTRL_APP_SELECT"/>
    <SCREEN id="SCR_BT_REMOTE_CTRL_APP"/>
    <SCREEN id="SCR_BT_REMOTE_CTRL_UNPLUG_CONFIRM"/>
    <SCREEN id="SCR_BT_REMOTE_CTRL_DISC_CONFIRM"/>
    <SCREEN id="SCR_BT_REMOTE_CTRL_PROGRESS"/>

    <SCREEN id="SCR_BT_MYDEV"/>
    <SCREEN id="SCR_BT_MYDEV_OPT"/>
    <SCREEN id="SCR_BT_MYDEV_PROF_CHO"/>
    <SCREEN id="SCR_BT_MYDEV_CON"/>
    <SCREEN id="SCR_BT_MYDEV_CONNECTED_PROF"/>
    <SCREEN id="SCR_BT_MYDEV_DISCON"/>
    <SCREEN id="SCR_BT_MYDEV_SIM_CNF"/>
    <SCREEN id="SCR_BT_MYDEV_SIM_SEL"/>
    <SCREEN id="SCR_BT_MYDEV_REN"/>
    <SCREEN id="SCR_BT_MYDEV_REN_OPT"/>
    <SCREEN id="SCR_BT_MYDEV_AUTH"/>
    <SCREEN id="SCR_BT_MYDEV_DEL"/>
    <SCREEN id="SCR_BT_MYDEV_DEL_ALL"/>
    <SCREEN id="SCR_BT_MYDEV_SUP_PROFILE"/>
    <SCREEN id="SCR_BT_MYDEV_SCH"/>

    <SCREEN id="SCR_BT_ACT_DEV"/>
    <SCREEN id="SCR_BT_DISC_PROC"/>
    <SCREEN id="SCR_BT_ENFORCE_DISC_CNF"/>

    <SCREEN id="SCR_BT_SET"/>
    <SCREEN id="SCR_BT_SET_NAME"/>
    <SCREEN id="SCR_BT_SET_NAME_OPT"/>
    <SCREEN id="SCR_BT_SET_VIS"/>
    <SCREEN id="SCR_BT_SET_VIS_MENU"/>
    <SCREEN id="SCR_BT_SET_AUTH"/>
    <SCREEN id="SCR_BT_SET_AUDIO_PATH"/>
    <SCREEN id="SCR_BT_SET_BLOCK_LIST"/>
    <SCREEN id="SCR_BT_SET_FTP"/>
    <SCREEN id="SCR_BT_SET_SIMAP"/>
    <SCREEN id="SCR_BT_SET_STORAGE"/>
    <SCREEN id="SCR_BT_SET_SHARING"/>
    <SCREEN id="SCR_BT_SET_PERMISSION"/>
    <SCREEN id="SCR_BT_SET_IMAGE_FOLDER"/>
    <SCREEN id="SCR_BT_SET_STORAGE_CONFIRM"/>
    <SCREEN id="SCR_BT_SEL_DRV1"/>
    <SCREEN id="SCR_BT_SEL_DRV2"/>
    <SCREEN id="SCR_BT_SEL_DRV3"/>
    <SCREEN id="SCR_BT_SEL_DRV4"/>


    <SCREEN id="SCR_BT_SEND_DUMMY"/>
    <SCREEN id="SCR_BT_SEND_DEVICE_OPTION"/>
    <SCREEN id="SCR_BT_SEND_CNF_TO_DEFAULT"/>
    <SCREEN id="SCR_BT_SEND_CNF_SET_DEFAULT"/>
    <SCREEN id="SCR_BT_SEND_CNF_POWER_ON"/>

    <SCREEN id="SCR_BT_ABOUT"/>
    <SCREEN id="SCR_BT_MY_SPECIFIC_DEV"/>
    <SCREEN id="SCR_BT_MY_SPECIFIC_DEV_DUMMY"/>
    <SCREEN id="SCR_BT_SWITCH_SPEECH_PATH"/>

    <SCREEN id="SCR_BT_CONNECT_LAST_HEADSET"/>
    <SCREEN id="SCR_BT_NOT_ALLOWED"/>
    <SCREEN id="SCR_BT_NOT_PROHIBIT_BY_SIMAP"/>
    <SCREEN id="SCR_BT_SET_DEFAULT_HS"/>
    <SCREEN id="SCR_BT_CM_LAST"/>

    <SCREEN id="SCR_HF_CONNECTING"/>
    <SCREEN id="SCR_HF_RELEASING"/>

    <SCREEN id="SCR_OPP_NOTY_FILE_RECV"/>
    <SCREEN id="SCR_OPP_NOTY_RECV_ACCEPT"/>
    <SCREEN id="SCR_OPP_SENDING"/>
    <SCREEN id="SCR_OPP_ABORTING"/>
    <SCREEN id="SCR_OPP_DISCONNECTING"/>

    <SCREEN id="SCR_FTP_SETTING"/>
    <SCREEN id="SCR_FTP_ACCESS_RIGHT_OPTION"/>
    <SCREEN id="SCR_FTP_SELECT_SHARED_FOLDER"/>
    <SCREEN id="SCR_FTP_NOTY_CONN_REQ"/>
    <SCREEN id="SCR_FTP_FILE_BROWSER"/>
    <SCREEN id="SCR_FTP_NOTY_FILE_RECV"/>
    <SCREEN id="SCR_FTP_RECEIVING"/>
    <SCREEN id="SCR_FTP_DISCONNECTING"/>
    <SCREEN id="SCR_FTP_ABORTING"/>
    <SCREEN id="SCR_FTP_DETAIL_INFO"/>
    <SCREEN id="SCR_FTP_MARK_SEVERAL"/>
    <SCREEN id="SCR_FTP_CONNECTING"/>
    <SCREEN id="SCR_FTP_OPENING_FOLDER"/>
    <SCREEN id="SCR_FTP_CONNECT_CANCELING"/>
    <SCREEN id="SCR_ID_BT_AVCRP_CT_MAIN"/>
    <SCREEN id="SCR_BPP_DUMMY"/>
    <SCREEN id="SCR_BPP_CONNECTING"/>
    <SCREEN id="SCR_BPP_AUTHENTICATING"/>
    <SCREEN id="SCR_BPP_GETTING"/>
    <SCREEN id="SCR_BPP_PRINT_SETTING"/>
    <SCREEN id="SCR_BPP_LAYOUT_PREVIEW"/>
    <SCREEN id="SCR_BPP_CREATING"/>
    <SCREEN id="SCR_BPP_COMPOSING"/>
    <SCREEN id="SCR_BPP_PRINTING"/>
    <SCREEN id="SCR_BPP_TROUBLE"/>
    <SCREEN id="SCR_BPP_DISCONNECTING"/>
    <SCREEN id="SCR_OBEX_INPUT_AUTHPWD"/>
    <SCREEN id="SCR_BPP_SP_PRINT_SETUP"/>
    <SCREEN id="SCR_BPP_SP_PREVIEW"/>
    <SCREEN id="SCR_BPP_SP_PRINTING"/>
    <SCREEN id="SCR_BPP_SP_PASSWORD_INPUT"/>
    <SCREEN id="SCR_BPP_SP_TROUBLE"/>
    <SCREEN id="SCR_BPP_SP_DUMMY"/>
    <SCREEN id="SCR_BPP_SP_PRINT_OPTION"/>
    <SCREEN id="SCR_BPP_PRINTER_SETUP_OPTION"/>

    <SCREEN id="GRP_ID_BIP_OBJ_DETAIL"/>
    <SCREEN id="SCR_BIP_SETTING"/>
    <SCREEN id="SCR_BIP_SENDING"/>
    <SCREEN id="SCR_BIP_CONNECTING"/>
    <SCREEN id="SCR_BIP_ABORTING"/>
    <SCREEN id="SCR_BIP_RECEIVING"/>
    <SCREEN id="SCR_BIP_DISCONNECTING"/>
    <SCREEN id="SCR_BIP_IMGLIST_BROWSER"/>
    <SCREEN id="SCR_BIP_IMG_DETAIL"/>
    <SCREEN id="SCR_BIP_THM_PREVIEW"/>
    <SCREEN id="SCR_BIP_IMGLIST_OPTION"/>
    <SCREEN id="SCR_BIP_GETTING_IMGPROP"/>
    <SCREEN id="SCR_BIP_NOTY_CONN_REQ"/>
    <SCREEN id="SCR_BIP_NOTY_FILE_RECV"/>
    <SCREEN id="SCR_BIP_NOTY_CONTINUE_SEND"/>
    <SCREEN id="SCR_BIP_EXIT_CONFIRM"/>
    <SCREEN id="SCR_BIP_CONNECT_CANCELING"/>
    <SCREEN id="SCR_BIP_PUSH_ABORTING"/>
    <SCREEN id="SCR_BIP_RECV_FILE_CONFIRM"/>

    <SCREEN id="GRP_ID_PBAP_AUTHENTICATION"/>
    <SCREEN id="SCR_PBAP_AUTHENTICATING_ID"/>
    <SCREEN id="SCR_PBAP_NOTY_CONN_REQ_ID"/>
    <SCREEN id="SCR_EXTDEV_BT_LAST"/>
    <SCREEN id="GRP_ID_BT_BPP"/>
# 1874 "temp/res/Bluetooth.c"
    <EVENT id="EVT_ID_SPPC_CONNECT_CNF" type="SENDER"/>
    <EVENT id="EVT_ID_SPPC_DISCONNECT_CNF" type="SENDER"/>
    <EVENT id="EVT_ID_SPPC_READY_TO_READ" type="SENDER"/>
    <EVENT id="EVT_ID_SPPC_READY_TO_WRITE" type="SENDER"/>


    <EVENT id="EVT_ID_SPPS_CONNECT_IND" type="SENDER"/>
    <EVENT id="EVT_ID_SPPS_DISCONNECT_CNF" type="SENDER"/>
    <EVENT id="EVT_ID_SPPS_READY_TO_READ" type="SENDER"/>
    <EVENT id="EVT_ID_SPPS_READY_TO_WRITE" type="SENDER"/>

    <!-----------------BT Dialer Service Events begin--------------------------------------------------->
# 1899 "temp/res/Bluetooth.c"
</APP>
