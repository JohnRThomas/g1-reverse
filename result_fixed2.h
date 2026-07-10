struct device_info_t // sizeof=0x18E0
{
    unsigned __int8 device_type; // XREF: switch_to_dfu_mode+1E/r
    unsigned __int8 work_mode; // 
    unsigned __int8; // Modified from reserved_early
    unsigned __int8 gap_0003[101]; // 
    unsigned __int8; // Modified from reserved_early[102]
    unsigned __int8 gap_0069[23]; // 
    unsigned __int8; // Modified from reserved_early[126]
    unsigned __int8 gap_0081[72]; // 
    unsigned __int8; // Modified from reserved_early[199]
    unsigned __int8; // Modified from reserved_early[200]
    unsigned __int8 last_battery_soc; // 
    unsigned __int8 reserved_cc; // 
    unsigned __int8 onboarding_state; // 
    unsigned __int8 reserved_ce[6]; // 
    unsigned __int8 display_command; // 
    unsigned __int8; // Modified from current_screen_id
    unsigned __int8 reserved_d6[15]; // 
    unsigned __int8 sync_command_type; // 
    unsigned __int8 sync_sub_command; // 
    unsigned __int8 sync_param1; // 
    unsigned __int8 sync_param2; // 
    unsigned __int8 reserved_e9[3]; // 
    unsigned __int8 next_screen_id; // 
    unsigned __int8 gap_00ED[1671]; // 
    void* system_function_ptr; // Modified from gap_ed[1671]
    unsigned __int8 gap_0778[564]; // 
    void* settings_save_address_ptr; // Modified from gap_ed[2239]
    unsigned __int8 gap_09B0[4]; // 
    unsigned __int32; // Modified from gap_ed[2247]
    unsigned __int8 gap_09B5[302]; // 
    unsigned __int8; // Modified from gap_ed[2550]
    unsigned __int8 gap_0AE4[16]; // 
    void* display_control_ptr; // Modified from gap_ed[2567]
    unsigned __int8 gap_0AF8[20]; // 
    unsigned __int8; // Modified from gap_ed[2591]
    unsigned __int8 gap_0B0D[75]; // 
    unsigned __int8 is_debug; // 
    unsigned __int8 gap_b59[19]; // 
    unsigned __int8 gap_0B6C[888];
    unsigned __int8 gap_0EE4[16]; // 
    unsigned __int8; // Modified from gap_rem[16]
    unsigned __int8; // Modified from gap_rem[17]
    unsigned __int8 gap_0EF6[106]; // 
    unsigned __int8; // Modified from gap_rem[124]
    unsigned __int8 gap_0F61[8]; // 
    unsigned __int8 current_battery_soc; // 
    unsigned __int8 reserved_ed6; // 
    unsigned __int8 battery_soc_display; // 
    unsigned __int8 gap_ed8[12]; // 
    unsigned __int8 display_state; // 
    unsigned __int8 gap_0F79[31]; // 
    unsigned __int8; // Modified from gap_ee5[31]
    unsigned __int8 gap_0F99[39]; // 
    unsigned __int8; // Modified from gap_ee5[71]
    unsigned __int8; // Modified from gap_ee5[72]
    unsigned __int8; // Modified from gap_ee5[73]
    unsigned __int8 gap_0FC3; // 
    unsigned __int8; // Modified from gap_ee5[75]
    unsigned __int8; // Modified from gap_ee5[76]
    unsigned __int8; // Modified from gap_ee5[77]
    unsigned __int8 gap_0FC7[5]; // 
    unsigned __int8; // Modified from gap_ee5[83]
    unsigned __int8 gap_0FCD[13]; // 
    unsigned __int8; // Modified from gap_ee5[97]
    unsigned __int8 gap_0FDB[14]; // 
    unsigned __int8; // Modified from gap_ee5[112]
    unsigned __int8; // Modified from gap_ee5[113]
    unsigned __int8 gap_0FEB; // 
    void* schedule_checksum_ptr; // Modified from gap_ee5[115]
    void* countdown_timer_ptr; // Modified from gap_ee5[119]
    void* schedule_task_data_ptr; // Modified from gap_ee5[123]
    unsigned __int8 gap_0FF8[4]; // 
    void* teleprompter_data_ptr; // Modified from gap_ee5[131]
    void* flash_storage_interface_ptr; // Modified from gap_ee5[135]
    void* reset_type_1_ptr; // Modified from gap_ee5[139]
    void* reset_type_2_ptr; // Modified from gap_ee5[143]
    void* factory_reset_ptr; // Modified from gap_ee5[147]
    unsigned __int8 gap_1010[8]; // 
    void* raster_config_ptr; // Modified from gap_ee5[159]
    unsigned __int8 gap_101C[16]; // 
    void* dfu_function_ptr; // Modified from gap_ee5[179]
    unsigned __int8 gap_1030[28]; // 
    unsigned __int32; // Modified from gap_ee5[211]
    unsigned __int8 gap_104D[7]; // 
    void* task_status_ptr; // Modified from gap_ee5[219]
    unsigned __int8 gap_1058[51]; // 
    unsigned __int8 sync_mode; // 
    unsigned __int8 initial_flag; // 
    unsigned __int8 gap_fe8[2]; // 
    unsigned __int8; // Modified from special_screen_id
    unsigned __int8 gap_feb[21]; // 
    unsigned __int8 gap_10A5[11];
    unsigned __int8 gap_1008[8]; // XREF: spec_ble_command_hook+94C/r
    unsigned __int8 gap_10B8[4];
    unsigned __int8 gap_10BC[10]; // 
    unsigned __int8; // Modified from gap_1014[10]
    unsigned __int8 gap_10C7[17]; // 
    unsigned __int8 gap_10D8[8];
    unsigned __int8 gap_10E0[368]; // 
    unsigned __int8; // Modified from remaining[368]
    unsigned __int8 gap_1251[7]; // 
    unsigned __int8; // Modified from remaining[376]
    unsigned __int8 gap_1259[30]; // 
    unsigned __int8; // Modified from remaining[407]
    unsigned __int8 gap_1278[1452]; // 
    unsigned __int8; // Modified from remaining[1860]
    unsigned __int8; // Modified from remaining[1861]
    unsigned __int8 gap_1826[186]; // 
};