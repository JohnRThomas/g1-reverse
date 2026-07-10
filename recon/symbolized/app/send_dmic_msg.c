#include "g1_app_symbols.h"
/* named: send_dmic_msg */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed send_dmic_msg @ 0x19ed4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned,...);
extern int get_device_info(void);
extern void debug_print(unsigned,...);
extern int get_dmic_msgq_count(void);
extern int dequeue_dmic(void*);
extern void set_shutdown_flag(int,int);
extern void memset_bytes(void*,int,int);
extern unsigned long long thunk_FUN_00074f68(void);
typedef int (*cf)(void*,int);
int send_dmic_msg(int param_1)
{
  unsigned char bVar1; volatile unsigned char *pbVar3; volatile int *piVar4; int iVar5, iVar8;
  unsigned local_e4; unsigned char auStack_e0[204];
  local_e4 = 0;
  memset_bytes(auStack_e0, 0, 199);
  piVar4 = (volatile int*)((uintptr_t)&g_dmic_send_fail_cnt) /*=0x20007558*/;
  pbVar3 = (volatile unsigned char*)((uintptr_t)&g_dmic_msg_seq) /*=0x20010321*/;
  ((unsigned char*)&local_e4)[0] = 0xf1;
  do {
    ((unsigned char*)&local_e4)[1] = *pbVar3;
    iVar5 = get_dmic_msgq_count();
    if (iVar5 == 0) return 0;
    iVar5 = dequeue_dmic((char*)&local_e4 + 2);
    if (iVar5 != 0) return iVar5;
    iVar5 = (*(cf*)(param_1 + 0xc))(&local_e4, 0xca);
    if ((iVar5 < 0) && (iVar8 = *piVar4, *piVar4 = iVar8 + 1, 9 < iVar8 + 1)) {
      unsigned uVar6 = get_device_info();
      set_shutdown_flag(uVar6, 1);
      if (0 < *(int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
        if (*(int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) DEBUG_PRINT("%s(): BLE send failed for %d times\n" /*=0x9b45e*/, "send_dmic_msg" /*=0x9e0a4*/, *piVar4);
        else debug_print("%s(): BLE send failed for %d times\n" /*=0x9b45e*/, "send_dmic_msg" /*=0x9e0a4*/, *piVar4);
      }
      *piVar4 = 0;
      return iVar5;
    }
    if (*(int*)((uintptr_t)&g_dmic_send_pos_cnt) /*=0x2000755c*/ + 1 < 100) {
      *(volatile int*)((uintptr_t)&g_dmic_send_pos_cnt) /*=0x2000755c*/ = *(int*)((uintptr_t)&g_dmic_send_pos_cnt) /*=0x2000755c*/ + 1;
    } else {
      *(volatile int*)((uintptr_t)&g_dmic_send_pos_cnt) /*=0x2000755c*/ = 0;
      unsigned long long uVar10 = thunk_FUN_00074f68();
      iVar5 = *(int*)((uintptr_t)&g_dmic_send_hundreds_cnt) /*=0x20007560*/;
      *(volatile int*)((uintptr_t)&g_dmic_send_hundreds_cnt) /*=0x20007560*/ = iVar5 + 1;
      if (0 < *(int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
        if (*(int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
          DEBUG_PRINT("%s(): dmic_send_count %d send_fail_count %d time %lld\n" /*=0x9b482*/, "send_dmic_msg" /*=0x9e0a4*/, (iVar5 + 1) * 100, *piVar4, (unsigned)uVar10, (unsigned)(uVar10 >> 32));
        else debug_print("%s(): dmic_send_count %d send_fail_count %d time %lld\n" /*=0x9b482*/);
      }
    }
    bVar1 = *pbVar3;
    *pbVar3 = bVar1 + 1;
  } while (((bVar1 + 1) & 3) != 0);
  return 0;
}

