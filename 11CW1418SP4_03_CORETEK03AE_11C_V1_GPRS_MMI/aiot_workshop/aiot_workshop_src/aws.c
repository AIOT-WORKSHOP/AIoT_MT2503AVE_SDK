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
	StartTimer(AWS_UT_TIMER, AWS_UT_TIMER_TIME, AWS_UT_Case1_timer);

#endif
}

#endif/*__AIOT_WORKSHOP__*/