/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2005
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE. 
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/
/*****************************************************************************
 *
 * Filename:
 * ---------
 *  MMI_features_switch.h
 *
 * Project:
 * -------- 
 *  MAUI
 *
 * Description:
 * ------------
 *  MMI feature switch file
 *
 * Author:
 * -------
 * -------
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
#ifndef __MMI_FEATURES_SWITCH_H__
#define __MMI_FEATURES_SWITCH_H__

/*****************************************************************************
* Option Value Definition                                                                     
*****************************************************************************/
#include "MMI_features_type.h"

/*****************************************************************************
* Switch Description
*****************************************************************************/

/*****************************************************************************
* Application Framework
    * GDI
        * Image
*****************************************************************************/

/*****************************************************************************
* Application Framework
    * GDI
        * Memory
*****************************************************************************/

/*
  Description: GDI using two layer
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MT6261-GDI-SLIM_Feature_Options.ppt
*/
#define CFG_GDI_MEMORY_PROFILE_2	(__OFF__)

/*****************************************************************************
* Application Framework
    * Pluto Framework
        * Event Management
*****************************************************************************/

/*****************************************************************************
* Application Framework
    * Pluto Framework
        * Misc
*****************************************************************************/

/*
  Description: Dump screen string information by AT command
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_FRM_DUMP_SCREEN_STRING.doc
*/
#define CFG_MMI_SUPPORT_DUMP_SCREEN_STRING	(__OFF__)

/*
  Description: the mainmenu type of smart watch
  Option: [__ONE__, __FOUR__, __ALL__]
  Reference: n/a
*/
#define CFG_MMI_SMART_WATCH_MAINMENU_TYPE	(__ONE__)

/*****************************************************************************
* Application Framework
    * Pluto Framework
        * Resource Management
*****************************************************************************/

/*
  Description: Compress Audio data when compress rate is more than 50%, will save ROM and waste RAM,for the detail size of ROM and RAM please open and do Resgen, then check resource_compresss_log.csv
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_Resource_Generator_Tool.doc
*/
#define CFG_MMI_RESOURCE_AUDIO_COMPRESS	(__OFF__)

/*
  Description: Internal option of Resgen.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_RESOURCE_STR_COMPRESS	(__OFF__)

/*
  Description: Config Image data compress rate, when image compress rate is bigger than this number ,Resgen will compress the image, will save ROM and waste RAM,for the detail size of ROM and RAM please open and do Resgen, then check resource_compresss_log.csv
  Option: [__OFF__, 10~90]
  Reference: DD_Resource_Generator_Tool.doc
*/
#define CFG_MMI_RESOURCE_IMAGE_COMPRESS_RATE	(__OFF__)

/*
  Description: MainMenu Icon default selection
  Option: [__MAINMENU_ICON_SEL_0__, __MAINMENU_ICON_SEL_1__, __MAINMENU_ICON_SEL_2__]
  Reference: CosmosSlim_Mainmenu_Icon_resource_switch.ppt
*/
#define CFG_MMI_MAINMENU_ICON_DEFAULT_SEL	(__MAINMENU_ICON_SEL_0__)

/*
  Description: Compressed image resource with LZMA compressor
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_RESOURCE_LZMA_IMAGE_GROUP_COMPRESS	(__OFF__)

/*****************************************************************************
* Application Framework
    * Pluto Framework
        * Screen Management
*****************************************************************************/

/*
  Description: history mechanism disable
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_FRM_Framework_layer_Maintrunk.doc
*/
#define CFG_MMI_FRM_REMOVE_HISTORY	(__ON__)

/*****************************************************************************
* Application Framework
    * Pluto UI
*****************************************************************************/

/*
  Description: Image/animation type of active screens (Ex: USB, charging)Note: BMP recommended for MT6223. JPG/GIF recommended for other chips.
  Option: [__OFF__, __RES_TYPE_BMP__, __RES_TYPE_GIF__, __RES_TYPE_JPG__]
  Reference: SOP_UI_Display_Performance_Tuning.doc
*/
#define CFG_MMI_RES_TYPE_ACTIVE_SCREEN_SEL	(__RES_TYPE_BMP__)

/*
  Description: Dynamic screen rotation (Only multimedia apps supported)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Category_Screen_Support_Rotate.doc
*/
#define CFG_MMI_SCREEN_ROTATE	(__OFF__)

/*
  Description: Support calendar on Idle screen
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_ORGANIZER_06B_for_240x320.doc
*/
#define CFG_MMI_CALENDAR_ON_IDLE_SCREEN	(__OFF__)

/*
  Description: If defined, then IDLE screen wiil be full screen background
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SAP_CategoryScreens.doc
*/
#define CFG_MMI_IDLE_FULL_SCREEN	(__ON__)

/*
  Description: animation type of popup screens
  Option: [__RES_TYPE_GIF__, __RES_TYPE_PNG__, __RES_TYPE_SEQUENCE__]
  Reference: SOP_UI_Customization.doc
*/
#define CFG_MMI_RES_TYPE_POPUP_SCREEN_SEL	(__RES_TYPE_PNG__)

/*
  Description: Image/animation type of SubLCD wallpaperNote: BMP recommended for MT6223. GIF recommended for other chips.(Note: SubLCD wallpaper should not use JPEG due to hardware limitation)
  Option: [__OFF__, __RES_TYPE_BMP__, __RES_TYPE_GIF__]
  Reference: SOP_UI_Display_Performance_Tuning.doc
*/
#define CFG_MMI_RES_TYPE_SUBLCD_WALLPAPER_SEL	(__OFF__)

/*
  Description: Max number of system themes.
  Option: [1~10]
  Reference: UI Customization SOP
*/
#define CFG_MMI_THEME_MAX_NUMBER	(1)

/*
  Description: Display Idle Screen shortcuts
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SAP_CategoryScreens_06B_08B.doc
*/
#define CFG_MMI_TOUCH_IDLESCREEN_SHORTCUTS	(__OFF__)

/*
  Description: Choose the effect style of cascading menu and popup background
  Option: [MMI_UI_FADE_EFFECT_STYLE_GRAY, MMI_UI_FADE_EFFECT_STYLE_DARKEN]
  Reference: UI Customization SOP
*/
#define CFG_MMI_UI_FADE_EFFECT_STYLE	(MMI_UI_FADE_EFFECT_STYLE_DARKEN)

/*
  Description: If this macro is defined, it can make the inline support the default text display if the inline singleline editor is empty
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_UI_INLINE.doc
*/
#define CFG_MMI_UI_INLINE_EDIT_DEFAULT_TEXT_EFFECT	(__OFF__)

/*
  Description: scrollbar default style
  Option: [__OFF__, 1~6]
  Reference: SOP_UI_Customization.doc
*/
#define CFG_MMI_UI_SCROLLBAR_DEFAULT_STYLE	(__OFF__)

/*
  Description: Techno styled idle screen bar containing clock
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SAP_CategoryScreens_06B_08B.doc
*/
#define CFG_MMI_UI_TECHNO_IDLESCREEN_BAR	(__OFF__)

/*
  Description: Bootup logo image file format. May use GIF for smaller size but it will  increase bootup time.
  Option: [__RES_TYPE_BMP__, __RES_TYPE_GIF__]
  Reference: UI Document (DD_UIDESIGN_[LCD RESOLUTION]_[BRANCH].doc)
*/
#define CFG_MMI_RES_TYPE_BOOTUP_LOGO_IMAGE_SEL	(__RES_TYPE_BMP__)

/*
  Description: use image in digital clock on techno bar
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_UI_Customization.doc
*/
#define CFG_MMI_DIGITAL_CLOCK_IMAGE_NUMBER	(__OFF__)

/*
  Description: icon shortcut bar on idle screen
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SAP_CategoryScreens_06B_08B.doc
*/
#define CFG_MMI_IDLE_SCREEN_ICON_SHORTCUT	(__OFF__)

/*
  Description: Wider scrollbar style in FTE
  Option: [__OFF__, 1~7]
  Reference: SOP_UI_Customization.doc
*/
#define CFG_MMI_UI_SCROLLBAR_WIDER_STYLE	(__OFF__)

/*
  Description: clock use small digital image to display digital clock
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: PRST_UI_Promotion_08B
*/
#define CFG_MMI_UI_CLOCK_SMAILL_DIGITAL_IMAGE_CLOCK	(__OFF__)

/*
  Description: support touch feedback on FTE project
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_TOUCH_FEEDBACK_SUPPORT	(__OFF__)

/*
  Description: FTE support slim
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_UI_Customization.doc
*/
#define CFG_MMI_FTE_SUPPORT_SLIM	(__ON__)

/*
  Description: Disable fancy UI effects on big LCD for better UI responsiveness
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_UI_Display_Performance_Tuning.doc
*/
#define CFG_MMI_UI_DISABLE_FANCY_EFFECT	(__AUTO__)

/*
  Description: Turn on/off the screen switch effect
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: UI Customization SOP
*/
#define CFG_MMI_SCREEN_SWITCH_EFFECT	(__OFF__)

/*
  Description: Use animated logo or not in ZIMAGE
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_UI_Customization.doc
*/
#define CFG_ZIMAGE_LOGO_ANIMATED_SUPPORT	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_FWUI_SLIM	(__ON__)

/*
  Description: BT BOX Keyhandle for 4keys
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_MMI_BTBOX.ppt
*/
#define CFG_MMI_BTBOX_KEYBOARD_STYLE	(__OFF__)

/*
  Description: BTBOX UI Style
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_BTDIALER.pptx
*/
#define CFG_MMI_BTD_BOX_UI_STYLE	(__OFF__)

/*
  Description: BTBOX Time Picker
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_BTDIALER.pptx
*/
#define CFG_MMI_GUI_PICKER	(__ON__)

/*
  Description: tabbar slim
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MT6261-tabbar-SLIM_Feature_Options.ppt
*/
#define CFG_MMI_TAB_BARS_SUPPORT	(__OFF__)

/*
  Description: BTBOX Dialer pad
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_MMI_BTBOX.ppt
*/
#define CFG_MMI_UI_DIALER_PAD	(__OFF__)

/*
  Description: BTBOX Time Picker
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_MMI_BTBOX.ppt
*/
#define CFG_MMI_UI_TIME_PICKER	(__ON__)

/*****************************************************************************
* Application Framework
    * Pluto UI
        * Category Screen
*****************************************************************************/

/*
  Description: For Small Image Select Screen
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SAP_CategoryScreens.doc
*/
#define CFG_MMI_SMALL_IMAGE_SELECTOR_SCREEN	(__OFF__)

/*
  Description: Support small list screen
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SAP_CategoryScreens_06B_08B.doc
*/
#define CFG_MMI_SMALL_LIST_SCREEN	(__OFF__)

/*
  Description: For Small Editor Screen
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SAP_CategoryScreens.doc
*/
#define CFG_MMI_SMALL_EDIT_SCREEN	(__OFF__)

/*
  Description: Support small pin editor screen
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SAP_CategoryScreens.doc
*/
#define CFG_MMI_SMALL_PIN_EDIT_SCREEN	(__OFF__)

/*****************************************************************************
* Application Framework
    * Pluto UI
        * Fundamental CUI
*****************************************************************************/

/*****************************************************************************
* Application Framework
    * Pluto UI
        * Misc
*****************************************************************************/

/*
  Description: sublcd to show out the date at idle mode
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SAP_CategoryScreens.doc
*/
#define CFG_MMI_SUBLCD_SHOW_DATE	(__OFF__)

/*
  Description: sublcd to show out the city at idle mode
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SAP_CategoryScreens.doc
*/
#define CFG_MMI_SUBLCD_SHOW_ONE_CITY	(__OFF__)

/*
  Description: sublcd to show out the time at idle mode
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SAP_CategoryScreens.doc
*/
#define CFG_MMI_SUBLCD_SHOW_TIME	(__OFF__)

/*****************************************************************************
* Application Framework
    * Pluto UI
        * Theme
*****************************************************************************/

/*****************************************************************************
* Application Framework
    * Pluto UI
        * Touch Screen
*****************************************************************************/

/*****************************************************************************
* Application Framework
    * Pluto UI Component
        * Bars
*****************************************************************************/

/*
  Description: Enable signal strength status icon combine with line switch
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_UI_Customization.doc
*/
#define CFG_MMI_STATUS_ICON_SIGNAL_WITH_LINE_SWITCH	(__OFF__)

/*
  Description: Idlescreen shows status icon on bottom and draw while segment lines
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_UI_Customization.doc
*/
#define CFG_MMI_UI_STATUS_BAR_AT_BOTTOM	(__OFF__)

/*
  Description: Statuc icon is alignment right
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_UI_Customization.doc
*/
#define CFG_WGUI_STATUS_ICON_ALIGN_RIGHT	(__OFF__)

/*
  Description: Show clock in right of status iocn bar
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_UI_Customization.doc
*/
#define CFG_WGUI_STATUS_ICON_SHOW_TIME_IN_RIGHT	(__ON__)

/*
  Description: Do not draw the status bar underline
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_UI_Customization.doc
*/
#define CFG_MMI_STATUS_BAR_NO_UNDERLINE	(__AUTO__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_NW_INFO_DN_STATUS_ULINK_DLINK_ICONS	(__OFF__)

/*****************************************************************************
* Application Framework
    * Pluto UI Component
        * Menu
*****************************************************************************/

/*
  Description: Cascade menu feature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: UI Customization SOP
*/
#define CFG_MMI_CASCADE_MENU	(__OFF__)

/*
  Description: Double lines of menuitem
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: UI Customization SOP
*/
#define CFG_MMI_UI_HINTS_IN_MENUITEM	(__OFF__)

/*
  Description: List highlight effect
  Option: [HIGHLIGHT_EFFECT_AUTO, HIGHLIGHT_EFFECT_SLIDE, HIGHLIGHT_EFFECT_TRANSPARENCY, HIGHLIGHT_EFFECT_FLASH_FEELING, HIGHLIGHT_EFFECT_ANIMATION, HIGHLIGHT_EFFECT_NONE]
  Reference: UI Customization SOP
*/
#define CFG_MMI_UI_LIST_HIGHLIGHT_EFFECT_TYPE_SEL	(HIGHLIGHT_EFFECT_NONE)

/*
  Description: Support list highlight effect
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: UI Customization SOP
*/
#define CFG_MMI_UI_LIST_HIGHLIGHT_EFFECTS	(__OFF__)

/*
  Description: 2 line menuitem with Inline Select effect
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: UI Customization SOP
*/
#define CFG_MMI_UI_TWO_LINE_MENUITEM_STYLES	(__OFF__)

/*
  Description: Add bold font in highlight
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: UI Customization SOP
*/
#define CFG_MMI_UI_LIST_HIGHLIGHT_BOLD	(__OFF__)

/*
  Description: Access menu by shortcut directly
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: UI Customization SOP
*/
#define CFG_MMI_LIST_MENU_HIGHLIGHT_CHANGE_AND_GOTO_BY_SHORTCUT	(__OFF__)

/*
  Description: enable the display of cascaded option menu
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_Menu_Common_UI.doc
*/
#define CFG_MMI_CASCADED_OPTION_MENU	(__OFF__)

/*
  Description: Set Default Highlight Mainmenu Item
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Modify_Guide_MessageDefaultHighlight.doc
*/
#define CFG_MMI_DEFAULT_MAIN_MENU_HIGHLIGHT_MESSAGE	(__OFF__)

/*
  Description: slim for mainmenu
  Option: [__ON__, __AUTO__, __OFF__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_IDLE_CLASSIC_AND_MAINMENU_SUPPORT	(__ON__)

/*
  Description: Support list main menu
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: UI Customization SOP
*/
#define CFG_MMI_MAINMENU_LIST_SUPPORT	(__ON__)

/*
  Description: Support matrix main menu
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: UI Customization SOP
*/
#define CFG_MMI_MAINMENU_MATRIX_SUPPORT	(__OFF__)

/*
  Description: Support page main menu
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: UI Customization SOP
*/
#define CFG_MMI_MAINMENU_PAGE_SUPPORT	(__OFF__)

/*
  Description: Spread pluto mainmenu items.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_UI_Customization.doc
*/
#define CFG_MMI_MAINMENU_SPREAD_SUPPORT	(__OFF__)

/*
  Description: For Speed Up matrix mainmenu display
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: UI Customization SOP
*/
#define CFG_MMI_MATRIX_MAIN_MENU_OPTIMIZE	(__OFF__)

/*
  Description: Select the matrix main menu highlight image type
  Option: [__RES_TYPE_PNG__, __RES_TYPE_GIF__, __RES_TYPE_SEQUENCE__]
  Reference: UI Customization SOP
*/
#define CFG_MMI_RES_TYPE_MAINMENU_MATRIX_ANI_SEL	(__RES_TYPE_PNG__)

/*
  Description: Select the matrix main menu normal image type
  Option: [__RES_TYPE_PNG__, __RES_TYPE_GIF__]
  Reference: UI Customization SOP
*/
#define CFG_MMI_RES_TYPE_MAINMENU_MATRIX_SEL	(__RES_TYPE_PNG__)

/*
  Description: Matrix main menu highlight effect
  Option: [HIGHLIGHT_EFFECT_AUTO, HIGHLIGHT_EFFECT_NONE, HIGHLIGHT_EFFECT_SLIDE]
  Reference: UI Customization SOP
*/
#define CFG_MMI_UI_MAIN_MENU_MATRIX_HIGHLIGHT_EFFECT_TYPE_SEL	(HIGHLIGHT_EFFECT_NONE)

/*
  Description: Scaling effect for matrix main menu.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: UI Customization SOP
*/
#define CFG_MMI_UI_MATRIX_MAIN_MENU_SCALING_EFFECT	(__OFF__)

/*****************************************************************************
* Application Framework
    * Pluto UI Component
        * Text
*****************************************************************************/

/*
  Description: Copy/cut/paste in editor
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: HLD_Clipboard.ppt
*/
#define CFG_MMI_CLIPBOARD	(__OFF__)

/*
  Description: Editor option menu style
  Option: [__STYLE_NONE__, __STYLE_1__, __STYLE_2__, __STYLE_3__]
  Reference: 
*/
#define CFG_MMI_EDITOR_OPTION_MENU_STYLE	(__STYLE_NONE__)

/*****************************************************************************
* Application Framework
    * System Application
        * Bootup & Shutdown
*****************************************************************************/

/*
  Description: Enable forwarding image to power on/off display
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PhoneSetup.doc
*/
#define CFG_MMI_POWER_ON_OFF_DISPLAY	(__OFF__)

/*
  Description: Power on off video display
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PhoneSetup.doc
*/
#define CFG_MMI_POWER_ON_OFF_DISPLAY_VIDEO	(__OFF__)

/*
  Description: SLIM common option for Bootup
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_BOOTUP_SLIM	(__ON__)

/*
  Description: Support boot up mode selection.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_BOOTUP_MODE_SEL_SUPPORT	(__OFF__)

/*
  Description: for fast entry to Factory mode during power-on period
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_BOOTUP_SHUTDOWN.doc
*/
#define CFG_DIRECT_ENTRY_FACTORY_MODE_ON_BOOTUP	(__OFF__)

/*****************************************************************************
* Application Framework
    * System Application
        * NCenter(Service)
*****************************************************************************/

/*
  Description: Enable key-only NCenter in FTE projects
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_FRM_Notifications_NCenter_11B_Latest.pptx
*/
#define CFG_MMI_KEY_ONLY_NCENTER	(__ON__)

/*
  Description: Enable NCenter function (FTE/Cosmos only).
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: (Herman)PRST_VsrvNCenter.pptx
*/
#define CFG_MMI_NCENTER_SUPPORT	(__ON__)

/*****************************************************************************
* Application Framework
    * Venus UI
        * Core
*****************************************************************************/

/*
  Description: Add CFG for venus test bed
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: HLD_Venus_RT_Revise.ppt
*/
#define CFG_MMI_VENUS_RT	(__OFF__)

/*
  Description: VRT cache memory configuration
  Option: [__OFF__, (480)]
  Reference: 
*/
#define CFG_MMI_VRT_CACHE_SIZE_FACTOR	(__OFF__)

/*
  Description: To switch the size of Venus System Global Memory
  Option: [__OFF__, 100 * 1024, 150 * 1024]
  Reference: 
*/
#define CFG_MMI_VFX_SYS_GLOBAL_MEM_SIZE	(__OFF__)

/*
  Description: Venus UI Engine Slim
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VUI_ENGINE.pptx
*/
#define CFG_MMI_REDUCED_UI_BUFFER	(__OFF__)

/*****************************************************************************
* Application Framework
    * Venus UI
        * Download Theme(Cosmos)
*****************************************************************************/

/*****************************************************************************
* Application Framework
    * Venus UI Component
        * Bars
*****************************************************************************/

/*
  Description: status icon bar slim for cosmos
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_STATUSICON.pptx
*/
#define CFG_MMI_COSMOS_STATUS_BAR_SLIM	(__OFF__)

/*****************************************************************************
* Application Framework
    * Venus UI Component
        * Text
*****************************************************************************/

/*
  Description: Turn on/off text CP (text editor, text view) emotion icon support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VcpTextView_VcpTextEditor.ppt
*/
#define CFG_MMI_VUI_TEXT_EMOTION_ICON_SUPPORT	(__OFF__)

/*****************************************************************************
* Auxiliary
    * Engineering Mode
*****************************************************************************/

/*
  Description: Turn-on MMI Engineer Mode Application
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_ENGINEER_MODE	(__OFF__)

/*
  Description: Engineer Mode: Speech Enhancement
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_EM_AUDIO	(__OFF__)

/*
  Description: Engineer Mode: BT->Audio connection & disconnection
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_EM_BT_AUDIO_CONN	(__OFF__)

/*
  Description: To add CTA conformance test mode to let CMCC TD pass CMCC CTA authrization.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_EM_CTM_CTA_TDD	(__OFF__)

/*
  Description: Engineer Mode: Dev-Clam
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_EM_DEV_CLAM	(__OFF__)

/*
  Description: Engineer Mode: Dev-DCM
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_EM_DEV_DCM_MODE	(__OFF__)

/*
  Description: Engineer Mode: Dev-EINT
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_EM_DEV_EINT	(__OFF__)

/*
  Description: Engineer Mode: Memory Device Test. To show memory device detail information in EM Deivce menu.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_EM_DEV_MEMORY_TEST	(__OFF__)

/*
  Description: Engineer Mode: PMU  register setting
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_EM_DEV_PMU_REGISTER_SETTING	(__AUTO__)

/*
  Description: EngineerMode: Device->PXS Sensor
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_FM.doc
*/
#define CFG_MMI_EM_DEV_PXS_SENSOR	(__AUTO__)

/*
  Description: Engineer Mode: Device->Tst output mode, CFG=__ON__ means can turn on it even in EM slim modeCFG = __AUTO__ means can not turn on it in EM slim mode
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_EM_DEV_TST_OUTPUT_MODE	(__AUTO__)

/*
  Description: EngineerMode: Device->USB-> USB Tethering(RNBS)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_EM_DEV_USB_TETHERING	(__AUTO__)

/*
  Description: Engineer Mode: GPRS->Auto attach
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_EM_GPRS_AUTO_ATTACH	(__AUTO__)

/*
  Description: Multi-Touch test in Engineer mode
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_EM_MISC_MULTI_TOUCH	(__OFF__)

/*
  Description: Engineer Mode: Touch Screen
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_EM_MISC_TOUCH_SCREEN	(__OFF__)

/*
  Description: EngineerMode: 3G FDD network info
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_EM_NW_FDD_NETWORK_INFO	(__OFF__)

/*
  Description: Engineer Mode: Network settings->network info
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_EM_NW_NETWORK_INFO	(__ON__)

/*
  Description: Engineer Mode: Preference for PLMN List.To control by select "Speed Preferred" or "Accuracy Preferred"
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_EM_NW_PLMN_LIST	(__AUTO__)

/*
  Description: EngineerMode: 3G TDD network info
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_EM_NW_TDD_NETWORK_INFO	(__OFF__)

/*
  Description: TD
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: When this compile option is set to __AUTO__ or __ON__ the service selection will not be displayed in network setting but in EM => Network information
*/
#define CFG_MMI_EM_NW_SERVICE_MODE_SELECTION	(__OFF__)

/*
  Description: Engineer Mode: RF test tools-> GSM RF test
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_EM_RF_GSM	(__AUTO__)

/*
  Description: Engineer Mode: RF test toos->WIFI-slim
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_EM_RF_WIFI	(__OFF__)

/*
  Description: Interactive UI performance profiling in Engineer Mode
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_UI_Display_Performance_Tuning.xls
*/
#define CFG_MMI_INTERACTIVE_PROFILNG	(__OFF__)

/*
  Description: Engineer Mode: UI Benchmark
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_UI_Customization.doc
*/
#define CFG_MMI_UI_BENCHMARK	(__OFF__)

/*
  Description: Engineermode NFC test
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_EM_NFC_SUPPORT	(__AUTO__)

/*
  Description: support "power on cpu query"feature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: USER_MANUAL_APP_EM.doc
*/
#define CFG_MMI_EM_MISC_POWER_ON_CPU_QUERY	(__OFF__)

/*
  Description: support "SWLA" feature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: USER_MANUAL_APP_EM.doc
*/
#define CFG_MMI_EM_PROFILING_SWLA	(__OFF__)

/*
  Description: slim for em
  Option: [__ON__, __AUTO__, __OFF__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_EM_BT_TEST_SLIM	(__ON__)

/*
  Description: Engineer Mode: Device->Sleep Mode
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_EM_DEV_SLEEP_MODE	(__OFF__)

/*
  Description: It config is for EM GPRS Fast dormancy
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_EM_GPRS_FAST_DORMANCY	(__AUTO__)

/*
  Description: Engineer Mode: Audio->PDP
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_EM_GPRS_PDP	(__OFF__)

/*
  Description: slim for em
  Option: [__ON__, __AUTO__, __OFF__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_EM_GPRS_PDP_SLIM	(__OFF__)

/*
  Description: surport for wcdma preferred in em
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: WCDMA Preferred_DD
*/
#define CFG_MMI_EM_NW_WCDMA_PREFERRED	(__AUTO__)

/*
  Description: slim for em
  Option: [__ON__, __AUTO__, __OFF__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_EM_SLEEP_MODE_SLIM	(__ON__)

/*
  Description: the setting of Video Streaming mode/User Agent selection by EM
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: video_streaming_em_menu.ppt
*/
#define CFG_MMI_EM_VIDEO_STREAMING_SETTING	(__OFF__)

/*
  Description: Engineer Mode: SLIM Engineer Mode
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_EM.doc
*/
#define CFG_MMI_SLIM_ENGINEER_MODE	(__ON__)

/*****************************************************************************
* Auxiliary
    * Engineering Mode
        * Multimedia
*****************************************************************************/

/*****************************************************************************
* Auxiliary
    * Factory Mode
*****************************************************************************/

/*
  Description: FactoryMode NFC  test
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: User_Manual_APP_FM.doc
*/
#define CFG_MMI_FM_NFC_SUPPORT	(__AUTO__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_SLIM_FACTORY_MODE	(__ON__)

/*****************************************************************************
* Bluetooth
    * BT Dialer
        * Notifier APK
*****************************************************************************/

/*
  Description: this feature is for apk smart install
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_BLE_DOGP_SUPPORT	(__ON__)

/*
  Description: this feature is for apk smart install
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_BT_APK_SMART_INSTALL_SUPPORT	(__OFF__)

/*****************************************************************************
* Bluetooth
    * BT Dialer
        * Remote Notifier (Pluto)
*****************************************************************************/

/*
  Description: It will enable BT Notification Enhance, such as page, group, action, sync etc
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_BT_NOTIFICATION_ENHANCE	(__OFF__)

/*****************************************************************************
* Bluetooth
    * Profile
*****************************************************************************/

/*
  Description: This feature will let ftp client support "Get all files" and "Get list files", it can make ftp client get file much more easily.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_MTK_FTP_06A_Latest.doc
*/
#define CFG_MMI_FTC_MULTIPULL_SUPPORT	(__AUTO__)

/*
  Description: While transferring objects via Bluetooth, this feature can storage the objects to different folders according to their types. It makes classifying the received files much more convenient. For instance, Image files will stored in 'Image' folder, Audio files will stored in 'Audio' folder etc.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Bluetooth_feature_supplement.doc
*/
#define CFG_MMI_BT_RECV_FDR_SWITCH	(__OFF__)

/*
  Description: to enable bluetooth device authorization mechanism
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_MTK_BT_CM_09A_Latest.doc
*/
#define CFG_MMI_BT_AUTHORIZE	(__OFF__)

/*
  Description: to enable auto bt power on/off while doing object push
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_MTK_BT_CM_09A_Latest.doc
*/
#define CFG_MMI_BT_AUTO_POWER_SWITCH	(__OFF__)

/*
  Description: open double buffer to write file
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_MTK_OPP_08B_latest
*/
#define CFG_MMI_BT_RX_ENHANCE	(__OFF__)

/*
  Description: to display more receiving object information, object name and type,  for OPP server and BIP responder
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_MTK_OPP_08B_latest
*/
#define CFG_MMI_BT_RECV_OBJ_DETAIL	(__OFF__)

/*
  Description: to turn on BT in flight mode feature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_MTK_BT_CM_09A_Latest.doc
*/
#define CFG_MMI_BT_IN_FLIGHT_MODE	(__OFF__)

/*
  Description: to enable the discoverable duration be 2 minutes
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_MTK_BT_CM_09A_Latest.doc
*/
#define CFG_MMI_BT_TEMP_VISIBILITY	(__OFF__)

/*
  Description: This feature is about anti-lost
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Anti_lost_UI_design_doc.ppt
*/
#define CFG_MMI_BT_ANTI_LOST_BY_RSSI	(__OFF__)

/*
  Description: This feature is about BQB test.It is configed as AUTO or ON on specified project.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: BQB.ppt
*/
#define CFG_MMI_BT_APPLICATION_BQB	(__OFF__)

/*
  Description: If defined, default device will be supported in Send via Bluetooth function. End user can set or clear default device each time sending is ongoing.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Bluetooth_feature_supplement.doc
*/
#define CFG_MMI_BT_DEF_SEND_DEVICE	(__OFF__)

/*
  Description: BT dialer Support - Support BT call
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_BT_DIALER_SUPPORT	(__OFF__)

/*
  Description: It will use APK (by SPP) to replace MAP profile in BT dialer v2.x projects
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_BT_Dialer.ppt
*/
#define CFG_MMI_BT_MAPC_BY_SPP	(__OFF__)

/*
  Description: It will enable Remote Notifier App in BT dialer v2.x projects
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_BT_Dialer.ppt
*/
#define CFG_MMI_BT_NOTIFICATION	(__OFF__)

/*
  Description: It will enable remote capture App in BT dialer projects.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_BT_Dialer.ppt
*/
#define CFG_MMI_BT_REMOTE_CAPTURE	(__OFF__)

/*
  Description: Bluetooth MMI slim version support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_BT_SLIM	(__OFF__)

/*
  Description: It will enable wearable device features, such as Clock/Mainmenu, Pedometer, Yahoo weather, Facebook, etc
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_Wearable_Device.ppt
*/
#define CFG_MMI_WEARABLE_DEVICE	(__OFF__)

/*
  Description: It will enable wristband device features, such as Clock/Mainmenu, heartrate etc
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Reference: DD_Wristband_Device.ppt
*/
#define CFG_MMI_WRISTBAND_SUPPORT	(__OFF__)

/*****************************************************************************
* Bluetooth
    * Profile
        * BT App(Pluto)
*****************************************************************************/

/*
  Description: enable BLE data transfer feature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_BLE_PDMS_SUPPORT	(__OFF__)

/*****************************************************************************
* Bluetooth
    * Profile
        * SPP(Service)
*****************************************************************************/

/*
  Description: enable Bas service
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_BLE_BAS_SUPPORT	(__OFF__)

/*****************************************************************************
* Connectivity
    * Bearer Management
        * CBM(Pluto)
*****************************************************************************/

/*****************************************************************************
* Connectivity
    * Data Account
        * Data Account(Pluto)
*****************************************************************************/

/*
  Description: SLIM common option for Data account
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: provide after 32MP
*/
#define CFG_MMI_DTCNT_SLIM	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_DTCNT_XML_SLIM	(__OFF__)

/*****************************************************************************
* Device
    * GPIO
*****************************************************************************/

/*
  Description: When clam close, phone will go back to idle screen
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_DEVICEINTERFACE.doc
*/
#define CFG_MMI_CLAMCLOSE_BACK2IDLE	(__OFF__)

/*
  Description: When defined __MMI_CLAMSHELL__, it should define __MMI_SYNC_LCD_GPIO_MODE__.There are 2 policy of backlight handling. One is for clam/slide phone, and the other is for bar phone.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_DEVICEINTERFACE.doc
*/
#define CFG_MMI_SYNC_LCD_GPIO_MODE	(__OFF__)

/*
  Description: For some LCM can retain display even when backlight is turned off, and hence we can turn off backlight without making LCM sleep.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_DEVICEINTERFACE.doc
*/
#define CFG_MMI_GPIO_DISABLE_SLEEP_MODE	(__OFF__)

/*
  Description: BTBOX Linein
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_BTDIALER.pptx
*/
#define CFG_MMI_LINE_IN	(__OFF__)

/*****************************************************************************
* Device
    * Sensor
        * Sensor(APP)
*****************************************************************************/

/*
  Description: to enable all sensor init
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: how to preload MRE application.ppt
*/
#define CFG_MMI_MRE_ALL_SENSOR_INIT	(__ON__)

/*****************************************************************************
* Device
    * USB
        * USB(Cosmos)
*****************************************************************************/

/*
  Description: USB Slim
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_USB.ppt
*/
#define CFG_MMI_USB_SLIM	(__ON__)

/*****************************************************************************
* Device
    * USB
        * USB(Service)
*****************************************************************************/

/*****************************************************************************
* Extra
    * Calculator
        * Calculator(Pluto)
*****************************************************************************/

/*
  Description: Turn on Calculator application
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_CALCULATOR.doc
*/
#define CFG_MMI_CALCULATOR	(__OFF__)

/*****************************************************************************
* Extra
    * Converter
        * Converter(Cosmos)
*****************************************************************************/

/*
  Description: Converter support FTO
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MMI_DD_CURRENCYCONVERTER.doc
*/
#define CFG_MMI_CONVERTER	(__OFF__)

/*****************************************************************************
* Extra
    * EBook Reader
        * Ebook Reader(Cosmos)
*****************************************************************************/

/*
  Description: Cosmos EBook Reader
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_EBOOK_READER	(__OFF__)

/*****************************************************************************
* Extra
    * Location and Navigation
        * E-Compass(Pluto)
*****************************************************************************/

/*
  Description: to turn on ECOMPASS application
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_ECompass.doc
*/
#define CFG_MMI_ECOMPASS	(__OFF__)

/*****************************************************************************
* Extra
    * Rights Manager
        * Rights Manager(Pluto)
*****************************************************************************/

/*
  Description: setting premission of LinkIt applications
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: CTA_Security_Level1_for_Wearable_SOP.pptx
*/
#define CFG_MMI_SMART_DEVICE_SECURITY_SUPPORT	(__OFF__)

/*****************************************************************************
* Extra
    * World Clock
        * World Clock(Cosmos)
*****************************************************************************/

/*
  Description: Turn on World Clock
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_WORLDCLOCK.doc
*/
#define CFG_MMI_WORLD_CLOCK	(__ON__)

/*
  Description: Extended World Clock version. It support time zone selection and display datetime of local and foreign cities.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_NITZ.doc
*/
#define CFG_MMI_WC_TZ_SUPPORT	(__ON__)

/*
  Description: WorldClock UE changed
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_GALLERY.ppt
*/
#define CFG_MMI_WORLDCLOCK_SLIM	(__ON__)

/*****************************************************************************
* Internet
    * Browser
*****************************************************************************/

/*
  Description: Baidu search application
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_Baidu.doc
*/
#define CFG_MMI_SEARCH_WEB_BAIDU	(__OFF__)

/*
  Description: Disable Push URL Display
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PUSH_08A_latest.doc
*/
#define CFG_MMI_BRW_DISABLE_PUSH_URL_DISPLAY	(__OFF__)

/*
  Description: Push Connect Confirmation
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PUSH_08A_latest.doc
*/
#define CFG_MMI_BRW_PUSH_CONNECT_CONF	(__OFF__)

/*
  Description: Support for browser content types in Push msges
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_BROWSER_07A_latest.doc
*/
#define CFG_MMI_BRW_BROWSER_CONTENT_TYPES_IN_PUSH	(__OFF__)

/*
  Description: Automatically delete SL message after it has been launched in browser.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PUSH_08A_latest.doc
*/
#define CFG_MMI_BRW_PUSH_DELETE_SL_AFTER_LAUNCH_SUPPORT	(__OFF__)

/*
  Description: Configures WAP push's whitelist address via OMA Client Provisioning.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PUSH_08A_latest.doc
*/
#define CFG_MMI_BRW_PUSH_WHITELIST_OTA_SUPPORT	(__OFF__)

/*
  Description: Input url auto completion support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_BROWSER_07A_latest.doc
*/
#define CFG_MMI_BRW_URL_AUTO_COMPLETION	(__OFF__)

/*
  Description: Bookmarks transfer support to memory card
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_BROWSER_07A_latest.doc
*/
#define CFG_MMI_BRW_TRANSFER_BOOKMARK_TO_EXT_MEMORY	(__OFF__)

/*
  Description: To display page fetching status (connecting, processing, loading) in progress bar
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_BROWSER_07A_latest.doc
*/
#define CFG_MMI_BRW_PAGE_FETCHING_STATUS	(__OFF__)

/*
  Description: This feature optin is used to turn on/off browser bookmark API support. When this option is on, user can add URL to browser bookmark when he reads message/email and insert bookmark to message/email when he edits message/email.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: HLD_bookmark_cui.ppt
*/
#define CFG_MMI_BRW_BKM_INTERFACE_SUPPORT	(__OFF__)

/*
  Description: to turn on/off browser splash screen
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_BRA_07B_Latest.doc
*/
#define CFG_MMI_WAP_SPLASH_SCREEN_SUPPORT	(__OFF__)

/*
  Description: Q05A browser start-up page
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: CMCC RELATED SPECS
*/
#define CFG_MMI_Q05A_LAUNCH_SCREEN	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_BRW_SEND_ADDRESS_SLIM	(__ON__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_BRW_USER_DEFINED_HOMEPAGE_SLIM	(__ON__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_BRW_RECENT_PAGES_SLIM	(__ON__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_BRW_IMG_RES_SLIM	(__ON__)

/*
  Description: Compile option for Baidu Search APP in Cosmos
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_BAIDU_SEARCH_COSMOS	(__OFF__)

/*
  Description: Browser Slim
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_BRW.ppt
*/
#define CFG_MMI_BRW_SLIM	(__ON__)

/*
  Description: Turn ON File Upload support in Obigo Browser
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_BRW_FILE_UPLOAD_SUPPORT	(__OFF__)

/*
  Description: Browser memory SLIM
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MT6261-browser_bookmark-SLIM_Feature_Options.ppt
*/
#define CFG_MMI_BRW_SLIM_BOOKMARK_SUPPORT	(__ON__)

/*
  Description: Option to set image cache location
  Option: [__TCARD__, __SYS_DRIVE__, __PH_DRIVE__, __ASM__, __TCARD_PLUS_SYS__, __TCARD_PLUS_PH__]
  Reference: n/a
*/
#define CFG_MMI_WAP_IMAGE_CACHE_OPTION	(__TCARD__)

/*****************************************************************************
* Internet
    * Cloud
        * SSO(Cosmos)
*****************************************************************************/

/*
  Description: When any interrupt happens on logging in screen, login procedure can still continue in background.If this feature is off, any interuppt will cause the login procedure canceled.Recommend to turn it off on limited ASM projects (ex. 128+64 projects)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FTE_UE_Spec_Yahoo_Cloud_Service.vsd, FTO_UE_Spec_Yahoo_Cloud_Service.vsd
*/
#define CFG_MMI_SSO_BACKGROUND_LOGIN	(__OFF__)

/*****************************************************************************
* Internet
    * Cloud
        * SSO(Pluto)
*****************************************************************************/

/*
  Description: SSO means "Single Sign On" , user can login once and be able to access multiple services.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: TBD
*/
#define CFG_MMI_SSO	(__OFF__)

/*
  Description: OOBE means "Out of box experience", when user first boots-up the phone, there will be prompt out for user to enter account/password, and enable the SSO service.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: TBD
*/
#define CFG_MMI_SSO_OOBE	(__OFF__)

/*
  Description: Pre-load the Yahoo! SSO plug-in(vpp file) in ROM,1. User won't have chance to delete the VPP file (1st version),2. Can always upgrade VPP file if the 1st version plug-in exists when CFG_MMI_SSO_VPP_UPGRADE is on.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FTE_UE_Spec_Yahoo_Cloud_Service.vsd
*/
#define CFG_MMI_SSO_PRELOAD_YAHOO	(__OFF__)

/*
  Description: Enable the function of Yahoo! sso plug-in(vpp file) upgrade by upgrade service
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FTE_UE_Spec_Yahoo_Cloud_Service.vsd
*/
#define CFG_MMI_SSO_VPP_UPGRADE	(__OFF__)

/*****************************************************************************
* Internet
    * Download Agent
        * Download Agent(Cosmos)
*****************************************************************************/

/*
  Description: Download aget slim
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_DLA.pptx
*/
#define CFG_MMI_DLA_SLIM	(__OFF__)

/*****************************************************************************
* Internet
    * Download Agent
        * Download Agent(Pluto)
*****************************************************************************/

/*
  Description: To support download multiple files on browser at the same time. Download list will be shown while downloading.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_DA_08B_W0901.doc
*/
#define CFG_MMI_DOWNLOAD_AGENT_MULTI_DL	(__OFF__)

/*
  Description: OMA download support for browser download. Please refer to the spec document OMA-Download-OTA-V1_0-20040625-A.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_DA_08B_W0901.doc,  OMA-Download-OTA-V1_0-20040625-A
*/
#define CFG_MMI_OMA_DD_DOWNLOAD	(__OFF__)

/*
  Description: To support tag <iconURI> for OMA download. If this feature is on, DLAgent will download the icon at <iconURI> and register it to FMGR. Afterward users can see the icon associated to the file downloaded on File Manager.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_DA_08B_W0901.doc
*/
#define CFG_MMI_DA_OMA_ICONURI_SUPPORT	(__OFF__)

/*
  Description: Pressing LSK to show <name> and <description> in View Detail screen for OMA download
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_DA_08B_W0901.doc
*/
#define CFG_MMI_DA_OBJECT_DESCRIPTION_SUPPORT	(__OFF__)

/*
  Description: To configure the screen flow of downloading a file.__DA_FLOW_1__: Object confirm -> Options to view DD -> Select storage -> Input filename ->               Start to download__DA_FLOW_2__: Object confirm-> Select storage -> Start to download__DA_FLOW_3__: Object confirm -> Options to view DD -> Select storage -> Start to download"Object confirm" shows the information of the file to be downloaded.    The information is extracted from HTTP header for normal download.    For OMA download, it will be extracted from the download descriptor."Options to view DD" is present only for OMA download. It provides an options menu of    "View descriptor" to view the content of the download descriptor and    "Start download" to continue next step.
  Option: [__DA_FLOW_1__, __DA_FLOW_2__, __DA_FLOW_3__]
  Reference: FRS_DA_08B_W0901.doc
*/
#define CFG_MMI_DA_DOWNLOAD_FLOW	(__DA_FLOW_1__)

/*
  Description: Resumption support of browser downloads
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_DA_08B_W0901.doc
*/
#define CFG_MMI_DA_RESUME	(__OFF__)

/*
  Description: download agent config
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: CMCC releated spec
*/
#define CFG_MMI_DA_DOWNLOAD_AUTO_RESUME_WHEN_BROWSER_EXIT	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_DA_CONF_PAGE_SLIM	(__OFF__)

/*****************************************************************************
* Internet
    * Download Agent
        * Download Agent(Service)
*****************************************************************************/

/*****************************************************************************
* Internet
    * SNS
*****************************************************************************/

/*
  Description: To enable SNS online album support for applications.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: PromotionalSlides_SNS_deep_integration.pptx
*/
#define CFG_MMI_SNS_ALBUM	(__AUTO__)

/*
  Description: To enable SNS support for calendar application.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: PromotionalSlides_SNS_deep_integration.pptx
*/
#define CFG_MMI_SNS_CALENDAR	(__AUTO__)

/*
  Description: To enable social network center application
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_SNS_CENTER	(__AUTO__)

/*
  Description: To enable social network support in phonebook application
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_SNS_CONTACTS	(__AUTO__)

/*
  Description: To enable social network support in unified messages (cosmos)to enable social netwotk message support in social network center (fte 2.0)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_SNS_MESSAGES	(__AUTO__)

/*
  Description: To enable uploading photo to social network from gallery
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_SNS_PHOTO_UPLOAD	(__AUTO__)

/*
  Description: Preload Facebook plug-in
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SNS_CONFIGURATION_GUIDE.doc
*/
#define CFG_MMI_SNS_PRELOAD_FACEBOOK	(__AUTO__)

/*
  Description: Preload Renren plug-in
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SNS_CONFIGURATION_GUIDE.doc
*/
#define CFG_MMI_SNS_PRELOAD_RENREN	(__OFF__)

/*
  Description: Preload Twitter plug-in
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SNS_CONFIGURATION_GUIDE.doc
*/
#define CFG_MMI_SNS_PRELOAD_TWITTER	(__AUTO__)

/*
  Description: To enable SNS online album support for applications
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: PromotionalSlides_SNS_deep_integration.pptx
*/
#define CFG_MMI_VUI_HOMESCREEN_SNS	(__AUTO__)

/*****************************************************************************
* Internet
    * Search
        * Search Web(Pluto)
*****************************************************************************/

/*****************************************************************************
* Internet
    * Search
        * Winguo(Pluto)
*****************************************************************************/

/*****************************************************************************
* Language and Input Method
    * Font
        * Font Engine
*****************************************************************************/

/*
  Description: Use 16x16 Chinese font
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_16X16_CHINESE_FONT	(__OFF__)

/*
  Description: BDF Font Compression.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Bitmap_Font_Compression_Codec_SDS_V1.0.doc
*/
#define CFG_MMI_BDF_SW_COMPRESSION	(__ON__)

/*
  Description: To support install vector font resource from storage, like, phone storage or memory card
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_Vector_Font_On_Memory_Card.ppt
*/
#define CFG_MMI_FE_VECTOR_FONT_ON_FILE_SYSTEM	(__OFF__)

/*
  Description: Enable compressed font.In MTK internal project: only Support resolution: 176X220, 240X320 only Support language: English, SC
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: HLD_Font Compression.ppt
*/
#define CFG_MMI_FONT_COMPRESSION	(__OFF__)

/*
  Description: Vector Font Pre-load On Memory Card
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_FONT&IME_MEMORYCARD.doc
*/
#define CFG_MMI_VECTOR_FONT_MEMORY_CARD_SUPPORT	(__OFF__)

/*
  Description: font group compression
  Option: [__ON__, off.auto]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_FONT_GROUP_COMPRESSION	(__ON__)

/*****************************************************************************
* Language and Input Method
    * IME
*****************************************************************************/

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_MULTITAP_PHONETIC_INPUT	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_STROKE_INPUT	(__OFF__)

/*
  Description: turn on preferred writing language setting menu in phone setup. Can't exist with __MMI_PREFER_INPUT_METHOD__ or __MMI_IME_MIXED_LANG_SUPPORT__
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_INPUT_METHOD.doc
*/
#define CFG_MMI_IME_PREFER_WRITING_LANG	(__OFF__)

/*
  Description: turn on mixed language support for Alphabetic langauge.  Can't exist with __MMI_PREFER_INPUT_METHOD__ or __MMI_IME_PREFER_WRITING_LANG__.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_Mixed_Language_Support
*/
#define CFG_MMI_IME_MIXED_LANG_SUPPORT	(__OFF__)

/*
  Description: to turn on Alphabetic word prediction
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_INPUT_METHOD.doc
*/
#define CFG_MMI_IME_ALPHABETIC_WORD_PREDICTION	(__OFF__)

/*
  Description: Whether use user dictionary
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_INPUT_METHOD.doc
*/
#define CFG_MMI_IME_CSTAR_USER_DICT	(__OFF__)

/*
  Description: Defines this compile option for VK unfold style . that means the Virtual Keyboard will default be unfolded when entry new screen and change input mode
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_FRM_HANDWRITING.doc
*/
#define CFG_MMI_IME_EDITOR_PEN_VK_UNFOLD	(__OFF__)

/*
  Description: Multi-block Handwriting Style support. It depends on global compile option __MMI_TOUCH_SCREEN__
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_FRM_HANDWRITING.doc
*/
#define CFG_MMI_IME_HANDWRITING_MULTI_BLOCK	(__OFF__)

/*
  Description: use PenPower Phrase function under SC and TC mode
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_FRM_HANDWRITING.doc
*/
#define CFG_MMI_IME_HANDWRITING_PHRASE	(__OFF__)

/*
  Description: to turn on T9 default BoPoMo input method keymaping
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A, SOP_T9_Input_Method_Resource_Generation and vendor relative document
*/
#define CFG_MMI_IME_T9_DEFAULT_KEY_DEFINITION	(__OFF__)

/*
  Description: to turn on Multitap Keymap 1
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, DD_Input_Method_Keymap and SOP_Language_and_Input_Method_Porting_Guide_08A
*/
#define CFG_MMI_IME_MULTITAP_THAI_PROFILE_1	(__AUTO__)

/*
  Description: to turn on Multitap Keymap 2
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, DD_Input_Method_Keymap and SOP_Language_and_Input_Method_Porting_Guide_08A
*/
#define CFG_MMI_IME_MULTITAP_THAI_PROFILE_2	(__AUTO__)

/*
  Description: to turn on capital switch, can not be turned on with __MMI_IME_PREFER_WRITING_LANG__ or __MMI_IME_MIXED_LANG_SUPPORT__
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_INPUT_METHOD.doc
*/
#define CFG_MMI_IME_IMC_CAPITAL_SWITCH	(__OFF__)

/*
  Description: to turn on first letter uppercase input methods
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_INPUT_METHOD.doc
*/
#define CFG_MMI_IME_SMART_FIRST_UPPERCASE	(__OFF__)

/*
  Description: to turn on multitap first upper case input methods
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_INPUT_METHOD.doc
*/
#define CFG_MMI_IME_MULTITAP_FIRST_UPPERCASE	(__OFF__)

/*
  Description: to turn on the input mode change rules
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_INPUT_METHOD.doc
*/
#define CFG_MMI_IME_INPUT_MODE_CHANGE_RULES	(__OFF__)

/*
  Description: to turn on Magic one support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_IME_MAGIC_ONE	(__OFF__)

/*
  Description: to turn on smart input method with input area style
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_IME_SMART_WITH_INPUT_AREA	(__OFF__)

/*
  Description: multitap input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_MULTITAP	(__AUTO__)

/*
  Description: Turn ON multitap input support from Cstar library, instead of MTK's internal multitap support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_CSTAR_MULTITAP	(__OFF__)

/*
  Description: For enabling T9 Multitap
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_T9_MULTITAP	(__AUTO__)

/*
  Description: change dialling screen mulitap + p w from key star to key-zero
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, DD_Input_Method_Keymap and SOP_Language_and_Input_Method_Porting_Guide_08A
*/
#define CFG_MMI_MULTITAP_KEY_0	(__OFF__)

/*
  Description: to turn on reselection of smart alphabetic input mode
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_INPUT_METHOD.doc
*/
#define CFG_MMI_SMART_ALPHABETIC_RESELECTION	(__OFF__)

/*
  Description: To turn on vertical candidate box of smart alpahbetic input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_INPUT_METHOD.doc
*/
#define CFG_MMI_IME_VERTICAL_CAND_BOX	(__OFF__)

/*
  Description: To turn on floating candidate box of input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_INPUT_METHOD.doc
*/
#define CFG_MMI_IME_FLOATING_CAND_BOX	(__OFF__)

/*
  Description: Whether use user customized theme setting
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_Font_And_Input_Method_Spec_for_Different_Languages, SOP_Language_and_Input_Method_Porting_Guide, LanguageStatus, vendor relative document
*/
#define CFG_MMI_CSTAR_USE_CUSTOMIZED_THEME	(__OFF__)

/*
  Description: turn on preferred input method setting menu in phone setup
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_INPUT_METHOD
*/
#define CFG_MMI_PREFER_INPUT_METHOD	(__ON__)

/*
  Description: If the hardware key has "Clear" keypad, define this macro can support the "Clear" keypad function
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SAP MULTILINE EDITOR CONTROL.doc
*/
#define CFG_MMI_WITH_C_KEY	(__OFF__)

/*
  Description: popup hint of virtual keyboard
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_UI_Customization.doc
*/
#define CFG_MMI_VK_POPUP_HINT	(__OFF__)

/*
  Description: to turn on Input method user data base
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_INPUT_METHOD.doc
*/
#define CFG_MMI_IME_USER_DATABASE	(__OFF__)

/*
  Description: Multigraph support in editor & IME
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_MULTIGRAPH_SUPPORT	(__OFF__)

/*
  Description: to turn on Cstar pinyin phrase input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_INPUT_METHOD.doc
*/
#define CFG_MMI_CSTAR_PHRASE_INPUT	(__OFF__)

/*
  Description: qwerty vk type for IMEV3
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_INPUT_METHOD_IMEV3.doc
*/
#define CFG_MMI_IME_VK_TYPE_QWERTY	(__OFF__)

/*
  Description: Fuzzy Pinyin vk type for IMEV3
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_INPUT_METHOD_IMEV3.doc
*/
#define CFG_MMI_IME_FUZZY_PINYIN	(__OFF__)

/*
  Description: Alphanumeric vk type for IMEV3
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_INPUT_METHOD_IMEV3.doc
*/
#define CFG_MMI_IME_VK_TYPE_ALPHANUMERIC	(__ON__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_INPUT_METHOD.doc
*/
#define CFG_MMI_IME_MALDOVAN	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_IME_SLIM	(__ON__)

/*
  Description: memory card support for inputmethod
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_FONT&IME_MEMORYCARD.doc
*/
#define CFG_MMI_IME_MEMORY_CARD_SUPPORT	(__OFF__)

/*
  Description: memory card support for handwriting
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_FONT&IME_MEMORYCARD.doc
*/
#define CFG_MMI_HANDWRITING_MEMORY_CARD_SUPPORT	(__OFF__)

/*
  Description: BDF fonts from Guobi vendor
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_GUOBI_BDF_FONT	(__OFF__)

/*
  Description: auto capital
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MT6261-auto_capital-SLIM_Feature_Options.ppt
*/
#define CFG_MMI_IME_AUTO_CAPITALIZATION	(__OFF__)

/*****************************************************************************
* Language and Input Method
    * IME
        * Handwriting
*****************************************************************************/

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_ARABIC	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_BULGARIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_CROATIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_CZECH	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_DANISH	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_DUTCH	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_FINNISH	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_FRENCH	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_GERMAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_GREEK	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_HUNGARIAN	(__AUTO__)

/*
  Description: Guobi vendor integration for Indonesian handwriting
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_FRM_HANDWRITING.doc
*/
#define CFG_MMI_IME_HANDWRITING_INDONESIAN	(__OFF__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_ITALIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_LATVIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_LITHUANIAN	(__AUTO__)

/*
  Description: Guobi vendor integration for Malay handwriting
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_FRM_HANDWRITING.doc
*/
#define CFG_MMI_IME_HANDWRITING_MALAY	(__OFF__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_MALDOVAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_NORWEGIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_POLISH	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_PORTUGESE	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_ROMANIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_RUSSIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_SLOVAK	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_SM_CHINESE	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_SPANISH	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_SWEDISH	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_THAI	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_TR_CHINESE	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_TURKISH	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_UKRANIAN	(__AUTO__)

/*****************************************************************************
* Language and Input Method
    * IME
        * Handwriting(Vendor)
*****************************************************************************/

/*****************************************************************************
* Language and Input Method
    * IME
        * Input Method Management
*****************************************************************************/

/*
  Description: Smart mode for the Afrikaans language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_INPUT_METHOD.doc
*/
#define CFG_MMI_IME_AFRIKAANS	(__OFF__)

/*
  Description: Smart mode  for the Albanian language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_INPUT_METHOD.doc
*/
#define CFG_MMI_IME_ALBANIAN	(__OFF__)

/*
  Description: ARABIC input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_ARABIC	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_ASSAMESE	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_AZERBAIJANI	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_BASQUE	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_BENGALI	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_BULGARIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_CATALAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_CROATIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_CZECH	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_DANISH	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_DUTCH	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_ENGLISH	(__ON__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_ESTONIAN	(__AUTO__)

/*
  Description: Smart mode for the Filipino language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_INPUT_METHOD.doc
*/
#define CFG_MMI_IME_FILIPINO	(__OFF__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_FINNISH	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_FRENCH	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_GALICIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_GEORGIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_GERMAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_GREEK	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_GUJARATI	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_ESTONIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HANDWRITING_SLOVENIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HAUSA	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HEBREW	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HINDI	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HINGLISH	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HK_CHINESE	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_HUNGARIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_ICELANDIC	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_IGBO	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_INDONESIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_IRISH	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_ITALIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_KANNADA	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_KAZAKH	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_KHMER	(__AUTO__)

/*
  Description: Smart mode for the Lao language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_INPUT_METHOD.doc
*/
#define CFG_MMI_IME_LAO	(__OFF__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_LATVIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_LITHUANIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_MACEDONIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_MALAY	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_MALAYALAM	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_MARATHI	(__AUTO__)

/*
  Description: Smart mode for myanmar language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_INPUT_METHOD.doc
*/
#define CFG_MMI_IME_MYANMAR	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_NORWEGIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_ORIYA	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_PERSIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_POLISH	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_PORTUGUESE	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_PUNJABI	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_ROMANIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_RUSSIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_SERBIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_SESOTHO	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_SLOVAK	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_SLOVENIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_SM_CHINESE	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_SPANISH	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_SWAHILI	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_SWEDISH	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_TAGALOG	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_TAMIL	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_TELUGU	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_THAI	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_TR_CHINESE	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_TURKISH	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_UKRAINIAN	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_URDU	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_VIETNAMESE	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_XHOSA	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_YORUBA	(__AUTO__)

/*
  Description: input method
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_IME_ZULU	(__AUTO__)

/*****************************************************************************
* Language and Input Method
    * IME
        * Input Method UI
*****************************************************************************/

/*****************************************************************************
* Language and Input Method
    * IME
        * Multitap
*****************************************************************************/

/*****************************************************************************
* Language and Input Method
    * IME
        * Multitap(Vendor)
*****************************************************************************/

/*
  Description: Guobi multitap support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, DD_Input_Method_Keymap
*/
#define CFG_MMI_GUOBI_MULTITAP	(__OFF__)

/*****************************************************************************
* Language and Input Method
    * IME
        * Smart Input
*****************************************************************************/

/*****************************************************************************
* Language and Input Method
    * IME
        * Virtual Keyboard
*****************************************************************************/

/*
  Description: to turn on virtual keyboard in editors
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_VIRTUAL_KEYBOARD	(__ON__)

/*****************************************************************************
* Language and Input Method
    * Languages
        * Character Set
*****************************************************************************/

/*
  Description: Turn on Arabic ISO charset (ISO-8859-6)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_ARABIC_ISO	(__OFF__)

/*
  Description: Turn on Arabic WIN charset (Windows-1256)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_ARABIC_WIN	(__OFF__)

/*
  Description: to turn on Armenian  ISO10585 Character-set
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_ARMENIAN_ISO	(__AUTO__)

/*
  Description: Turn on Baltic ISO charset (ISO-8859-4)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_BALTIC_ISO	(__OFF__)

/*
  Description: Turn on Arabic WIN charset (Windows-1257)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_BALTIC_WIN	(__OFF__)

/*
  Description: Turn on traditional Chinese BIG5 charset
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_BIG5	(__OFF__)

/*
  Description: Turn on Centrual European ISO charset (ISO-8859-2)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_CEURO_ISO	(__OFF__)

/*
  Description: Turn on Centrual European WIN charset (Windows-1250)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_CEURO_WIN	(__OFF__)

/*
  Description: Turn ON ISO 8859-5 (cyrillic) character set support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_CYRILLIC_ISO	(__OFF__)

/*
  Description: Turn ON Win-1251 (cyrillic) character set support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_CYRILLIC_WIN	(__OFF__)

/*
  Description: Turn on Korean charset (EUC-KR [Korean])
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_EUCKR_WIN	(__OFF__)

/*
  Description: Turn on simple Chinese GB18030 charset
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_GB18030	(__OFF__)

/*
  Description: Turn on simple Chinese GB2312 charset
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_GB2312	(__OFF__)

/*
  Description: Turn on Greek ISO charset (ISO-8859-7)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_GREEK_ISO	(__OFF__)

/*
  Description: Turn on Greek WIN charset (Windows-1253)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_GREEK_WIN	(__OFF__)

/*
  Description: Turn on Hebrew ISO charset (ISO-8859-8)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_HEBREW_ISO	(__OFF__)

/*
  Description: Turn on Hebrew WIN charset (Windows-1255)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_HEBREW_WIN	(__OFF__)

/*
  Description: Turn ON HKSCS character set support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_HKSCS	(__OFF__)

/*
  Description: macro for KOI9-R encoding
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_KOI8_R	(__OFF__)

/*
  Description: Turn on Latin ISO charset
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_LATIN_ISO	(__OFF__)

/*
  Description: Turn on Nordic ISO charset
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_NORDIC_ISO	(__OFF__)

/*
  Description: Turn on Persian CP1097 charset
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_PERSIAN_CP1097	(__AUTO__)

/*
  Description: Turn on Persian CP1098 charset (PC)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_PERSIAN_CP1098	(__AUTO__)

/*
  Description: Turn on Sourth European ISO charset (ISO-8859-3)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_SEURO_ISO	(__OFF__)

/*
  Description: Turn on Thai WIN charset (Windows-874)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_THAI_WINDOWS	(__AUTO__)

/*
  Description: Turn ON TIS-620 character set support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_TIS_620	(__OFF__)

/*
  Description: Turn on Turkish ISO charset (ISO-8859-9)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_TURKISH_ISO	(__AUTO__)

/*
  Description: Turn on Turkish WIN charset (Windows-1254)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_TURKISH_WIN	(__AUTO__)

/*
  Description: Turn on UTF7 charset
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_UTF7	(__OFF__)

/*
  Description: Turn on Vietnamese WIN charset (Windows-1258)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_VIETNAMESE_WINDOWS	(__AUTO__)

/*
  Description: Turn on Western ISO charset (ISO-8859-1)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_WESTERN_ISO	(__AUTO__)

/*
  Description: Turn on Western WIN charset (Windows-1252)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_CHSET_WESTERN_WIN	(__ON__)

/*****************************************************************************
* Language and Input Method
    * Languages
        * IRE and BIDI
*****************************************************************************/

/*****************************************************************************
* Language and Input Method
    * Languages
        * Language Management
*****************************************************************************/

/*
  Description: to turn on Arabic language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_ARABIC	(__OFF__)

/*
  Description: For enabling Bengali language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: BengaliFontSpec, LanguageStatus.xls
*/
#define CFG_MMI_LANG_BENGALI	(__OFF__)

/*
  Description: to turn on Bulgarian language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_BULGARIAN	(__OFF__)

/*
  Description: Enable related charset according the language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Add_New_Charset_Conversion.doc
*/
#define CFG_MMI_LANG_CHSET_DEPENDENCE	(__AUTO__)

/*
  Description: to turn on Croatian language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_CROATIAN	(__OFF__)

/*
  Description: to turn on Czech language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_CZECH	(__OFF__)

/*
  Description: to turn on Danish language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_DANISH	(__OFF__)

/*
  Description: to turn on Dutch language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_DUTCH	(__OFF__)

/*
  Description: to turn on English language, English is default language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_ENGLISH	(__ON__)

/*
  Description: to turn on Finnish language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_FINNISH	(__OFF__)

/*
  Description: to turn on French language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_FRENCH	(__OFF__)

/*
  Description: to turn on German language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_GERMAN	(__OFF__)

/*
  Description: to turn on Greek language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_GREEK	(__OFF__)

/*
  Description: to turn on Hebrew Language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_HEBREW	(__OFF__)

/*
  Description: For enabling Hindi language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: HindiFontSpec, LanguageStatus.xls
*/
#define CFG_MMI_LANG_HINDI	(__OFF__)

/*
  Description: to turn on Hungarian language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_HUNGARIAN	(__OFF__)

/*
  Description: to turn on Indonesian language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_INDONESIAN	(__OFF__)

/*
  Description: to turn on Italic language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_ITALIAN	(__OFF__)

/*
  Description: to turn on Malay language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_MALAY	(__OFF__)

/*
  Description: For enabling Marathi language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: HindiFontSpec, LanguageStatus.xls
*/
#define CFG_MMI_LANG_MARATHI	(__OFF__)

/*
  Description: to turn on Norwegian language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_NORWEGIAN	(__OFF__)

/*
  Description: to turn on Persian language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_PERSIAN	(__OFF__)

/*
  Description: to turn on Polish language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_POLISH	(__OFF__)

/*
  Description: to turn on Portuguese language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_PORTUGUESE	(__OFF__)

/*
  Description: For enabling Punjabi language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: PunjabiFontSpec, LanguageStatus.xls
*/
#define CFG_MMI_LANG_PUNJABI	(__OFF__)

/*
  Description: to turn on Romanian language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_ROMANIAN	(__OFF__)

/*
  Description: to turn on Russian language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_RUSSIAN	(__OFF__)

/*
  Description: to turn on Slovak language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_SLOVAK	(__OFF__)

/*
  Description: to turn on Slovenian language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_SLOVENIAN	(__OFF__)

/*
  Description: to turn on Simpled Chinese language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_SM_CHINESE	(__OFF__)

/*
  Description: to turn on Spanish language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_SPANISH	(__OFF__)

/*
  Description: to turn on Swedish language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_SWEDISH	(__OFF__)

/*
  Description: For enabling Tamil language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: TamilFontSpec, LanguageStatus.xls
*/
#define CFG_MMI_LANG_TAMIL	(__OFF__)

/*
  Description: For enabling Telugu language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: TeluguFontSpec, LanguageStatus.xls
*/
#define CFG_MMI_LANG_TELUGU	(__OFF__)

/*
  Description: to turn on Thai language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_THAI	(__OFF__)

/*
  Description: to turn on Traditional Chinese language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_TR_CHINESE	(__OFF__)

/*
  Description: to turn on Turkish language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_TURKISH	(__OFF__)

/*
  Description: to turn on UKRAINIAN language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_UKRAINIAN	(__OFF__)

/*
  Description: to turn on Urdu language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_URDU	(__OFF__)

/*
  Description: to turn on Vietnamese language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus, SOP_Language_and_Input_Method_Porting_Guide_08A and DD_Font_And_Input_Method_Spec_for_Different_Languages
*/
#define CFG_MMI_LANG_VIETNAMESE	(__OFF__)

/*
  Description: to turn on Xhosa language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_Font_And_Input_Method_Spec_for_Different_Languages, SOP_Language_and_Input_Method_Porting_Guide, LanguageStatus, vendor relative document
*/
#define CFG_MMI_LANG_XHOSA	(__OFF__)

/*
  Description: to turn on Swahili language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_Font_And_Input_Method_Spec_for_Different_Languages, SOP_Language_and_Input_Method_Porting_Guide, LanguageStatus, vendor relative document
*/
#define CFG_MMI_LANG_SWAHILI	(__OFF__)

/*
  Description: to turn on Afrikaans language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_Font_And_Input_Method_Spec_for_Different_Languages, SOP_Language_and_Input_Method_Porting_Guide, LanguageStatus, vendor relative document
*/
#define CFG_MMI_LANG_AFRIKAANS	(__OFF__)

/*
  Description: to turn on Zulu  language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_Font_And_Input_Method_Spec_for_Different_Languages, SOP_Language_and_Input_Method_Porting_Guide, LanguageStatus, vendor relative document
*/
#define CFG_MMI_LANG_ZULU	(__OFF__)

/*
  Description: to turn on Lithuanian language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_Font_And_Input_Method_Spec_for_Different_Languages, SOP_Language_and_Input_Method_Porting_Guide, LanguageStatus, vendor relative document
*/
#define CFG_MMI_LANG_LITHUANIAN	(__OFF__)

/*
  Description: to turn on Latvian language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_Font_And_Input_Method_Spec_for_Different_Languages, SOP_Language_and_Input_Method_Porting_Guide, LanguageStatus, vendor relative document
*/
#define CFG_MMI_LANG_LATVIAN	(__OFF__)

/*
  Description: to turn on Estonian language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_Font_And_Input_Method_Spec_for_Different_Languages, SOP_Language_and_Input_Method_Porting_Guide, LanguageStatus, vendor relative document
*/
#define CFG_MMI_LANG_ESTONIAN	(__OFF__)

/*
  Description: to turn on Armenian language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_Font_And_Input_Method_Spec_for_Different_Languages, SOP_Language_and_Input_Method_Porting_Guide, LanguageStatus, vendor relative document
*/
#define CFG_MMI_LANG_ARMENIAN	(__OFF__)

/*
  Description: to turn on Georgian language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_Font_And_Input_Method_Spec_for_Different_Languages, SOP_Language_and_Input_Method_Porting_Guide, LanguageStatus, vendor relative document
*/
#define CFG_MMI_LANG_GEORGIAN	(__OFF__)

/*
  Description: to turn on Moldovan language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_Font_And_Input_Method_Spec_for_Different_Languages, SOP_Language_and_Input_Method_Porting_Guide, LanguageStatus, vendor relative document
*/
#define CFG_MMI_LANG_MOLDOVAN	(__OFF__)

/*
  Description: For enabling Oriya language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: OriyaFontSpec, LanguageStatus.xls
*/
#define CFG_MMI_LANG_ORIYA	(__OFF__)

/*
  Description: For enabling Kannada language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: KannadaFontSpec, LanguageStatus.xls
*/
#define CFG_MMI_LANG_KANNADA	(__OFF__)

/*
  Description: For enabling Malayalam language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MalayalamFontSpec, LanguageStatus.xls
*/
#define CFG_MMI_LANG_MALAYALAM	(__OFF__)

/*
  Description: Albanian Language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_ALBANIAN	(__OFF__)

/*
  Description: For enabling Assamese language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: BengaliFontSpec, LanguageStatus.xls
*/
#define CFG_MMI_LANG_ASSAMESE	(__OFF__)

/*
  Description: For enabling Gujarati language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: GujaratiFontSpec, LanguageStatus.xls
*/
#define CFG_MMI_LANG_GUJARATI	(__OFF__)

/*
  Description: For enabling language Azerbaijani
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_AZERBAIJANI	(__OFF__)

/*
  Description: For enabling language Catalan
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_CATALAN	(__OFF__)

/*
  Description: For enabling language hausa
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_HAUSA	(__OFF__)

/*
  Description: For enabling language Icelandic
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_ICELANDIC	(__OFF__)

/*
  Description: For enabling language Kazakh
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_KAZAKH	(__OFF__)

/*
  Description: For enabling language Macedonian
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_MACEDONIAN	(__OFF__)

/*
  Description: For enabling language Serbian
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_SERBIAN	(__OFF__)

/*
  Description: For enabling language Sesotho
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_SESOTHO	(__OFF__)

/*
  Description: For enabling language Tagalog
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_TAGALOG	(__OFF__)

/*
  Description: For enabling language Yoruba
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_YORUBA	(__OFF__)

/*
  Description: For enabling language SA portuguese
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_SA_PORTUGUESE	(__OFF__)

/*
  Description: For enabling language Canadian French
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_CA_FRENCH	(__OFF__)

/*
  Description: For enabling language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_HK_CHINESE	(__OFF__)

/*
  Description: For enabling language Sa Spanish
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_SA_SPANISH	(__OFF__)

/*
  Description: For enabling language UK English
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_UK_ENGLISH	(__OFF__)

/*
  Description: For enabling language igbo
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_IGBO	(__OFF__)

/*
  Description: For enabling language Basque
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_BASQUE	(__OFF__)

/*
  Description: For enabling language Galician
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_GALICIAN	(__OFF__)

/*
  Description: For enabling language Filipino
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_FILIPINO	(__OFF__)

/*
  Description: For enabling language Irish
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_IRISH	(__OFF__)

/*
  Description: To turn on Khmer languge
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_KHMER	(__OFF__)

/*
  Description: To turn on Myanmar language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_MYANMAR	(__OFF__)

/*
  Description: To turn on Zawgyi Myanmar language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_ZAWGYI_MYANMAR	(__OFF__)

/*
  Description: To turn on Lao language
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LanguageStatus.xls
*/
#define CFG_MMI_LANG_LAO	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_IRE_SLIM	(__OFF__)

/*
  Description: Bangla government specs for keymap
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_MULTITAP_BANGLA_SPEC	(__OFF__)

/*****************************************************************************
* Launcher
    * Home Screen
        * Launcher Style
*****************************************************************************/

/*
  Description: Define this compile option to enable the Cosmos launcher.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_COSMOS_LAUNCHER.pptx
*/
#define CFG_MMI_VUI_LAUNCHER_COSMOS	(__AUTO__)

/*
  Description: When this option is on, we add the memory concurrency for launcher, java and video. In this case, we guarantee the launcher, background java and video wallpaper can run concurrently. Otherwise, if this option is off, the handset might not have enough memory for video wallpaper. When it happens, video wallpaper will only display the first frame of the video
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_LAUNCHER.pptx
*/
#define CFG_MMI_VUI_LAUNCHER_JAVA_VIDEO_CONCURRENCY	(__OFF__)

/*
  Description: Enable a new launcher named key launcher which can support full key/full touch operations, this launcher has components of Homescreen, Main menu and some widgets.1. if want to turn off some widget, please add CFG_xx to each widget's compile options.2. we support launcher dynamic switch feature now. They are some other laucnhers named FTE Launcher and ShellApp, Key luancher has no dependency with these two old launchers, customer can turn on Key launcher and FTE Launcher at the same time now, if so, they is a luancher dynamic switch setting entry in General Setting AP. to turn on FTE launcher, please set CFG_MMI_VUI_HOMESCREEN_TYPE_SEL = HOMESCREEN_VUI_LAUNCHER and CFG_MMI_VUI_MAINMENU_TYPE_SEL = MAINMENU_VUI_LAUNCHER.3. we don't SQC the ShellApp + Key launcher and leave it for customers' customizations even they can be turned on now, customer may need to SQC it by themselves.4. if want to save code size, please do remember to only turn on one of the launcher and turn off others.5. of course, if customer want to support Key launcher + FTE Launcher + ShellApp dynamic switch, they need to redefined the compile options of CFG_MMI_VUI_HOMESCREEN_TYPE_SEL and CFG_MMI_VUI_MAINMENU_TYPE_SEL and all the related dependencys.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_KEY_LAUNCHER_HOME.ppt
*/
#define CFG_MMI_VUI_LAUNCHER_KEY	(__AUTO__)

/*
  Description: Define this compile option to enable the main menu launcher.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_MM_LAUNCHER.pptx
*/
#define CFG_MMI_VUI_LAUNCHER_MM	(__OFF__)

/*
  Description: This option turns on the MRE downloadable launcher.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_DLUI_LAUNCHER.pptx
*/
#define CFG_MMI_VUI_LAUNCHER_MRE	(__OFF__)

/*
  Description: Define this comiple option to enable the robot launcher.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_ROBOT_LAUNCHER.pptx
*/
#define CFG_MMI_VUI_LAUNCHER_ROBOT	(__OFF__)

/*****************************************************************************
* Launcher
    * Home Screen
        * Screen Lock(Cosmos)
*****************************************************************************/

/*
  Description: MRE Launcher uses ASM
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_LAUNCHER.doc
*/
#define CFG_MMI_VUI_LAUNCHER_MRE_USE_ASM	(__OFF__)

/*
  Description: Define this compile option to enable the Cosmos screen lock.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_COSMOS_SCREEN_LOCK.pptx
*/
#define CFG_MMI_VUI_SCREEN_LOCK_COSMOS	(__AUTO__)

/*
  Description: MRE Screen Lock  uses ASM
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_SCREEN_LOCK.doc
*/
#define CFG_MMI_VUI_SCREEN_LOCK_MRE_USE_ASM	(__OFF__)

/*
  Description: Define the compile option to enable the painting screen lock.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_PAINTING_SCREEN_LOCK.pptx
*/
#define CFG_MMI_VUI_SCREEN_LOCK_PAINTING	(__OFF__)

/*
  Description: Define this compile opiton to enable the pattern screen lock.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_PATTERN_SCREEN_LOCK.pptx
*/
#define CFG_MMI_VUI_SCREEN_LOCK_PATTERN	(__OFF__)

/*
  Description: Screen lock rhythm
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_SCREENLOCK.ppt
*/
#define CFG_MMI_VUI_SCREEN_LOCK_RHYTHM	(__OFF__)

/*
  Description: Define this compile option to enable the steam screen lock.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_STEAM_SCREEN_LOCK.pptx
*/
#define CFG_MMI_VUI_SCREEN_LOCK_STEAM	(__AUTO__)

/*
  Description: Define the compile option to enable the zipper screen lock.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_ZIPPER_SCREEN_LOCK.pptx
*/
#define CFG_MMI_VUI_SCREEN_LOCK_ZIPPER	(__OFF__)

/*
  Description: Enable a fancy screen locker with long press style which is only supported on touch-enable projects.More details about to save code size or support locker dynamic switch feature,  please refer to the description of _MMI_VUI_SHELL_SCREEN_LOCK.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Venus_UI_Customization.doc
*/
#define CFG_MMI_VUI_SHELL_SCREEN_LOCK	(__AUTO__)

/*****************************************************************************
* Launcher
    * Home Screen
        * Screen Lock(Pluto)
*****************************************************************************/

/*
  Description: Enable auto keypad menu to configure the timeout value
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_SECURITYSETUP.doc
*/
#define CFG_MMI_AUTO_KEYPAD_LOCK	(__AUTO__)

/*
  Description: Enable a new fancy screen locker which can support full key and full touch operations.  Please note, 1. There is another old fancy screen locker which is only supported on touch-enable projects and controlled by CFG_MMI_VUI_SHELL_SCREEN_LOCK. 2. There are no dependency between these two locker now, they both can be turned on at the same time, but only this key locker can be seen because it has some higher priorty than the other.3.  customers can add locker dynamic switch setting in Setting AP to let end user select which locker can be used on touch enable projects, the code of setting can refer to "Launcher dynamic switch".4. if don't need this lock dynamic switch feature or want to save code size, please do remember to only turn on one of them to save code size.5. If both of them are turne off, the classic screen locker with poup style is used, customer can decide if need to turn of screen saver (CFG_MMI_SCREEN_SAVER)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_SCREEN_LOCK_KEY.PPT
*/
#define CFG_MMI_VUI_SCREEN_LOCK_KEY	(__AUTO__)

/*****************************************************************************
* Launcher
    * Home Screen
        * Screen Saver(Pluto)
*****************************************************************************/

/*
  Description: When clasm open, stop screen saver.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_DEVICEINTERFACE.doc
*/
#define CFG_MMI_CLAMOPEN_STOP_SCRSAVER	(__OFF__)

/*
  Description: add compile option on screen saver
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: PRST_APP_IDLE_06B_09B.ppt
*/
#define CFG_MMI_SCREEN_SAVER	(__OFF__)

/*****************************************************************************
* Launcher
    * Home Screen
        * Wall Paper(Cosmos)
*****************************************************************************/

/*
  Description: enable or disable Intergrafx's live wallpaper and games
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Intergrafx_Livewallpaper_and_Game.docx
*/
#define CFG_MMI_VUI_HOMESCREEN_IG_LIVE_WALLPAPER_CLOCK	(__OFF__)

/*
  Description: enable or disable Intergrafx's live wallpaper and games
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Intergrafx_Livewallpaper_and_Game.docx
*/
#define CFG_MMI_VUI_HOMESCREEN_IG_LIVE_WALLPAPER_DAYDREAM	(__OFF__)

/*
  Description: enable or disable Intergrafx's live wallpaper and games
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Intergrafx_Livewallpaper_and_Game.docx
*/
#define CFG_MMI_VUI_HOMESCREEN_IG_LIVE_WALLPAPER_FISH	(__OFF__)

/*
  Description: enable or disable Intergrafx's live wallpaper and games
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Intergrafx_Livewallpaper_and_Game.docx
*/
#define CFG_MMI_VUI_HOMESCREEN_IG_LIVE_WALLPAPER_GIRL	(__OFF__)

/*
  Description: enable or disable Intergrafx's live wallpaper and games
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Intergrafx_Livewallpaper_and_Game.docx
*/
#define CFG_MMI_VUI_HOMESCREEN_IG_LIVE_WALLPAPER_HORSE	(__OFF__)

/*
  Description: enable or disable Intergrafx's live wallpaper and games
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Intergrafx_Livewallpaper_and_Game.docx
*/
#define CFG_MMI_VUI_HOMESCREEN_IG_LIVE_WALLPAPER_LIGHTHOUSE	(__OFF__)

/*
  Description: enable or disable Intergrafx's live wallpaper and games
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Intergrafx_Livewallpaper_and_Game.docx
*/
#define CFG_MMI_VUI_HOMESCREEN_IG_LIVE_WALLPAPER_MIMOSA	(__OFF__)

/*
  Description: enable or disable Intergrafx's live wallpaper and games
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Intergrafx_Livewallpaper_and_Game.docx
*/
#define CFG_MMI_VUI_HOMESCREEN_IG_LIVE_WALLPAPER_PUPPY	(__OFF__)

/*
  Description: enable or disable Intergrafx's live wallpaper and games
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Intergrafx_Livewallpaper_and_Game.docx
*/
#define CFG_MMI_VUI_HOMESCREEN_IG_LIVE_WALLPAPER_SOLAR	(__OFF__)

/*
  Description: enable or disable Intergrafx's live wallpaper and games
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Intergrafx_Livewallpaper_and_Game.docx
*/
#define CFG_MMI_VUI_HOMESCREEN_IG_LIVE_WALLPAPER_TRANSFORMER	(__OFF__)

/*
  Description: Live wallpaper which can interaction with user
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: HLD_VHS_LIVEWALLPAPER.ppt
*/
#define CFG_MMI_VUI_HOMESCREEN_LIVE_WALLPAPER	(__OFF__)

/*
  Description: 3d live wallpaper cassia
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Sakura_3D_description.pptx
*/
#define CFG_MMI_VUI_HOMESCREEN_LIVE_WALLPAPER_3D_CASSIA	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_WALLPAPER_3D_EARTH.pptx
*/
#define CFG_MMI_VUI_HOMESCREEN_LIVE_WALLPAPER_3D_EARTH	(__OFF__)

/*
  Description: 3d live wallpaper maple
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Sakura_3D_description.pptx
*/
#define CFG_MMI_VUI_HOMESCREEN_LIVE_WALLPAPER_3D_MAPLE	(__OFF__)

/*
  Description: Enable 3D Sakura live wallpaper
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Sakura_3D_description.pptx
*/
#define CFG_MMI_VUI_HOMESCREEN_LIVE_WALLPAPER_3D_SAKURA	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_WALLPAPER_3D_WAVE.pptx
*/
#define CFG_MMI_VUI_HOMESCREEN_LIVE_WALLPAPER_3D_WAVE	(__OFF__)

/*
  Description: Chipset wallpaper
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: HLD_VHS_LIVEWALLPAPER.ppt
*/
#define CFG_MMI_VUI_HOMESCREEN_LIVE_WALLPAPER_CHIPSET	(__OFF__)

/*
  Description: Comet wallpaper
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: HLD_VHS_LIVEWALLPAPER.ppt
*/
#define CFG_MMI_VUI_HOMESCREEN_LIVE_WALLPAPER_COMET	(__OFF__)

/*
  Description: Firfly wallpaper
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: HLD_VHS_LIVEWALLPAPER.ppt
*/
#define CFG_MMI_VUI_HOMESCREEN_LIVE_WALLPAPER_FIREFLY	(__OFF__)

/*
  Description: Interactive Video Live Wallpaper
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_VUI_HOMESCREEN_LIVE_WALLPAPER_INTERACTIVE_VIDEO	(__AUTO__)

/*
  Description: Matrix wallpaper
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: HLD_VHS_LIVEWALLPAPER.ppt
*/
#define CFG_MMI_VUI_HOMESCREEN_LIVE_WALLPAPER_MATRIX	(__OFF__)

/*
  Description: MAV wallpaper support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MAV_description.pptx
*/
#define CFG_MMI_VUI_HOMESCREEN_LIVE_WALLPAPER_MAV	(__OFF__)

/*
  Description: This is MMI CFG option for "Sakura 2D" Live wallpaper
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: LW_Sakura 2D_guide.pptx
*/
#define CFG_MMI_VUI_HOMESCREEN_LIVE_WALLPAPER_SAKURA	(__OFF__)

/*
  Description: Space wallpaper
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: HLD_VHS_LIVEWALLPAPER.ppt
*/
#define CFG_MMI_VUI_HOMESCREEN_LIVE_WALLPAPER_SPACE	(__OFF__)

/*
  Description: Spangle wallpaper
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: HLD_VHS_LIVEWALLPAPER.ppt
*/
#define CFG_MMI_VUI_HOMESCREEN_LIVE_WALLPAPER_SPANGLE	(__OFF__)

/*
  Description: Wave reflection wallpaper
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: HLD_VHS_LIVEWALLPAPER.ppt
*/
#define CFG_MMI_VUI_HOMESCREEN_LIVE_WALLPAPER_WAVE	(__OFF__)

/*
  Description: Wildworld wallpaper
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: HLD_VHS_LIVEWALLPAPER.ppt
*/
#define CFG_MMI_VUI_HOMESCREEN_LIVE_WALLPAPER_WILDWORLD	(__OFF__)

/*
  Description: __MMI_VUI_HOMESCREEN_VIDEO_WALLPAPER__
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_VUI_HOMESCREEN_VIDEO_WALLPAPER	(__AUTO__)

/*
  Description: This option turns on the MRE downloadable screen lock.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_DLUI_SCREEN_LOCK.pptx
*/
#define CFG_MMI_VUI_SCREEN_LOCK_MRE	(__OFF__)

/*
  Description: Download UI Wallpaper
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: VendorTraining_Helloworld_App_Introduction.pptx
*/
#define CFG_MMI_VUI_WALLPAPER_MRE	(__OFF__)

/*****************************************************************************
* Launcher
    * Home Screen
        * Wall Paper(Pluto)
*****************************************************************************/

/*****************************************************************************
* Launcher
    * Home Screen
        * Widget(Pluto)
*****************************************************************************/

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_Venus_UI_Customization.doc
*/
#define CFG_MMI_VUI_LAUNCHER	(__AUTO__)

/*****************************************************************************
* Launcher
    * Home Screen
        * Widget Framework(Cosmos)
*****************************************************************************/

/*
  Description: This option is used to turn on the home screen switch effect.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_HOMESCREEN.docx
*/
#define CFG_MMI_VUI_HOME_SCREEN_SWITCH_EFFECT	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: HLD_COSMOS3D_WIDGET_CLOCK.pptx
*/
#define CFG_MMI_VUI_WIDGET_3D_CLOCK	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: HLD_COSMOS3D_WIDGET_MUSICPLAYER.pptx
*/
#define CFG_MMI_VUI_WIDGET_3D_MUSIC_PLAYER	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_COSMOS3D_WIDGET_PET.pptx
*/
#define CFG_MMI_VUI_WIDGET_3D_PET	(__OFF__)

/*
  Description: baidu search widget
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_COSMOS_WIDGET_BAIDU_SEARCH.pptx
*/
#define CFG_MMI_VUI_WIDGET_BAIDU_SEARCH	(__OFF__)

/*
  Description: Calendar widget
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_COSMOS_WIDGET_CALENDAR.pptx
*/
#define CFG_MMI_VUI_WIDGET_CALENDAR	(__OFF__)

/*
  Description: Clock widget
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_COSMOS_WIDGET_CLOCK1.pptx
*/
#define CFG_MMI_VUI_WIDGET_CLOCK1	(__OFF__)

/*
  Description: Clock widget
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_COSMOS_WIDGET_CLOCK2.pptx
*/
#define CFG_MMI_VUI_WIDGET_CLOCK2	(__OFF__)

/*
  Description: Clock widget
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_COSMOS_WIDGET_CLOCK3.pptx
*/
#define CFG_MMI_VUI_WIDGET_CLOCK3	(__OFF__)

/*
  Description: Clock widget
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_COSMOS_WIDGET_CLOCK4.pptx
*/
#define CFG_MMI_VUI_WIDGET_CLOCK4	(__OFF__)

/*
  Description: Digital Clock widget
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_COSMOS_WIDGET_DCLOCK.pptx
*/
#define CFG_MMI_VUI_WIDGET_DCLOCK	(__OFF__)

/*
  Description: This option is used to turn on the flip clock widget.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_HOMESCREEN.docx
*/
#define CFG_MMI_VUI_WIDGET_FLIP_CLOCK	(__OFF__)

/*
  Description: FM radio widget
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_COSMOS_WIDGET_FM_RADIO.pptx
*/
#define CFG_MMI_VUI_WIDGET_FM_RADIO	(__OFF__)

/*
  Description: Gallery Widget
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_COSMOS_WIDGET_GALLERY.pptx
*/
#define CFG_MMI_VUI_WIDGET_GALLERY	(__OFF__)

/*
  Description: Google search bar widget
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_COSMOS_WIDGET_GOOGLE.pptx
*/
#define CFG_MMI_VUI_WIDGET_GOOGLE	(__OFF__)

/*
  Description: This option turns on the MRE downloadable widget.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_DLUI_WIDGET.pptx
*/
#define CFG_MMI_VUI_WIDGET_MRE	(__OFF__)

/*
  Description: music player widget
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_COSMOS_WIDGET_MUSIC_PLAYER.pptx
*/
#define CFG_MMI_VUI_WIDGET_MUSIC_PLAYER	(__OFF__)

/*
  Description: quick switch widget provide easy way for users to switch some functions, such as wifi or profile mode..etc.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_COSMOS_WIDGET_QUICK_SWITCH.pptx
*/
#define CFG_MMI_VUI_WIDGET_QUICK_SWITCH	(__OFF__)

/*
  Description: SNS widget
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_COSMOS_WIDGET_SNS_STICKY.pptx
*/
#define CFG_MMI_VUI_WIDGET_SNS_STICKY	(__OFF__)

/*
  Description: SNS widget
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_COSMOS_WIDGET_SNS_TABBAR.pptx
*/
#define CFG_MMI_VUI_WIDGET_SNS_TABBAR	(__OFF__)

/*
  Description: VIP Contact widget
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_COSMOS_WIDGET_VIP_CONTACT.pptx
*/
#define CFG_MMI_VUI_WIDGET_VIP_CONTACT	(__OFF__)

/*****************************************************************************
* Launcher
    * Main Menu
*****************************************************************************/

/*
  Description: Define the compile option to enable the downloadable app icon.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_DOWNLOADABLE_APP_ICON.pptx
*/
#define CFG_MMI_VUI_DOWNLOADABLE_APP_ICON	(__OFF__)

/*
  Description: Define the compile option to enable the main menu switch effect.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_MAIN_MENU_SWITCH_EFFECT.pptx
*/
#define CFG_MMI_VUI_MAIN_MENU_SWITCH_EFFECT	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Cosmos_Downloadable_Theme_AppIcon_Promotion.pptx
*/
#define CFG_MMI_VUI_APP_ICON_ROBOT	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Cosmos_Downloadable_Theme_AppIcon_Promotion.pptx
*/
#define CFG_MMI_VUI_APP_ICON_MM	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_LAUNCHER_APP_LIST_INTERACTIVE_VIDEO_WALLPAPER	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_APPLIST_BARREL_SUPPORT	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_LAUNCHER_APP_LIST	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_LAUNCHER_APP_LIST_VIDEO_WALLPAPER	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_DOWNLOADABLE_APP_ICON_FW_SUPPORT	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_APP_ICON_FW_SUPPORT	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_APPLIST_KEY_SUPPORT	(__OFF__)

/*****************************************************************************
* Launcher
    * Main Menu
        * Download UI(Cosmos)
*****************************************************************************/

/*****************************************************************************
* Messaging
    * Email
*****************************************************************************/

/*****************************************************************************
* Messaging
    * Email
        * Email(Pluto)
*****************************************************************************/

/*
  Description: support extract HTML content in Email
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_EMAIL.doc
*/
#define CFG_MMI_EMAIL_HTML	(__OFF__)

/*
  Description: To support the IMAP IDLE Push Mail in Email.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FTO_UE_Spec_Email_V1.1.vsd
*/
#define CFG_MMI_EMAIL_IMAP_PUSH	(__OFF__)

/*
  Description: If an outbox is provided for off line composition/sending, its content shall also be transmitted during the synchronization
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_EMAIL.doc
*/
#define CFG_MMI_EMAIL_SEND_BEFORE_SYNC	(__AUTO__)

/*****************************************************************************
* Messaging
    * Email
        * Email(Service)
*****************************************************************************/

/*****************************************************************************
* Messaging
    * MMS
*****************************************************************************/

/*
  Description: add compile option for MMS BGSR to block user cancel a downloading message
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_MMS_APP_09A_latest.doc
*/
#define CFG_MMI_MMS_BGSR_CANCEL_PROHIBIT	(__OFF__)

/*
  Description: Calculate MMS message size by user inserted elements
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_MMS_VIEWER_09A_latest.doc
*/
#define CFG_MMI_MMS_CALC_MSG_SIZE_BY_USER_ELEMENTS	(__OFF__)

/*
  Description: not allow user to download a corrupted MMS message again
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_MMS_APP_09A_latest.doc
*/
#define CFG_MMI_MMS_NOT_ALLOW_USER_DOWNLOAD_CORRUPTED_MMS_MSG	(__OFF__)

/*
  Description: Allow MMS Slide Manual Play
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_MMS_VIEWER_09A_latest.doc
*/
#define CFG_MMI_MMS2_MV_MANUAL_PLAY	(__OFF__)

/*
  Description: Support Landscape mode in MMS2
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_MMS_VIEWER_09A_latest.doc
*/
#define CFG_MMI_MV_SUPPORT_LANDSCAPE_MODE	(__OFF__)

/*
  Description: to support ref id tag in MMS2
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_MMS_VIEWER_09A_latest.doc
*/
#define CFG_MMI_MV_SUPPORT_REF_ID	(__OFF__)

/*
  Description: to turn on validity period in setting
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_MMS_APP_09A_latest.doc
*/
#define CFG_MMI_MMS_SETTINGS_VALIDITY_PERIOD_VISIBILITY	(__OFF__)

/*
  Description: Allow user to change the read status of MMS message.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_MMS_VIEWER_09A_latest.doc
*/
#define CFG_MMI_MMS_SWITCH_MSG_READ_STATUS	(__OFF__)

/*
  Description: To allow 300kb message size in WAP connection
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_MMS_APP_09A_latest.doc
*/
#define CFG_MMI_MMS_WAP_CONNECTION_MAX_SIZE_SUPPORT	(__OFF__)

/*
  Description: To Disable image functionality from signature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_MMS_APP_09A_latest.doc
*/
#define CFG_MMI_MMS_UMMS_IMAGE_FEATURE	(__OFF__)

/*
  Description: To Disable audio functionality from signature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_MMS_APP_09A_latest.doc
*/
#define CFG_MMI_MMS_UMMS_AUDIO_FEATURE	(__OFF__)

/*
  Description: To Disable video functionality from signature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_MMS_APP_09A_latest.doc
*/
#define CFG_MMI_MMS_UMMS_VIDEO_FEATURE	(__OFF__)

/*
  Description: To turn on best page feature in MMS viewer and composer
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_MMS_VIEWER_09A_latest.doc
*/
#define CFG_MMI_MMS_BEST_PAGE_SUPPORT	(__OFF__)

/*
  Description: To support unlimited use detail
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_MMS_VIEWER_09A_latest.doc
*/
#define CFG_MMI_MMS_UNLIMITED_USE_DETAILS_SUPPORT	(__OFF__)

/*
  Description: To turn on/off mms-v02 templates
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_MMS_APP_09A_latest.doc, (http://dcc.mediatek.inc/WebAgenda/ViewDocument/DocKey_0000076218)
*/
#define CFG_MMI_MMS_V02_TEMPLATES_SUPPORT	(__OFF__)

/*
  Description: Encode Forward-Lock/Combine-Delivery object in MMS to DCF format
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_MMS_VIEWER_09A_latest.doc
*/
#define CFG_MMI_MMS_MMA_DRM_ENCODING	(__OFF__)

/*
  Description: When this feature option is turned ON, MMS sending will be instantly retried if error occurred during connection establishment or failed inbetween sending. This retry is hidden from user and is independent of the normal retry policy.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_SRV_UMMS_10A_latest.doc
*/
#define CFG_MMI_WAP_MMS_SEND_INSTANT_RETRY	(__OFF__)

/*
  Description: When this feature option is turned,User can send the MMS after preview
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_MMS_VIEWER_09A_latest.doc
*/
#define CFG_MMI_UMMS_PREVIEW_SEND	(__OFF__)

/*
  Description: When this feature option is turned, MMS will not reject the MMS notification when the message size it specified is more thatn max mms message we can support.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_UMMS_10A_latest.doc
*/
#define CFG_MMI_WAP_MMS_NO_REJECT_NOTIFICATION_BY_SIZE	(__OFF__)

/*
  Description: Message UE Enhancement
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: UE_Enhancement_For_Composer_And_Viewer.ppt, FRS_APP_UNIFIEDCOMPOSER.doc
*/
#define CFG_MMI_MSG_FTE_ENHANCE	(__OFF__)

/*
  Description: Show Sent/Received Icon in MMS Viewer Contact Bar
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_COSMOS_MMS_VIEWER_CONTACT_BAR_STATUS_ICON	(__OFF__)

/*
  Description: Enhanced, high resolution image view expeirence in MMS Viewer and Unified Composer.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: TR ID TSSQA00312997
*/
#define CFG_MMI_MMS_IMAGE_VIEW_ENHANCEMENT	(__OFF__)

/*
  Description: Support attachment file add/Delete in Low Tier MMS Solutions
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_UMMS_11A_latest.doc
*/
#define CFG_MMI_MMS_LT_NO_ATTACHMENT_SUPPORT	(__ON__)

/*
  Description: Support a low tier background send /receive functions for MMS
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_UMMS_11A_latest.doc
*/
#define CFG_MMI_MMS_LOW_TIER_BGSR_SUPPORT	(__ON__)

/*
  Description: Support Audio file add/Delete in Low Tier MMS Solutions
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_UMMS_11A_latest.doc
*/
#define CFG_MMI_MMS_LT_NO_AUDIO_SUPPORT	(__ON__)

/*
  Description: MMS setting new config for 4 solution
  Option: [MMS_SETTING_AUTO, MMS_SETTING_FULL, MMS_SETTING_OMA_ONLY, MMS_SETTING_NONE]
  Reference: DD_VAPP_MMS_11B(SLIM).pptx
*/
#define CFG_MMI_MMS_SETTING_SEL	(MMS_SETTING_AUTO)

/*
  Description: Three features will be disabled for 61 slim
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MT6261-mms-SLIM_Feature_Options.ppt
*/
#define CFG_MMI_MMS_FOR_6261_SLIM	(__ON__)

/*
  Description: This CFG is used to enable MMS IOT Testing when it is necessary and DT_SUPPORT is false.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_MMS_IOT_TEST_SUPPORT	(__OFF__)

/*****************************************************************************
* Messaging
    * Provisioning
*****************************************************************************/

/*
  Description: to turn on SMS bootstrap feature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SAP_CCA.doc
*/
#define CFG_MMI_CCA_OMACP_BOOTSTRAP_UPDATE_SUPPORT	(__OFF__)

/*
  Description: This compile option is for Provisioning Inbox to support UM box. To turn on this option, Provisioning can be listed in UM inbox and archive.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_ProvBoxUI.doc
*/
#define CFG_MMI_PROV_IN_UM	(__OFF__)

/*
  Description: This compile option is for Provisioning Inbox . Turn on this option, Provisioning Inbox is open and provisioniings can be saved and listed in settings message box.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_ProvBoxUI.doc
*/
#define CFG_MMI_PROV_MESSAGE_SUPPORT	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_CCA_SUPPORT	(__OFF__)

/*****************************************************************************
* Messaging
    * Provisioning
        * Streaming Provisioning
*****************************************************************************/

/*****************************************************************************
* Messaging
    * SMS
*****************************************************************************/

/*
  Description: Support DM Self-Register; It allow to send a register SMS to a specific server when power on. If the server give a positve confirm with a SMS for the register information, it don't send the register SMS again to the server when power on, otherwise, it will send again.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DM_CMCC_Customization_Guide.doc
*/
#define CFG_MMI_DM_SELF_REGISTER_SUPPORT	(__OFF__)

/*
  Description: CB Immediate Message Display In The Idle Screen, the CB message content is showed in the Idle screen, different with the design that popup an indication screen to show the content.If don't support two mode CB display (__MMI_MESSAGES_TWO_CB_MODES_DISPLAY__), when turn on this compile option, the all mode CB message is showed in the idle screen; If support two mode CB display, when turn on this compile option, the immediate CB message is showed in the idle screen, the normal mode CB message is diplay with a popup screen.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_CELLBROADCAST.doc
*/
#define CFG_MMI_MESSAGES_CB_DISPLAY_IN_IDLE	(__OFF__)

/*
  Description: SMS COPY and MOVE function
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SOP_APP_SMS_COPY.doc
*/
#define CFG_MMI_MESSAGES_COPY	(__OFF__)

/*
  Description: SMS Remaining Count Display in EMS Editor information bar
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_EMS
*/
#define CFG_MMI_MESSAGES_EMS_REMAINING_COUNTER	(__OFF__)

/*
  Description: Support immediate mode and normal mode cb display, different mode CB message have different behavior.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_CELLBROADCAST.doc
*/
#define CFG_MMI_MESSAGES_TWO_CB_MODES_DISPLAY	(__OFF__)

/*
  Description: Long SMS support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_SMS
*/
#define CFG_EMS_DYNAMIC_SEG_NUM	(__OFF__)

/*
  Description: Allow user to change the read status of SMS message.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_SMS
*/
#define CFG_MMI_SMS_SWITCH_MSG_READ_STATUS	(__OFF__)

/*
  Description: To enable inline hint with list item in message main menu.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_SMS
*/
#define CFG_MMI_MESSAGE_MAIN_MENU_HINT_INLINE	(__OFF__)

/*
  Description: to enable SMS list advanced option authorization mechanism
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_SMS
*/
#define CFG_MMI_MESSAGES_LIST_ADVANCED	(__OFF__)

/*
  Description: Add cmpile option for sms high light viewer feature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_SMS
*/
#define CFG_MMI_MESSAGE_SMS_HILITE_VIEWER	(__OFF__)

/*
  Description: Add SMS content to Calendar
  Option: [__ON__, __AUTO__, __OFF__]
  Reference: MMI_UE_Specification_Add_to_Calendar.vsd
*/
#define CFG_MMI_SMS_SET_AS_REMINDER	(__OFF__)

/*
  Description: Add compile option for SMS detailsIF open SMS email interworking feature,  SMS details will not support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MMI_UE_specication_SMS_details.vsd
*/
#define CFG_MMI_SMS_DETAILS_INFO	(__ON__)

/*
  Description: SMS editor with recipient
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_SMS_Number_Content_Same_Scrn.vsd
*/
#define CFG_MMI_MSG_EDITOR_WITH_RECIPIENT	(__OFF__)

/*
  Description: SLIM common option for SMS
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: provide after 44MP
*/
#define CFG_MMI_SMS_SLIM	(__ON__)

/*
  Description: Support SMS storage only in SIM(Thus Preferred Storage can be removed), 10.No Memory Status is shown
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_SMS
*/
#define CFG_MMI_MESSAGES_PREFER_STORAGE_MEMORY_STATUS	(__OFF__)

/*
  Description: SMS predefined template
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_SMS
*/
#define CFG_MMI_MESSAGES_PREDEFINED_TEMPLATE	(__OFF__)

/*
  Description: SMS user defined template
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_SMS
*/
#define CFG_MMI_MESSAGES_USERDEFINED_TEMPLATE	(__OFF__)

/*
  Description: ADD CFG for Broadcast message
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_CELLBROADCAST.doc
*/
#define CFG_MMI_CBS_SUPPORT	(__OFF__)

/*
  Description: SMS support memory card storage
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: TSSQA00210669
*/
#define CFG_MMI_SMS_TCARD_STORAGE_SUPPORT	(__OFF__)

/*****************************************************************************
* Messaging
    * SMS
        * SMS(Service)
*****************************************************************************/

/*****************************************************************************
* Messaging
    * Unified Composer
*****************************************************************************/

/*
  Description: subject character counting rule -- chinese word take 2 characters, and english word take 1 characters
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_UNIFIEDCOMPOSER.doc
*/
#define CFG_MMI_MMS_CHARACTER_NUM_SUBJECT_LENGTH_SUPPORT	(__OFF__)

/*
  Description: Insert owner number as MMS From address
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_MMS_APP_09A_latest.doc
*/
#define CFG_MMI_MMS_INSERT_SENDER_ADDR_FROM_SIM	(__OFF__)

/*
  Description: to specify if MMS client conform to OMA MMS Subject Length
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_UNIFIEDCOMPOSER.doc
*/
#define CFG_MMI_MMS_OMA_SUBJECT_LENGTH_SUPPORT	(__OFF__)

/*
  Description: can resize image based on left mms size.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_UNIFIEDCOMPOSER.doc
*/
#define CFG_MMI_UC_AUTO_RESIZE_IMG_BASED_ON_LEFT_MMS_SIZE	(__OFF__)

/*
  Description: Image resolution in UC
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_UNIFIEDCOMPOSER.doc
*/
#define CFG_MMI_UC_MMS_IMG_RESOLUTION	(__OFF__)

/*
  Description: 3K text buffer support for each slide and support Encoding based text length
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_UC_ENCODING_BASED_SLIDE_TEXT_LENGTH_SUPPORT	(__OFF__)

/*
  Description: Maximum resolution option for MMS image resizing setting menu
  Option: [__160x120__, __320x240__, __640x480__]
  Reference: DD_APP_MMS_APP_09A_latest.doc
*/
#define CFG_MMI_MMS_MAX_IMAGE_RESIZING_RESOLUTION	(__160x120__)

/*
  Description: To disable following features of UC(Unified Composer) for slim project:1. Play the inserted video while edit a MMS.2. Preview MMS while edit a MMS
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_Unified Composer_11B_SLIM.pptx
*/
#define CFG_MMI_COSMOS_UC_VIDEO_SLIM_SUPPORT	(__ON__)

/*****************************************************************************
* Messaging
    * Unified Message
        * Unified Message(Pluto)
*****************************************************************************/

/*
  Description: To enable dial sender from UM inbox feature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_UNIFIEDMESSAGE_09B_Latest
*/
#define CFG_MMI_UM_DIAL_FROM_FOLDER	(__OFF__)

/*
  Description: Iterator viewer support on UM
  Option: [__ON__, __AUTO__, __OFF__]
  Reference: DD_APP_UNIFIEDMESSAGE_09A.doc
*/
#define CFG_MMI_UM_ITERATOR_VIEWER	(__OFF__)

/*
  Description: Conversation box support on UM, this feature will be auto turned on on shell/cosmos project.
  Option: [__ON__, __AUTO__, __OFF__]
  Reference: FRS_APP_UNIFIEDMESSAGE_09B_Latest_0125.doc
*/
#define CFG_MMI_UM_CONVERSATION_BOX	(__OFF__)

/*
  Description: Add conversation enhance compile option
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: APP_UM_DD.doc
*/
#define CFG_MMI_UM_CONVERSATION_BOX_ENHANCE	(__OFF__)

/*
  Description: Conversation box including outbox message on UM
  Option: [__ON__, __AUTO__, __OFF__]
  Reference: FRS_APP_UNIFIEDMESSAGE_09B_Latest_0125.doc
*/
#define CFG_MMI_UM_CONVERSATION_BOX_WITH_OUTBOX	(__OFF__)

/*
  Description: Use to turn on/off the report box features
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_UNIFIEDMESSAGE_09B_Latest_0125.doc
*/
#define CFG_MMI_UM_REPORT_BOX	(__OFF__)

/*
  Description: The delivery stauts appear in the option menu of sent messages
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_UNIFIEDMESSAGE_09B_Latest.doc
*/
#define CFG_MMI_UM_REPORT_STATUS_IN_SENT_BOX	(__OFF__)

/*
  Description: To enable inline message folder list in the unified message folder.
  Option: [__UM_LIST_NORMAL__, __UM_LIST_INLINE__]
  Reference: FRS_APP_UNIFIEDMESSAGE_09B_Latest
*/
#define CFG_MMI_UNIFIED_MESSAGE_FOLDER_LIST_STYLE	(__UM_LIST_NORMAL__)

/*
  Description: For SLIM_PROJECT, slight defeature will be performed on UM app. This option will be Used as default MMI feature config for slim project.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_UNIFIEDMESSAGE.doc
*/
#define CFG_MMI_UM_SLIM	(__OFF__)

/*
  Description: Message over all slim compile option for cosmos slim package
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_Unified Message_11B.pptx
*/
#define CFG_MMI_MESSAGE_SLIM	(__OFF__)

/*
  Description: The feature is used in UM and it provide the boxlist style to view messages. The feature is not available in COSMOS Slim project.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_UM_BOX_LIST_SUPPORT	(__OFF__)

/*****************************************************************************
* Multimedia
    * ATV
        * ATV(Service)
*****************************************************************************/

/*****************************************************************************
* Multimedia
    * Auto Answer Machine
        * Auto Answer Machine(Pluto)
*****************************************************************************/

/*
  Description: Enable new feature , auto answer machine
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_AUTOAM_08B_latest.doc
*/
#define CFG_MMI_AUTO_ANSWER_MACHINE	(__OFF__)

/*****************************************************************************
* Multimedia
    * Camera
        * Camcorder(Cosmos)
*****************************************************************************/

/*
  Description: Phone Drive
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_CAMCO_NOPHONEDRIVE	(__ON__)

/*
  Description: Camcorder Slim version with sample UE  CFG option
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_UCM.pptx
*/
#define CFG_MMI_CAMCO_SLIM	(__ON__)

/*****************************************************************************
* Multimedia
    * Camera
        * Camera(Pluto)
*****************************************************************************/

/*
  Description: determine Slim Camera is on or off
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Camera_Slim_HLD.pptx
*/
#define CFG_MMI_CAMERA_SLIM	(__ON__)

/*
  Description: Camera is on or off
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Camera_Slim_HLD.pptx
*/
#define CFG_MMI_DISABLE_CAMERA	(__ON__)

/*****************************************************************************
* Multimedia
    * Camera
        * Video Recorder(Pluto)
*****************************************************************************/

/*
  Description: enable ONE key toggle between video recorder and camera
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_CAMERA.doc
*/
#define CFG_MMI_CAMERA_RECORDER_ONE_KEY_TOGGLE	(__ON__)

/*
  Description: determine Slim video recorder is on or off.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: VdoRec_Slim_HLD.pptx
*/
#define CFG_MMI_VIDEO_RECORDER_SLIM	(__ON__)

/*****************************************************************************
* Multimedia
    * Camera
        * Webcam
*****************************************************************************/

/*****************************************************************************
* Multimedia
    * FM Radio
        * FM Radio(Cosmos)
*****************************************************************************/

/*
  Description: FM Radio Slim
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_FMRADIO.ppt
*/
#define CFG_MMI_FM_RADIO_SLIM	(__ON__)

/*****************************************************************************
* Multimedia
    * FM Radio
        * FM Radio(Pluto)
*****************************************************************************/

/*
  Description: Animation background for FM Radio
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_FM_RADIO
*/
#define CFG_MMI_FM_RADIO_ANIMATION	(__OFF__)

/*
  Description: Force user to plug-in earphone before turn on FM radio
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_FM_RADIO
*/
#define CFG_MMI_FM_RADIO_BIND_EARPHONE	(__AUTO__)

/*
  Description: Stops at the first channel after preset auto search
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_FM_RADIO
*/
#define CFG_MMI_FM_RADIO_FIRST_CHANNEL	(__AUTO__)

/*
  Description: Enable FM output path from loud speaker
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_FM_RADIO
*/
#define CFG_MMI_FM_RADIO_LOUD_SPEAK	(__AUTO__)

/*
  Description: Select the top-N strongest channel after FM Radio preset auto search
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_FM_RADIO
*/
#define CFG_MMI_FM_RADIO_PRESET_TOP_N	(__OFF__)

/*
  Description: FM Radio skin synchronize to theme
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_FM_RADIO
*/
#define CFG_MMI_FM_SKIN_SYN_TO_THEME	(__ON__)

/*
  Description: Only use one FM radio skin
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_FM_RADIO
*/
#define CFG_MMI_FM_SLIM_SKIN	(__ON__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_FM_PLUTO_SLIM	(__ON__)

/*****************************************************************************
* Multimedia
    * Gallery
        * Image(Cosmos)
*****************************************************************************/

/*
  Description: to enable photo editor in cosmos project
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PhotoEditor_PhotoArt_V0.3.doc
*/
#define CFG_MMI_COSMOS_PHOTOEDITOR	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: HLD_Cosmos3D_Slideshow.pptx
*/
#define CFG_MMI_COSMOS_GALLERY_3D_SLIDESHOW	(__OFF__)

/*
  Description: Cosmos Gallery
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_COSMOS_GALLERY_SLIM_PROFILE_5M	(__ON__)

/*
  Description: Gallery Slim version with sample UE & slim data model, MMI feature option
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_GALLERY.ppt
*/
#define CFG_MMI_GALLERY_SLIM	(__ON__)

/*
  Description: controls Gallery zoom ratio, __ON__ ==> 4x LCD__OFF__ ==> 9x LCD
  Option: [__ON__, __AUTO__, __OFF__]
  Reference: gallery_feature.pptx
*/
#define CFG_MMI_COSMOS_GALLERY_IMAGE_VIEWER_MAGNIFICATION_SLIM	(__ON__)

/*****************************************************************************
* Multimedia
    * Gallery
        * Video(Cosmos)
*****************************************************************************/

/*****************************************************************************
* Multimedia
    * Image Viewer
        * Image Clipper CUI(Pluto)
*****************************************************************************/

/*
  Description: Image Clipper CUI
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FTE2.0 photo edior clip_CUI_v0.55.vsd
*/
#define CFG_MMI_IMAGE_CLIP_CUI	(__OFF__)

/*****************************************************************************
* Multimedia
    * Image Viewer
        * Image Editor(Cosmos)
*****************************************************************************/

/*
  Description: Config the photo editor IES working memory as 8M
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: USER_MANUAL_IMGEDT_PARTIAL.doc
*/
#define CFG_MMI_COSMOS_IMGEDT_PARTIAL	(__OFF__)

/*
  Description: If this Compile option turn on, IES service memory costdown from 8M to 6M, but app do not support add frame if file larger then 5MP
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_COSMOS_IMGEDT_SLIM	(__ON__)

/*****************************************************************************
* Multimedia
    * Image Viewer
        * Image Viewer(Pluto)
*****************************************************************************/

/*
  Description: To switch cache function of standard image viewer
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_IV_SEandCACHE.vsd
*/
#define CFG_MMI_IMGVIEW_CACHE	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_IV_PLUTO_SLIM	(__ON__)

/*
  Description: When ON, Gallery Image Viewer (launched from Camera or MATV) will also include video files in the interface.This results in larger ASM FG usage and concurrency.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_GALLERY_VIDEO_IN_IMAGE_VIEWER	(__OFF__)

/*****************************************************************************
* Multimedia
    * Misc
        * Media Cache
*****************************************************************************/

/*
  Description: create meta for ies to decode image quickly.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Media_cache.ppt
*/
#define CFG_MMI_SRV_IES_META	(__OFF__)

/*
  Description: using sqlite to save and read META, then you can see image quickly and clearly
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Media_cache.ppt
*/
#define CFG_MMI_SRV_IES_META_DB	(__OFF__)

/*****************************************************************************
* Multimedia
    * Music Player
        * Audio Player(Pluto)
*****************************************************************************/

/*
  Description: audio player spectrum display
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_AUDIO_PLAYER_06B.doc
*/
#define CFG_MMI_AUDIO_SPECTRUM_DISPLAY	(__ON__)

/*
  Description: supports editable equlaizer
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_AUDIO_PLAYER_06B.doc
*/
#define CFG_MMI_EDITABLE_AUDIO_EQUALIZER	(__OFF__)

/*
  Description: Supports MMI Audio Player
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_AUDIO_PLAYER_06B.doc
*/
#define CFG_MMI_AUDIO_PLAYER	(__OFF__)

/*
  Description: shows audio player animation.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_AUDIO_PLAYER_06B.doc
*/
#define CFG_MMI_AUDIO_PLAYER_ANIMATION	(__OFF__)

/*
  Description: auto update play list when files are modified in file manager when auto gen on
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_AUDIO_PLAYER_06B.doc
*/
#define CFG_MMI_AUDIO_PLAYER_AUTO_REFRESH_LIST_AUTOGEN_ON	(__OFF__)

/*
  Description: shows filename, channel, quality in audio player details.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_AUDIO_PLAYER_06B.doc
*/
#define CFG_MMI_AUDIO_PLAYER_DETAIL_SHOW_MORE_INFO	(__OFF__)

/*
  Description: Enable single line scrolling lyrics display
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_AUDIO_PLAYER_06B.doc
*/
#define CFG_MMI_AUDIO_PLAYER_LYRIC_DISPLAY	(__OFF__)

/*
  Description: supports only one skin for audio player to reduce memory consumption
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_AUDIO_PLAYER_06B.doc
*/
#define CFG_MMI_SLIM_AUDIO_PLAYER	(__ON__)

/*
  Description: Enables Multiline lyrics display
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_AUDIO_PLAYER_LYRIC_NLINE_DISPLAY	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_AUDIO_PLAYER_ULTRA_SLIM	(__ON__)

/*
  Description: Music player widget Slim version with sample UE,  MMI feature option
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_WIDGET.pptx
*/
#define CFG_MMI_VUI_WIDGET_MUSIC_PLAYER_SLIM	(__ON__)

/*
  Description: Music player sound effect setting Slim version,  MMI feature option
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_MUSICPLAY.pptx
*/
#define CFG_MMI_MUSIC_PLAYER_SLIM_SOUND_EFFECT	(__ON__)

/*
  Description: Supports MMI Audio Player BT Dailer
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_AUDIO_PLAYER_06B.doc
*/
#define CFG_MMI_AUDIO_PLAYER_BT	(__OFF__)

/*
  Description: Enable/Disable Audio player details feature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_AUDIO_PLAYER_DETAILS_SUPPORT	(__ON__)

/*
  Description: Supports MMI BT Music APP
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_AUDIO_PLAYER_06B.doc
*/
#define CFG_MMI_BT_MUSIC	(__OFF__)

/*
  Description: BTBOX Karaoke
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_MMI_BTBOX.ppt
*/
#define CFG_MMI_KARAOKE	(__OFF__)

/*
  Description: BTBOX Megaphone
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_BTDIALER.pptx
*/
#define CFG_MMI_MEGAPHONE_SUPPORT	(__OFF__)

/*
  Description: Audio player specs
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Making Audio player SLIM for PLUTO_QVGA project
*/
#define CFG_MMI_ULTRA_SLIM_AUDIO_PLAYER	(__ON__)

/*****************************************************************************
* Multimedia
    * Music Player
        * Media player(Cosmos)
*****************************************************************************/

/*
  Description: let ATV support phone drive
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_ATV_PHONE_DRIVE_SUPPORT	(__OFF__)

/*
  Description: ATV slim
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_ATV.ppt
*/
#define CFG_MMI_ATV_SLIM	(__OFF__)

/*
  Description: : If __MMI_MEDIA_PLAYER_PLST_DB_STYLE__ is defined , customs could define __IMAGE_FLOW_SUPPORT__ to swith image flow on.
  Option: [__ON__, __AUTO__, __OFF__]
  Reference: UT_IMAGE_FLOW.xls
*/
#define CFG_MMI_MEDIA_PLAYER_IMAGE_FLOW_SUPPORT	(__AUTO__)

/*
  Description: Media player lyric display support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_MEDIAPLAYER_SETTINGS.doc
*/
#define CFG_MMI_MEDIA_PLAYER_LYRIC_DISPLAY	(__OFF__)

/*
  Description: If defined __INTEGRATED_PLAYER_FTE_DB__ custom could define  __MMI_MEDIA_PLAYER_PLST_DB_ENHANCE__ to swith on enhancement media player autogetegy. In this version List service and auto category media player enhancement for:1. Support prefix search for media lib info2. Edit audio detail info3. support default playlist including: My favoriout, recent played, most played...
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MEDIA_PLAYER_MENU_TREE.vsd
*/
#define CFG_MMI_MEDIA_PLAYER_PLST_DB_ENHANCE	(__OFF__)

/*
  Description: support 1G128 phone drvie feature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_MUSIC_PLAYER_PHONE_DRIVE	(__OFF__)

/*****************************************************************************
* Multimedia
    * Sound Recorder
        * Sound Recorder(Cosmos)
*****************************************************************************/

/*
  Description: SoundRec Slim
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_SOUNDREC.ppt
*/
#define CFG_MMI_SOUNDREC_SLIM	(__ON__)

/*****************************************************************************
* Multimedia
    * Sound Recorder
        * Sound Recorder(Pluto)
*****************************************************************************/

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_SNDREC_SLIM	(__ON__)

/*
  Description: This feature is to slim down sound recorder settings. By turning this feature ON sound recorder would not show settings option. All the settings would be taken default for recording
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MT6261-soundrecorder-SLIM_Feature_Options.ppt
*/
#define CFG_MMI_SNDREC_SLIM_SETTINGS	(__ON__)

/*****************************************************************************
* Multimedia
    * Sound Recorder
        * Sound Recorder(Service)
*****************************************************************************/

/*****************************************************************************
* Multimedia
    * Video Player
        * Video Player(Pluto)
*****************************************************************************/

/*
  Description: upport OMA Client Provisioning on Streaming and AGPS
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_MMI_OTAP_streaming.doc
*/
#define CFG_MMI_STREAMING_OTAP	(__OFF__)

/*
  Description: to enable video clipper
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_VIDEO_CLIPPER	(__OFF__)

/*
  Description: Youtube PGDL
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 8_Cosmos_Slim_YouTube_PGDL.pptx
*/
#define CFG_MMI_YOUTUBE_SHORTCUT	(__OFF__)

/*****************************************************************************
* PIM
    * Alarm
        * Alarm(Pluto)
*****************************************************************************/

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_ALARM_SLIM	(__ON__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_RTC_TEST_SLIM	(__ON__)

/*****************************************************************************
* PIM
    * Calendar
        * Azaan Alarm(Pluto)
*****************************************************************************/

/*
  Description: To turn on Azaan Alarm
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_AzaanAlarm.doc
*/
#define CFG_MMI_AZAAN_ALARM	(__OFF__)

/*****************************************************************************
* PIM
    * Calendar
        * Calendar(Cosmos)
*****************************************************************************/

/*
  Description: Calendar Slim
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_CALENDAR.ppt
*/
#define CFG_MMI_CAL_SLIM	(__ON__)

/*****************************************************************************
* PIM
    * Calendar
        * Calendar(Pluto)
*****************************************************************************/

/*
  Description: If birth field is filled in in phonebook, there will be reminder when entry Calendar.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_ORGANIZER_06B_for_240x320.doc
*/
#define CFG_MMI_BIRTHDAY_REMINDER	(__OFF__)

/*
  Description: Turn on Calendar application
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_ORGANIZER_06A.doc
*/
#define CFG_MMI_CALENDAR	(__OFF__)

/*
  Description: calendar event support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: TODO_FEATURE_GUIDELINE.ppt
*/
#define CFG_MMI_CALENDAR_EVENT	(__OFF__)

/*
  Description: To turn on Hijri Calendar
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_HIJRI.doc
*/
#define CFG_MMI_HIJRI_CALENDAR	(__OFF__)

/*
  Description: Support Hindu Calendar
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_Indian_calendar_1.1.doc
*/
#define CFG_MMI_INDICAL	(__OFF__)

/*****************************************************************************
* PIM
    * Calendar
        * Calendar(Service)
*****************************************************************************/

/*****************************************************************************
* PIM
    * File Manager
*****************************************************************************/

/*
  Description: Default hide mp3 extensionand FMGR will display MP3 extension while this compile option is turned-on
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_FMGR_08B_Latest.doc
*/
#define CFG_MMI_SHOW_DAF_FILE_EXT	(__OFF__)

/*
  Description: Show file extension file.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_FMGR_08B_Latest.doc
*/
#define CFG_MMI_SHOW_FILE_EXT	(__AUTO__)

/*
  Description: Turn-on MMI File Manager Application with SLIM version.SLIM version means the number of FMGR cache is less.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_FMGR_08B_Latest.doc
*/
#define CFG_MMI_SLIM_FILE_MANAGER	(__ON__)

/*
  Description: When memory card/OTG device is plugged in, FMGR will ask user if he want to apply this device as default storage
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_FMGR_08B_Latest.doc
*/
#define CFG_MMI_FMGR_SUPPORT_DEFAULT_STORAGE	(__OFF__)

/*
  Description: To enable FMGR thumbnail decoding support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_FMGR_08B_Latest.doc
*/
#define CFG_MMI_FMGR_SUPPORT_THUMB_DECODE	(__OFF__)

/*
  Description: The compile option is for new feature "Folder Copy". In file manager, user can not only copy file(s), but also copy folder(s).
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: HLD_FOLDER_COPY.pptx
*/
#define CFG_MMI_FMGR_FOLDER_COPY_SUPPORT	(__OFF__)

/*
  Description: if defined, then cannot forward image and video from file manager to phonesetup and phonebook
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_Phonebook.c
*/
#define CFG_MMI_FILE_USEAS_SUPPORT	(__ON__)

/*
  Description: For ultra SLIM FMGR. Including SLIM FMGR and there are NO file option CUI and storage selector CUI.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_FMGR_10A_Latest.doc
*/
#define CFG_MMI_ULTRA_SLIM_FILE_MANAGER	(__ON__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_FMGR_HIDE_FORMAT_DRIVE	(__ON__)

/*
  Description: to turn on fast forward support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_FMGR_08B_Latest.doc
*/
#define CFG_FMGR_CSK_FORWARD	(__OFF__)

/*****************************************************************************
* PIM
    * Note
        * Note(Pluto)
*****************************************************************************/

/*
  Description: Application MMI compile option
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_NOTE_APP.doc
*/
#define CFG_MMI_NOTE_APP	(__OFF__)

/*****************************************************************************
* PIM
    * Phonebook
*****************************************************************************/

/*
  Description: Disable optional field in phonebook.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_PHB_OPTIONAL_FIELD	(__OFF__)

/*
  Description: second email field support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_PHB_OPTIONAL_FIELDS_2ND_EMAIL	(__OFF__)

/*
  Description: to reduce PHB optional fields
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_Phonebook.doc
*/
#define CFG_MMI_PHB_OPTIONAL_FIELD_ADDITIONAL	(__ON__)

/*
  Description: phonebook support last name field
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_Phonebook.doc
*/
#define CFG_MMI_PHB_LAST_NAME_FIELD	(__OFF__)

/*
  Description: to disable phonebook caller group for SLIM project
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_PHB_CALLER_GROUP	(__OFF__)

/*
  Description: to disable PHB caller resource
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_Phonebook.doc
*/
#define CFG_MMI_PHB_CALLER_RES	(__OFF__)

/*
  Description: Showing video for calling screen
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_PHB_CALLER_VIDEO	(__OFF__)

/*
  Description: This feature provides phonebook and AB repeater to save and get file path into a file database. If turn off, phonebook can not store incoming image.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_SRV_PHB_CALLER_RES_DATA_STORE	(__OFF__)

/*
  Description: PHB UI with Tab Screens
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_PHB_UI_IN_TABS	(__OFF__)

/*
  Description: Show Name and Number with selection and associated Picture
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_PHB_TWO_LINE_MENUITEM_DISPLAY	(__OFF__)

/*
  Description: ask user if copy SIM data to phone when first time bootup
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_PHB_STARTUP_COPY_SIM	(__OFF__)

/*
  Description: Allow sos number editable
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_PHB_SOS_NUM_EDIT	(__OFF__)

/*
  Description: Phonebook save unknown number from CM and messages
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_PHB_SAVE_CONTACT_NOTIFY	(__OFF__)

/*
  Description: Enable Quick search feature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_PHB_QUICK_SEARCH	(__OFF__)

/*
  Description: Sort phonebook list in Pinyin order
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_PHB_PINYIN_SORT	(__OFF__)

/*
  Description: enable multi copy and multi delete feature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_Phonebook.doc
*/
#define CFG_MMI_PHB_MULTI_OPERATION	(__OFF__)

/*
  Description: phb multi select for other apps
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_PHB_GENERIC_MULTI_SELECT	(__OFF__)

/*
  Description: To enable phone lock check when delete all
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_PHB_DELETE_ALL_CHECK_PHONE_LOCK	(__OFF__)

/*
  Description: Phonebook default number support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_PHB_DEFAULT_NUMBER	(__OFF__)

/*
  Description: Compare number filed only in mobile number field
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_PHB_ADV_NUM_MATCH_MOBILE	(__ON__)

/*
  Description: Turn on birthday field in phonebook field
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_PHB_BIRTHDAY_FIELD	(__OFF__)

/*
  Description: To turn on title, url, address, note field in phonebook
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_PHB_INFO_FIELD	(__OFF__)

/*
  Description: add phonebook photo sticker support config
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: TSSQA00209886
*/
#define CFG_MMI_PHB_PHOTO_STICKER_SUPPORT	(__OFF__)

/*
  Description: provide PHB list to replace when saving contact
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_SAVE_CONTACT_REPLACE	(__OFF__)

/*
  Description: phb support msn field
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_PHB_MSN_FIELD	(__OFF__)

/*
  Description: phb support custom define number & email type
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_PHB_CUSTOM_FIELD_TYPE	(__OFF__)

/*
  Description: phb support custom define number & email type
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_PHB_EMPTY_NAME_TOP	(__OFF__)

/*
  Description: Enable multi vCard objects
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_VOJECT.doc
*/
#define CFG_MMI_MULTI_VCARD	(__OFF__)

/*
  Description: ADD CFG for Phonebook speed dial
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_PHB_SPEED_DIAL	(__OFF__)

/*
  Description: Contact support memory card storage
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: TSSQA00210668
*/
#define CFG_MMI_PHB_TCARD_STORAGE_SUPPORT	(__OFF__)

/*
  Description: Dialer slim
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_CONTACT.ppt
*/
#define CFG_MMI_CONTACT_SLIM	(__ON__)

/*
  Description: To support sync BT contacts from Smart phone or other devices via BT PBAP profile
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_PHB_PBAPC_SYNC_CONTACT	(__OFF__)

/*****************************************************************************
* PIM
    * Phonebook
        * Contact Operation
*****************************************************************************/

/*****************************************************************************
* PIM
    * Synchronization
*****************************************************************************/

/*
  Description: Make  client can get syncml profiles updated from provisioning or DM.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_SYNCML(NEW UI+ PC SYNC) .doc
*/
#define CFG_MMI_SYNCML_CCA_SUPPORT	(__AUTO__)

/*
  Description: To enable task sync feature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_SYNCML(NEW UI+ PC SYNC).do
*/
#define CFG_MMI_SYNCML_SYNC_TASK_SUPPORT	(__OFF__)

/*
  Description: To enable canlendar sync feature.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_SYNCML(NEW UI+ PC SYNC).do
*/
#define CFG_MMI_SYNCML_SYNC_CALENDAR_SUPPORT	(__OFF__)

/*
  Description: Start sync from applications
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_SYNCML(NEW UI+ PC SYNC).doc
*/
#define CFG_MMI_SYNCML_APP_SYNC_MENU_SUPPORT	(__OFF__)

/*
  Description: Store factory default needs to restore sync settings
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_SYNCML(NEW UI+ PC SYNC).doc
*/
#define CFG_MMI_SYNCML_RESTORE_FACTORY_DEFAULT	(__OFF__)

/*
  Description: Sync delay for each record modified
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_SYNCML(NEW UI+ PC SYNC).doc
*/
#define CFG_MMI_SYNCML_DATA_CHANGE_SYNC_DELAY	(__OFF__)

/*
  Description: This feature allows data synchornization, which is basing on SyncML, between two phones via blue tooth.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_PHONESYNC.doc
*/
#define CFG_MMI_SYNCML_DEVICE_SYNC	(__OFF__)

/*
  Description: Add a status icon for syncml , show it when sync is running, disappear when finish
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_SYNCML(NEW UI+ PC SYNC).doc
*/
#define CFG_MMI_SYNCML_STATUS_ICON_SUPPORT	(__OFF__)

/*
  Description: This compile option support the device sync database tasks
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_PHONESYNC.doc
*/
#define CFG_MMI_SYNCML_DEVICE_TASK_SUPPORT	(__OFF__)

/*
  Description: This compile option support the device sync database calendar.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_PHONESYNC.doc
*/
#define CFG_MMI_SYNCML_DEVICE_CALENDAR_SUPPORT	(__OFF__)

/*
  Description: Pc sync : phone can synchronize its data with pc
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_SYNCML(NEW UI+ PC SYNC).doc
*/
#define CFG_MMI_SYNCML_PC_SYNC_SUPPORT	(__OFF__)

/*
  Description: Sync when data changed will be applied on regular sync way
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_SYNCML(NEW UI+ PC SYNC).doc
*/
#define CFG_MMI_SYNCML_VF_DATA_CHANGE_SYNC	(__OFF__)

/*
  Description: note sync for syncml, can sync note database
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_SYNCML(NEW UI+ PC SYNC).doc
*/
#define CFG_MMI_SYNCML_SYNC_NOTE_SUPPORT	(__OFF__)

/*****************************************************************************
* PIM
    * To-Do List
        * To-Do List(Cosmos)
*****************************************************************************/

/*
  Description: Turn on To Do List application
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_ORGANIZER_06A.doc
*/
#define CFG_MMI_TODOLIST	(__OFF__)

/*
  Description: Todo with NITZ support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_ORGANIZER_06B_for_240x320.doc
*/
#define CFG_MMI_TDL_NITZ_SUPPORT	(__OFF__)

/*
  Description: Turn on vCalendar Application
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_VOJECT.doc
*/
#define CFG_MMI_VCALENDAR	(__AUTO__)

/*****************************************************************************
* Run Time Environment
    * Java
        * JSR
*****************************************************************************/

/*****************************************************************************
* Run Time Environment
    * MRE Engine
*****************************************************************************/

/*
  Description: MRE entry will be in main menu
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_Porting_Manual.doc
*/
#define CFG_MMI_MRE_MAIN_MENU	(__OFF__)

/*
  Description: MRE entry will be in sub menu of func & game
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_Porting_Manual.doc
*/
#define CFG_MMI_MRE_SUB_MENU	(__OFF__)

/*
  Description: MRE shortcut -- Opera
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_APP_Config.doc
*/
#define CFG_MMI_MRE_SHORTCUT_OPERA	(__OFF__)

/*
  Description: Is it support update
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_APP_Config.doc
*/
#define CFG_MMI_MRE_SUPPORT_UPDATE	(__OFF__)

/*
  Description: not able to install and launch
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: CFG_MMI_MRE_NO_POPUP_AUTHENTICATION_SUPPORT.txt
*/
#define CFG_MMI_MRE_NO_POPUP_AUTHENTICATION_SUPPORT	(__OFF__)

/*
  Description: Enable auto start mre application.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Safemode.ppt.
*/
#define CFG_MMI_MRE_AUTO_START	(__OFF__)

/*
  Description: Enable M-Space Application.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: M-Space_introduction.ppt
*/
#define CFG_MMI_MRE_MSPACE	(__ON__)

/*
  Description: Define the widget memory size
  Option: [600*1024, 1420*1024, 1800*1024]
  Reference: DD_VAPP_HOMESCREEN.docx
*/
#define CFG_MMI_VUI_WIDGET_MRE_MEM_SIZE	(600*1024)

/*****************************************************************************
* Run Time Environment
    * MRE Engine
        * Common(Service)
*****************************************************************************/

/*
  Description: preinstall mre app in phone package
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: pre-installation.pptx
*/
#define CFG_MMI_MRE_PREINSTALL_PHONE_PACKAGE	(__OFF__)

/*
  Description: preinstall mre app in system package
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: pre-installation.pptx
*/
#define CFG_MMI_MRE_PREINSTALL_SYS_PACKAGE	(__OFF__)

/*****************************************************************************
* Run Time Environment
    * MRE Preload APPs
*****************************************************************************/

/*
  Description: This compile option is used to enable MRE based Yahoo Finance as built-in app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Yahoo_Finance_FRS_v8.vsd
*/
#define CFG_MMI_MRE_APP_YAHOOFINANCE	(__OFF__)

/*
  Description: This compile option is used to enable MRE based Yahoo News as built-in app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Yahoo_news_Frs_v5.vsd
*/
#define CFG_MMI_MRE_APP_YAHOONEWS	(__OFF__)

/*
  Description: This compile option is used to enable MRE based Yahoo Weather as built-in app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Yahoo_Weather_FRS_v5.vsd
*/
#define CFG_MMI_MRE_APP_YAHOOWEATHER	(__OFF__)

/*
  Description: This compile option is used to enable MRE based FacebookLite as built-in app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Facebook_FRS_v5.vsd
*/
#define CFG_MMI_MRE_APP_FBLITE	(__OFF__)

/*
  Description: MRE Application -- opera
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_APP_Config.doc
*/
#define CFG_MMI_MRE_APP_OPERA	(__OFF__)

/*
  Description: This compile option is used to enable MRE based stopwatch app as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_MRE_APP_STOPWATCH	(__OFF__)

/*
  Description: This compile option is used to enable MRE based health app as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_MRE_APP_HEALTH	(__OFF__)

/*
  Description: This compile option is used to enable MRE based converter app as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_MRE_APP_CONVERTER	(__OFF__)

/*
  Description: This compile option is used to enable MRE based ZAKAT calculator as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_MRE_APP_ZAKAT	(__OFF__)

/*
  Description: This compile option is used to enable MRE based ebook as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_MRE_APP_ZY_EBOOK	(__OFF__)

/*
  Description: This compile option is used to enable MRE based calculator as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_MRE_APP_CALCULATOR	(__OFF__)

/*
  Description: This CFG will turn on MRE based Y!M v2 as built-in app.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Yahoo_Messenger2_FRS_v6.vsd
*/
#define CFG_MMI_MRE_APP_YAHOOMV2	(__OFF__)

/*
  Description: This CFG will enable package 2 for GameLoft games for China billing system
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: GameLoft_Games_FRS
*/
#define CFG_MMI_MRE_APP_GAMELOFT_CN_PACKAGE2	(__OFF__)

/*
  Description: This CFG will enable package 3 for GameLoft games for global billing system
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: GameLoft_Games_FRS
*/
#define CFG_MMI_MRE_APP_GAMELOFT_GB_PACKAGE3	(__OFF__)

/*
  Description: This CFG will enable package 3 for GameLoft games for China billing system
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: GameLoft_Games_FRS
*/
#define CFG_MMI_MRE_APP_GAMELOFT_CN_PACKAGE3	(__OFF__)

/*
  Description: This CFG will enable package 1 for GameLoft games for China billing system
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: GameLoft_Games_FRS
*/
#define CFG_MMI_MRE_APP_GAMELOFT_CN_PACKAGE1	(__OFF__)

/*
  Description: This CFG will enable package 1 for GameLoft games for global billing system
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: GameLoft_Games_FRS
*/
#define CFG_MMI_MRE_APP_GAMELOFT_GB_PACKAGE1	(__OFF__)

/*
  Description: This CFG will enable package 2 for GameLoft games for global billing system
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: GameLoft_Games_FRS
*/
#define CFG_MMI_MRE_APP_GAMELOFT_GB_PACKAGE2	(__OFF__)

/*
  Description: This CFG will enable package 4 for GameLoft games for global billing system
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: GameLoft_Games_FRS
*/
#define CFG_MMI_MRE_APP_GAMELOFT_GB_PACKAGE4	(__OFF__)

/*
  Description: This CFG will enable package 4 for GameLoft games for China billing system
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: GameLoft_Games_FRS
*/
#define CFG_MMI_MRE_APP_GAMELOFT_CN_PACKAGE4	(__OFF__)

/*
  Description: This compile option is used to enable MRE based Youku client as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_Youku_preload.doc
*/
#define CFG_MMI_MRE_APP_YOUKU	(__OFF__)

/*
  Description: This CFG will turn on/off MRE based MRE Yahoo Cricket
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: PromotionalSlides_YahooCricket.pptx
*/
#define CFG_MMI_MRE_APP_YAHOOCRICKET	(__OFF__)

/*
  Description: This compile option is used to enable MRE based KKFUN-FISHINGFUN_SC as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_FruitNinja_preload.doc
*/
#define CFG_MMI_MRE_APP_FISHINGFUN_SC	(__OFF__)

/*
  Description: This compile option is used to enable MRE based KKFUN-FISHINGFUN_EN as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_FruitNinja_preload.doc
*/
#define CFG_MMI_MRE_APP_FISHINGFUN_EN	(__OFF__)

/*
  Description: This compile option is used to enable MRE based KKFUN-FRUITNINJA_SC as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_FruitNinja_preload.doc
*/
#define CFG_MMI_MRE_APP_FRUITNINJA_SC	(__OFF__)

/*
  Description: This compile option is used to enable MRE based KKFUN-ANGRYBIRDS_EN as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_AngryBirds_preload.doc
*/
#define CFG_MMI_MRE_APP_ANGRYBIRDS_EN	(__OFF__)

/*
  Description: This compile option is used to enable MRE based KKFUN-ANGRYBIRDS_SC as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_AngryBirds_preload.doc
*/
#define CFG_MMI_MRE_APP_ANGRYBIRDS_SC	(__OFF__)

/*
  Description: This compile option is used to enable MRE based KKFUN-FRUITNINJA_EN as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_FruitNinja_preload.doc
*/
#define CFG_MMI_MRE_APP_FRUITNINJA_EN	(__OFF__)

/*
  Description: This CFG will turn on/off MRE  facebook v2 application
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Facebook_v2 FRS
*/
#define CFG_MMI_MRE_APP_FACEBOOK_V2	(__OFF__)

/*
  Description: MRE application rash motor TC version.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: PromotionSlides_BalanceBall.ppt
*/
#define CFG_MMI_MRE_APP_3GT_GAME_BALANCE_BALL_CHT	(__OFF__)

/*
  Description: MRE application rash motor SC version.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: PromotionSlides_BalanceBall.ppt
*/
#define CFG_MMI_MRE_APP_3GT_GAME_BALANCE_BALL_CHS	(__OFF__)

/*
  Description: MRE application rash motor TC version.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: PromotionSlides_RashMotor.ppt
*/
#define CFG_MMI_MRE_APP_3GT_GAME_RASH_MOTOR_CHT	(__OFF__)

/*
  Description: MRE application rash motor SC version.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: PromotionSlides_RashMotor.ppt
*/
#define CFG_MMI_MRE_APP_3GT_GAME_RASH_MOTOR_CHS	(__OFF__)

/*
  Description: MRE application rash motor English version.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: PromotionSlides_BalanceBall.ppt
*/
#define CFG_MMI_MRE_APP_3GT_GAME_BALANCE_BALL_ENG	(__OFF__)

/*
  Description: MRE application rash motor English version.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: PromotionSlides_RashMotor.ppt
*/
#define CFG_MMI_MRE_APP_3GT_GAME_RASH_MOTOR_ENG	(__OFF__)

/*
  Description: This compile option is used to enable MRE based KINGCOMBAT_CHS as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_KINGCOMBAT_CHS	(__OFF__)

/*
  Description: This compile option is used to enable MRE based HAPPYWAR_EN as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_HAPPYWAR_EN	(__OFF__)

/*
  Description: This compile option is used to enable MRE based GIRLSLOT_CHS as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_GIRLSLOT_CHS	(__OFF__)

/*
  Description: This compile option is used to enable MRE based HAPPYWAR_CHS as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_HAPPYWAR_CHS	(__OFF__)

/*
  Description: This compile option is used to enable MRE based HAPPYEGG_CHS as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_HAPPYEGG_CHS	(__OFF__)

/*
  Description: This compile option is used to enable MRE based MOTO_CHS as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_MOTO_CHS	(__OFF__)

/*
  Description: This compile option is used to enable MRE based EGYPTCODE_EN as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_EGYPTCODE_EN	(__OFF__)

/*
  Description: This compile option is used to enable MRE based EGYPTCODE_CHS as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_EGYPTCODE_CHS	(__OFF__)

/*
  Description: This compile option is used to enable MRE based MOTO_EN as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_MOTO_EN	(__OFF__)

/*
  Description: This compile option is used to enable MRE based TEARDRESS_EN as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_TEARDRESS_EN	(__OFF__)

/*
  Description: This compile option is used to enable MRE based GOLDMINER_EN as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_GOLDMINER_EN	(__OFF__)

/*
  Description: This compile option is used to enable MRE based PARKOUR_EN as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_PARKOUR_EN	(__OFF__)

/*
  Description: This compile option is used to enable MRE based HAPPYEGG_EN as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_HAPPYEGG_EN	(__OFF__)

/*
  Description: This compile option is used to enable MRE based TEARDRESS_CHS as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_TEARDRESS_CHS	(__OFF__)

/*
  Description: This compile option is used to enable MRE based PARKOUR_CHS as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_PARKOUR_CHS	(__OFF__)

/*
  Description: This compile option is used to enable MRE based GOLDMINER_CHS as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_GOLDMINER_CHS	(__OFF__)

/*
  Description: This compile option is used to enable MRE based GIRLSLOT_EN as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_GIRLSLOT_EN	(__OFF__)

/*
  Description: This compile option is used to enable MRE based KINGCOMBAT_EN as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_KINGCOMBAT_EN	(__OFF__)

/*
  Description: This CFG will turn on/off MRE  facebook v2 standard version application
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Facebook_v2_promotion_slide.pptx
*/
#define CFG_MMI_MRE_APP_FACEBOOK_V2_STANDARD	(__OFF__)

/*
  Description: This compile option is used to enable MRE based Wochacha  as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: promotionalslides_wochacha.pptx
*/
#define CFG_MMI_MRE_APP_WOCHACHA	(__OFF__)

/*
  Description: This compile option is used to enable MRE based HAPPYEGG_EN as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_HAPPYEGG_EN_SHORTCUT	(__OFF__)

/*
  Description: This compile option is used to enable MRE based GOLDMINER_EN as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_GOLDMINER_EN_SHORTCUT	(__OFF__)

/*
  Description: This compile option is used to enable MRE based ZAKAT calculator as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_APP_Config.doc
*/
#define CFG_MMI_MRE_APP_ZAKAT_SHORTCUT	(__OFF__)

/*
  Description: This compile option is used to enable MRE based GIRLSLOT_EN as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_GIRLSLOT_EN_SHORTCUT	(__OFF__)

/*
  Description: This compile option is used to enable MRE based EGYPTCODE_EN as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_EGYPTCODE_EN_SHORTCUT	(__OFF__)

/*
  Description: This compile option is used to enable MRE based calculator as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_APP_Config.doc
*/
#define CFG_MMI_MRE_APP_CALCULATOR_SHORTCUT	(__OFF__)

/*
  Description: This compile option is used to enable MRE based health app as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_APP_Config.doc
*/
#define CFG_MMI_MRE_APP_HEALTH_SHORTCUT	(__OFF__)

/*
  Description: This compile option is used to enable MRE based stopwatch app as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_APP_Config.doc
*/
#define CFG_MMI_MRE_APP_STOPWATCH_SHORTCUT	(__OFF__)

/*
  Description: This compile option is used to enable MRE based TEARDRESS_EN as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_TEARDRESS_EN_SHORTCUT	(__OFF__)

/*
  Description: This compile option is used to enable MRE based Yahoo News as built-in app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Yahoo_news_Frs_v5.vsd
*/
#define CFG_MMI_MRE_APP_YAHOONEWS_SHORTCUT	(__OFF__)

/*
  Description: This CFG will turn on/off MRE  facebook v2 application
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Facebook_v2 FRS
*/
#define CFG_MMI_MRE_APP_FACEBOOK_V2_SHORTCUT	(__OFF__)

/*
  Description: This CFG will turn on/off MRE based MRE Yahoo Cricket
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: PromotionalSlides_YahooCricket.pptx
*/
#define CFG_MMI_MRE_APP_YAHOOCRICKET_SHORTCUT	(__OFF__)

/*
  Description: Option to turn on/off MRE based Twitter applicatiion as built-in app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Twitter FRS
*/
#define CFG_MMI_MRE_APP_TWITTER_SHORTCUT	(__OFF__)

/*
  Description: This CFG will turn on MRE based Y!M v2 as built-in app.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Yahoo_Messenger2_FRS_v6.vsd
*/
#define CFG_MMI_MRE_APP_YAHOOMV2_SHORTCUT	(__OFF__)

/*
  Description: This compile option is used to enable MRE based MOTO_EN as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_MOTO_EN_SHORTCUT	(__OFF__)

/*
  Description: MRE APP mBounce Appstore
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_APP_Config.doc
*/
#define CFG_MMI_MRE_APP_MBOUNCE_APPSTORE_SHORTCUT	(__OFF__)

/*
  Description: MRE APP Gameloft live
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_APP_Config.doc
*/
#define CFG_MMI_MRE_APP_GAMELOFT_LIVE_SHORTCUT	(__OFF__)

/*
  Description: This compile option is used to enable MRE based Yahoo Finance as built-in app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Yahoo_Finance_FRS_v8.vsd
*/
#define CFG_MMI_MRE_APP_YAHOOFINANCE_SHORTCUT	(__OFF__)

/*
  Description: MRE APP Gmobi Appstore
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_APP_Config.doc
*/
#define CFG_MMI_MRE_APP_GMOBI_APPSTORE_SHORTCUT	(__OFF__)

/*
  Description: This compile option is used to enable MRE based Yahoo Weather as built-in app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Yahoo_Weather_FRS_v5.vsd
*/
#define CFG_MMI_MRE_APP_YAHOOWEATHER_SHORTCUT	(__OFF__)

/*
  Description: This compile option is used to enable MRE based converter app as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_APP_Config.doc
*/
#define CFG_MMI_MRE_APP_CONVERTER_SHORTCUT	(__OFF__)

/*
  Description: This compile option is used to enable MRE based HAPPYWAR_EN as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_HAPPYWAR_EN_SHORTCUT	(__OFF__)

/*
  Description: This compile option is used to enable MRE based KINGCOMBAT_EN as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_KINGCOMBAT_EN_SHORTCUT	(__OFF__)

/*
  Description: This compile option is used to enable MRE based PARKOUR_EN as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MtoneGame_AppendixNote.doc
*/
#define CFG_MMI_MRE_GAME_PARKOUR_EN_SHORTCUT	(__OFF__)

/*
  Description: Turn on/off Twitter app which support key
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Twitter APP FRS
*/
#define CFG_MMI_MRE_APP_TWITTER_KEY_SUPPORT	(__OFF__)

/*
  Description: switch mre app iBingo UI store preload
  Option: [Use mre app mask to config, refer to mmi_features_type.h]
  Reference: iBingo_uistore_promotion.pdf
*/
#define CFG_MMI_MRE_APP_IBINGO_UISTORE	(__MRE_APP_CLOSE__)

/*
  Description: preinstall mre app in tcard package
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: prinstall_mre_app_in_tcard.txt
*/
#define CFG_MMI_MRE_PREINSTALL_TCARD_PACKAGE	(__OFF__)

/*
  Description: switch mre app mobim feichengwurao app
  Option: [Use mre app mask to config, refer to mmi_features_type.h]
  Reference: mobim_fcwr_promotion.pdf
*/
#define CFG_MMI_MRE_APP_MOBIM_FCWR	(__MRE_APP_CLOSE__)

/*
  Description: Preload All APPs in 3rd ROM
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: How to Preload MRE Application.ppt
*/
#define CFG_MMI_MRE_3RD_ROM_PRELOAD	(__OFF__)

/*
  Description: This compile option is used to enable MRE based 3GT game as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_3GT_preload.doc
*/
#define CFG_MMI_MRE_APP_3GT_GAME_BOWLING_CHS	(__OFF__)

/*
  Description: This compile option is used to enable MRE based 3GT game as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_3GT_preload.doc
*/
#define CFG_MMI_MRE_APP_3GT_GAME_BOWLING_CHT	(__OFF__)

/*
  Description: This compile option is used to enable MRE based 3GT game as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_3GT_preload.doc
*/
#define CFG_MMI_MRE_APP_3GT_GAME_BOWLING_ENG	(__OFF__)

/*
  Description: This compile option is used to enable MRE based 3GT game as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_3GT_preload.doc
*/
#define CFG_MMI_MRE_APP_3GT_GAME_DANDELION	(__OFF__)

/*
  Description: This CFG will turn on/off MRE  facebook v2 standard version application
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Facebook_v2_promotion_slide.pptx
*/
#define CFG_MMI_MRE_APP_FACEBOOK_V2_STANDARD_SHORTCUT	(__OFF__)

/*
  Description: FacebookLitev1.1 has some enhancements over FBLitev1.0. Added Messages and Find friend feature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: PromotionalSlides_Facebook_v1.1.pptx
*/
#define CFG_MMI_MRE_APP_FBLITEV11	(__OFF__)

/*
  Description: Turn on GLive and Mortal Combat games
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: GameLodt 2nd Wave FRS
*/
#define CFG_MMI_MRE_APP_GAMELOFT_2ND_PACKAGE	(__OFF__)

/*
  Description: It will show shortcut download link for Assassin Creed game
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: GameLoft games FRS
*/
#define CFG_MMI_MRE_APP_GAMELOFT_AC_SHORTCUT	(__OFF__)

/*
  Description: It will preload Asphalt6 (China version) for MT6250 and HVGA project only. Also, Glive will enabled along with.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: GameLoft games FRS
*/
#define CFG_MMI_MRE_APP_GAMELOFT_AS6_CN_MT6250	(__OFF__)

/*
  Description: It will preload Asphalt6 (Global version) for MT6250 and HVGA project only. Also, Glive will enabled along with.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: GameLoft games FRS
*/
#define CFG_MMI_MRE_APP_GAMELOFT_AS6_GB_MT6250	(__OFF__)

/*
  Description: It will show shortcut download link for Asphalt game
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: GameLoft games FRS
*/
#define CFG_MMI_MRE_APP_GAMELOFT_AS6_SHORTCUT	(__OFF__)

/*
  Description: It will show shortcut download link for Block Breaker game
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: GameLoft games FRS
*/
#define CFG_MMI_MRE_APP_GAMELOFT_BB_SHORTCUT	(__OFF__)

/*
  Description: It will show shortcut download link for Brain Challenge game
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: GameLoft games FRS
*/
#define CFG_MMI_MRE_APP_GAMELOFT_BC_SHORTCUT	(__OFF__)

/*
  Description: It will show shortcut download link for Mortal Combat game
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: GameLoft games FRS
*/
#define CFG_MMI_MRE_APP_GAMELOFT_MC2_SHORTCUT	(__OFF__)

/*
  Description: This compile option is used to enable MRE based Kaixin client as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_Kaixin_preload.doc
*/
#define CFG_MMI_MRE_APP_KAIXIN	(__OFF__)

/*
  Description: This compile option is used to enable MRE based MOBIM app store as preload app shortcut
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_APP_Config.doc
*/
#define CFG_MMI_MRE_APP_MOBIM_APPSTORE_SHORTCUT	(__OFF__)

/*
  Description: Momagic appstore preload-link
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Momagicappstore.txt
*/
#define CFG_MMI_MRE_APP_MOMAGIC_APPSTORE_SHORTCUT	(__OFF__)

/*
  Description: This compile option is used to enable MRE based calculator as preload app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MRE_APP_Config.doc
*/
#define CFG_MMI_MRE_APP_OPERA_MINI_V6	(__OFF__)

/*
  Description: switch mre app sina weibo preload
  Option: [Use mre app mask to config, refer to mmi_features_type.h]
  Reference: sina_weibo_promotion.pdf
*/
#define CFG_MMI_MRE_APP_SINA_WEIBO	(__MRE_APP_CLOSE__)

/*
  Description: Option to turn on/off MRE based Twitter applicatiion as built-in app
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Twitter FRS
*/
#define CFG_MMI_MRE_APP_TWITTER	(__OFF__)

/*
  Description: Youtube PGDL
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 8_Cosmos_Slim_YouTube_PGDL.pptx
*/
#define CFG_MMI_MRE_APP_YOUTUBE	(__OFF__)

/*****************************************************************************
* Settings
    * Call Settings
*****************************************************************************/

/*
  Description: Auto quick end when time out
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_CALLHISTORY.doc
*/
#define CFG_MMI_CH_QUICK_END	(__OFF__)

/*
  Description: Turn on Black List feature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_CALLSETUP.doc
*/
#define CFG_MMI_CM_BLACK_LIST	(__OFF__)

/*
  Description: Auto rejection of no caller id
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_CALLSETUP.doc
*/
#define CFG_MMI_UCM_AUTO_REJECT_NO_CALL_ID	(__OFF__)

/*
  Description: CM white list support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_CALLSETUP.doc
*/
#define CFG_MMI_CM_WHITE_LIST	(__OFF__)

/*
  Description: Reject MT call by SMS feature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MMI_FRS_UCM_30.doc
*/
#define CFG_MMI_UCM_REJECT_BY_SMS	(__OFF__)

/*
  Description: Closed user group setting
  Option: [__ON__, __AUTO__, __OFF__]
  Reference: FRS_CALL_SETTING.doc
*/
#define CFG_MMI_CALLSET_CUG	(__OFF__)

/*
  Description: Call time display setting. If the config is OFF, call time display is default on and the users cannot turn off it through call setting.
  Option: [__ON__, __AUTO__, __OFF__]
  Reference: FRS_CALL_SETTING.doc
*/
#define CFG_MMI_CALLSET_CTD_CONFIGURABLE	(__OFF__)

/*
  Description: Caller ID setting. Hide / Show the caller id.
  Option: [__ON__, __AUTO__, __OFF__]
  Reference: FRS_CALL_SETTING.doc
*/
#define CFG_MMI_CALLSET_CALLER_ID	(__OFF__)

/*
  Description: callset slim for call time reminder,call barring,call line switching
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MT6261-CALLSET-SLIM_Feature_Options.ppt
*/
#define CFG_MMI_CALLSET_SLIM	(__ON__)

/*****************************************************************************
* Settings
    * Phone Settings
        * Phone Settings
*****************************************************************************/

/*
  Description: Enable analog clock wallpaper
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PhoneSetup.doc
*/
#define CFG_MMI_ANALOG_CLOCK	(__OFF__)

/*
  Description: Enable digital clock wallpaper
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PhoneSetup.doc
*/
#define CFG_MMI_DIGITAL_CLOCK	(__OFF__)

/*
  Description: LCD partial-display screen saver
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PhoneSetup.doc
*/
#define CFG_MMI_LCD_PARTIAL_ON	(__OFF__)

/*
  Description: Enable LCD partial-display screen saver by default
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PhoneSetup.doc
*/
#define CFG_MMI_LCD_PARTIAL_ON_ENABLED	(__OFF__)

/*
  Description: Turn on NITZ feature. It can accept date/time and PLMN information from operator.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_NITZ.doc
*/
#define CFG_MMI_NITZ	(__ON__)

/*
  Description: Support time zone and daylight saving time update of NITZ
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_NITZ.doc
*/
#define CFG_MMI_NITZ_TZ_SUPPORT	(__ON__)

/*
  Description: Image/animation type of power on/offNote: BMP recommended for MT6223. JPG/GIF recommended for other chips.
  Option: [__OFF__, __RES_TYPE_BMP__, __RES_TYPE_GIF__, __RES_TYPE_JPG__]
  Reference: SOP_UI_Display_Performance_Tuning.doc
*/
#define CFG_MMI_RES_TYPE_POWER_ONOFF_SEL	(__RES_TYPE_BMP__)

/*
  Description: Image/animation type of screen saverNote: BMP recommended for MT6223. JPG/GIF recommended for other chips.
  Option: [__OFF__, __RES_TYPE_BMP__, __RES_TYPE_GIF__, __RES_TYPE_JPG__]
  Reference: SOP_UI_Display_Performance_Tuning.doc
*/
#define CFG_MMI_RES_TYPE_SCREEN_SAVER_SEL	(__RES_TYPE_BMP__)

/*
  Description: Image/animation type of wallpaperNote: BMP recommended for MT6223. JPG/GIF recommended for other chips.
  Option: [__OFF__, __RES_TYPE_BMP__, __RES_TYPE_GIF__, __RES_TYPE_JPG__]
  Reference: SOP_UI_Display_Performance_Tuning.doc
*/
#define CFG_MMI_RES_TYPE_WALLPAPER_SEL	(__RES_TYPE_JPG__)

/*
  Description: Screensaver video display
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PhoneSetup.doc
*/
#define CFG_MMI_SCREENSAVER_DISPLAY_VIDEO	(__OFF__)

/*
  Description: PhoneSetup set default encoding type
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PhoneSetup.doc
*/
#define CFG_MMI_SET_DEF_ENCODING_TYPE	(__OFF__)

/*
  Description: sublcd wallpaper support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PhoneSetup.doc
*/
#define CFG_MMI_SUB_WALLPAPER	(__OFF__)

/*
  Description: Set screensaver waiting time from 1-59 seconds
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PhoneSetup.doc
*/
#define CFG_MMI_SETTING_SS_WAITTIME_SELECT	(__OFF__)

/*
  Description: configure screen switch effect
  Option: [SSE_SETTING_NONE, SSE_SETTING_SIMPLE, SSE_SETTING_FULL]
  Reference: DD_APP_PhoneSetup.doc
*/
#define CFG_MMI_SCREEN_SWITCH_EFFECT_SETTING	(SSE_SETTING_SIMPLE)

/*
  Description: dual clock feature for og home screen and venus ui
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PhoneSetup.doc
*/
#define CFG_MMI_DUAL_CLOCK	(__OFF__)

/*
  Description: Add compile option for preferred network setting
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_NETWORKSETUP.doc
*/
#define CFG_MMI_PREF_NETWORK	(__OFF__)

/*
  Description: Add compile option for time zone / home city setting
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PhoneSetup.doc
*/
#define CFG_MMI_TIMEZONE_SETTING	(__ON__)

/*
  Description: Compile option for enable / disable data lock settingFor Unicom
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: WCDMA
*/
#define CFG_MMI_DATA_LOCK	(__OFF__)

/*
  Description: number of wallpaper
  Option: [__OFF__, 1~16]
  Reference: DD_APP_PhoneSetup.doc
*/
#define CFG_MMI_WALLPAPER_NUM	(1)

/*
  Description: enable two layer homecity menu
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PhoneSetup.doc
*/
#define CFG_MMI_TWO_LAYER_HOMECITY	(__OFF__)

/*
  Description: to enable 3G enhancement of dual mode phone
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_NetworkSetup.doc
*/
#define CFG_MMI_NETSET_3G_ENHANCE	(__OFF__)

/*
  Description: User can decide which SIM will be used to bootup in Settings menu, and don't care the status of SIM.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: HLD_Bootup_10A_Latest.doc, CTA dual SIM standard
*/
#define CFG_MMI_DUAL_SIM_STATIC_MODE	(__ON__)

/*
  Description: UART setting
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: UART setting document
*/
#define CFG_MMI_UART_SETTING	(__OFF__)

/*
  Description: FTE support Dynamic SIM and Dynamic UI with SIM name, not support for single SIM project.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: TSSQA00210090
*/
#define CFG_MMI_DYNAMIC_SIM_DYNAMIC_UI	(__OFF__)

/*
  Description: Add config for schedule power on/off
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PhoneSetup.doc
*/
#define CFG_MMI_PHNSET_SCHEDULE_POWER_ON_OFF	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_PHONESETTING_SLIM	(__ON__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_NETWORKSETTING_SLIM	(__OFF__)

/*
  Description: Disable all shortcuts function, including VRSI.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_SHORTCUTS.doc
*/
#define CFG_DISABLE_SHORTCUTS_IMPL	(__ON__)

/*
  Description: Dedicated key could be set as shortcuts.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_SHORTCUTS.doc
*/
#define CFG_MMI_DEDICATED_KEY_SHORTCUTS	(__OFF__)

/*****************************************************************************
* Settings
    * Security Settings
        * Security Settings(Pluto)
*****************************************************************************/

/*
  Description: SLIM common option for security settings
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_SECSET_SLIM	(__OFF__)

/*****************************************************************************
* Settings
    * Theme Settings
        * Display Settings(Cosmos)
*****************************************************************************/

/*
  Description: Turn on Theme application
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_THEME
*/
#define CFG_MMI_THEMES_APPLICATION	(__OFF__)

/*****************************************************************************
* Settings
    * User Profiles
*****************************************************************************/

/*
  Description: split message tone to MMS/SMS/EMAIL/VOICE tones seperately.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_USER_PROFILES_07B_LATEST.doc
*/
#define CFG_MMI_PROF_SPLIT_MSG_TONES	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_PROF_ADD_DEL_PROF_SUPPORT	(__OFF__)

/*
  Description: remove power on / off tone and do not play power on / off tone.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_USER_PROFILES_07B_LATEST.doc
*/
#define CFG_MMI_POWER_ON_OFF_MUTE	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_POWER_ON_OFF_NO_CUSTOMIZE	(__ON__)

/*
  Description: SLIM common option for Profiles
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_PROF_SLIM	(__ON__)

/*
  Description: This feature is for Slim profiles, it will remove some of rarely used profile setting like Message volume and alert tone.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MT6261-profile-SLIM_Feature_Options.ppt
*/
#define CFG_MMI_PROF_SLIM_PROFILES	(__ON__)

/*****************************************************************************
* Telephony
    * Call Logs
*****************************************************************************/

/*
  Description: To support MMI call cost
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_CALLLOG.doc
*/
#define CFG_MMI_CLOG_CALL_COST	(__OFF__)

/*
  Description: To turn on call time feature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_CALLLOG.doc
*/
#define CFG_MMI_CLOG_CALL_TIME	(__OFF__)

/*
  Description: to turn on GPRS counter feature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_CALLLOG.doc
*/
#define CFG_MMI_CLOG_GPRS_COUNT	(__OFF__)

/*
  Description: to support mark/unmark several calllog to delete
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_CALLLOG.doc
*/
#define CFG_MMI_CLOG_MARK_SEVERAL	(__OFF__)

/*
  Description: To turn on Phonebook name sync feature in CalLLogSrv,suggestion only turn off this  on ultra low cost project if code size is so urgent.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_CALLLOG.doc
*/
#define CFG_MMI_CLOG_PHB_SYNC_SUPPORT	(__ON__)

/*
  Description: to turn on the featue of accumulate missed call before view even reboot
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_CALLHISTORY.doc
*/
#define CFG_MMI_CLOG_REBOOT_NO_UNREAD_SUPPORT	(__OFF__)

/*
  Description: Add CFG for CMCC TD-calllog select SIMx logs
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: calllog APP DD
*/
#define CFG_MMI_CLOG_SIM_FILTER	(__OFF__)

/*
  Description: to turn on SIM sync in CallLog
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_SRV_CALLLOG.doc
*/
#define CFG_MMI_CLOG_SIM_SYNC_SUPPORT	(__OFF__)

/*
  Description: SLIM common option for Call log
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: provide after 32MP
*/
#define CFG_MMI_CLOG_SLIM	(__ON__)

/*
  Description: CalllogSrv Rewrite for MT6261
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MT6261-calllogs-SLIM_Feature_Options.ppt
*/
#define CFG_MMI_CLOG_SLIM_FOR_MT6261	(__ON__)

/*
  Description: to turn on SMS counter feature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_CALLLOG.doc
*/
#define CFG_MMI_CLOG_SMS_COUNT	(__OFF__)

/*
  Description: to turn on tab style for call log
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_CALLHISTORY.doc
*/
#define CFG_MMI_CLOG_TAB_SUPPORT	(__OFF__)

/*****************************************************************************
* Telephony
    * Call Management
*****************************************************************************/

/*
  Description: Display cause of no CLI
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_GCALL_SRV.doc
*/
#define CFG_MMI_UCM_DISPLAY_CAUSE_OF_NO_CLI	(__OFF__)

/*
  Description: Hide SAT MO number if alpha id 2 is NULL or empty
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_GCALL_SRV.doc
*/
#define CFG_MMI_UCM_HIDE_SAT_MO_NUMBER	(__OFF__)

/*
  Description: Support number type information for incoming call, includes mobile, home, office, fax
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MMI_FRS_UCM_30.doc
*/
#define CFG_MMI_UCM_NUMBER_TYPE	(__OFF__)

/*
  Description: Post action for mo failure
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MMI_FRS_UCM_30.doc
*/
#define CFG_MMI_UCM_MO_FAIL_POST_ACTION	(__OFF__)

/*
  Description: GSM cipher support. If not ciphered network, it will show an icon to user
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SAP_NW_Info.chm
*/
#define CFG_MMI_NETWORK_CIPHER_SUPPORT	(__OFF__)

/*
  Description: Call deflect function, when there is incoming call, there may be option to deflect it to another number
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MMI_FRS_UCM_30.doc
*/
#define CFG_MMI_UCM_DEFLECT	(__OFF__)

/*
  Description: Explicit call transfer function, this function is to merge two individual calls together and leave.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MMI_FRS_UCM_30.doc
*/
#define CFG_MMI_UCM_ECT	(__OFF__)

/*
  Description: Call related SS. End user could do some actions for current active call(or incoming call)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_SRV_UCM.doc
*/
#define CFG_MMI_UCM_SHORT_STIRNG_CRSS	(__OFF__)

/*
  Description: Show the detail error information for different error causes.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_SRV_UCM.doc
*/
#define CFG_MMI_UCM_DETAIL_ERROR_MSG	(__OFF__)

/*
  Description: When there is USSD message, MS should display tone to notify user.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_CALLSETUP.doc
*/
#define CFG_MMI_RECEIVE_USSD_TONE	(__OFF__)

/*
  Description: Users can reply their choices directly in the USSR screen.But currenly no support for UCS2 input type
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_USSD_REPLY_IN_SAME_SCREEN	(__OFF__)

/*
  Description: UCM notify timeout as 5 seconds,
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MMI_FRS_UCM_30.doc
*/
#define CFG_MMI_UCM_NOTIFY_TIMEOUT_5S	(__OFF__)

/*
  Description: Show call indicator on the status bar (includes call state) when it is in-call,
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MMI_FRS_UCM_30.doc
*/
#define CFG_MMI_CALL_INDICATOR	(__OFF__)

/*
  Description: UCM auto answer notification support,
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MMI_FRS_UCM_30.doc
*/
#define CFG_MMI_UCM_AUTO_ANSWER_NOTIFICATION	(__ON__)

/*
  Description: use category 20 to display in-call screen on HVGA project,
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MMI_FRS_UCM_30.doc
*/
#define CFG_MMI_UCM_SINGLE_CALL_SCREEN_ENHANCE	(__OFF__)

/*
  Description: The desing of MUTE on RSK,
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MMI_FRS_UCM_30.doc
*/
#define CFG_MMI_UCM_RSK_MUTE	(__OFF__)

/*
  Description: The desing of SILENT on RSK for incoming call,
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MMI_FRS_UCM_30.doc
*/
#define CFG_MMI_UCM_RSK_SUPPRESS_RING	(__OFF__)

/*
  Description: SLIM common option for UCM
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: provide after 32MP
*/
#define CFG_MMI_UCM_SLIM	(__ON__)

/*
  Description: Connect notice setting. Play connect tone when the call is connected.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_CALL_SETTING.doc
*/
#define CFG_MMI_CONNECT_NOTICE	(__OFF__)

/*
  Description: Read Message during VT call
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: UCM DD
*/
#define CFG_MMI_UCM_VT_MSG	(__OFF__)

/*
  Description: BTBOX notify when bt disconnect
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_BTDIALER.pptx
*/
#define CFG_MMI_UCM_BT_CALL_RECORDER	(__OFF__)

/*
  Description: Can end all calls to dial ECC
  Option: [__ON__, __AUTO__, __OFF__]
  Reference: FRS_APP_UCM3.0_11B.vsd
*/
#define CFG_MMI_UCM_ECC_BEST_EFFORT	(__ON__)

/*****************************************************************************
* Telephony
    * Call Management
        * UCM(Pluto)
*****************************************************************************/

/*****************************************************************************
* Telephony
    * Call Management
        * UCM(Service)
*****************************************************************************/

/*
  Description: To support battery icon display in the iphone
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Battery support feature(IOS).pptx
*/
#define CFG_MMI_HF_BAT_SUPPORT	(__ON__)

/*
  Description: To support One key SOS
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: One_Key_SOS_v1.4.pptx
*/
#define CFG_MMI_ONE_KEY_SOS_SUPPORT	(__OFF__)

/*****************************************************************************
* Telephony
    * Dialer
        * Dialer(Cosmos)
*****************************************************************************/

/*
  Description: Dialer slim
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_DIALER.ppt
*/
#define CFG_MMI_DIALER_SLIM	(__ON__)

/*****************************************************************************
* Telephony
    * Dialer
        * Dialer(Pluto)
*****************************************************************************/

/*
  Description: Search matched phonebook and call log entries from dialer screen
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_PHONEBOOK.doc
*/
#define CFG_MMI_DIALER_SEARCH	(__OFF__)

/*
  Description: add mmi option for dialer app in wearable device
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_WATCH_NativeAPP_Dialer.ppt
*/
#define CFG_MMI_WEARABLE_DEVICE_DIALER	(__OFF__)

/*****************************************************************************
* Telephony
    * Network Info
*****************************************************************************/

/*****************************************************************************
* Telephony
    * Network Info
        * Idle Message(Pluto)
*****************************************************************************/

/*
  Description: Prompt invalid SIM message on Idle screen if network reject the SIM.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_NW_INFO_INVALID_SIM_MESSAGE	(__OFF__)

/*****************************************************************************
* Telephony
    * Network Info
        * Operator Name(Service)
*****************************************************************************/

/*
  Description: EONS: enhance operator name serviceit can be disable in china area for slim project
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: PRST_APP_IDLE_06B_09B.ppt
*/
#define CFG_MMI_EONS_SRV	(__OFF__)

/*****************************************************************************
* Telephony
    * SIM
*****************************************************************************/

/*
  Description: Support to read MExE files from SIM (Java used only)
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_SAT.doc
*/
#define CFG_MMI_MExE_SUPPORT	(__OFF__)

/*
  Description: SLIM common option for SIM status control process
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_SIM_CTRL_SLIM	(__OFF__)

/*
  Description: SIM-ME-Lock support in MMI
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_SIM_ME_LOCK.doc
*/
#define CFG_MMI_SML_MENU	(__OFF__)

/*****************************************************************************
* WiFi
    * WiFi Direct
        * WiFi(Pluto)
*****************************************************************************/

/*
  Description: WLAN Over-The-Air provisioning. This option turns on the support for a proprietary spec. This option should not be used together with __MMI_WLAN_OTAP_OMAEXT__.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_DataAccount_WLAN for WLAN OTAP part
*/
#define CFG_MMI_WLAN_OTAP_DMP	(__OFF__)

/*****************************************************************************
* WiFi
    * WiFi Direct
        * WiFi(Service)
*****************************************************************************/

/*****************************************************************************
* Others
*****************************************************************************/

/*
  Description: define the mot app support phone drive or not
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VAPP_MOVIE_THEATER.pptx
*/
#define CFG_MMI_COSMOS_MOT_NO_USER_DRIVE	(__OFF__)

/*
  Description: BLE Apple notification center service support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_BLE_ANCS_SUPPORT	(__OFF__)

/*
  Description: GSM call UI support
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_GSM_CALL_SUPPORT	(__ON__)

/*
  Description: Content Adaptive Backlight Control (CABC) of supported LCMs can save energy by dynamically adjust the backlight brightness according to the current display content. For example, we can use moving picture mode for video recorder and video player, still picture mode for image viewer.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: CABC.ppt
*/
#define CFG_MMI_CABC	(__OFF__)

/*
  Description: CU2.0 required feature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: CU2.0 customization spec
*/
#define CFG_MMI_PUSH_TURN_ON_OFF_SWITCH	(__OFF__)

/*
  Description: Config Save Bookmark function in Venus Email/SMS/MMS App
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: HLD_bookmark_cui.ppt
*/
#define CFG_MMI_VUI_SAVE_BOOKMARK_SUPPORT	(__OFF__)

/*
  Description: This feature was used to convert a solar day to the corresponding lunar day, or convert a lunar day to  the solar day, it also can query the solar/lunar info of a given festival or solar terms.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_lunarquery.doc
*/
#define CFG_MMI_LUNAR_QUERY	(__OFF__)

/*
  Description: enable BLE FMP APP
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_BLE_FMP_SUPPORT	(__OFF__)

/*
  Description: 3D application. It provides 3D UI to launch other multimedia app.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DETF_DD_3D_Media_Center.pptx
*/
#define CFG_MMI_3D_MEDIA_CENTER	(__ON__)

/*
  Description: enable BLE TIP APP
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_BLE_TIP_SUPPORT	(__OFF__)

/*
  Description: enable BLE Low power control feature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_BLE_LOW_POWER	(__OFF__)

/*
  Description: MMI support push notification UI, including Badge, NCenter,Pop-up, Notification on status bar.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Push notification presentation.pptx
*/
#define CFG_MMI_PNS	(__AUTO__)

/*
  Description: Support SNS MRE VPP version check and upgrade mechanism
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SNS_Update_Service_Proposal.pptx
*/
#define CFG_MMI_SNS_VPP_UPGRADE	(__AUTO__)

/*
  Description: Enable vCard feature
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_VOJECT.doc
*/
#define CFG_MMI_VCARD	(__OFF__)

/*
  Description: TEL; VOICE will not import to cell number
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_VOJECT.doc
*/
#define CFG_MMI_VCARD_TEL_VOICE_CELL_DIFFERENT	(__OFF__)

/*
  Description: enable or disable Intergrafx's live wallpaper and games
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Intergrafx_Livewallpaper_and_Game.docx
*/
#define CFG_MMI_3D_GAME_INTERGRAFX_TOWER	(__AUTO__)

/*
  Description: enable or disable Intergrafx's live wallpaper and games
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Intergrafx_Livewallpaper_and_Game.docx
*/
#define CFG_MMI_3D_GAME_INTERGRAFX_CG_FROM_FILE	(__AUTO__)

/*
  Description: Native Game
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: fp_nativegame.doc
*/
#define CFG_MMI_GAME_FROGCANDY	(__OFF__)

/*
  Description: Native Game
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: fp_nativegame.doc
*/
#define CFG_MMI_GAME_TOPGUN	(__OFF__)

/*
  Description: enable or disable Intergrafx's live wallpaper and games
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Intergrafx_Livewallpaper_and_Game.docx
*/
#define CFG_MMI_3D_GAME_INTERGRAFX_TANKFANTASY	(__AUTO__)

/*
  Description: enable or disable Intergrafx's live wallpaper and games
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Intergrafx_Livewallpaper_and_Game.docx
*/
#define CFG_MMI_3D_GAME_INTERGRAFX_CUBEWORLD	(__AUTO__)

/*
  Description: Native Game
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: fp_nativegame.doc
*/
#define CFG_MMI_GAME_NINJACLIMB	(__OFF__)

/*
  Description: Native Game
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: fp_nativegame.doc
*/
#define CFG_MMI_GAME_DIAMOND	(__OFF__)

/*
  Description: enable or disable Intergrafx's live wallpaper and games
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Intergrafx_Livewallpaper_and_Game.docx
*/
#define CFG_MMI_3D_GAME_INTERGRAFX_JUMPEMPEROR	(__AUTO__)

/*
  Description: enable or disable Intergrafx's live wallpaper and games
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Intergrafx_Livewallpaper_and_Game.docx
*/
#define CFG_MMI_3D_GAME_INTERGRAFX_NO_CG	(__OFF__)

/*
  Description: Native Game
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: fp_nativegame.doc
*/
#define CFG_MMI_GAME_FRUITNINJA	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_3D_GAME_INTERGRAFX	(__AUTO__)

/*
  Description: enable or disable Intergrafx's live wallpaper and games
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Intergrafx_Livewallpaper_and_Game.docx
*/
#define CFG_MMI_3D_GAME_INTERGRAFX_DANCING	(__AUTO__)

/*
  Description: Native Game
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: fp_nativegame.doc
*/
#define CFG_MMI_GAME_TRUEMAN	(__OFF__)

/*
  Description: enable BLE PXP APP
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_BLE_PXP_SUPPORT	(__OFF__)

/*
  Description: To switch the Hyperlink item displayed in MyFavorite VIDEO Folder
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_MY_FAVORITE.doc
*/
#define CFG_MMI_MY_FAVORITE_VIDEO_HYPERLINK	(__OFF__)

/*
  Description: To switch the image menu item displayed in MyFavorite main screen
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_MY_FAVORITE.doc
*/
#define CFG_MMI_MY_FAVORITE_IMAGES	(__AUTO__)

/*
  Description: To switch the Hyperlink item displayed in MyFavorite Audio Folder
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_MY_FAVORITE.doc
*/
#define CFG_MMI_MY_FAVORITE_AUDIO_HYPERLINK	(__OFF__)

/*
  Description: To switch the Hyperlink item displayed in JavaMenu screen
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_MY_FAVORITE.doc
*/
#define CFG_MMI_MY_FAVORITE_JAVA_HYPERLINK	(__OFF__)

/*
  Description: To switch the others menu item displayed in MyFavorite main screen
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_MY_FAVORITE.doc
*/
#define CFG_MMI_MY_FAVORITE_OTHERS	(__AUTO__)

/*
  Description: To switch the memory card menu item displayed in MyFavorite main screen
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_MY_FAVORITE.doc
*/
#define CFG_MMI_MY_FAVORITE_MEMORYCARD	(__AUTO__)

/*
  Description: To switch the mmsbox menu item displayed in MyFavorite main screen
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_MY_FAVORITE.doc
*/
#define CFG_MMI_MY_FAVORITE_MMSBOX	(__AUTO__)

/*
  Description: To switch the Hyperlink item displayed in MyFavorite OTHERS Folder
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_MY_FAVORITE.doc
*/
#define CFG_MMI_MY_FAVORITE_OTHERS_HYPERLINK	(__OFF__)

/*
  Description: To switch the Hyperlink item displayed in MyFavorite Animation Folder
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_MY_FAVORITE.doc
*/
#define CFG_MMI_MY_FAVORITE_SWFLASH_HYPERLINK	(__OFF__)

/*
  Description: To switch the theme menu item displayed in MyFavorite main screen
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_MY_FAVORITE.doc
*/
#define CFG_MMI_MY_FAVORITE_THEME	(__AUTO__)

/*
  Description: To switch the audio menu item displayed in MyFavorite main screen
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_MY_FAVORITE.doc
*/
#define CFG_MMI_MY_FAVORITE_AUDIO	(__AUTO__)

/*
  Description: To switch the Hyperlink item displayed in MyFavorite MMSBOX Folder
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_MY_FAVORITE.doc
*/
#define CFG_MMI_MY_FAVORITE_MMSBOX_HYPERLINK	(__OFF__)

/*
  Description: Support press menu key(KEY_ENTER) to launch WAP application in the idle screen directly
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_BROWSER_07A_latest.doc
*/
#define CFG_MMI_WITH_WAP_KEY	(__OFF__)

/*
  Description: To switch the Hyperlink item displayed in MyFavorite Images Folder
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_MY_FAVORITE.doc
*/
#define CFG_MMI_MY_FAVORITE_IMAGES_HYPERLINK	(__OFF__)

/*
  Description: To switch the g+ game menu item displayed in MyFavorite main screen
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_MY_FAVORITE.doc
*/
#define CFG_MMI_MY_FAVORITE_GPLUSGAME	(__OFF__)

/*
  Description: To switch the javabox menu item displayed in MyFavorite main screen
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_MY_FAVORITE.doc
*/
#define CFG_MMI_MY_FAVORITE_JAVABOX	(__AUTO__)

/*
  Description: To switch the Hyperlink item displayed in MyFavorite THEME Folder
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_MY_FAVORITE.doc
*/
#define CFG_MMI_MY_FAVORITE_THEME_HYPERLINK	(__OFF__)

/*
  Description: To switch the video menu item displayed in MyFavorite main screen
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: FRS_APP_MY_FAVORITE.doc
*/
#define CFG_MMI_MY_FAVORITE_VIDEO	(__AUTO__)

/*
  Description: Composer will save msg unsaved copy in draft on Home key press.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_APP_UNIFIEDCOMPOSER.doc
*/
#define CFG_MMI_COSMOS_UC_END_KEY_SAVE_SUPPORT	(__OFF__)

/*
  Description: enable BLE ANP APP
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: n/a
*/
#define CFG_MMI_BLE_ANP_SUPPORT	(__OFF__)

/*
  Description: Disable ASM 2.0
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: MT6261-ASMv2-SLIM_Feature_Options.ppt
*/
#define CFG_MMI_SUPPORT_ASMV2	(__ON__)

/*
  Description: slim for sat
  Option: [__ON__, __AUTO__, __OFF__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_SAT_ULTRA_SLIM	(__OFF__)

/*
  Description: To support brief string prompt
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SLIM UE/UI General Guideline
*/
#define CFG_MMI_BRIEF_TEXT	(__ON__)

/*
  Description: In Slim project, there is less memory and cause OOM screen appear more often than non-slim project.This option is to turn OOM Auto kill on.When OOM Auto kill is turned on, when out of memory, FW will auto kill application without interrupt User.
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: Cosmos_Slim_OOM_Proposal.pptx
*/
#define CFG_MMI_ASM_OOM_AUTO_KILL	(__OFF__)

/*
  Description: To support the most basic UI display and UE behavior
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: SLIM UE/UI General Guideline
*/
#define CFG_MMI_BASIC_UI_STYLE	(__ON__)

/*
  Description: bootup slim
  Option: [__ON__, off.auto]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_BOOTUP_DISK_CHECK_SLIM	(__OFF__)

/*
  Description: cosmos slim
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_MMI_COSMOS_APP_MANAGER	(__OFF__)

/*
  Description: Platform context
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_VFX_FW.pptx
*/
#define CFG_MMI_VUI_PLATFORM_CONTEXT_SLIM	(__OFF__)

/*
  Description: 
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: DD_PLUTO_3232_SLIM.doc
*/
#define CFG_MMI_MATV_SLIM	(__OFF__)

/*
  Description: Cosmos music player cover flow page
  Option: [__ON__, __OFF__, __AUTO__]
  Reference: 
*/
#define CFG_COSMOS_MUSICPLY_COVER_FLOW	(__ON__)

#endif /* __MMI_FEATURES_SWITCH_H__ */
