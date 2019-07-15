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
 * Filename:
 * ---------
 * Custom_at_command.c
 *
 * Description:
 * ------------
 *   This file is intends for Customer to implement and parse its own defined AT commands
 *
 * Author:
 * -------
 * -------
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
*****************************************************************************/
//#include "kal_release.h"
//#include "kal_non_specific_general_types.h"
#include "stdio.h"
#include "string.h"
//#include "stack_config.h"	

#include "kal_general_types.h"
#include "kal_internal_api.h"
#include "ata_external.h"
#if (defined(__COMPOSITE_WEBCAM__))
#include "cal_api.h"
#include "cal_comm_def.h"
#endif
#ifdef __TWOMICNR_SUPPORT__
#include "two_mic_NR_custom_if.h" 
#endif

#if defined(__PLMN_LIST_WITH_CELL_INFO__)
#include "ps_public_struct.h"
#endif


#if defined(__FUNET_ENABLE__)
#include "FUNET.h"
#endif

extern void kal_monitor_buffer(kal_uint32 index);
extern kal_bool twomicnr_command_hdlr(char *full_cmd_string);
#if defined(__IOT_LOCK__)
extern kal_bool is_ata_port_flag; 
#endif
/*****************************************************************************
* CUSTOM_SYMBOL:
*	customer can modify this symbol.
*     Every command begin with this symbol will be recognized as a customer-defined command
*	and passed to custom_command_hdlr().
*     For example: if CUSTOM_SYMBOL is set to '^', 
*				then AT^AAAA, AT^BBBB will be customer-defined command.
*   	NOTE:  '+'  and '/' and ' \ 'is not allowed since they might be standard command format
*****************************************************************************/
#define CUSTOM_SYMBOL  '^'	 // '+'  and '/' and ' \ 'is NOT allowed   

/*****************************************************************************
* MAX_UART_LEN = 128 bytes.
*	when you write a lot of data to UART at the same time, 
*	UART's buffer might be full and cannot handle.
*     so the safer way is to seperate the long data, each time only write data length <= 128
*****************************************************************************/

kal_uint8 custom_get_atcmd_symbol(void);
kal_bool custom_command_hdlr(char *full_cmd_string);

/*****************************************************************************
* FUNCTION
*  	rmmi_write_to_uart()
* DESCRIPTION
*   	This function extern L4C RMMI function,
*     is to write data to UART
* PARAMETERS
*   	kal_uint8 * buffer 	- the data to be written
*	kal_uint16 length 	- the length of data to be written
*     kal_bool stuff 		- KAL_TRUE : <CR><LF> will be added at the beginning and end. (eg.<CR><LF>OK<CR><LF>)
*					   KAL_FALSE: no <CR><LF> is added
* RETURNS
*	none
*****************************************************************************/
extern void rmmi_write_to_uart(kal_uint8 * buffer, kal_uint16 length, kal_bool stuff); 

#ifdef __GATI_ENABLE__
extern kal_bool gati_command_hdlr(kal_uint8* cmd_string, kal_uint8* full_string);

module_type gati_mod_table[] = 
{
    MOD_PHB,
    MOD_L4C,
    MOD_L4C,
    MOD_L4C, 
    MOD_NIL         /* Need to be the last one */
};

kal_char *gati_cmd_table[] = 
{
    "CPBBA",
    "CPBBR",
    "CPBBS",
    "CPBB"
};

#endif

extern kal_bool gas_command_hdlr(kal_uint8* cmd_string, kal_uint8* full_string);

module_type gas_mod_table[] = 
{
#ifdef __GAS_SUPPORT__
#ifdef __TCPIP__
#ifndef __WIFI_SCAN_ONLY_AT_CMD__
    MOD_ABM,
#endif
#endif

    MOD_L4C,
    MOD_CSM,
#if defined(__BTMTK__)
    MOD_BT,
#endif
#endif
#if defined(__MRE_PACKAGE_FULL__) || defined(__MRE_PACKAGE_NORMAL__) || defined(__MRE_PACKAGE_SLIM__)   
    MOD_MMI,   
#endif
    MOD_NIL         /* Need to be the last one */
};

kal_char *gas_cmd_table[] = 
{
#ifdef __GAS_SUPPORT__
#ifdef __TCPIP__
#ifndef __WIFI_SCAN_ONLY_AT_CMD__
    "EWIFI",
#endif
#endif
    "CL4C",
    "CCSM",
#if defined(__BTMTK__)
    "EBTAT",
#endif
#endif
#if defined(__MRE_PACKAGE_FULL__) || defined(__MRE_PACKAGE_NORMAL__) || defined(__MRE_PACKAGE_SLIM__)
    "EMREAT",
#endif
};

typedef struct
{
	char *commandString;
	custom_rsp_type_enum (*commandFunc)(custom_cmdLine *commandBuffer_p);
} custom_atcmd;

custom_cmd_mode_enum custom_find_cmd_mode(custom_cmdLine *cmd_line);

custom_rsp_type_enum custom_test_func(custom_cmdLine *commandBuffer_p)
{
    custom_cmd_mode_enum result;
    custom_rsp_type_enum ret_value  = CUSTOM_RSP_ERROR;

    result = custom_find_cmd_mode(commandBuffer_p);		
    switch (result)
    {
        case CUSTOM_READ_MODE:
            ret_value = CUSTOM_RSP_OK;
            break;
        case CUSTOM_ACTIVE_MODE:
            ret_value = CUSTOM_RSP_OK;
            break;
        case CUSTOM_SET_OR_EXECUTE_MODE:
            ret_value = CUSTOM_RSP_OK;
            break;
        case CUSTOM_TEST_MODE:
            ret_value = CUSTOM_RSP_OK;
            break;    
        default:
            ret_value = CUSTOM_RSP_ERROR;
            break;
	}
    return ret_value;
}

#if defined(__FUNET_ENABLE__)
extern L4cuem_reboot_req(void);

//Add an at command for FOTA test, "AT+FOTA="
custom_rsp_type_enum custom_fota_test_func(custom_cmdLine *commandBuffer_p)
{
    custom_cmd_mode_enum result;
    custom_rsp_type_enum ret_value  = CUSTOM_RSP_ERROR;

    kal_prompt_trace(MOD_ATCI, "fota AT command handler enter.");
    result = custom_find_cmd_mode(commandBuffer_p);
    switch (result)
    {
        case CUSTOM_READ_MODE:
            ret_value = CUSTOM_RSP_OK;
            break;
        case CUSTOM_ACTIVE_MODE:
            ret_value = CUSTOM_RSP_OK;
            break;
        case CUSTOM_SET_OR_EXECUTE_MODE:
        case CUSTOM_TEST_MODE:
            ret_value = CUSTOM_RSP_OK;  
            kal_prompt_trace(MOD_ATCI, "reboot device.");
            FUNET_TriggerDL(NULL, FUNET_UPDATE_FULL);
            l4cuem_reboot_req();
            break;    
        default:
            ret_value = CUSTOM_RSP_ERROR;
            break;
    }
    return ret_value;
}
#endif /* __FUNET_ENABLE__ */

/********************************
* The following table is used for the customer
* They can defined their own command and 
* corresponding handler function here
* Note that the last line {NULL, NULL} should not be removed
* since it is the terminator indicator
*********************************/
const custom_atcmd custom_cmd_table[ ] =
{    
    {"AT%CUSTOM",custom_test_func},

#if defined(__FUNET_ENABLE__)
    {"AT+FOTA",custom_fota_test_func},
#endif

#if defined(__ATA_SUPPORT__) && defined(__MTK_TARGET__)
	#if (defined(__MSDC_SD_MMC__)|| defined(__MSDC2_SD_MMC__))
						{"AT^MSDC",ata_t_card_hdlr_v1}, 		  //T Card
	#endif
				
						{"AT+EMVI",ata_vibrator_hdlr_v1},	//BLEST  now		  //Vibrator
				
	#if (defined(FM_RADIO_ENABLE))	
						{"AT+EMFM",ata_fm_hdlr_v1}, 			  //FM
	#endif
				
	#if defined(TOUCH_PANEL_SUPPORT) && defined(TOUCH_PANEL_INTERNAL)
						{"AT+ETPID",ata_tp_hdlr_v1},			  //TouchPanel
	#endif
				
	#if defined(ISP_SUPPORT)
						{"AT+ECMFP",ata_camera_hdlr_v1},		  //camera
	#endif
				
	#if defined(__ATV_SUPPORT__)
						{"AT+EMATV",ata_matv_hdlr_v1},				//Matv
						{"AT+EMATVP",ata_matv_video_hdlr_v1},				//Matv video	
	#endif
				
	#if defined(NORMAL_KEYPAD)|| defined(REDUCED_KEYPAD)|| defined(QWERTY_KEYPAD)
						{"AT+EKPT",ata_kpt_hdlr_v1},			  //Keypad Test
						{"AT+EKPTV2",ata_kpt_hdlr_v2},			  //Keypad Test
	#endif

	#if defined(TOUCH_PANEL_SUPPORT)
						{"AT+ETPV2",ata_tp_hdlr_v2},             //TP Test
	#endif
	
	#if defined(__LCD_SUPPORT__)
						{"AT+ETPUI",ata_tp_ui_hdlr},			  //TP UI
						{"AT+ELCMV2",ata_lcm_hdlr_v2},			  //LCM
	#endif
						//{"AT+EMAUDIO",ata_audio_hdlr_v1},			  //Audio
						{"AT+ELED",ata_led_hdlr},			   //LED 
						{"AT+ELEDT",ata_led_tsem_hdlr},		   //LED take sem
						{"AT+ELEDG",ata_led_gsem_hdlr},		   //LED give sem
						{"AT+ELCM",ata_lcm_hdlr},			   //LCM
						{"AT+EMBKL",ata_bkl_hdlr},			   //Backlight
	#if 0//!defined(SIM_NOT_PRESENT)
						{"AT+ESIMV2",ata_sim_hdlr_v2},			  //SIM Test
	#endif
						{"AT+ECUSLCD",ata_customer_lcd_hdlr},			  //LCD
						{"AT+ELEDV2",ata_led_hdlr_v2},			  //LED //LED2
						{"AT+ELEDV1",ata_led_hdlr_v1},			  //LED //LED1
						
						{"AT+EGPIOT",ata_lock_hdlr},	
						{"AT+EMAUDIO",ata_beep_hdlr},	
						{"AT+EMAUDSTOP",ata_beep_stop_hdlr},	
						{"AT+EM500HZ",ata_500hz_hdlr},	
						{"AT+EM1000HZ",ata_1000hz_hdlr},	
						{"AT+EM3000HZ",ata_3000hz_hdlr},	
						{"AT+EGGPS",ata_gps_hdlr},	
						{"AT+EGSENSOR",ata_Gsensor_hdlr},
						{"AT+ESIMV2",ata_Sim_hdlr},
						{"AT+ECHARGE",ata_Charge_hdlr},
						{"AT+ESPCHECK",ata_Speakercheck_hdlr},
						{"AT+ELED1CHECK",ata_Led1check_hdlr},
						{"AT+ELED2CHECK",ata_Led2check_hdlr},
						{"AT+ELADC",ata_Ladc_hdlr}, //
						{"AT+ETADC",ata_Tadc_hdlr}, //
						{"AT+ETEMP",ata_Temp_hdlr},//
#endif/*__ATA_SUPPORT__ && __MTK_TARGET__*/

    {NULL, NULL}  // this lind should not be removed, it will be treat as 
};

/*****************************************************************************
* FUNCTION
*     custom_find_cmd_mode()
* DESCRIPTION
*     This function is used to parsing the command mode for the customer
*     The input position of the cmd_line should stay at the character right after the command name
* PARAMETERS
*     cmd_line      the custom_cmdLine which contains the command string and its current parsing position
* RETURNS
*     custom_cmd_mode_enum
*****************************************************************************/
custom_cmd_mode_enum custom_find_cmd_mode(custom_cmdLine *cmd_line)
{
    custom_cmd_mode_enum result;

    if (cmd_line->position < cmd_line->length - 1)
    {
        switch (cmd_line->character[cmd_line->position])
        {
            case '?':  /* AT+...? */
            {
                cmd_line->position++;
                result = CUSTOM_READ_MODE;
                break;
            }
            case '=':  /* AT+...= */
            {
                cmd_line->position++;
                if ((cmd_line->position < cmd_line->length - 1 ) &&
                    (cmd_line->character[cmd_line->position] == '?'))
                {
                    cmd_line->position++;
                    result = CUSTOM_TEST_MODE;
                }
                else
                {
                    result = CUSTOM_SET_OR_EXECUTE_MODE;
                }
                break;
            }
            default:  /* AT+... */
            {
                result = CUSTOM_ACTIVE_MODE;
                break;
            }
        }
    }
    else
    {
        result = CUSTOM_ACTIVE_MODE;
    }
    return (result);
}

/*****************************************************************************
* FUNCTION
*  	custom_command_hdlr()
* DESCRIPTION
*   	This function should parse the custom AT command and do correspondent action.
*     Customer should maintain and modify the code.
* PARAMETERS
*   	kal_uint8 * cmd_string
* RETURNS
*    KAL_TRUE : the command is handled by the customer
*    KAL_FALSE: the command is not handled by the customer
*****************************************************************************/
kal_bool custom_command_hdlr(char *full_cmd_string)
{
    char buffer[MAX_UART_LEN+1]; //MAUI_02377056
    char *cmd_name, *cmdString;
    kal_uint8 index = 0; 
    kal_uint16 length;
    kal_uint16 i;
    custom_cmdLine command_line;

    cmd_name = buffer;

    length = strlen(full_cmd_string);
    length = length > MAX_UART_LEN ? MAX_UART_LEN : length;    
    while ((full_cmd_string[index] != '=' ) &&  //might be TEST command or EXE command
        (full_cmd_string[index] != '?' ) && // might be READ command
        (full_cmd_string[index] != 13 ) && //carriage return
        index < length)  
    {
        cmd_name[index] = full_cmd_string[index] ;
        index ++;
    }
    cmd_name[index] = '\0' ;    

    //ata test tool
#if defined(__IOT_LOCK__)
    ata_srv_app_notify_cb(cmd_name,strlen(cmd_name));

	if(is_ata_port_flag==KAL_TRUE)
	{
		is_ata_port_flag=KAL_FALSE;
        return KAL_TRUE;
	}
	//end
#endif

	
    for (i = 0 ; custom_cmd_table[i].commandString != NULL; i++ )
    {
        cmdString = custom_cmd_table[i].commandString;
        if (strcmp(cmd_name, cmdString) == 0 )
        {
            strncpy(command_line.character, full_cmd_string, COMMAND_LINE_SIZE + NULL_TERMINATOR_LENGTH);
            command_line.character[COMMAND_LINE_SIZE] = '\0';
            command_line.length = strlen(command_line.character);
            command_line.position = index;
            if (custom_cmd_table[i].commandFunc(&command_line) == CUSTOM_RSP_OK) 
            {
                sprintf(buffer, "OK");
                rmmi_write_to_uart((kal_uint8*)buffer, strlen(buffer), KAL_TRUE);
            }
            else
            {
                sprintf(buffer, "ERROR");
                rmmi_write_to_uart((kal_uint8*)buffer, strlen(buffer), KAL_TRUE);
            }
            return KAL_TRUE;
        }
    }    

    if (index <= 2)
        return KAL_FALSE;
	
    /* just a very basic example : customer can implement their own */
    cmd_name += 3;
    if (strcmp(cmd_name, "EXAMPLE") == 0)
    {		
        /* BEGIN: do the following parsing and correspondent action */
        /*  												    */
        /*  												    */
        /*  												    */
        /* END: do the following parsing and correspondent action    */

        /* generate final result code: "OK" or "ERROR" */
        if(KAL_TRUE)    // if operation is success
        {
                sprintf(buffer, "OK");
                rmmi_write_to_uart((kal_uint8*)buffer, strlen(buffer), KAL_TRUE);
        }
        else if (KAL_FALSE) // if operation is fail
        {
            sprintf(buffer, "ERROR");
            rmmi_write_to_uart((kal_uint8*)buffer, strlen(buffer), KAL_TRUE);
        }
        return KAL_TRUE;
    }
    #if !defined(__MMI_FMI__) || defined(WISDOM_MMI)
    else if (strcmp(cmd_name, "buffer") == 0)
    {		
        kal_print("Buffer Monitor enabled!");
        kal_monitor_buffer(0xffffffff);		
        sprintf(buffer, "OK");
        rmmi_write_to_uart((kal_uint8*)buffer, strlen(buffer), KAL_TRUE);

        return KAL_TRUE;
    }	
    #endif	
    #ifdef __TWOMICNR_SUPPORT__ 
    else if (twomicnr_command_hdlr(full_cmd_string) == KAL_TRUE)
    {
	return KAL_TRUE;
    }
    #endif
    #if (defined(__COMPOSITE_WEBCAM__)) 
    else if (strcmp(cmd_name, "SENSOR") == 0)
    {
        CAL_FEATURE_CTRL_STRUCT CalInPara;
        CalInPara.FeatureId = CAL_FEATURE_CAMERA_TUNING_SENSOR;
        CalInPara.FeatureSetValue = (kal_uint32)(full_cmd_string);
        CalCtrl(CAL_FEATURE_CTRL, (void*)&CalInPara, NULL, 0, NULL);
        return KAL_TRUE;
    }
    #endif
    else
    {
        if( gas_command_hdlr( (kal_uint8*)cmd_name, (kal_uint8*)full_cmd_string)==KAL_TRUE )
        {
            // it is a gati command and we will send the command to the appropriate module
            return KAL_TRUE;
        }
    #ifdef __GATI_ENABLE__ 
        /* Judge if the command string is a GATI command*/
        if( gati_command_hdlr( (kal_uint8*)cmd_name, (kal_uint8*)full_cmd_string)==KAL_TRUE )
        {
            // it is a gati command and we will send the command to the appropriate module
            return KAL_TRUE;
        }		 	
    #endif
    }	
		 
    /* unrecognized command */
    /* we should return KAL_FALSE to let ATCI judge if the it can handle the command */
    return KAL_FALSE;
	
}

/*****************************************************************************
* FUNCTION
*  	custom_get_atcmd_symbol()
* DESCRIPTION
*   	This function returns special symbol for customer-defined AT command, 
*   	so AT parser can recognize its a custom command and forward the string to custom_command_handler().
*
*     CUSTOMER DOES NOT need to modify this function.
* PARAMETERS
*   	none
* RETURNS
*     kal_uint8 
*****************************************************************************/
kal_uint8 custom_get_atcmd_symbol(void)
{
   return (CUSTOM_SYMBOL);
}

/*****************************************************************************
* USER DEFINE CONSTANT
*  	RMMI_CUSTOM_DCD_VALUE_IN_DATA_STATE
* DESCRIPTION
* 	1. This value defines the control DCD value for data mode (CSD/GPRS dialup)
*   2. CUSTOMER CAN modify this value accroding to its TE requirement
*****************************************************************************/
#define RMMI_CUSTOM_DCD_VALUE_IN_DATA_STATE (1)

/*****************************************************************************
* USER DEFINE CONSTANT
*  	RMMI_CUSTOM_DCD_VALUE_IN_CMD_STATE
* DESCRIPTION
* 	1. This value defines the control DCD value for AT command mode (Normal/Escaped AT)
*   2. CUSTOMER CAN modify this value accroding to its TE requirement
*****************************************************************************/
#define RMMI_CUSTOM_DCD_VALUE_IN_CMD_STATE (0)

/*****************************************************************************
* FUNCTION
*  	custom_get_dcd_value_for_data_state()
* DESCRIPTION
*   	This function returns the user-defined DCD value for data state
*
*     CUSTOMER DOES NOT need to modify this function.
* PARAMETERS
*   	none
* RETURNS
*     kal_uint8 
*****************************************************************************/
kal_uint8 custom_get_dcd_value_for_data_state(void)
{
    return (kal_uint8) RMMI_CUSTOM_DCD_VALUE_IN_DATA_STATE;
}

/*****************************************************************************
* FUNCTION
*  	custom_get_dcd_value_for_cmd_state()
* DESCRIPTION
*   	This function returns the user-defined DCD value for command state
*       It shall be inverted value of custom_get_dcd_value_for_data_state()
*     CUSTOMER DOES NOT need to modify this function.
* PARAMETERS
*   	none
* RETURNS
*     kal_uint8 
*****************************************************************************/
kal_uint8 custom_get_dcd_value_for_cmd_state(void)
{
    return (kal_uint8)RMMI_CUSTOM_DCD_VALUE_IN_CMD_STATE;
}

#ifdef __MOD_TCM__
/*****************************************************************************
* FUNCTION
*  	custom_get_gprs_dialup_connect_post_string()
* DESCRIPTION
*   This function returns the post string right after CONNECT in gprs dialup.
*
*   The return string length must be less than 64
*
*   If post_string is XXXXXX, 
*   then MS sends "<cr><lf>CONNECT XXXXXX<cr><lf>" when GPRS dialup
*   Ex.1 if post_string=" 230400", 
*        then entire output string is "<cr><lf>CONNECT 230400<cr><lf>"
*   Ex.2 if post_string=" 56000 V42bis", 
*        then entire output string is "<cr><lf>CONNECT 56000 V42bis<cr><lf>"
*    
* PARAMETERS
*   kal_uint8 act, ACcess Technology, 
                   This field value can be referred to TS27.007
                   0,   GSM
                   1,   GSM Compact
                   2,   UTRAN
                   3,   GSM w/EGPRS
                   4,   UTRAN w/HSDPA
                   5,   UTRAN w/HSUPA
                   6,   UTRAN w/HSDPA and HSUPA
* RETURNS
*     kal_uint8* post_string
*****************************************************************************/
const kal_uint8* custom_get_gprs_dialup_connect_post_string(kal_uint8 act)
{
    /* Note: The return string length must be less than 64!!! */
#ifdef __TC01__
    #if defined(__HSDPA_SUPPORT__)
/* under construction !*/
	#elif defined(__EGPRS_MODE__)
/* under construction !*/
	#else
/* under construction !*/
	#endif
#elif defined(__PS_DIALUP_CONNECT_STRING_BY_ACT__)
    static kal_uint8 temp_string[64];
    const kal_uint8* post_string = temp_string;    
    if ((act == 0) || (act == 1) || (act == 3))
    {
        strcpy(temp_string, " 236800");
    }
    else
    {
        strcpy(temp_string, " 7200000");
    }    
#else
  //Note: user MUST prepare a space before the speed number
  #if defined(__HSDPA_SUPPORT__) && defined(__UMTS_FDD_MODE__)
	static const kal_uint8 post_string[] = " 7200000"; //7.2Mbps
  #elif defined(__HSDPA_SUPPORT__) && defined(__UMTS_TDD128_MODE__)
  	static const kal_uint8 post_string[] = " 2624000"; //2.6Mbps
  #elif defined(__UMTS_FDD_MODE__) || defined(__UMTS_TDD128_MODE__)
    static const kal_uint8 post_string[] =  " 384000"; //384kbps
  #elif defined(__EGPRS_MODE__)
    static const kal_uint8 post_string[] =  " 473600"; //473.6kbps
  #else
    static const kal_uint8 post_string[] =   " 80000"; //80kbps  
  #endif
#endif
    return (const kal_uint8*) post_string;
} // MAUI_02386357, mtk02285, MAUI_02825172
#endif /* __MOD_TCM__ */

/*****************************************************************************
* FUNCTION
*  	custom_is_edit_mode_command()
* DESCRIPTION
*   This function is used to let customer judge if the input command is needed to enter 
* editor mode or not. If true, we will output "> " and wait for 
*       ctrl+z character to execute the whole command string
*       ESC character to cancel the command
*    
* PARAMETERS
*   	data    [IN]    input command string header, maximum length : 10
* RETURNS
*     KAL_TRUE or KAL_FALSE
*****************************************************************************/
kal_bool custom_is_edit_mode_command(kal_uint8 *data)
{
    /*if (strncmp(data, "AT%EDIT", 7) == 0)
        return KAL_TRUE;
    else*/
        return KAL_FALSE;
}

#if defined(__PLMN_LIST_WITH_CELL_INFO__)
kal_uint32 custom_at_posi_get_ndssign(kal_char *buffer, kal_uint32 buf_len, kal_uint8 plmn_num, l4c_rat_plmn_info_struct *list)
{
    /* buf_len: MAX size of the 'buffer' please do not cruppt
       string_length: Indicates how many bytes writes into 'buffer'
    */
    
   /* Prototype of l4c_rat_plmn_info_struct
            #ifdef __PLMN_LIST_WITH_CELL_INFO__
                #define MAX_NUM_CELL_PER_PLMN  10
            #endif 
            
            #if defined(__PLMN_LIST_WITH_CELL_INFO__)
            typedef struct {
                kal_uint16       arfcn;
                kal_int16        rxlev;
                kal_uint8        bsic;
                kal_uint8        la_code[2];
                kal_uint16       cell_id;
                }l4c_location_cell_info_struct;
            #endif
            
            typedef struct {
               kal_uint8   plmn_id[7];
               kal_uint8   status;
               kal_uint8 rat;
               #if defined(__PLMN_LIST_WITH_CELL_INFO__)
               l4c_location_cell_info_struct cell_list[MAX_NUM_CELL_PER_PLMN];
               #endif
            } l4c_rat_plmn_info_struct;
      */
     /* sample code, judge how many PLMN and cell info in the parameter 'list'
          kal_uint8 i;
          kal_uint8 j;
          kal_uint8 ended;
          kal_uint16 temp_lac;
          kal_uint16 temp_lac_2;
          
          for (i = 0; i < plmn_num; i++)
            {
                for(j = 0; j < MAX_NUM_CELL_PER_PLMN; j++)
                {
                    temp_lac = list[i].cell_list[j].la_code[0];
                    temp_lac = (temp_lac << 8) | (list[i].cell_list[j].la_code[1]);

                    if((temp_lac == 0) && (list[i].cell_list[j].cell_id == 0))
                    {
                        break;
                    }

                    // Judge if this is the last cell info 
                    if((i == (plmn_num - 1)) && (j == (MAX_NUM_CELL_PER_PLMN - 1)))
                    {
                        ended = 1;
                    }
                    else if(i == (plmn_num - 1))
                    {
                        temp_lac_2 = list[i].cell_list[j+1].la_code[0];
                        temp_lac_2 = (temp_lac_2 << 8) | (list[i].cell_list[j+1].la_code[1]);

                        if((temp_lac_2 == 0) && (list[i].cell_list[j+1].cell_id == 0))
                        {
                            ended = 1;
                        }
                    }
                 }
             }
    */
    kal_uint32 string_length = 0;
    
    /* Replace the line after thie comment, calculate NDSSIGN and write into buffer */
    string_length = kal_sprintf(buffer, "\"NDSSIGN\"");

    
    /* It's recommended that do not remove the codes after this line! */
    if(string_length > buf_len)
    {
        /* Add length check, void memory curruption */
        ASSERT(0);
    }
    return string_length;
}

kal_bool custom_process_at_posi()
{
	  // customer code
    return KAL_FALSE;
}
#endif
