/*
 * Recovered global device state block for the Even G1 app core.
 *
 * The firmware keeps almost all cross-module state in one large struct at a
 * fixed RAM address; individual reconstructed functions currently reference its
 * fields via absolute addresses (see the parity-proof convention). This header
 * is the consolidated, named view recovered from reverse engineering
 * (mods.txt / result.h). Offsets are authoritative; names are best-effort.
 *
 * sizeof == 0x18E0
 */
#ifndef G1_DEVICE_INFO_H
#define G1_DEVICE_INFO_H

#include <stdint.h>

struct projector_controller_t;  /* forward: per-projector (L/R) control block */

struct device_info_t {
	uint8_t  device_type;          /* 0x000  L/R role, DFU switch reads this   */
	uint8_t  work_mode;            /* 0x001                                    */
	uint8_t  esb_channel_number;   /* 0x002  Nordic ESB sync channel (L<->R)   */
	uint8_t  gap_0003[198];
	uint8_t  dfu_soc_flag_1;       /* 0x0C9  set 0x83 to enter DFU             */
	uint8_t  dfu_soc_flag_2;       /* 0x0CA  set 1                             */
	uint8_t  last_battery_soc;     /* 0x0CB                                    */
	uint8_t  reserved_cc;
	uint8_t  onboarding_state;     /* 0x0CD                                    */
	uint8_t  reserved_ce[6];
	uint8_t  display_command;      /* 0x0D4                                    */
	uint8_t  current_app_id;       /* 0x0D5  current running application id    */
	uint8_t  reserved_d6[15];
	uint8_t  sync_command_type;    /* 0x0E5                                    */
	uint8_t  sync_sub_command;     /* 0x0E6                                    */
	uint8_t  sync_param1;          /* 0x0E7                                    */
	uint8_t  sync_param2;          /* 0x0E8                                    */
	uint8_t  reserved_e9[3];
	uint8_t  next_screen_id;       /* 0x0EC                                    */
	uint8_t  gap_00ED[1671];
	void    *system_function_ptr;  /* 0x778                                    */
	uint8_t  gap_0778[564];
	void    *settings_save_address_ptr;
	uint8_t  gap_09B0[4];
	uint32_t system_status_value;
	uint8_t  gap_09B8[299];
	uint8_t  system_status_flag;
	uint8_t  gap_0AE4[16];
	void    *display_control_ptr;
	uint8_t  gap_0AF8[20];
	uint8_t  display_mode_flag;
	uint8_t  gap_0B0D[75];
	uint8_t  is_debug;             /* 0xB58                                    */
	uint8_t  gap_b59[19];
	uint8_t  projector_controller[888]; /* 0xB6C struct projector_controller_t */
	uint8_t  gap_0EE4[16];
	uint8_t  wakeup_angle_level;   /* IMU wear/wake tuning                     */
	uint8_t  wakeup_angle_offset;
	uint8_t  gap_0EF6[106];
	uint8_t  anti_shake_enable;
	uint8_t  gap_0F61[8];
	uint8_t  current_battery_soc;  /* 0xF69                                    */
	uint8_t  reserved_ed6;
	uint8_t  battery_soc_display;
	uint8_t  gap_ed8[12];
	uint8_t  display_state;        /* 0xF78                                    */
	uint8_t  gap_0F79[31];
	uint8_t  auto_brightness_flag;
	uint8_t  gap_0F99[39];
	uint8_t  device_status_byte_1;
	uint8_t  device_status_byte_2;
	uint8_t  device_status_flag;
	uint8_t  gap_0FC3;
	uint8_t  device_info_byte_3;
	uint8_t  device_info_byte_4;
	uint8_t  device_info_byte_5;
	uint8_t  gap_0FC7[19];
	uint8_t  mac_addresses[12];    /* Master / Node / Slave BLE MACs           */
	uint8_t  gap_0FDB[14];
	uint8_t  display_setting_mode; /* 3 = always-on                            */
	uint8_t  display_silent_mode;  /* 10 normal, 11 always-on, 12 DND          */
	uint8_t  gap_0FEB;
	void    *schedule_checksum_ptr;
	void    *countdown_timer_ptr;
	void    *schedule_task_data_ptr;
	uint8_t  gap_0FF8[4];
	void    *teleprompter_data_ptr;
	void    *flash_storage_interface_ptr;
	void    *reset_type_1_ptr;
	void    *reset_type_2_ptr;
	void    *factory_reset_ptr;
	uint8_t  gap_1010[8];
	void    *raster_config_ptr;
	uint8_t  gap_101C[16];
	void    *dfu_function_ptr;
	uint8_t  gap_1030[28];
	uint32_t settings_save_command_id;
	uint8_t  gap_1050[4];
	void    *task_status_ptr;
	uint8_t  gap_1058[51];
	uint8_t  sync_mode;            /* 0x108B                                   */
	uint8_t  initial_flag;
	uint8_t  gap_fe8[2];
	uint8_t  wear_detection_mode;
	uint8_t  gap_feb[21];
	uint8_t  gap_10A5[11];
	uint8_t  gap_1008[8];
	uint8_t  gap_10B8[4];
	uint8_t  gap_10BC[10];
	uint8_t  buried_point_data[192]; /* usage analytics                        */
	uint8_t  gap_10C7[17];
	uint8_t  gap_10D8[8];
	uint8_t  gap_10E0[368];
	uint8_t  phone_connection_type;  /* 1 = iOS, 2 = Android                    */
	uint8_t  gap_1251[7];
	uint8_t  ancs_enable_flag;       /* Apple Notification Center Service       */
	uint8_t  gap_1259[30];
	uint8_t  message_stay_time_mode;
	uint8_t  gap_1278[1452];
	uint8_t  display_raster_height_gear;
	uint8_t  display_canvas_distance_gear;
	uint8_t  gap_1826[186];
};

#endif /* G1_DEVICE_INFO_H */
