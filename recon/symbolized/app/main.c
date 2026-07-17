#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00016eb8 @ 0x00016eb8
 * public-name: main
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   switch_to_dfu_mode                       <= FUN_000158bc @ 0x000158bc
 *   power_for_panel                          <= FUN_00015df4 @ 0x00015df4
 *   power_for_imu_and_mic                    <= FUN_00015f80 @ 0x00015f80
 *   runtime_info_sync                        <= FUN_00016268 @ 0x00016268
 *   check_device_readiness                   <= FUN_000167b4 @ 0x000167b4
 *   button_init                              <= FUN_00017a40 @ 0x00017a40
 *   ancs_ctx_init                            <= FUN_00018208 @ 0x00018208
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   sett_init                                <= FUN_00022518 @ 0x00022518
 *   device_info_register_persistent_fields   <= FUN_00023230 @ 0x00023230
 *   drain_setting_storage_queue              <= FUN_00023acc @ 0x00023acc
 *   getAppLanguageInfofromFlash              <= FUN_00023d0c @ 0x00023d0c
 *   getDashboardStartUpModeInfofromFlash     <= FUN_00023df4 @ 0x00023df4
 *   drain_quick_note_data_queue              <= FUN_000243fc @ 0x000243fc
 *   st25dv_read_chip_ids                     <= FUN_00025290 @ 0x00025290
 *   serialization_init                       <= FUN_00025c54 @ 0x00025c54
 *   register_ipc_service_context             <= FUN_00025d40 @ 0x00025d40
 *   register_imu_funsion_context             <= FUN_00026250 @ 0x00026250
 *   spi_master_install_ops                   <= FUN_0002659c @ 0x0002659c
 *   run_main_dispatch_thread                 <= FUN_0002a65c @ 0x0002a65c
 *   ext_flash_api_init                       <= FUN_0002e4e8 @ 0x0002e4e8
 *   fuel_gauge_sample_init_timestamp         <= FUN_0002ea28 @ 0x0002ea28
 *   dmic_stream_start                        <= FUN_0002f080 @ 0x0002f080
 *   pt_nfc_eeprom_link_start                 <= FUN_00030c90 @ 0x00030c90
 *   notification_system_init                 <= FUN_00034944 @ 0x00034944
 *   init_dashboard_info                      <= FUN_00036ed8 @ 0x00036ed8
 *   quicknote_buffer_pool_init               <= FUN_00047148 @ 0x00047148
 *   boot_uptime_seconds_capture              <= FUN_0004a500 @ 0x0004a500
 *   burial_point_record_info_init            <= FUN_0004ab3c @ 0x0004ab3c
 *   lsm6dso_init_chip                        <= FUN_000622a0 @ 0x000622a0
 *   mutex_lock_syscall_handler               <= FUN_00072908 @ 0x00072908
 *   malloc                                   <= FUN_00076d6c @ 0x00076d6c
 *   app_msleep_thunk_a                       <= FUN_0007c038 @ 0x0007c038
 *   rproc_virtio_negotiate_features          <= FUN_0007c34a @ 0x0007c34a
 *   init_analytics_settings                  <= FUN_0007c360 @ 0x0007c360
 *   product_code_is_supported_egp_family     <= FUN_0007cefc @ 0x0007cefc
 *   read_rtc_counter_ms                      <= FUN_0007d0aa @ 0x0007d0aa
 *   set_device_sync_timestamp                <= FUN_0007d230 @ 0x0007d230
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   ADDR_local_esbs_ipc_service_recv_THUMB   @ 0x00015961
 *   rodata_162ed                             @ 0x000162ed
 *   rodata_16bf1                             @ 0x00016bf1
 *   rodata_7c00d                             @ 0x0007c00d
 *   rodata_87cb0                             @ 0x00087cb0
 *   rodata_87d58                             @ 0x00087d58
 *   rodata_87d70                             @ 0x00087d70
 *   rodata_99830                             @ 0x00099830
 *   rodata_99835                             @ 0x00099835
 *   rodata_9985c                             @ 0x0009985c
 *   rodata_99899                             @ 0x00099899
 *   rodata_998ad                             @ 0x000998ad
 *   rodata_998b5                             @ 0x000998b5
 *   rodata_998da                             @ 0x000998da
 *   rodata_998e7                             @ 0x000998e7
 *   rodata_998fc                             @ 0x000998fc
 *   rodata_99908                             @ 0x00099908
 *   rodata_9992e                             @ 0x0009992e
 *   rodata_99942                             @ 0x00099942
 *   rodata_9995c                             @ 0x0009995c
 *   rodata_99969                             @ 0x00099969
 *   rodata_99976                             @ 0x00099976
 *   rodata_9999c                             @ 0x0009999c
 *   rodata_999c2                             @ 0x000999c2
 *   rodata_999e4                             @ 0x000999e4
 *   rodata_999ff                             @ 0x000999ff
 *   rodata_99a23                             @ 0x00099a23
 *   rodata_99a3e                             @ 0x00099a3e
 *   rodata_99a60                             @ 0x00099a60
 *   rodata_99a7f                             @ 0x00099a7f
 *   rodata_99a94                             @ 0x00099a94
 *   rodata_99aa4                             @ 0x00099aa4
 *   rodata_99acf                             @ 0x00099acf
 *   rodata_99af4                             @ 0x00099af4
 *   rodata_99b1e                             @ 0x00099b1e
 *   rodata_99b3d                             @ 0x00099b3d
 *   rodata_99b4c                             @ 0x00099b4c
 *   rodata_99ba5                             @ 0x00099ba5
 *   rodata_99bb2                             @ 0x00099bb2
 *   rodata_fa9b4                             @ 0x000fa9b4
 *   rodata_faa2c                             @ 0x000faa2c
 *   g_log_level                              @ 0x2000230c
 *   g_200036c8                               @ 0x200036c8
 *   g_20003700                               @ 0x20003700
 *   g_ambient_light_sensor_ready             @ 0x200069f8
 *   device_info                              @ 0x200069fc
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_runtime_mode_flag                      @ 0x2000ff6e
 *   g_dashboard_startup_mode_info_defaults   @ 0x2007fc00
 */
/* Reconstructed main @ 0x16eb8  CFG_VERIFY_PREFIX_FIRST CFG_VERIFY_PREFIX_K=500 */
#include <stdint.h>
#pragma GCC diagnostic warning "-Wint-conversion"
#pragma GCC diagnostic warning "-Wimplicit-int"
#pragma GCC diagnostic warning "-Wimplicit-function-declaration"
#pragma GCC diagnostic warning "-Wint-to-pointer-cast"
#pragma GCC diagnostic warning "-Wpointer-to-int-cast"
#pragma GCC diagnostic warning "-Wincompatible-pointer-types"
#pragma GCC diagnostic warning "-Wdiscarded-qualifiers"
typedef uint8_t undefined1; typedef uint8_t byte; typedef uint8_t undefined; typedef uint8_t uchar;
typedef uint16_t undefined2; typedef uint16_t ushort; typedef uint16_t wchar_t;
typedef uint32_t undefined4; typedef uint32_t uint;
typedef long long code(int,...);
typedef uint64_t undefined8; typedef uint64_t ulonglong;
typedef int64_t longlong; typedef int32_t int32; typedef unsigned int uint3;

extern long long DEBUG_PRINT(int, ...);
extern long long switch_to_dfu_mode(int, ...);
extern long long power_for_panel(int, ...);
extern long long power_for_imu_and_mic(int, ...);
extern long long FUN_00016110(int, ...);
extern long long runtime_info_sync(int, ...);
extern long long check_device_readiness(int, ...);
extern long long button_init(int, ...);
extern long long ancs_ctx_init(int, ...);
extern long long debug_print(int, ...);
extern long long sett_init(int, ...);
extern long long device_info_register_persistent_fields(int, ...);
extern long long drain_setting_storage_queue(int, ...);
extern long long getAppLanguageInfofromFlash(int, ...);
extern long long getDashboardStartUpModeInfofromFlash(int, ...);
extern long long drain_quick_note_data_queue(int, ...);
extern long long st25dv_read_chip_ids(int, ...);
extern long long serialization_init(int, ...);
extern long long register_ipc_service_context(int, ...);
extern long long register_imu_funsion_context(int, ...);
extern long long spi_master_install_ops(int, ...);
extern long long run_main_dispatch_thread(int, ...);
extern long long ext_flash_api_init(int, ...);
extern long long FUN_0002e8fc(int, ...);
extern long long fuel_gauge_sample_init_timestamp(int, ...);
extern long long FUN_0002ea78(int, ...);
extern long long FUN_0002eaa8(int, ...);
extern long long dmic_stream_start(int, ...);
extern long long pt_nfc_eeprom_link_start(int, ...);
extern long long FUN_00032808(int, ...);
extern long long notification_system_init(int, ...);
extern long long init_dashboard_info(int, ...);
extern long long FUN_000406e4(int, ...);
extern long long quicknote_buffer_pool_init(int, ...);
extern long long boot_uptime_seconds_capture(int, ...);
extern long long burial_point_record_info_init(int, ...);
extern long long FUN_0004f564(int, ...);
extern long long FUN_0004f770(int, ...);
extern long long lsm6dso_init_chip(int, ...);
extern long long FUN_00062644(int, ...);
extern long long mutex_lock_syscall_handler(int, ...);
extern long long FUN_00075174(int, ...);
extern long long malloc(int, ...);
extern long long FUN_0007c030(int, ...);
extern long long app_msleep_thunk_a(int, ...);
extern long long rproc_virtio_negotiate_features(int, ...);
extern long long init_analytics_settings(int, ...);
extern long long product_code_is_supported_egp_family(int, ...);
extern long long read_rtc_counter_ms(int, ...);
extern long long set_device_sync_timestamp(int, ...);
extern long long z_device_is_ready(int, ...);
extern long long memset_bytes(int, ...);
extern long long change_work_mode_to(int, ...);

#define DAT_00017200 (((unsigned long)&rodata_fa9b4) /*=0xfa9b4*/)
#define DAT_00017204 (((unsigned long)&rodata_faa2c) /*=0xfaa2c*/)
#define DAT_00017208 ((volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define DAT_0001720c ((volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_00017210 (((unsigned long)&rodata_99830) /*=0x99830*/)
#define DAT_00017214 (((unsigned long)&rodata_99bb2) /*=0x99bb2*/)
#define DAT_00017218 (((unsigned long)&rodata_99835) /*=0x99835*/)
#define DAT_0001721c (((unsigned long)&g_20003700) /*=0x20003700*/)
#define DAT_00017234 (0x65920080UL)
#define DAT_00017258 (0x0a090804UL)
#define DAT_0001725c ((volatile int*)((unsigned long)&g_ambient_light_sensor_ready) /*=0x200069f8*/)
#define DAT_00017260 ((volatile int*)((unsigned long)&device_info) /*=0x200069fc*/)
#define DAT_0001750c ((volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_00017510 (((unsigned long)&rodata_99b4c) /*=0x99b4c*/)
#define DAT_00017514 (((unsigned long)&rodata_99942) /*=0x99942*/)
#define DAT_00017518 (((unsigned long)&rodata_99bb2) /*=0x99bb2*/)
#define DAT_0001751c (((unsigned long)&rodata_9985c) /*=0x9985c*/)
#define DAT_00017520 (0x00099919UL)
#define DAT_00017524 (((unsigned long)&g_200036c8) /*=0x200036c8*/)
#define DAT_00017528 (((unsigned long)&rodata_87d58) /*=0x87d58*/)
#define DAT_0001752c (((unsigned long)&rodata_99ba5) /*=0x99ba5*/)
#define DAT_00017530 (((unsigned long)&rodata_9995c) /*=0x9995c*/)
#define DAT_00017534 (((unsigned long)&rodata_99b3d) /*=0x99b3d*/)
#define DAT_00017538 (((unsigned long)&rodata_99969) /*=0x99969*/)
#define DAT_0001753c (((unsigned long)&rodata_99976) /*=0x99976*/)
#define DAT_00017540 (((unsigned long)&rodata_9999c) /*=0x9999c*/)
#define DAT_00017544 (((unsigned long)&rodata_999c2) /*=0x999c2*/)
#define DAT_00017548 ((volatile undefined4*)((unsigned long)&rodata_87cb0) /*=0x87cb0*/)
#define DAT_0001754c (((unsigned long)&rodata_999e4) /*=0x999e4*/)
#define DAT_00017550 ((volatile char*)((unsigned long)&g_runtime_mode_flag) /*=0x2000ff6e*/)
#define DAT_00017554 (((unsigned long)&rodata_9992e) /*=0x9992e*/)
#define DAT_00017558 (((unsigned long)&rodata_999ff) /*=0x999ff*/)
#define DAT_0001755c (((unsigned long)&rodata_87d70) /*=0x87d70*/)
#define DAT_00017560 (((unsigned long)&rodata_99a23) /*=0x99a23*/)
#define DAT_00017564 (((unsigned long)&rodata_99a3e) /*=0x99a3e*/)
#define DAT_00017568 (((unsigned long)&rodata_99a60) /*=0x99a60*/)
#define DAT_00017664 (((unsigned long)&rodata_99a7f) /*=0x99a7f*/)
#define DAT_00017668 (((unsigned long)&rodata_99a94) /*=0x99a94*/)
#define DAT_0001766c (((unsigned long)&rodata_99aa4) /*=0x99aa4*/)
#define DAT_00017670 ((volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_00017674 (((unsigned long)&rodata_99b3d) /*=0x99b3d*/)
#define DAT_00017678 (((unsigned long)&rodata_99acf) /*=0x99acf*/)
#define DAT_0001767c (((unsigned long)&rodata_99af4) /*=0x99af4*/)
#define DAT_00017680 (((unsigned long)&rodata_99b1e) /*=0x99b1e*/)
#define DAT_00017684 (((unsigned long)&g_dashboard_startup_mode_info_defaults) /*=0x2007fc00*/)
#define PTR_s_2024_12_28_20_20_45_00017220 (((unsigned long)&rodata_99899) /*=0x99899*/)
#define PTR_s_1b85815_00017224 (((unsigned long)&rodata_998ad) /*=0x998ad*/)
#define PTR_s__s_____Build_Info__Ver_v_d__d__d_00017228 (((unsigned long)&rodata_9985c) /*=0x9985c*/)
#define PTR_s_init_context_0001722c (((unsigned long)&rodata_99ba5) /*=0x99ba5*/)
#define PTR_s__s_____cpuapp__global_context_in_00017230 (((unsigned long)&rodata_998b5) /*=0x998b5*/)
#define PTR_s_cpuapp_hw_id_00017238 (((unsigned long)&rodata_998da) /*=0x998da*/)
#define PTR_LAB_000162ec_1_0001723c (((unsigned long)&rodata_162ed) /*=0x162ed*/)
#define PTR_s_cpunet_esbm_cpu_sync_00017240 (((unsigned long)&rodata_998e7) /*=0x998e7*/)
#define PTR_LAB_00016bf0_1_00017244 (((unsigned long)&rodata_16bf1) /*=0x16bf1*/)
#define PTR_s_cpunet_esbs_00017248 (((unsigned long)&rodata_998fc) /*=0x998fc*/)
#define PTR_FUN_00015960_1_0001724c (ADDR_local_esbs_ipc_service_recv_THUMB /*=0x15961*/)
#define PTR_s_cpunet_esbs_ctrl_00017250 (((unsigned long)&rodata_99908) /*=0x99908*/)
#define PTR_LAB_0007c00c_1_00017254 (((unsigned long)&rodata_7c00d) /*=0x7c00d*/)

void main(void)

{
  int *piVar1;
  int *piVar2;
  undefined *puVar3;
  char *pcVar4;
  char cVar5;
  int iVar6;
  char *pcVar7;
  undefined4 uVar8;
  undefined8 uVar64;
  undefined4 *puVar9;
  undefined1 *puVar10;
  undefined2 *puVar11;
  undefined4 extraout_r1 = 0;
  undefined4 extraout_r1_00 = 0;
  undefined4 extraout_r1_01 = 0;
  byte bVar12;
  uint uVar13;
  char *pcVar14;

  ((long long (*)(void))boot_uptime_seconds_capture)();
  iVar6 = FUN_0004f564(0x10);
  if (iVar6 != 0) {
    *(volatile undefined4 *)(iVar6 + 4) = DAT_00017200;
  }
  piVar1 = DAT_00017208;
  *(volatile undefined4 *)(iVar6 + 8) = DAT_00017204;
  *(volatile undefined1 *)(iVar6 + 0xc) = 0;
  ((long long (*)(void))FUN_0004f770)();
  if (0 < *piVar1) {
    if (*DAT_0001720c == 0) {
      DEBUG_PRINT(DAT_00017218,DAT_00017214,DAT_00017210);
    }
    else {
      ((long long (*)(void))debug_print)();
    }
  }
  FUN_00075174(DAT_0001721c);
  ((long long (*)(void))serialization_init)();
  piVar2 = DAT_0001720c;
  if (1 < *piVar1) {
    if (*DAT_0001720c == 0) {
      DEBUG_PRINT(DAT_0001751c,DAT_00017518,1,4,5,PTR_s_1b85815_00017224,
                  PTR_s_2024_12_28_20_20_45_00017220);
    }
    else {
      debug_print(PTR_s__s_____Build_Info__Ver_v_d__d__d_00017228,DAT_00017214);
    }
    if (1 < *piVar1) {
      if (*piVar2 == 0) {
        DEBUG_PRINT(PTR_s__s_____cpuapp__global_context_in_00017230,PTR_s_init_context_0001722c);
      }
      else {
        ((long long (*)(void))debug_print)();
      }
    }
  }
  pcVar7 = (char *)malloc(0x1188);
  memset_bytes(pcVar7,0,0x1188);
  piVar2 = DAT_00017260;
  *(volatile undefined4 *)(pcVar7 + 0xfda) = 0xffffffff;
  *(volatile undefined2 *)(pcVar7 + 0xfde) = 0xffff;
  *(volatile undefined4 *)(pcVar7 + 0xfe0) = 0xffffffff;
  *(volatile undefined2 *)(pcVar7 + 0xfe4) = 0xffff;
  *(volatile char *)pcVar7 = '\x01';
  *piVar2 = (int)pcVar7;
  FUN_0007c030(pcVar7 + 8,1);
  FUN_0007c030(pcVar7 + 0x20,10);
  FUN_0007c030(pcVar7 + 0x38,1);
  FUN_0007c030(pcVar7 + 0x50,1);
  pcVar14 = pcVar7 + 0x68;
  FUN_0007c030(pcVar7 + 0xaf4,1);
  FUN_0007c030(pcVar14,1);
  FUN_0007c030(pcVar7 + 0x80,1);
  FUN_0007c030(pcVar7 + 0x98,1);
  FUN_0007c030(pcVar7 + 0xb0,1);
  iVar6 = *piVar2;
  *(undefined1 *)(iVar6 + 1) = 0xff;
  *(undefined2 *)(iVar6 + 0x105c) = 0;
  change_work_mode_to(0);
  iVar6 = malloc(0x6a);
  *(int *)(pcVar7 + 0xfec) = iVar6;
  if (iVar6 != 0) {
    memset_bytes(iVar6,0,0x6a);
  }
  set_device_sync_timestamp(DAT_00017234);
  uVar8 = malloc(7);
  *(undefined4 *)(pcVar7 + 0xff0) = uVar8;
  puVar9 = (undefined4 *)malloc(5);
  *(undefined4 **)(pcVar7 + 0x1054) = puVar9;
  if (puVar9 != (undefined4 *)0x0) {
    *puVar9 = 0;
    *(undefined1 *)(puVar9 + 1) = 0;
  }
  iVar6 = malloc(0x217);
  *(int *)(pcVar7 + 0xffc) = iVar6;
  if (iVar6 != 0) {
    memset_bytes(iVar6,0,0x217);
  }
  uVar8 = malloc(0xf5);
  *(undefined4 *)(pcVar7 + 0x1000) = uVar8;
  uVar8 = malloc(0x198);
  *(undefined4 *)(pcVar7 + 0x1004) = uVar8;
  uVar8 = malloc(0x198);
  *(undefined4 *)(pcVar7 + 0x1008) = uVar8;
  uVar8 = malloc(0x199);
  *(undefined4 *)(pcVar7 + 0x100c) = uVar8;
  iVar6 = malloc(0x50f);
  *(int *)(pcVar7 + 0x1020) = iVar6;
  if (iVar6 != 0) {
    memset_bytes(iVar6,0,0x50f);
  }
  iVar6 = malloc(0x201);
  *(int *)(pcVar7 + 0x1024) = iVar6;
  if (iVar6 != 0) {
    memset_bytes(iVar6,0,0x201);
  }
  iVar6 = malloc(0x201);
  *(int *)(pcVar7 + 0x1028) = iVar6;
  if (iVar6 != 0) {
    memset_bytes(iVar6,0,0x201);
  }
  iVar6 = malloc(0x16a);
  *(int *)(pcVar7 + 0xff4) = iVar6;
  if (iVar6 != 0) {
    *(undefined1 *)(iVar6 + 0x168) = 0;
    *(undefined4 *)(iVar6 + 0x164) = 0;
  }
  uVar8 = malloc(0xaf);
  *(undefined4 *)(pcVar7 + 0xff8) = uVar8;
  puVar9 = (undefined4 *)malloc(0xb);
  *(undefined4 **)(pcVar7 + 0x1010) = puVar9;
  if (puVar9 != (undefined4 *)0x0) {
    *puVar9 = 0;
    puVar9[1] = 0;
    *(undefined4 *)((int)puVar9 + 7) = 0;
  }
  uVar8 = malloc(0x21);
  *(undefined4 *)(pcVar7 + 0x1014) = uVar8;
  ((long long (*)(void))FUN_000406e4)();
  puVar10 = (undefined1 *)malloc(1);
  *(undefined1 **)(pcVar7 + 0x1018) = puVar10;
  if (puVar10 != (undefined1 *)0x0) {
    *puVar10 = 0;
  }
  puVar11 = (undefined2 *)malloc(2);
  *(undefined2 **)(pcVar7 + 0x101c) = puVar11;
  if (puVar11 != (undefined2 *)0x0) {
    *puVar11 = 0;
  }
  *(volatile undefined4 *)(pcVar7 + 0x1069) = 0xffffffff;
  *(volatile undefined4 *)(pcVar7 + 0x106c) = 0xffffffff;
  *(volatile undefined2 *)(pcVar7 + 0x1070) = 0;
  register_ipc_service_context(pcVar7 + 0x714);
  puVar3 = (undefined *)PTR_s_cpuapp_hw_id_00017238;
  pcVar7[0x6e4] = '\x01';
  *(undefined **)(pcVar7 + 0x6e8) = puVar3;
  *(undefined **)(pcVar7 + 0x6ec) = (undefined *)PTR_LAB_000162ec_1_0001723c;
  (**(code **)(pcVar7 + 0x778))(pcVar7 + 0x6e4);
  pcVar7[0x6f0] = '\x06';
  *(undefined **)(pcVar7 + 0x6f4) = (undefined *)PTR_s_cpunet_esbm_cpu_sync_00017240;
  *(undefined **)(pcVar7 + 0x6f8) = (undefined *)PTR_LAB_00016bf0_1_00017244;
  pcVar7[0x6fc] = '\x04';
  *(undefined **)(pcVar7 + 0x700) = (undefined *)PTR_s_cpunet_esbs_00017248;
  *(undefined **)(pcVar7 + 0x704) = (undefined *)PTR_FUN_00015960_1_0001724c;
  pcVar7[0x708] = '\x05';
  *(undefined **)(pcVar7 + 0x70c) = (undefined *)PTR_s_cpunet_esbs_ctrl_00017250;
  *(undefined **)(pcVar7 + 0x710) = (undefined *)PTR_LAB_0007c00c_1_00017254;
  (**(code **)(pcVar7 + 0x778))(pcVar7 + 0x6f0);
  (**(code **)(pcVar7 + 0x778))(pcVar7 + 0x6fc);
  (**(code **)(pcVar7 + 0x778))(pcVar7 + 0x708);
  uVar8 = DAT_00017258;
  *(volatile undefined4 *)(pcVar7 + 0xb24) = 0;
  *(volatile undefined4 *)(pcVar7 + 0xb28) = uVar8;
  *(volatile undefined2 *)(pcVar7 + 0xb2c) = 0x200b;
  spi_master_install_ops(pcVar7 + 0xb10);
  iVar6 = ((long long (*)(void))button_init)();
  *DAT_0001725c = iVar6;
  cVar5 = ext_flash_api_init(pcVar7 + 0x1030,pcVar7 + 0x1034,pcVar7 + 0x1038);
  pcVar7[0x1089] = cVar5;
  pcVar7[1] = '\0';
  sett_init(pcVar7 + 0x103c);
  init_analytics_settings(pcVar7);
  if (*DAT_0001725c == 0) {
    iVar6 = *piVar1;
    *pcVar7 = '\x01';
    if (0 < iVar6) {
      iVar6 = *DAT_0001750c;
      uVar8 = DAT_00017520;
LAB_000172a6:
      if (iVar6 == 0) {
        DEBUG_PRINT(uVar8,DAT_00017510);
      }
      else {
        ((long long (*)(void))debug_print)();
      }
    }
  }
  else if (*DAT_0001725c == 1) {
    *pcVar7 = '\x02';
    if (0 < *piVar1) {
      iVar6 = *DAT_0001750c;
      uVar8 = DAT_00017554;
      goto LAB_000172a6;
    }
  }
  else if (0 < *piVar1) {
    if (*DAT_0001750c == 0) {
      DEBUG_PRINT(DAT_00017514,DAT_00017510);
    }
    else {
      ((long long (*)(void))debug_print)();
    }
  }
  uVar64 = runtime_info_sync(pcVar7);
  if (*pcVar7 == '\x01') {
    *(volatile undefined2 *)(pcVar7 + 0xfcc) = 0x0401;
    *(volatile undefined1 *)(pcVar7 + 0xfce) = 5;
    pcVar7[0xe4] = pcVar7[0xe4] | 4;
  }
  else if (*pcVar7 == '\x02') {
    *(volatile undefined1 *)(pcVar7 + 0xfcf) = 1;
    *(volatile undefined2 *)(pcVar7 + 0xfd0) = 0x0504;
    pcVar7[0x6de] = pcVar7[0x6de] | 4;
  }
  mutex_lock_syscall_handler(pcVar7 + 8,(uint)(uVar64 >> 32),0xffffffff,0xffffffff);
  if (pcVar7[1] == '\x01') {
LAB_00017372:
    if (1 < *piVar1) {
      if (*DAT_0001750c == 0) {
        DEBUG_PRINT(DAT_00017538,DAT_00017534);
      }
      else {
        ((long long (*)(void))debug_print)();
      }
    }
  }
  else {
    ancs_ctx_init(pcVar7 + 0x77c);
    ((long long (*)(void))power_for_panel)();
    if (*pcVar7 == '\x01') {
      ((long long (*)(void))burial_point_record_info_init)();
      FUN_00075174(DAT_00017524);
      ((long long (*)(void))power_for_imu_and_mic)();
      *(undefined4 *)(pcVar7 + 0xf00) = DAT_00017528;
      lsm6dso_init_chip(DAT_00017528);
      register_imu_funsion_context(pcVar7 + 0xee4);
      FUN_0002e8fc(pcVar7 + 0xf80);
    }
    else if (*pcVar7 == '\x02') {
      ((long long (*)(void))power_for_imu_and_mic)();
      *(undefined4 *)(pcVar7 + 0xf00) = DAT_00017528;
      lsm6dso_init_chip(DAT_00017528);
    }
    quicknote_buffer_pool_init(pcVar7 + 0xb6c);
    ((long long (*)(void))st25dv_read_chip_ids)();
    init_dashboard_info(*(undefined4 *)(*piVar2 + 0xfec));
    ((long long (*)(void))getDashboardStartUpModeInfofromFlash)();
    ((long long (*)(void))getAppLanguageInfofromFlash)();
    ((long long (*)(void))drain_setting_storage_queue)();
    ((long long (*)(void))drain_quick_note_data_queue)();
    pcVar7[0x108e] = '\0';
    *(undefined2 *)(pcVar7 + 0xed8) = *(undefined2 *)(pcVar7 + 0xede);
    pcVar7[0x108c] = '\0';
    if (1 < *piVar1) {
      if (*DAT_0001750c == 0) {
        DEBUG_PRINT(DAT_00017530,DAT_0001752c);
      }
      else {
        ((long long (*)(void))debug_print)();
      }
      goto LAB_00017372;
    }
  }
  device_info_register_persistent_fields(pcVar7);
  iVar6 = (**(code **)(pcVar7 + 0x77c))(pcVar7 + 0x77c);
  if ((iVar6 != 0) && (1 < *piVar1)) {
    if (*DAT_0001750c == 0) {
      DEBUG_PRINT(DAT_0001753c,DAT_00017534,iVar6);
    }
    else {
      ((long long (*)(void))debug_print)();
    }
  }
  if (*pcVar7 == '\x01') {
    iVar6 = (**(code **)(pcVar7 + 0xf70))(pcVar7 + 0xee4);
    if ((iVar6 != 0) && (1 < *piVar1)) {
      if (*DAT_0001750c == 0) {
        DEBUG_PRINT(DAT_00017540,DAT_00017534,iVar6);
      }
      else {
        ((long long (*)(void))debug_print)();
      }
    }
    iVar6 = (**(code **)(pcVar7 + 0xf80))(pcVar7 + 0xf80);
    if ((iVar6 != 0) && (1 < *piVar1)) {
      if (*DAT_0001750c == 0) {
        DEBUG_PRINT(DAT_00017544,DAT_00017534,iVar6);
      }
      else {
        ((long long (*)(void))debug_print)();
      }
    }
  }
  puVar9 = DAT_00017548;
  iVar6 = z_device_is_ready(DAT_00017548);
  uVar8 = DAT_0001754c;
  if (iVar6 != 0) {
    DEBUG_PRINT(DAT_00017558,*puVar9);
    iVar6 = z_device_is_ready(DAT_0001755c);
    uVar8 = DAT_00017560;
    if (((iVar6 != 0) && (iVar6 = fuel_gauge_sample_init_timestamp(DAT_0001755c), uVar8 = DAT_00017564, -1 < iVar6)) &&
       (iVar6 = FUN_00062644(DAT_0001755c), uVar8 = DAT_00017568, -1 < iVar6)) {
      DEBUG_PRINT(DAT_00017664);
      DEBUG_PRINT(DAT_00017668);
      ((long long (*)(void))FUN_00016110)();
      iVar6 = ((long long (*)(void))product_code_is_supported_egp_family)();
      if (iVar6 != 0) {
        DEBUG_PRINT(DAT_0001766c);
        ((long long (*)(void))FUN_0002ea78)();
      }
      iVar6 = (**(code **)(pcVar7 + 0xb10))(pcVar7 + 0xb10);
      if ((iVar6 != 0) && (1 < *piVar1)) {
        if (*DAT_00017670 == 0) {
          DEBUG_PRINT(DAT_00017678,DAT_00017674,iVar6);
        }
        else {
          ((long long (*)(void))debug_print)();
        }
      }
      iVar6 = (**(code **)(pcVar7 + 0xb6c))(pcVar7 + 0xb6c);
      if ((iVar6 != 0) && (1 < *piVar1)) {
        if (*DAT_00017670 == 0) {
          DEBUG_PRINT(DAT_0001767c,DAT_00017674,iVar6);
        }
        else {
          ((long long (*)(void))debug_print)();
        }
      }
      ((long long (*)(void))pt_nfc_eeprom_link_start)();
      ((long long (*)(void))notification_system_init)();
      if (1 < *piVar1) {
        if (*DAT_00017670 == 0) {
          DEBUG_PRINT(DAT_00017680,DAT_00017674);
        }
        else {
          ((long long (*)(void))debug_print)();
        }
      }
      *(volatile undefined4 *)(pcVar7 + 0x1078) = 0;
      read_rtc_counter_ms(pcVar7 + 0x1078);
      FUN_00032808(*(undefined1 *)(DAT_00017684 + 0x70));
      goto LAB_00017414;
    }
  }
  DEBUG_PRINT(uVar8);
LAB_00017414:
  run_main_dispatch_thread(pcVar7);
  uVar64 = ((long long (*)(void))FUN_0002eaa8)();
  pcVar4 = DAT_00017550;
  uVar8 = (uint)(uVar64 >> 32);
  do {
    mutex_lock_syscall_handler(pcVar14,uVar8,0xffffffff,0xffffffff);
    if (*pcVar4 == '\x01') {
      switch_to_dfu_mode(pcVar14);
    }
    while( true ) {
      uVar13 = (uint)(byte)pcVar7[0x1059];
      if (uVar13 == 0) break;
      if ((int)(uVar13 << 0x1f) < 0) {
        rproc_virtio_negotiate_features(pcVar7,0);
        bVar12 = pcVar7[0x1059] & 0xfe;
        goto LAB_0001762a;
      }
      if ((int)(uVar13 << 0x1e) < 0) {
        pcVar7[0xfea] = '\v';
        bVar12 = pcVar7[0x1059] & 0xfd;
        goto LAB_0001762a;
      }
      if ((int)(uVar13 << 0x1d) < 0) {
        ((long long (*)(void))dmic_stream_start)();
        bVar12 = pcVar7[0x1059] & 0xfb;
        goto LAB_0001762a;
      }
      if ((int)(uVar13 << 0x1c) < 0) {
        ((long long (*)(void))check_device_readiness)();
        bVar12 = pcVar7[0x1059] & 0xf7;
LAB_0001762a:
        pcVar7[0x1059] = bVar12;
      }
    }
    uVar64 = app_msleep_thunk_a(1);
    uVar8 = (uint)(uVar64 >> 32);
  } while( true );
}
