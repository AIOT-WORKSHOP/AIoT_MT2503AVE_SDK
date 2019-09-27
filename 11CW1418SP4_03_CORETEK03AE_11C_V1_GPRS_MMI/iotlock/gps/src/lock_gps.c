#include <stdlib.h>
#include "mmi_features.h"
#include "MMIDataType.h"
#include "kal_release.h"
#include "kal_trace.h"
#include "drv_comm.h"
#include "MMITimer_Int.h"
#include "CharBatSrvGprot.h"
#include "mmi_frm_queue_gprot.h"
#include "syscomp_config.h"
#include "nvram_common_defs.h"
#include "common_nvram_editor_data_item.h"
#include "Mmi_rp_srv_iot_lock_def.h"
#include "NwInfoSrv.h"
#include "soc_api.h"
#include "mdi_gps.h"
#include "lock_gps.h"
#include "lock_data.h"
#include "lock_net.h"
#include "lock_drv.h"
#include "lock_utils.h"
#include "iotlock.h"

static kal_uint32 gps_time = 0;
static kal_uint32 gps_duration_time = 0;
static kal_uint8 gps_count = 0;
static kal_uint8 gps_state = 0;

GPS_STATE g_gps_state = GPS_OFF;
COMM_LOC g_comm_loc;
ATTACH_LOC g_attach_loc;

kal_uint32 gps_preon_time = 60; //60s
kal_bool g_need_open_gps = KAL_TRUE;
Word g_serial_number = 0;
kal_bool g_report_vibrate = KAL_TRUE;

extern kal_char g_device_id[13];
extern gprs_lock_cntx g_lock_cntx;

extern kal_bool gps_atatest_flag;
extern kal_int16 iotlock_get_battery_temperature(void);
static kal_uint8 gps_satelitte_arry[20] ={0};
applib_time_struct g_gps_locate_time = {0};

static kal_uint8  gps_satelitte_strength_max=0;
extern kal_bool g_reboot_use_pre_gps_data;
#ifndef MIN
   #define MIN(x, y) ((((x)) <= ((y)))? x: y)
#endif // MIN
#define __NEW_AT_HL300_SUPPORT__

extern void bmt_get_avg_adc_channel_voltage(DCL_ADC_CHANNEL_TYPE_ENUM ch, kal_uint32 *voltage, kal_uint32 time);

#if defined(__MRE_PACKAGE_NONE__)
static int htoi(char ch)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    if ((ch >= '0') && (ch <= '9'))
        return ch - '0';

    if ((ch >= 'a') && (ch <= 'f'))
        return ch - 'a' + 10;

    if ((ch >= 'A') && (ch <= 'F'))
        return ch - 'A' + 10;

    return -1;
}
static int dtoi(char ch)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    if ((ch >= '0') && (ch <= '9'))
        return ch - '0';

    return -1;
}
static int strtoi(char *s)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    int v, t, i, hex = 0;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    for (i = 0; s[i] != 0; i++)
        if (((s[i] >= 'a') && (s[i] <= 'f')) || ((s[i] >= 'A') && (s[i] <= 'F'))) {
            hex = 1;
            break;
        }

        for (i = 0, v = 0; s[i] != 0; i++) {
            if (hex) {
                if ((t = htoi(s[i])) == -1)
                    return -1;
                v = (v << 4) + t;
            }
            else {
                if ((t = dtoi(s[i])) == -1)
                    return -1;
                v = v * 10 + t;
            }
        }

        return v;
}
#endif

void gps_open()
{
	kal_prompt_trace(MOD_MMI, "AWS gps_open iotlock");
	//if(g_gps_state == GPS_OFF && (g_need_open_gps || read_lock_state() == UNLOCKED)) {
		g_gps_state = GPS_ON;
		kal_prompt_trace(MOD_MMI, "iotlock: %s gps_open begin", __FUNCTION__);
		gps_time = drv_get_current_time();
		gps_state = 1; //�� ��δ��λ
		mdi_gps_uart_open((U16)mdi_get_gps_port(), MDI_GPS_UART_MODE_RAW_DATA, gps_callback);
		mdi_gps_uart_open((U16)mdi_get_gps_port(), MDI_GPS_UART_MODE_LOCATION, gps_callback);	
		StartTimer(LOCK_GPS_CTL_TIMER, gps_preon_time*1000, start_lbs_and_off_gps);
	//}

	//WDQ TODO
	//StartTimer(LOCK_GPS_STOP_TIMER, gps_preon_time*1000,  gps_sleep);
}

void ata_gps_open(void)
{
	if(!IsMyTimerExist(LOCK_ATA_AT_TIMER3))
	{
		mdi_gps_uart_open((U16)mdi_get_gps_port(), MDI_GPS_UART_MODE_RAW_DATA, gps_callback);
		mdi_gps_uart_open((U16)mdi_get_gps_port(), MDI_GPS_UART_MODE_LOCATION, gps_callback);
	}
	StartTimer(LOCK_ATA_AT_TIMER3, 500*1000,  gps_sleep);
}

void ata_gps_sleep(void)
{
	mdi_gps_uart_close((U16)mdi_get_gps_port(), MDI_GPS_UART_MODE_RAW_DATA, gps_callback);
	mdi_gps_uart_close((U16)mdi_get_gps_port(), MDI_GPS_UART_MODE_LOCATION, gps_callback);
}

void iot_ata_gps_open(void)
{
	ata_gps_open();
}

void iot_ata_gps_sleep(void)
{
	StopTimer(LOCK_ATA_AT_TIMER3);
	ata_gps_sleep();
}

//GPS����
kal_bool gps_open_test(void)
{
	 MDI_RESULT ret ;
	 ret =gps_open_ext();
	 
	 if(ret<0) 
	 {
		 return MMI_FALSE;
	 }
	 else
	 {	 	
	 	return MMI_TRUE;
	 }
}

void gps_sleep()
{
	kal_prompt_trace(MOD_MMI, "AWS gps_sleep iotlock");

	memset(gps_satelitte_arry, 0 , 20);

	if(g_gps_state == GPS_ON) {
		g_gps_state = GPS_OFF;
		gps_state = 0;
		g_need_open_gps = KAL_FALSE;
		mdi_gps_uart_close((U16)mdi_get_gps_port(), MDI_GPS_UART_MODE_RAW_DATA, gps_callback);
		mdi_gps_uart_close((U16)mdi_get_gps_port(), MDI_GPS_UART_MODE_LOCATION, gps_callback);
	}
 }

void start_lbs_and_off_gps()
{
	//lock_socket_create(TYPE_LBS_SOC);
}

void gps_callback(mdi_gps_parser_info_enum type, void *buffer, U32 length)
{
	switch(type){
	case MDI_GPS_PARSER_RAW_DATA:
		{
			//�õ�GPS��λ�ĵ���λ����Ϣ
			//kal_prompt_trace(MOD_MMI,"iotlock: %s GPS RAW_DATA: %s", __FUNCTION__, buffer);
			//��������λ����Ϣ
			get_loc_msg_from_gps(buffer);
		}
		break;
	default:
		kal_prompt_trace(MOD_MMI,"iotlock: %s type: %d", __FUNCTION__, type);
		break;
	}
	
}
void gps_callback_ext(mdi_gps_parser_info_enum type, void *buffer, U32 length)
{

	switch(type){
	case MDI_GPS_PARSER_RAW_DATA:
		{
			//char buffer1[128+1];
			//�õ�GPS��λ�ĵ���λ����Ϣ
			//kal_prompt_trace(MOD_MMI,"iotlock: %s raw data: %s", __FUNCTION__, buffer);
			//��������λ����Ϣ
			get_loc_msg_from_gps(buffer);
		}
		break;
	default:break;
	}
}

kal_uint8 get_next(char *buffer, char*out, kal_uint8 index) {
	kal_uint8 i = 0;
	kal_uint8 pre = 0;
	kal_uint8 cur = 0;
	kal_uint8 count = 0;
	kal_int8 ret = -1;
	
	for(; i < strlen(buffer); i++){
		if(buffer[i] == ',' || (index == 1 && buffer[i] == '.')) {
			pre = cur;
			cur = i;
			count++;
			if(count == index) {
				if((cur-pre) > 1) {
					if(index == 1) {
						strncpy(out, buffer + pre, cur-pre);
					} else {
						strncpy(out, buffer + pre + 1, cur-pre-1);
					}
					ret = 1;
				} else {
					ret = 0;
				}
				break;
			}
		}
	}

	return ret;
}

kal_uint8 get_next_ext(char *buffer, char*out, kal_uint8 index) {
	kal_uint8 i = 0;
	kal_uint8 pre = 0;
	kal_uint8 cur = 0;
	kal_uint8 count = 0;
	kal_int8 ret = -1;

	for(; i < strlen(buffer); i++){
		if(buffer[i] == '*' ||buffer[i] == ',' || (index == 1 && buffer[i] == '.')) {
			pre = cur;
			cur = i;
			count++;
			if(count == index) {
				if((cur-pre) > 1) {
					if(index == 1) {
						strncpy(out, buffer + pre, cur-pre);
					} else {
						strncpy(out, buffer + pre + 1, cur-pre-1);
					}
					ret = 1;
				} else {
					ret = 0;
				}
				break;
			}
		}
	}

	return ret;
}

//$GNGGA,032730.000,3112.6362,N,12137.4683,E,1,5,2.48,54.7,M,8.4,M,,*49
void get_loc_msg_from_gps(char* buffer) {
	if(strncmp(buffer, "$GNGGA", 6) == 0) {
		char *ptr = buffer + 7;
		char result[16] = {0};
		kal_uint8 state = 0;

		if(get_next(ptr, result, 6) == 1) {
			state = result[0]-'0';
		}

		memset(result, 0 , 16);
		get_next(ptr, result, 7);
		gps_count =(Byte)strtoi(result);
		g_attach_loc.attach.gnss[0] = 0x31;
		g_attach_loc.attach.gnss[1] = 0x01;
		g_attach_loc.attach.gnss[2] = gps_count;
		
	    //ata
		//kal_prompt_trace(MOD_MMI,"%s iotlock: gps_counts: %d", __FUNCTION__, gps_count);
		if(strncmp(buffer, "$GNGGA", 6) == 0) {
		if(gps_atatest_flag == KAL_TRUE)
		{
				sprintf(buffer, "\r\n+EGGPS:%d\r\n", gps_count);
				rmmi_write_to_uart((kal_uint8*)buffer, strlen(buffer), KAL_TRUE);
				//kal_prompt_trace(MOD_MMI, "gps_counts=%d", gps_count);
				gps_atatest_flag = KAL_FALSE;

		}
		}
		//end

		if(state == 1 || state == 2) {
			memset(result, 0 , 16);
			if(get_next(ptr, result, 9) == 1) {
				g_comm_loc.hight = (Word)(strtof(result, NULL) + 0.5);
			}
		}
	} 
	else if(strncmp(buffer, "$GNRMC", 6) == 0){
		char *ptr = buffer + 7;
		char result[16] = {0};

		kal_uint8 state = 'V';

		if(get_next(ptr, result, 2) == 1) {
			state = result[0];
		}
		
		
		if(state == 'A') {
			gps_duration_time = drv_get_duration_ms(gps_time);
			applib_dt_get_rtc_time(&g_gps_locate_time);
			gps_state = 2; //�� �Ѷ�λ
			StopTimer(LOCK_GPS_CTL_TIMER);

			g_comm_loc.state |= 0x2;
			memset(result, 0 , 16);
			get_next(ptr, result, 3);
			g_comm_loc.latitude = convert(result);

			memset(result, 0 , 16);
			get_next(ptr, result, 4);
			if(result[0] == 'N'){
				g_comm_loc.state &= (~0x4);
			} else if(result[0] == 'S') {
				g_comm_loc.state |= 0x4;
			}

			memset(result, 0 , 16);
			get_next(ptr, result, 5);
			g_comm_loc.longitude= convert(result);

			memset(result, 0 , 16);
			get_next(ptr, result, 6);
			if(result[0] == 'E'){
				g_comm_loc.state &= (~0x8);
			} else if(result[0] == 'W') {
				g_comm_loc.state |= 0x8;
			}

			memset(result, 0 , 16);
			get_next(ptr, result, 8);
			g_comm_loc.direction = (Word)(strtof(result, NULL) + 0.5);

			//kal_prompt_trace(MOD_MMI, "iot_gps: lat=%.6f, long=%.6f", (float)g_comm_loc.latitude / 1000000, (float)g_comm_loc.longitude/1000000);
		} else {
			g_comm_loc.state &= (~0x2);
			gps_state = 1;
		}
	} 
	else if(strncmp(buffer, "$GNVTG", 6) == 0){
		char *ptr = buffer + 7;
		char result[16] = {0};

		get_next(ptr, result, 7);
		g_comm_loc.speed = (Word)((strtof(result, NULL) * 10) + 0.5);
	}
	//panxiang 20170809 add for get gps_satelitte count and use strength >= 20
	//$GPGSV,3,1,10,24,82,023,40,05,62,285,32,01,62,123,00,17,59,229,28*70
	else if (strncmp(buffer, "$GPGSV", 6) == 0){
		char *ptr = buffer + 7;
		char result[16] = {0};
		char sendbuffer[128+1];

		kal_uint8 i,j,bufferlength,sum;
              kal_uint8 gps_strength_count = 0;

		kal_uint8 gps_satelitte =0;
		kal_uint8 gps_strength =0;
              kal_bool isInArray = KAL_FALSE;
		kal_uint8 gps_strength_scale =40;

#ifdef __NEW_AT_HL300_SUPPORT__
		gps_strength_scale = 1;
#endif
		gps_strength_count = strlen(gps_satelitte_arry);

		//sprintf(sendbuffer, "get_loc_msg_from_gps  000  GPSSTRENGTH=%s -- %d", buffer,gps_strength_count);
		//rmmi_write_to_uart((kal_uint8*)sendbuffer, strlen(sendbuffer), KAL_TRUE);

		bufferlength = strlen(buffer);
		for(i=0;i<4;i++)
		{
			memset(result, 0 , 16);
			get_next_ext(ptr, result, 4+4*i);
			gps_satelitte =(Byte)strtoi(result);

			memset(result, 0 , 16);
			get_next_ext(ptr, result, 7+4*i);
			gps_strength =(Byte)strtoi(result);

#ifdef __NEW_AT_HL300_SUPPORT__
			if(gps_strength > gps_satelitte_strength_max)
			{
				gps_satelitte_strength_max = gps_strength;
			}
#endif
			//sprintf(sendbuffer, "get_loc_msg_from_gps  111  GPSSTRENGTH=%d %d", gps_satelitte,gps_strength);
			//rmmi_write_to_uart((kal_uint8*)sendbuffer, strlen(sendbuffer), KAL_TRUE);

			if(gps_strength >= gps_strength_scale)
			{
				for(j = 0; j < gps_strength_count; j ++)
				{
					//sprintf(sendbuffer, "get_loc_msg_from_gps  222  gps_satelitte = %d   gps_satelitte_arry[j] = %d", gps_satelitte,gps_satelitte_arry[j]);
					//rmmi_write_to_uart((kal_uint8*)sendbuffer, strlen(sendbuffer), KAL_TRUE);
					isInArray = KAL_FALSE;
					if(gps_satelitte_arry[j] == gps_satelitte)
					{
						isInArray	= KAL_TRUE;
						break;
					}
				}

				if(isInArray	 == KAL_FALSE )
				{
					/*
					sprintf(sendbuffer, "get_loc_msg_from_gps  333  GPSSTRENGTH=%d %d", gps_strength_count,gps_satelitte);
					rmmi_write_to_uart((kal_uint8*)sendbuffer, strlen(sendbuffer), KAL_TRUE);
					*/
					gps_satelitte_arry[gps_strength_count] = gps_satelitte;
					gps_strength_count++;
				}
			}
		}
	}
}

MDI_RESULT gps_open_ext()
{
	MDI_RESULT ret =-1;

	ret=mdi_gps_uart_open((U16)mdi_get_gps_port(), MDI_GPS_UART_MODE_RAW_DATA, gps_callback_ext);
	mdi_gps_uart_open((U16)mdi_get_gps_port(), MDI_GPS_UART_MODE_LOCATION, gps_callback_ext);

	return ret;
}

//panxiang 20170809 add for get gps_satelitte count and use strength >= 20
kal_uint8 get_gps_strength_count()
{
	kal_uint8 sum;
       kal_uint8 gps_strength_count = 0;
	char sendbuffer[128+1];
	gps_strength_count = strlen(gps_satelitte_arry);

	//for(sum=0;sum<gps_strength_count;sum++){
	//	sprintf(sendbuffer, "get_gps_strength_count  GPSSTRENGTH=%d", gps_satelitte_arry[sum]);
	//	rmmi_write_to_uart((kal_uint8*)sendbuffer, strlen(sendbuffer), KAL_TRUE);
	//}
	
	memset(gps_satelitte_arry, 0 , 20);

	return gps_strength_count;
}

kal_uint8 get_gps_strength_max()
{
       kal_uint8 gps_strength_max = gps_satelitte_strength_max;

	gps_satelitte_strength_max = 0;

	return gps_strength_max;
}

kal_uint8 get_gps_count() 
{
	return gps_count;
}

kal_uint8 get_gps_state() 
{
	return gps_state;
}

kal_uint8 get_gps_duration_time() 
{
	kal_uint8 tmp = (gps_duration_time + 500)/1000;
	if(tmp >= 255){
		tmp = 255;
	}
	return tmp;
}

void reset_vibrate_report(){
	g_report_vibrate = KAL_TRUE;
}

void open_gps_and_get_loc(DWord gap, LOC_REPORT_TYPE type){
	kal_bool report = KAL_FALSE;

	kal_prompt_trace(MOD_MMI,"iotlock: %s low_power: %d",__func__, g_lock_cntx.low_power);
	if(g_lock_cntx.low_power == 1) return; //�͹���ģʽ������GPS��λ

	if(type == VIB_LOC_REPORT) {
		report = g_report_vibrate;
		if(g_report_vibrate) {
			g_report_vibrate = KAL_FALSE;
			#ifdef __IOT_LOCK_BEEPSPK__
			open_beep_ms(100, 4);
			#else
			//iot_play_tone_with_filepath(IOT_TONE_WARN);
			#endif
		}
	}

	if(gap == 0) {
		g_need_open_gps = KAL_TRUE;
		get_loc();
		if(type == VIB_LOC_REPORT || type == MOVE_LOC_REPORT) {
			order_info *info = get_one_order_info();
			info->unlocks = get_unlock_count();
			info->timestamp = iotlock_srv_brw_get_current_utc_time();
			info->rssi = get_gsm_strength();
			info->serial_num = get_serial_number();
			info->msg_id = TERMINAL_LOC_COM_ID;
			info->ans_serial = 0;
			info->bj = 0;
			info->state = type<<1;

			if(read_lock_state() == UNLOCKED) {
				info->state |= 1;
				get_open_lock_time_from_nvram(&info->unlock_timestamp);
				get_order_num_from_nvram(info->order_num);
			}

			add_one_node(&g_report_list, info);
			StartTimer(LOCK_LOC_REPORT_TIMER, LOCK_LOC_REPORT_DELAY*1000, loc_report_delay);
		}
	}
	else if(gap < GPS_LOCATION_TIME) {
		get_loc();
		if(type == TIMER_LOC_REPORT) {
			StartTimer(LOCK_GPS_UPDATE_TIMER, gap*1000, report_loc_timer);
		}
	} else {
		StartTimer(LOCK_GPS_ON_TIMER, (gap-GPS_LOCATION_TIME) * 1000, get_loc);
		StartTimer(LOCK_GPS_UPDATE_TIMER, gap*1000, report_loc_timer);
	}

	if(report) {
		StartTimer(LOCK_VIB_REPORT_TIMER, VIBRATE_REPORT_GAP * 1000, reset_vibrate_report);
	}
}

void open_timer_gps_and_get_loc()
{
	open_gps_and_get_loc(g_lock_cntx.gps_update_lock_gap, TIMER_LOC_REPORT);
}

void get_curr_time(BCD *datetime, kal_uint32 utc_sec)
{
	applib_time_struct curr_time;
	kal_uint32 my_sec = utc_sec + 8 *3600;
	
	applib_dt_utc_sec_2_mytime(my_sec, &curr_time, KAL_FALSE);

	datetime[0] = (((curr_time.nYear%100) / 10)<<4) + curr_time.nYear%10;
	datetime[1] = ((curr_time.nMonth/10)<<4) + curr_time.nMonth%10;
	datetime[2] = ((curr_time.nDay/10)<<4) + curr_time.nDay%10;
	datetime[3] = ((curr_time.nHour/10)<<4) + curr_time.nHour%10;
	datetime[4] = ((curr_time.nMin/10)<<4) + curr_time.nMin%10;
	datetime[5] = ((curr_time.nSec/10)<<4) + curr_time.nSec%10;
}

//��ȡС����Ϣ
void spconser_sal_stub_cell_reg_req(void)
{
	SetProtocolEventHandler(spconser_sal_cell_reg_rsp, MSG_ID_L4C_NBR_CELL_INFO_REG_CNF);
	SetProtocolEventHandler(spconser_sal_cell_reg_rsp, MSG_ID_L4C_NBR_CELL_INFO_IND);
	
	mmi_frm_send_ilm(MOD_L4C, MSG_ID_L4C_NBR_CELL_INFO_REG_REQ, NULL, NULL);
}

void copy_nbr_data(Byte count, gas_nbr_cell_info_struct cell_info ) 
{
	kal_uint8  i = 0;

	g_attach_loc.stations = MIN(BASE_STATION_MAX,(count + 1));
	g_attach_loc.mcc = (Word)cell_info.serv_info.gci.mcc;
	g_attach_loc.mnc = (Word)cell_info.serv_info.gci.mnc;
	g_attach_loc.base_station[0].strenth = (Byte)cell_info.nbr_meas_rslt.nbr_cells[cell_info.serv_info.nbr_meas_rslt_index].rxlev;
	g_attach_loc.base_station[0].lac = (Word)cell_info.serv_info.gci.lac;
	g_attach_loc.base_station[0].ci = (DWord)cell_info.serv_info.gci.ci;

	while(i < count)
	{
		g_attach_loc.base_station[i+1].strenth = (Byte)cell_info.nbr_meas_rslt.nbr_cells[cell_info.nbr_cell_info[i].nbr_meas_rslt_index].rxlev;
		g_attach_loc.base_station[i+1].lac = (Word)cell_info.nbr_cell_info[i].gci.lac;
		g_attach_loc.base_station[i+1].ci = (DWord)cell_info.nbr_cell_info[i].gci.ci;
		i++;
	}
	ClearProtocolEventHandler(MSG_ID_L4C_NBR_CELL_INFO_REG_CNF);
	ClearProtocolEventHandler(MSG_ID_L4C_NBR_CELL_INFO_IND);
	mmi_frm_send_ilm(MOD_L4C, MSG_ID_L4C_NBR_CELL_INFO_DEREG_REQ, NULL, NULL);
}

void spconser_sal_cell_reg_rsp(l4c_nbr_cell_info_ind_struct *msg_ptr)
{
	kal_uint8 count = 0;
	gas_nbr_cell_info_struct cell_info = {0};

	if(msg_ptr == NULL)
	{
		kal_prompt_trace(MOD_MMI, "iotlock: %s msg_ptr NULL", __func__);
		return;
	}

	kal_prompt_trace(MOD_MMI, "iotlock: %s valid = %d", __func__, msg_ptr->is_nbr_info_valid);
	if (KAL_TRUE == msg_ptr->is_nbr_info_valid)
	{
		memcpy((void *)&cell_info, (void *)(&(msg_ptr->ps_nbr_cell_info_union.gas_nbr_cell_info)), sizeof(gas_nbr_cell_info_struct));
		count = MIN(BASE_STATION_MAX_COUNT, cell_info.nbr_cell_num);
		copy_nbr_data(count, cell_info);
	}
}

void get_loc()
{
	kal_prompt_trace(MOD_MMI,"AWS GPS Open: %s ", __FUNCTION__);
	gps_open();
	spconser_sal_stub_cell_reg_req();
}

void report_loc_timer()
{
	order_info *info = get_one_order_info();
	info->unlocks = get_unlock_count();
	info->timestamp = iotlock_srv_brw_get_current_utc_time();
	info->rssi = get_gsm_strength();
	info->serial_num = get_serial_number();
	info->msg_id = TERMINAL_LOC_COM_ID;
	info->ans_serial = 0;
	
	if(read_lock_state()==UNLOCKED) {
		get_open_lock_time_from_nvram(&info->unlock_timestamp);
		get_order_num_from_nvram(info->order_num);
		if(g_lock_cntx.current_unlock_mode == NT_UNLOCK){
			info->state = (NT_UNLOCK_TIMER_LOC_REPORT<<1);
		}else if(g_lock_cntx.current_unlock_mode == BT_UNLOCK){
			info->state = (BT_UNLOCK_TIMER_LOC_REPORT<<1);
		}else if(g_lock_cntx.current_unlock_mode == SMS_UNLOCK){
			info->state = (SMS_UNLOCK_TIMER_LOCK_REPORT<<1);
		}
		info->state |= 1;
	}else{
		info->state = (TIMER_LOC_REPORT<<1);
	}

	add_one_node(&g_report_list, info);
	report_loc(KAL_FALSE);

	if(read_lock_state()==LOCKED) {
		open_gps_and_get_loc(g_lock_cntx.gps_update_lock_gap, TIMER_LOC_REPORT);
	} else {
		open_gps_and_get_loc(g_lock_cntx.gps_update_run_gap, TIMER_LOC_REPORT);
	}
}

void loc_report_delay()
{
	report_loc(KAL_FALSE);
}

void lock_warn_report_loc(LOC_WARN_REPORT_TYPE type)
{
	if(get_curr_mode() == IOT_LOCK_MODE_TRANS)
		return;
	if(g_lock_cntx.low_power == 0) {
		order_info *info = get_one_order_info();
		info->unlocks = get_unlock_count();
		info->timestamp = iotlock_srv_brw_get_current_utc_time();
		info->rssi = get_gsm_strength();
		info->serial_num = get_serial_number();
		info->msg_id = TERMINAL_LOC_COM_ID;
		info->ans_serial = 0;

		g_comm_loc.state &= 0xFFFD;
		g_attach_loc.attach.gnss[2] =0;
		get_loc();

		if(type ==LOW_TEMP_LOC_REPORT) {
			info->bj = 0x02;
		}else if(type ==HIGH_TEMP_LOC_REPORT) {
			info->bj =  0x04;
		}else if(type ==LOW_POWER_LOC_REPORT) {
			info->state = (LOW_BATT_REPORT<<1);
			info->bj =  0x06;
		}else if(type ==NORMAL_POWER_LOC_REPORT) {
			info->bj =  0x08;
		}

		if(read_lock_state() == UNLOCKED) {
			info->state |= 1;
		}

		add_one_node(&g_report_list, info);
		StartTimer(LOCK_LOC_REPORT_TIMER, LOCK_LOC_REPORT_DELAY*1000, loc_report_delay);
	}
}

void unlock_time_over_valid_time_gap_report_loc( UNLOCK_TYPE type, Word ans_serial)
{
	order_info *info = get_one_order_info();
	info->unlocks = get_unlock_count();
	info->timestamp = iotlock_srv_brw_get_current_utc_time();
	info->rssi = get_gsm_strength();
	info->serial_num = get_serial_number();
	info->msg_id = PLATFORM_CTRL_ANS_ID;
	info->ans_serial = ans_serial;
	info->bj = 0;

	if(type == NT_UNLOCK){
		info->state = (GPRS_UNLOCK_DELAY_LOC_REPORT<<1);
		kal_prompt_trace(MOD_MMI, "iotlock:  %s ,%d GPRS_UNLOCK_DELAY_LOC_REPORT", __func__, __LINE__);
	}else if(type == SMS_UNLOCK){
		info->state = (SMS_UNLOCK_DELAY_LOC_REPORT<<1);
		kal_prompt_trace(MOD_MMI, "iotlock:  %s ,%d SMS_UNLOCK_DELAY_LOC_REPORT", __func__, __LINE__);
	}

	if(read_lock_state() == UNLOCKED) {
		info->state |= 1;
	}
	
	get_order_num_from_nvram(info->order_num);
	get_open_lock_time_from_nvram(&info->unlock_timestamp);

	add_one_node(&g_report_list, info);
	report_loc(KAL_FALSE);	

}


void has_same_order_num_report_loc( UNLOCK_TYPE type, Word ans_serial)
{
	order_info *info = get_one_order_info();
	info->unlocks = get_unlock_count();
	info->timestamp = iotlock_srv_brw_get_current_utc_time();
	info->rssi = get_gsm_strength();
	info->serial_num = get_serial_number();
	info->msg_id = PLATFORM_CTRL_ANS_ID;
	info->ans_serial = ans_serial;
	info->bj = 0;

	if(type == NT_UNLOCK){
		info->state = (UNLOCK_LOC_REPORT<<1);
	}else if(type == BT_UNLOCK){
		info->state = (BT_UNLOCK_LOC_REPORT<<1);
	}else if(type == SMS_UNLOCK){
		info->state = (SMS_UNLOCK_LOC_REPORT<<1);
	}

	if(read_lock_state() == UNLOCKED) {
		info->state |= 1;
	}
	
	get_order_num_from_nvram(info->order_num);

	add_one_node(&g_report_list, info);
	report_loc(KAL_FALSE);

	kal_prompt_trace(MOD_MMI, "iotlock:  %s ,%d has_same_order_num_report_loc", __func__, __LINE__);

}

void report_loc(kal_bool report_amend)
{
	NODE *node = g_report_list.header;

	kal_prompt_trace(MOD_MMI, "iotlock:  %s ,begin", __func__);

	//gps ��λ�ɹ��������ϱ����������е�����
	while(node != NULL){
		COMM_LOC comm_loc = {0};
		ATTACH_LOC att_loc = {0};

		order_info *info = (order_info*)node->data;
		
		memcpy(&comm_loc, &g_comm_loc, sizeof(COMM_LOC));
		memcpy(&att_loc, &g_attach_loc, sizeof(ATTACH_LOC));

		kal_prompt_trace(MOD_MMI, "iotlock:  %s , amend state: %d", __func__, (info->state&0xFE));
		if(!report_amend) {
			NODE *tmp = NULL;
			if((info->state&0xFE) != (LOCK_AMEND_LOC_REPORT<<1)) {
				att_loc.attach.lock_state[3] |= info->state;
				send_location_and_state(info, &comm_loc, &att_loc);
				tmp = node;
				node = node->next;
				delete_one_node(&g_report_list, tmp);
				node_free(tmp);
			} else {
				node = node->next;
			}
		} else {
			NODE *tmp = NULL;
			if((info->state&0xFE) == (LOCK_AMEND_LOC_REPORT<<1)) {
				att_loc.attach.lock_state[3] |= info->state;
				send_location_and_state(info, &comm_loc, &att_loc);
				tmp = node;
				delete_one_node(&g_report_list, tmp);
				node_free(tmp);
			} else {
				node = node->next;
			}
		}
	}
	kal_prompt_trace(MOD_MMI, "iotlock:  %s ,end", __func__);
}

kal_bool check_loc_data_is_has_zero(COMM_LOC *comm_loc,ATTACH_LOC *att_loc)
{
	GPS_INFO info;
	int i;
	if((comm_loc->latitude ==0)&&(comm_loc->longitude ==0)&&(comm_loc->hight ==0))
	{
		kal_prompt_trace(MOD_MMI, "iotlock:  %s line:%d comm_loc latitude longitude hight has zero", __FUNCTION__, __LINE__);
		return KAL_TRUE;
	}
	else
	{

		info.alarm = comm_loc->alarm;
		info.state = comm_loc->state;
		info.hight = comm_loc->hight;
		info.latitude = comm_loc->latitude;
		info.longitude = comm_loc->longitude;
		info.speed = comm_loc->speed;
		info.direction = comm_loc->direction;

		att_loc->stations = MIN(BASE_STATION_MAX,att_loc->stations);
		info.stations = att_loc->stations;
		info.gnss = att_loc->attach.gnss[2];
		kal_prompt_trace(MOD_MMI, "iotlock:  %s line:%d info.attach.gnss[2] = %d", __FUNCTION__, __LINE__,info.gnss);
		info.mcc = att_loc->mcc;
		info.mnc = att_loc->mnc;
		for(i = 0; i < att_loc->stations; i++) {

			memcpy(&info.base_station[i], &att_loc->base_station[i], sizeof(BASE_STATION));
		}
		
		kal_prompt_trace(MOD_MMI, "iotlock:  %s line:%d alarm = %d latitude = %d state = %d longitude = %d hight = %d speed = %d direction = %d", __FUNCTION__, __LINE__
			,comm_loc->alarm,comm_loc->state,comm_loc->latitude,comm_loc->longitude,comm_loc->hight,comm_loc->speed,comm_loc->direction);

		kal_prompt_trace(MOD_MMI, "iotlock:  %s line:%d stations = %d mcc = %d mnc = %d", __FUNCTION__, __LINE__
			,att_loc->stations,att_loc->mcc,att_loc->mnc);
		
		iot_set_bkup_nv_gps_info(&info);
		kal_prompt_trace(MOD_MMI, "iotlock:  %s line:%d comm_loc latitude longitude hight no zero", __FUNCTION__, __LINE__);
		return KAL_FALSE;

	}
}

void comm_loc_has_zero_need_use_pre_comm_loc(COMM_LOC *comm_loc,ATTACH_LOC *att_loc)
{
	GPS_INFO info;
	int i;
	iot_get_bkup_nv_gps_info(&info);

	comm_loc->alarm = info.alarm;
	comm_loc->state = info.state;
	comm_loc->latitude = info.latitude;
	comm_loc->longitude = info.longitude;
	comm_loc->hight = info.hight;
	comm_loc->speed = info.speed;
	comm_loc->direction = info.direction;

	info.stations = MIN(BASE_STATION_MAX,info.stations);
	att_loc->stations = info.stations;
	att_loc->attach.gnss[2] = info.gnss;
	kal_prompt_trace(MOD_MMI, "iotlock:  %s line:%d info.attach.gnss[2] = %d", __FUNCTION__, __LINE__,info.gnss);
	att_loc->mcc = info.mcc;
	att_loc->mnc = info.mnc;

	for(i = 0; i < info.stations; i++) 
	{
		memcpy(&att_loc->base_station[i],&info.base_station[i], sizeof(BASE_STATION));
	}
	kal_prompt_trace(MOD_MMI, "iotlock:  %s line:%d alarm = %d state = %d latitude = %d longitude = %d hight = %d speed = %d direction = %d", __FUNCTION__, __LINE__
		,comm_loc->alarm,comm_loc->state,comm_loc->latitude,comm_loc->longitude,comm_loc->hight,comm_loc->speed,comm_loc->direction);

	kal_prompt_trace(MOD_MMI, "iotlock:  %s line:%d stations = %d mcc = %d mnc = %d", __FUNCTION__, __LINE__
		,att_loc->stations,att_loc->mcc,att_loc->mnc);
}

void send_location_and_state(order_info *orderInfo, COMM_LOC *comm_loc, ATTACH_LOC *att_loc)
{
	
	Byte buffer[400] = {0};
	Byte header[16] = {0};
	Byte body[384] = {0};
	
	kal_uint16 len;
	kal_uint16 body_len = 0;
	MESSAGE msg;
	Byte check_code;
	kal_bool resend = KAL_TRUE;
	
	if(check_loc_data_is_has_zero(comm_loc,att_loc))
	{
		if(g_reboot_use_pre_gps_data)
		{
			comm_loc_has_zero_need_use_pre_comm_loc(comm_loc,att_loc);
		}
		g_reboot_use_pre_gps_data = KAL_FALSE;
	}
	gen_location_and_state_info(body, &body_len, orderInfo, comm_loc, att_loc);
	msg.bodylen = body_len; //sizeof(COMM_LOC) + sizeof(ATTACH) + n*sizeof(BASE_STATION);
	msg.body = body;
	msg.headerlen = get_msg_hearder(header, orderInfo->msg_id, SECRET_NONE, msg.bodylen, &orderInfo->serial_num);
	msg.header = header;
	check_code = compute_check_code(msg);

	len = message_escape_and_addflag(buffer, msg, check_code);
	kal_prompt_trace(MOD_MMI, "iotlock:  %s begin body_len =%d, len=%d", __FUNCTION__, body_len, len);
	if(g_lock_cntx.auth_result) {
		lock_socket_send(g_lock_cntx.socket_id, buffer, len, resend, orderInfo->serial_num);
	}
}

void gen_location_and_state_info(Byte *body, kal_uint16 *body_len, order_info *orderInfo, COMM_LOC *comm_loc, ATTACH_LOC *att_loc)
{
	Byte *ptr = body;
	DWord unlock_count = 0;
	Word elec = 0;
	kal_uint32 vbat;
	BCD datetime[6] = {0};

	ORDER_NUM s_order_num;
	DATE_TIME s_date_time;
	BATT_TEMP s_batt_temp;
	kal_int16 temp;
	kal_bool is_has_order_num;
	*body_len = 0;
	if(orderInfo->msg_id == PLATFORM_CTRL_ANS_ID) {
		Word ansno = soc_htons(orderInfo->ans_serial);
		memcpy(ptr, &ansno, sizeof(Word));
		ptr += sizeof(Word);
		*body_len += sizeof(Word);
		lock_debug_print(MOD_MMI, "iotlock: %s sizeof(Word): %d, body_len=%d", __FUNCTION__, sizeof(Word), *body_len);
	}
	
	comm_loc->alarm = soc_htonl(orderInfo->bj);
	comm_loc->state = soc_htonl(comm_loc->state);
	comm_loc->state |= 0x1; //acc always open
	comm_loc->latitude = soc_htonl(comm_loc->latitude);
	comm_loc->longitude = soc_htonl(comm_loc->longitude);
	comm_loc->hight = soc_htons(comm_loc->hight);
	comm_loc->speed = soc_htons(comm_loc->speed);
	comm_loc->direction = soc_htons(comm_loc->direction);
	get_curr_time(comm_loc->datetime, orderInfo->timestamp);
	memcpy(ptr, comm_loc, sizeof(COMM_LOC));
	ptr += sizeof(COMM_LOC);
	*body_len += sizeof(COMM_LOC);
	lock_debug_print(MOD_MMI, "iotlock: %s sizeof(COMM_LOC): %d, body_len=%d", __FUNCTION__, sizeof(COMM_LOC), *body_len);

	att_loc->attach.network_strenth[0] = 0x30;
	att_loc->attach.network_strenth[1] = 0x01;
	att_loc->attach.network_strenth[2] = orderInfo->rssi;

	att_loc->attach.gnss[0] = 0x31;
	att_loc->attach.gnss[1] = 0x01;
	att_loc->attach.gnss[2] = gps_count;
	lock_debug_print(MOD_MMI, "iotlock: %s line:%d gps_count=%d", __FUNCTION__,__LINE__, gps_count);
	unlock_count = orderInfo->unlocks;
	att_loc->attach.unlock_count.id = 0xE1;
	att_loc->attach.unlock_count.len = 0x04;
	att_loc->attach.unlock_count.count = soc_htonl(unlock_count);

	att_loc->attach.lock_state[0] = 0xE2;
	att_loc->attach.lock_state[1] = 0x02;
	att_loc->attach.lock_state[2] = 0x0;
	lock_debug_print(MOD_MMI, "iotlock: %s lock_state=%d", __FUNCTION__, att_loc->attach.lock_state[3]);

	elec = get_battery_level();

	if(srv_charbat_is_charging()) {
		att_loc->attach.lock_state[3] |= (1<<6);
	} else {
		att_loc->attach.lock_state[3] &= ~(1<<6);
		if(g_lock_cntx.low_power == 1) 
		{
			att_loc->attach.lock_state[3] |= (1<<5);
		} else {
			att_loc->attach.lock_state[3] &= ~(1<<5);
		}
	}
	att_loc->attach.lock_state[3] &= ~(1<<7);
	
	att_loc->attach.volt.id = 0xE3;
	att_loc->attach.volt.len = 0x06;
	att_loc->attach.volt.elec = soc_htons(elec);
	bmt_get_avg_adc_channel_voltage(DCL_VBAT_ADC_CHANNEL, &vbat, 20);
	att_loc->attach.volt.volt = soc_htons((Word)(vbat/10000));
	bmt_get_avg_adc_channel_voltage(DCL_VCHARGER_ADC_CHANNEL, &vbat, 20);
	if((vbat/10000) < 350) {
		att_loc->attach.volt.charge_volt = 0;
	} else {
		att_loc->attach.volt.charge_volt = soc_htons((Word)(vbat/10000));
	}

	memcpy(ptr, &att_loc->attach, sizeof(ATTACH));
	ptr += sizeof(ATTACH);
	*body_len += sizeof(ATTACH);
	lock_debug_print(MOD_MMI, "iotlock: %s sizeof(ATTACH): %d, body_len=%d", __FUNCTION__, sizeof(ATTACH), *body_len);

	att_loc->stations = MIN(BASE_STATION_MAX,att_loc->stations);
	if(att_loc->stations > 0) {
		kal_uint8 i;
		*ptr = 0xE4;
		ptr++;
		*ptr = att_loc->stations * 7+4;
		ptr++;

		*ptr = att_loc->mcc >>8;
		ptr++;
		*ptr = att_loc->mcc %256;
		ptr++;

		*ptr = att_loc->mnc >>8;
		ptr++;
		*ptr = att_loc->mnc %256;
		ptr++;
		*body_len += 6;
		for(i = 0; i < att_loc->stations; i++) {
			att_loc->base_station[i].lac = soc_htons(att_loc->base_station[i].lac);
			att_loc->base_station[i].ci = soc_htonl(att_loc->base_station[i].ci);

			memcpy(ptr, &att_loc->base_station[i], sizeof(BASE_STATION));
			ptr += sizeof(BASE_STATION);
			*body_len += sizeof(BASE_STATION);
			lock_debug_print(MOD_MMI, "iotlock: %s sizeof(BASE_STATION): %d, body_len=%d", __FUNCTION__, sizeof(BASE_STATION), *body_len);
		}
	}
	
	if((g_lock_cntx.current_unlock_mode == NT_UNLOCK||g_lock_cntx.current_unlock_mode == BT_UNLOCK||
		g_lock_cntx.current_unlock_mode == SMS_UNLOCK) )
	{
		get_is_has_order_num(&is_has_order_num);
		lock_debug_print(MOD_MMI, "iotlock: %s  is_has_order_num=%d g_lock_cntx.is_has_order_num = %d g_lock_cntx.is_has_same_order_num = %d", __FUNCTION__,
				is_has_order_num,g_lock_cntx.is_has_order_num,g_lock_cntx.is_has_same_order_num);
		if((is_has_order_num||g_lock_cntx.is_has_order_num)&&!g_lock_cntx.is_has_same_order_num)
		{
			memset(&s_order_num, 0, sizeof(ORDER_NUM));
			s_order_num.id= 0xD1;
			s_order_num.len = strlen(orderInfo->order_num);//LOCK_ORDER_NUM_MAX_LEN - 1; //�̶�11�ֽ�
			memcpy(s_order_num.order_num, orderInfo->order_num, s_order_num.len);
			lock_debug_print(MOD_MMI, "iotlock: Line:%d, %s,order_num=%s",__LINE__, __func__, orderInfo->order_num);
			memcpy(ptr, &s_order_num, s_order_num.len+2);
			ptr += s_order_num.len+2;
			*body_len += s_order_num.len+2;
			lock_debug_print(MOD_MMI, "iotlock: %s() %d sizeof(ORDER_NUM): %d, body_len=%d,s_order_num.order_num = %s s_order_num.len = %d",
				__FUNCTION__,__LINE__, sizeof(ORDER_NUM), *body_len,s_order_num.order_num,s_order_num.len);

		}
		memset(&s_date_time, 0, sizeof(DATE_TIME));
		s_date_time.id= 0xD2;
		s_date_time.len = 0x04;
		s_date_time.open_lock_time = soc_htonl(orderInfo->unlock_timestamp);
		
		memcpy(ptr, &s_date_time, sizeof(DATE_TIME));
		ptr += sizeof(DATE_TIME);
		*body_len += sizeof(DATE_TIME);
		lock_debug_print(MOD_MMI, "iotlock: %s() %d sizeof(DATE_TIME): %d, body_len=%d",
			__FUNCTION__,__LINE__, sizeof(DATE_TIME), *body_len);

	}	
	
	s_batt_temp.id = 0xD3;
	s_batt_temp.len = 0x02;
	temp = iotlock_get_battery_temperature();
	s_batt_temp.vbat_temp = soc_htons(temp);
	
	memcpy(ptr, &s_batt_temp, sizeof(BATT_TEMP));
	ptr += sizeof(BATT_TEMP);
	*body_len += sizeof(BATT_TEMP);

	lock_debug_print(MOD_MMI, "iotlock: %s body_len: %d", __FUNCTION__, *body_len);
}

void gen_loc_request(kal_char* request)
{
	kal_uint8 i;
	kal_int16 strength;
	kal_char tmp[32] = {0};
	srv_nw_info_cntx_struct *cntx;
	kal_uint32 plmn;

	strcat(request, "GET ");
	strcat(request, lbs_path);

	cntx = srv_nw_info_get_cntx(MMI_SIM1);

	strength = cntx->signal.gsm_RSSI_in_qdBm >> 2;
	plmn = atoi(cntx->location.plmn);
	sprintf(tmp, "cl=%d,%d", (plmn/100), (plmn%100));
	strcat(request, tmp);
	memset(tmp, 0, sizeof(tmp));

	sprintf(tmp, ";%d,%d,%d", cntx->location.lac, cntx->location.cell_id, strength);
	strcat(request, tmp);
	memset(tmp, 0, sizeof(tmp));

	g_attach_loc.stations = MIN(BASE_STATION_MAX,g_attach_loc.stations);
	for(i = 0; i < g_attach_loc.stations; i++)
	{
		sprintf(tmp, ";%d,%d,%d", g_attach_loc.base_station[i].lac, g_attach_loc.base_station[i].ci,g_attach_loc.base_station[i].strenth);
		strcat(request, tmp);
		memset(tmp, 0, sizeof(tmp));
	}

	strcat(request, "&format=NMEA&app_key=ecbb8874ef592697764ac9c6847d602f");
	strcat(request, "&did=");
	strcat(request, g_device_id);
	strcat(request, " HTTP/1.1\r\n");
	strcat(request, "Host: ");
	strcat(request, lbs_host);
	strcat(request, "\r\n");
	strcat(request, "Connection: Closed\r\n\r\n");
}

void send_lbs_request(kal_int8 socket_id)
{
	kal_char request[256] = {0};
	gen_loc_request(request);
	if(soc_send(socket_id, request, strlen(request), 0) > 0){
		lock_debug_print(MOD_MMI, "iotlock: %s, send:%s", __FUNCTION__, request);
	}
}

void get_loc_from_json(kal_char *buffer)
{
	kal_char *p = strstr(buffer, "200 OK");
	double lon = 0.0;
	double lat = 0.0;
	kal_uint8 i;

	kal_prompt_trace(MOD_MMI, "iotlock: %s", buffer);
	if(p != NULL) {
		p = strstr(buffer, "\r\n\r\n") + 4; //skip http header
		kal_prompt_trace(MOD_MMI, "iotlock: %s", p);
		for(i = 0; i < 3; i++){
			if(p != NULL){
				p = strchr(p, ',');
				p +=1; //skip comma
			}
		}

		if(p != NULL) {
			lon = strtod(p, NULL);
			p = strchr(p, ',');
		}

		if(p != NULL){
			lat = strtod(p+1, NULL);
		}

		g_comm_loc.longitude = convert2(lon);
		g_comm_loc.latitude = convert2(lat);
	}
}

void delay_report_loc(order_info *info)
{
	kal_uint32 locate_time = 0;
	applib_time_struct curr_time;
	applib_dt_get_rtc_time(&curr_time);
	locate_time = applib_get_time_difference_ext_in_second(&curr_time, &g_gps_locate_time);

	if(locate_time > 5 && info->ans_serial == 0) {
		order_info *amend_info = get_one_order_info();
		memcpy(amend_info, info, sizeof(order_info));
		amend_info->state = LOCK_AMEND_LOC_REPORT<<1;
		g_attach_loc.attach.gnss[2] = 0; //gps counts
		g_comm_loc.state &= 0xFFFD;
		add_one_node(&g_report_list, amend_info);
		if(!IsMyTimerExist(LOCK_LOCK_AMEND_TIMER)) {
			StartTimer(LOCK_LOCK_AMEND_TIMER, gps_preon_time*1000, iot_lock_amend_locate);
		}
	}
	report_loc(KAL_FALSE);
}

void iot_lock_amend_locate()
{
	kal_prompt_trace(MOD_MMI, "iotlock: %s", __func__);
	report_loc(KAL_TRUE);
}
