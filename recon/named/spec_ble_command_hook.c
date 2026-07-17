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
 *   mark_master_or_low_battery_flag          <= FUN_0002efc0 @ 0x0002efc0
 *   debug_print_hex_dump                     <= FUN_0004a424 @ 0x0004a424
 *   sys_reboot                               <= FUN_0004c0a8 @ 0x0004c0a8
 *   cjson_delete                             <= FUN_00064b1c @ 0x00064b1c
 *   cjson_create_object                      <= FUN_00064ca4 @ 0x00064ca4
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   k_uptime_get_0                           <= FUN_0007c18e @ 0x0007c18e
 *   ble_requeue_command_via_dispatch         <= FUN_0007c244 @ 0x0007c244
 *   check_is_release_mode                    <= FUN_00086a06 @ 0x00086a06
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 *   vdprintf_to_fd                           <= FUN_00086f00 @ 0x00086f00
 *   strcpy                                   <= FUN_00086fee @ 0x00086fee
 *   __strcpy_chk                             <= FUN_00086ffe @ 0x00086ffe
 *   strncmp                                  <= FUN_00087036 @ 0x00087036
 *   strstr                                   <= FUN_000870be @ 0x000870be
 * address symbols (name @ address):
 *   ADDR_ble_requeue_command_via_dispatch_THUMB @ 0x0007c245
 *   rodata_99899                             @ 0x00099899
 *   rodata_9d7f7                             @ 0x0009d7f7
 *   rodata_9d7fa                             @ 0x0009d7fa
 *   rodata_9d81e                             @ 0x0009d81e
 *   rodata_9d822                             @ 0x0009d822
 *   rodata_9d857                             @ 0x0009d857
 *   rodata_9d85b                             @ 0x0009d85b
 *   rodata_9d88c                             @ 0x0009d88c
 *   rodata_9d890                             @ 0x0009d890
 *   rodata_9d8b1                             @ 0x0009d8b1
 *   rodata_9d8b5                             @ 0x0009d8b5
 *   rodata_9d8da                             @ 0x0009d8da
 *   rodata_9d8de                             @ 0x0009d8de
 *   rodata_9d8ed                             @ 0x0009d8ed
 *   rodata_9d8fc                             @ 0x0009d8fc
 *   rodata_9d90a                             @ 0x0009d90a
 *   rodata_9d925                             @ 0x0009d925
 *   rodata_9d92b                             @ 0x0009d92b
 *   rodata_9d94a                             @ 0x0009d94a
 *   rodata_9d95b                             @ 0x0009d95b
 *   rodata_9d969                             @ 0x0009d969
 *   rodata_9d9a5                             @ 0x0009d9a5
 *   rodata_9d9ed                             @ 0x0009d9ed
 *   rodata_9da2f                             @ 0x0009da2f
 *   rodata_9da61                             @ 0x0009da61
 *   rodata_9db03                             @ 0x0009db03
 *   rodata_9db15                             @ 0x0009db15
 *   rodata_9db45                             @ 0x0009db45
 *   rodata_9db4f                             @ 0x0009db4f
 *   rodata_9db81                             @ 0x0009db81
 *   rodata_9db91                             @ 0x0009db91
 *   rodata_9dbb4                             @ 0x0009dbb4
 *   rodata_9dbc5                             @ 0x0009dbc5
 *   rodata_9dbec                             @ 0x0009dbec
 *   rodata_9dc17                             @ 0x0009dc17
 *   rodata_9dc1a                             @ 0x0009dc1a
 *   rodata_9dc9c                             @ 0x0009dc9c
 *   rodata_9dcbb                             @ 0x0009dcbb
 *   rodata_9dd09                             @ 0x0009dd09
 *   rodata_9dd24                             @ 0x0009dd24
 *   rodata_9dd27                             @ 0x0009dd27
 *   rodata_9dd4b                             @ 0x0009dd4b
 *   rodata_9dd4e                             @ 0x0009dd4e
 *   rodata_9dd6a                             @ 0x0009dd6a
 *   rodata_9dd6d                             @ 0x0009dd6d
 *   rodata_9dd70                             @ 0x0009dd70
 *   rodata_9dd73                             @ 0x0009dd73
 *   rodata_9dd91                             @ 0x0009dd91
 *   rodata_9dd94                             @ 0x0009dd94
 *   rodata_9ddb9                             @ 0x0009ddb9
 *   rodata_9ddbc                             @ 0x0009ddbc
 *   rodata_9ddbf                             @ 0x0009ddbf
 *   rodata_9ddc8                             @ 0x0009ddc8
 *   rodata_9ddcb                             @ 0x0009ddcb
 *   rodata_9ddce                             @ 0x0009ddce
 *   rodata_9ddd8                             @ 0x0009ddd8
 *   rodata_9dddb                             @ 0x0009dddb
 *   rodata_9ddde                             @ 0x0009ddde
 *   rodata_9dde8                             @ 0x0009dde8
 *   rodata_9ddeb                             @ 0x0009ddeb
 *   rodata_9de32                             @ 0x0009de32
 *   rodata_9de35                             @ 0x0009de35
 *   rodata_9de4c                             @ 0x0009de4c
 *   rodata_9de4f                             @ 0x0009de4f
 *   rodata_9de5e                             @ 0x0009de5e
 *   rodata_9de61                             @ 0x0009de61
 *   rodata_9de63                             @ 0x0009de63
 *   rodata_9de6e                             @ 0x0009de6e
 *   rodata_9de71                             @ 0x0009de71
 *   rodata_9de74                             @ 0x0009de74
 *   rodata_9dfa9                             @ 0x0009dfa9
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
#define DAT_0000f1e4 0x0009d7f7u
#define DAT_0000f1e8 ((volatile int *)0x2000230cu)
#define DAT_0000f1ec ((volatile int *)0x20007554u)
#define DAT_0000f1f0 0x0009dfa9u
#define DAT_0000f458 0x00000000u
#define DAT_0000f46c ((volatile int *)0x2000230cu)
#define DAT_0000f470 ((volatile int *)0x20007554u)
#define DAT_0000f474 0x0009d92bu
#define DAT_0000f478 0x000a1f20u
#define DAT_0000f4a0 0x000f3c02u
#define DAT_0000f4a4 0x0009db03u
#define DAT_0000f4a8 0x0009db91u
#define DAT_0000f76c ((volatile int *)0x20007554u)
#define DAT_0000f770 0x0009dfa9u
#define DAT_0000f794 ((volatile int *)0x2000230cu)
#define DAT_0000fa50 0x0009dd70u
#define DAT_0000fa54 ((volatile int *)0x200069e8u)
#define DAT_0000fa64 0x0009dd73u
#define DAT_0000fa68 0x0009dd91u
#define DAT_0000fa6c ((volatile int *)0x2000230cu)
#define DAT_0000fa70 ((volatile int *)0x20007554u)
#define DAT_0000fa74 0x0009dfa9u
#define DAT_0000fa84 ((volatile int *)0x20007aacu)
#define DAT_0000fa88 0x0009ddbfu
#define DAT_0000fa8c 0x0009ddc8u
#define DAT_0000faac ((volatile int *)0x2000a074u)
#define DAT_0000fab0 0x00099899u
#define DAT_0000fab4 0x2000ff4eu
#define DAT_0000fca0 0x00000000u
#define DAT_0000fca8 0x00000000u
#define DAT_0000fcc8 ((volatile int *)0x20007554u)
#define DAT_0000fce0 0x000f1031u
#define PTR_DAT_0000f1f8 0x0009d81eu
#define PTR_DAT_0000f1fc 0x0009d822u
#define PTR_DAT_0000f204 0x0009d857u
#define PTR_DAT_0000f208 0x0009d85bu
#define PTR_DAT_0000f20c 0x0009d88cu
#define PTR_DAT_0000f214 0x0009d8b1u
#define PTR_DAT_0000f21c 0x0009d8dau
#define PTR_DAT_0000f484 0x0009d969u
#define PTR_DAT_0000f49c 0x0009da61u
#define PTR_DAT_0000f784 0x0009dc17u
#define PTR_DAT_0000f7a0 0x0009dd24u
#define PTR_DAT_0000f7a8 0x0009dd4bu
#define PTR_DAT_0000f7b0 0x0009dd6au
#define PTR_DAT_0000f7b4 0x0009dd6du
#define PTR_DAT_0000fa58 0x200069ecu
#define PTR_DAT_0000fa5c 0x200069f0u
#define PTR_DAT_0000fa60 0x200069f4u
#define PTR_DAT_0000fa7c 0x0009ddb9u
#define PTR_DAT_0000fa80 0x0009ddbcu
#define PTR_DAT_0000fa94 0x0009ddcbu
#define PTR_DAT_0000fa9c 0x0009ddd8u
#define PTR_DAT_0000faa0 0x0009dddbu
#define PTR_DAT_0000faa8 0x0009dde8u
#define PTR_DAT_0000fabc 0x0009de32u
#define PTR_DAT_0000fac4 0x0009de4cu
#define PTR_DAT_0000fcb0 0x0009de5eu
#define PTR_DAT_0000fcbc 0x0009de6eu
#define PTR_DAT_0000fcc0 0x0009de71u
#define PTR_DAT_0000fcdc 0x0009db4fu
#define PTR_FUN_0007c244_1_0000f200 0x0007c245u
#define PTR_FUN_0007c244_1_0000f490 0x0007c245u
#define PTR_FUN_0007c244_1_0000f77c 0x0007c245u
#define PTR_FUN_0007c244_1_0000fcec 0x0007c245u
#define PTR_SIM_NAV_0000fcd0 0x0009db15u
#define PTR_SIM_TEL_0000f494 0x0009da2fu
#define PTR_s_B__d__V__d__A__d__T__d_0000fac0 0x0009de35u
#define PTR_s_VADC__d_TMR__d_0000fac8 0x0009de4fu
#define PTR_s______display_mode_______d_0000f7ac 0x0009dd4eu
#define PTR_s______start_upload_audio______0000f78c 0x0009dc9cu
#define PTR_s______test_callback_audio_data____0000f788 0x0009dc1au
#define PTR_s______test_set_esb_channel________0000f7a4 0x0009dd27u
#define PTR_s___whitelist_app___com_apple_Mobi_0000f488 0x0009d9a5u
#define PTR_s__cmd__0000f468 0x0009d925u
#define PTR_s__s____11_len__d_0000f47c 0x0009d94au
#define PTR_s__s____22_len__d_0000f774 0x0009dbb4u
#define PTR_s__s______cmd_type__s__value__s__t_0000f780 0x0009dbecu
#define PTR_s__s_____cmd_type__s__title__s__ms_0000f778 0x0009dbc5u
#define PTR_s__s____buf__s_0000f220 0x0009d8deu
#define PTR_s__s____cmd__d_0000f480 0x0009d95bu
#define PTR_s__s____cmd__s_0000f224 0x0009d8edu
#define PTR_s__s____cmd_type__s__value__s__tx__0000f48c 0x0009d9edu
#define PTR_s__s____cmd_type__s__value__s__tx__0000fce8 0x0009d9edu
#define PTR_s__s____en__s_0000f228 0x0009d8fcu
#define PTR_s__s____enable___d__sec__d_0000f22c 0x0009d90au
#define PTR_s__s____enable___d__sec__d_0000f464 0x0009d90au
#define PTR_s__s____pos__s__new_log_level_set__0000f218 0x0009d8b5u
#define PTR_s__s____pos__s__new_screen_id__d_0000f210 0x0009d890u
#define PTR_s__s____sys_reboot_because_reboot_c_0000fa78 0x0009dd94u
#define PTR_s__s____test_BLE_REQ_POST_BT_UNPAI_0000f1f4 0x0009d7fau
#define PTR_s__s____unable_to_audio_transfer__d_0000f79c 0x0009dcbbu
#define PTR_s__s____unable_to_change_MTU_for_a_0000f798 0x0009dc3fu
#define PTR_s_deinit_flash_0000fcb8 0x0009de61u
#define PTR_s_direction_0000fcd8 0x0009db45u
#define PTR_s_enable_0000f498 0x0009e235u
#define PTR_s_enable_0000fcd4 0x0009e235u
#define PTR_s_init_flash_0000fcb4 0x0009de63u
#define PTR_s_level___d_0000fa98 0x0009ddceu
#define PTR_s_master_mac___02X__02X__02X__02X__0000fcc4 0x0009de74u
#define PTR_s_navigation_info_0000fce4 0x0009db81u
#define PTR_s_net_build_time___s__app_build_ti_0000fab8 0x0009ddebu
#define PTR_s_pitch___d_0000faa4 0x0009dddeu
#define PTR_s_spec_ble_command_hook_0000f460 0x0009dfa9u
#define PTR_s_spec_ble_command_hook_0000fccc 0x0009dfa9u
#define PTR_s_t0____d_error_count____d_0000f790 0x0009dd09u
extern uint32_t log_message(uintptr_t,...);
extern uint32_t strcmp(uintptr_t,...);
extern uint32_t strlen(uintptr_t,...);
extern uint32_t opt3007_get_max_lux(uintptr_t,...);
extern uint32_t ancs_get_conn_ctx(uintptr_t,...);
extern uint32_t debug_print(uintptr_t,...);
extern uint32_t subcontracing_send_data_pkcs7(uintptr_t,...);
extern uint32_t mobile_send_notification_to_ble_device_test(uintptr_t,...);
extern uint32_t simulator_ancs_calendar_schedule_trigger(uintptr_t,...);
extern uint32_t FUN_00025448(uintptr_t,...);
extern uint32_t mark_master_or_low_battery_flag(uintptr_t,...);
extern uint32_t debug_print_hex_dump(uintptr_t,...);
extern uint32_t sys_reboot(uintptr_t,...);
extern uint32_t cjson_delete(uintptr_t,...);
extern uint32_t cjson_create_object(uintptr_t,...);
extern uint32_t z_impl_k_sem_take(uintptr_t,...);
extern uint32_t FUN_00074844(uintptr_t,...);
extern uint32_t k_uptime_get_0(uintptr_t,...);
extern uint32_t ble_requeue_command_via_dispatch(uintptr_t,...);
extern uint32_t FUN_00085014(uintptr_t,...);
extern uint32_t FUN_00085046(uintptr_t,...);
extern uint32_t FUN_00085076(uintptr_t,...);
extern uint32_t FUN_0008509e(uintptr_t,...);
extern uint32_t check_is_release_mode(uintptr_t,...);
extern uint32_t memcpy(uintptr_t,...);
extern uint32_t FUN_00086c1e(uintptr_t,...);
extern uint32_t memset_bytes(uintptr_t,...);
extern uint32_t vdprintf_to_fd(uintptr_t,...);
extern uint32_t strcpy(uintptr_t,...);
extern uint32_t __strcpy_chk(uintptr_t,...);
extern uint32_t strncmp(uintptr_t,...);
extern uint32_t FUN_00087080(uintptr_t,...);
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
  undefined4 local_5c4;
  int local_5c0;
  undefined1 auStack_5bc [28];
  undefined4 local_5a0;
  undefined1 auStack_59c [124];
  undefined1 local_520;
  undefined1 uStack_51f;
  char cStack_51e;
  undefined1 uStack_51d;
  undefined1 uStack_51c;
  undefined1 local_51b;
  undefined4 local_420;
  int local_41c;
  int iStack_418;
  int local_414;

  iVar4 = ancs_get_conn_ctx(0);
  local_520 = 0;
  uStack_51f = 0;
  cStack_51e = '\0';
  uStack_51d = 0;
  memset_bytes((uintptr_t)&uStack_51c,0,0xfc);
  FUN_00086c1e((uintptr_t)&local_520,param_1,param_2,0x100);
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
    FUN_00087080((uintptr_t)&local_5a0,pcVar13,(int)pcVar18 - (int)pcVar13,0x20);
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
          FUN_00086c1e((uintptr_t)&local_5c0,&local_420,(int)pcVar14 - (int)&local_420,4);
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
          FUN_00086c1e((uintptr_t)&local_5a0,pcVar14,(int)pcVar18 - (int)pcVar14,4);
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
          FUN_00086c1e((uintptr_t)&local_5c4,pcVar14,(int)pcVar18 - (int)pcVar14,4);
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
                FUN_00085076((int)DAT_0000fca0,uVar8,PTR_s_enable_0000fcd4);
                FUN_00085076((int)DAT_0000fca8,uVar8,PTR_s_direction_0000fcd8);
                FUN_0008509e(uVar8,DAT_0000fce0,PTR_DAT_0000fcdc);
                uVar12 = cjson_create_object(0);
                FUN_00085046(uVar12,PTR_s_navigation_info_0000fce4,uVar8);
                uVar8 = FUN_00085014(uVar12);
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
                FUN_00086c1e((uintptr_t)&local_5a0,pcVar18,(int)pcVar13 - (int)pcVar18,0x80);
                pcVar14 = (char *)&local_5a0;
                do {
                  pcVar13 = pcVar14;
                  pcVar14 = pcVar13 + 1;
                } while (*pcVar13 != '#');
                FUN_00087080((uintptr_t)&local_5c0,&local_5a0,(int)pcVar13 - (int)&local_5a0,0x20);
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
          FUN_00085076((int)DAT_0000f458,uVar8,PTR_s_enable_0000f498);
          FUN_0008509e(uVar8,DAT_0000f4a0,PTR_DAT_0000f49c);
          uVar12 = cjson_create_object(0);
          FUN_00085046(uVar12,DAT_0000f4a4,uVar8);
          uVar8 = FUN_00085014(uVar12);
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
              iVar7 = k_uptime_get_0(0);
              uVar19 = 0;
              iVar5 = 0;
              do {
                local_5a0 = (local_5a0 & 0xff000000u) | ((uint32_t)(uint8_t)iVar5 << 16) | 0x0af1u;
                memcpy((int)&local_5a0 + 3,pcVar14,0x68);
                while (iVar10 = (**(code **)(iVar4 + 0xc))((uintptr_t)&local_5a0,0x6b), iVar10 != 0) {
                  uVar19 = uVar19 + 1 & 0xffff;
                  FUN_00074844(0x148,0);
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
                  iVar4 = k_uptime_get_0(0);
                  log_message(PTR_s_t0____d_error_count____d_0000f790,iVar4 - iVar7,uVar19);
                  return 0;
                }
              } while( true );
            }
            FUN_00074844(0x148,0);
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
                    FUN_00074844(0x4000,0);
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
                    uVar12 = FUN_00025448(0);
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
