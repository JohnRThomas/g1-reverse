#include "g1_app_symbols.h"
/* named: cpu_idle_wfi_gate_check */
/* Reconstructed cpu_idle_wfi_gate_check @ 0x4c1f0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int sys_clock_cycle_get_32(void);
uint32_t cpu_idle_wfi_gate_check(void){
  volatile uint8_t *pbVar2 = (volatile uint8_t*)((uintptr_t)&g_analytics_evt_buf_idx) /*=0x2001d44a*/;
  uint32_t iVar3 = ((uintptr_t)&g_analytics_evt_tick_buf) /*=0x2000a0b4*/;
  volatile uint8_t *pcVar4 = (volatile uint8_t*)((uintptr_t)&g_analytics_evt_hist_ready) /*=0x2001d449*/;
  uint32_t uVar7 = ((uint32_t)*pbVar2 + 1) % 5;
  int iVar5 = sys_clock_cycle_get_32();
  int enter;
  if(*pcVar4 == 0){
    enter = 1;
  } else {
    uint32_t diff = (uint32_t)(iVar5 - *(volatile int*)(iVar3 + uVar7*4));
    enter = (diff > 7);
  }
  if(!enter){
    return 0;
  }
  if(*(volatile uint32_t*)REG_50005114 /*=0x50005114*/ != 0){
    *(volatile uint32_t*)REG_50005114 /*=0x50005114*/ = 0;
    (void)*(volatile uint32_t*)REG_50005114 /*=0x50005114*/;
    *pbVar2 = (uint8_t)uVar7;
    if(uVar7 == 0){
      *pcVar4 = 1;
    }
  }
  uint8_t bVar1 = *pbVar2;
  uint32_t uVar6 = sys_clock_cycle_get_32();
  *(volatile uint32_t*)(iVar3 + (uint32_t)bVar1*4) = uVar6;
  return 1;
}

