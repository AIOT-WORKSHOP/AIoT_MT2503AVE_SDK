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
 * aws_main.c
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

//#ifdef __AIOT_WORKSHOP__

/*****************************************************************************
 * Include                                                                     
 ****************************************************************************/
#include "aws.h"
#include "aws_main.h"
#include "kal_general_types.h"
#include "stack_msgs.h"         /* enum for message IDs */
#include "app_ltlcom.h"         /* Task message communiction */
#include "syscomp_config.h"
#include "task_config.h"        /* Task creation */
#include "kal_public_defs.h"
#include "kal_public_api.h"
#include "kal_internal_api.h"

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
 *  aws_main
 * DESCRIPTION
 *  Message handler
 * PARAMETERS
 *  ilm_ptr     [IN]     message data
 * RETURNS
 *  void
 *****************************************************************************/
void aws_main(ilm_struct *ilm_ptr)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/ 

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
		AWS_PRINTF(MOD_AWS, "AWS MAIN,  msg_id: %d",ilm_ptr->msg_id);
		
		#ifdef AWS_UT//only for Unit testing...
    if (MSG_ID_AWS_UT_MMI_REQ == ilm_ptr->msg_id)
    {
			aws_task_send_msg(MOD_MMI, AWS_SAP, MSG_ID_AWS_UT_MMI_CNF, NULL);
    }
		#endif

		#if 0
	  if (MSG_ID_ == ilm_ptr->msg_id)
    {
        
    }
    else if (MSG_ID_ == ilm_ptr->msg_id)
    {
        
    }
    else if (MSG_ID_ == ilm_ptr->msg_id)
    {
        
    }
    else if (MSG_ID_ == ilm_ptr->msg_id)
    {
    
    }
		#endif

}
/*****************************************************************************
 * FUNCTION
 *  aws_task_init
 * DESCRIPTION
 *  Init AWS task
 * PARAMETERS
 *  task_indx       [IN]    task index             
 * RETURNS
 *  KAL_BOOL
 *****************************************************************************/
kal_bool aws_task_init(task_indx_type task_indx)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
		AWS_PRINTF(MOD_AWS, "AWS TASK INIT OK");
		
    return KAL_TRUE;
}

/*****************************************************************************
 * FUNCTION
 *  aws_task_reset
 * DESCRIPTION
 *  Reset AWS task
 * PARAMETERS
 *  task_indx       [IN]    task index             
 * RETURNS
 *  KAL_BOOL
 *****************************************************************************/
kal_bool aws_task_reset(task_indx_type task_indx)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
  
     return KAL_TRUE;
}

/*****************************************************************************
 * FUNCTION
 *  aws_task_main
 * DESCRIPTION
 *  AWS task main
 * PARAMETERS
 *  task_entry_ptr      [IN]        task struct pointer 
 * RETURNS
 *  void
 *****************************************************************************/
void aws_task_main(task_entry_struct *task_entry_ptr)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    ilm_struct current_ilm;
    kal_uint32 my_index;
		static kal_uint32 cnt = 0;
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    kal_get_my_task_index(&my_index);

    while (1)
    {		
			AWS_PRINTF(MOD_AWS, "AWS TASK MAIN LOOP:%d", ++cnt);

			receive_msg_ext_q_for_stack(task_info_g[task_entry_ptr->task_indx].task_ext_qid, &current_ilm);
			stack_set_active_module_id(my_index, current_ilm.dest_mod_id);

			aws_main((void*)&current_ilm);

			free_ilm(&current_ilm);
    }

}

/*****************************************************************************
 * FUNCTION
 *	aws_create
 * DESCRIPTION
 * 	create AWS task
 * PARAMETERS
 * 	handle      [IN]     handle
 * RETURNS
 *	KAL_BOOL
 ****************************************************************************/
kal_bool aws_create(comptask_handler_struct **handle)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    static const comptask_handler_struct aws_handler_info = 
    {
        aws_task_main,  /* task entry function */
        aws_task_init,  /* task initialization function */
        NULL,           /* task configuration function */
        aws_task_reset, /* task reset handler */
        NULL,           /* task termination handler */
    };

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    *handle = (comptask_handler_struct*)&aws_handler_info;

    return KAL_TRUE;
}


void aws_task_send_msg(module_type  dest_mod, sap_type sap_id, msg_type msg_id, void *local_param_ptr)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    ilm_struct  *ilm_ptr;
    module_type src_mod;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    src_mod = MOD_AWS; //stack_get_active_module_id();
    ilm_ptr = allocate_ilm(src_mod);
    ilm_ptr->src_mod_id = src_mod;
    ilm_ptr->dest_mod_id = dest_mod;
    ilm_ptr->sap_id = sap_id;
    ilm_ptr->msg_id = msg_id;
    ilm_ptr->local_para_ptr = (local_para_struct*) local_param_ptr;
    ilm_ptr->peer_buff_ptr = (peer_buff_struct*) NULL;
    msg_send_ext_queue(ilm_ptr);
}

//#endif/*__AIOT_WORKSHOP__*/
