#include "g1_app_symbols.h"
/* named: process_for_message_show */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed process_for_message_show @ 0x2c714  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char byte; typedef unsigned char undefined1; typedef uint32_t undefined4; typedef unsigned int uint;
extern int DEBUG_PRINT(int,...);
extern int get_device_info(int,...);
extern int debug_print(int,...);
extern int update_temp_task_status(int,...);
extern int update_persist_task_status_to_idle(void*,...);
extern int get_message_type_param(int,...);
extern int FUN_00033c04(int,...);
extern int FUN_00034410(int,...);
extern int FUN_0003443c(int,...);
extern int is_msg_expiration(int,...);
extern int sync_to_slave(void*,...);
extern int thunk_FUN_00074844(int,...);

undefined4 process_for_message_show(char *param_1,int param_2,byte *param_3,undefined4 *param_4)
{
  byte bVar1; volatile int *piVar2; undefined1 uVar3; int iVar4=0; char *pcVar5;
  undefined4 uVar6; byte bVar7; short sVar8; uint uVar9; int bVar10;
  sVar8 = 1000;
  do {
    iVar4 = get_device_info(0);
    if (*(char *)(iVar4 + 0xdd) == '\0') break;
    iVar4 = get_device_info(0);
    iVar4 = FUN_00033c04(*(byte *)(iVar4 + 0xdd) - 1);
    if (iVar4 == 4) break;
    sVar8 = sVar8 + -1;
    thunk_FUN_00074844(0x21,0);
  } while (sVar8 != 0);
  uVar9 = 0;
  *(undefined1 *)(param_2 + 8) = 0;
  FUN_0003443c(4);
  uVar3 = get_message_type_param(param_1[0xfea],0xf);
  piVar2 = (volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
  *(undefined1 *)(param_2 + 7) = uVar3;
  do {
    while( 1 ) {
      if (param_1[0x108f] == '\0') { bVar10 = *param_3 == 1; }
      else { iVar4 = is_msg_expiration(0); bVar10 = iVar4 == 2; }
      if (((bVar10) || (*(char *)(param_2 + 7) == '\0')) && (param_1[0xfea] == '\n')) break;
      if (((param_1[1] == '\x01') || (iVar4 = get_device_info(0), *(char *)(iVar4 + 1) == '\b')) ||
         (iVar4 = get_device_info(0), *(char *)(iVar4 + 0xfea) == '\f')) {
        if (2 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
          if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT("%s(): #2 %d: I will go to suspend, goodbye!\n" /*=0xa294a*/,"process_for_message_show" /*=0xa39d6*/,(uint)*(byte *)(param_2 + 1));
          } else { debug_print(0); }
        }
        update_persist_task_status_to_idle(param_1);
        *param_4 = "imu-trigger-off-imm" /*=0xa3311*/;
        FUN_0003443c(5);
        return 10;
      }
      if (*(char *)(param_2 + 1) != '\x04') {
        if (2 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
          if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT("%s(): #3 %d: screen_id is changed, I will go to next screen, goodbye!\n" /*=0xa2977*/,"process_for_message_show" /*=0xa39d6*/,(uint)*(byte *)(param_2 + 1));
          } else { debug_print(0); }
        }
        if (*(char *)(param_2 + 1) != '\0') { return 0xb; }
        goto LAB_0002c884;
      }
      uVar9 = uVar9 + 1;
      if (((uVar9 & 0xf) == 0) && (2 < *piVar2)) {
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
          DEBUG_PRINT(((uintptr_t)&rodata_a29be) /*=0xa29be*/,"process_for_message_show" /*=0xa39d6*/,uVar9,**(undefined4 **)(param_1 + 0xff0),
                      (uint)*param_3,(uint)*(byte *)(param_2 + 9),(uint)*(byte *)(param_2 + 0xf),
                      *(undefined4 *)(param_2 + 0xb),(uint)*(byte *)(param_2 + 8));
        } else { debug_print(0); }
      }
      if (((param_1[0x108f] != '\0') && (*param_1 == '\x01')) &&
         (((uVar9 * 0xcccccccdU >> 2 | uVar9 * 0x40000000) ) <= 0x0ccccccc)) {
        bVar1 = *(byte *)(param_2 + 7);
        bVar7 = bVar1;
        if (bVar1 < 0x14) { bVar7 = bVar1 - 1; }
        if (bVar1 < 0x14) { *(byte *)(param_2 + 7) = bVar7; }
      }
LAB_0002c894:
      thunk_FUN_00074844(0x667,0);
    }
    if ((*(char *)(param_2 + 1) == '\x06') ||
       ((*(char *)(param_2 + 1) != '\x06' && (*param_3 == 2)))) {
      iVar4 = get_device_info(0);
      if ((*(char *)(iVar4 + 0x108f) != '\0') &&
         (pcVar5 = (char *)get_device_info(0), *pcVar5 == '\x01')) {
        iVar4 = get_device_info(0);
        uVar9 = *(uint *)(iVar4 + 0x1060);
        *(uint *)(iVar4 + 0x1060) = uVar9 - 1000;
        *(uint *)(iVar4 + 0x1064) = *(int *)(iVar4 + 0x1064) + -1 + (uint)(999 < uVar9);
      }
      sync_to_slave(param_1,0xc,0);
      uVar6 = get_device_info(0);
      update_temp_task_status(uVar6,6,2);
      if (2 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
          DEBUG_PRINT("%s(): #0 %d: I will go to dashboard, goodbye!\n" /*=0xa28ee*/,"process_for_message_show" /*=0xa39d6*/,(uint)*(byte *)(param_2 + 1));
        } else { debug_print(0); }
      }
      return 0xb;
    }
    sync_to_slave(param_1,8,0);
    if (*param_1 == '\x01') { update_persist_task_status_to_idle(param_1); }
    else if (*(char *)(param_2 + 1) == '\x04') goto LAB_0002c894;
    FUN_0003443c(5);
    if (*param_1 == '\x01') { thunk_FUN_00074844(0x4000,0); }
    iVar4 = FUN_00034410(0);
  } while (iVar4 == 4);
  if (2 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
    if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
      DEBUG_PRINT("%s(): #1 %d: I will go to suspend, goodbye!\n" /*=0xa291d*/,"process_for_message_show" /*=0xa39d6*/,(uint)*(byte *)(param_2 + 1));
    } else { debug_print(0); }
  }
LAB_0002c884:
  *param_4 = "imu-trigger-off-imm" /*=0xa3311*/;
  return 10;
}

