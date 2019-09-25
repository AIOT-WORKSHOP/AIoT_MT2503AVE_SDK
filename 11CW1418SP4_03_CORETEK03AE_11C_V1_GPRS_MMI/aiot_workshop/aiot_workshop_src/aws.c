/*
 * ShenZhen AIOT WORKSHOP (C) 2019
 * aiot_workshop@qq.com
 * Create the AIOT WORKSHOP Software on Aug,8 2018.
 * Software is eating up the world...
 * Across the Great Wall, we can reach every corner in the world. 
 *
 * */

/*
 * Filename:
 * ----------
 * aws.c
 *
 * Project:
 * ----------
 * AWS : (AIOT WORKSHOP)
 *
 * Description:
 * ------------
 * AIOT WORKSHOP (AIOT工作室) Source Template
 *
 * Author:
 * --------
 * aiot_workshop@qq.com
 *
 * */

#ifdef __AIOT_WORKSHOP__
/*****************************************************************************
 * Include                                                                     
 ****************************************************************************/
#include "aws.h"
#include "kal_trace.h"
#include "nvram_common_defs.h"
#include "mmi_frm_nvram_gprot.h"
#include "common_nvram_editor_data_item.h"

/*****************************************************************************
 * Define                                                                      
 ****************************************************************************/

/*****************************************************************************
 * Typedef                                                                     
 ****************************************************************************/

/*****************************************************************************
 * Local Variable                                                              
 ****************************************************************************/

/*****************************************************************************
 * Extern Global Variable                                                      
 ****************************************************************************/

/*****************************************************************************
 * Local Function                                                              
 ****************************************************************************/

/*****************************************************************************
 * Extern Global Function                                                      
 ****************************************************************************/


/*****************************************************************************
 * FUNCTION
 *  AWS_UT_Case1_timer
 * DESCRIPTION
 *  AWS Unit testing Case  
 * PARAMETERS
 * 
 * RETURNS
 * 
 *****************************************************************************/

void AWS_UT_Case1_timer(void)
{
	static kal_uint16 AWS_UT_Case1_timer_count = 0;
	
	AWS_PRINTF(MOD_MMI, "AWS_UT_Case1_timer %d: AWS_UT_TIMER", ++AWS_UT_Case1_timer_count);
	StartTimer(AWS_UT_TIMER, AWS_UT_TIMER_TIME, AWS_UT_Case1_timer);
}

/*****************************************************************************
 * FUNCTION
 *  UT_Case2_msg
 * DESCRIPTION
 *  Unit testing Case: send msg from here(MOD_MMI) to MOD_AWS
 * PARAMETERS
 * 	void
 * RETURNS
 *  void
 *****************************************************************************/

void UT_Case2_msg(void)
{
	/*----------------------------------------------------------------*/
	/* Local Variables                                                */
	/*----------------------------------------------------------------*/

	/*----------------------------------------------------------------*/
	/* Code Body                                                      */
 	/*----------------------------------------------------------------*/

	module_send_msg(MOD_MMI, MOD_AWS, AWS_SAP, MSG_ID_AWS_UT_MMI_REQ, NULL);
	StartTimer(AWS_UT_TIMER, AWS_UT_TIMER_TIME, UT_Case2_msg);
}

/*****************************************************************************
 * FUNCTION
 *  module_send_msg
 * DESCRIPTION
 *  Unit testing Case: send msg from src_mod to dest_mod
 * PARAMETERS
 * 	void
 * RETURNS
 *  void
 *****************************************************************************/

void module_send_msg(module_type  src_mod, module_type  dest_mod, sap_type sap_id, msg_type msg_id, void *local_param_ptr)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    ilm_struct  *ilm_ptr;
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    ilm_ptr = allocate_ilm(src_mod);
    ilm_ptr->src_mod_id = src_mod;
    ilm_ptr->dest_mod_id = dest_mod;
    ilm_ptr->sap_id = sap_id;
    ilm_ptr->msg_id = msg_id;
    ilm_ptr->local_para_ptr = (local_para_struct*) local_param_ptr;
    ilm_ptr->peer_buff_ptr = (peer_buff_struct*) NULL;
    msg_send_ext_queue(ilm_ptr);
}
/*****************************************************************************
 * FUNCTION
 *  AWS_Init
 * DESCRIPTION
 *  The main fuction of AIOT WORKSHOP 
 * PARAMETERS
 * 
 * RETURNS
 *
 ****************************************************************************/
void AWS_Init(void)
{
	/*----------------------------------------------------------------*/
	/* Local Variables                                                */
	/*----------------------------------------------------------------*/
	
	/*----------------------------------------------------------------*/
	/* Code Body                                                      */
 	/*----------------------------------------------------------------*/
	

#ifdef AWS_UT
	//StartTimer(AWS_UT_TIMER, AWS_UT_TIMER_TIME, AWS_UT_Case1_timer);
	StartTimer(AWS_UT_TIMER, AWS_UT_TIMER_TIME, UT_Case2_msg);
#endif
}

#endif/*__AIOT_WORKSHOP__*/