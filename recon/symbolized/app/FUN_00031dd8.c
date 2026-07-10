#include "g1_app_symbols.h"
/* named: FUN_00031dd8 */
/* globals referenced:
//   0x20007aa8  device_info.app_switch_pending_flag [g_device_info+0x10ac (new field, not yet in device_info.h)]
//   0x20019ef3  g_test_mode_flag             
*/
/* Reconstructed FUN_00031dd8 @ 0x31dd8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned,...);
extern int get_device_info(void);
extern void build_and_send_device_status_report(unsigned,int);
extern int read_sys_settting_from_flash(void*);
extern void k_msleep_ticks32768_b(int);
extern void memset_bytes(void*,int,int);
extern void vdprintf_to_fd(void*,int,int,unsigned,int);
unsigned FUN_00031dd8(unsigned param_1, unsigned param_2, unsigned **param_3, unsigned char *param_4)
{
  int *piVar1; int iVar2, iVar4; unsigned uVar3; unsigned char *puVar5; unsigned char uVar6; char cVar7;
  unsigned local_b0; unsigned char auStack_ac[16]; unsigned char auStack_9c[12]; int local_90;
  DEBUG_PRINT("join in set_imu_base\n" /*=0xa715d*/);
  if ((param_3 == 0) || (param_4 == 0)) { DEBUG_PRINT("set_imu_base para is NULL\n" /*=0xa7173*/); return 0xffffffff; }
  if (*(char*)((uintptr_t)&g_test_mode_flag) /*=0x20019ef3*/ != 1) { DEBUG_PRINT("warning: not test mode,disable setting\n" /*=0xa672f*/); return 0xfffffffe; }
  puVar5 = (unsigned char*)*param_3;
  *(volatile unsigned char*)(puVar5) = 0x2d;
  *(volatile unsigned char*)(puVar5+2) = 3;
  *(volatile unsigned char*)(puVar5+3) = 5;
  *(volatile unsigned char*)(puVar5+1) = 1;
  piVar1 = (int*)((uintptr_t)&g_ble_switch_status_reason) /*=0x20007aac*/;
  local_b0 = 0;
  memset_bytes(auStack_ac, 0, 0x10);
  if ((((*(int*)((uintptr_t)&g_app_switch_pending_flag) /*=0x20007aa8*/ == 0 && *piVar1 == 0) && *(int*)((uintptr_t)&g_dashboard_lock_pending_flag) /*=0x20007aa4*/ == 0) &&
       (iVar2 = get_device_info(), *(int*)(iVar2+0x107c) == 0)) &&
      (iVar2 = get_device_info(), *(int*)(iVar2+0x1080) == 0)) {
    iVar2 = get_device_info();
    uVar6 = 1;
    if (*(int*)(iVar2+0x1084) == 0) goto LAB_6e;
  }
  iVar2 = get_device_info();
  uVar6 = 0;
  *(volatile int*)(iVar2+0xf64) = *piVar1;
LAB_6e:
  iVar2 = *piVar1;
  *(volatile unsigned char*)(puVar5+4) = uVar6;
  vdprintf_to_fd(&local_b0, 0, 0x14, "base: %d" /*=0x9ddbf*/, iVar2);
  iVar2 = get_device_info();
  cVar7 = 0;
  *(volatile unsigned*)(puVar5+5) = *(unsigned*)(iVar2+0xf64);
  uVar3 = get_device_info();
  build_and_send_device_status_report(uVar3, 0);
  iVar2 = get_device_info();
  iVar2 = *(int*)(iVar2+0xf64);
  do {
    iVar4 = read_sys_settting_from_flash(auStack_9c);
    if ((iVar4 == 0) && (local_90 == iVar2)) goto LAB_c0;
    cVar7 = cVar7 + 1;
    k_msleep_ticks32768_b(100);
  } while (cVar7 != 5);
  *(volatile unsigned char*)(puVar5+4) = 2;
LAB_c0:
  *(volatile unsigned char*)param_4 = 9;
  return 0;
}

