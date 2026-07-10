#include "g1_app_symbols.h"
/* named: rtc_read_extended_cycle_count */
/* globals referenced:
//   0x200066b8  g_rtc_cycle_range_minmax     
//   0x2000b2dc  g_rtc_overflow_hi32          [g_obj_2000b2d0.f_c]
*/
/* Reconstructed rtc_read_extended_cycle_count @ 0x63610  (parity: 300/300 trials, PROVEN) */

unsigned long long rtc_read_extended_cycle_count(void)
{
  unsigned int counterVal = *(volatile unsigned int *)((uintptr_t)&g_uptime_tick_overflow_state) /*=0x2000b2dc*/;
  unsigned int uVar1 = counterVal >> 8;
  unsigned int shifted = counterVal << 24;
  __asm__ volatile("dmb sy" ::: "memory");
  unsigned int uVar3 = *(volatile unsigned int *)REG_50015504 /*=0x50015504*/;
  unsigned int uVar2 = uVar3 + shifted;
  unsigned int carry1 = (uVar2 < uVar3) ? 1 : 0;
  uVar1 = uVar1 + carry1;
  if (uVar3 < FLASH_OFF_100000 /*=0x100000*/) {
    unsigned int lo = *(volatile unsigned int *)((uintptr_t)&g_rtc_cycle_range_minmax) /*=0x200066b8*/;
    unsigned int hi = *(volatile unsigned int *)((uintptr_t)&g_uptime_ref_tick_hi) /*=0x200066bc*/;
    unsigned long long a = ((unsigned long long)uVar1 << 32) | uVar2;
    unsigned long long b = ((unsigned long long)hi << 32) | lo;
    if (a < b) {
      unsigned int old = uVar2;
      uVar2 = uVar2 + 0x1000000;
      unsigned int carry2 = (uVar2 < old) ? 1 : 0;
      uVar1 = uVar1 + carry2;
    }
  }
  return ((unsigned long long)uVar1 << 32) | uVar2;
}

