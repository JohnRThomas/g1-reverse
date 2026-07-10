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
  volatile int *piVar1 = (volatile int*)0x2000230cUL;
  volatile int *g50   = (volatile int*)0x20007554UL;
  volatile int *puVar3= (volatile int*)0x00087cc8UL;
  volatile int *piVar4= (volatile int*)0x20007b50UL;
  int iVar5, uVar6, fmt, iVar7;
  int st[8];
  (void)param_1;(void)param_2;(void)param_3;(void)param_4;

  if (3 < *piVar1) { if (*g50==0) DEBUG_PRINT(0x000a1b10,0x000a1c96); else debug_print(); }
  iVar5 = z_device_is_ready(0x00087cc8);
  if (iVar5 == 0) {
    if (0 < *piVar1) { if (*g50==0) DEBUG_PRINT(0x000a1b33,0x000a1c96,*puVar3); else debug_print(); }
    return 0;
  }
  memset_bytes((void*)st,0,0x10);
  if (3 < *piVar1) { if (*g50==0) DEBUG_PRINT(0x000a1b50,0x000a1c96); else debug_print(); }
  iVar7 = puVar3[2];
  iVar5 = ((fp_t)(*(volatile int*)(iVar7+8)))(0x00087cc8, (int)st);
  *piVar4 = iVar5;
  if (iVar5 == -0x86) {
    if (0 < *piVar1) { if (*g50==0) DEBUG_PRINT(0x000a1b88,0x000a1c96); else debug_print(); }
    iVar7 = puVar3[2];
    iVar5 = ((fp_t)(*(volatile int*)(iVar7+8)))(0x00087cc8, (int)st);
    *piVar4 = iVar5;
  }
  if (*piVar4 < 0) {
    if (*piVar1 < 1) return 0;
    iVar5 = *g50; uVar6 = 0x000a1bbc;
  } else {
    iVar7 = puVar3[2];
    iVar5 = ((fp_t)(*(volatile int*)iVar7))(0x00087cc8, 2);
    if (iVar5 < 0) {
      if (*piVar1 < 1) return 0;
      iVar5 = *g50; uVar6 = 0x000a1bda;
    } else {
      if (3 < *piVar1) { if (*g50==0) DEBUG_PRINT(0x000a1bf6,0x000a1c96,5); else debug_print(); }
      fmt = 0x000a1c17;
      iVar5 = 5;
      do {
        if (3 < *piVar1) { if (*g50==0) DEBUG_PRINT(fmt,0x000a1c96); else debug_print(); }
        iVar7 = puVar3[2];
        if (((fp_t)(*(volatile int*)(iVar7+0xc)))(0x00087cc8, *piVar4) == 0) break;
        FUN_00074844(0x667,0);
        iVar5 = iVar5 - 1;
      } while (iVar5 != 0);
      if (*piVar1 < 4) return 0;
      iVar5 = *g50; uVar6 = 0x000a1c32;
    }
  }
  if (iVar5 == 0) DEBUG_PRINT(uVar6,0x000a1c96); else debug_print();
  return 0;
}

