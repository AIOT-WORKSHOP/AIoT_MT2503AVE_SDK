#include "stdio.h"
#include <stdlib.h>
#include "MMI_features.h"
#include "kal_release.h"
#include "kal_trace.h"
#include "syscomp_config.h"
#include "dcl_pmu.h"
#include "eint.h"
#include "eint_drv.h"
#include "drv_comm.h"
#include "device.h"
#include "pwm_drv.h"
#include "mmi_frm_mem_gprot.h"
#include "lock_data.h"
#include "lock_net.h"
#include "lock_gps.h"
#include "lock_drv.h"
#include "iotlock.h"
#include "motion_sensor_custom.h"

#ifdef __NSK_ECG__
#include "nsk_ecg_core.h"
#include "nsk_ecg_ext.h"
#endif
#include "TimerEvents.h"


#ifndef MAX_MOVE_COUNT
#define MAX_MOVE_COUNT 20
#endif
#ifndef MAX_MOVE_SEC
#define MAX_MOVE_SEC 60
#endif

#ifndef MAX_MOVE_COUNT_2S
#define MAX_MOVE_COUNT_2S 	2
#endif
#ifndef MAX_MOVE_SEC_2S
#define MAX_MOVE_SEC_2S 	2
#endif

static kal_uint8 led_beep_count =0xFF;
kal_bool g_beep_beep = KAL_FALSE;
const kal_uint8 CLOSE_LOCK_EINT = 0;
const kal_uint8 OPEN_LOCK_EINT = 1;
const kal_uint8 G_SENSOR_EINT2 = 12;
const kal_uint8 G_SENSOR_EINT1 = 23;
kal_uint32 move_time[MAX_MOVE_COUNT];
kal_uint8 move_time_count = 0;

kal_uint32 move_time_2s[MAX_MOVE_COUNT_2S];
kal_uint8 move_time_count_2s = 0;

kal_uint16 aging_counts;
kal_uint16 counts;
kal_uint8 agingbuf[512] = {0};
kal_uint8 at_sendbuf[32];

kal_bool 	g_aging_test = KAL_FALSE;
kal_bool 	g_normal_open_lock_state = KAL_FALSE;
kal_bool 	g_lock_opening = KAL_FALSE;
kal_bool 	open_lock_exception = KAL_FALSE;
#define 	IOT_BATTERY_MAX_TEMP	45		//bat max charge temperature
#define 	IOT_BATTERY_MIN_TEMP	0		//bat min charge temperature

#define 	IOT_BATTERY_DISCHARGE_MAX_TEMP	61		//bat max charge temperature
#define 	IOT_BATTERY_DISCHARGE_MIN_TEMP	(-21)		//bat min charge temperature


#define __UART_SLEEP_WAKEUP__
#ifdef __UART_SLEEP_WAKEUP__
static kal_uint8	ATA_uart1_handler	= 0xff;		// sleep handle
#endif

kal_uint16 led1_ctrl_time = 0x00;
kal_uint8 led1_ctrl_count = 0x00;
kal_uint8 led1_ctrl_state = 0x00;

kal_uint16 led2_ctrl_time = 0x00;
kal_uint8 led2_ctrl_count = 0x00;
kal_uint8 led2_ctrl_state = 0x00;

static kal_uint8 led2_flash_count = 0x00;

//end
extern gprs_lock_cntx g_lock_cntx;
extern kal_bool g_need_open_gps;

extern void iot_get_battery(void);
extern COMM_LOC g_comm_loc;

extern void RestoreIRQ(kal_uint32 irq);
extern kal_uint32 DisableIRQ(void);
extern void aging_test_callback();
extern kal_int16 iot_get_battery_isense(void);
extern void iot_bat_charger_en(kal_bool chr_en);
kal_int16 iot_get_battery_temperature(void);
extern kal_uint8 iot_get_bkup_nv_first_byte(void);
extern void iot_set_bkup_nv_first_byte(kal_uint8 type);
extern void acc_sensor_get_xyz(kal_int16 *accl_x,kal_int16 *accl_y,kal_int16 *accl_z);

extern kal_bool g_need_open_gps;
extern gprs_lock_cntx g_lock_cntx;
extern Word g_serial_number;
static  kal_bool is_temp_warn_state = KAL_FALSE;
static  kal_bool is_volt_warn_state = KAL_FALSE;
static  kal_bool is_vib_warn_state = KAL_FALSE;

#ifdef 		__NSK_ECG__

#define                                 ECG_UART_PORT                   uart_port1
#define                                 ECG_OWNER_ID                    MOD_MMI
#define                                 MAX_ECG_PACKET_LEN              2048
#define                                 MAX_ECG_RESULT_LEN              2048
#define                                 CALCULATION_COUNT               30


kal_uint8				ECG_RESULT_BUFF[MAX_ECG_RESULT_LEN];
extern kal_uint8	 	g_ecg_result_buff[MAX_ECG_RESULT_LEN];
static kal_uint8 		gabyUartBuffer[MAX_ECG_PACKET_LEN];
kal_uint8 				ECG_raw_data_buf[MAX_ECG_PACKET_LEN];

kal_uint16				ECG_RESULT_LEN			= 0;
kal_uint16				gwECG_data_len			= 0;
kal_uint16				gwECG_data_temp_len 	= 0;
kal_uint8 				uart_handler 			= 0xff;
kal_uint8 				gbUartInitialized 		= KAL_FALSE;
module_type				gbUartOwnerId;

// user feedback for previous session, 1-100. Set to 0 if no feedback.
kal_uint8 				ecg_feedback 			= 0x00;
// 0 for male, 1 for female
kal_uint8 				ecg_gender 				= 0;
// age, in years.  16-90
kal_uint8 				ecg_age 				= 40;
// height, in cm. 1-300
kal_uint16				ecg_height 				= 165;
// weight, in kg. 1-300
kal_uint16 				ecg_weight 				= 65;

kal_uint16 				g_ecg_out_buff_len 		= 0;
kal_bool 				g_ecg_is_begin_upload 	= KAL_FALSE;
kal_uint8 				send_cnt_num 			= 0;
static kal_uint16 		gwLenUartBuffer 		= 0;
static kal_uint8 		ghSleepMode;
static module_type 		gnOrigUartOwner;

kal_uint16 				g_ecg_out_count 		= 0;

void ECG_UART_DeInit(void);
void ECG_UART_Init(void);
void ECG_UART_handler(void *msg);
static void UART_SetOwner(UART_PORT port, module_type ownerid);
static module_type UART_GetOwnerID(UART_PORT port);
extern void U_ClrTxBuffer(UART_PORT port, module_type ownerid);
extern void U_ClrRxBuffer(UART_PORT port, module_type ownerid);
extern kal_uint16 U_PutBytes_VFIFO(UART_PORT port, kal_uint8 *Buffaddr, kal_uint16 Length, module_type ownerid);
kal_uint16 ECG_UART_Read(kal_uint8 *buf, kal_uint16 maxlen, UART_PORT port, module_type ownerid);
kal_uint8 ECG_UART_Write(kal_uint8 *buf, kal_uint16 buflen, UART_PORT port, module_type ownerid);
void dump_uart_data(kal_uint8 *buf,kal_uint16 len);
void ECG_PWR_ON(void);
void ECG_PWR_OFF(void);
void ECG_data_handler2(void);
void ECG_data_handler3(void);

#endif
kal_bool need_report = KAL_FALSE;
kal_uint32 get_curr_rtc_sec(void)
{	
	kal_uint32 currSec = 0;
	applib_time_struct updateTime;
	applib_dt_get_rtc_time(&updateTime);
	currSec = applib_dt_mytime_2_utc_sec(&updateTime, MMI_FALSE);
	return currSec;
}

kal_bool need_notify_move(void)
{	
	kal_uint8 i = 0;
	if(need_report == KAL_TRUE)
	{
		return KAL_FALSE;
	}
	if((move_time_count == MAX_MOVE_COUNT)&&((move_time[MAX_MOVE_COUNT - 1] - move_time[0]) < (MAX_MOVE_SEC + 1)))
	{
		kal_prompt_trace(MOD_ENG,"%s() %d %d",__func__,__LINE__,move_time_count);
		memset(move_time, 0x00, MAX_MOVE_COUNT);
		move_time_count = 0;
		return KAL_TRUE;
	}
	else
	{
		if(move_time_count < MAX_MOVE_COUNT)
		{
			move_time[move_time_count] = get_curr_rtc_sec();
			kal_prompt_trace(MOD_ENG,"%s() %d %d %d",__func__,__LINE__,move_time_count,move_time[move_time_count]);
			move_time_count++;
		}
		else
		{
			kal_prompt_trace(MOD_ENG,"%s() %d %d",__func__,__LINE__,move_time_count);
			for(i = 0;i < MAX_MOVE_COUNT - 1;i++)
			{
				move_time[i] = move_time[i + 1];
			}
			move_time[MAX_MOVE_COUNT - 1] = get_curr_rtc_sec();
			kal_prompt_trace(MOD_ENG,"%s() %d %d %d",__func__,__LINE__,move_time_count,move_time[MAX_MOVE_COUNT - 1]);
		}
		return KAL_FALSE;
	}
}

kal_bool need_notify_move_2s(void)
{
	kal_uint8 i = 0;
	if(is_vib_warn_state == KAL_TRUE)
	{
		return KAL_FALSE;
	}
	if((move_time_count_2s == MAX_MOVE_COUNT_2S)&&((move_time_2s[MAX_MOVE_COUNT_2S- 1] - move_time_2s[0]) < (MAX_MOVE_SEC_2S+ 1)))
	{
		kal_prompt_trace(MOD_ENG,"%s() %d %d", __func__, __LINE__,move_time_count_2s);
		memset(move_time_2s, 0x00, MAX_MOVE_COUNT_2S);
		move_time_count_2s= 0;
		return KAL_TRUE;
	}
	else
	{
		if(move_time_count_2s< MAX_MOVE_COUNT_2S)
		{
			move_time_2s[move_time_count_2s] = get_curr_rtc_sec();
			kal_prompt_trace(MOD_ENG,"%s() %d %d %d",__func__,__LINE__,move_time_count_2s,move_time_2s[move_time_count_2s]);
			move_time_count_2s++;
		}
		else
		{
			kal_prompt_trace(MOD_ENG,"%s() %d %d", __func__, __LINE__, move_time_count_2s);
			for(i = 0;i < MAX_MOVE_COUNT_2S- 1;i++)
			{
				move_time_2s[i] = move_time_2s[i + 1];
			}
			move_time_2s[MAX_MOVE_COUNT_2S- 1] = get_curr_rtc_sec();
			kal_prompt_trace(MOD_ENG,"%s() %d %d %d", __func__, __LINE__, move_time_count_2s,move_time_2s[MAX_MOVE_COUNT_2S- 1]);
		}
		return KAL_FALSE;
	}
}

void stop_move_notify_timer(void)
{
	kal_prompt_trace(MOD_ENG,"%s() %d",__func__,__LINE__);
	StopTimer(LOCK_MOVE_TIMER);
	//iot_play_tone_with_filepath(IOT_TONE_WARN);
}
void move_stop_timer_cb(void)
{
	StopTimer(LOCK_MOVE_STOP_TIMER);
	kal_prompt_trace(MOD_ENG,"%s() %d",__func__,__LINE__);
	if(need_report == KAL_TRUE)
	{
		kal_prompt_trace(MOD_ENG,"%s() %d",__func__,__LINE__);
		if(read_lock_state() == LOCKED) 
		{
			kal_prompt_trace(MOD_ENG,"%s() %d",__func__,__LINE__);
			g_comm_loc.alarm = 1;
			g_need_open_gps = KAL_TRUE;
			open_gps_and_get_loc(0, MOVE_LOC_REPORT);
		}
		need_report = KAL_FALSE;
	}
}

static void led1_ctrl(kal_uint16 en) //isink control
{
    DCL_HANDLE pwm_handle;
    PWM_LEVEL_T level;
    DCL_HANDLE handle; 
    PMU_CTRL_ISINK_SET_EN isink_en;

    if(en == 0)
    {
        level.pwm_level = LED_LIGHT_LEVEL0;
    }
    else
    {
        level.pwm_level = LED_LIGHT_LEVEL1;
    }
    pwm_handle= DclPWM_Open(DCL_MAIN_LCD_BL, MOD_UEM);
	DclPWM_Control(pwm_handle, PWM_CMD_SET_LEVEL,(DCL_CTRL_DATA_T*)&level);
	DclPWM_Close(pwm_handle); 

    handle = DclPMU_Open(DCL_PMU, FLAGS_NONE);

    if( en == 0)
	{
        // ISINK0
        isink_en.isink = ISINK0;
        isink_en.enable = DCL_FALSE;
        DclPMU_Control(handle, ISINK_SET_EN, (DCL_CTRL_DATA_T *)&isink_en);

        //ISINK1
        isink_en.isink = ISINK1;
        isink_en.enable = DCL_FALSE;
        DclPMU_Control(handle, ISINK_SET_EN, (DCL_CTRL_DATA_T *)&isink_en);
    }
	else
	{
	    // ISINK0 
        isink_en.isink = ISINK0;
        isink_en.enable = DCL_TRUE;
        DclPMU_Control(handle, ISINK_SET_EN, (DCL_CTRL_DATA_T *)&isink_en);

        //ISINK1
        isink_en.isink = ISINK1;
        isink_en.enable = DCL_TRUE;
        DclPMU_Control(handle, ISINK_SET_EN, (DCL_CTRL_DATA_T *)&isink_en);
	}
    DclPMU_Close(handle);
}

static void led2_ctrl(kal_uint16 en)//kpled control
{
    DCL_HANDLE pwm_handle;
    PWM_LEVEL_T level;
    PMU_CTRL_KPLED_SET_EN val_kpled;
    DCL_HANDLE handle;

    if(en)
    {
        level.pwm_level = LED_LIGHT_LEVEL1;
        val_kpled.enable = DCL_TRUE;
    }
    else
    {
        level.pwm_level = LED_LIGHT_LEVEL0;
        val_kpled.enable = DCL_FALSE;
    }

    pwm_handle= DclPWM_Open(DCL_LED_KP, MOD_UEM);
    DclPWM_Control(pwm_handle, PWM_CMD_SET_LEVEL,(DCL_CTRL_DATA_T*)&level);
	DclPWM_Close(pwm_handle); 

    handle = DclPMU_Open(DCL_PMU, FLAGS_NONE);
	DclPMU_Control(handle, KPLED_SET_EN, (DCL_CTRL_DATA_T *)&val_kpled);
	DclPMU_Close(handle);
}

static void led3_ctrl(kal_uint16 en)
{
	GPIO_ModeSetup(28,0);
	GPIO_InitIO(1, 28);
	GPIO_WriteIO(0,28);
	GPIO_WriteIO(en,28);
}

static void led4_ctrl(kal_uint16 en)
{
	GPIO_ModeSetup(29,0);
	GPIO_InitIO(1, 29);
	GPIO_WriteIO(0,29);
	GPIO_WriteIO(en,29);
}

void led_ctrl(LED_CTRL *ctrl) {
	if(ctrl !=NULL) {
		kal_uint16 time = ctrl->time;
		if(ctrl->state == 0) { //off
			if(ctrl->count > 0) {
				ctrl->state = 1;
				if(ctrl->led_no == 1) {
					led1_ctrl(1); //turn on
					StartTimerEx(LOCK_LED1_TIMER, time, led_ctrl, ctrl);
				} else if(ctrl->led_no == 2) {
					led2_ctrl(1); //turn on
					StartTimerEx(LOCK_LED2_TIMER, time, led_ctrl, ctrl);
				}
			}
		} else { //on
			ctrl->count -= 1;
			if(ctrl->led_no == 1) {
				led1_ctrl(0); //turn off
				if(ctrl->count > 0) {
					ctrl->state = 0;
					StartTimerEx(LOCK_LED1_TIMER, time, led_ctrl, ctrl);
				}
			}else if(ctrl->led_no == 2) {
				led2_ctrl(0); //turn off
				if(ctrl->count > 0) {
					ctrl->state = 0;
					StartTimerEx(LOCK_LED2_TIMER, time, led_ctrl, ctrl);
				}
			}
		}

		if(ctrl->count == 0) {
			mmi_mfree(ctrl);
		}
	}
}

void spronser_led_ctrl(kal_uint8 led_no, kal_uint16 time, kal_uint8 count)
{
#if 0
	LED_CTRL *ctrl = (LED_CTRL*)mmi_malloc(sizeof(LED_CTRL));
	ctrl->led_no = led_no;
	ctrl->time = time;
	ctrl->count = count;
	ctrl->state = 1;

	if(led_no == 1) {
		led1_ctrl(1);
		StartTimerEx(LOCK_LED1_TIMER, time, led_ctrl, ctrl);
	} else if(led_no == 2) {
		led2_ctrl(1);
		StartTimerEx(LOCK_LED2_TIMER, time, led_ctrl, ctrl);
	}
#endif
	iot_led_ctrl(led_no,time,count);
}

void led_power_switch(kal_bool on) //isink control
{
	led1_ctrl(on);
}

void led_beep_timer_callback(void)
{
	StopTimer(BOOTUP_LED_BEEP_TIMER);
	led_power_switch(0);
}

void bootup_beep_led(void)
{
	if(iot_get_bkup_nv_exception_reboot())
		return;
	if(led_beep_count == 0xff)
	{
		led_power_switch(1);
		StartTimer(BOOTUP_LED_BEEP_TIMER, 200, led_beep_timer_callback);
	}
}

void feed_watchdog_work()
{
	GPIO_WriteIO(1,21);
	Spconser_Delayms(1);
	GPIO_WriteIO(0,21);
	iot_get_battery();
	iot_battery_over_temp_callback();
}
void feed_watchdog_stop()
{
    GPIO_WriteIO(1,21);
}

void aiot_relay_ctrl(kal_bool onoff)
{
	GPIO_ModeSetup(AIOT_GPIO_RELAY, 0);
	GPIO_InitIO(OUTPUT, AIOT_GPIO_RELAY);
	GPIO_WriteIO(onoff, AIOT_GPIO_RELAY);
}

void aiot_rs485_DE_enable(void)
{
	GPIO_ModeSetup(AIOT_GPIO_RS485_DE_RE, 0);
	GPIO_InitIO(OUTPUT, AIOT_GPIO_RS485_DE_RE);
	GPIO_WriteIO(1, AIOT_GPIO_RS485_DE_RE);
}

void aiot_rs485_RE_enable(void)
{
	GPIO_ModeSetup(AIOT_GPIO_RS485_DE_RE, 0);
	GPIO_InitIO(OUTPUT, AIOT_GPIO_RS485_DE_RE);
	GPIO_WriteIO(0, AIOT_GPIO_RS485_DE_RE);
}

#ifdef __NSK_ECG__
void testcase_ECG_uart1(void)
{
	kal_uint8 uart1_write_len = 0;
	kal_uint8 buf[]="hello ecg uart1";

	aiot_rs485_DE_enable();
	uart1_write_len = ECG_UART_Write(buf, sizeof(buf)-1, ECG_UART_PORT, ECG_OWNER_ID);
	lock_debug_print(MOD_MMI, "ECG ECU iotlock:  %s, uart1_write_len=%d", __FUNCTION__, uart1_write_len);
	
	StartTimer(LOCK_MOVE_TIMER, 5*1000, testcase_ECG_uart1);

	Spconser_Delayms(100);
	aiot_rs485_RE_enable();
}
#endif/*__NSK_ECG__*/

void init_drv()
{
	kal_uint32 save_mask;
	save_mask = DisableIRQ();

	EINT_Set_HW_Debounce(CLOSE_LOCK_EINT, 2);
	EINT_Registration(CLOSE_LOCK_EINT,KAL_TRUE,KAL_FALSE, close_lock_capacitive_hisr, KAL_TRUE);
	EINT_Set_Sensitivity(CLOSE_LOCK_EINT, EDGE_SENSITIVE);
	EINT_Set_Polarity(CLOSE_LOCK_EINT, KAL_TRUE);

	EINT_Set_HW_Debounce(OPEN_LOCK_EINT, 2);
	EINT_Registration(OPEN_LOCK_EINT,KAL_TRUE,KAL_FALSE, open_lock_capacitive_hisr, KAL_TRUE);
	EINT_Set_Sensitivity(OPEN_LOCK_EINT, EDGE_SENSITIVE);
	EINT_Set_Polarity(OPEN_LOCK_EINT, KAL_FALSE);

	EINT_Set_HW_Debounce(G_SENSOR_EINT1, 2);		//G-sensor INT1
	EINT_Registration(G_SENSOR_EINT1,KAL_TRUE,KAL_FALSE, gsensor_capacitive_hisr1, KAL_TRUE);
	EINT_Set_Sensitivity(G_SENSOR_EINT1, EDGE_SENSITIVE);
	EINT_Set_Polarity(G_SENSOR_EINT1, KAL_FALSE);

	EINT_Set_HW_Debounce(G_SENSOR_EINT2, 2);		//G-sensor INT2
	EINT_Registration(G_SENSOR_EINT2,KAL_TRUE,KAL_FALSE, gsensor_capacitive_hisr2, KAL_TRUE);
	EINT_Set_Sensitivity(G_SENSOR_EINT2, EDGE_SENSITIVE);
	EINT_Set_Polarity(G_SENSOR_EINT2, KAL_FALSE);

	RestoreIRQ(save_mask);

	GPIO_ModeSetup(MOTO_GPIO1,0);
	GPIO_InitIO(1, MOTO_GPIO1);
	GPIO_WriteIO(0,MOTO_GPIO1);

	GPIO_ModeSetup(MOTO_GPIO2,0);
	GPIO_InitIO(1, MOTO_GPIO2);
	GPIO_WriteIO(0,MOTO_GPIO1);

	GPIO_ModeSetup(41, 0);
	GPIO_InitIO(1, 41);
	GPIO_WriteIO(0, 41);

	aiot_relay_ctrl(KAL_FALSE);
	
	#ifdef __NSK_ECG__
	ECG_PWR_ON();

	StartTimer(LOCK_MOVE_TIMER, 5*1000, testcase_ECG_uart1);
	
	#endif
#ifdef __UART_SLEEP_WAKEUP__
	iot_system_sleep_mode_switch();
#endif
	//StartTimer(LOCK_ATA_AT_TIMER4,1000,iot_acc_sensor_get_xyz_test);
}

void Spconser_Delayms(kal_uint16 data)
{
    kal_uint32 time1;
    
    time1 = drv_get_current_time();
    while (drv_get_duration_ms(time1) <= data);
}

void start_moto()
{
	GPIO_WriteIO(0, MOTO_GPIO1);
	GPIO_WriteIO(1,MOTO_GPIO2);
	open_lock_exception = KAL_FALSE;
}

void stop_moto()
{
	//brake
	GPIO_WriteIO(1, MOTO_GPIO1);
	GPIO_WriteIO(1, MOTO_GPIO2);

	Spconser_Delayms(10);
	open_lock_exception = KAL_FALSE;

	//stop
	GPIO_WriteIO(0, MOTO_GPIO1);
	GPIO_WriteIO(0, MOTO_GPIO2);
}

#ifdef OPEN_LOCK_WAIT_3S
void open_lock_wait_3s(){
	lock_debug_print(MOD_MMI, "iotlock_drv: %s start", __FUNCTION__);
	stop_moto();
	StartTimer(LOCK_LOCK_TIMER, 3*1000, start_moto);
}
#endif
void open_lock_hisr(void)
{
	EINT_Mask(OPEN_LOCK_EINT);
	need_report = KAL_FALSE;
	if(GPIO_ReadIO(OPEN_LOCK_EINT)==0)
	{
		lock_debug_print(MOD_MMI, "iotlock_drv: %s eint A", __FUNCTION__);
		EINT_Set_Polarity(OPEN_LOCK_EINT, KAL_TRUE);
	} 
	else 
	{
		lock_debug_print(MOD_MMI, "iotlock_drv: %s eint B", __FUNCTION__);
		stop_open_lock_normal();
		EINT_Set_Polarity(OPEN_LOCK_EINT, KAL_FALSE);
	}
	memset(at_sendbuf,0,sizeof(at_sendbuf));
	sprintf(at_sendbuf, "S1=%d", GPIO_ReadIO(OPEN_LOCK_EINT));
	rmmi_write_to_uart((kal_uint8*)at_sendbuf, strlen(at_sendbuf), KAL_TRUE);
	EINT_UnMask(OPEN_LOCK_EINT);
}
void close_lock_hisr(void)
{
	EINT_Mask(CLOSE_LOCK_EINT);
	if(GPIO_ReadIO(CLOSE_LOCK_EINT)==0)
	{
		lock_debug_print(MOD_MMI, "iotlock_drv: %s eint A", __FUNCTION__);
#ifdef OPEN_LOCK_WAIT_3S
		open_lock_wait_3s();
#endif
		EINT_Set_Polarity(CLOSE_LOCK_EINT, KAL_TRUE);//down
	} 
	else 
	{
		lock_debug_print(MOD_MMI, "iotlock_drv: %s eint B", __FUNCTION__);
		if(g_lock_opening)
			open_lock_exception = KAL_TRUE;
		else
			lock_bike_callback();
		EINT_Set_Polarity(CLOSE_LOCK_EINT, KAL_FALSE);//up
	}
	memset(at_sendbuf,0,sizeof(at_sendbuf));
	sprintf(at_sendbuf, "S2=%d", GPIO_ReadIO(CLOSE_LOCK_EINT));
	rmmi_write_to_uart((kal_uint8*)at_sendbuf, strlen(at_sendbuf), KAL_TRUE);
	EINT_UnMask(CLOSE_LOCK_EINT);
}

void open_lock_capacitive_hisr()
{
	StartTimer(LOCK_OPEN_HISR_TIMER, 10, open_lock_hisr);
}

/*���������ж�ʱ�ú���������*/
void close_lock_capacitive_hisr()
{
	StartTimer(LOCK_CLOSE_HISR_TIMER, 10, close_lock_hisr);
}

#ifdef __IOT_BLE_BKSS_SUPPORT__
extern void bkss_set_vib_status(char state);
#endif

#ifdef __UART_SLEEP_WAKEUP__
void uart1_sleep_enable(void)
{
	if(ATA_uart1_handler != 0xFF)
		L1SM_SleepEnable(ATA_uart1_handler);
	//ATA_uart1_handler = L1SM_IntGetHandle();
	//L1SM_IntSleepEnable(ATA_uart1_handler);
}

void uart1_sleep_disable(void)
{
	ATA_uart1_handler = L1SM_GetHandle();
	L1SM_SleepDisable(ATA_uart1_handler);
}

#endif

void gsensor_slope(void)
{
#ifdef __UART_SLEEP_WAKEUP__
	//uart1_sleep_disable();
#endif

	if(read_lock_state() == UNLOCKED) 
	{
		need_report = KAL_FALSE;
		if(!IsMyTimerExist(LOCK_SHARK_GAP_TIMER))
		{
			bike_vibrate_callback();
		}
	}
	else 
	{
		//bike_slope_callback();
	}
#ifdef __IOT_BLE_BKSS_SUPPORT__
	bkss_set_vib_status(1);
#endif
	kal_prompt_trace(MOD_MMI, "iotlock_drv: %s eint23", __FUNCTION__);
#ifdef __UART_SLEEP_WAKEUP__
	//uart1_sleep_enable();
#endif
}

void iot_reset_move_2s_warn(void)
{
	is_vib_warn_state = KAL_FALSE;
}

void iot_led_move_2s_warn(void)
{
	StartTimer(LOCK_ACC_VIB_TIMER4,60*1000,iot_reset_move_2s_warn);
	iot_led_ctrl(1,500,4);
}

void iot_speaker_move_2s_warn(void)
{
	#ifdef __IOT_LOCK_BEEPSPK__
		open_beep_ms(100, 4);
	#else
		iot_play_tone_with_filepath(IOT_TONE_WARN);
	#endif
}


void iot_move_2s_warning(void)
{
	if(is_vib_warn_state == KAL_FALSE)
	{
		kal_prompt_trace(MOD_MMI,"%s--iot_move_2s_warning start",__FUNCTION__);
		StartTimer(LOCK_ACC_VIB_TIMER2,2,iot_led_move_2s_warn);
		StartTimer(LOCK_ACC_VIB_TIMER3,2,iot_speaker_move_2s_warn);
		is_vib_warn_state = KAL_TRUE;
		
	}
}

void gsensor_vib(void)
{
#ifdef __IOT_BLE_BKSS_SUPPORT__
	bkss_set_vib_status(1);
#endif
	if(read_lock_state() == LOCKED) 
	{
		if(need_notify_move_2s())
		{
			kal_prompt_trace(MOD_ENG,"%s--need_notify_move_2s", __func__);
			StartTimer(LOCK_ACC_VIB_TIMER1, 10, iot_move_2s_warning);
		}
		if(need_notify_move())
		{
			need_report = KAL_TRUE;
			kal_prompt_trace(MOD_ENG,"%s() %d",__func__,__LINE__);
			StartTimer(LOCK_MOVE_TIMER, 10, stop_move_notify_timer);
		}
		kal_prompt_trace(MOD_ENG,"%s() %d",__func__,__LINE__);
		if(need_report == KAL_TRUE)
		{
			kal_prompt_trace(MOD_ENG,"%s() %d",__func__,__LINE__);
			StopTimer(LOCK_MOVE_STOP_TIMER);
			StartTimer(LOCK_MOVE_STOP_TIMER, 3*60*1000, move_stop_timer_cb);
		}
	}
}
/*������бʱ�����жϵ��øú���*/
void gsensor_capacitive_hisr1(void)
{
	EINT_Mask(G_SENSOR_EINT1);
	StartTimer(LOCK_SLOPE_TIMER, 50, gsensor_slope);
	EINT_UnMask(G_SENSOR_EINT1);
}

/*������ʱ�����жϵ��øú���*/
void gsensor_capacitive_hisr2(void)
{
	EINT_Mask(G_SENSOR_EINT2);
	StartTimer(LOCK_SHARK_TIMER, 50, gsensor_vib);

	kal_prompt_trace(MOD_MMI, "iotlock_drv: %s eint12", __FUNCTION__);
	EINT_UnMask(G_SENSOR_EINT2);
}
void bike_vibrating_callback(void)
{
	StopTimer(LOCK_SHARK_GAP_TIMER);
}
void bike_vibrate_callback(void)
{
	if (!srv_bootup_is_launched() || srv_shutdown_is_running())
	{
		return;
	}
	g_comm_loc.alarm = 1;
	g_need_open_gps = KAL_TRUE;
	if(read_lock_state() == UNLOCKED) 
	{
		open_gps_and_get_loc(0, VIB_LOC_REPORT);
		lock_debug_print(MOD_MMI, "iotlock_drv: %s  report loc when vibrate", __FUNCTION__);
	}
	if(!IsMyTimerExist(LOCK_SHARK_GAP_TIMER))
	{
		StartTimer(LOCK_SHARK_GAP_TIMER, 10*60*1000, bike_vibrating_callback);
	}
}

void bike_slope_callback(){
	if (!srv_bootup_is_launched() || srv_shutdown_is_running())
	{
		return;
	}
	g_comm_loc.alarm = 1;
	open_gps_and_get_loc(0, VIB_LOC_REPORT);
	lock_debug_print(MOD_MMI, "iotlock_drv: %s  report loc when slope", __FUNCTION__);
}


void bike_break(){

	g_comm_loc.alarm = 1;
	g_need_open_gps = KAL_TRUE;
	if(read_lock_state() == LOCKED) {
		open_gps_and_get_loc(0, VIB_LOC_REPORT);
		lock_debug_print(MOD_MMI, "iotlock_drv: %s  report loc when bike_break", __FUNCTION__);
	#ifdef __NSK_ECG__
		ECG_PWR_OFF();
	#endif
	}
}

/*��ʼ��������*/
void init_beep(void)
{
	lock_debug_print(MOD_MMI, "iotlock_drv: %s", __FUNCTION__);
	//GPIO_54ʹ�ܷ����������ó�GPIOģʽ
	GPIO_ModeSetup(54, 0);
	//���ó����
	GPIO_InitIO(1, 54);
	//Ĭ�ϵ͵�ƽ���ر�״̬
	GPIO_WriteIO(0, 54);
}

/*�÷���������*/
void open_beep_ms(kal_uint16 time, kal_uint8 count)
{
	kal_uint8 index = 0;
	g_beep_beep = KAL_TRUE;
	// time not use
	init_beep();

	for(; index < count; index++) {
		if(g_beep_beep) {
			GPIO_WriteIO(1, 54);
			Spconser_Delayms(time);
			GPIO_WriteIO(0, 54);
			Spconser_Delayms(time);
		}
	}
}

//no usefull
 void reset_lock(void)
{
	open_lock_ata();
}

open_lock_callback open_lock_cb;
void stop_open_lock_exception()
{
	if(open_lock_cb != NULL)
	{
		open_lock_cb(KAL_FALSE);
		open_lock_cb = NULL;
	}
	StopTimer(LOCK_OPEN_LOCK_TIMER);
	stop_moto();
	lock_debug_print(MOD_MMI, "iotlock: %s open lock", __FUNCTION__);
	g_lock_opening = KAL_FALSE;
	StartTimer(LOCK_OPEN_G_SENEOR_TIMER, OPEN_G_SENSER_DELAY*1000, motion_sensor_pwr_on_off_switch);
	//should never come here, except the switch cannot work
	lock_debug_print(MOD_MMI, "iotlock_drv: %s should never come here, except the switch cannot work", __FUNCTION__);
}
void save_open_lock_time_to_nvram(kal_uint32 open_lock_time)
{
	order_num info = {0};
	ReadRecordIot(NVRAM_EF_ORDER_NUM_LID, 1, (void*)&info, NVRAM_EF_ORDER_NUM_SIZE);
	info.unlock_timestamp = open_lock_time;
	WriteRecordIot(NVRAM_EF_ORDER_NUM_LID, 1, (void*)&info, NVRAM_EF_ORDER_NUM_SIZE);
}

void get_open_lock_time_from_nvram(kal_uint32 *open_lock_time)
{
	order_num info = {0};

	ReadRecordIot(NVRAM_EF_ORDER_NUM_LID, 1, (void*)&info, NVRAM_EF_ORDER_NUM_SIZE);
	*open_lock_time = info.unlock_timestamp;
}

void stop_open_lock_normal()
{
	order_info *info = NULL;
	if(open_lock_cb != NULL)
	{
		open_lock_cb(!open_lock_exception);
		open_lock_cb = NULL;
	}
	StopTimer(LOCK_OPEN_LOCK_TIMER);
	stop_moto();
	lock_debug_print(MOD_MMI, "iotlock_drv: %s open lock", __FUNCTION__);

	unlock_count_add_one();
	lock_debug_print(MOD_MMI, "iotlock_drv: %s  report loc when open lock", __FUNCTION__);
	g_normal_open_lock_state = TRUE;

	info = get_one_order_info();
	info->unlocks = get_unlock_count();
	info->timestamp = iotlock_srv_brw_get_current_utc_time();
	info->rssi = get_gsm_strength();
	info->serial_num = get_serial_number();
	info->msg_id = PLATFORM_CTRL_ANS_ID;
	info->ans_serial = g_serial_number;
	info->bj = 0;
	if(g_lock_cntx.current_unlock_mode == BT_UNLOCK){
		info->state = BT_UNLOCK_LOC_REPORT<<1;
	} else if(g_lock_cntx.current_unlock_mode == NT_UNLOCK){
		info->state = UNLOCK_LOC_REPORT<<1;
	} else if(g_lock_cntx.current_unlock_mode == SMS_UNLOCK) {
		info->state = SMS_UNLOCK_LOC_REPORT<<1;
	}

	if(read_lock_state() == UNLOCKED) {
		info->state |= 1;
	}
	
	//��¼�¿���ʱ��
	info->unlock_timestamp = iotlock_srv_brw_get_current_utc_time();
	save_open_lock_time_to_nvram(info->unlock_timestamp);
	get_order_num_from_nvram(info->order_num);
	lock_debug_print(MOD_MMI, "iotlock: %s line: %d  info->order_num=%s len = %d", __FUNCTION__,__LINE__, info->order_num,strlen(info->order_num));
	add_one_node(&g_report_list, info);
	report_loc(KAL_FALSE);

	open_gps_and_get_loc(g_lock_cntx.gps_update_run_gap, TIMER_LOC_REPORT);
	
#ifdef __NSK_ECG__
	if(g_lock_cntx.ecg_is_update == 1)
		ECG_PWR_ON();
#endif
	iot_led_ctrl(2,1000,1);		//open lock led
	g_lock_opening = KAL_FALSE;
	StartTimer(LOCK_OPEN_G_SENEOR_TIMER, OPEN_G_SENSER_DELAY*1000, motion_sensor_pwr_on_off_switch);
}

void open_lock_first_play_tone_then_unlock(UNLOCK_TYPE type)
{
	if(get_curr_mode() == IOT_LOCK_MODE_TRANS)
		return;
	if(g_lock_opening == KAL_TRUE||read_lock_state() == UNLOCKED)
		return;
	g_lock_cntx.current_unlock_mode = type;
	open_lock_cb = NULL;
#ifdef __IOT_LOCK_BEEPSPK__
	open_beep_ms(100, 2);
#else
	iot_play_tone_with_filepath_ext(IOT_TONE_UNLOCK,SRV_PROF_RING_TYPE_ONCE,open_lock);
#endif

}

void open_lock(void)
{
	
	if(need_report == KAL_TRUE)
	{
		need_report = KAL_FALSE;
	}
	g_lock_opening = KAL_TRUE;
	acc_sensor_pwr_down();		//stop g-sensor
	lock_debug_print(MOD_MMI, "iotlock_drv: %s open lock", __FUNCTION__);
	open_gps_and_get_loc(0, UNLOCK_LOC_REPORT);
	start_moto();
	StartTimer(LOCK_OPEN_LOCK_TIMER, 5*1000, stop_open_lock_exception);
}
void bt_open_lock(UNLOCK_TYPE type,open_lock_callback cb)
{
	open_lock_first_play_tone_then_unlock(type);
	open_lock_cb = cb;
}
LOCK_STATE read_lock_state(void)
{
	LOCK_STATE state = UNLOCKED;
	state = (GPIO_ReadIO(CLOSE_LOCK_EINT) == 1 ? LOCKED : UNLOCKED);
	return state;
}


kal_bool g_lock_test = KAL_FALSE;
void open_lock_capacitive_hisr_test()
{
	EINT_Mask(OPEN_LOCK_EINT);

	g_lock_test = KAL_TRUE;
	if(GPIO_ReadIO(OPEN_LOCK_EINT)==0)
	{
	lock_debug_print(MOD_MMI, "iotlock_drv: %s eint A", __FUNCTION__);
	EINT_Set_Polarity(OPEN_LOCK_EINT, KAL_TRUE);
	} else {
	lock_debug_print(MOD_MMI, "iotlock_drv: %s eint B", __FUNCTION__);
	stop_moto();
	EINT_Set_Polarity(OPEN_LOCK_EINT, KAL_FALSE);
	}
	

	EINT_UnMask(OPEN_LOCK_EINT);
}

/*close_lock_capacitive_hisr*/
void close_lock_capacitive_hisr_test()
{
	EINT_Mask(CLOSE_LOCK_EINT);
	g_lock_test = KAL_TRUE;
	if(GPIO_ReadIO(CLOSE_LOCK_EINT)==0)
	{
		lock_debug_print(MOD_MMI, "iotlock_drv: %s eint A", __FUNCTION__);

		EINT_Set_Polarity(CLOSE_LOCK_EINT, KAL_TRUE);
	} else {
		lock_debug_print(MOD_MMI, "iotlock_drv: %s eint B", __FUNCTION__);
		stop_moto();
		EINT_Set_Polarity(CLOSE_LOCK_EINT, KAL_FALSE);
	}

	EINT_UnMask(CLOSE_LOCK_EINT);
}
void open_lock_test_start(void)
{
   kal_uint32 save_mask;
   kal_bool state= KAL_FALSE;
   kal_prompt_trace(MOD_MMI, "open_lock_test: enter %s ", __FUNCTION__);
   g_lock_test = KAL_FALSE;
   save_mask = DisableIRQ();

   EINT_Set_HW_Debounce(CLOSE_LOCK_EINT, 20);
   EINT_Registration(CLOSE_LOCK_EINT,KAL_TRUE,KAL_FALSE, close_lock_capacitive_hisr_test, KAL_TRUE);
   EINT_Set_Sensitivity(CLOSE_LOCK_EINT, EDGE_SENSITIVE);
   EINT_Set_Polarity(CLOSE_LOCK_EINT, KAL_FALSE);

   EINT_Set_HW_Debounce(OPEN_LOCK_EINT, 2);
   EINT_Registration(OPEN_LOCK_EINT,KAL_TRUE,KAL_FALSE, open_lock_capacitive_hisr_test, KAL_TRUE);
   EINT_Set_Sensitivity(OPEN_LOCK_EINT, EDGE_SENSITIVE);
   EINT_Set_Polarity(OPEN_LOCK_EINT, KAL_FALSE);
   RestoreIRQ(save_mask);
   start_moto();
   Spconser_Delayms(3000);

}

//�������
kal_bool open_lock_test(void)
{
	/*����*/
	/*kal_uint8 i;
	lock_debug_print(MOD_MMI, "iotlock: %s open lock", __FUNCTION__);
	for (i=0; i<3; i++)
    {
	GPIO_WriteIO(1, MOTO_GPIO1);
	GPIO_WriteIO(0, MOTO_GPIO2);
	
	Spconser_Delayms(200);
	
	GPIO_WriteIO(1, MOTO_GPIO1);
	GPIO_WriteIO(1, MOTO_GPIO2);
	
	Spconser_Delayms(200);
	
	GPIO_WriteIO(0, MOTO_GPIO1);
	GPIO_WriteIO(0, MOTO_GPIO2);
	Spconser_Delayms(1000);
    }*/
    open_lock_test_start();
	if(g_lock_test == KAL_TRUE)
	{
	return MMI_TRUE;
	}
	else
	{
	return MMI_FALSE;
	}

}

//���Ȳ���
kal_bool close_lock_test(void)
{
	lock_debug_print(MOD_MMI, "iotlock: %s close lock", __FUNCTION__);
	GPIO_WriteIO(0, MOTO_GPIO1);
	GPIO_WriteIO(0, MOTO_GPIO2);
	
	return MMI_TRUE;
}


//���Ȳ���
 kal_bool open_beep_ms_test(void)
{

	#if 0//def __IOT_LOCK_BEEPSPK__
	open_beep_ms(300, 1);
	#else
	iot_play_tone_with_filepath(IOT_TONE_LOCK);
	#endif
	
	lock_debug_print(MOD_MMI, "iotlock: %s", __FUNCTION__);

	return MMI_TRUE;



}
 kal_int16 open_Charge_test(void)
{
	kal_int16 i=0;
	char buffer[128+1];

	i=iot_get_battery_isense();
	return i;
	/*	sprintf(buffer, "\r\nisense=%d\r\n",i);
		rmmi_write_to_uart((kal_uint8*)buffer, strlen(buffer), KAL_TRUE);
	if(i>300)
	{
	lock_debug_print(MOD_MMI, "iotlock: %s TRUE", __FUNCTION__);
	 return MMI_TRUE;
	}
	else
	{	
	lock_debug_print(MOD_MMI, "iotlock: %s FALSE", __FUNCTION__);
	return MMI_FALSE;
	}*/

	
}
//ata_speaker_check
 kal_bool ata_speaker_check(void)
 {
	 ATA_RESULT state = ATA_FAIL;
	 GPIO_ModeSetup(IN_SPK_GPIO,0);
	 GPIO_InitIO(0, IN_SPK_GPIO);
	 state = (GPIO_ReadIO(IN_SPK_GPIO) == 1 ? ATA_PASS : ATA_FAIL);
	 kal_prompt_trace(MOD_MMI,"speaker--GPIO_ReadIO:%d",GPIO_ReadIO(IN_SPK_GPIO));
	 return state;
 }
//LED1 CHECK
 static void led1_ctrl_ata(kal_uint16 en) //isink control
 {
	 DCL_HANDLE pwm_handle;
	 PWM_LEVEL_T level;
	 DCL_HANDLE handle; 
	 PMU_CTRL_ISINK_SET_EN isink_en;
 
	 if(en == 0)
	 {
		 level.pwm_level = LED_LIGHT_LEVEL0;
	 }
	 else
	 {
		 level.pwm_level = LED_LIGHT_LEVEL5;
	 }
	 pwm_handle= DclPWM_Open(DCL_MAIN_LCD_BL, MOD_UEM);
	 DclPWM_Control(pwm_handle, PWM_CMD_SET_LEVEL,(DCL_CTRL_DATA_T*)&level);
	 DclPWM_Close(pwm_handle); 
 
	 handle = DclPMU_Open(DCL_PMU, FLAGS_NONE);
 
	 if( en == 0)
	 {
		 // ISINK0
		 isink_en.isink = ISINK0;
		 isink_en.enable = DCL_FALSE;
		 DclPMU_Control(handle, ISINK_SET_EN, (DCL_CTRL_DATA_T *)&isink_en);
 
		 //ISINK1
		 isink_en.isink = ISINK1;
		 isink_en.enable = DCL_FALSE;
		 DclPMU_Control(handle, ISINK_SET_EN, (DCL_CTRL_DATA_T *)&isink_en);
	 }
	 else
	 {
		 // ISINK0 
		 isink_en.isink = ISINK0;
		 isink_en.enable = DCL_TRUE;
		 DclPMU_Control(handle, ISINK_SET_EN, (DCL_CTRL_DATA_T *)&isink_en);
 
		 //ISINK1
		 isink_en.isink = ISINK1;
		 isink_en.enable = DCL_TRUE;
		 DclPMU_Control(handle, ISINK_SET_EN, (DCL_CTRL_DATA_T *)&isink_en);
	 }
	 DclPMU_Close(handle);
 }

 kal_bool ata_led1_check(void)
 {
	 ATA_RESULT state = ATA_FAIL;
	 GPIO_ModeSetup(IN_LED1_GPIO,0);
	 GPIO_InitIO(0, IN_LED1_GPIO);
	 state = (GPIO_ReadIO(IN_LED1_GPIO) == 1 ? ATA_FAIL : ATA_PASS);
	 kal_prompt_trace(MOD_MMI,"led1 GPIO_ReadIO:%d",GPIO_ReadIO(IN_LED1_GPIO));
	 return state;
 }
  void close_led1_ctrl(void)
 {
    led1_ctrl_ata(1);
	kal_prompt_trace(MOD_MMI,"close_led1_ctrl");
  }

 void open_LED1_test(void)
{
	 led1_ctrl_ata(1);
	 
	//StartTimer(ATA_LED1_TEST_TIMER, 20000, close_led1_ctrl);
	kal_prompt_trace(MOD_MMI,"open_LED1_test");
}
 //LED2 CHECK
 
 static void led2_ctrl_ata(kal_uint16 en)//kpled control
 {
	 DCL_HANDLE pwm_handle;
	 PWM_LEVEL_T level;
	 PMU_CTRL_KPLED_SET_EN val_kpled;
	 DCL_HANDLE handle;
 
	 if(en)
	 {
		 level.pwm_level = LED_LIGHT_LEVEL2;
		 val_kpled.enable = DCL_TRUE;
	 }
	 else
	 {
		 level.pwm_level = LED_LIGHT_LEVEL0;
		 val_kpled.enable = DCL_FALSE;
	 }
 
	 pwm_handle= DclPWM_Open(DCL_LED_KP, MOD_UEM);
	 DclPWM_Control(pwm_handle, PWM_CMD_SET_LEVEL,(DCL_CTRL_DATA_T*)&level);
	 DclPWM_Close(pwm_handle); 
 
	 handle = DclPMU_Open(DCL_PMU, FLAGS_NONE);
	 DclPMU_Control(handle, KPLED_SET_EN, (DCL_CTRL_DATA_T *)&val_kpled);
	 DclPMU_Close(handle);
 }
 kal_bool ata_led2_check(void)
 {
	 ATA_RESULT state = ATA_FAIL;
	 GPIO_ModeSetup(IN_LED2_GPIO,0);
	 GPIO_InitIO(0, IN_LED2_GPIO);
	 state = (GPIO_ReadIO(IN_LED2_GPIO) == 1 ? ATA_FAIL : ATA_PASS);
	 kal_prompt_trace(MOD_MMI,"led2 GPIO_ReadIO:%d",GPIO_ReadIO(IN_LED2_GPIO));
	 return state;
 }

   void close_led2_ctrl(void)
 {
    led2_ctrl_ata(1);
	kal_prompt_trace(MOD_MMI,"close_led2_ctrl");
  }
  void open_LED2_test(void)
 {
	  led2_ctrl_ata(1);
	  
	  ///StartTimer(ATA_LED2_TEST_TIMER, 20000, close_led2_ctrl);
	  kal_prompt_trace(MOD_MMI,"open_LED2_test");
	 
 }



//aging_test_timeout

void aging_test_timeout()
{
		
		g_aging_test = KAL_FALSE;
		StopTimer(AGING_TEST_TIMER);
		init_beep();
		GPIO_WriteIO(1, 54);
		stop_moto();
}


void aging_test_count()
{
	
	if( counts != aging_counts)
	{
		counts = aging_counts;
		StartTimer(AGING_TEST_TIMER, 2000, aging_test_count);
	} else {
		kal_prompt_trace(MOD_MMI, "Atatest: aging_test_timeout LINE: %d", __LINE__);
		aging_test_timeout();
	}
}

void aging_test()
{
	kal_prompt_trace(MOD_MMI, "Atatest: %s begin", __FUNCTION__);
	StartTimer(AGING_TEST_TIMER, 3000, aging_test_count);
	start_moto();
}

void aging_test_ata()
{
	kal_uint32 save_mask;

	kal_prompt_trace(MOD_MMI, "Atatest: enter %s ", __FUNCTION__);
	aging_counts = 0;
	counts = 0;
	g_aging_test = KAL_TRUE;
	save_mask = DisableIRQ();

	EINT_Set_HW_Debounce(CLOSE_LOCK_EINT, 20);
	EINT_Registration(CLOSE_LOCK_EINT,KAL_TRUE,KAL_FALSE, close_lock_capacitive_hisr, KAL_TRUE);
	EINT_Set_Sensitivity(CLOSE_LOCK_EINT, EDGE_SENSITIVE);
	EINT_Set_Polarity(CLOSE_LOCK_EINT, KAL_FALSE);

	EINT_Set_HW_Debounce(OPEN_LOCK_EINT, 2);
	EINT_Registration(OPEN_LOCK_EINT,KAL_TRUE,KAL_FALSE, open_lock_capacitive_hisr, KAL_TRUE);
	EINT_Set_Sensitivity(OPEN_LOCK_EINT, EDGE_SENSITIVE);
	EINT_Set_Polarity(OPEN_LOCK_EINT, KAL_FALSE);

	RestoreIRQ(save_mask);
	aging_test();
}

void save_aging_test_result()
{
	kal_uint8 buf[512] = {0};
	
	kal_prompt_trace(MOD_MMI, "Atatest: %s, begain", __FUNCTION__);
	ReadRecordIot(NVRAM_EF_LOCK_AGING_LID, 1, buf, sizeof(buf));
	buf[0] = 0x01;
	//kal_prompt_trace(MOD_MMI, "Atatest: %s, end1, flag=%d", __FUNCTION__, buf[0]);
	WriteRecordIot(NVRAM_EF_LOCK_AGING_LID, 1, buf, sizeof(buf));
	memset(agingbuf, 0, sizeof(agingbuf));	
	//kal_prompt_trace(MOD_MMI, "Atatest: %s, end2, flag=%d", __FUNCTION__, buf[0]);
	ReadRecordIot(NVRAM_EF_LOCK_AGING_LID, 1, buf, sizeof(buf));
	memcpy(agingbuf, buf, strlen(buf));
	
	kal_prompt_trace(MOD_MMI, "Atatest: %s, end, flag=%d", __FUNCTION__, buf[0]);
}

void aging_test_callback()
{
	
	kal_prompt_trace(MOD_MMI, "Atatest: %s count:%d", __FUNCTION__, aging_counts);
		aging_counts += 1;
		if(aging_counts >= 3000){
			
			stop_moto();	
			StopTimer(AGING_TEST_TIMER);
			//ok
			
			save_aging_test_result();
			g_aging_test = KAL_FALSE;
		} 
}

void open_lock_ata(void)
{
	lock_debug_print(MOD_MMI, "iotlock_drv: %s open lock", __FUNCTION__);
	memset(at_sendbuf,0,sizeof(at_sendbuf));
	sprintf(at_sendbuf, "S1=%d", GPIO_ReadIO(OPEN_LOCK_EINT));
	rmmi_write_to_uart((kal_uint8*)at_sendbuf, strlen(at_sendbuf), KAL_TRUE);
	Spconser_Delayms(100);
	memset(at_sendbuf,0,sizeof(at_sendbuf));
	sprintf(at_sendbuf, "S2=%d", GPIO_ReadIO(CLOSE_LOCK_EINT));
	rmmi_write_to_uart((kal_uint8*)at_sendbuf, strlen(at_sendbuf), KAL_TRUE);
	//start moto
	start_moto();
	StartTimer(LOCK_OPEN_LOCK_TIMER, 5*1000, stop_open_lock_exception);
}

void WriteDomain(char * buffer)
{
	DOMAIN_T domainbuffer;
	nvram_ef_iot_lock_struct info;
	
	ReadRecordIot(NVRAM_EF_IOT_LOCK_LID, 1, &info, NVRAM_EF_IOT_LOCK_SIZE);
	memset(info.ip_domain, 0, sizeof(info.ip_domain));
	kal_prompt_trace(MOD_ENG,"info.ip_domain=%s",buffer);
	memcpy(info.ip_domain, buffer, strlen(buffer));
	
	WriteRecordIot(NVRAM_EF_IOT_LOCK_LID, 1, &info, NVRAM_EF_IOT_LOCK_SIZE);
	memset(info.ip_domain, 0, sizeof(info.ip_domain));	
	ReadRecordIot(NVRAM_EF_IOT_LOCK_LID, 1, &info, NVRAM_EF_IOT_LOCK_SIZE);
	

	memcpy(g_lock_cntx.domain.domain_buffer, info.ip_domain, sizeof(info.ip_domain));
	kal_prompt_trace(MOD_ENG,"DOMAIN-domain.domain_buffer=%s",g_lock_cntx.domain.domain_buffer);
	
}

void WritePort(kal_uint32 port)
{
	nvram_ef_iot_lock_struct info;
	
	ReadRecordIot(NVRAM_EF_IOT_LOCK_LID, 1, &info, NVRAM_EF_IOT_LOCK_SIZE);
	//memset(info.port, 0, sizeof(info.port));
	info.port =0;
	kal_prompt_trace(MOD_ENG,"info.port=%d",port);
	//memcpy(info.port, port, strlen(port));
	info.port = port;
	WriteRecordIot(NVRAM_EF_IOT_LOCK_LID, 1, &info, NVRAM_EF_IOT_LOCK_SIZE);
	//memset(info.port, 0, sizeof(info.port));	
	info.port =0;
	ReadRecordIot(NVRAM_EF_IOT_LOCK_LID, 1, &info, NVRAM_EF_IOT_LOCK_SIZE);
	

	//memcpy(g_lock_cntx.domain.port, info.port, sizeof(info.port));
	g_lock_cntx.domain.port = info.port;
	kal_prompt_trace(MOD_ENG,"g_lock_cntx.domain.port=%d",g_lock_cntx.domain.port);
	
}

//end

#ifdef __NSK_ECG__

void dump_uart_data(kal_uint8 *buf, kal_uint16 len)
{
	kal_uint16 i = 0;
	//kal_prompt_trace(MOD_MMI,"%s--dump uart buff", __FUNCTION__);
	for(i=0; i<len; i++)
	{
		kal_prompt_trace(MOD_MMI,"[data %d]:%x",i,buf[i]);
	}
}

static void UART_TurnOnPower(UART_PORT port, kal_bool on)
{
    DCL_HANDLE handle;
    UART_CTRL_POWERON_T data;

    handle = DclSerialPort_Open(port, 0);
    data.bFlag_Poweron = on;
    DclSerialPort_Control(handle, UART_CMD_POWER_ON, (DCL_CTRL_DATA_T*)&data);

    DclSerialPort_Close(handle);
}

static void UART_SetDCBConfig(DCL_DEV port, UART_CONFIG_T *UART_Config, DCL_UINT32 ownerid)
{
	DCL_HANDLE handle;
	UART_CTRL_DCB_T data;

	data.u4OwenrId = ownerid;
	data.rUARTConfig.u4Baud = UART_Config->u4Baud;
	data.rUARTConfig.u1DataBits = UART_Config->u1DataBits;
	data.rUARTConfig.u1StopBits = UART_Config->u1StopBits;
	data.rUARTConfig.u1Parity = UART_Config->u1Parity;
	data.rUARTConfig.u1FlowControl = UART_Config->u1FlowControl;
	data.rUARTConfig.ucXonChar = UART_Config->ucXonChar;
	data.rUARTConfig.ucXoffChar = UART_Config->ucXoffChar;
	data.rUARTConfig.fgDSRCheck = UART_Config->fgDSRCheck;
	handle = DclSerialPort_Open(port,0);
	DclSerialPort_Control(handle,SIO_CMD_SET_DCB_CONFIG, (DCL_CTRL_DATA_T*)&data);
	DclSerialPort_Close(handle);
}

static kal_uint32 UART_Open(UART_PORT port, module_type ownerid)
{
	DCL_HANDLE handle;
	UART_CTRL_OPEN_T data;
	kal_uint32  status;

	data.u4OwenrId = ownerid;
	handle = DclSerialPort_Open(port,0);
	status = DclSerialPort_Control(handle,SIO_CMD_OPEN, (DCL_CTRL_DATA_T*)&data);

	return status;
}

static module_type UART_GetOwnerID(UART_PORT port)
{
	DCL_HANDLE handle;
	UART_CTRL_OWNER_T data;
	handle = DclSerialPort_Open(port,0);
	DclSerialPort_Control(handle,SIO_CMD_GET_OWNER_ID, (DCL_CTRL_DATA_T*)&data);
	return (module_type)(data.u4OwenrId);
}

static void UART_SetOwner(UART_PORT port, module_type ownerid)
{
	DCL_HANDLE handle;
	UART_CTRL_OWNER_T data;
	data.u4OwenrId = ownerid;
	handle = DclSerialPort_Open(port,0);
	DclSerialPort_Control(handle,SIO_CMD_SET_OWNER, (DCL_CTRL_DATA_T*)&data);
}

static DCL_UINT16 UART_GetBytesAvail(DCL_DEV port)
{
	DCL_HANDLE handle;
	UART_CTRL_RX_AVAIL_T data;

	handle = DclSerialPort_Open(port,0);
	DclSerialPort_Control(handle,SIO_CMD_GET_RX_AVAIL, (DCL_CTRL_DATA_T*)&data);
	DclSerialPort_Close(handle);
	return data.u2RetSize;
}

static kal_uint16 UART_GetBytes(UART_PORT port, kal_uint8 *Buffaddr, kal_uint16 Length, kal_uint8 *status, module_type ownerid)
{
    DCL_HANDLE handle;
    UART_CTRL_GET_BYTES_T data;
    data.u4OwenrId = ownerid;
    data.u2Length = Length;
    data.puBuffaddr = Buffaddr;
    data.pustatus = status;
    handle = DclSerialPort_Open(port,0);
    DclSerialPort_Control(handle,SIO_CMD_GET_BYTES, (DCL_CTRL_DATA_T*)&data);
    return data.u2RetSize;
}

kal_uint16 ECG_UART_Read(kal_uint8 *buf, kal_uint16 maxlen, UART_PORT port, module_type ownerid)
{
	kal_uint16 readlen;
	kal_uint16 avail;
	kal_uint16 retlen = 0;
	kal_uint8  status = 0;
	while ((avail = U_GetBytesAvail_VFIFO(port) && retlen < maxlen)>0)
	{
		if (avail + retlen > maxlen)
			avail = maxlen - retlen;
		readlen = U_GetBytes_VFIFO(port, (kal_uint8 *)(buf+retlen),(kal_uint16)avail, &status, ownerid);
		retlen +=  readlen;
	}
	U_ClrRxBuffer(port, ownerid);
	return retlen;
}

kal_uint8 ECG_UART_Write(kal_uint8 *buf, kal_uint16 buflen, UART_PORT port, module_type ownerid)
{
	kal_uint8 ret = FALSE;
	kal_uint16 sent;
	module_type UART_Owner = 0;
	sent = 0;
	//kal_prompt_trace(MOD_MMI,"%s--ECG_UART write!", __FUNCTION__);
	U_Purge(port, RX_BUF, ownerid);
	U_Purge(port, TX_BUF, ownerid);
	U_ClrTxBuffer(port, ownerid);
	U_ClrRxBuffer(port, ownerid);
	//sent = UART_PutBytes(port, (kal_uint8 *)buf, (kal_uint16)buflen, ownerid);
	sent = U_PutBytes_VFIFO(port, (kal_uint8 *)buf, (kal_uint16)buflen, ownerid);

	if (sent == buflen)
		ret = TRUE;
	return ret;
}

void ECG_PWR_ON(void)
{
	ECG_UART_Init();
	GPIO_ModeSetup(41, 0);//���ó�GPIOģʽ
	GPIO_InitIO(1, 41);	 //���ó����
	GPIO_WriteIO(1, 41);	 // ON
}

void ECG_PWR_OFF(void)
{
	GPIO_ModeSetup(41, 0);//���ó�GPIOģʽ
	GPIO_InitIO(1, 41);	 //���ó����
	GPIO_WriteIO(0, 41);	// OFF
	ECG_UART_DeInit();
}

void ECG_UART_DeInit(void)
{
	if(gbUartInitialized)
	{
		ClearProtocolEventHandler(MSG_ID_UART_READY_TO_READ_IND);
		U_SetOwner(ECG_UART_PORT, gbUartOwnerId);
		U_SetBaudRate(ECG_UART_PORT, UART_BAUD_115200, gbUartOwnerId);
		gbUartInitialized = KAL_FALSE;
	}
}
void ECG_UART_Init(void)
{
	kal_uint32 status = 0;
	if(gbUartInitialized)
	{
		return;
	}
	//ECG_PWR_ON();
	UART_TurnOnPower(ECG_UART_PORT, KAL_TRUE);	//open uart

	kal_prompt_trace(MOD_MMI,"ECG_UART_Init!");
	uart_handler = L1SM_GetHandle();
	//L1SM_SleepDisable(uart_handler);

	//����uart power
	//UART_TurnOnPower(ECG_UART_PORT, KAL_TRUE);  //open uart
	status =  UART_Open(ECG_UART_PORT, ECG_OWNER_ID);
	//kal_prompt_trace(MOD_MMI, "UART_Open return %d", status);

	gbUartOwnerId = UART_GetOwnerID(ECG_UART_PORT);
	kal_prompt_trace(MOD_MMI,"Old gbUartOwnerId=%d",gbUartOwnerId);
	//DCBdefault = (UART_CONFIG_T *)&UART_DefaultConfig;
	U_SetOwner(ECG_UART_PORT, MOD_MMI);
	//  �趨uart �����ʵ���Ϣ��ע���ڵ��ô˺���֮ǰ��Ҫ�ȳ�ʼ��Dcb�ṹ��
	//UART_SetDCBConfig(UART_LIN_PORT, DCBdefault, ECG_OWNER_ID);
	U_SetBaudRate(ECG_UART_PORT, UART_BAUD_57600, MOD_MMI);
	//����MSG_ID_UART_READY_TO_READ_IND��Ϣ����Ӧ����
	ClearProtocolEventHandler(MSG_ID_UART_READY_TO_READ_IND);
	U_ClrTxBuffer(ECG_UART_PORT, MOD_MMI);
	U_ClrRxBuffer(ECG_UART_PORT, MOD_MMI);
	SetProtocolEventHandler(ECG_UART_handler, MSG_ID_UART_READY_TO_READ_IND);
	gbUartInitialized = KAL_TRUE;
	nsk_ecg_set_raw_sample_rate(512);
	nsk_ecg_init();
}

void ECG_data_handler2(void)
{
	kal_uint16 i;
	kal_uint8 * ptr_raw_data = NULL;
	kal_int16 sample = 0;
	kal_int16 rri      = 0; // R-to-R interval
	kal_int16 rriCount = 0;
	kal_int16 sq       = 0; // signal quality
	kal_int16 osq      = 0; // overall signal quality
	kal_int16 hr       = 0; // Heart Rate
	kal_int16 mood     = 0;
	kal_int16 stress   = 0;
	kal_int16 hrv 	   = 0;
	kal_int16 htz      = 0;
	short user_stress_history[128] = { 0 };
	BCD datetime[6] = {0};
	kal_uint32 ecg_current_time = 0;
	
	ptr_raw_data = ECG_raw_data_buf;
	if(ptr_raw_data == NULL)
		return;
	for(i=0;i<gwECG_data_len-8;i++)
	{
		if((*(ptr_raw_data+i)==0xAA)&&(*(ptr_raw_data+i+1)==0xAA))
		{
			if(*(ptr_raw_data+i+2)== 0x04)
			{
				sample = (kal_int16)((*(ptr_raw_data+i+5))<<8);
				sample |= *(ptr_raw_data+i+6);
				//kal_prompt_trace(MOD_MMI, "%d" , sample);
				nsk_ecg_update(sample);

				if( nsk_ecg_is_new_beat() ) 
				{
					kal_prompt_trace(MOD_MMI, "BEAT!");
					rri      = nsk_ecg_get_rri();
					rriCount = nsk_ecg_get_rri_count();
					sq       = nsk_ecg_get_signal_quality();
					osq      = nsk_ecg_get_overall_signal_quality();
					hr       = nsk_ecg_compute_hr();
					
					kal_prompt_trace(MOD_MMI, "%s--hr=%d, rri=%d, rriCount=%d, sq=%d, osq=%d", __FUNCTION__, hr, rri, rriCount, sq, osq);
					if( rriCount == CALCULATION_COUNT ) {
						hrv 	 = nsk_ecg_compute_hrv();
						mood   = nsk_ecg_compute_mood();
						stress = nsk_ecg_compute_stress(
							ecg_feedback, // user feedback for previous session, 1-100. Set to 0 if no feedback.
							ecg_gender, // 0 for male, 1 for female
							ecg_age, // age, in years.  16-90
							ecg_height, // height, in cm. 1-300
							ecg_weight, // weight, in kg. 1-300
							user_stress_history // short integer array of length NEL_IOG
						);
						kal_prompt_trace(MOD_MMI, "%s--mood=%d, stress=%d", __FUNCTION__, mood, stress);
						htz 	 = nsk_ecg_get_heart_training_zone(
							  	ecg_gender, // 0 for male, 1 for female
							 	ecg_age, // age, in years.  16-90
								ecg_weight, // weight, in kg. 1-300
							hr);
						nsk_ecg_set_raw_sample_rate(512);
						nsk_ecg_init();
						kal_prompt_trace(MOD_MMI, "%s:hrv=%d--htz=%d", __FUNCTION__, hrv, htz);
					}
					if(ECG_RESULT_LEN>MAX_ECG_RESULT_LEN-ECG_PARA_NUM)
						ECG_RESULT_LEN = 0;
					g_ecg_out_buff_len ++;
					
					rri+=rri;
					hrv+=hrv;
					sq+=sq;
					htz+=htz;
					hr+=hr;
					mood+=mood;
					stress+=stress;
					if(g_ecg_out_buff_len>=g_lock_cntx.ecg_samp_time_gap){
						
						rri = rri/g_lock_cntx.ecg_samp_time_gap;
						hrv = hrv/g_lock_cntx.ecg_samp_time_gap;
						sq = sq/g_lock_cntx.ecg_samp_time_gap;
						htz = htz/g_lock_cntx.ecg_samp_time_gap;
						hr = hr/g_lock_cntx.ecg_samp_time_gap;
						mood = mood/g_lock_cntx.ecg_samp_time_gap;
						stress = stress/g_lock_cntx.ecg_samp_time_gap;

						kal_prompt_trace(MOD_MMI, "%s--hr=%d, hrv=%d, sq=%d, sq=%d, htz=%d, mood=%d, stress=%d", __FUNCTION__, hr, hrv, sq, sq, htz,mood,stress);
						ecg_current_time = iotlock_srv_brw_get_current_utc_time();

						ecg_current_time = soc_htonl(ecg_current_time);
						kal_prompt_trace(MOD_MMI, "%s--%d ecg_current_time%d", __FUNCTION__, __LINE__,ecg_current_time);
						ECG_RESULT_BUFF[ECG_RESULT_LEN]=ecg_current_time%256;
						ecg_current_time = ecg_current_time/256;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]=ecg_current_time%256;
						ecg_current_time = ecg_current_time/256;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]=ecg_current_time%256;
						ecg_current_time = ecg_current_time/256;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]=ecg_current_time%256;

						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x00;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x36;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x02;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN] 	= rri>>8;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= rri;
										
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x00;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x37;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x02;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= hrv>>8;		//replace rriCount
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= hrv;

						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x00;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x38;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x02;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= sq>>8;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= sq;

						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x00;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x39;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x02;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= htz>>8;	//replace osq
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= htz;

						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x00;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x3a;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x02;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= hr>>8;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= hr;

						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x00;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x3b;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x02;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= mood>>8;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= mood;

						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x00;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x3c;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x02;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= stress>>8;
						ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= stress;

						kal_prompt_trace(MOD_MMI, "lock_drv_ecg: ECG_RESULT_BUFF[ECG_RESULT_LEN-1]=%d, ECG_RESULT_LEN=%d", ECG_RESULT_BUFF[ECG_RESULT_LEN], ECG_RESULT_LEN);
						ECG_RESULT_LEN++;
						rri=0;
						hrv=0;
						sq=0;
						htz=0;
						hr=0;
						mood=0;
						stress=0;
						g_ecg_out_count++;
						kal_prompt_trace(MOD_MMI, "lock_drv_ecg: %s(),%d g_ecg_out_count=%d", __FUNCTION__,__LINE__ ,g_ecg_out_count);
						g_ecg_out_buff_len = 0;
					}
					
					kal_prompt_trace(MOD_MMI, "lock_drv_ecg: %s(),%d g_ecg_out_buff_len=%d", __FUNCTION__,__LINE__ ,g_ecg_out_buff_len);
					kal_prompt_trace(MOD_MMI, "lock_drv_ecg: %s(),%d ecg_update_data_time_gap=%d", __FUNCTION__,__LINE__ ,g_lock_cntx.ecg_update_data_time_gap);
					kal_prompt_trace(MOD_MMI, "lock_drv_ecg: %s(),%d ecg_samp_time_gap=%d", __FUNCTION__,__LINE__ ,g_lock_cntx.ecg_samp_time_gap);

					if(g_ecg_out_count == (g_lock_cntx.ecg_update_data_time_gap/g_lock_cntx.ecg_samp_time_gap))
					{
						memset(g_ecg_result_buff,0,sizeof(g_ecg_result_buff));
						memcpy(g_ecg_result_buff, ECG_RESULT_BUFF, g_ecg_out_count*ECG_PARA_NUM);
						g_ecg_out_count = 0;
						kal_prompt_trace(MOD_MMI, "lock_drv_ecg: %s(),%d g_lock_cntx.ecg_is_update=%d", __FUNCTION__,__LINE__ ,g_lock_cntx.ecg_is_update);
						kal_prompt_trace(MOD_MMI, "lock_drv_ecg: %s(),%d g_ecg_result_buff=%s", __FUNCTION__,__LINE__ ,g_ecg_result_buff);
						kal_prompt_trace(MOD_MMI, "lock_drv_ecg: %s(),%d strlen(ECG_RESULT_BUFF)=%s", __FUNCTION__,__LINE__ ,strlen(ECG_RESULT_BUFF));

						if(g_lock_cntx.ecg_is_update==1)
						{
							open_lock_ecg_msg_upload();

						}
					}
					
				}
			}
		}
	}
			StartTimer(LOCK_ECG_TIMER2, 1000, ECG_data_handler2);
}

void ECG_data_handler3(void)
{
	kal_uint16 i;
	kal_uint8 * ptr_raw_data = NULL;
	kal_int16 sample = 0;
	kal_int16 rri      = 0; // R-to-R interval
	kal_int16 rriCount = 0;
	kal_int16 sq       = 0; // signal quality
	kal_int16 osq      = 0; // overall signal quality
	kal_int16 hr       = 0; // Heart Rate
	kal_int16 mood     = 0;
	kal_int16 stress   = 0;
	short user_stress_history[128] = { 0 };

	ptr_raw_data = ECG_raw_data_buf;
	if(ptr_raw_data == NULL)
		return;
	//dump_uart_data(ECG_raw_data_buf,gwECG_data_len);
	kal_prompt_trace(MOD_MMI, "ECG data handler3 %d", gwECG_data_len);

	for(i=0;i<gwECG_data_len-8;i++)
	{
		if((*(ptr_raw_data+i)==0xAA)&&(*(ptr_raw_data+i+1)==0xAA))
		{
			if(*(ptr_raw_data+i+2)== 0x04)
			{
				sample = (kal_int16)((*(ptr_raw_data+i+5))<<8);
				sample |= *(ptr_raw_data+i+6);
				//kal_prompt_trace(MOD_MMI, "%d", sample);
				nsk_ecg_update(sample);

				if( nsk_ecg_is_new_beat() ) 
				{
					kal_prompt_trace(MOD_MMI, "BEAT!");
					rri      = nsk_ecg_get_rri();
					rriCount = nsk_ecg_get_rri_count();
					sq       = nsk_ecg_get_signal_quality();
					osq      = nsk_ecg_get_overall_signal_quality();
					hr       = nsk_ecg_compute_hr();
					kal_prompt_trace(MOD_MMI, "%s--hr=%d, rri=%d, rriCount=%d, sq=%d, osq=%d", __FUNCTION__, hr, rri, rriCount, sq, osq);

					if( rriCount == CALCULATION_COUNT ) {
						mood   = nsk_ecg_compute_mood();
						stress = nsk_ecg_compute_stress(
							ecg_feedback, // user feedback for previous session, 1-100. Set to 0 if no feedback.
							ecg_gender, // 0 for male, 1 for female
							ecg_age, // age, in years.  16-90
							ecg_height, // height, in cm. 1-300
							ecg_weight, // weight, in kg. 1-300
							user_stress_history // short integer array of length NEL_IOG
						);
						nsk_ecg_set_raw_sample_rate(512);
						nsk_ecg_init();
						kal_prompt_trace(MOD_MMI, "%s--mood=%d, stress=%d", __FUNCTION__, mood, stress);
					}
					if(ECG_RESULT_LEN>MAX_ECG_RESULT_LEN-28)
						ECG_RESULT_LEN = 0;

					ECG_RESULT_BUFF[ECG_RESULT_LEN]		= 0x00;
					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x36;
					ECG_RESULT_BUFF[++ECG_RESULT_LEN] 	= rri>>8;
					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= rri;

					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x00;
					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x37;
					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= rriCount>>8;
					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= rriCount;

					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x00;
					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x38;
					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= sq>>8;
					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= sq;

					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x00;
					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x39;
					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= osq>>8;
					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= osq;

					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x00;
					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x3a;
					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= hr>>8;
					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= hr;

					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x00;
					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x3b;
					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= mood>>8;
					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= mood;

					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x00;
					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= 0x3c;
					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= stress>>8;
					ECG_RESULT_BUFF[++ECG_RESULT_LEN]	= stress;

					kal_prompt_trace(MOD_MMI, "ECG_RESULT_LEN=%d", ECG_RESULT_LEN);
					ECG_RESULT_LEN++;
				}
			}
		}
	}
	gwECG_data_len=0;
}

void ECG_UART_handler(void *msg)
{
	kal_uint16 i;
	kal_uint16 temp_sum = 0;
	kal_uint16 temp_len = 0;
	kal_uint8 * prt_buff = NULL;
	kal_int16 sample = 0;
	kal_uint16 data_len = 0;
	kal_uint16 send_cnt=0;
	uart_ready_to_read_ind_struct *tmp = (uart_ready_to_read_ind_struct *)msg;
	kal_prompt_trace(MOD_MMI,"ECG UART handler!");

	if (UART_GetOwnerID(tmp->port) != ECG_OWNER_ID)
		return ;
	if (tmp->port != ECG_UART_PORT)
		return;

	gwLenUartBuffer = ECG_UART_Read(gabyUartBuffer, sizeof(gabyUartBuffer), ECG_UART_PORT, ECG_OWNER_ID);
	kal_prompt_trace(MOD_MMI,"ecg recv len:%d, %s", gwLenUartBuffer, gabyUartBuffer);
	for(i=0;i<gwLenUartBuffer;i++)
	{
		ECG_raw_data_buf[i] = gabyUartBuffer[i];
		gabyUartBuffer[i]  = 0;
	}
	gwECG_data_len = gwLenUartBuffer;
	gwLenUartBuffer = 0;
	StartTimer(LOCK_ECG_TIMER2, 5, ECG_data_handler2);
}
#endif

void iot_battery_over_temp_callback(void)
{
	Word battery_level = 0;
	kal_int16 cur_temp = 0x00;
	nvram_ef_iot_lock_struct info;
	ReadRecordIot(NVRAM_EF_IOT_LOCK_LID, 1, &info, NVRAM_EF_IOT_LOCK_SIZE);
	cur_temp = iot_get_battery_temperature();
	//over temperature for charge protect
	if(cur_temp > IOT_BATTERY_MAX_TEMP)
	{
		iot_bat_charger_en(0);		//stop charge
		kal_prompt_trace(MOD_MMI,"%s STOP charge:BAT HIGH temperature:%d",__FUNCTION__, cur_temp);
	}else if(cur_temp < IOT_BATTERY_MIN_TEMP)
	{
		iot_bat_charger_en(0);		//stop charge
		kal_prompt_trace(MOD_MMI,"%s STOP charge:BAT LOW temperature:%d",__FUNCTION__, cur_temp);
	}
	else
	{
		iot_bat_charger_en(1);		//start charge
		kal_prompt_trace(MOD_MMI,"START charge:BAT temperature:%d", cur_temp);
	}

	//over temperature for discharge protect
	battery_level = iot_get_battery_percentage();
	kal_prompt_trace(MOD_MMI,"iotlock: %s battery_level: %d",__func__, battery_level);
	if((cur_temp < IOT_BATTERY_DISCHARGE_MIN_TEMP)||(cur_temp > IOT_BATTERY_DISCHARGE_MAX_TEMP))
	{
		if(is_temp_warn_state  == KAL_FALSE)
		{
			if(cur_temp < IOT_BATTERY_DISCHARGE_MIN_TEMP)
				lock_warn_report_loc(LOW_TEMP_LOC_REPORT);
			if(cur_temp > IOT_BATTERY_DISCHARGE_MAX_TEMP)
				lock_warn_report_loc(HIGH_TEMP_LOC_REPORT);
		}
		is_temp_warn_state = KAL_TRUE;
	}
	else
	{
		is_temp_warn_state = KAL_FALSE;
	}
	if(get_curr_mode() != IOT_LOCK_MODE_TRANS)
	{
		if(battery_level < 20)
		{
			if(is_volt_warn_state == KAL_FALSE)
			{
				lock_warn_report_loc(LOW_POWER_LOC_REPORT);
			}
			is_volt_warn_state = KAL_TRUE;
		}
		else 
		{
			if(battery_level > 25) 
			{
				if(is_volt_warn_state == KAL_TRUE)
				{
					lock_warn_report_loc(NORMAL_POWER_LOC_REPORT);
				}
				is_volt_warn_state = KAL_FALSE;
			}
			
			if(info.mode != IOT_LOCK_MODE_NORMAL)
			{
				if((cur_temp > IOT_BATTERY_DISCHARGE_MIN_TEMP)&&(cur_temp < IOT_BATTERY_DISCHARGE_MAX_TEMP))
				{
					kal_prompt_trace(MOD_MMI,"%s START NORMAL MODE:BAT temperature:%d,mode=%d",__FUNCTION__, cur_temp,info.mode);
					if(battery_level > 25) 
					{
						switch_lock_mode(IOT_LOCK_MODE_NORMAL);
					}
				}
			}
		}
	}
}

void iot_led_ctrl(kal_uint8 led_no, kal_uint16 time, kal_uint8 count)
{
	if(time < 1)
		return;
	if(count <1)
		return;

	if(led_no == 0x01)
	{
		if(!IsMyTimerExist(LOCK_LED1_TIMER))
		{
			led1_ctrl_time = time;
			led1_ctrl_count = count;
			led1_ctrl_state = 0x01;
			StartTimer(LOCK_LED1_TIMER, led1_ctrl_time, led1_ctrl_callback);
		}
	}
	else if(led_no == 0x02)
	{
		if(!IsMyTimerExist(LOCK_LED2_TIMER))
		{
			led2_ctrl_time = time;
			led2_ctrl_count = count;
			led2_ctrl_state = 0x01;
			StartTimer(LOCK_LED2_TIMER, led2_ctrl_time, led2_ctrl_callback);
		}
	}
}

void led1_ctrl_callback(void)
{
	if(led1_ctrl_count == 0)
	{
		led1_ctrl(0);
		return;
	}
	if(led1_ctrl_state ==0x01)
	{
		led1_ctrl(1);
		led1_ctrl_state=0;
		led1_ctrl_count--;
	}
	else
	{
		led1_ctrl(0);
		led1_ctrl_state=1;
	}
	StartTimer(LOCK_LED1_TIMER, led1_ctrl_time, led1_ctrl_callback);
}


void led2_ctrl_callback(void)
{
	if(led2_ctrl_count == 0)
	{
		led2_ctrl(0);
		return;
	}
	if(led2_ctrl_state ==0x01)
	{
		led2_ctrl(1);
		led2_ctrl_state=0;
		led2_ctrl_count--;
	}
	else
	{
		led2_ctrl(0);
		led2_ctrl_state=1;
	}
	StartTimer(LOCK_LED2_TIMER, led2_ctrl_time, led2_ctrl_callback);
}

void iot_led_on_off_ctrl(kal_uint8 led_no, kal_bool b_on)
{
	if(led_no == 1)
	{
		led1_ctrl_ata(b_on);
	}
	else if(led_no == 2)
	{
		led2_ctrl_ata(b_on);
	}
}

void motion_sensor_pwr_on_off_switch(void)
{
	if(get_curr_mode() == IOT_LOCK_MODE_NORMAL||get_curr_mode() == IOT_LOCK_MODE_LOW_ENERGY)
	{
		if(read_lock_state() == UNLOCKED)
			acc_sensor_init_violent();
		else
			acc_sensor_init_with_interrupt();
	}
	else
		acc_sensor_pwr_down();
}

#ifdef __UART_SLEEP_WAKEUP__
void iot_system_sleep_mode_switch(void)
{
	kal_uint8 sleep_key = 0x0;
	sleep_key = iot_get_bkup_nv_first_byte();
	if(sleep_key == 0xAA)
	{
		kal_prompt_trace(MOD_MMI,"%s uart1_sleep_enable: sleep_key=%x",__FUNCTION__, sleep_key);
		//uart1_sleep_enable();
	}
	else
	{
		kal_prompt_trace(MOD_MMI,"%s uart1_sleep_disable: sleep_key=%x",__FUNCTION__, sleep_key);
		uart1_sleep_disable();
	}
}

//AT+ESLEEP
void iot_set_system_sleep_mode_enable(void)
{
	kal_uint8 sleep_key = 0x0;
	sleep_key = iot_get_bkup_nv_first_byte();
	kal_prompt_trace(MOD_MMI,"%s uart1_sleep_enable: sleep_key=%x",__FUNCTION__, sleep_key);
	if(sleep_key == 0xAA)
	{
		uart1_sleep_enable();
	}
	else
	{
		iot_set_bkup_nv_first_byte(0xAA);
		uart1_sleep_enable();
	}
	kal_prompt_trace(MOD_MMI,"%s",__FUNCTION__);
}

//AT+DSLEEP
void iot_set_system_sleep_mode_disable(void)
{
	kal_uint8 sleep_key = 0x0;
	sleep_key = iot_get_bkup_nv_first_byte();
	kal_prompt_trace(MOD_MMI,"%s--sleep_key=0x00",__FUNCTION__, sleep_key);
	if(sleep_key == 0xAA)
	{
		iot_set_bkup_nv_first_byte(0x00);
		uart1_sleep_disable();
	}
	else
	{
		uart1_sleep_disable();
	}
	kal_prompt_trace(MOD_MMI,"%s",__FUNCTION__);
}

#endif

void iot_motor_start(kal_bool b_dir)
{
	if(b_dir)
	{
		GPIO_WriteIO(0, MOTO_GPIO1);
		GPIO_WriteIO(1,MOTO_GPIO2);
	}
	else
	{
		GPIO_WriteIO(1, MOTO_GPIO1);
		GPIO_WriteIO(0,MOTO_GPIO2);
	}
}

kal_uint8 iot_get_switch_state(kal_uint8 num)
{
	if(num == 1)
	{
		return GPIO_ReadIO(OPEN_LOCK_EINT);
	}
	else if(num == 2)
	{
		return GPIO_ReadIO(CLOSE_LOCK_EINT);
	}
}

void iot_motor_stop(void)
{
	//brake
	GPIO_WriteIO(1, MOTO_GPIO1);
	GPIO_WriteIO(1, MOTO_GPIO2);

	Spconser_Delayms(10);

	//stop
	GPIO_WriteIO(0, MOTO_GPIO1);
	GPIO_WriteIO(0, MOTO_GPIO2);
}

void iot_acc_sensor_get_xyz_mg(kal_int16 *accl_x,kal_int16 *accl_y,kal_int16 *accl_z)
{
	acc_sensor_get_xyz(accl_x, accl_y, accl_z);
	(*accl_x) *= 4;
	(*accl_y) *= 4;
	(*accl_z) *= 4;
	//kal_prompt_trace(MOD_MMI,"%s-acc_x=%d,acc_y=%d,acc_z=%d",__FUNCTION__,(*accl_x),(*accl_y),(*accl_z));
}

void iot_acc_sensor_get_xyz_test(void)
{
	kal_int16 accl_x=0, accl_y=0, accl_z=0;
	iot_acc_sensor_get_xyz_mg(&accl_x, &accl_y, &accl_z);
	kal_prompt_trace(MOD_MMI,"%s-acc_x=%d,acc_y=%d,acc_z=%d",__FUNCTION__, accl_x, accl_y , accl_z);
	StartTimer(LOCK_ATA_AT_TIMER4,1000,iot_acc_sensor_get_xyz_test);
}

void iot_uart1_power_ctrl(kal_bool b_on)
{
	UART_TurnOnPower(uart_port1, b_on);
}

void iot_find_bike_led_flash(void)
{
	StartTimer(LOCK_LED3_TIMER,100,iot_led_flash);
}

void iot_led_flash(void)
{
	iot_led_ctrl(2,200,3);
	StartTimer(LOCK_LED3_TIMER,2000,iot_led_flash);
	led2_flash_count++;
	if(led2_flash_count > 30)
	{
		led2_flash_count = 0;
		StopTimer(LOCK_LED3_TIMER);
	}
}

kal_bool iot_led_speak_warning_callback(void)
{
	led2_flash_count = 0;
	StopTimer(LOCK_LED3_TIMER);
#ifdef __IOT_LOCK_BEEPSPK__
	open_beep_ms(100, 4);
#else
	iot_play_tone_with_filepath(IOT_TONE_WARN);
#endif
	iot_find_bike_led_flash();
	return KAL_TRUE;
}

void gprs_and_sms_find_bike_led_flash(void)
{
	if(g_lock_cntx.led_flash_counts>0)
	{
		iot_led_ctrl(2,200,3);
		StartTimer(FIND_BIKE_LED_TIMER,2000,gprs_and_sms_find_bike_led_flash);
		g_lock_cntx.led_flash_counts--;
	}
	else
	{
		StopTimer(FIND_BIKE_LED_TIMER);

	}
}

void gprs_and_sms_find_bike_speaker_led_flash(void)
{
	if(g_lock_cntx.speaker_led_flash_counts>0)
	{
		iot_led_speak_warning_callback();
		StartTimer(FIND_BIKE_SPEAKER_LED_TIMER,60*1000,gprs_and_sms_find_bike_speaker_led_flash);
		g_lock_cntx.speaker_led_flash_counts--;
	}
	else
	{
		StopTimer(FIND_BIKE_SPEAKER_LED_TIMER);
	}
}

