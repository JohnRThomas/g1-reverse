#include "g1_app_symbols.h"
/* named: init_watchdog */
/* globals referenced:
//   0x00087cc8  g_watchdog_device            
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed init_watchdog @ 0x2ace0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(int,...);
extern void debug_print(void);
extern int  FUN_00074844(int,int);
extern int  z_device_is_ready(int);
extern void memset_bytes(void*,int,int);
typedef int (*fp_t)(int,int);

int init_watchdog(int param_1,int param_2,int param_3,int param_4){
  volatile int *piVar1 = (volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
  volatile int *g50   = (volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
  volatile int *puVar3= (volatile int*)((uintptr_t)&g_watchdog_device) /*=0x87cc8*/;
  volatile int *piVar4= (volatile int*)((uintptr_t)&g_wdt_channel_id) /*=0x20007b50*/;
  int iVar5, uVar6, fmt, iVar7;
  int st[8];
  (void)param_1;(void)param_2;(void)param_3;(void)param_4;

  if (3 < *piVar1) { if (*g50==0) DEBUG_PRINT("%s(): Watchdog sample application\n" /*=0xa1b10*/,"init_watchdog" /*=0xa1c96*/); else debug_print(); }
  iVar5 = z_device_is_ready(((uintptr_t)&g_watchdog_device) /*=0x87cc8*/);
  if (iVar5 == 0) {
    if (0 < *piVar1) { if (*g50==0) DEBUG_PRINT("%s(): %s: device not ready.\n" /*=0xa1b33*/,"init_watchdog" /*=0xa1c96*/,*puVar3); else debug_print(); }
    return 0;
  }
  memset_bytes((void*)st,0,0x10);
  if (3 < *piVar1) { if (*g50==0) DEBUG_PRINT("%s(): Callback in RESET_SOC disabled for this platform\n" /*=0xa1b50*/,"init_watchdog" /*=0xa1c96*/); else debug_print(); }
  iVar7 = puVar3[2];
  iVar5 = ((fp_t)(*(volatile int*)(iVar7+8)))(((uintptr_t)&g_watchdog_device) /*=0x87cc8*/, (int)st);
  *piVar4 = iVar5;
  if (iVar5 == -0x86) {
    if (0 < *piVar1) { if (*g50==0) DEBUG_PRINT("%s(): Callback support rejected, continuing anyway\n" /*=0xa1b88*/,"init_watchdog" /*=0xa1c96*/); else debug_print(); }
    iVar7 = puVar3[2];
    iVar5 = ((fp_t)(*(volatile int*)(iVar7+8)))(((uintptr_t)&g_watchdog_device) /*=0x87cc8*/, (int)st);
    *piVar4 = iVar5;
  }
  if (*piVar4 < 0) {
    if (*piVar1 < 1) return 0;
    iVar5 = *g50; uVar6 = "%s(): Watchdog install error\n" /*=0xa1bbc*/;
  } else {
    iVar7 = puVar3[2];
    iVar5 = ((fp_t)(*(volatile int*)iVar7))(((uintptr_t)&g_watchdog_device) /*=0x87cc8*/, 2);
    if (iVar5 < 0) {
      if (*piVar1 < 1) return 0;
      iVar5 = *g50; uVar6 = "%s(): Watchdog setup error\n" /*=0xa1bda*/;
    } else {
      if (3 < *piVar1) { if (*g50==0) DEBUG_PRINT("%s(): Feeding watchdog %d times\n" /*=0xa1bf6*/,"init_watchdog" /*=0xa1c96*/,5); else debug_print(); }
      fmt = "%s(): Feeding watchdog...\n" /*=0xa1c17*/;
      iVar5 = 5;
      do {
        if (3 < *piVar1) { if (*g50==0) DEBUG_PRINT(fmt,"init_watchdog" /*=0xa1c96*/); else debug_print(); }
        iVar7 = puVar3[2];
        if (((fp_t)(*(volatile int*)(iVar7+0xc)))(((uintptr_t)&g_watchdog_device) /*=0x87cc8*/, *piVar4) == 0) break;
        FUN_00074844(0x667,0);
        iVar5 = iVar5 - 1;
      } while (iVar5 != 0);
      if (*piVar1 < 4) return 0;
      iVar5 = *g50; uVar6 = "%s(): Waiting for reset...\n" /*=0xa1c32*/;
    }
  }
  if (iVar5 == 0) DEBUG_PRINT(uVar6,"init_watchdog" /*=0xa1c96*/); else debug_print();
  return 0;
}

