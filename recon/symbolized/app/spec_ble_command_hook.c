#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0000ef28 @ 0x0000ef28
 * public-name: spec_ble_command_hook
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strcmp                                   <= FUN_0000eefe @ 0x0000eefe
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   opt3007_get_max_lux                      <= FUN_00010a68 @ 0x00010a68
 *   ancs_get_conn_ctx                        <= FUN_000181fc @ 0x000181fc
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   subcontracing_send_data_pkcs7            <= FUN_00021a40 @ 0x00021a40
 *   mobile_send_notification_to_ble_device_test <= FUN_00021c04 @ 0x00021c04
 *   simulator_ancs_calendar_schedule_trigger <= FUN_00021cd8 @ 0x00021cd8
 *   refresh_and_read_box_field_timer         <= FUN_00025448 @ 0x00025448
 *   mark_master_or_low_battery_flag          <= FUN_0002efc0 @ 0x0002efc0
 *   debug_print_hex_dump                     <= FUN_0004a424 @ 0x0004a424
 *   sys_reboot                               <= FUN_0004c0a8 @ 0x0004c0a8
 *   cjson_delete                             <= FUN_00064b1c @ 0x00064b1c
 *   cjson_create_object                      <= FUN_00064ca4 @ 0x00064ca4
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
 *   k_uptime_get_0                           <= FUN_0007c18e @ 0x0007c18e
 *   ble_requeue_command_via_dispatch         <= FUN_0007c244 @ 0x0007c244
 *   cjson_print_pretty                       <= FUN_00085014 @ 0x00085014
 *   cjson_add_item_to_object_thunk           <= FUN_00085046 @ 0x00085046
 *   cjson_object_add_number                  <= FUN_00085076 @ 0x00085076
 *   cjson_add_string_to_object               <= FUN_0008509e @ 0x0008509e
 *   check_is_release_mode                    <= FUN_00086a06 @ 0x00086a06
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   safe_memcpy_checked                      <= FUN_00086c1e @ 0x00086c1e
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 *   vdprintf_to_fd                           <= FUN_00086f00 @ 0x00086f00
 *   strcpy                                   <= FUN_00086fee @ 0x00086fee
 *   __strcpy_chk                             <= FUN_00086ffe @ 0x00086ffe
 *   strncmp                                  <= FUN_00087036 @ 0x00087036
 *   checked_strncpy_zero_pad                 <= FUN_00087080 @ 0x00087080
 *   strstr                                   <= FUN_000870be @ 0x000870be
 * address symbols (name @ address):
 *   ADDR_ble_requeue_command_via_dispatch_THUMB @ 0x0007c245
 *   rodata_99899                             @ 0x00099899   [INLINED -- G6 literal batch]
 *   rodata_9d7f7                             @ 0x0009d7f7
 *   rodata_9d7fa                             @ 0x0009d7fa   [INLINED -- G6 literal batch]
 *   rodata_9d81e                             @ 0x0009d81e
 *   rodata_9d822                             @ 0x0009d822   [INLINED -- G6 literal batch]
 *   rodata_9d857                             @ 0x0009d857
 *   rodata_9d85b                             @ 0x0009d85b   [INLINED -- G6 literal batch]
 *   rodata_9d88c                             @ 0x0009d88c
 *   rodata_9d890                             @ 0x0009d890   [INLINED -- G6 literal batch]
 *   rodata_9d8b1                             @ 0x0009d8b1
 *   rodata_9d8b5                             @ 0x0009d8b5   [INLINED -- G6 literal batch]
 *   rodata_9d8da                             @ 0x0009d8da
 *   rodata_9d8de                             @ 0x0009d8de   [INLINED -- G6 literal batch]
 *   rodata_9d8ed                             @ 0x0009d8ed   [INLINED -- G6 literal batch]
 *   rodata_9d8fc                             @ 0x0009d8fc   [INLINED -- G6 literal batch]
 *   rodata_9d90a                             @ 0x0009d90a   [INLINED -- G6 literal batch]
 *   rodata_9d925                             @ 0x0009d925   [INLINED -- G6 literal batch]
 *   rodata_9d92b                             @ 0x0009d92b   [INLINED -- G6 literal batch]
 *   rodata_9d94a                             @ 0x0009d94a   [INLINED -- G6 literal batch]
 *   rodata_9d95b                             @ 0x0009d95b   [INLINED -- G6 literal batch]
 *   rodata_9d969                             @ 0x0009d969   [INLINED -- G6 literal batch]
 *   rodata_9d9a5                             @ 0x0009d9a5   [INLINED -- G6 literal batch]
 *   rodata_9d9ed                             @ 0x0009d9ed   [INLINED -- G6 literal batch]
 *   rodata_9da2f                             @ 0x0009da2f   [INLINED -- G6 literal batch]
 *   rodata_9da61                             @ 0x0009da61
 *   rodata_9db03                             @ 0x0009db03   [INLINED -- G6 literal batch]
 *   rodata_9db15                             @ 0x0009db15   [INLINED -- G6 literal batch]
 *   rodata_9db45                             @ 0x0009db45   [INLINED -- G6 literal batch]
 *   rodata_9db4f                             @ 0x0009db4f   [INLINED -- G6 literal batch]
 *   rodata_9db81                             @ 0x0009db81   [INLINED -- G6 literal batch]
 *   rodata_9db91                             @ 0x0009db91   [INLINED -- G6 literal batch]
 *   rodata_9dbb4                             @ 0x0009dbb4   [INLINED -- G6 literal batch]
 *   rodata_9dbc5                             @ 0x0009dbc5   [INLINED -- G6 literal batch]
 *   rodata_9dbec                             @ 0x0009dbec   [INLINED -- G6 literal batch]
 *   rodata_9dc17                             @ 0x0009dc17
 *   rodata_9dc1a                             @ 0x0009dc1a   [INLINED -- G6 literal batch]
 *   rodata_9dc9c                             @ 0x0009dc9c   [INLINED -- G6 literal batch]
 *   rodata_9dcbb                             @ 0x0009dcbb   [INLINED -- G6 literal batch]
 *   rodata_9dd09                             @ 0x0009dd09   [INLINED -- G6 literal batch]
 *   rodata_9dd24                             @ 0x0009dd24
 *   rodata_9dd27                             @ 0x0009dd27   [INLINED -- G6 literal batch]
 *   rodata_9dd4b                             @ 0x0009dd4b
 *   rodata_9dd4e                             @ 0x0009dd4e   [INLINED -- G6 literal batch]
 *   rodata_9dd6a                             @ 0x0009dd6a
 *   rodata_9dd6d                             @ 0x0009dd6d
 *   rodata_9dd70                             @ 0x0009dd70
 *   rodata_9dd73                             @ 0x0009dd73   [INLINED -- G6 literal batch]
 *   rodata_9dd91                             @ 0x0009dd91
 *   rodata_9dd94                             @ 0x0009dd94   [INLINED -- G6 literal batch]
 *   rodata_9ddb9                             @ 0x0009ddb9
 *   rodata_9ddbc                             @ 0x0009ddbc
 *   rodata_9ddbf                             @ 0x0009ddbf
 *   rodata_9ddc8                             @ 0x0009ddc8
 *   rodata_9ddcb                             @ 0x0009ddcb
 *   rodata_9ddce                             @ 0x0009ddce   [INLINED -- G6 literal batch]
 *   rodata_9ddd8                             @ 0x0009ddd8
 *   rodata_9dddb                             @ 0x0009dddb
 *   rodata_9ddde                             @ 0x0009ddde   [INLINED -- G6 literal batch]
 *   rodata_9dde8                             @ 0x0009dde8
 *   rodata_9ddeb                             @ 0x0009ddeb   [INLINED -- G6 literal batch]
 *   rodata_9de32                             @ 0x0009de32
 *   rodata_9de35                             @ 0x0009de35   [INLINED -- G6 literal batch]
 *   rodata_9de4c                             @ 0x0009de4c
 *   rodata_9de4f                             @ 0x0009de4f   [INLINED -- G6 literal batch]
 *   rodata_9de5e                             @ 0x0009de5e
 *   rodata_9de61                             @ 0x0009de61   [INLINED -- G6 literal batch]
 *   rodata_9de63                             @ 0x0009de63
 *   rodata_9de6e                             @ 0x0009de6e
 *   rodata_9de71                             @ 0x0009de71
 *   rodata_9de74                             @ 0x0009de74   [INLINED -- G6 literal batch]
 *   rodata_9dfa9                             @ 0x0009dfa9   [INLINED -- G6 literal batch]
 *   rodata_9e235                             @ 0x0009e235
 *   rodata_a1f20                             @ 0x000a1f20
 *   rodata_f1031                             @ 0x000f1031
 *   rodata_f3c02                             @ 0x000f3c02
 *   g_log_level                              @ 0x2000230c
 *   g_battery_percent                        @ 0x200069e8
 *   g_200069ec                               @ 0x200069ec
 *   g_200069f0                               @ 0x200069f0
 *   g_200069f4                               @ 0x200069f4
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ble_switch_status_reason               @ 0x20007aac
 *   g_panel_spi_id                           @ 0x2000a074
 *   g_2000ff4e                               @ 0x2000ff4e
 */
/* Full reconstruction spec_ble_command_hook @ 0xef28. */
#include <stdint.h>
#include <stdbool.h>
typedef uint8_t undefined; typedef uint8_t undefined1; typedef uint16_t undefined2;
typedef uint32_t undefined4; typedef uint64_t undefined8; typedef uint8_t byte;
typedef uint32_t uint; typedef uint64_t ulonglong; typedef uint32_t code(uintptr_t,...);
#define DAT_0000f1e4 ((unsigned long)&rodata_9d7f7) /*=0x9d7f7*/
#define DAT_0000f1e8 ((volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define DAT_0000f1ec ((volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_0000f1f0 ((unsigned long)"spec_ble_command_hook") /*=0x9dfa9*/
#define DAT_0000f458 0x00000000u
#define DAT_0000f46c ((volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define DAT_0000f470 ((volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_0000f474 ((unsigned long)"%s(): pos=%s, tx_data_len=%d\n\n") /*=0x9d92b*/
#define DAT_0000f478 ((unsigned long)&rodata_a1f20) /*=0xa1f20*/
#define DAT_0000f4a0 ((unsigned long)&rodata_f3c02) /*=0xf3c02*/
#define DAT_0000f4a4 ((unsigned long)"teleprompter_info") /*=0x9db03*/
#define DAT_0000f4a8 ((unsigned long)"%s(): simulator:SCHEDULE \350\247\246\345\217\221.\n\n") /*=0x9db91*/
#define DAT_0000f76c ((volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_0000f770 ((unsigned long)"spec_ble_command_hook") /*=0x9dfa9*/
#define DAT_0000f794 ((volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define DAT_0000fa50 ((unsigned long)&rodata_9dd70) /*=0x9dd70*/
#define DAT_0000fa54 ((volatile int *)((unsigned long)&g_battery_percent) /*=0x200069e8*/)
#define DAT_0000fa64 ((unsigned long)"TX:%d,fail:%d,RX:%d,Signal:%d") /*=0x9dd73*/
#define DAT_0000fa68 ((unsigned long)&rodata_9dd91) /*=0x9dd91*/
#define DAT_0000fa6c ((volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define DAT_0000fa70 ((volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_0000fa74 ((unsigned long)"spec_ble_command_hook") /*=0x9dfa9*/
#define DAT_0000fa84 ((volatile int *)((unsigned long)&g_ble_switch_status_reason) /*=0x20007aac*/)
#define DAT_0000fa88 ((unsigned long)&rodata_9ddbf) /*=0x9ddbf*/
#define DAT_0000fa8c ((unsigned long)&rodata_9ddc8) /*=0x9ddc8*/
#define DAT_0000faac ((volatile int *)((unsigned long)&g_panel_spi_id) /*=0x2000a074*/)
#define DAT_0000fab0 ((unsigned long)"2024-12-28 20:20:45") /*=0x99899*/
#define DAT_0000fab4 ((unsigned long)&g_2000ff4e) /*=0x2000ff4e*/
#define DAT_0000fca0 0x00000000u
#define DAT_0000fca8 0x00000000u
#define DAT_0000fcc8 ((volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_0000fce0 ((unsigned long)&rodata_f1031) /*=0xf1031*/
#define PTR_DAT_0000f1f8 ((unsigned long)&rodata_9d81e) /*=0x9d81e*/
#define PTR_DAT_0000f1fc ((unsigned long)"%s(): \346\250\241\346\213\237\346\216\245\346\224\266\345\210\260\346\226\260\351\200\232\347\237\245 title:%s, message:%s\n") /*=0x9d822*/
#define PTR_DAT_0000f204 ((unsigned long)&rodata_9d857) /*=0x9d857*/
#define PTR_DAT_0000f208 ((unsigned long)"%s(): \346\250\241\346\213\237\346\212\254\345\244\264/\344\275\216\345\244\264\350\247\246\345\217\221:pos:%s, val=%d\n\n") /*=0x9d85b*/
#define PTR_DAT_0000f20c ((unsigned long)&rodata_9d88c) /*=0x9d88c*/
#define PTR_DAT_0000f214 ((unsigned long)&rodata_9d8b1) /*=0x9d8b1*/
#define PTR_DAT_0000f21c ((unsigned long)&rodata_9d8da) /*=0x9d8da*/
#define PTR_DAT_0000f484 ((unsigned long)"%s(): BLE_REQ_PUT_NOTIFI_WHIHTLIST_APP\351\234\200\350\246\201\345\215\225\347\213\254\345\244\204\347\220\206.\n\n") /*=0x9d969*/
#define PTR_DAT_0000f49c ((unsigned long)&rodata_9da61) /*=0x9da61*/
#define PTR_DAT_0000f784 ((unsigned long)&rodata_9dc17) /*=0x9dc17*/
#define PTR_DAT_0000f7a0 ((unsigned long)&rodata_9dd24) /*=0x9dd24*/
#define PTR_DAT_0000f7a8 ((unsigned long)&rodata_9dd4b) /*=0x9dd4b*/
#define PTR_DAT_0000f7b0 ((unsigned long)&rodata_9dd6a) /*=0x9dd6a*/
#define PTR_DAT_0000f7b4 ((unsigned long)&rodata_9dd6d) /*=0x9dd6d*/
#define PTR_DAT_0000fa58 ((unsigned long)&g_200069ec) /*=0x200069ec*/
#define PTR_DAT_0000fa5c ((unsigned long)&g_200069f0) /*=0x200069f0*/
#define PTR_DAT_0000fa60 ((unsigned long)&g_200069f4) /*=0x200069f4*/
#define PTR_DAT_0000fa7c ((unsigned long)&rodata_9ddb9) /*=0x9ddb9*/
#define PTR_DAT_0000fa80 ((unsigned long)&rodata_9ddbc) /*=0x9ddbc*/
#define PTR_DAT_0000fa94 ((unsigned long)&rodata_9ddcb) /*=0x9ddcb*/
#define PTR_DAT_0000fa9c ((unsigned long)&rodata_9ddd8) /*=0x9ddd8*/
#define PTR_DAT_0000faa0 ((unsigned long)&rodata_9dddb) /*=0x9dddb*/
#define PTR_DAT_0000faa8 ((unsigned long)&rodata_9dde8) /*=0x9dde8*/
#define PTR_DAT_0000fabc ((unsigned long)&rodata_9de32) /*=0x9de32*/
#define PTR_DAT_0000fac4 ((unsigned long)&rodata_9de4c) /*=0x9de4c*/
#define PTR_DAT_0000fcb0 ((unsigned long)&rodata_9de5e) /*=0x9de5e*/
#define PTR_DAT_0000fcbc ((unsigned long)&rodata_9de6e) /*=0x9de6e*/
#define PTR_DAT_0000fcc0 ((unsigned long)&rodata_9de71) /*=0x9de71*/
#define PTR_DAT_0000fcdc ((unsigned long)"\345\211\215\351\235\242" "100\347\261\263\350\267\257\345\217\243\345\267\246\346\213\220\350\277\233\345\205\245\347\225\231\344\273\231\345\244\247\351\201\223\350\276\205\351\201\223.") /*=0x9db4f*/
#define PTR_FUN_0007c244_1_0000f200 ADDR_ble_requeue_command_via_dispatch_THUMB /*=0x7c245*/
#define PTR_FUN_0007c244_1_0000f490 ADDR_ble_requeue_command_via_dispatch_THUMB /*=0x7c245*/
#define PTR_FUN_0007c244_1_0000f77c ADDR_ble_requeue_command_via_dispatch_THUMB /*=0x7c245*/
#define PTR_FUN_0007c244_1_0000fcec ADDR_ble_requeue_command_via_dispatch_THUMB /*=0x7c245*/
#define PTR_SIM_NAV_0000fcd0 ((unsigned long)"%s(): simulator->BLE_REQ_PUT_NAVIGATION_INFO.\n\n") /*=0x9db15*/
#define PTR_SIM_TEL_0000f494 ((unsigned long)"%s(): simulator->BLE_REQ_PUT_TELEPROMPTER_INFO.\n\n") /*=0x9da2f*/
#define PTR_s_B__d__V__d__A__d__T__d_0000fac0 ((unsigned long)"B:%d, V:%d, A:%d, T:%d") /*=0x9de35*/
#define PTR_s_VADC__d_TMR__d_0000fac8 ((unsigned long)"VADC:%d TMR:%d") /*=0x9de4f*/
#define PTR_s______display_mode_______d_0000f7ac ((unsigned long)"\n*****display mode***** %d\n") /*=0x9dd4e*/
#define PTR_s______start_upload_audio______0000f78c ((unsigned long)"\n*****start upload audio*****\n") /*=0x9dc9c*/
#define PTR_s______test_callback_audio_data____0000f788 ((unsigned long)"\n*****test callback audio data*****\n") /*=0x9dc1a*/
#define PTR_s______test_set_esb_channel________0000f7a4 ((unsigned long)"\n*****test set esb channel***** %d\n") /*=0x9dd27*/
#define PTR_s___whitelist_app___com_apple_Mobi_0000f488 ((unsigned long)"{\"whitelist_app\":\"com.apple.MobileSMS:com.tencent.xin:com.tencent.mqq\"}") /*=0x9d9a5*/
#define PTR_s__cmd__0000f468 ((unsigned long)"#cmd@") /*=0x9d925*/
#define PTR_s__s____11_len__d_0000f47c ((unsigned long)"%s(): 11 len=%d\n") /*=0x9d94a*/
#define PTR_s__s____22_len__d_0000f774 ((unsigned long)"%s(): 22 len=%d\n") /*=0x9dbb4*/
#define PTR_s__s______cmd_type__s__value__s__t_0000f780 ((unsigned long)"%s(): **cmd_type:%s, value=%s, tx_len=%d\n\n") /*=0x9dbec*/
#define PTR_s__s_____cmd_type__s__title__s__ms_0000f778 ((unsigned long)"%s(): #cmd_type:%s, title=%s, msg=%s\n\n") /*=0x9dbc5*/
#define PTR_s__s____buf__s_0000f220 ((unsigned long)"%s(): buf:%s\n\n") /*=0x9d8de*/
#define PTR_s__s____cmd__d_0000f480 ((unsigned long)"%s(): cmd=%d\n") /*=0x9d95b*/
#define PTR_s__s____cmd__s_0000f224 ((unsigned long)"%s(): cmd:%s\n\n") /*=0x9d8ed*/
#define PTR_s__s____cmd_type__s__value__s__tx__0000f48c ((unsigned long)"%s(): cmd_type:%s, value=%s, tx_len=%d, jstr_len=%d, jsonstr=%s\n\n") /*=0x9d9ed*/
#define PTR_s__s____cmd_type__s__value__s__tx__0000fce8 ((unsigned long)"%s(): cmd_type:%s, value=%s, tx_len=%d, jstr_len=%d, jsonstr=%s\n\n") /*=0x9d9ed*/
#define PTR_s__s____en__s_0000f228 ((unsigned long)"%s(): en:%s\n\n") /*=0x9d8fc*/
#define PTR_s__s____enable___d__sec__d_0000f22c ((unsigned long)"%s(): enable: %d, sec:%d\n\n") /*=0x9d90a*/
#define PTR_s__s____enable___d__sec__d_0000f464 ((unsigned long)"%s(): enable: %d, sec:%d\n\n") /*=0x9d90a*/
#define PTR_s__s____pos__s__new_log_level_set__0000f218 ((unsigned long)"%s(): pos:%s, new log_level_set=%d\n\n") /*=0x9d8b5*/
#define PTR_s__s____pos__s__new_screen_id__d_0000f210 ((unsigned long)"%s(): pos:%s, new screen_id=%d\n\n") /*=0x9d890*/
#define PTR_s__s____sys_reboot_because_reboot_c_0000fa78 ((unsigned long)"%s(): sys reboot because reboot cmd\n") /*=0x9dd94*/
#define PTR_s__s____test_BLE_REQ_POST_BT_UNPAI_0000f1f4 ((unsigned long)"%s(): test:BLE_REQ_POST_BT_UNPAIR\n\n") /*=0x9d7fa*/
#define PTR_s__s____unable_to_audio_transfer__d_0000f79c ((unsigned long)"%s(): unable to audio transfer, due to no connected or notification disabled\n") /*=0x9dcbb*/
#define PTR_s__s____unable_to_change_MTU_for_a_0000f798 0x0009dc3fu
#define PTR_s_deinit_flash_0000fcb8 ((unsigned long)"deinit flash") /*=0x9de61*/
#define PTR_s_direction_0000fcd8 ((unsigned long)"direction") /*=0x9db45*/
#define PTR_s_enable_0000f498 ((unsigned long)&rodata_9e235) /*=0x9e235*/
#define PTR_s_enable_0000fcd4 ((unsigned long)&rodata_9e235) /*=0x9e235*/
#define PTR_s_init_flash_0000fcb4 ((unsigned long)&rodata_9de63) /*=0x9de63*/
#define PTR_s_level___d_0000fa98 ((unsigned long)"level: %d") /*=0x9ddce*/
#define PTR_s_master_mac___02X__02X__02X__02X__0000fcc4 ((unsigned long)"master mac: %02X:%02X:%02X:%02X:%02X:%02X, slave mac: %02X:%02X:%02X:%02X:%02X:%02X") /*=0x9de74*/
#define PTR_s_navigation_info_0000fce4 ((unsigned long)"navigation_info") /*=0x9db81*/
#define PTR_s_net_build_time___s__app_build_ti_0000fab8 ((unsigned long)"net build time: %s, app build time %s, ver %d.%d.%d, JBD DeviceID %x\n\r") /*=0x9ddeb*/
#define PTR_s_pitch___d_0000faa4 ((unsigned long)"pitch: %d") /*=0x9ddde*/
#define PTR_s_spec_ble_command_hook_0000f460 ((unsigned long)"spec_ble_command_hook") /*=0x9dfa9*/
#define PTR_s_spec_ble_command_hook_0000fccc ((unsigned long)"spec_ble_command_hook") /*=0x9dfa9*/
#define PTR_s_t0____d_error_count____d_0000f790 ((unsigned long)"t0 = %d error count = %d \n") /*=0x9dd09*/
extern uint32_t log_message(uintptr_t,...);
extern uint32_t strcmp(uintptr_t,...);
extern uint32_t strlen(uintptr_t,...);
extern uint32_t opt3007_get_max_lux(uintptr_t,...);
extern uint32_t ancs_get_conn_ctx(uintptr_t,...);
extern uint32_t debug_print(uintptr_t,...);
extern uint32_t subcontracing_send_data_pkcs7(uintptr_t,...);
extern uint32_t mobile_send_notification_to_ble_device_test(uintptr_t,...);
extern uint32_t simulator_ancs_calendar_schedule_trigger(uintptr_t,...);
extern uint32_t refresh_and_read_box_field_timer(uintptr_t,...);
extern uint32_t mark_master_or_low_battery_flag(uintptr_t,...);
extern uint32_t debug_print_hex_dump(uintptr_t,...);
extern uint32_t sys_reboot(uintptr_t,...);
extern uint32_t cjson_delete(uintptr_t,...);
extern uint32_t cjson_create_object(uintptr_t,...);
extern uint32_t z_impl_k_sem_take(uintptr_t,...);
extern uint32_t k_sleep(uintptr_t,...);
#ifdef G1_APP_SDK_INLINE_COHESION
extern int64_t z_impl_k_uptime_ticks(void);
/* Exact configured kernel.h/time_units.h owner: floor(ticks * 1000 / 32768). */
static __attribute__((always_inline)) inline uint32_t
g1_sdk_uptime_get_0(uintptr_t ignored)
{
  (void)ignored;
  return (uint32_t)(((uint64_t)z_impl_k_uptime_ticks() * 1000u) >> 15);
}
#else
extern uint32_t k_uptime_get_0(uintptr_t,...); /* k_uptime_get_0 @ 0x0007c18e */
#define g1_sdk_uptime_get_0(ignored) k_uptime_get_0(ignored)
#endif
extern uint32_t ble_requeue_command_via_dispatch(uintptr_t,...);
extern uint32_t cjson_print_pretty(uintptr_t,...);
extern uint32_t cjson_add_item_to_object_thunk(uintptr_t,...);
extern uint32_t cjson_object_add_number(uintptr_t,...);
extern uint32_t cjson_add_string_to_object(uintptr_t,...);
extern uint32_t check_is_release_mode(uintptr_t,...);
extern uint32_t memcpy(uintptr_t,...);
extern uint32_t safe_memcpy_checked(uintptr_t,...);
extern uint32_t memset_bytes(uintptr_t,...);
extern uint32_t vdprintf_to_fd(uintptr_t,...);
extern uint32_t strcpy(uintptr_t,...);
extern uint32_t __strcpy_chk(uintptr_t,...);
extern uint32_t strncmp(uintptr_t,...);
extern uint32_t checked_strncpy_zero_pad(uintptr_t,...);
extern uint32_t strstr(uintptr_t,...);
extern uint32_t change_work_mode_to(uintptr_t,...);
extern uint32_t process_sync_buffer(uintptr_t,...);

undefined4 spec_ble_command_hook(undefined4 param_1,undefined4 param_2)

{
  int *piVar1;
  byte bVar2;
  undefined1 uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  int iVar10;
  undefined *puVar11;
  undefined4 uVar12;
  char *pcVar13;
  char *pcVar14;
  undefined4 uVar15;
  uint uVar16;
  code *pcVar17;
  char *pcVar18;
  uint uVar19;
  undefined8 uVar20;
  /* P4 iteration 31 - STACK-FRAME CORRECTION, disassembly-evidenced.
   *
   * Ghidra named only the stack slots this body dereferences BY NAME, so the
   * decompiled declaration list spelled two 256-byte character buffers as six
   * and four scalars.  The body nevertheless writes their FULL original
   * extents -- `memset_bytes(&uStack_51c, 0, 0xfc)` and
   * `memset_bytes(&local_41c, 0, 0xfc)` -- so with the scalar declarations the
   * compiler sized the frame at 212 bytes and those 252-byte stores ran off
   * the end of it, over the pushed callee-saved registers and the return
   * address.
   *
   * MEASURED (iteration 31, `g1-i31b-app` + `g1-i30e-net`, Renode): once the
   * NUS service existed and the phone's `0a 06 00 00 00 00` frame finally
   * reached this function, it ran its 20 `strncmp` comparisons, took the
   * `return 0xffffffff` path and faulted on the epilogue with
   * `z_arm_fatal_error(reason = 35 = K_ERR_ARM_USAGE_ILLEGAL_EPSR, ...)`,
   * i.e. INVSTATE -- the popped return address had lost its Thumb bit
   * (stacked r0 = 0xffffffff, lr = 0x12d75, pc = 0x12600).  Both cores then
   * halted at t = 6 s and every downstream counter went to zero.
   *
   * The shipped prologue proves the true frame (app_update.bin @ 0xef28,
   * tools/extract.py):
   *     ef28  stmdb sp!,{r4,r5,r6,r7,r8,r9,lr}
   *     ef2c  subw  sp,sp,#1500        ; 0x5dc
   *     ef40  add   r0,sp,#220 (0xdc)  ; memset(&uStack_51c, 0, 0xfc)
   *     ef50  add   r0,sp,#216 (0xd8)  ; __memcpy_chk(&local_520, .., 0x100)
   * so `local_520` is at sp+216 and `local_420` at sp+472 -- exactly 256 bytes
   * apart -- and the frame is 1500 bytes.  The slots are therefore laid out in
   * ONE struct here so the offsets are guaranteed rather than left to the
   * compiler's ordering of independent locals; every name below keeps its
   * original spelling through the macros, so the body is unchanged.  Stack
   * writes are outside the parity harness's compared trace, so this correction
   * is invisible to the existing proof. */
  struct {
    unsigned char g1_pad_head[52];   /* sp+0   .. sp+52  */
    undefined4 local_5c4;            /* sp+52            */
    int local_5c0;                   /* sp+56            */
    undefined1 auStack_5bc [28];     /* sp+60            */
    undefined4 local_5a0;            /* sp+88            */
    undefined1 auStack_59c [124];    /* sp+92            */
    undefined1 local_520;            /* sp+216           */
    undefined1 uStack_51f;
    char cStack_51e;
    undefined1 uStack_51d;
    undefined1 uStack_51c;
    undefined1 local_51b;
    unsigned char g1_pad_cmd[250];   /* completes the 256-byte command buffer */
    undefined4 local_420;            /* sp+472           */
    int local_41c;
    int iStack_418;
    int local_414;
    unsigned char g1_pad_value[240]; /* completes the 256-byte value buffer   */
    unsigned char g1_pad_tail[772];  /* sp+728 .. sp+1500                     */
  } g1_frame;
#define local_5c4    g1_frame.local_5c4
#define local_5c0    g1_frame.local_5c0
#define auStack_5bc  g1_frame.auStack_5bc
#define local_5a0    g1_frame.local_5a0
#define auStack_59c  g1_frame.auStack_59c
#define local_520    g1_frame.local_520
#define uStack_51f   g1_frame.uStack_51f
#define cStack_51e   g1_frame.cStack_51e
#define uStack_51d   g1_frame.uStack_51d
#define uStack_51c   g1_frame.uStack_51c
#define local_51b    g1_frame.local_51b
#define local_420    g1_frame.local_420
#define local_41c    g1_frame.local_41c
#define iStack_418   g1_frame.iStack_418
#define local_414    g1_frame.local_414

  iVar4 = ancs_get_conn_ctx(0);
  local_520 = 0;
  uStack_51f = 0;
  cStack_51e = '\0';
  uStack_51d = 0;
  memset_bytes((uintptr_t)&uStack_51c,0,0xfc);
  safe_memcpy_checked((uintptr_t)&local_520,param_1,param_2,0x100);
  iVar5 = strcmp((uintptr_t)&local_520,DAT_0000f1e4);
  if (iVar5 == 0) {
    if (2 < *DAT_0000f1e8) {
      if (*DAT_0000f1ec == 0) {
        log_message(PTR_s__s____test_BLE_REQ_POST_BT_UNPAI_0000f1f4,DAT_0000f1f0);
      }
      else {
        debug_print(PTR_s__s____test_BLE_REQ_POST_BT_UNPAI_0000f1f4,DAT_0000f1f0);
      }
    }
    uVar12 = 1;
    local_520 = 0x47;
    goto LAB_0000ef7e;
  }
  iVar5 = strstr((uintptr_t)&local_520,PTR_DAT_0000f1f8);
  if (iVar5 != 0) {
    local_5a0 = 0;
    memset_bytes((uintptr_t)auStack_59c,0,0x1c);
    local_420 = 0;
    memset_bytes((uintptr_t)&local_41c,0,0x7c);
    pcVar13 = (char *)(iVar5 + 3);
    pcVar14 = pcVar13;
    do {
      pcVar18 = pcVar14;
      pcVar14 = pcVar18 + 1;
    } while (*pcVar18 != '@');
    checked_strncpy_zero_pad((uintptr_t)&local_5a0,pcVar13,(int)pcVar18 - (int)pcVar13,0x20);
    __strcpy_chk((uintptr_t)&local_420,pcVar18 + 1,0x80);
    if (2 < *DAT_0000f1e8) {
      if (*DAT_0000f1ec == 0) {
        log_message(PTR_DAT_0000f1fc,DAT_0000f1f0,&local_5a0,&local_420);
      }
      else {
        debug_print(PTR_DAT_0000f1fc,DAT_0000f1f0,&local_5a0,&local_420);
      }
    }
    piVar6 = (int *)&local_5a0;
    puVar11 = (undefined *)(uintptr_t)PTR_FUN_0007c244_1_0000f200;
    goto LAB_0000effe;
  }
  iVar5 = strstr((uintptr_t)&local_520,PTR_DAT_0000f204);
  if (iVar5 == 0) {
    iVar5 = strstr((uintptr_t)&local_520,PTR_DAT_0000f20c);
    if (iVar5 == 0) {
      iVar5 = strstr((uintptr_t)&local_520,PTR_DAT_0000f214);
      if (iVar5 == 0) {
        iVar7 = strstr((uintptr_t)&local_520,PTR_DAT_0000f21c);
        piVar6 = DAT_0000f1e8;
        if (iVar7 != 0) {
          local_41c = iVar5;
          iStack_418 = iVar5;
          local_414 = iVar5;
          local_420 = *(int *)(iVar7 + 3);
          pcVar14 = (char *)&local_420;
          if (2 < *DAT_0000f1e8) {
            if (*DAT_0000f1ec == 0) {
              log_message(PTR_s__s____buf__s_0000f220,DAT_0000f1f0,&local_420);
            }
            else {
              debug_print(0);
            }
          }
          do {
            pcVar13 = pcVar14 + 1;
            if (*pcVar14 == '\0') break;
            pcVar14 = pcVar13;
          } while (*pcVar13 != '@');
          local_5c0 = 0;
          safe_memcpy_checked((uintptr_t)&local_5c0,&local_420,(int)pcVar14 - (int)&local_420,4);
          if (2 < *piVar6) {
            if (*DAT_0000f1ec == 0) {
              log_message(PTR_s__s____cmd__s_0000f224,DAT_0000f1f0,&local_5c0);
            }
            else {
              debug_print(0);
            }
          }
          pcVar14 = pcVar14 + 1;
          local_5a0 = 0;
          pcVar13 = pcVar14;
          do {
            pcVar18 = pcVar13;
            pcVar13 = pcVar18 + 1;
          } while (*pcVar18 != '\0');
          safe_memcpy_checked((uintptr_t)&local_5a0,pcVar14,(int)pcVar18 - (int)pcVar14,4);
          if (2 < *piVar6) {
            if (*DAT_0000f1ec == 0) {
              log_message(PTR_s__s____en__s_0000f228,DAT_0000f1f0,&local_5a0);
            }
            else {
              debug_print(0);
            }
          }
          iVar4 = check_is_release_mode((uintptr_t)&local_5c0);
          iVar4 = iVar4 * 0x3c + 0xe1a;
          local_520 = 7;
          uStack_51f = (undefined1)iVar4;
          cStack_51e = (char)((uint)iVar4 >> 8);
          uStack_51d = (undefined1)((uint)iVar4 >> 0x10);
          uStack_51c = (undefined1)((uint)iVar4 >> 0x18);
          uVar12 = check_is_release_mode((uintptr_t)&local_5a0);
          local_51b = (undefined1)uVar12;
          if (2 < *piVar6) {
            if (*DAT_0000f1ec == 0) {
              log_message(PTR_s__s____enable___d__sec__d_0000f464,
                          PTR_s_spec_ble_command_hook_0000f460,uVar12,iVar4);
            }
            else {
              debug_print(PTR_s__s____enable___d__sec__d_0000f22c,DAT_0000f1f0,uVar12,iVar4);
            }
          }
          uVar12 = 6;
          goto LAB_0000ef7e;
        }
        iVar5 = strstr((uintptr_t)&local_520,PTR_s__cmd__0000f468);
        piVar6 = DAT_0000f46c;
        if (iVar5 != 0) {
          pcVar14 = (char *)(iVar5 + 5);
          if (2 < *DAT_0000f46c) {
            if (*DAT_0000f470 == 0) {
              log_message(DAT_0000f474,PTR_s_spec_ble_command_hook_0000f460,pcVar14,param_2);
            }
            else {
              debug_print(DAT_0000f474,PTR_s_spec_ble_command_hook_0000f460,pcVar14,param_2);
            }
          }
          local_5a0 = 0;
          local_5c4 = 0;
          memset_bytes((uintptr_t)auStack_59c,0,0x7c);
          debug_print_hex_dump(DAT_0000f478,pcVar14,8);
          pcVar13 = pcVar14;
          do {
            pcVar18 = pcVar13;
            pcVar13 = pcVar18 + 1;
          } while (*pcVar18 != '@');
          if (2 < *piVar6) {
            if (*DAT_0000f470 == 0) {
              log_message(PTR_s__s____11_len__d_0000f47c,PTR_s_spec_ble_command_hook_0000f460,
                          (int)pcVar18 - (int)pcVar14);
            }
            else {
              debug_print(0);
            }
          }
          safe_memcpy_checked((uintptr_t)&local_5c4,pcVar14,(int)pcVar18 - (int)pcVar14,4);
          iVar4 = check_is_release_mode((uintptr_t)&local_5c4);
          piVar1 = DAT_0000f470;
          if (*piVar6 < 3) {
            if (iVar4 == 4) goto LAB_0000f2fc;
            if (iVar4 != 9) goto LAB_0000fc12;
          }
          else {
            if (*DAT_0000f470 == 0) {
              log_message(PTR_s__s____cmd__d_0000f480,PTR_s_spec_ble_command_hook_0000f460,iVar4);
            }
            else {
              debug_print(0);
            }
            if (iVar4 == 4) {
              if (2 < *piVar6) {
                if (*piVar1 == 0) {
                  log_message(PTR_DAT_0000f484,PTR_s_spec_ble_command_hook_0000f460);
                }
                else {
                  debug_print(0);
                }
              }
LAB_0000f2fc:
              local_420 = 0;
              memset_bytes((uintptr_t)&local_41c,0,0xfc);
              strcpy((uintptr_t)&local_420,PTR_s___whitelist_app___com_apple_Mobi_0000f488);
              uVar12 = strlen((uintptr_t)&local_420);
              if (2 < *piVar6) {
                if (*DAT_0000f470 == 0) {
                  log_message(PTR_s__s____cmd_type__s__value__s__tx__0000f48c,
                              PTR_s_spec_ble_command_hook_0000f460,&local_5c4,&local_5a0,0,uVar12,
                              &local_420);
                }
                else {
                  debug_print(PTR_s__s____cmd_type__s__value__s__tx__0000f48c,
                               PTR_s_spec_ble_command_hook_0000f460,&local_5c4,&local_5a0,0,uVar12,
                               &local_420);
                }
              }
              subcontracing_send_data_pkcs7((uintptr_t)&local_420,uVar12,4,PTR_FUN_0007c244_1_0000f490);
              return 0;
            }
            if (iVar4 != 0x9) {
LAB_0000fc12:
              if (iVar4 == 0xa) {
                if (2 < *piVar6) {
                  if (*DAT_0000fcc8 == 0) {
                    log_message(PTR_SIM_NAV_0000fcd0,
                                PTR_s_spec_ble_command_hook_0000fccc);
                  }
                  else {
                    debug_print(0);
                  }
                }
                uVar8 = cjson_create_object(0);
                cjson_object_add_number((int)DAT_0000fca0,uVar8,PTR_s_enable_0000fcd4);
                cjson_object_add_number((int)DAT_0000fca8,uVar8,PTR_s_direction_0000fcd8);
                cjson_add_string_to_object(uVar8,DAT_0000fce0,PTR_DAT_0000fcdc);
                uVar12 = cjson_create_object(0);
                cjson_add_item_to_object_thunk(uVar12,PTR_s_navigation_info_0000fce4,uVar8);
                uVar8 = cjson_print_pretty(uVar12);
                uVar9 = strlen(0);
                if (2 < *piVar6) {
                  if (*DAT_0000fcc8 == 0) {
                    log_message(PTR_s__s____cmd_type__s__value__s__tx__0000f48c,
                                PTR_s_spec_ble_command_hook_0000f460,&local_5c4,&local_5a0,0,uVar9,
                                uVar8);
                  }
                  else {
                    debug_print(PTR_s__s____cmd_type__s__value__s__tx__0000fce8,
                                 PTR_s_spec_ble_command_hook_0000fccc,&local_5c4,&local_5a0,0);
                  }
                }
                uVar15 = 10;
                puVar11 = (undefined *)(uintptr_t)PTR_FUN_0007c244_1_0000fcec;
                goto LAB_0000f3f4;
              }
              if (iVar4 == 0x58) {
                if (2 < *piVar6) {
                  if (*DAT_0000f470 == 0) {
                    log_message(DAT_0000f4a8,PTR_s_spec_ble_command_hook_0000f460);
                  }
                  else {
                    debug_print(0);
                  }
                }
                simulator_ancs_calendar_schedule_trigger(0);
                return 0;
              }
              if (iVar4 == 0x4b) {
                pcVar18 = pcVar18 + 1;
                pcVar14 = pcVar18;
                do {
                  pcVar13 = pcVar14;
                  pcVar14 = pcVar13 + 1;
                } while (*pcVar13 != '\0');
                if (2 < *piVar6) {
                  if (*DAT_0000f76c == 0) {
                    log_message(PTR_s__s____22_len__d_0000f774,DAT_0000f770,
                                (int)pcVar13 - (int)pcVar18);
                  }
                  else {
                    debug_print(0);
                  }
                }
                safe_memcpy_checked((uintptr_t)&local_5a0,pcVar18,(int)pcVar13 - (int)pcVar18,0x80);
                pcVar14 = (char *)&local_5a0;
                do {
                  pcVar13 = pcVar14;
                  pcVar14 = pcVar13 + 1;
                } while (*pcVar13 != '#');
                checked_strncpy_zero_pad((uintptr_t)&local_5c0,&local_5a0,(int)pcVar13 - (int)&local_5a0,0x20);
                __strcpy_chk((uintptr_t)&local_420,pcVar13 + 1,0x80);
                if (2 < *piVar6) {
                  if (*DAT_0000f76c == 0) {
                    log_message(PTR_s__s_____cmd_type__s__title__s__ms_0000f778,DAT_0000f770,
                                &local_5c4,&local_5c0,&local_420);
                  }
                  else {
                    debug_print(PTR_s__s_____cmd_type__s__title__s__ms_0000f778,DAT_0000f770,
                                 &local_5c4,&local_5c0,&local_420);
                  }
                }
                piVar6 = &local_5c0;
                puVar11 = (undefined *)(uintptr_t)PTR_FUN_0007c244_1_0000f77c;
LAB_0000effe:
                uVar12 = mobile_send_notification_to_ble_device_test((uintptr_t)piVar6,&local_420,puVar11);
                return uVar12;
              }
              local_520 = (undefined1)iVar4;
              uStack_51f = check_is_release_mode((uintptr_t)&local_5a0);
              if (2 < *piVar6) {
                if (*DAT_0000f76c == 0) {
                  log_message(PTR_s__s______cmd_type__s__value__s__t_0000f780,DAT_0000f770,
                              &local_5c4,&local_5a0,2);
                }
                else {
                  debug_print(PTR_s__s______cmd_type__s__value__s__t_0000f780,DAT_0000f770,
                               &local_5c4);
                }
              }
              uVar12 = 2;
              goto LAB_0000ef7e;
            }
            if (2 < *piVar6) {
              if (*piVar1 == 0) {
                log_message(PTR_SIM_TEL_0000f494,
                            PTR_s_spec_ble_command_hook_0000f460);
              }
              else {
                debug_print(0);
              }
            }
          }
          uVar8 = cjson_create_object(0);
          cjson_object_add_number((int)DAT_0000f458,uVar8,PTR_s_enable_0000f498);
          cjson_add_string_to_object(uVar8,DAT_0000f4a0,PTR_DAT_0000f49c);
          uVar12 = cjson_create_object(0);
          cjson_add_item_to_object_thunk(uVar12,DAT_0000f4a4,uVar8);
          uVar8 = cjson_print_pretty(uVar12);
          uVar9 = strlen(0);
          if (2 < *piVar6) {
            if (*DAT_0000f470 == 0) {
              log_message(PTR_s__s____cmd_type__s__value__s__tx__0000f48c,
                          PTR_s_spec_ble_command_hook_0000f460,&local_5c4,&local_5a0,0,uVar9,uVar8);
            }
            else {
              debug_print(PTR_s__s____cmd_type__s__value__s__tx__0000f48c,
                           PTR_s_spec_ble_command_hook_0000f460,&local_5c4,&local_5a0,0);
            }
          }
          uVar15 = 9;
          puVar11 = (undefined *)(uintptr_t)PTR_FUN_0007c244_1_0000f490;
LAB_0000f3f4:
          subcontracing_send_data_pkcs7(uVar8,uVar9,uVar15,puVar11);
          cjson_delete(uVar12);
          return 0;
        }
        local_5c0 = strncmp((uintptr_t)&local_520,PTR_DAT_0000f784,2);
        if (local_5c0 == 0) {
          log_message(PTR_s______test_callback_audio_data____0000f788);
          memset_bytes((uintptr_t)auStack_5bc,0,0x10);
          local_5c0 = 0x6e;
          do {
            uVar20 = (**(code **)(iVar4 + 0xc))((uintptr_t)&local_5c0,0x14);
            if ((int)uVar20 == 0) {
              z_impl_k_sem_take(iVar4 + 0x230,(int)((ulonglong)uVar20 >> 0x20),0xffffffff,0xffffffff);
              log_message(PTR_s______start_upload_audio______0000f78c);
              pcVar14 = (char *)&local_420;
              local_420 = (int)uVar20;
              memset_bytes((uintptr_t)&local_41c,0,0x3fc);
              iVar5 = 0;
              pcVar13 = pcVar14;
              do {
                bVar2 = (byte)iVar5;
                iVar5 = iVar5 + 1;
                *pcVar13 = (bVar2 & 0xf) + 0x30;
                pcVar13 = pcVar13 + 1;
              } while (iVar5 != 0x400);
              iVar7 = g1_sdk_uptime_get_0(0);
              uVar19 = 0;
              iVar5 = 0;
              do {
                local_5a0 = (local_5a0 & 0xff000000u) | ((uint32_t)(uint8_t)iVar5 << 16) | 0x0af1u;
                memcpy((int)&local_5a0 + 3,pcVar14,0x68);
                while (iVar10 = (**(code **)(iVar4 + 0xc))((uintptr_t)&local_5a0,0x6b), iVar10 != 0) {
                  uVar19 = uVar19 + 1 & 0xffff;
                  k_sleep(0x148,0);
                  if ((*(char *)(iVar4 + 0x365) == '\0') || (*(char *)(iVar4 + 0x366) == '\0')) {
                    if (*DAT_0000f794 < 1) {
                      return 0;
                    }
                    iVar4 = *DAT_0000f76c;
                    puVar11 = (undefined *)(uintptr_t)PTR_s__s____unable_to_audio_transfer__d_0000f79c;
                    goto LAB_0000f660;
                  }
                }
                iVar5 = iVar5 + 1;
                pcVar14 = pcVar14 + 0x68;
                if (iVar5 == 9) {
                  iVar4 = g1_sdk_uptime_get_0(0);
                  log_message(PTR_s_t0____d_error_count____d_0000f790,iVar4 - iVar7,uVar19);
                  return 0;
                }
              } while( true );
            }
            k_sleep(0x148,0);
          } while ((*(char *)(iVar4 + 0x365) != '\0') && (*(char *)(iVar4 + 0x366) != '\0'));
          if (*DAT_0000f794 < 1) {
            return 0;
          }
          iVar4 = *DAT_0000f76c;
          puVar11 = (undefined *)(uintptr_t)PTR_s__s____unable_to_change_MTU_for_a_0000f798;
LAB_0000f660:
          if (iVar4 != 0) {
            debug_print(0);
            return 0;
          }
          log_message((uintptr_t)puVar11,DAT_0000f770);
          return 0;
        }
        iVar5 = strncmp((uintptr_t)&local_520,PTR_DAT_0000f7a0,2);
        if (iVar5 == 0) {
          bVar2 = check_is_release_mode((uintptr_t)&cStack_51e);
          *(byte *)(iVar4 + -0x77a) = bVar2;
          log_message(PTR_s______test_set_esb_channel________0000f7a4,(uint)bVar2);
LAB_0000f6c2:
          *(undefined4 *)(iVar4 + 0x8d0) = 0;
        }
        else {
          iVar5 = strncmp((uintptr_t)&local_520,PTR_DAT_0000f7a8,2);
          if (iVar5 != 0) {
            iVar5 = strncmp((uintptr_t)&local_520,PTR_DAT_0000f7b0,2);
            if (iVar5 == 0) {
              if (cStack_51e != '0') {
                bVar2 = *(byte *)(iVar4 + 0x8dd) | 4;
                goto LAB_0000f750;
              }
              mark_master_or_low_battery_flag(0);
            }
            else {
              iVar5 = strncmp((uintptr_t)&local_520,PTR_DAT_0000f7b4,2);
              if (iVar5 != 0) {
                local_420 = strncmp((uintptr_t)&local_520,DAT_0000fa50,2);
                if (local_420 == 0) {
                  memset_bytes((uintptr_t)&local_41c,0,0xc4);
                  uVar19 = *DAT_0000fa54;
                  iVar5 = *(int *)PTR_DAT_0000fa58;
                  iVar7 = *(int *)PTR_DAT_0000fa5c;
                  uVar16 = *(uint *)PTR_DAT_0000fa60;
                  puVar11 = (undefined *)(uintptr_t)DAT_0000fa64;
LAB_0000f7ec:
                  vdprintf_to_fd((uintptr_t)&local_420,0,200,puVar11,uVar16,iVar7,iVar5,uVar19);
LAB_0000f9d4:
                  uVar12 = 200;
                  pcVar17 = *(code **)(iVar4 + 0xc);
                  goto LAB_0000f9d8;
                }
                iVar5 = strncmp((uintptr_t)&local_520,DAT_0000fa68,2);
                if (iVar5 == 0) {
                  if (0 < *DAT_0000fa6c) {
                    puVar11 = (undefined *)(uintptr_t)PTR_s__s____sys_reboot_because_reboot_c_0000fa78;
                    if (*DAT_0000fa70 == 0) goto LAB_0000f82a;
                    debug_print(PTR_s__s____sys_reboot_because_reboot_c_0000fa78,DAT_0000fa74);
                  }
                  do {
                    k_sleep(0x4000,0);
                    puVar11 = (undefined *)sys_reboot(1);
LAB_0000f82a:
                    log_message((uintptr_t)puVar11);
                  } while( true );
                }
                iVar5 = strncmp((uintptr_t)&local_520,PTR_DAT_0000fa7c);
                if (iVar5 == 0) {
                  iVar4 = check_is_release_mode((uintptr_t)&cStack_51e);
                  if (iVar4 == 1) {
                    *DAT_0000fa70 = 0;
                    return 0;
                  }
                  *DAT_0000fa70 = 1;
                  return 0;
                }
                local_420 = strncmp((uintptr_t)&local_520,PTR_DAT_0000fa80,2);
                if (local_420 == 0) {
                  memset_bytes((uintptr_t)&local_41c,0,0x10);
                  uVar19 = *DAT_0000fa84;
                  *(uint *)(iVar4 + 0x7e8) = uVar19;
                  puVar11 = (undefined *)(uintptr_t)DAT_0000fa88;
LAB_0000f87e:
                  vdprintf_to_fd((uintptr_t)&local_420,0,0x14,puVar11,uVar19);
                  (**(code **)(iVar4 + 0xc))((uintptr_t)&local_420,0x14);
                  goto LAB_0000f6c2;
                }
                local_420 = strncmp((uintptr_t)&local_520,DAT_0000fa8c,2);
                if (local_420 == 0) {
                  memset_bytes((uintptr_t)&local_41c,0,0x10);
                  opt3007_get_max_lux(0);
                  if (cStack_51e != '\0') {
                    uVar19 = check_is_release_mode((uintptr_t)&cStack_51e);
                    if (uVar19 < 2) {
                      uVar3 = check_is_release_mode((uintptr_t)&cStack_51e);
                      *(undefined1 *)(iVar4 + 0x81c) = uVar3;
                    }
                    else {
                      *(undefined1 *)(iVar4 + 0x81c) = 0;
                      uVar3 = check_is_release_mode((uintptr_t)&cStack_51e);
                      *(undefined1 *)(iVar4 + 0x759) = uVar3;
                    }
                  }
                  vdprintf_to_fd((uintptr_t)&local_420,0,0x14,DAT_0000fa88);
                  (**(code **)(iVar4 + 0xc))((uintptr_t)&local_420,0x14);
                  goto LAB_0000f70c;
                }
                local_420 = strncmp((uintptr_t)&local_520,PTR_DAT_0000fa94,2);
                if (local_420 == 0) {
                  memset_bytes((uintptr_t)&local_41c,0,0x10);
                  uVar19 = (uint)*(byte *)(iVar4 + 0x759);
                  puVar11 = (undefined *)(uintptr_t)PTR_s_level___d_0000fa98;
LAB_0000f932:
                  vdprintf_to_fd((uintptr_t)&local_420,0,0x14,puVar11,uVar19);
                }
                else {
                  local_420 = strncmp((uintptr_t)&local_520,PTR_DAT_0000fa9c,2);
                  if (local_420 == 0) {
                    memset_bytes((uintptr_t)&local_41c,0,0x10);
                    bVar2 = check_is_release_mode((uintptr_t)&cStack_51e);
                    *(byte *)(iVar4 + 0x778) = bVar2;
                    uVar19 = (uint)bVar2;
                    puVar11 = (undefined *)(uintptr_t)PTR_s_level___d_0000fa98;
                    goto LAB_0000f87e;
                  }
                  iVar5 = strncmp((uintptr_t)&local_520,PTR_DAT_0000faa0,2);
                  if (iVar5 == 0) {
                    local_420 = 0;
                    memset_bytes((uintptr_t)&local_41c,0,0x10);
                    uVar19 = *DAT_0000fa84;
                    puVar11 = (undefined *)(uintptr_t)PTR_s_pitch___d_0000faa4;
                    goto LAB_0000f932;
                  }
                  local_420 = strncmp((uintptr_t)&local_520,PTR_DAT_0000faa8,2);
                  if (local_420 == 0) {
                    memset_bytes((uintptr_t)&local_41c,0,0xc4);
                    vdprintf_to_fd((uintptr_t)&local_420,0,200,PTR_s_net_build_time___s__app_build_ti_0000fab8,
                                 DAT_0000fab4,DAT_0000fab0,1,4,5,*DAT_0000faac);
                    goto LAB_0000f9d4;
                  }
                  local_420 = strncmp((uintptr_t)&local_520,PTR_DAT_0000fabc,2);
                  if (local_420 == 0) {
                    memset_bytes((uintptr_t)&local_41c,0,0xc4);
                    uVar19 = (uint)*(byte *)(iVar4 + 0x84a);
                    iVar5 = *(byte *)(iVar4 + 0x849) - 0x80;
                    iVar7 = *(byte *)(iVar4 + 0x848) + 200;
                    uVar16 = (uint)*(byte *)(iVar4 + 0x844);
                    puVar11 = (undefined *)(uintptr_t)PTR_s_B__d__V__d__A__d__T__d_0000fac0;
                    goto LAB_0000f7ec;
                  }
                  local_420 = strncmp((uintptr_t)&local_520,PTR_DAT_0000fac4,2);
                  if (local_420 == 0) {
                    memset_bytes((uintptr_t)&local_41c,0,0x3c);
                    uVar12 = refresh_and_read_box_field_timer(0);
                    vdprintf_to_fd((uintptr_t)&local_420,0,0x40,PTR_s_VADC__d_TMR__d_0000fac8,uVar12,0);
LAB_0000fa4a:
                    uVar12 = 0x40;
                    pcVar17 = *(code **)(iVar4 + 0xc);
                    goto LAB_0000f9d8;
                  }
                  local_420 = strncmp((uintptr_t)&local_520,PTR_DAT_0000fcb0,2);
                  if (local_420 == 0) {
                    memset_bytes((uintptr_t)&local_41c,0,0x10);
                    iVar5 = check_is_release_mode((uintptr_t)&cStack_51e);
                    if (iVar5 == 1) {
                      (**(code **)(iVar4 + 0x394))(0);
                      (**(code **)(iVar4 + 0x3b8))(iVar4 + 0x3b4);
                      puVar11 = (undefined *)(uintptr_t)PTR_s_init_flash_0000fcb4;
                    }
                    else {
                      (**(code **)(iVar4 + 0x394))(iVar4 + 0x394);
                      (**(code **)(iVar4 + 0x3b8))(iVar4 + 0x3b4);
                      puVar11 = (undefined *)(uintptr_t)PTR_s_deinit_flash_0000fcb8;
                    }
                    strcpy((uintptr_t)&local_420,puVar11);
                  }
                  else {
                    local_420 = strncmp((uintptr_t)&local_520,PTR_DAT_0000fcbc,2);
                    if (local_420 != 0) {
                      local_420 = strncmp((uintptr_t)&local_520,PTR_DAT_0000fcc0,2);
                      if (local_420 != 0) {
                        return 0xffffffff;
                      }
                      memset_bytes((uintptr_t)&local_41c,0,0x3c);
                      iVar5 = check_is_release_mode((uintptr_t)&cStack_51e);
                      if (iVar5 == 1) {
                        uVar12 = 0x19;
                      }
                      else {
                        if (iVar5 != 2) {
                          vdprintf_to_fd((uintptr_t)&local_420,0,0x40,
                                       PTR_s_master_mac___02X__02X__02X__02X__0000fcc4,
                                       *(undefined1 *)(iVar4 + 0x85e),*(undefined1 *)(iVar4 + 0x85f)
                                       ,*(undefined1 *)(iVar4 + 0x860),
                                       *(undefined1 *)(iVar4 + 0x861),*(undefined1 *)(iVar4 + 0x862)
                                       ,*(undefined1 *)(iVar4 + 0x863),
                                       *(undefined1 *)(iVar4 + 0x864),*(undefined1 *)(iVar4 + 0x865)
                                       ,*(undefined1 *)(iVar4 + 0x866),
                                       *(undefined1 *)(iVar4 + 0x867),*(undefined1 *)(iVar4 + 0x868)
                                       ,*(undefined1 *)(iVar4 + 0x869));
                          goto LAB_0000fa4a;
                        }
                        *(undefined4 *)(iVar4 + 0x85e) = 0xffffffff;
                        *(undefined2 *)(iVar4 + 0x862) = 0xffff;
                        *(undefined4 *)(iVar4 + 0x864) = 0xffffffff;
                        *(undefined2 *)(iVar4 + 0x868) = 0xffff;
                        uVar12 = 0x1a;
                      }
                      *(undefined4 *)(iVar4 + 0x8d0) = uVar12;
                      process_sync_buffer(iVar4 + -0x6fc);
                      goto LAB_0000fa4a;
                    }
                    memset_bytes((uintptr_t)&local_41c,0,0x10);
                    if (cStack_51e == '\0') {
                      uVar12 = 7;
                    }
                    else {
                      uVar12 = check_is_release_mode((uintptr_t)&cStack_51e);
                    }
                    change_work_mode_to(uVar12);
                  }
                }
                uVar12 = 0x14;
                pcVar17 = *(code **)(iVar4 + 0xc);
LAB_0000f9d8:
                (*pcVar17)((uintptr_t)&local_420,uVar12);
                return 0;
              }
              bVar2 = *(byte *)(iVar4 + 0x8dd) | 8;
LAB_0000f750:
              *(byte *)(iVar4 + 0x8dd) = bVar2;
            }
            iVar5 = -0x714;
            goto LAB_0000f742;
          }
          bVar2 = check_is_release_mode((uintptr_t)&cStack_51e);
          *(byte *)(iVar4 + 0x86e) = bVar2;
          log_message(PTR_s______display_mode_______d_0000f7ac,(uint)bVar2);
          if (*(char *)(iVar4 + 0x86e) == '\v') {
            *(undefined1 *)(iVar4 + 0x768) = 2;
            change_work_mode_to(0);
            if (*(char *)(iVar4 + -0x77c) == '\x02') {
              process_sync_buffer(iVar4 + -0x75c);
            }
          }
          else {
            *(undefined1 *)(iVar4 + 0x768) = 1;
            change_work_mode_to(3);
          }
LAB_0000f70c:
          *(undefined4 *)(iVar4 + 0x8d0) = 0;
        }
        iVar5 = -0x6fc;
LAB_0000f742:
        process_sync_buffer(iVar4 + iVar5);
        return 0;
      }
      iVar5 = iVar5 + 3;
      iVar4 = check_is_release_mode(iVar5);
      if (2 < iVar4) {
        if (*DAT_0000f1ec == 0) {
          log_message(PTR_s__s____pos__s__new_log_level_set__0000f218,DAT_0000f1f0,iVar5,iVar4);
        }
        else {
          debug_print(PTR_s__s____pos__s__new_log_level_set__0000f218,DAT_0000f1f0,iVar5,iVar4);
        }
      }
      uStack_51f = 2;
      cStack_51e = (char)iVar4;
    }
    else {
      iVar5 = iVar5 + 3;
      uVar12 = check_is_release_mode(iVar5);
      if (2 < *DAT_0000f1e8) {
        if (*DAT_0000f1ec == 0) {
          log_message(PTR_s__s____pos__s__new_screen_id__d_0000f210,DAT_0000f1f0,iVar5,uVar12);
        }
        else {
          debug_print(PTR_s__s____pos__s__new_screen_id__d_0000f210,DAT_0000f1f0,iVar5,uVar12);
        }
      }
      uStack_51f = 3;
      cStack_51e = (char)uVar12;
    }
  }
  else {
    iVar5 = iVar5 + 3;
    iVar4 = check_is_release_mode(iVar5);
    if (2 < *DAT_0000f1e8) {
      if (*DAT_0000f1ec == 0) {
        log_message(PTR_DAT_0000f208,DAT_0000f1f0,iVar5,iVar4);
      }
      else {
        debug_print(PTR_DAT_0000f208,DAT_0000f1f0,iVar5,iVar4);
      }
    }
    if (iVar4 != 0) {
      iVar4 = 1;
    }
    uStack_51f = 1;
    cStack_51e = (char)iVar4;
  }
  local_520 = 5;
  uVar12 = 3;
LAB_0000ef7e:
  ble_requeue_command_via_dispatch((uintptr_t)&local_520,uVar12);
  return 0;
}
