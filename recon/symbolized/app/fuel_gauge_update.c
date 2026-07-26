#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00010b18 @ 0x00010b18
 * public-name: fuel_gauge_update
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __aeabi_dadd                             <= FUN_0000d58c @ 0x0000d58c
 *   __extendsfdf2                            <= FUN_0000d848 @ 0x0000d848
 *   __muldf3                                 <= FUN_0000d8f8 @ 0x0000d8f8
 *   __fixunsdfsi                             <= FUN_0000dea8 @ 0x0000dea8
 *   __floatdisf                              <= FUN_0000e128 @ 0x0000e128
 *   battery_soc_from_curve                   <= FUN_0000e340 @ 0x0000e340
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   get_product_code_buf                     <= FUN_000232b8 @ 0x000232b8
 *   esb_send_command_and_wait_ack            <= FUN_00027448 @ 0x00027448
 *   fuel_gauge_read_voltage_current_temp     <= FUN_0002e988 @ 0x0002e988
 *   fuel_gauge_poll_should_stop              <= FUN_00030cac @ 0x00030cac
 *   fuel_gauge_lock                          <= FUN_000330c4 @ 0x000330c4
 *   fuel_gauge_unlock                        <= FUN_000330d8 @ 0x000330d8
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
 *   set_shutdown_flag                        <= FUN_0007cbfe @ 0x0007cbfe
 *   k_uptime_get_3                           <= FUN_0007ceda @ 0x0007ceda
 *   product_code_is_supported_egp_family     <= FUN_0007cefc @ 0x0007cefc
 * address symbols (name @ address):
 *   rodata_a3d37                             @ 0x000a3d37   [INLINED -- G6 literal batch]
 *   rodata_a3d62                             @ 0x000a3d62   [INLINED -- G6 literal batch]
 *   rodata_a3d83                             @ 0x000a3d83   [INLINED -- G6 literal batch]
 *   rodata_a3dae                             @ 0x000a3dae   [INLINED -- G6 literal batch]
 *   rodata_a3e08                             @ 0x000a3e08   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_fuel_gauge_init_timestamp              @ 0x20004790
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_20007b70                               @ 0x20007b70
 *   g_20007b74                               @ 0x20007b74
 *   g_flash_crc_skip_watchdog_flag           @ 0x20018d90
 *   g_20018da2                               @ 0x20018da2
 */
/* Full reconstruction fuel_gauge_update @ 0x10b18. */
#include <stdint.h>
#include <stdbool.h>
#include "../../headers/g1_log.h"
typedef uint8_t undefined1; typedef uint16_t undefined2;
typedef uint32_t undefined4; typedef uint64_t undefined8;
typedef uint8_t byte; typedef int64_t longlong; typedef uint64_t ulonglong; typedef uint32_t uint;
#define NAN(x) __builtin_isnan((x))
#define DAT_00010be4 0.0f
#define DAT_00010be8 1000.0f
#define DAT_00010bec ((int64_t *)((unsigned long)&g_fuel_gauge_init_timestamp) /*=0x20004790*/)
#define DAT_00010bf0 ((unsigned long)"Error: Could not read from charger device\n") /*=0xa3d37*/
#define DAT_00010bf4 100.0f
#define DAT_00010f40 0xd2f1a9fcu
#define DAT_00010f44 0x3fc0624du
#define DAT_00010f48 ((int *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define DAT_00010f4c ((int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define DAT_00010f50 ((unsigned long)"fuel_gauge_update") /*=0xa3e08*/
#define DAT_00010f54 ((unsigned long)"%s(): V: %.3f, I: %.3f, T: %.2f\n") /*=0xa3d62*/
#define DAT_00010f58 100.0f
#define DAT_00010f5c ((int *)((unsigned long)&g_20007b70) /*=0x20007b70*/)
#define DAT_00010f60 ((float *)((unsigned long)&g_20007b74) /*=0x20007b74*/)
#define DAT_00010f64 ((unsigned long)"%s(): Original soc %.2f, New Soc %.2f, %s\n") /*=0xa3d83*/
#define DAT_00010f68 150.0f
#define DAT_00010f6c 93.5f
#define DAT_00010f70 94.0f
#define DAT_00010f74 94.5f
#define DAT_00010f78 95.0f
#define DAT_00010f7c 200.0f
#define DAT_00010f80 ((uint8_t *)((unsigned long)&g_20018da2) /*=0x20018da2*/)
#define DAT_00010f84 0x408f4000u
#define DAT_00010f88 1000.0f
#define DAT_00010f8c 60.0f
#define DAT_00010f90 120.0f
#define DAT_00010f94 (-50.0f)
#define DAT_00010f98 ((unsigned long)"%s(): #############################Abnormal temperature################################\n\n") /*=0xa3dae*/
#define DAT_00010f9c 0x0001d4bfu
#define DAT_00010fa0 ((uint8_t *)((unsigned long)&g_flash_crc_skip_watchdog_flag) /*=0x20018d90*/)
#define DAT_00010fa4 0.0f
extern uint64_t __aeabi_dadd(uint32_t,...); extern uint64_t __extendsfdf2(float);
extern uint64_t __muldf3(uint32_t,...); extern uint8_t __fixunsdfsi(uint32_t,...);
extern float __floatdisf(void); extern float battery_soc_from_curve(float,float,float,float,uint32_t);
extern uint32_t get_device_info(void);
extern uint32_t get_product_code_buf(void); extern uint32_t esb_send_command_and_wait_ack(uintptr_t,...);
extern int fuel_gauge_read_voltage_current_temp(uint32_t,float*,float*,float*); extern int fuel_gauge_poll_should_stop(void);
extern void fuel_gauge_lock(void); extern void fuel_gauge_unlock(void);
extern uint32_t k_sleep(uintptr_t,...); extern uint32_t set_shutdown_flag(uintptr_t,...);
extern int64_t k_uptime_get_3(void); extern uint32_t product_code_is_supported_egp_family(void);
extern uint32_t send_event(uintptr_t,...); extern uint32_t sync_to_slave(uintptr_t,...);

int fuel_gauge_update(undefined4 param_1)

{
  bool bVar1;
  bool bVar2;
  float fVar3;
  longlong *plVar4;
  int *piVar5;
  byte *pbVar6;
  undefined1 uVar7;
  int iVar8;
  undefined4 uVar9;
  char *pcVar10;
  undefined4 uVar11;
  byte bVar12;
  int iVar13;
  float fVar14;
  float fVar15;
  longlong lVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  float local_44;
  float local_40;
  float local_3c [2];

  plVar4 = DAT_00010bec;
  fVar3 = DAT_00010be8;
  iVar13 = 0xb;
  fVar15 = DAT_00010be4;
  while (iVar8 = fuel_gauge_poll_should_stop(), iVar8 == 0) {
    fuel_gauge_lock();
    iVar8 = fuel_gauge_read_voltage_current_temp(param_1,&local_44,&local_40,local_3c);
    fuel_gauge_unlock();
    if (iVar8 < 0) {
      log_message(DAT_00010bf0);
      return iVar8;
    }
    lVar16 = k_uptime_get_3();
    lVar16 = lVar16 - *plVar4;
    if ((int)((ulonglong)lVar16 >> 0x20) < (int)(uint)((uint)lVar16 < 1000)) {
      return -1;
    }
    fVar15 = (float)__floatdisf();
    fVar14 = local_40;
    fVar15 = (float)battery_soc_from_curve(local_44,local_40,local_3c[0],fVar15 / fVar3,0);
    if ((((fVar14 != 0.0) || (iVar13 = iVar13 + -1, iVar13 == 0)) ||
        (-1 < (int)((uint)(fVar15 < DAT_00010bf4) << 0x1f))) ||
       (fVar15 == 0.0 || fVar15 < 0.0 != NAN(fVar15))) {
      lVar16 = k_uptime_get_3();
      *plVar4 = lVar16;
      goto LAB_00010c00;
    }
    k_sleep(0xa4,0);
  }
  if (fVar15 == 0.0 || fVar15 < 0.0 != NAN(fVar15)) {
    return 0;
  }
LAB_00010c00:
  piVar5 = DAT_00010f48;
  if (0 < *DAT_00010f48) {
    uVar17 = __extendsfdf2(local_44);
    uVar11 = (undefined4)((ulonglong)uVar17 >> 0x20);
    uVar18 = __extendsfdf2(local_40);
    uVar19 = __extendsfdf2(local_3c[0]);
    if (*DAT_00010f4c == 0) {
      log_message(DAT_00010f54,DAT_00010f50,(int)uVar17,uVar11,(int)uVar18,
                  (int)((ulonglong)uVar18 >> 0x20),(int)uVar19,(int)((ulonglong)uVar19 >> 0x20));
    }
    else {
      debug_print(DAT_00010f54,DAT_00010f50,(int)uVar17,uVar11);
    }
  }
  iVar13 = k_uptime_get_3();
  fVar3 = DAT_00010f58;
  if (((fVar15 == 0.0) || (*DAT_00010f60 == fVar15)) &&
     (fVar15 < DAT_00010f58 != (NAN(fVar15) || NAN(DAT_00010f58)))) {
    if (DAT_00010f9c < (uint)(iVar13 - *DAT_00010f5c)) {
      *DAT_00010fa0 = 1;
    }
  }
  else {
    *DAT_00010f5c = iVar13;
    *DAT_00010f60 = fVar15;
  }
  iVar13 = product_code_is_supported_egp_family();
  fVar14 = fVar15;
  if (iVar13 != 0) {
    fVar14 = fVar15 * 1.25;
  }
  if (0 < *piVar5) {
    uVar17 = __extendsfdf2(fVar15);
    uVar11 = (undefined4)((ulonglong)uVar17 >> 0x20);
    uVar18 = __extendsfdf2(fVar14);
    if (*DAT_00010f4c == 0) {
      uVar9 = get_product_code_buf();
      log_message(DAT_00010f64,DAT_00010f50,(int)uVar17,uVar11,(int)uVar18,
                  (int)((ulonglong)uVar18 >> 0x20),uVar9);
    }
    else {
      uVar9 = get_product_code_buf();
      debug_print(DAT_00010f64,DAT_00010f50,(int)uVar17,uVar11,uVar18,uVar9);
    }
  }
  fVar15 = DAT_00010fa4;
  if (((((int)((uint)(fVar14 < 0.0) << 0x1f) < 0) ||
       (fVar14 < DAT_00010f68 == (NAN(fVar14) || NAN(DAT_00010f68)))) ||
      (fVar15 = DAT_00010f58, fVar14 < fVar3 == (NAN(fVar14) || NAN(fVar3)))) ||
     (((fVar15 = fVar14, fVar14 < DAT_00010f6c != (NAN(fVar14) || NAN(DAT_00010f6c)) ||
       (-1 < (int)((uint)(fVar14 < DAT_00010f70) << 0x1f))) &&
      ((fVar14 < DAT_00010f74 != (NAN(fVar14) || NAN(DAT_00010f74)) ||
       (-1 < (int)((uint)(fVar14 < DAT_00010f78) << 0x1f))))))) {
    iVar13 = get_device_info();
    uVar7 = 0;
  }
  else {
    iVar13 = get_device_info();
    uVar7 = 1;
  }
  *(undefined1 *)(iVar13 + 0xfc2) = uVar7;
  iVar13 = get_device_info();
  fVar14 = local_44 * fVar3 - DAT_00010f7c;
  *(char *)(iVar13 + 0xfc0) = (0.0 < fVar15) * (char)(int)fVar15;
  iVar13 = get_device_info();
  pbVar6 = DAT_00010f80;
  *(char *)(iVar13 + 0xfc4) = (0.0 < fVar14) * (char)(int)fVar14;
  if (local_40 == 0.0) {
    bVar12 = *pbVar6 + 1;
    if (5 < bVar12) {
      *pbVar6 = 0;
      uVar17 = __extendsfdf2(local_40);
      uVar17 = __aeabi_dadd((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),DAT_00010f40,DAT_00010f44);
      uVar17 = __muldf3((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,DAT_00010f84);
      iVar13 = get_device_info();
      uVar7 = __fixunsdfsi((int)uVar17,(int)((ulonglong)uVar17 >> 0x20));
      fVar15 = local_40 * DAT_00010f88;
      *(undefined1 *)(iVar13 + 0xfc5) = uVar7;
      iVar13 = get_device_info();
      *(char *)(iVar13 + 0xfc8) = (char)(int)fVar15;
      goto LAB_00010dca;
    }
  }
  else {
    uVar17 = __extendsfdf2(local_40);
    uVar17 = __aeabi_dadd((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),DAT_00010f40,DAT_00010f44);
    uVar17 = __muldf3((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,DAT_00010f84);
    iVar13 = get_device_info();
    fVar15 = DAT_00010f88;
    uVar7 = __fixunsdfsi((int)uVar17,(int)((ulonglong)uVar17 >> 0x20));
    *(undefined1 *)(iVar13 + 0xfc5) = uVar7;
    iVar13 = get_device_info();
    *(char *)(iVar13 + 0xfc8) = (char)(int)(local_40 * fVar15);
    bVar12 = 0;
  }
  *pbVar6 = bVar12;
LAB_00010dca:
  iVar13 = get_device_info();
  *(char *)(iVar13 + 0xfc6) = (0.0 < local_3c[0]) * (char)(int)local_3c[0];
  iVar13 = get_device_info();
  bVar1 = local_3c[0] < DAT_00010f8c;
  bVar2 = NAN(DAT_00010f8c);
  *(short *)(iVar13 + 0xfca) = (short)(int)(local_3c[0] * fVar3);
  if ((((bVar1 == (NAN(local_3c[0]) || bVar2)) &&
       ((int)((uint)(local_3c[0] < DAT_00010f90) << 0x1f) < 0)) ||
      ((local_3c[0] < DAT_00010f94 == (NAN(local_3c[0]) || NAN(DAT_00010f94)) &&
       (local_3c[0] <= -20.0)))) && (iVar13 = get_device_info(), *(char *)(iVar13 + 0xfea) != '\f')) {
    send_event(4);
    pcVar10 = (char *)get_device_info();
    if (*pcVar10 == '\x01') {
      uVar11 = get_device_info();
      sync_to_slave(uVar11,4,0);
      uVar11 = get_device_info();
      set_shutdown_flag(uVar11,0);
    }
    else {
      uVar11 = get_device_info();
      esb_send_command_and_wait_ack(uVar11,7,0);
    }
    iVar13 = get_device_info();
    *(undefined1 *)(iVar13 + 0xfea) = 0xc;
    uVar11 = get_device_info();
    set_shutdown_flag(uVar11,1);
    if (0 < *piVar5) {
      if (*DAT_00010f4c == 0) {
        log_message(DAT_00010f98,DAT_00010f50);
      }
      else {
        debug_print(0);
      }
    }
  }
  return 0;
}
