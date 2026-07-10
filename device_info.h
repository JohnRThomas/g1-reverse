00000000 struct device_info_t // sizeof=0x18E0
00000000 {                                       // XREF: RAM:device_info/r
00000000     unsigned __int8 device_type;        // XREF: switch_to_dfu_mode+1E/r
00000000                                         // local_esbs_ipc_service_recv+1B4/r ...
00000001     unsigned __int8 work_mode;
00000002     unsigned __int8 reserved_early[201]; // XREF: sub_1793C+1E/w
00000002                                         // sub_17A40+124/w ...
000000CB     unsigned __int8 last_battery_soc;
000000CC     unsigned __int8 reserved_cc;
000000CD     unsigned __int8 onboarding_state;
000000CE     unsigned __int8 reserved_ce[6];
000000D4     unsigned __int8 display_command;
000000D5     unsigned __int8 current_screen_id;
000000D6     unsigned __int8 reserved_d6[15];
000000E5     unsigned __int8 sync_command_type;
000000E6     unsigned __int8 sync_sub_command;
000000E7     unsigned __int8 sync_param1;
000000E8     unsigned __int8 sync_param2;
000000E9     unsigned __int8 reserved_e9[3];
000000EC     unsigned __int8 next_screen_id;
000000ED     unsigned __int8 gap_ed[2667];       // XREF: spec_ble_command_hook+44/r
000000ED                                         // spec_ble_command_hook+C0/r ...
00000B58     unsigned __int8 is_debug;
00000B59     unsigned __int8 gap_b59[19];
00000B6C     struct projector_controller_t projector_controller;
00000EE4     unsigned __int8 gap_rem[133];
00000F69     unsigned __int8 current_battery_soc;
00000F6A     unsigned __int8 reserved_ed6;
00000F6B     unsigned __int8 battery_soc_display;
00000F6C     unsigned __int8 gap_ed8[12];
00000F78     unsigned __int8 display_state;
00000F79     unsigned __int8 gap_ee5[274];       // XREF: sub_FCF0+9C/w
00000F79                                         // sub_FCF0+F8/w ...
0000108B     unsigned __int8 sync_mode;
0000108C     unsigned __int8 initial_flag;
0000108D     unsigned __int8 gap_fe8[2];
0000108F     unsigned __int8 special_screen_id;
00001090     unsigned __int8 gap_feb[21];
000010A5     // padding byte
000010A6     // padding byte
000010A7     // padding byte
000010A8     void *not_disturb_struct_ptr;       // XREF: sub_31DD8+5C/r
000010AC     void *onboarding_struct_ptr;        // XREF: sub_31DD8+56/r
000010B0     unsigned __int8 gap_1008[8];        // XREF: spec_ble_command_hook+94C/r
000010B0                                         // spec_ble_command_hook+A64/r ...
000010B8     void *unknown_ptr_1032;
000010BC     unsigned __int8 gap_1014[28];
000010D8     void *screen_state_ptr;
000010DC     void *notification_buffer_ptr;
000010E0     unsigned __int8 remaining[2048];    // XREF: fuel_gauge_update:loc_10C82/w
000010E0                                         // fuel_gauge_update:loc_10E9E/r ...
000018E0 };