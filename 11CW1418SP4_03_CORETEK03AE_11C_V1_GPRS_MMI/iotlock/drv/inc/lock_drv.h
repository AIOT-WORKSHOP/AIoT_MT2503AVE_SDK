#ifndef __LOCK_DRV_H__
#define __LOCK_DRV_H__
#include "gpio_drv.h"
//#define OPEN_LOCK_WAIT_3S

#define MOTO_GPIO1   3
#define MOTO_GPIO2   2

#define ECG_MAX_ARRAY   10
#define ECG_PARA_NUM   39

#define 	IN_LED1_GPIO		0
#define 	IN_LED2_GPIO		27
#define 	IN_SPK_GPIO		1

#define AIOT_GPIO_RELAY 16

typedef enum{
	ATA_FAIL,
	ATA_PASS,
}ATA_RESULT;
typedef void (*open_lock_callback) (kal_bool result);

kal_bool ata_led1_check(void);
kal_bool ata_led2_check(void);
kal_bool ata_speaker_check(void);

void spronser_led_ctrl(kal_uint8 led_no, kal_uint16 time, kal_uint8 count);
void init_drv();
void feed_watchdog_work();
void Spconser_Delayms(kal_uint16 data);
LOCK_STATE read_lock_state(void);
void open_lock(void);
void open_lock_first_play_tone_then_unlock(UNLOCK_TYPE type);
void bt_open_lock(UNLOCK_TYPE type,open_lock_callback cb);
void reset_lock(void);
void open_beep_ms(kal_uint16 time, kal_uint8 count);
void init_beep(void);
void bike_break();
void bike_break_callback();
void bike_vibrate_callback();
void bike_slope_callback();
void open_lock_capacitive_hisr();
#ifdef OPEN_LOCK_WAIT_3S
void open_lock_wait_3s();
#endif
void gsensor_capacitive_hisr1(void);
void gsensor_capacitive_hisr2(void);
void close_lock_capacitive_hisr();
void stop_open_lock_normal();
void stop_open_lock_exception();
kal_bool open_lock_test(void);
kal_bool close_lock_test(void);
kal_bool open_beep_ms_test(void);

void get_ecg_begin_upload_data_timer(void);
kal_bool get_g_ecg_begin_upload_data(void);
void send_lock_ecg_data(void);
kal_int16  open_Charge_test(void);
void open_LED1_test(void);
void open_LED2_test(void);

void save_open_lock_time_to_nvram(kal_uint32 open_lock_time);
void get_open_lock_time_from_nvram(kal_uint32 *open_lock_time);
void iot_battery_over_temp_callback(void);
void uart1_sleep_enable(void);
void uart1_sleep_disable(void);
kal_int16 iot_get_battery_temp_volt(void);


void ECG_PWR_ON(void);
void ECG_PWR_OFF(void);
void iot_led_ctrl(kal_uint8 led_no, kal_uint16 time, kal_uint8 count);
void led1_ctrl_callback(void);
void led2_ctrl_callback(void);
void iot_led_on_off_ctrl(kal_uint8 led_no, kal_bool b_on);
void motion_sensor_pwr_on_off_switch(void);
void iot_system_sleep_mode_switch(void);
void iot_set_system_sleep_mode_enable(void);
void iot_set_system_sleep_mode_disable(void);
void iot_motor_start(kal_bool b_dir);
kal_uint8 iot_get_switch_state(kal_uint8 num);
void iot_motor_stop(void);
void iot_acc_sensor_get_xyz_test(void);
void iot_acc_sensor_get_xyz_mg(kal_int16 *accl_x,kal_int16 *accl_y,kal_int16 *accl_z);
void iot_uart1_power_ctrl(kal_bool b_on);
void iot_reset_move_2s_warn(void);
void iot_move_2s_warning(void);
kal_bool need_notify_move_2s(void);
void iot_led_flash(void);
kal_bool iot_led_speak_warning_callback(void);
void iot_find_bike_led_flash(void);
void gprs_and_sms_find_bike_led_flash(void);
void gprs_and_sms_find_bike_speaker_led_flash(void);
void open_lock_ata(void);
void aiot_relay_ctrl(kal_bool onoff);

#endif
