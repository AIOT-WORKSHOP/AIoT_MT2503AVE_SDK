/*
 * ShenZhen AIOT WORKSHOP (C) 2019
 * aiot_workshop@qq.com
 * Create the AIOT WORKSHOP Software on SEP,24 2019.
 * Software is eating up the world...
 * Across the Great Wall, we can reach every corner in the world. 
 *
 * */

/*
 * Filename:
 * ----------
 * aws.h
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
#ifndef __AWS_H__
#define __AWS_H__
#include <stdlib.h>
#include "MMI_features.h"
#include "MMIDataType.h"
#include "kal_general_types.h"
#include "dcl.h"
#include "Mmi_rp_srv_aws_def.h"
#include "ProfilesSrv.h"
#include "resource_audio.h"
#include "mdi_datatype.h"
#include "mmi_rp_srv_prof_def.h"
#include "bmt_utility.h"
#include "soc_api.h"
#include "common_nvram_editor_data_item.h"
#include "gpio_drv.h"
#include "nbr_public_struct.h"
#include "mdi_gps.h"
/*****************************************************************************
 * Type Definitions
 ****************************************************************************/

/*****************************************************************************
 * Constant definition
 ****************************************************************************/
#define AWS_UT
#define AWS_UT_TIMER_TIME (5*1000)
/*****************************************************************************
 * Macros Without Parameters
 ****************************************************************************/
#define AWS_DEBUG

#ifdef AWS_DEBUG
#define AWS_PRINTF	kal_prompt_trace
#else
#define AWS_PRINTF(...)
#endif
/*****************************************************************************
 * Macros With Parameters
 ****************************************************************************/

/***************************************************************************** 
 * interface 
 ****************************************************************************/

/***************************************************************************** 
 * Extern Variable
 ****************************************************************************/

/***************************************************************************** 
 * Extern Function
 ****************************************************************************/
#endif /*__AWS_H__*/
#endif/*__AIOT_WORKSHOP__*/