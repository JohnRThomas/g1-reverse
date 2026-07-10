#include "g1_app_symbols.h"
/* named: ble_whitelist_app */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed ble_whitelist_app @ 0x22218  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t undefined4; typedef unsigned int uint; typedef unsigned char byte;
extern int DEBUG_PRINT(int,...); extern int strcmp(int,...); extern int get_device_info(int,...);
extern int debug_print(int,...); extern int get_app_whitelist_buffer(int,...);
typedef int (*codeptr)(int,...);

int ble_whitelist_app(undefined4 param_1,undefined4 param_2,codeptr param_3,undefined4 param_4)
{
  int iVar1; undefined4 uVar2; undefined4 uVar3; uint *puVar4; uint uVar5; int iVar6;
  iVar1 = strcmp(param_1,"ble_whitelist_app" /*=0x9e1a8*/);
  if (iVar1 == 0) {
    uVar2 = get_app_whitelist_buffer(0); uVar3 = 0x15e2;
LAB_2232:
    iVar1 = (*param_3)(param_4,uVar2,uVar3);
    if (-1 < iVar1) return 0;
    iVar6 = *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
LAB_2270:
    if (iVar6 < 2) return iVar1;
    if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) { DEBUG_PRINT("%s(): Failed to read %s, error: %d\n" /*=0x9e1ba*/,"sett_handler" /*=0x9e53c*/,param_1,iVar1); return iVar1; }
    debug_print("%s(): Failed to read %s, error: %d\n" /*=0x9e1ba*/,"sett_handler" /*=0x9e53c*/,param_1,iVar1);
    return iVar1;
  }
  iVar1 = strcmp(param_1,"dashboard_ts" /*=0x9e1de*/);
  if (iVar1 == 0) {
    iVar1 = get_device_info(0);
    if (*(int *)(iVar1 + 0xfec) == 0) return 0;
    iVar1 = get_device_info(0);
    iVar1 = (*param_3)(param_4,*(undefined4 *)(iVar1 + 0xfec),0x6a);
    iVar6 = *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
    if (iVar1 < 0) goto LAB_2270;
    if (iVar6 < 3) return 0;
    if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
      iVar1 = get_device_info(0); puVar4 = *(uint **)(iVar1 + 0xfec);
LAB_22b4: uVar5 = *puVar4;
LAB_22b6: DEBUG_PRINT("%s(): key:%s, val=%d\n" /*=0x9e1eb*/,"sett_handler" /*=0x9e53c*/,param_1,uVar5); return 0;
    }
    iVar1 = get_device_info(0); puVar4 = *(uint **)(iVar1 + 0xfec);
  } else {
    iVar1 = strcmp(param_1,"countdown_ts" /*=0x9e201*/);
    if (iVar1 != 0) {
      iVar1 = strcmp(param_1,"first_enter_flag" /*=0x9e20e*/);
      if (iVar1 == 0) {
        iVar1 = get_device_info(0);
        iVar1 = (*param_3)(param_4,iVar1 + 0x1050,4);
        iVar6 = *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
        if (iVar1 < 0) goto LAB_2270;
        if (iVar6 < 3) return 0;
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ != 0) { iVar1 = get_device_info(0); uVar5 = *(uint *)(iVar1 + 0x1050); goto LAB_22a0; }
        iVar1 = get_device_info(0); uVar5 = *(uint *)(iVar1 + 0x1050); goto LAB_22b6;
      }
      iVar1 = strcmp(param_1,"brightness_level" /*=0x9e21f*/);
      if (iVar1 == 0) {
        iVar1 = get_device_info(0);
        iVar1 = (*param_3)(param_4,iVar1 + 0xed5,1);
        iVar6 = *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
        if (iVar1 < 0) goto LAB_2270;
        if (iVar6 < 3) return 0;
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) { iVar1 = get_device_info(0); uVar5 = (uint)*(byte *)(iVar1 + 0xed5); goto LAB_22b6; }
        iVar1 = get_device_info(0); uVar5 = (uint)*(byte *)(iVar1 + 0xed5); goto LAB_22a0;
      }
      iVar1 = strcmp(param_1,"3dof_enable" /*=0x9e230*/);
      if (iVar1 == 0) {
        iVar1 = get_device_info(0);
        iVar1 = (*param_3)(param_4,iVar1 + 0xf60,1);
        iVar6 = *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
        if (iVar1 < 0) goto LAB_2270;
        if (iVar6 < 3) return 0;
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) { iVar1 = get_device_info(0); uVar5 = (uint)*(byte *)(iVar1 + 0xf60); goto LAB_22b6; }
        iVar1 = get_device_info(0); uVar5 = (uint)*(byte *)(iVar1 + 0xf60); goto LAB_22a0;
      }
      iVar1 = strcmp(param_1,"display_mode" /*=0x9e23c*/);
      if (iVar1 == 0) {
        iVar1 = get_device_info(0);
        iVar1 = (*param_3)(param_4,iVar1 + 0xfea,1);
        iVar6 = *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
        if (iVar1 < 0) goto LAB_2270;
        if (iVar6 < 3) return 0;
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) { iVar1 = get_device_info(0); uVar5 = (uint)*(byte *)(iVar1 + 0xfea); goto LAB_22b6; }
        iVar1 = get_device_info(0); uVar5 = (uint)*(byte *)(iVar1 + 0xfea); goto LAB_22a0;
      }
      iVar1 = strcmp(param_1,"runtime_mode" /*=0x990cf*/);
      if (iVar1 == 0) {
        iVar1 = get_device_info(0);
        iVar1 = (*param_3)(param_4,iVar1 + 1);
        iVar6 = *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
        if (iVar1 < 0) goto LAB_2270;
        if (iVar6 < 3) return 0;
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) { iVar1 = get_device_info(0); uVar5 = (uint)*(byte *)(iVar1 + 1); goto LAB_22b6; }
        iVar1 = get_device_info(0); uVar5 = (uint)*(byte *)(iVar1 + 1); goto LAB_22a0;
      }
      iVar1 = strcmp(param_1,"user_sched_info" /*=0x9e249*/);
      if (iVar1 != 0) {
        iVar1 = strcmp(param_1,"wakeup_angle" /*=0x9e259*/);
        if (iVar1 != 0) return 0;
        iVar1 = get_device_info(0);
        iVar1 = (*param_3)(param_4,iVar1 + 0xef4,1);
        iVar6 = *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
        if (iVar1 < 0) goto LAB_2270;
        if (iVar6 < 3) return 0;
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) { iVar1 = get_device_info(0); uVar5 = (uint)*(byte *)(iVar1 + 0xef4); goto LAB_22b6; }
        iVar1 = get_device_info(0); uVar5 = (uint)*(byte *)(iVar1 + 0xef4); goto LAB_22a0;
      }
      iVar1 = get_device_info(0);
      if (*(int *)(iVar1 + 0xff4) == 0) return 0;
      iVar1 = get_device_info(0);
      uVar3 = 0x16a; uVar2 = *(undefined4 *)(iVar1 + 0xff4);
      goto LAB_2232;
    }
    iVar1 = get_device_info(0);
    if (*(int *)(iVar1 + 0xff0) == 0) return 0;
    iVar1 = get_device_info(0);
    iVar1 = (*param_3)(param_4,*(undefined4 *)(iVar1 + 0xff0),7);
    iVar6 = *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
    if (iVar1 < 0) goto LAB_2270;
    if (iVar6 < 3) return 0;
    if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) { iVar1 = get_device_info(0); puVar4 = *(uint **)(iVar1 + 0xff0); goto LAB_22b4; }
    iVar1 = get_device_info(0); puVar4 = *(uint **)(iVar1 + 0xff0);
  }
  uVar5 = *puVar4;
LAB_22a0:
  debug_print("%s(): key:%s, val=%d\n" /*=0x9e1eb*/,"sett_handler" /*=0x9e53c*/,param_1,uVar5);
  return 0;
}

