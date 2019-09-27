#ifdef __MTK_TARGET__
#include <stdlib.h>

#include "kal_general_types.h"
#include "MMIDataType.h"
#include "nbr_public_struct.h"
#include "mmi_frm_queue_gprot.h"
#include "mmi_msg_struct.h"
#include "NwInfoSrv.h"
#include "NwInfoSrvGprot.h"

#include "iotlock.h"

#include "kal_release.h"
#include "kal_trace.h"
#include "custom_config.h"
#include "kal_internal_api.h"

#include "mmi_frm_mem_gprot.h"
#include "EventsGprot.h"
#include "med_utility.h"
#include "ModeSwitchSrvGprot.h"

#include "cbm_api.h"
#include "soc_api.h"
#include "soc_consts.h"
#include "app_datetime.h"
#include "DateTimeType.h"
#include "Mmi_rp_srv_iot_lock_def.h"
#include "MMITimer_Int.h"

#include "mmi_frm_events_gprot.h"
#include "ProtocolEvents.h"
#include "mmi_msg_struct.h"
#include "nvram_common_defs.h"
#include "mmi_frm_nvram_gprot.h"
#include "common_nvram_editor_data_item.h"
#include "lock_data.h"
#include "lock_gps.h"
#include "lock_drv.h"
#include "lock_net.h"
#include "lock_utils.h"
#include "motion_sensor_custom.h"


const kal_char *lbs_host = "api.wiselbs.cn";
const kal_char *lbs_path = "/cell/get?";

gprs_lock_cntx g_lock_cntx = {0};

kal_uint32 auth_counts = 0;
kal_uint32 reg_counts = 0;
kal_bool g_switch_server_flag = KAL_FALSE;

extern kal_uint32 gps_preon_time;
Word g_gps_serial_number = 0;
static FS_HANDLE file_handle;
Byte date_buffer[MAX_BUFFER_LEN] = {0};
static int rec_len = 0;
static MMI_BOOL bGetHttpHead = MMI_FALSE;
#define SPCONSER_DEBUG
kal_uint32 g_voice_wirte_file_sum;

static kal_uint32 gprs_time = 0;
sockaddr_struct g_server_ip = {SOC_SOCK_STREAM, 0x04, 20000, {153, 3, 252, 58}}; //112.64.126.122 7089,114.215.70.46 6969
//sockaddr_struct g_server_ip = {SOC_SOCK_STREAM, 0x04, 20000, {115, 220, 253, 83}}; //112.64.126.122 7089,114.215.70.46 6969
//sockaddr_struct g_server_ip = {SOC_SOCK_STREAM, 0x04, 30000, {153, 3, 252, 58}}; //112.64.126.122 7089,114.215.70.46 6969


FS_HANDLE g_checkfile_handle;

kal_uint8 g_socket_reconnect_count = 0;
static kal_uint8 CONNECT_DELAY[2] = {30, 60};
applib_time_struct g_connect_timestamp = {0};
applib_time_struct g_rev_data_timestamp = {0};

extern kal_bool g_is_update_heart_gap;
extern kal_bool g_need_open_gps;

#define __USE_THE_COMPANY_IP__
/******************************************Global variable start******************/

//extern void mir3da_pwr_up(void);

/******************************************Global variable end******************/

kal_bool ensure_close_socket(SOCKET_TYPE soc_type)
{
	kal_bool result = KAL_FALSE;

	if(soc_type == TYPE_LOCK_SOC) {
		if(g_lock_cntx.socket_id >= 0) {
			if(soc_close(g_lock_cntx.socket_id) == SOC_SUCCESS) {
				g_lock_cntx.socket_id = -1;
				result = KAL_TRUE;
			}
		} else {
			result = KAL_TRUE;
		}
	} else if(soc_type == TYPE_NEW_LOCK_SOC) {
		if( g_lock_cntx.new_socket_id >= 0){
			if(soc_close(g_lock_cntx.new_socket_id) == SOC_SUCCESS) {
				g_lock_cntx.new_socket_id = -1;
				result = KAL_TRUE;
			}
		} else {
			result = KAL_TRUE;
		}
	} else if(soc_type == TYPE_LBS_SOC) {
		if( g_lock_cntx.lbs_socket >= 0){
			if(soc_close(g_lock_cntx.lbs_socket) == SOC_SUCCESS) {
				g_lock_cntx.lbs_socket = -1;
				result = KAL_TRUE;
			}
		} else {
			result = KAL_TRUE;
		}
	} else if(soc_type == TYPE_DOWNLOAD_SOC){
		if( g_lock_cntx.download_id >= 0){
			if(soc_close(g_lock_cntx.download_id) == SOC_SUCCESS) {
				g_lock_cntx.download_id = -1;
				result = KAL_TRUE;
			}
		} else {
			result = KAL_TRUE;
		}
	}

	return result;
}

void lock_init_account(void)
{
	static kal_bool inited = KAL_FALSE;
	if(!inited)
	{
		if(g_lock_cntx.app_id==0)
		{
			cbm_app_info_struct info; 
			memset(&info,0,sizeof(info));
			info.app_str_id = 10000;
			info.app_icon_id = 20000;
			info.app_type = DTCNT_APPTYPE_EMAIL | DTCNT_APPTYPE_SKIP_WIFI;
			cbm_register_app_id_with_app_info(&info, &g_lock_cntx.app_id);
			g_lock_cntx.account_id=CBM_DEFAULT_ACCT_ID;
			g_lock_cntx.account_id= cbm_encode_data_account_id(g_lock_cntx.account_id, CBM_SIM_ID_SIM1, g_lock_cntx.app_id, KAL_FALSE);
		}
		inited = KAL_TRUE;
	}
}


void lock_socket_create(SOCKET_TYPE soc_type)
{
	kal_uint8 val_async;
	kal_bool val_nonblocking=KAL_TRUE;
	kal_int8 ret_connect=SOC_ERROR;
	kal_bool val_nodelay = KAL_TRUE;
	kal_int8 ret_domain;
	kal_int8 socket_id;
	kal_uint8 ipbuf[16] = {0};
	kal_char domain_buffer[IOT_LOCK_DOMAIN_MAX_LEN] = {0};
	kal_uint8 iplen;
	kal_int32 request_id = 0;
	sockaddr_struct server_ip;
	static kal_uint8 create_fail = 0;

	g_lock_cntx.gprs_time = drv_get_current_time();

	//step 1: register data account
	lock_init_account();
	if(g_lock_cntx.app_id == 0)
	{
		lock_debug_print(MOD_MMI, "iotlock: %s register data account failed!", __FUNCTION__);
		lock_submit_error(soc_type, ERR_REGISTER_APPID);
		return;
	}

	//Step2: socket create
	if(ensure_close_socket(soc_type))
	{
		lock_debug_print(MOD_MMI, "iotlock: %s colse old socket ok!", __func__);
		socket_id = soc_create(SOC_PF_INET,SOC_SOCK_STREAM,0,MOD_MMI, g_lock_cntx.account_id);
		if(socket_id < 0)
		{
			lock_debug_print(MOD_MMI, "iotlock: %s create socket failed!", __func__);
			create_fail++;
			if(create_fail > 10)
			{
				kal_uint8 ex_reboot = 1;
				iot_set_bkup_nv_exception_reboot(&ex_reboot);
				srv_reboot_normal_start();
			}
			else
			{
				lock_submit_error(soc_type, ERR_SOCKET_CREATE);
			}
			return;
		}
		else
		{
			create_fail = 0;
		}

		if(soc_type == TYPE_LOCK_SOC) {
			g_lock_cntx.socket_id = socket_id;
			request_id = GET_LOCK_HOSTNAME;
			server_ip.port = g_lock_cntx.domain.port;
			g_lock_cntx.gprs_is_connecting = KAL_TRUE;
			memcpy(domain_buffer, g_lock_cntx.domain.domain_buffer, g_lock_cntx.domain.len);
		} else if(soc_type == TYPE_NEW_LOCK_SOC) {
			g_lock_cntx.new_socket_id = socket_id;
			request_id = GET_NEW_LOCK_HOSTNAME;
			server_ip.port = g_lock_cntx.new_domain.port;
			memcpy(domain_buffer, g_lock_cntx.new_domain.domain_buffer, g_lock_cntx.new_domain.len);
		} else if(soc_type == TYPE_LBS_SOC) {
			g_lock_cntx.lbs_socket = socket_id;
			request_id = GET_LBS_HOSTNAME;
			server_ip.port = g_lock_cntx.lbs_domain.port;
			memcpy(domain_buffer, g_lock_cntx.lbs_domain.domain_buffer, g_lock_cntx.lbs_domain.len);
		} else if(soc_type == TYPE_DOWNLOAD_SOC){
			g_lock_cntx.download_id = socket_id;
			request_id = GET_DOWNLOAD_VOICEPACKAGE;
			server_ip.port = g_lock_cntx.download_domian.port;
			memcpy(domain_buffer, g_lock_cntx.download_domian.domain_buffer, g_lock_cntx.download_domian.len);
			lock_debug_print(MOD_MMI, "iotlock: %s, copy info %d", g_lock_cntx.download_domian.domain_buffer,g_lock_cntx.download_id);
		}
	}
	else {
		lock_debug_print(MOD_MMI, "iotlock: %s colse old socket failed!", __func__);
		lock_submit_error(soc_type, ERR_SOCKET_CREATE);
		return;
	}

	//Step3:socket set nonblocking
	if(soc_setsockopt(socket_id, SOC_NBIO, &val_nonblocking,sizeof(val_nonblocking))<0)
	{
		lock_debug_print(MOD_MMI, "iotlock: %s set sockopt SOC_NBIO failed!", __FUNCTION__);
		lock_submit_error(soc_type, ERR_SOCKET_SET_NBIO);    
		return;
	}

	//Step4:socket set async
	val_async = SOC_WRITE | SOC_READ | SOC_CONNECT | SOC_CLOSE;
	if(soc_setsockopt(socket_id,SOC_ASYNC, &val_async,sizeof(val_async))<0)
	{
		lock_debug_print(MOD_MMI, "iotlock: %s set sockopt SOC_ASYNC failed!", __FUNCTION__);
		lock_submit_error(soc_type, ERR_SOCKET_SET_SYNC);
		return;
	}

	//Step5:socket set nodelay
	if(soc_setsockopt(socket_id,SOC_NODELAY, &val_nodelay, sizeof(val_nodelay))<0)
	{
		lock_debug_print(MOD_MMI, "iotlock: %s set sockopt SOC_NODELAY failed!", __FUNCTION__);
		lock_submit_error(soc_type, ERR_SOCKET_SET_NODELAY);
		return;
	}

	//Step6:DNS
	ret_domain = soc_gethostbyname(KAL_FALSE,MOD_MMI,request_id, domain_buffer, ipbuf, &iplen, 0, g_lock_cntx.account_id);
	if(ret_domain == SOC_SUCCESS)
	{
		memcpy(server_ip.addr, ipbuf, iplen);
		server_ip.addr_len = iplen;
		server_ip.sock_type = SOC_SOCK_STREAM;

		lock_debug_print(MOD_MMI, "iotlock: %s, addr:%d.%d.%d.%d", __FUNCTION__,
								ipbuf[0], ipbuf[1], ipbuf[2], ipbuf[3]);
		
		//step7:connect to server
		set_gsm_state(GSM_CONN_TCP);
		mmi_frm_set_protocol_event_handler(MSG_ID_APP_SOC_NOTIFY_IND,
												(PsIntFuncPtr)lock_socket_notify, MMI_TRUE);
		ret_connect = soc_connect(socket_id, &server_ip);
		if(ret_connect == SOC_SUCCESS)
		{
			if(soc_type == TYPE_LOCK_SOC)
			{
				//reg lock
				register_lock();
			} else if(soc_type == TYPE_NEW_LOCK_SOC)
			{
				save_new_server();
				register_lock();
			} else if(soc_type == TYPE_LBS_SOC) {
				//send lbs req
				//send_lbs_request(g_lock_cntx.lbs_socket);
			} else if(soc_type == TYPE_DOWNLOAD_SOC) {
				 //send http request
				send_download_request(g_lock_cntx.download_id); //send http request
			}
		}
		else if(ret_connect != SOC_WOULDBLOCK)
		{
			lock_submit_error(soc_type, ERR_SOCKET_CONNECT);
			return;
		}
	}
	else if(ret_domain != SOC_WOULDBLOCK) 
	{
		lock_submit_error(soc_type, ERR_DNS);
		return ;
	}else{
		lock_debug_print(MOD_MMI, "iotlock: %s  DNS SOC_WOULDBLOCK", __FUNCTION__);
		mmi_frm_set_protocol_event_handler(MSG_ID_APP_SOC_GET_HOST_BY_NAME_IND,
												(PsIntFuncPtr)get_host_by_name, MMI_TRUE);
	}
}

void lock_submit_error(SOCKET_TYPE soc_type, gprs_lock_error err_code){
	if(soc_type == TYPE_LOCK_SOC) {
		if(g_lock_cntx.socket_id >= 0) {
			if(soc_close(g_lock_cntx.socket_id) == SOC_SUCCESS) {
				g_lock_cntx.socket_id = -1;
			} else {
				lock_debug_print(MOD_MMI, "iotlock: %s TYPE_LOCK_SOC close socket error", __func__);
			}
		}
	} else if(soc_type == TYPE_NEW_LOCK_SOC) {
		if(g_lock_cntx.new_socket_id >= 0) {
			if(soc_close(g_lock_cntx.new_socket_id) == SOC_SUCCESS){
				g_lock_cntx.new_socket_id = -1;
			} else {
				lock_debug_print(MOD_MMI, "iotlock: %s TYPE_NEW_LOCK_SOC  close socket error", __func__);
			}
		}
	} else if(soc_type == TYPE_LBS_SOC) {
		if(g_lock_cntx.lbs_socket>= 0) {
			if(soc_close(g_lock_cntx.lbs_socket) == SOC_SUCCESS){
				g_lock_cntx.lbs_socket = -1;
			} else {
				lock_debug_print(MOD_MMI, "iotlock: %s TYPE_LBS_SOC  close socket error", __func__);
			}
		}
	}else if(soc_type == TYPE_DOWNLOAD_SOC) {
		if(g_lock_cntx.download_id>= 0) {
			if(soc_close(g_lock_cntx.download_id) == SOC_SUCCESS){
				g_lock_cntx.download_id = -1;
			} else {
				lock_debug_print(MOD_MMI, "iotlock: %s TYPE_DOWNLOAD_SOC  close socket error", __func__);
			}
		}
		lock_debug_print(MOD_MMI, "iotlock: %s  connect failed", __FUNCTION__);
	}

	switch(err_code){
		case ERR_REGISTER_APPID:
		case ERR_SOCKET_CREATE:
		case ERR_SOCKET_SET_NBIO:
		case ERR_SOCKET_SET_SYNC:
		case ERR_SOCKET_SET_NODELAY:
		case ERR_SOCKET_CONNECT:
		case ERR_DNS:
			break;
		default:
			break;
	}

	if(get_curr_mode() == IOT_LOCK_MODE_NORMAL||get_curr_mode() == IOT_LOCK_MODE_LOW_ENERGY) {
		StartTimerEx(LOCK_LOCK_TIMER, 10*1000, (oslTimerFuncPtr)lock_socket_create, (void*)soc_type);
	}
}

kal_bool get_host_by_name(void* inMsg)
{
	kal_int8 ret_connect=SOC_ERROR;
	kal_uint8 domain_app_id;
	app_soc_get_host_by_name_ind_struct* dns_ind;
	sockaddr_struct server_ip;

	lock_debug_print(MOD_MMI, "iotlock: %s, request_id=%d", __FUNCTION__, dns_ind->request_id);
	memset((void*)&server_ip, 0, sizeof(sockaddr_struct));
	if(g_lock_cntx.socket_id == -1){
		kal_prompt_trace(MOD_MMI, "iotlock: %s, socket_id = -1", __FUNCTION__);
		return KAL_FALSE;
	}
	if(!(inMsg))
	{
		return KAL_FALSE;
	}

	dns_ind = (app_soc_get_host_by_name_ind_struct*)inMsg;
	domain_app_id = cbm_get_app_id(dns_ind->account_id);
	if(domain_app_id != g_lock_cntx.app_id)
	{
		return KAL_FALSE;
	}

	if(dns_ind->request_id == GET_LOCK_HOSTNAME) {
		if (dns_ind && dns_ind->result == KAL_TRUE){
#ifdef __USE_THE_COMPANY_IP__
			server_ip.addr[0] = g_server_ip.addr[0];
			server_ip.addr[1] = g_server_ip.addr[1];
			server_ip.addr[2] = g_server_ip.addr[2];
			server_ip.addr[3] = g_server_ip.addr[3];
			server_ip.port = g_server_ip.port;
			server_ip.addr_len = 0x04;
			server_ip.sock_type = SOC_SOCK_STREAM;
#else
			memcpy(server_ip.addr, dns_ind->addr, dns_ind->addr_len);
        		server_ip.addr_len = dns_ind->addr_len;
			server_ip.sock_type = SOC_SOCK_STREAM;
			server_ip.port = g_lock_cntx.domain.port;
#endif		
			memcpy((void *)&g_lock_cntx.server_ip, &server_ip, sizeof(sockaddr_struct));

			kal_prompt_trace(MOD_MMI, "iotlock: %s, ip:%d.%d.%d.%d", __FUNCTION__,
				server_ip.addr[0], server_ip.addr[1], server_ip.addr[2], server_ip.addr[3]);
			kal_prompt_trace(MOD_MMI, "iotlock: %s, ip len:%d, sock-type=%d, port=%d", __FUNCTION__,
				server_ip.addr_len, server_ip.sock_type, server_ip.port);

			//step7:connect to server
			set_gsm_state(GSM_CONN_TCP);
			mmi_frm_set_protocol_event_handler(MSG_ID_APP_SOC_NOTIFY_IND,
													(PsIntFuncPtr)lock_socket_notify, MMI_TRUE);
			ret_connect = soc_connect(g_lock_cntx.socket_id, &server_ip);
			if(ret_connect == SOC_SUCCESS)
			{
				//reg lock
				set_gsm_state(GSM_SUCCESS);
				register_lock();
			}
			else if(ret_connect != SOC_WOULDBLOCK)
			{
				lock_submit_error(TYPE_LOCK_SOC, ERR_SOCKET_CONNECT);
			}
		}
		else {
 			 lock_submit_error(TYPE_LOCK_SOC, ERR_DNS);
		}
		return MMI_TRUE;
	}
	else if(dns_ind->request_id == GET_NEW_LOCK_HOSTNAME) {
		if (dns_ind && dns_ind->result == KAL_TRUE){
			memcpy(server_ip.addr, dns_ind->addr, dns_ind->addr_len);
        		server_ip.addr_len = dns_ind->addr_len;
			server_ip.sock_type = SOC_SOCK_STREAM;
			server_ip.port = g_lock_cntx.new_domain.port;
			memcpy((void *)&g_lock_cntx.new_server_ip, &server_ip, sizeof(sockaddr_struct));

			kal_prompt_trace(MOD_MMI, "iotlock: %s, ip:%d.%d.%d.%d", __FUNCTION__,
				dns_ind->addr[0], dns_ind->addr[1], dns_ind->addr[2], dns_ind->addr[3]);

			//step7:connect to server
			mmi_frm_set_protocol_event_handler(MSG_ID_APP_SOC_NOTIFY_IND,
													(PsIntFuncPtr)lock_socket_notify, MMI_TRUE);
			ret_connect = soc_connect(g_lock_cntx.new_socket_id, &server_ip);
			if(ret_connect == SOC_SUCCESS)
			{
				save_new_server();
				register_lock();
			}
			else if(ret_connect != SOC_WOULDBLOCK)
			{
				lock_submit_error(TYPE_NEW_LOCK_SOC, ERR_SOCKET_CONNECT);
			}
		}
		else {
	 		 lock_submit_error(TYPE_NEW_LOCK_SOC, ERR_DNS);
		}
		return MMI_TRUE;
	}	
	else if(dns_ind->request_id == GET_LBS_HOSTNAME) {
		lock_debug_print(MOD_MMI, "iotlock: %s, result=%d", __FUNCTION__, dns_ind->result);
		if (dns_ind && dns_ind->result == KAL_TRUE){
			lock_debug_print(MOD_MMI, "iotlock: %s, ip:%d.%d.%d.%d", __FUNCTION__,
				dns_ind->addr[0], dns_ind->addr[1], dns_ind->addr[2], dns_ind->addr[3]);
			memcpy(server_ip.addr, dns_ind->addr, dns_ind->addr_len);
			server_ip.addr_len = dns_ind->addr_len;
			server_ip.sock_type = SOC_SOCK_STREAM;
			server_ip.port = g_lock_cntx.lbs_domain.port;
			memcpy((void *)&g_lock_cntx.lbs_server_ip, &server_ip, sizeof(sockaddr_struct));

			//step7: connect to server
			mmi_frm_set_protocol_event_handler(MSG_ID_APP_SOC_NOTIFY_IND,
													(PsIntFuncPtr)lock_socket_notify, MMI_TRUE);
			ret_connect = soc_connect(g_lock_cntx.lbs_socket, &server_ip);
			if(ret_connect == SOC_SUCCESS)
			{
				//send lbs req
				send_lbs_request(g_lock_cntx.lbs_socket);
			}
			else if(ret_connect != SOC_WOULDBLOCK)
			{
				lock_submit_error(TYPE_LBS_SOC, ERR_SOCKET_CONNECT);
			}
		}
		else {
			lock_submit_error(TYPE_LBS_SOC, ERR_DNS);
		}
		return MMI_TRUE;
	}else if(dns_ind->request_id == GET_DOWNLOAD_VOICEPACKAGE) {
		lock_debug_print(MOD_MMI, "iotlock: %s, result=%d", __FUNCTION__, dns_ind->result);
		if (dns_ind && dns_ind->result == KAL_TRUE){
			lock_debug_print(MOD_MMI, "iotlock: %s, ip:%d.%d.%d.%d", __FUNCTION__,
				dns_ind->addr[0], dns_ind->addr[1], dns_ind->addr[2], dns_ind->addr[3]);
			memcpy(server_ip.addr, dns_ind->addr, dns_ind->addr_len);
			server_ip.addr_len = dns_ind->addr_len;
			server_ip.sock_type = SOC_SOCK_STREAM;
			server_ip.port = g_lock_cntx.download_domian.port;
			memcpy((void *)&g_lock_cntx.download_server_ip, &server_ip, sizeof(sockaddr_struct));

			//step7: connect to server
			mmi_frm_set_protocol_event_handler(MSG_ID_APP_SOC_NOTIFY_IND,
													(PsIntFuncPtr)lock_socket_notify, MMI_TRUE);
			ret_connect = soc_connect(g_lock_cntx.download_id, &server_ip);
			if(ret_connect == SOC_SUCCESS)
			{
				//send download req
				send_download_request(g_lock_cntx.download_id);
			}
			else if(ret_connect != SOC_WOULDBLOCK)
			{
				lock_submit_error(TYPE_DOWNLOAD_SOC, ERR_SOCKET_CONNECT);
			}
		}
		else {
			lock_submit_error(TYPE_DOWNLOAD_SOC, ERR_DNS);
		}
		return MMI_TRUE;
	}
	return MMI_FALSE;
}

kal_bool lock_socket_receive(kal_uint8 socket_id, Byte *buffer, kal_uint16 len, kal_uint16 *recvlen)
{
	int ret_recv = 0;
	
	ret_recv = soc_recv(socket_id,buffer, len,0);
	lock_debug_print(MOD_MMI, "iotlock:  %s soc_recv ret_recv =%d", __FUNCTION__, ret_recv);

	if(ret_recv > 0) {
		*recvlen = ret_recv;
		dump_buffer(buffer, ret_recv);
		return KAL_TRUE;
	} else {
		if(ret_recv != SOC_WOULDBLOCK) {
			*recvlen = 0;
			lock_debug_print(MOD_MMI, "iotlock: %s soc_recv failed", __FUNCTION__);
		}
		return KAL_FALSE;
	}
	
}

void lock_socket_send(kal_int8 socket_id, Byte *buffer, kal_uint16 len, kal_bool resend, Word number){
#ifdef __LOCK_ADD_AES_ENCRYPT__
			Byte aes_buff_in[1024] = {0};
			kal_uint16 in_buf_len = len;
			Byte aes_buff_out[1024] = {0};
			kal_uint32 out_buf_len = 0;
			memcpy(aes_buff_in, buffer,in_buf_len);
			lock_msg_body_add_aes_encrypt_to_buff(aes_buff_in,in_buf_len, aes_buff_out, (kal_uint32 *) &out_buf_len);
			memcpy(buffer, aes_buff_out,out_buf_len);
			len = out_buf_len;
#endif
	kal_prompt_trace(MOD_MMI, "iotlock: %s, resend=%d", __FUNCTION__, resend);
	if(socket_id >= 0) {
		kal_int32 ret = soc_send(socket_id, buffer, len, 0);
		kal_prompt_trace(MOD_MMI, "iotlock: %s, soc_send ret=%d", __FUNCTION__, ret);
		if(ret >= 0 || ret == SOC_WOULDBLOCK) {
			kal_uint8 offset = number % 40;
			kal_prompt_trace(MOD_MMI, "iotlock: %s, sending number=%d, state=%d", __FUNCTION__, number, STATE_SENDING);
			if(resend) {
				add_one_msg_to_list(buffer, len, number, STATE_SENDING);
				StartTimerEx(LOCK_RESEND_TIMEOUT_TIMER0 + offset,
						SEND_TIMEOUT, (oslTimerFuncPtr)resend_msg_timeout, (void*)number);
			}
		} else { //disconnected, need reconnect to server
			if(resend) {
				add_one_msg_to_list(buffer, len, number, STATE_WAIT_SEND);
			}
			//reconnect to server
			if(get_gsm_state() == GSM_SUCCESS) {
				kal_prompt_trace(MOD_MMI, "iotlock: %s, connect to server", __FUNCTION__);
				soc_close(socket_id);
				if(socket_id == g_lock_cntx.socket_id) {
					my_lock_socket_create();
				}
			}
		}
	}
	else {
		if(resend) {
			add_one_msg_to_list(buffer, len, number, STATE_WAIT_SEND);
		}
	}

	dump_out_buffer(buffer, len);
	
	kal_prompt_trace(MOD_MMI, "iotlock: end %s", __FUNCTION__);
}

void send_download_result(kal_bool result)
{
	lock_debug_print(MOD_MMI, "iotlock: %s ,result=%d", __FUNCTION__,result);
	FS_Close(file_handle);
	file_handle = -1;
	rec_len = 0;
	soc_close(g_lock_cntx.download_id);
	g_lock_cntx.download_id = -1;
	g_lock_cntx.is_downloading = MMI_FALSE;
	g_lock_cntx.is_receiveing= MMI_FALSE;
	bGetHttpHead = MMI_FALSE;
	if(result)
	{
		send_download_result_soc(g_lock_cntx.download_serial, 0);
	}
	else
	{
		send_download_result_soc(g_lock_cntx.download_serial, 1);
	}
}

kal_bool lock_socket_notify (void* msg_ptr)
{
	app_soc_notify_ind_struct* lock_soc_notify = (app_soc_notify_ind_struct*)msg_ptr;
	kal_int8 ret_connect=SOC_ERROR;

	lock_debug_print(MOD_MMI, "iotlock:  %s lock_soc_notify->socket_id=%d, g_lock_cntx.socket_id=%d, result=%d", __FUNCTION__,
			lock_soc_notify->socket_id, g_lock_cntx.socket_id, lock_soc_notify->result);

	lock_debug_print(MOD_MMI, "iotlock:  %s lock_soc_notify->socket_id=%d, g_lock_cntx.lbs_socket=%d, result=%d", __FUNCTION__,
			lock_soc_notify->socket_id, g_lock_cntx.lbs_socket, lock_soc_notify->result);
	
	lock_debug_print(MOD_MMI, "iotlock:  %s lock_soc_notify->socket_id=%d, g_lock_cntx.download_id=%d, result=%d", __FUNCTION__,
			lock_soc_notify->socket_id, g_lock_cntx.download_id, lock_soc_notify->result);
	
	lock_debug_print(MOD_MMI, "iotlock:  %s begin event_type=%d", __FUNCTION__, lock_soc_notify->event_type);

	switch(lock_soc_notify->event_type)
	{
		case SOC_READ: //0x01
		{
			kal_uint16 recvlen;
			if(lock_soc_notify->socket_id == g_lock_cntx.lbs_socket) {
				Byte buffer[MAX_BUFFER_LEN*2] = {0};
				if(lock_socket_receive(lock_soc_notify->socket_id, buffer, MAX_BUFFER_LEN*2, &recvlen)) {
					get_loc_from_json((kal_char*)buffer);
					soc_close(g_lock_cntx.lbs_socket);
					g_lock_cntx.lbs_socket = -1;
				}
			}else if(lock_soc_notify->socket_id == g_lock_cntx.download_id){
				my_download_socket_receive();
			}
			else if( lock_soc_notify->socket_id ==  g_lock_cntx.socket_id){
				Byte buffer[MAX_BUFFER_LEN] = {0};
				applib_dt_get_rtc_time(&g_rev_data_timestamp);
				if(lock_socket_receive(lock_soc_notify->socket_id, buffer, MAX_BUFFER_LEN, &recvlen)) {
					kal_uint16 i;
					kal_uint16 j = 0;
					kal_uint8 flag = 0;
					kal_uint8 count = 0;
					for(i = 0; i < recvlen; i++) {
						if(buffer[i] == 0x7E) {
							flag +=1;
							if(flag == 2) {
								flag = 0;
								count += 1;
								handle_command(buffer+j);
								j = i+1;
							}
						}
					}
				}
			}
			else {
				soc_close(lock_soc_notify->socket_id);
			}
			break;
		}
		case SOC_WRITE: //0x02
			{
				lock_debug_print(MOD_MMI, "iotlock: %s, SOC_WRITE", __FUNCTION__);
			}
			break;
		case SOC_CONNECT: //0x08
		{
			if(lock_soc_notify->socket_id == g_lock_cntx.lbs_socket)
			{
				if(lock_soc_notify->result == KAL_TRUE) //connect to server ok
				{
					send_lbs_request(g_lock_cntx.lbs_socket); //send http request
					lock_debug_print(MOD_MMI, "iotlock: , lbs_socket connect success");
				} else {
					soc_close(g_lock_cntx.lbs_socket);
					g_lock_cntx.lbs_socket = -1;
				}
			} 
			else if(lock_soc_notify->socket_id == g_lock_cntx.download_id)
			{
				if(lock_soc_notify->result == KAL_TRUE) //connect to server ok
				{
					if(g_lock_cntx.is_receiveing == MMI_FALSE)
					{
						send_download_request(g_lock_cntx.download_id); //send http request
					}
					lock_debug_print(MOD_MMI, "iotlock: %s, download_id connect success",__FUNCTION__);
				} else {
					soc_close(g_lock_cntx.download_id);
					g_lock_cntx.download_id = -1;
					send_download_result(MMI_FALSE);
					lock_debug_print(MOD_MMI, "iotlock: %s, download_id connect failed",__FUNCTION__);
				}
			} 
			else if(lock_soc_notify->socket_id == g_lock_cntx.socket_id)
			{
				if(lock_soc_notify->result == KAL_FALSE)    //connect to server failed
				{
					U32 delay = CONNECT_DELAY[g_socket_reconnect_count%2]*1000;
					lock_debug_print(MOD_MMI, "iotlock: %s socket connect failed, again", __FUNCTION__);
					StartTimerEx(LOCK_RECONNECT_TIMER, delay, (oslTimerFuncPtr)my_socket_reconnect, (void*)TYPE_LOCK_SOC);
				}
				else if(lock_soc_notify->result == KAL_TRUE) //connect to server ok
				{
					set_gsm_state(GSM_SUCCESS);
					g_socket_reconnect_count = 0;
					g_lock_cntx.gprs_is_connecting = KAL_FALSE;
					lock_debug_print(MOD_MMI, "iotlock: %s, connect to server ok", __FUNCTION__);
					g_lock_cntx.gprs_duration_time = drv_get_duration_ms(g_lock_cntx.gprs_time);
					StopTimer(LOCK_RECONNECT_TIMER);
					register_lock();
				}
			}
			else if(lock_soc_notify->socket_id == g_lock_cntx.new_socket_id)
			{
				if(lock_soc_notify->result == KAL_FALSE)    //connect to new server failed
				{
					//�����·�����ʧ�ܣ�ֱ�ӹر�
					soc_close(g_lock_cntx.new_socket_id);
				}
				else if(lock_soc_notify->result == KAL_TRUE) //connect to new server ok
				{
					lock_debug_print(MOD_MMI, "iotlock: %s, connect to new server ok", __FUNCTION__);
					
					//save new server ip and port
					set_gsm_state(GSM_SUCCESS);
					g_socket_reconnect_count = 0;
					g_switch_server_flag = KAL_TRUE;
					StopTimer(LOCK_RECONNECT_TIMER);
					save_new_server();
					register_lock();
					//lock_socket_create(TYPE_LBS_SOC); //LBS
				}
			}
			else {
				soc_close(lock_soc_notify->socket_id);
				lock_debug_print(MOD_MMI, "iotlock: %s, connect to server socket slot leaked", __func__);
			}
			break;
		}
		case SOC_CLOSE: //0x10
			if(lock_soc_notify->socket_id == g_lock_cntx.socket_id ) {
				if(lock_soc_notify->error_cause == SOC_CONNRESET) {
					//TCP half-write close
					lock_debug_print(MOD_MMI, "iotlock: %s, TCP half-write close", __FUNCTION__);
				} else {
					lock_debug_print(MOD_MMI, "iotlock: %s, other case it close, cause: %d", __FUNCTION__, lock_soc_notify->error_cause);
				}
				my_lock_socket_create();
			}
			else if(lock_soc_notify->socket_id == g_lock_cntx.download_id)
			{
				g_lock_cntx.is_downloading = MMI_FALSE;
				soc_close(g_lock_cntx.download_id);
				g_lock_cntx.download_id = -1;
			} else {
				soc_close(lock_soc_notify->socket_id);
			}
			break;
	}
	return MMI_TRUE;
}

void save_new_server()
{
	nvram_ef_iot_lock_struct info;

	soc_close(g_lock_cntx.socket_id); //close the old connection
	g_lock_cntx.socket_id = g_lock_cntx.new_socket_id;
	g_lock_cntx.new_socket_id = -1;

	memcpy((void*)&g_lock_cntx.domain, (void*)&g_lock_cntx.new_domain, sizeof(DOMAIN_T));

	ReadRecordIot(NVRAM_EF_IOT_LOCK_LID, 1, &info, NVRAM_EF_IOT_LOCK_SIZE);
	memset(info.ip_domain, 0, sizeof(info.ip_domain));
	memcpy(info.ip_domain, g_lock_cntx.new_domain.domain_buffer, g_lock_cntx.new_domain.len);
	info.port = g_lock_cntx.new_domain.port;
	memset(&info.auth_code, 0, 128);
	WriteRecordIot(NVRAM_EF_IOT_LOCK_LID, 1, &info, NVRAM_EF_IOT_LOCK_SIZE);
}

void lock_socket_close(SOCKET_TYPE soc_type)
{
	if(soc_type == TYPE_LOCK_SOC) {
		kal_prompt_trace(MOD_MMI, "iotlock: %s soc_type=%d", __FUNCTION__, soc_type);
		soc_close(g_lock_cntx.socket_id);
		g_lock_cntx.socket_id = -1;
		if(get_curr_mode() == IOT_LOCK_MODE_TRANS)
		{
			set_gsm_state(GSM_CLOSED); //power off
		}
		else
		{
			set_gsm_state(GSM_OPENED);
		}
		
	} else if(soc_type == TYPE_NEW_LOCK_SOC) {
		soc_close(g_lock_cntx.new_socket_id);
		g_lock_cntx.new_socket_id = -1;
	} else if(soc_type == TYPE_LBS_SOC) {
		soc_close(g_lock_cntx.lbs_socket);
		g_lock_cntx.lbs_socket = -1;
	}
}

U32 get_reg_auth_time_gap(kal_uint32 counts)
{
	U32 gap = 5;
	switch(counts) {
		case 1:
			gap = 5;
			break;
		case 2:
			gap = 10;
			break;
		case 3:
			gap = 30;
			break;
		case 4:
			gap = 60;
			break;
		case 5:
			gap = 180;
			break;
		default:
			gap = 180;
			break;
	}

	return gap;
}

void handle_register_ans(MESSAGE *msg)
{
	Byte token[128] = {0};
	Byte tokenlen;
	Byte ret = parse_reg_ans(msg->body, msg->bodylen, token, &tokenlen);
	StopTimer(LOCK_REG_TIMEOUT_TIMER);
	if( ret == 0 && tokenlen > 0) {
		reg_counts = 0;
		g_switch_server_flag = KAL_FALSE;
		kal_prompt_trace(MOD_MMI, "iotlock: %s tokenlen = %d", __FUNCTION__, tokenlen);
		save_token_to_nvram(token, tokenlen);
		lock_authorized();
	} else {
		U32 gap = get_reg_auth_time_gap(reg_counts);
		clear_token_from_nvram();
		kal_prompt_trace(MOD_MMI, "iotlock: %s gap=%ds", __FUNCTION__, gap);
		StartTimer(LOCK_REG_TIMER, gap*1000, register_lock);
	}
}

void handle_platform_com_ans(MESSAGE *msg)
{
	COMMON_REQ *req = (COMMON_REQ*)msg->body;
	kal_prompt_trace(MOD_MMI, "iotlock: %s, plat comm req id=%d, number = %d, result=%d", __FUNCTION__, req->id, req->serial, req->result);
	convert_comm_req_from_big_endian(req);
	kal_prompt_trace(MOD_MMI, "iotlock: %s, plat comm req id=%x", __FUNCTION__, req->id);

	switch(req->id) {
		case TERMINAL_AUTN_ID:
		{
			g_lock_cntx.auth_result = req->result == 0 ? KAL_TRUE : KAL_FALSE;
			StopTimer(LOCK_AUTH_TIMEOUT_TIMER);
			if(g_lock_cntx.auth_result) {
				auth_counts = 0;
				resend_msg(NULL);
				if(read_lock_state() == LOCKED) {
					open_gps_and_get_loc(g_lock_cntx.gps_update_lock_gap, TIMER_LOC_REPORT);
				} else {
					open_gps_and_get_loc(g_lock_cntx.gps_update_run_gap, TIMER_LOC_REPORT);
				}
			} else {
				if(auth_counts % 3 != 0) {
					U32 gap = get_reg_auth_time_gap(auth_counts);
					StartTimer(LOCK_AUTH_TIMER, gap*1000, lock_authorized);
				} else {
					register_lock();
				}
			}

			//ÿ��һ��ʱ�䷢��һ��������
			feed_watchdog_work();
			StartTimer(LOCK_HEART_BEAT_TIMER, g_lock_cntx.heart_beat_time_gap*1000, heart_beat);
		}
		break;
		case TERMINAL_HEART_ID:
			StopTimer(LOCK_HEART_TIMEOUT_TIMER);
			break;
		case TERMINAL_LOC_COM_ID:
		case PLATFORM_CTRL_ANS_ID:
		{
			//ȷ�Ϸ������Ѿ��յ���Ϣ
			remove_one_msg_from_list(KAL_TRUE, req->serial);
			//���ŷ��Ͷ����е���һ������
			resend_msg(NULL);
		}
		break;
		default:
			kal_prompt_trace(MOD_MMI, "iotlock: %s, plat comm req no this cmd", __FUNCTION__);
			break;
	}
}

void handle_set_terminal_param(MESSAGE *msg)
{
	Byte ret = set_device_paras(msg->body, msg->bodylen);
	MSG_HEADER *msg_header = (MSG_HEADER*) msg->header;

	send_term_com_ans(msg_header->serial_number, msg_header->id, ret);

	if(get_curr_mode() == IOT_LOCK_MODE_TRANS) {
		StartTimer(LOCK_TRANS_TIMER, 5*1000, switch_trans_mode);
	}

	if(domain_update()){
		reg_counts = 0;
		auth_counts = 0;
		lock_socket_create(TYPE_NEW_LOCK_SOC);
	}

	if(g_is_update_heart_gap)
	{
		StopTimer(LOCK_HEART_BEAT_TIMER);
		heart_beat();
		g_is_update_heart_gap = KAL_FALSE;
	}
}

void handle_terminal_ctrl(MESSAGE *msg)
{
	MSG_HEADER *msg_header = (MSG_HEADER*) msg->header;
	parse_flag_and_cmd(msg->body, msg->bodylen,msg_header->serial_number,msg_header->id);
}

void set_music_type(Byte type)
{
	
	switch(type)
	{
		case 0:
		{
			g_lock_cntx.music_type = LOCK_MUSIC_TYPE;
			break;
		}

		case 1:
		{
			g_lock_cntx.music_type = UNLOCK_MUSIC_TYPE;	
			break;
		}
		case 2:
		{
			g_lock_cntx.music_type = WARN_MUSIC_TYPE;	
			break;
		}
		default:
		{
			g_lock_cntx.music_type = LOCK_MUSIC_TYPE;
			break;
		}

	}
}


download_music_type get_music_type(void){
		return g_lock_cntx.music_type;
}

MMI_BOOL sethostbyurl(MESSAGE *msg)
{
	
	char *ptr = NULL;
	char *ptr1 = NULL;
	char *ptr2 = NULL;
	int url_len = 0;

	Byte type = *msg->body;

	set_music_type(type);
	kal_prompt_trace(MOD_MMI, "iotlock: %s, type = %d", __FUNCTION__,type);

	
	memset(g_lock_cntx.download_url,0,sizeof(g_lock_cntx.download_url));
	memcpy(g_lock_cntx.download_url,msg->body+1,msg->bodylen-1);
	ptr = strstr(g_lock_cntx.download_url,"//");
	if(ptr == NULL)
	{
		return MMI_FALSE;
	}

	ptr+=2;
	ptr1=strstr(ptr,"/");
	if(ptr1 == NULL)
	{
		return MMI_FALSE;
	}
	url_len = ptr1-ptr;
	if(url_len <= 0)
	{
		return MMI_FALSE;
	}
	g_lock_cntx.download_domian.len = url_len;
	memcpy(g_lock_cntx.download_domian.domain_buffer,ptr,url_len);
	kal_prompt_trace(MOD_MMI, "iotlock: %s, g_lock_cntx.download_domian.domain_buffer = %s", __FUNCTION__,
		g_lock_cntx.download_domian.domain_buffer);
	
	return MMI_TRUE;
}

void handle_set_ecg_param(MESSAGE *msg)
{
	Byte ret = set_ecg_paras(msg->body, msg->bodylen);
	MSG_HEADER *msg_header = (MSG_HEADER*) msg->header;

	send_term_com_ans(msg_header->serial_number, msg_header->id, ret);
}


void handle_set_device_state(MESSAGE *msg)
{
	MSG_HEADER *msg_header = (MSG_HEADER*) msg->header;
	Byte ret = parse_set_device_state_cmd(msg->body,msg_header->serial_number,msg_header->id);
	
	send_term_com_ans(msg_header->serial_number, msg_header->id, ret);
}


void handle_command(const Byte *buffer)
{
	kal_uint16 len;
	const Byte *ptr = (Byte*)buffer;

	if(check_cmd(buffer, &len)) {
		Byte buf_out[1024] = {0};
		Byte checkcode;
		MESSAGE msg;
		len = message_unescape(ptr, buf_out, len);
		split_buffer_to_msg(buf_out, len, &msg, &checkcode);
		if(check_check_code(msg, checkcode)) {
			MSG_HEADER *msg_header = (MSG_HEADER*) msg.header;
#ifdef __LOCK_ADD_AES_ENCRYPT__
			kal_uint32 aes_body_len = 0;
			Byte aes_msg_body[1024] = {0};
			aes_body_len = sizeof(aes_msg_body);
			if(check_message_is_aes_encrypt(msg_header))
			{
				free_msg(msg);
				split_aes_decrypt_buff_to_msg(buf_out, len, &msg);
			}
#endif
			convert_header_from_big_endian(msg_header);
			kal_prompt_trace(MOD_MMI, "iotlock: %s msg_id = %x", __FUNCTION__, msg_header->id);
			switch(msg_header->id) {
			case TERMINAL_REGISTER_ANS_ID: 
				//������Ӧ����Ϣ
				handle_register_ans(&msg);
				break;
			case PLATFORM_COM_ANS_ID:
				handle_platform_com_ans(&msg);
				break;
			case SET_TERMINAL_PARAM_ID:
				handle_set_terminal_param(&msg);
				break;
			case QUERY_TERMINAL_PARAM_ID:
				send_query_term_para_ans(msg_header->serial_number);
				break;
			case QUERY_TERMINAL_ATTR_ID:
				ans_query_attr(msg_header->serial_number);
				break;
			case TERMINAL_FOTA_ID:
			{
				send_term_com_ans(msg_header->serial_number, msg_header->id, 0);
				StartTimer(LOCK_FOTA_START_TIMER, 10 * 1000, adups_net_start_get_new_version);
			}	
				break;
			case TERMINAL_CTRL_ID:
				handle_terminal_ctrl(&msg);
				break;
			case QUERY_ONCE_GPS_REQ:
				{
					Byte flag = *msg.body;
					if(flag == 1) 	//���¶�λ�ϴ�gps��Ϣ
					{
						g_need_open_gps = KAL_TRUE;
						get_loc();
						g_gps_serial_number = msg_header->serial_number;
						StartTimer(LOCK_GPS_QUERY_TIMER, (gps_preon_time + 15)*1000, report_loc_gps_info);
					}
					else			//��ѯ�洢��gps��Ϣ
					{
						ans_saved_gps_attr(g_lock_cntx.socket_id,msg_header->serial_number);
					}
				}
				break;
			case PLATFORM_SET_DEVICE_STATE:
				{
					handle_set_device_state(&msg);
				}
				break;
			case QUERY_TEMP_ELEC_REQ:
					ans_query_charge_attr(g_lock_cntx.socket_id,msg_header->serial_number);
				break;

			case DOWN_VOICE_PACKAGE:
				{
					if(g_lock_cntx.is_downloading == MMI_TRUE)
					{
						send_term_com_ans(msg_header->serial_number, msg_header->id, 1);
					}
					else
					{
						g_lock_cntx.is_downloading = MMI_TRUE;
						if(sethostbyurl(&msg))
						{
							send_term_com_ans( msg_header->serial_number, msg_header->id, 0);
							g_lock_cntx.download_serial = msg_header->serial_number;
							kal_prompt_trace(MOD_MMI, "iotlock: %s create download soc begin", __FUNCTION__);
							lock_socket_create(TYPE_DOWNLOAD_SOC);
						}
						else
						{
							send_term_com_ans( msg_header->serial_number, msg_header->id, 1);
						}
					}
				}
				break;

			case QUERY_TERMINAL_IS_WORKING_ID:
					send_term_com_ans(msg_header->serial_number, msg_header->id, 0);
				break;

			case SET_ECG_CTR_PARAM_ID:
				handle_set_ecg_param(&msg);
				break;
			case QUERY_SET_ECG_CTR_PARAM_ID:
				send_query_ecg_para_ans(msg_header->serial_number);
				break;
			default:
				kal_prompt_trace(MOD_MMI, "iotlock: %s NO THIS COMMAND", __FUNCTION__);
				break;
			}
		}
		free_msg(msg);
		kal_prompt_trace(MOD_MMI, "iotlock: %s end", __FUNCTION__);
	} else {
		kal_prompt_trace(MOD_MMI, "iotlock: %s INVALID COMMAND", __FUNCTION__);
	}
}

kal_bool domain_update()
{
	if(g_lock_cntx.domain.len != g_lock_cntx.new_domain.len)
	{
		kal_prompt_trace(MOD_MMI, "iotlock: %s domain_len not equal", __FUNCTION__);
		return KAL_TRUE;
	}

	if(g_lock_cntx.domain.port != g_lock_cntx.new_domain.port)
	{
		kal_prompt_trace(MOD_MMI, "iotlock: %s domain_port not equal", __FUNCTION__);
		return KAL_TRUE;
	}

	if(strcmp(g_lock_cntx.domain.domain_buffer, g_lock_cntx.new_domain.domain_buffer)) {
		kal_prompt_trace(MOD_MMI, "iotlock: %s domain_domain_buffer not equal", __FUNCTION__);
		return KAL_TRUE;
	}

	return KAL_FALSE;
}

/*A5 A5 CC 33 11 11 11 11 30 00 00 00 01 00 00 00 01 02 00 45 00 00 00 00 00 00 00 00 00 00 00 01 4C 49 4E 57 00 00 00 00 7D FD BF C8 DE AD BE EF*/

void ecu_login_test(void)
{
	
	
	kal_uint8 login_buff[]={0xA5,0xA5,0xCC,0x33,0x11,0x11,0x11,0x11,
						0x30,0x00,0x00,0x00,0x01,0x00,0x00,0x00,
						0x01,0x02,0x00,0x45,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
						0x4C,0x49,0x4E,0x57,0x00,0x00,0x00,0x00,
						0x7D,0xFD,0xBF,0xC8,0xDE,0xAD,0xBE,0xEF};	

	
	StartTimer(LOCK_HEART_BEAT_TIMER, 10*1000, ecu_login_test);
	
	if(get_gsm_state() == GSM_SUCCESS) 
	{
		if(g_lock_cntx.socket_id >= 0 ) 
		{
			kal_uint8 write_len = 0;
			write_len = soc_send(g_lock_cntx.socket_id, login_buff, sizeof(login_buff), 0);
			dump_out_buffer(login_buff, sizeof(login_buff));
			lock_debug_print(MOD_MMI, "ecu iotlock:  %s, write_len=%d", __FUNCTION__, write_len);
		}
	}
	
}

void ecu_heartbeat_test(void)
{
	
	
}

void heart_beat()
{
	StartTimer(LOCK_HEART_BEAT_TIMER, g_lock_cntx.heart_beat_time_gap*1000, heart_beat);

	if(get_gsm_state() == GSM_SUCCESS) 
	{
		if(g_lock_cntx.socket_id >= 0 && g_lock_cntx.auth_result) 
		{
			send_heart_beat(g_lock_cntx.socket_id);
		}
	}
}
void check_gprs_connect(void)
{
	if(get_curr_mode() == IOT_LOCK_MODE_NORMAL||get_curr_mode() == IOT_LOCK_MODE_LOW_ENERGY) {
		kal_uint32 connect_time = 0;
		kal_uint32 no_data_time = 0;
		applib_time_struct curr_time = {0};

		applib_dt_get_rtc_time(&curr_time); //��ȡ��ǰʱ���

		if(applib_dt_is_valid(&g_connect_timestamp)) {
			connect_time = applib_get_time_difference_ext_in_second(&curr_time, &g_connect_timestamp);
		}

		if(g_lock_cntx.gprs_is_connecting) {
			if(connect_time >= 360) { //6 mintue
				//need to close and open rf
				lock_debug_print(MOD_MMI, "iotlock:  %s line:%d  need reconnect", __FUNCTION__,__LINE__);
				switch_reconnect_mode();
			}
		} else {
			if(applib_dt_is_valid(&g_rev_data_timestamp)) {
				no_data_time = applib_get_time_difference_ext_in_second(&curr_time, &g_rev_data_timestamp);
				if(get_gsm_state() == GSM_SUCCESS) 
				{
					if(no_data_time > 600) { //10 mintue
						//need to re-connect
						lock_debug_print(MOD_MMI, "iotlock:  %s line:%d  no need reconnect", __FUNCTION__,__LINE__);
						my_lock_socket_create();
					}
				}
			}
		}
	}
}
void kick_dog(void)
{
	kal_uint32 connect_time = 0;
	kal_uint32 no_data_time = 0;
	applib_time_struct curr_time = {0};
	StartTimer(LOCK_KICK_DOG_TIMER, 4*60*1000, kick_dog);
	feed_watchdog_work();
	check_gprs_connect();
}


void uart1_state_init(void)
{
	g_lock_cntx.uart1_state = iot_get_bkup_nv_third_byte();

	if(g_lock_cntx.uart1_state==0)
	{
		iot_uart1_power_ctrl(0);
		kal_prompt_trace(MOD_ENG, "iotlock: %s() line:%d: close uart1", __FUNCTION__,__LINE__);
	}
	else if(g_lock_cntx.uart1_state == 1)
	{
		iot_uart1_power_ctrl(1);
		kal_prompt_trace(MOD_ENG, "iotlock: %s() line:%d: open uart1", __FUNCTION__,__LINE__);
	}
	else
	{
		kal_prompt_trace(MOD_ENG, "iotlock: %s() line:%d: uart1 error state", __FUNCTION__,__LINE__);
	}
	
}

void LockTaskInit()
{
	kal_uint8 domain_len;
	nvram_ef_iot_lock_struct lock_info;
	kal_prompt_trace(MOD_MMI, "iotlock: %s enter iotlock task begin", __FUNCTION__);
#ifdef __ADUPS_FOTA_SOC__
	update_fota_upgrate_status();
#endif

	//init 
	ReadRecordIot(NVRAM_EF_IOT_LOCK_LID, 1, &lock_info, NVRAM_EF_IOT_LOCK_SIZE);
	if((read_lock_state() == LOCKED)&&(lock_info.mode == IOT_LOCK_MODE_TRANS))
	{
		lock_info.mode = IOT_LOCK_MODE_NORMAL;
		WriteRecordIot(NVRAM_EF_IOT_LOCK_LID, 1, &lock_info, NVRAM_EF_IOT_LOCK_SIZE);
	}
	memset(&g_lock_cntx, 0, sizeof(gprs_lock_cntx));
	set_gsm_state(GSM_OPENED);

	g_lock_cntx.lbs_socket = -1;
	g_lock_cntx.socket_id = -1;
	g_lock_cntx.new_socket_id = -1;
	g_lock_cntx.download_id= -1;
	update_all_msg_from_nvram();
	
	
	domain_len = strlen(lock_info.ip_domain);
	if(domain_len > 0) {
		memcpy(g_lock_cntx.domain.domain_buffer, lock_info.ip_domain, domain_len);
		g_lock_cntx.domain.len = domain_len;
	}

	if(lock_info.port > 0) {
		g_lock_cntx.server_ip.port = lock_info.port;
		g_lock_cntx.domain.port = lock_info.port;
	}
	g_lock_cntx.lbs_domain.port = 80;
	g_lock_cntx.lbs_domain.len = strlen(lbs_host);
	strcpy(g_lock_cntx.lbs_domain.domain_buffer, lbs_host);

	g_lock_cntx.download_domian.port = 80;
	g_lock_cntx.is_downloading = MMI_FALSE;
	g_lock_cntx.is_receiveing = MMI_FALSE;

	//init time and mode from nv
	g_lock_cntx.gps_update_lock_gap = lock_info.lock_second;
	g_lock_cntx.gps_update_run_gap = lock_info.run_second;
	set_curr_mode(lock_info.mode);
	g_lock_cntx.heart_beat_time_gap =lock_info.heart_beat_time_gap;
	g_lock_cntx.low_power = lock_info.low_power;
	g_lock_cntx.unlock_valid_time_gap =lock_info.unlock_valid_time_gap;

	g_lock_cntx.ecg_is_update = lock_info.ecg_is_update;
	g_lock_cntx.ecg_samp_time_gap = lock_info.ecg_samp_time_gap;
	g_lock_cntx.ecg_update_data_time_gap = lock_info.ecg_update_data_time;
	g_lock_cntx.ecg_curr_update_mode = lock_info.ecg_update_data_mode;
	uart1_state_init();
	//ÿ��һ��ʱ�䷢��һ��������
	StartTimer(LOCK_HEART_BEAT_TIMER, g_lock_cntx.heart_beat_time_gap*1000, heart_beat);
	StartTimer(LOCK_KICK_DOG_TIMER, 4*60*1000, kick_dog);

	motion_sensor_pwr_on_off_switch();
	if(read_lock_state() == UNLOCKED)
		g_normal_open_lock_state = TRUE;
	kal_prompt_trace(MOD_MMI, "iotlock: %s exit", __FUNCTION__);
}

mmi_ret iot_lock_sr_nw_availability_changed_notify(mmi_event_struct *evt) {
	srv_nw_info_service_availability_changed_evt_struct *availability_evt;

	kal_prompt_trace(MOD_MMI, "iotlock: %s enter begin", __FUNCTION__);
	if(get_gsm_state() == GSM_CLOSED) 
		return MMI_RET_OK;
	MMI_EXT_ASSERT(evt->evt_id == EVT_ID_SRV_NW_INFO_SERVICE_AVAILABILITY_CHANGED, evt->evt_id, 0, 0);

	if(get_curr_mode() ==IOT_LOCK_MODE_TRANS) {
		switch_lock_mode(IOT_LOCK_MODE_TRANS);
		return MMI_RET_OK;
	}

	availability_evt = (srv_nw_info_service_availability_changed_evt_struct*)evt;
	if (availability_evt->sim == MMI_SIM1) {
		switch (availability_evt->new_status) {
			case SRV_NW_INFO_SA_NO_SERVICE:
				kal_prompt_trace(MOD_MMI, "iotlock: %s new status: SRV_NW_INFO_SA_NO_SERVICE", __FUNCTION__);
				if(srv_sim_ctrl_is_inserted(MMI_SIM1)) 
				{
					set_gsm_state(GSM_CHECK_GPRS); //no service
				} 
				else 
				{
					set_gsm_state(GSM_CHECK_SIM); //no simcard
				}

				break;
			case SRV_NW_INFO_SA_FULL_SERVICE:
				kal_prompt_trace(MOD_MMI, "iotlock: %s new status: SRV_NW_INFO_SA_FULL_SERVICE", __FUNCTION__);
#ifdef __ADUPS_FOTA_SOC__
				if(get_fota_upgrate_status()) {
					//fota ����ʧ�ܣ����¿�ʼ����
					kal_prompt_trace(MOD_MMI, "iotlock: %s to fota", __FUNCTION__);
					adups_net_start_get_new_version();
				}else
#endif
				{
					my_lock_socket_create();
					spconser_sal_stub_cell_reg_req();
				}
				break;
			case SRV_NW_INFO_SA_LIMITED_SERVICE:
				kal_prompt_trace(MOD_MMI, "iotlock: %s new status: SRV_NW_INFO_SA_LIMITED_SERVICE", __FUNCTION__);
				if(srv_sim_ctrl_is_inserted(MMI_SIM1)) 
				{
					kal_prompt_trace(MOD_MMI, "iotlock: %s : GSM_CHECK_GPRS ", __FUNCTION__);
					set_gsm_state(GSM_CHECK_GPRS); //no service
				} 
				else 
				{
					kal_prompt_trace(MOD_MMI, "iotlock: %s : GSM_CHECK_SIM ", __FUNCTION__);
					set_gsm_state(GSM_CHECK_SIM); //no simcard
				}
				break;
			case SRV_NW_INFO_SA_SEARCHING:
				kal_prompt_trace(MOD_MMI, "iotlock: %s new status: SRV_NW_INFO_SA_SEARCHING", __FUNCTION__);
				set_gsm_state(GSM_REG);
				break;
			default:
				//Ignore
				return MMI_RET_OK;
		}
	}

	kal_prompt_trace(MOD_MMI, "iotlock: %s exit end", __FUNCTION__);
	return MMI_RET_OK;
}

mmi_ret iot_lock_sim_imsi_changed_notify(mmi_event_struct *evt) {
	srv_sim_ctrl_imsi_changed_evt_struct *sim_imsi_evt;

	kal_prompt_trace(MOD_MMI, "iotlock: %s enter begin", __FUNCTION__);
	MMI_EXT_ASSERT(evt->evt_id == EVT_ID_SRV_SIM_CTRL_HOME_PLMN_CHANGED, evt->evt_id, 0, 0);

	sim_imsi_evt = (srv_sim_ctrl_imsi_changed_evt_struct*)evt;
	if(sim_imsi_evt->sim == MMI_SIM1) {
		//get iccid or imsi
		get_iccid_req();
	}

	kal_prompt_trace(MOD_MMI, "iotlock: %s exit end", __FUNCTION__);
	
	return MMI_RET_OK;
}


void my_lock_socket_create(void)
{
	if(get_lock_curr_mode() == IOT_LOCK_MODE_NORMAL||get_curr_mode() == IOT_LOCK_MODE_LOW_ENERGY)
	{
		set_gsm_state(GSM_CONN_PPP);

		//��¼��ʼ���������ʱ��
		applib_dt_get_rtc_time(&g_connect_timestamp);
		lock_debug_print(MOD_MMI, "iotlock:  %s line:%d  no need reconnect", __FUNCTION__,__LINE__);
		if(g_lock_cntx.socket_id>=0)
		{
			soc_close(g_lock_cntx.socket_id);
			g_lock_cntx.socket_id = -1;
		}
		lock_socket_create(TYPE_LOCK_SOC);
	}
}


void my_socket_reconnect(SOCKET_TYPE soc_type)
{
	if(get_lock_curr_mode() == IOT_LOCK_MODE_NORMAL||get_curr_mode() == IOT_LOCK_MODE_LOW_ENERGY) 
	{
		g_socket_reconnect_count++;
		applib_dt_get_rtc_time(&g_connect_timestamp);
		lock_debug_print(MOD_MMI, "iotlock: %s g_socket_reconnect_count = %d", __FUNCTION__,g_socket_reconnect_count);
		lock_socket_create(soc_type);
	}
}


/**********************************download voice begin*********************/


void check_play_tone_with_filepath_and_set_new(void){
		kal_uint8 tone_path[520] = {0};
		FS_HANDLE my_file_handle;
		S32 fs_ret = FS_NO_ERROR;
		download_music_type music_type = get_music_type();
		
		if(music_type == LOCK_MUSIC_TYPE){
			my_file_handle = FS_CheckFile(CLOSE_TONE_FILE_DIR);
			lock_debug_print(MOD_MMI, "iotlock:  %s close.mp3 my_file_handle = %d", __FUNCTION__,my_file_handle);
			if ( my_file_handle >= FS_NO_ERROR)
			{
			       FS_Close(my_file_handle);
				FS_Delete(CLOSE_TONE_FILE_DIR);
				lock_debug_print(MOD_MMI, "iotlock:  %s FS_Delete  close.mp3", __FUNCTION__);
			} 

			FS_Rename(MMI_DATA_DEFAULT_FILE_DIR,CLOSE_TONE_FILE_DIR);
			iot_play_tone_with_filepath(IOT_TONE_LOCK);
		}else if (music_type == UNLOCK_MUSIC_TYPE){
			my_file_handle = FS_CheckFile(OPEN_TONE_FILE_DIR);
			lock_debug_print(MOD_MMI, "iotlock:  %s open.mp3 my_file_handle = %d", __FUNCTION__,my_file_handle);
			if ( my_file_handle >= FS_NO_ERROR)
			{
			       FS_Close(my_file_handle);
				FS_Delete(OPEN_TONE_FILE_DIR);
				lock_debug_print(MOD_MMI, "iotlock:  %s FS_Delete  open.mp3", __FUNCTION__);
			} 
			fs_ret = FS_Rename(MMI_DATA_DEFAULT_FILE_DIR,OPEN_TONE_FILE_DIR);
			lock_debug_print(MOD_MMI, "iotlock:  %s() %d FS_Rename fs_ret = %d", __FUNCTION__,__LINE__,fs_ret);
			
			iot_play_tone_with_filepath(IOT_TONE_UNLOCK);

		}else if(music_type == WARN_MUSIC_TYPE){
		
			my_file_handle = FS_CheckFile(WARN_TONE_FILE_DIR);
			lock_debug_print(MOD_MMI, "iotlock:  %s FS_Delete  close.mp3", __FUNCTION__,my_file_handle);
			if ( my_file_handle >= FS_NO_ERROR)
			{
			       FS_Close(my_file_handle);
				FS_Delete(WARN_TONE_FILE_DIR);
				lock_debug_print(MOD_MMI, "iotlock:  %s FS_Delete  warn.mp3", __FUNCTION__);
			} 

			FS_Rename(MMI_DATA_DEFAULT_FILE_DIR,WARN_TONE_FILE_DIR);
			iot_play_tone_with_filepath(IOT_TONE_WARN);
		}else{
			lock_debug_print(MOD_MMI, "iotlock:  %s() %d error music type", __FUNCTION__,__LINE__);
		}
		lock_debug_print(MOD_MMI, "iotlock:  %s rename file name", __FUNCTION__);

}

void send_download_request(kal_int8 socket_id)
{
    	char  send_buf[300]={0};
    	char CRLF[] = {0x0d,0x0a,0x00};
	S32 ret_send=0;

	memset(send_buf,0,sizeof(send_buf));

	strcat(send_buf,"GET ");
	strcat(send_buf,g_lock_cntx.download_url);
	strcat(send_buf," HTTP/1.1");
	strcat(send_buf,CRLF);
	strcat(send_buf,"Host: ");
	strcat(send_buf,g_lock_cntx.download_domian.domain_buffer);
	strcat(send_buf,CRLF);
	strcat(send_buf,"Cache-Control: no-cache");
	strcat(send_buf,CRLF);
	strcat(send_buf,"Pragma: no-cache");
	strcat(send_buf,CRLF);
	strcat(send_buf,CRLF);

	ret_send = soc_send(socket_id, send_buf, strlen(send_buf)+1, 0);

	if(ret_send > 0)
	{		
		lock_debug_print(MOD_MMI, "iotlock: %s, send:%s", __FUNCTION__, send_buf);
	}
	else if(ret_send != SOC_WOULDBLOCK)
	{
		lock_submit_error(TYPE_DOWNLOAD_SOC, ERR_SOCKET_CONNECT);
	return ;
	}
}

static voice_download_bool_type VOICEDOWNLOAD_GET_FLAG(U32 flag)
{
    return ((g_lock_cntx.download_flag) & flag) != 0 ? voicedownload_type_success : voicedownload_type_fail;
}

static void VOICEDOWNLOAD_SET_FLAG(U32 flag)
{

	lock_debug_print(MOD_MMI, "iotlock: %s() %d,g_lock_cntx.download_flag = %d ,g_lock_cntx.download_flag | flag= %d ", __FUNCTION__,__LINE__,
		g_lock_cntx.download_flag,
		g_lock_cntx.download_flag | flag);
    g_lock_cntx.download_flag |= flag;
}

static S32 voicedownload_write (const void* buffer, U32 offset, U32 length,
                       U32* p_nWritten)
{
	UINT nWrite;
	int  result;

	lock_debug_print(MOD_MMI, "iotlock:  %s() %d voicedownload_write file_handle =%d", __FUNCTION__, __LINE__,file_handle);

 	if(file_handle == -1)
	{
		file_handle = FS_Open((U16*) MMI_DATA_DEFAULT_FILE_DIR, FS_READ_WRITE |FS_CREATE);
		lock_debug_print(MOD_MMI, "iotlock:  %s() %d reopen file_handle =%d", __FUNCTION__, __LINE__,file_handle);

	}
	FS_Seek(file_handle,0,SEEK_END);
	result = FS_Write(file_handle, (void*) buffer, length, &nWrite);
	if (p_nWritten)
	{
		*p_nWritten = nWrite;
		g_voice_wirte_file_sum += nWrite;
	}
	FS_Close(file_handle);
	file_handle = -1;
	lock_debug_print(MOD_MMI, "iotlock: %s() %d,g_voice_wirte_file_sum = %d ",
		__FUNCTION__,__LINE__,g_voice_wirte_file_sum);
	
	lock_debug_print(MOD_MMI, "iotlock: %s() %d,length = %d ,*p_nWritten = %d ,result =%d",
		__FUNCTION__,__LINE__,length,*p_nWritten,result);


	return  result ? DOWNLOAD_ERROR : DOWNLOAD_SUCCESS;
}


static U32  voice_download_epofile_property(char *buf,int length){
	int i;
	char* current_ptr=buf;
	char *ptr_csm=NULL;
	char *ptr_length=NULL;
	U32 ret=KAL_TRUE;
	for(i=0;i<length;i++){
		if(buf[i]==0x0d && buf[i+1]==0x0a){
			buf[i]=0;
			lock_debug_print(MOD_MMI, "iotlock: %s() %d,current_ptr = %s ", __FUNCTION__,__LINE__,current_ptr);
			
			if(NULL == ptr_length){
				ptr_length=strstr(current_ptr,"Content-Length: ");
				if(ptr_length){
					ptr_length=ptr_length+strlen("Content-Length: ");
					lock_debug_print(MOD_MMI, "iotlock: %s() %d,epofile sieze :%d ", __FUNCTION__,__LINE__,atoi(ptr_length));
					g_lock_cntx.DOWN_EPOFILE_SIZE = atoi(ptr_length);
					lock_debug_print(MOD_MMI, "iotlock: %s() %d,DOWN_EPOFILE_SIZE :%d ", __FUNCTION__,__LINE__,g_lock_cntx.DOWN_EPOFILE_SIZE);
				}
			}

			ptr_csm=strstr(current_ptr,"ETag");
			if(ptr_csm){
				ptr_csm=ptr_csm+4;
				if( ptr_csm[2] != '"'){
					lock_debug_print(MOD_MMI, "iotlock: %s() %d,ERR_ETAG_NOT_FOUND", __FUNCTION__,__LINE__);
					return ret;
				}
				//add err code
				VOICEDOWNLOAD_SET_FLAG(FLAG_FIND_ETAG);
				ptr_csm=ptr_csm+3;
				strncpy(g_lock_cntx.check_sum,ptr_csm,sizeof(g_lock_cntx.check_sum)-1);
				g_lock_cntx.check_sum[sizeof(g_lock_cntx.check_sum)-1]=0;
				lock_debug_print(MOD_MMI, "iotlock: %s() %d,find check sum :%s", __FUNCTION__,__LINE__,g_lock_cntx.check_sum);
				return ret;
				break;
			}
			ptr_csm=NULL;
			current_ptr=buf+i+2;
		}
	}
    
	if(NULL == ptr_csm){
		lock_debug_print(MOD_MMI, "iotlock: %s() %d,can't find check sum", __FUNCTION__,__LINE__);
		ret=KAL_FALSE;
	}
	return ret;
}


static S32 voicedownload_open (void)
{
	check_file_exist_and_delete_temp_file();
	file_handle = FS_Open((U16*) MMI_DATA_DEFAULT_FILE_DIR, FS_READ_WRITE |FS_CREATE);
	lock_debug_print(MOD_MMI, "iotlock:  %s FS_Open  file_handle=%d", __FUNCTION__, file_handle);
	if(file_handle < 0)
	{
		send_download_result(MMI_FALSE);
		return DOWNLOAD_ERROR;
	}

	if(file_handle >= 0)
		return DOWNLOAD_SUCCESS;
	return  DOWNLOAD_ERROR;
}


static voice_download_bool_type voice_dn_deal_with_receiving_packet(U8 *buffer,U32 length){
	S32 ret_recv=length;
	int i;
	U32 len=0;
	int sum_temp;
	lock_debug_print(MOD_MMI, "iotlock: %s() %d,VOICEDOWNLOAD_GET_FLAG(FLAG_FIND_ETAG) = %d ", __FUNCTION__,__LINE__,
		VOICEDOWNLOAD_GET_FLAG(FLAG_FIND_ETAG));
	
	if(VOICEDOWNLOAD_GET_FLAG(FLAG_FIND_ETAG) == voicedownload_type_success){
		//step11:deal with receiving data for rest part.
		sum_temp=g_lock_cntx.download_sum;
		g_lock_cntx.download_sum+=ret_recv;
		lock_debug_print(MOD_MMI, "iotlock: %s() %d,g_lock_cntx.download_sum = %d ", __FUNCTION__,__LINE__,g_lock_cntx.download_sum);	
		if(g_lock_cntx.download_sum>g_lock_cntx.DOWN_EPOFILE_SIZE){
			if(DOWNLOAD_ERROR== voicedownload_write(&g_lock_cntx.download_recv_buf[0],
						0,
						g_lock_cntx.DOWN_EPOFILE_SIZE-sum_temp,
						&len) ){
				lock_debug_print(MOD_MMI, "iotlock: %s() %d,ERR_FILE_WRITE_FAIL ", __FUNCTION__,__LINE__);
				return voicedownload_type_fail;
			}			
			g_lock_cntx.download_sum=g_lock_cntx.DOWN_EPOFILE_SIZE;
		}else{
			if(DOWNLOAD_ERROR == voicedownload_write(&g_lock_cntx.download_recv_buf[0],
						0,
						ret_recv,
						&len) ){
				lock_debug_print(MOD_MMI, "iotlock: %s() %d,ERR_FILE_WRITE_FAIL ", __FUNCTION__,__LINE__);
				return voicedownload_type_fail;
			}
		}		
	}else{//find \r\n\r\n,then writen the following content
		//step10:deal with receiving data for find some properties.
		for(i=0;i<ret_recv-3;i++){
			if(g_lock_cntx.download_recv_buf[i]==0x0d && g_lock_cntx.download_recv_buf[i+1]==0x0a && 
				g_lock_cntx.download_recv_buf[i+2]==0x0d && g_lock_cntx.download_recv_buf[i+3]==0x0a){
				if(voice_download_epofile_property(g_lock_cntx.download_recv_buf,ret_recv) == KAL_FALSE){
					return;
				}
				i+=4;
				g_lock_cntx.download_sum+=i;
				lock_debug_print(MOD_MMI, "iotlock: %s() %d,g_lock_cntx.download_sum = %d ", __FUNCTION__,__LINE__,g_lock_cntx.download_sum);	
				g_lock_cntx.download_sum=ret_recv-i;
				if(DOWNLOAD_ERROR == voicedownload_open()){
					lock_debug_print(MOD_MMI, "iotlock: %s() %d,ERR_FILE_OPEN_FAIL", __FUNCTION__,__LINE__);	
					return voicedownload_type_fail;
				}
				if(DOWNLOAD_ERROR == voicedownload_write(&g_lock_cntx.download_recv_buf[i],
						0,
						g_lock_cntx.download_sum,
						&len) ){
					lock_debug_print(MOD_MMI, "iotlock: %s() %d,ERR_FILE_WRITE_FAIL", __FUNCTION__,__LINE__);
					return voicedownload_type_fail;
				}
				
				return voicedownload_type_success;	
				break;
			}
		}
	}
	return voicedownload_type_success;
}

static voice_download_bool_type voicedownload_check_download_finish(void){
	lock_debug_print(MOD_MMI, "iotlock: %s() %d,g_lock_cntx.download_sum = %d ", __FUNCTION__,__LINE__,g_lock_cntx.download_sum);	
	lock_debug_print(MOD_MMI, "iotlock: %s() %d,g_lock_cntx.DOWN_EPOFILE_SIZE = %d ", __FUNCTION__,__LINE__,g_lock_cntx.DOWN_EPOFILE_SIZE);	

	if(g_lock_cntx.download_sum == g_lock_cntx.DOWN_EPOFILE_SIZE){
			if(g_lock_cntx.download_id != -1){
				soc_close(g_lock_cntx.download_id); 
				g_lock_cntx.download_id=-1;
				lock_debug_print(MOD_MMI, "iotlock: %s() %d,g_epo_socket_cntx.socket_id = %d", __FUNCTION__,__LINE__,g_lock_cntx.download_id);
			}else{
				lock_debug_print(MOD_MMI, "iotlock: %s() %d,SOCKET_ALREADY_RELEASED", __FUNCTION__,__LINE__);
			}
				VOICEDOWNLOAD_SET_FLAG(FLAG_FINISH);
			if(my_voice_download_check() == DOWNLOAD_SUCCESS){
				VOICEDOWNLOAD_SET_FLAG(FLAG_SUCCESS);
				lock_debug_print(MOD_MMI, "iotlock: %s() %d,ERR_NO", __FUNCTION__,__LINE__);
				return voicedownload_type_success;
			}else{
				lock_debug_print(MOD_MMI, "iotlock: %s() %d,download fail", __FUNCTION__,__LINE__);
				return voicedownload_type_fail;
			}
	}
	return voicedownload_type_fail;
}

/********************************receive http response start*****************/
static void my_download_socket_receive(void)
{
    	S32 ret_recv=0;
	int i;
	U32 len=0;
	int sum_temp;

	if(g_lock_cntx.download_id == -1){
		lock_debug_print(MOD_MMI, "iotlock: %s,g_lock_cntx.download_id == -1 ", __FUNCTION__);
		return;
	}
	

	//step9:receive data
	while( g_lock_cntx.download_id  != -1){
		ret_recv = soc_recv(
							g_lock_cntx.download_id,	
							g_lock_cntx.download_recv_buf+g_lock_cntx.download_recv_buf_len,
							sizeof(g_lock_cntx.download_recv_buf)-g_lock_cntx.download_recv_buf_len,
							0
					);
        
		if(ret_recv >= 0){//receive  data
			g_lock_cntx.download_recv_buf_len += ret_recv;
		}else if(ret_recv != SOC_WOULDBLOCK){//occur error
			lock_debug_print(MOD_MMI, "iotlock: %s,ERR_DATA_RECEIVE ", __FUNCTION__);
			return;
		}

		if(g_lock_cntx.download_recv_buf_len ==0 && ret_recv == SOC_WOULDBLOCK){//no receive data
			lock_debug_print(MOD_MMI, "iotlock: %s,no receive data ", __FUNCTION__);
			return;
		}
		//when meet condition: receive the whole packet, or have received some packet and last packet size<=0, or received count more than epofilesize
		if(g_lock_cntx.download_recv_buf_len == sizeof(g_lock_cntx.download_recv_buf) || 
			(g_lock_cntx.download_recv_buf_len != ret_recv) ||
			g_lock_cntx.download_sum + g_lock_cntx.download_recv_buf_len >= g_lock_cntx.DOWN_EPOFILE_SIZE ){
			
			if(voice_dn_deal_with_receiving_packet(g_lock_cntx.download_recv_buf,g_lock_cntx.download_recv_buf_len) == voicedownload_type_fail){
				send_download_result(MMI_FALSE);
				check_file_exist_and_delete_temp_file();
				return;
			}
			if(voicedownload_type_success == voicedownload_check_download_finish()){
				lock_debug_print(MOD_MMI, "iotlock: %s(),%d voicedownload_type_success", __FUNCTION__,__LINE__);
				send_download_result(MMI_TRUE);
				check_play_tone_with_filepath_and_set_new();
				return;
			}
			g_lock_cntx.download_recv_buf_len=0;
		}
		
		
		if(ret_recv<=0)break;
	}
	
	return;  
}


static S32 my_voice_download_check (void)
{
    	WCHAR wszFilename[32];
	int ret;
	applib_md5_ctx mdContext;
	unsigned char hash[16]={0};
	int i;
	U32  fileHandle;
	U32 file_size=0;
	g_checkfile_handle = FS_Open((U16*) MMI_DATA_DEFAULT_FILE_DIR, FS_READ_ONLY);
	FS_Seek(g_checkfile_handle,0,SEEK_SET);
	if (FS_GetFileSize(g_checkfile_handle, &file_size) < 0)
	{
		FS_Close(g_checkfile_handle);
		return DOWNLOAD_ERROR;
	}

	lock_debug_print(MOD_MMI, "iotlock: %s() %d,file_size = %d ,file_size/1024 = %d K", __FUNCTION__,__LINE__,file_size,file_size/1024);
	lock_debug_print(MOD_MMI, "iotlock: %s() %d,g_lock_cntx.DOWN_EPOFILE_SIZE = %d", __FUNCTION__,__LINE__,g_lock_cntx.DOWN_EPOFILE_SIZE);

	if(file_size ==  g_lock_cntx.DOWN_EPOFILE_SIZE){
		applib_md5_init(&mdContext);
		my_applib_md5_file_update(&mdContext, wszFilename);
		applib_md5_final(hash, &mdContext);
		if(hash_string(hash,sizeof(hash)) == KAL_TRUE){
			return  DOWNLOAD_SUCCESS;
		}else{
			return  DOWNLOAD_ERROR;
		}
	}
    return  DOWNLOAD_ERROR;
}

static int hash_string(unsigned char *hash,int length){
	int i=0;
	unsigned char temp;
	unsigned char buf[33]={0};
	memset(buf,0,sizeof(buf));
	for(i=0;i<length;i++){
		sprintf(buf+i*2,"%02X",hash[i]);	
	}
	lock_debug_print(MOD_MMI, "iotlock:  %s buf = %s", __FUNCTION__,buf);
	lock_debug_print(MOD_MMI, "iotlock:  %s g_lock_cntx.check_sum = %s", __FUNCTION__,g_lock_cntx.check_sum);
	if(strcmp(buf,g_lock_cntx.check_sum) == 0){
		lock_debug_print(MOD_MMI, "iotlock:  %s DOWNLOAD_CHECKSUM_OK", __FUNCTION__);
		return KAL_TRUE;
	}else{
		lock_debug_print(MOD_MMI, "iotlock:  %s DOWNLOAD_CHECKSUM_FAILURE", __FUNCTION__);
		return KAL_FALSE;
	}
}

static kal_bool my_applib_md5_file_update(applib_md5_ctx *mdContext, const kal_wchar *filename)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    kal_uint8 buffer[1024];
    kal_uint32 dataLen = 0;
    kal_uint32 fileSize = 0;
    kal_int32 fileHandle=g_checkfile_handle;
    kal_uint32 rd_no = 0;

    
    if (FS_GetFileSize(fileHandle, &fileSize) < 0)
    {
        FS_Close(fileHandle);
        return KAL_FALSE;
    }

    while (fileSize)
    {
        if (fileSize > 1024)
        {
            dataLen = 1024;
        }
        else
        {
            dataLen = fileSize;
        }

        FS_Read(fileHandle, buffer, dataLen, &rd_no);
        if (rd_no != dataLen)
        {
            ASSERT(0);
        }
        applib_md5_update(mdContext, buffer, dataLen);
        fileSize -= dataLen;
    }
    return KAL_TRUE;
}


void check_file_exist_and_delete_temp_file(void)
{
	FS_HANDLE my_file_handle = -1;
	U32 file_size=0;
	kal_int32   ret = 0;
	
	my_file_handle = FS_CheckFile(MMI_DATA_DEFAULT_FILE_DIR);
	FS_GetFileSize(my_file_handle, &file_size);
	lock_debug_print(MOD_MMI, "iotlock: %s() %d,file_size = %d ,file_size/1024 = %d K", __FUNCTION__,__LINE__,file_size,file_size/1024);
	lock_debug_print(MOD_MMI, "iotlock:  %s my_file_handle = %d", __FUNCTION__,my_file_handle);
	if ( my_file_handle >= FS_NO_ERROR)
	{
		FS_Delete(MMI_DATA_DEFAULT_FILE_DIR);
		lock_debug_print(MOD_MMI, "iotlock:  %s FS_Delete  temp.mp3", __FUNCTION__);
	} 
	FS_Close(my_file_handle);
}
/**********************************receive http response end*********************/

/**********************************download voice end*********************/

void aws_gsm_state_kpled_callback(void)
{
	static kal_bool relay_ctrl = KAL_FALSE;

	//hello world test
	//kal_prompt_trace(MOD_MMI, "AIOT hello world:  %s line:%d ", __FUNCTION__, __LINE__);

	//relay_ctrl = !relay_ctrl;
	//aiot_relay_ctrl(relay_ctrl);
	
	if (get_gsm_state() == GSM_SUCCESS){
		spronser_led_ctrl(2, 100, 3);
	}else{
		spronser_led_ctrl(2, 500, 1);
	}

	if(get_gps_count()>0){
		lock_debug_print(MOD_MMI, "iotlock: get_gps_count is %d", get_gps_count());
		spronser_led_ctrl(1, 100, 3);
	}else{
		spronser_led_ctrl(1, 500, 1);
	}
	
	StartTimer(AWS_GSM_STATE_LED_TIMER, 1000, aws_gsm_state_kpled_callback);
}

void aws_gsm_state_kpled_init(void)
{	
	StartTimer(AWS_GSM_STATE_LED_TIMER, 1000, aws_gsm_state_kpled_callback);
}


#else  /* __MTK_TARGET__ */

#endif

