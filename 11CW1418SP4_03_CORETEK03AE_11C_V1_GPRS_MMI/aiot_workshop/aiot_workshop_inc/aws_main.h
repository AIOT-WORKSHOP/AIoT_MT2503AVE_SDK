/*
 * ShenZhen AIOT WORKSHOP (C) 2019
 * aiot_workshop@qq.com
 * Create the AIOT WORKSHOP Software on Aug 8 2018.
 * Software is eating up the world...
 * Across the Great Wall, we can reach every corner in the world. 
 *
 * */

/*
 * Filename:
 * ----------
 * aws_main.h
 *
 * Project:
 * ----------
 * AWS : (AIOT WORKSHOP)
 *
 * Description:
 * ------------
 * AIOT WORKSHOP (AIOT工作室) Header files Template
 *
 * Author:
 * --------
 * aiot_workshop@qq.com
 *
 * */

#ifdef __AIOT_WORKSHOP__
#ifndef __AWS_MAIN_H__
#define __AWS_MAIN_H__

/*****************************************************************************
 * Type Definitions
 ****************************************************************************/

/*****************************************************************************
 * Constant definition
 ****************************************************************************/

/*****************************************************************************
 * Macros Without Parameters
 ****************************************************************************/

/*****************************************************************************
 * Macros With Parameters
 ****************************************************************************/

/***************************************************************************** 
 * interface 
 ****************************************************************************/
kal_bool aws_create(comptask_handler_struct **handle);
void aws_task_send_msg(module_type  dest_mod, sap_type sap_id, msg_type msg_id, void *local_param_ptr);
/***************************************************************************** 
 * Extern Variable
 ****************************************************************************/

/***************************************************************************** 
 * Extern Function
 ****************************************************************************/
#endif /*__AWS_MAIN_H__*/
#endif/*__AIOT_WORKSHOP__*/