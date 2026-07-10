#include "g1_app_symbols.h"
/* named: nrfx_clock_irq_enable */
/* globals referenced:
//   0x2000b31c  g_clock_cb                   
*/
/* Reconstructed nrfx_clock_irq_enable @ 0x651d8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void printk(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern void assert_post_action(unsigned int, unsigned int);
extern int arch_irq_is_enabled(int);
extern void arch_irq_enable(int);

void nrfx_clock_irq_enable(void)
{
  if (*(volatile char*)(((uintptr_t)&g_clock_cb) /*=0x2000b31c*/ + 4) == 0) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "m_clock_cb.module_initialized" /*=0xf6acd*/, "WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_clock.c" /*=0xf6a4e*/, 0x12e, 0);
    assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_clock.c" /*=0xf6a4e*/, 0x12e);
  }
  int iVar1 = arch_irq_is_enabled(5);
  if (iVar1 == 0) {
    arch_irq_enable(5);
  }
  *(volatile uint32_t*)REG_50005518 /*=0x50005518*/ = 1;
  *(volatile uint32_t*)REG_50005514 /*=0x50005514*/ = 1;
  *(volatile uint32_t*)REG_50005580 /*=0x50005580*/ = 1;
}

