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

/*******************************************************************************
 * Filename:
 * ---------
 *  mmi_menu_handlers.h
 *
 * Project:
 * --------
 *   MAUI
 *
 * Description:
 * ------------
 *   Hilite handlers and Hint handlers of menuitems
 *
 * Author:
 * -------
 *  Resource Generator
 *
*==============================================================================
 *              HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
 *------------------------------------------------------------------------------
 * $Log$
 *
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
 *============================================================================== 
 *******************************************************************************/

#ifndef _MENUHANDLER_H
#define _MENUHANDLER_H

/* need typedef void (*FuncPtr) (void); before include this file */

/* #define MENU_HILITE_HANDLER_COUNT   36; */
/* #define MENU_HINT_HANDLER_COUNT     1; */

#include "mmi_rp_all_defs.h"
/* Extern functions of Hilite Handler */
extern void mmi_frm_highlight_inline_generic_done(void);
extern void mmi_frm_highlight_input_method_generic(void);
extern void DataConnectGSMHiliteHandler(void);
extern void mmi_fmgr_highlight_to_phb(void);
extern void mmi_fmgr_highlight_to_sms(void);
extern void mmi_fmgr_highlight_audio_play(void);
extern void highlight_mainmenu_connectivity(void);
extern void mmi_bt_main_hilight_handler(void);
extern void mmi_secset_main_menu_highlight_hdlr(void);
extern void mmi_imgview_highlight_app(void);
extern void HighlightWCMenu(void);
extern void HighlightWcBrowseCity(void);
extern void mmi_data_connection_sim_hilite_hdlr(void);
extern void DataConnectHiliteHandler(void);
extern void highlight_mainmenu_profiles(void);
extern void HighlightPhnsetScr(void);
extern void mmi_ime_settings_inputmethodsettings_highlight(void);
extern void HighlightRstScr(void);
extern void HighlightMreApps(void);
extern void mmi_highlight_netset_main(void);
extern void mmi_service_hilite_sat_hdlr(void);
extern void HighlightAlmMenu(void);
extern void mmi_ucm_highlight_call_type_voice(void);
extern void highlight_mainmenu_messages(void);
extern void highlight_mainmenu_filemngr(void);
extern void highlight_mainmenu_phonebook(void);
extern void highlight_mainmenu_funandgames(void);
extern void highlight_mainmenu_extra(void);
extern void highlight_mainmenu_calllog(void);
extern void highlight_mainmenu_multimedia(void);
extern void highlight_mainmenu_services(void);
extern void highlight_mainmenu_organizer(void);
extern void highlight_mainmenu_settings(void);
extern void highlight_mainmenu_settings(void);
extern void highlight_mainmenu_callcenter(void);
extern void highlight_mainmenu_tools(void);


/* Extern functions of Hint Handler */
extern void HintPhnsetPreferedInputMethod(U16);

const mmi_frm_hilite_hdlr_struct mmi_frm_const_hilite_hdlr_table[] = {
    {MENU_DONE_OPTION_ID, mmi_frm_highlight_inline_generic_done},
    {MENU_INPUT_METHOD_OPTION_ID, mmi_frm_highlight_input_method_generic},
    {SERVICES_DATA_CONNECT_MENU_ID, DataConnectGSMHiliteHandler},
    {MENU_ID_FMGR_FWD_CONTACT, mmi_fmgr_highlight_to_phb},
    {MENU_ID_FMGR_FWD_SMS, mmi_fmgr_highlight_to_sms},
    {MENU_ID_FMGR_AUD_OPTION_PLAY, mmi_fmgr_highlight_audio_play},
    {MENU_ID_CONNECTIVITY, highlight_mainmenu_connectivity},
    {MENU_CONN_BT_MAIN, mmi_bt_main_hilight_handler},
    {MENU_ID_SECSET_MAIN_MENU, mmi_secset_main_menu_highlight_hdlr},
    {MENU_ID_IMGVIEW_APP, mmi_imgview_highlight_app},
    {ORGANIZER_WORLDCLOCK_MENU, HighlightWCMenu},
    {MITEM_WORLDCLOCK_BROWSECITY, HighlightWcBrowseCity},
    {MENU_ID_DATA_CONNECTION_SIM, mmi_data_connection_sim_hilite_hdlr},
    {SERVICES_DATA_CONNECT_MAIN_MENU_ID, DataConnectHiliteHandler},
    {MAIN_MENU_PROFILES_MENUID, highlight_mainmenu_profiles},
    {MENU9102_INITIAL_SETUP, HighlightPhnsetScr},
    {MENU_SETTING_PREFERED_INPUT_METHOD, mmi_ime_settings_inputmethodsettings_highlight},
    {MENU_SETTING_RESTORE, HighlightRstScr},
    {MENU_ID_SETTING_MREAPPS, HighlightMreApps},
    {MENU_ID_NETSET_MAIN, mmi_highlight_netset_main},
    {MENU_ID_SAT1_ENTRY, mmi_service_hilite_sat_hdlr},
    {ORGANIZER_ALARM_MENU, HighlightAlmMenu},
    {MENU_ID_UCM_CALL_TYPE_VOICE, mmi_ucm_highlight_call_type_voice},
    {MAIN_MENU_MESSAGES_MENUID, highlight_mainmenu_messages},
    {MAIN_MENU_FILE_MNGR_MENUID, highlight_mainmenu_filemngr},
    {MAIN_MENU_PHONEBOOK_MENUID, highlight_mainmenu_phonebook},
    {MAIN_MENU_FUNANDGAMES_MENUID, highlight_mainmenu_funandgames},
    {MAIN_MENU_EXTRA_MENUID, highlight_mainmenu_extra},
    {MAIN_MENU_CALL_LOG, highlight_mainmenu_calllog},
    {MAIN_MENU_MULTIMEDIA_MENUID, highlight_mainmenu_multimedia},
    {MAIN_MENU_SERVICES_MENUID, highlight_mainmenu_services},
    {MAIN_MENU_ORGANIZER_MENUID, highlight_mainmenu_organizer},
    {MAIN_MENU_SETTINGS_MENUID, highlight_mainmenu_settings},
    {MAIN_MENU_SETTINGS_NO_SIM_MENUID, highlight_mainmenu_settings},
    {MAIN_MENU_CALL_CENTER, highlight_mainmenu_callcenter},
    {MAIN_MENU_TOOLS_MENUID, highlight_mainmenu_tools},
};

const mmi_frm_hint_hdlr_struct mmi_frm_const_hint_hdlr_table[] = {
    {MENU_SETTING_PREFERED_INPUT_METHOD, HintPhnsetPreferedInputMethod},
};

#endif /* _MENUHANDLER_H */ 
