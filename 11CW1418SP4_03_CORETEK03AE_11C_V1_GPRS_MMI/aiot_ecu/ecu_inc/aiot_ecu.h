/*
 * Nanjing NWOW Technology Co.,Ltd.(C) 2019
 * www.nwowtec.com
 * dequan.wang@nwowtec.com
 * Create the AIOT ECU Software on March 27, 2019.
 * Software is eating up the world...
 * Across the Great Wall, we can reach every corner in the world. 
 *
 * */

/*
 * Filename:
 * ----------
 * aiot_ecu.h
 *
 * Project:
 * ----------
 * AIOT ECU
 *
 * Description:
 * ------------
 * AIOT ECU (Electronic Control Unit) Header file
 *
 * Author:
 * --------
 * WDQ
 *
 * */

#ifndef __AIOT_ECU_H__
#define __AIOT_ECU_H__
#include <stdlib.h>
#include "MMI_features.h"
#include "MMIDataType.h"
#include "kal_general_types.h"
#include "dcl.h"
#include "Mmi_rp_srv_aiot_ecu_def.h"
#include "ProfilesSrv.h"
#include "resource_audio.h"
#include "mdi_datatype.h"
#include "mmi_rp_srv_prof_def.h"
#include "bmt_utility.h"

/*****************************************************************************
 * Type Definitions
 ****************************************************************************/

/*****************************************************************************
 * Constant definition
 ****************************************************************************/

/*****************************************************************************
 * Macros Without Parameters
 ****************************************************************************/
#define ECU_DEBUG
#ifdef ECU_DEBUG
#define ecu_debug_print	kal_prompt_trace
#else
#define ecu_debug_print(...)
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
#endif /*__AIOT_ECU_H__*/
