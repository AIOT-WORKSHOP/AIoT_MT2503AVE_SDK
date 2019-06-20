#if defined(__IOT_LOCK__)
#include "iotlock.h"
#include "lock_data.h"
#include "lock_drv.h"
#include "lock_gps.h"
#include "lock_utils.h"
#include "lock_net.h"
#include "dcl_adc.h"
#include "kal_trace.h"
#include "nvram_common_defs.h"
#include "mmi_frm_nvram_gprot.h"
#include "common_nvram_editor_data_item.h"
#include "motion_sensor_custom.h"
#include "bmt_utility.h"
#include "linked_list.h"

static kal_uint32 current_vbat =0;
static kal_int16 current_vbat_temp =0;
static kal_uint8 current_percentage = 0;
extern kal_bool g_need_open_gps;
extern void LockTaskInit();
extern void bmt_get_avg_adc_channel_voltage(DCL_ADC_CHANNEL_TYPE_ENUM ch, kal_uint32 *voltage, kal_uint32 time);
extern kal_char *release_verno(void);
extern kal_char* build_date_time(void); 
kal_uint8 verno_date_time[16] = {0};
LINKEDLIST g_report_list = {NULL, NULL};
extern gprs_lock_cntx g_lock_cntx;
kal_bool g_reboot_use_pre_gps_data = KAL_FALSE;
void verno_date_time_init(void)
{
	if(verno_date_time[0] == 0)
	{
		U8* verno = release_verno();
		//U8* date_time = build_date_time();
		//memcpy(verno_date_time,verno + 9,7);
		//strncat(verno_date_time,date_time+2,6);
		memcpy(verno_date_time,verno + 9,9);
	}
}
#if defined(__IOT_BLE_BKSS_SUPPORT__)
extern void BkssSaveLocktime(applib_time_struct curr_time);
#endif

void iot_init_backup_nv(void)
{
	kal_uint8 backup[NVRAM_EF_IOT_BACKUP_SIZE] = {0};
	memset(backup, 0, NVRAM_EF_IOT_BACKUP_SIZE);
	ReadRecordIot(NVRAM_EF_IOT_BACKUP_LID, 1, backup, NVRAM_EF_IOT_BACKUP_SIZE);
	if(backup[0] == 0xFF)
	{
		backup[0] = 0;
	}

	if(backup[2] == 0xFF)
	{
		backup[2] = 1;
	}
	/*backup[3]~backup[93] has been used*/
	
	WriteRecordIot(NVRAM_EF_IOT_BACKUP_LID, 1, backup, NVRAM_EF_IOT_BACKUP_SIZE);
}
kal_uint8 iot_get_bkup_nv_first_byte(void)
{
	kal_uint8 backup[NVRAM_EF_IOT_BACKUP_SIZE] = {0};
	memset(backup, 0, NVRAM_EF_IOT_BACKUP_SIZE);
	ReadRecordIot(NVRAM_EF_IOT_BACKUP_LID, 1, backup, NVRAM_EF_IOT_BACKUP_SIZE);
	if(backup[0] == 0xFF)
	{
		backup[0] = 0;
		WriteRecordIot(NVRAM_EF_IOT_BACKUP_LID, 1, backup, NVRAM_EF_IOT_BACKUP_SIZE);
		
	}
	return backup[0];
}

kal_uint8 iot_get_bkup_nv_second_byte(void)
{
	kal_uint8 backup[NVRAM_EF_IOT_BACKUP_SIZE] = {0};
	memset(backup, 0, NVRAM_EF_IOT_BACKUP_SIZE);
	ReadRecordIot(NVRAM_EF_IOT_BACKUP_LID, 1, backup, NVRAM_EF_IOT_BACKUP_SIZE);
	if(backup[1] == 0xFF)
	{
		backup[1] = 0;
		WriteRecordIot(NVRAM_EF_IOT_BACKUP_LID, 1, backup, NVRAM_EF_IOT_BACKUP_SIZE);
		
	}
	return backup[1];
}


kal_uint8 iot_get_bkup_nv_third_byte(void)
{
	kal_uint8 backup[NVRAM_EF_IOT_BACKUP_SIZE] = {0};
	memset(backup, 0, NVRAM_EF_IOT_BACKUP_SIZE);
	ReadRecordIot(NVRAM_EF_IOT_BACKUP_LID, 1, backup, NVRAM_EF_IOT_BACKUP_SIZE);
	return backup[2];
}


void iot_get_bkup_nv_gps_info(GPS_INFO *info)
{
	kal_uint8 backup[NVRAM_EF_IOT_BACKUP_SIZE] = {0};
	kal_uint8 buf[sizeof(GPS_INFO)] = {0};
	kal_uint8 i = 0;
	memset(backup, 0, NVRAM_EF_IOT_BACKUP_SIZE);
	memset(info, 0, sizeof(GPS_INFO));
	ReadRecordIot(NVRAM_EF_IOT_BACKUP_LID, 1, backup, NVRAM_EF_IOT_BACKUP_SIZE);
	memcpy(info, backup+3, sizeof(GPS_INFO));
	memcpy(buf, backup+3, sizeof(GPS_INFO));
	kal_prompt_trace(MOD_MMI, "bkup_nv_gps_info:  %s line:%d latitude = %d longitude = %d hight = %d", __FUNCTION__, __LINE__
	,info->latitude,info->longitude,info->hight);
	for(i=0;i<sizeof(GPS_INFO);i++)
	{
		if(buf[i] != 0xff)
			return;
		else
			continue;
	}
	memset(info, 0, sizeof(GPS_INFO));
	memcpy(backup+3, info, sizeof(GPS_INFO));
	WriteRecordIot(NVRAM_EF_IOT_BACKUP_LID, 1, backup, NVRAM_EF_IOT_BACKUP_SIZE);
}


void iot_set_bkup_nv_first_byte(kal_uint8 type)
{
	kal_uint8 backup[NVRAM_EF_IOT_BACKUP_SIZE] = {0};
	memset(backup, 0, NVRAM_EF_IOT_BACKUP_SIZE);
	ReadRecordIot(NVRAM_EF_IOT_BACKUP_LID, 1, backup, NVRAM_EF_IOT_BACKUP_SIZE);
	backup[0] = type;
	WriteRecordIot(NVRAM_EF_IOT_BACKUP_LID, 1, backup, NVRAM_EF_IOT_BACKUP_SIZE);
}

void iot_set_bkup_nv_second_byte(kal_uint8 type)
{
	kal_uint8 backup[NVRAM_EF_IOT_BACKUP_SIZE] = {0};
	memset(backup, 0, NVRAM_EF_IOT_BACKUP_SIZE);
	ReadRecordIot(NVRAM_EF_IOT_BACKUP_LID, 1, backup, NVRAM_EF_IOT_BACKUP_SIZE);
	backup[1] = type;
	WriteRecordIot(NVRAM_EF_IOT_BACKUP_LID, 1, backup, NVRAM_EF_IOT_BACKUP_SIZE);
}

void iot_set_bkup_nv_third_byte(kal_uint8 type)
{
	kal_uint8 backup[NVRAM_EF_IOT_BACKUP_SIZE] = {0};
	memset(backup, 0, NVRAM_EF_IOT_BACKUP_SIZE);
	ReadRecordIot(NVRAM_EF_IOT_BACKUP_LID, 1, backup, NVRAM_EF_IOT_BACKUP_SIZE);
	backup[2] = type;
	WriteRecordIot(NVRAM_EF_IOT_BACKUP_LID, 1, backup, NVRAM_EF_IOT_BACKUP_SIZE);
}


void iot_set_bkup_nv_gps_info(GPS_INFO *info)
{
	kal_uint8 backup[NVRAM_EF_IOT_BACKUP_SIZE] = {0};
	memset(backup, 0, NVRAM_EF_IOT_BACKUP_SIZE);
	ReadRecordIot(NVRAM_EF_IOT_BACKUP_LID, 1, backup, NVRAM_EF_IOT_BACKUP_SIZE);
	kal_prompt_trace(MOD_MMI, "bkup_nv_gps_info:  %s line:%d latitude = %d longitude = %d hight = %d", __FUNCTION__, __LINE__
	,info->latitude,info->longitude,info->hight);
	memcpy(backup+3, info, sizeof(GPS_INFO));
	WriteRecordIot(NVRAM_EF_IOT_BACKUP_LID, 1, backup, NVRAM_EF_IOT_BACKUP_SIZE);
}
kal_bool iot_get_bkup_nv_exception_reboot(void)
{
	static kal_bool is_init = KAL_FALSE;
	static kal_bool ex_reboot = KAL_FALSE;

	if (!is_init)
	{
		kal_uint8 backup[NVRAM_EF_IOT_BACKUP_SIZE] = {0};
		kal_uint8 start = sizeof(GPS_INFO)+3;
		memset(backup, 0, NVRAM_EF_IOT_BACKUP_SIZE);
		ReadRecordIot(NVRAM_EF_IOT_BACKUP_LID, 1, backup, NVRAM_EF_IOT_BACKUP_SIZE);
		if(backup[start] == 1)
		{
			ex_reboot = KAL_TRUE;
			backup[start] = 0;
			WriteRecordIot(NVRAM_EF_IOT_BACKUP_LID, 1, backup, NVRAM_EF_IOT_BACKUP_SIZE);
		}
	}
	return ex_reboot;
}
void iot_set_bkup_nv_exception_reboot(kal_uint8 *ex_reboot)
{
	kal_uint8 backup[NVRAM_EF_IOT_BACKUP_SIZE] = {0};
	kal_uint8 start = sizeof(GPS_INFO)+3;
	memset(backup, 0, NVRAM_EF_IOT_BACKUP_SIZE);
	ReadRecordIot(NVRAM_EF_IOT_BACKUP_LID, 1, backup, NVRAM_EF_IOT_BACKUP_SIZE);
	backup[start] = *ex_reboot;
	WriteRecordIot(NVRAM_EF_IOT_BACKUP_LID, 1, backup, NVRAM_EF_IOT_BACKUP_SIZE);
}

void mmi_iot_init(void)
{
	init_drv();
	LockTaskInit();
	verno_date_time_init();
	iot_init_backup_nv();
	g_reboot_use_pre_gps_data = KAL_TRUE;

	nwow_gsm_state_kpled_init();
	StartTimer(LOCK_HEART_BEAT_TIMER, 10*1000, ecu_login_test);

	


	
	//spronser_led_ctrl(1,200,200);
	//spronser_led_ctrl(2,500,200);
	//open_gps_and_get_loc(0,MOVE_LOC_REPORT);
#if 1
	//g_need_open_gps = KAL_TRUE;
	//StartTimer(LOCK_GPS_ON_TIMER, 10 * 1000, get_loc);
	get_loc();
	//StartTimer(LOCK_GPS_UPDATE_TIMER, 10*1000, report_loc_timer);
#endif
}
extern void bkss_update_adv_data(void);

void iot_set_battery_percentage(kal_uint32 vbat)
{
	if(vbat > 4100)
	{
		current_percentage = 100;
	}
	else if (vbat >4030)
	{
		current_percentage = 90 + (vbat - 4030)/7;
	}
	else if(vbat > 3920)
	{
		current_percentage = 80 + (vbat - 3920)/11;
	}
	else if(vbat > 3810)
	{
		current_percentage = 70 + (vbat - 3810)/11;
	}
	else if(vbat > 3710)
	{
		current_percentage = 60 + (vbat - 3710)/10;
	}
	else if(vbat > 3650)
	{
		current_percentage = 50 + (vbat - 3650)/6;
	}
	else if(vbat > 3610)
	{
		current_percentage = 40 + (vbat - 3610)/4;
	}
	else if(vbat > 3580)
	{
		current_percentage = 30 + (vbat - 3580)/3;
	}
	else if(vbat > 3540)
	{
		current_percentage = 20 + (vbat - 3540)/4;
	}
	else if(vbat > 3450)
	{
		current_percentage = 10 + (vbat - 3450)/9;
	}
	else if(vbat > 2750)
	{
		current_percentage = 0 + (vbat - 2750)/70;
	}
	else
	{
		current_percentage = 0;
	}
}

kal_uint8 iot_get_battery_percentage(void)
{
	return current_percentage;
}

kal_uint32 iot_get_battery_voltage(void)
{
	kal_uint32 vbat = 0;
	bmt_get_avg_adc_channel_voltage(DCL_VBAT_ADC_CHANNEL, &vbat, 20);
	vbat = vbat/1000;
	return vbat;
}

void iot_get_battery(void)
{
	kal_uint32 vbat = 0;
	bmt_get_avg_adc_channel_voltage(DCL_VBAT_ADC_CHANNEL, &vbat, 20);
	current_vbat = vbat/1000;
	iot_set_battery_percentage(current_vbat);
}

kal_int16 iot_get_battery_temperature(void)
{
	kal_uint32 vbat_temp = 0;
	kal_int16 vbat_temp_val = 0;
	bmt_get_avg_adc_channel_voltage(DCL_VBATTMP_ADC_CHANNEL, &vbat_temp, 20);
	vbat_temp_val = bmt_change_VBatTmp_To_BatTmp(vbat_temp)/1000;
	return vbat_temp_val;
}

kal_int16 iotlock_get_battery_temperature(void)
{
	kal_uint32 vbat_temp = 0;
	kal_int16  vbat_temp_val = 0;
	bmt_get_avg_adc_channel_voltage(DCL_VBATTMP_ADC_CHANNEL, &vbat_temp, 20);
	vbat_temp_val = bmt_change_VBatTmp_To_BatTmp(vbat_temp)/10;
	return vbat_temp_val;
}


kal_int16 iot_get_battery_vcharger(void)
{
	kal_uint32 vbus_v = 0;
	bmt_get_avg_adc_channel_voltage(DCL_VCHARGER_ADC_CHANNEL, &vbus_v, 20);
	vbus_v /= 1000;
	return vbus_v;
}

kal_int16 iot_get_battery_isense(void)		// get battery charge current
{
	kal_uint32 vbat = 0;
	kal_uint32 vbat_isense = 0;
	kal_int16 isense = 0;
	bmt_get_avg_adc_channel_voltage(DCL_VBAT_ADC_CHANNEL, &vbat, 20);		// first get VBAT
	bmt_get_avg_adc_channel_voltage(DCL_VISENSE_ADC_CHANNEL, &vbat_isense, 20);	// then get VBAT_ISENSE
	//isense = bmt_change_Voltage_To_ISense(vbat_isense - vbat)*4/1000;	// for 50mohm resistor
	isense = (vbat_isense - vbat)/0.02/1000;	// for 20mohm resistor
	//kal_prompt_trace(MOD_MMI, "%s--BAT Volt IS: %d mV", __func__, vbat);
	//kal_prompt_trace(MOD_MMI, "%s--BAT Visens IS: %d mV", __func__, vbat_isense);
	kal_prompt_trace(MOD_MMI, "%s--BAT ISENSE IS: %d mA", __func__, isense);
	return isense;
}

//锁定时回调
void lock_bike_callback()
{
	nvram_ef_iot_lock_struct info;
	applib_time_struct curr_time;
	nvram_ef_order_info *order_info_ptr = NULL;
	if(g_normal_open_lock_state){
#ifdef __IOT_LOCK_BEEPSPK__
		open_beep_ms(300, 1);
#else
		iot_play_tone_with_filepath(IOT_TONE_LOCK);
#endif
		g_normal_open_lock_state = KAL_FALSE;
	}
	g_need_open_gps = KAL_TRUE;
	acc_sensor_pwr_down();		//stop g-sensor
	open_gps_and_get_loc(0, LOCK_LOC_REPORT);
	open_timer_gps_and_get_loc();
	StopTimer(LOCK_UPLOAD_ECG_BEGIN_TIMER);
	ReadRecordIot(NVRAM_EF_IOT_LOCK_LID, 1, &info, NVRAM_EF_IOT_LOCK_SIZE);

	//记录下关锁时间
	applib_dt_get_rtc_time(&curr_time);
#if defined(__IOT_BLE_BKSS_SUPPORT__)
	BkssSaveLocktime(curr_time);
#endif

	if(info.mode == IOT_LOCK_MODE_TRANS) 
	{
		lock_debug_print(MOD_MMI, "iotlock: %s switch to IOT_LOCK_MODE_NORMAL mode=%d", __FUNCTION__, info.mode);
		switch_normal_mode();
	} 
	else 
	{
		order_info *info = get_one_order_info();
		info->unlocks = get_unlock_count();
		info->timestamp = iotlock_srv_brw_get_current_utc_time();
		info->rssi = get_gsm_strength();
		info->serial_num = get_serial_number();
		info->msg_id = TERMINAL_LOC_COM_ID;
		info->ans_serial = 0;
		info->bj = 0;
		if(g_lock_cntx.current_unlock_mode == BT_UNLOCK){
			info->state = BT_LOCK_LOC_REPORT<<1;
		} else if(g_lock_cntx.current_unlock_mode == SMS_UNLOCK){
			info->state = SMS_LOCK_LOC_REPORT<<1;
		} else {
			info->state = LOCK_LOC_REPORT<<1;
		}

		if(read_lock_state() == UNLOCKED) {
			info->state |= 1;
		}
		
		get_order_num_from_nvram(info->order_num);
		get_open_lock_time_from_nvram(&info->unlock_timestamp);

		add_one_node(&g_report_list, info);
		StartTimerEx(LOCK_DELAY_REPORT_TIMER, 1000, delay_report_loc, info);
		//spronser_led_ctrl(2,200,10);
	}
#ifdef __NSK_ECG__
		ECG_PWR_OFF();
#endif
	//clear_order_num_from_nvram();
	//delay 2s to open g-sensor
	StartTimer(LOCK_OPEN_G_SENEOR_TIMER, OPEN_G_SENSER_DELAY*1000, motion_sensor_pwr_on_off_switch);
}
static void iot_play_audio_info_init(srv_prof_play_audio_struct* play_info, srv_prof_tone_enum tone_type)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    play_info->audio_id = 0;

    play_info->play_style = SRV_PROF_RING_TYPE_ONCE;

    play_info->volume = 7;

    play_info->tone_type = tone_type;

    play_info->play_from_full_struct = MMI_FALSE;

    play_info->aud_path = MDI_DEVICE_SPEAKER_BOTH;
}
mdi_result iot_play_tone_with_filepath_ext(iot_tone_enum tone_type,srv_prof_ring_type_enum play_style,srv_prof_play_tone_callback callback)
{
	/*----------------------------------------------------------------*/
	/* Local Variables                                                */
	/*----------------------------------------------------------------*/
	mdi_result play_result = MDI_AUDIO_FAIL;
	WCHAR tone_path[520] = {0};
	FILE * fp;
	static FS_HANDLE file_handle;
	U16 audio_id;
   	S32 fs_ret;
	U32 file_size=0;
	S32 file_result;
	/*----------------------------------------------------------------*/
	/* Code Body                                                      */
	/*----------------------------------------------------------------*/

	if (!srv_bootup_is_launched() || srv_shutdown_is_running())
	{
		return MDI_AUDIO_FAIL;
	}
	else 
	{

		switch(tone_type)
		{
			case IOT_TONE_UNLOCK:
			{
				audio_id = AUD_ID_PROF_TONE_CHECK_REPORT;
				mmi_wcscpy(tone_path, (WCHAR*)L"D:\\open.mp3");
				lock_debug_print(MOD_MMI, "iotlock:  enter %s() %d IOT_TONE_UNLOCK ", __FUNCTION__,__LINE__);	
				break;
			}

			case IOT_TONE_LOCK:
			{
				audio_id = AUD_ID_PROF_TONE_FINISH;
				mmi_wcscpy(tone_path, (WCHAR*)L"D:\\close.mp3");
				lock_debug_print(MOD_MMI, "iotlock:  enter %s() %d IOT_TONE_LOCK ", __FUNCTION__,__LINE__);	
				break;
			}
			case IOT_TONE_WARN:
			{
				audio_id = AUD_ID_PROF_TONE_WARN;//temp
				mmi_wcscpy(tone_path, (WCHAR*)L"D:\\warn.mp3");
				lock_debug_print(MOD_MMI, "iotlock:  enter %s() %d IOT_TONE_WARN ", __FUNCTION__,__LINE__);	
				break;
			}
			default:
			{
				audio_id = AUD_ID_PROF_TONE_YOUR_CODE;
				mmi_wcscpy(tone_path, (WCHAR*)L"D:\\open.mp3");
				break;
			}

		}



		lock_debug_print(MOD_ENG, "%s() %d audio_id = %d", __FUNCTION__,__LINE__,audio_id);
		play_result = srv_prof_play_tone_with_filepath(
		                    SRV_PROF_TONE_ALARM, 
		                    (WCHAR*)tone_path, 
		                    play_style, 
		                    callback);

		lock_debug_print(MOD_MMI, "iotlock:  %s() %d play_result = %d ", __FUNCTION__,__LINE__,play_result);	
		if (play_result == SRV_PROF_RET_FAIL)
		{
			 play_result = srv_prof_play_tone_with_id(SRV_PROF_TONE_ALARM, 
			                        audio_id, 
			                        play_style, 
			                        callback);			
		}


	}
	return play_result;

}

mdi_result iot_play_tone_with_filepath(iot_tone_enum tone_type)
{
	return iot_play_tone_with_filepath_ext(tone_type,SRV_PROF_RING_TYPE_ONCE,NULL);
}

srv_prof_play_tone_callback iot_open_lock_play_tone_callback(void)
{
	open_lock();
}

#endif
