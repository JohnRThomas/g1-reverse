#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004c1f0 @ 0x0004c1f0
 * public-name: cpu_idle_wfi_gate_check
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cpu_idle_wfi_gate_check                  <= FUN_0004c1f0 @ 0x0004c1f0
 *   sys_clock_cycle_get_32                   <= FUN_00084c76 @ 0x00084c76
 * address symbols (name @ address):
 *   g_analytics_evt_tick_buf                 @ 0x2000a0b4
 *   g_analytics_evt_hist_ready               @ 0x2001d449
 *   g_analytics_evt_buf_idx                  @ 0x2001d44a
 *   REG_50005114                             @ 0x50005114
 */
/* Reconstructed FUN_0004c1f0 @ 0x4c1f0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern uint32_t sys_clock_cycle_get_32(void);
uint32_t cpu_idle_wfi_gate_check(void){
  volatile uint8_t *pbVar2 = (volatile uint8_t*)((unsigned long)&g_analytics_evt_buf_idx) /*=0x2001d44a*/;
  uint32_t iVar3 = ((unsigned long)&g_analytics_evt_tick_buf) /*=0x2000a0b4*/;
  volatile uint8_t *pcVar4 = (volatile uint8_t*)((unsigned long)&g_analytics_evt_hist_ready) /*=0x2001d449*/;
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
