#include "g1_app_symbols.h"
/* named: FUN_00063524 */
/* Reconstructed FUN_00063524 @ 0x63524  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void FUN_00063524(unsigned int param_1, int param_2)
{
  if (param_2 != 0) {
    volatile uint32_t *p0 = (volatile uint32_t*)((uintptr_t)&g_gpio_pin_enabled_mask) /*=0x2000b2d8*/;
    *p0 = *p0 | (1u << (param_1 & 0xff));
    *(volatile uint32_t*)(REG_50015000 /*=0x50015000*/ + 0x304) = ((uintptr_t)&tbl_ffc8) /*=0x10000*/ << (param_1 & 0xff);
    uint32_t v = *(volatile uint32_t*)((uintptr_t)&g_gpio_pin_latch_mask) /*=0x2000b2d0*/;
    int iVar2 = (int)((v >> (param_1 & 0xff)) << 0x1f);
    if (iVar2 < 0) {
      *(volatile uint32_t*)(0xe000e100UL + 0x100) = 0x200000;
    }
  }
}

