#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000651d8 @ 0x000651d8
 * public-name: nrfx_clock_enable
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arch_irq_enable                          <= FUN_000500ac @ 0x000500ac
 *   arch_irq_is_enabled                      <= FUN_000500f0 @ 0x000500f0
 *   nrfx_clock_enable                        <= FUN_000651d8 @ 0x000651d8
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f6a4e                             @ 0x000f6a4e
 *   rodata_f6acd                             @ 0x000f6acd
 *   g_clock_cb                               @ 0x2000b31c
 *   REG_50005514                             @ 0x50005514
 *   REG_50005518                             @ 0x50005518
 *   REG_50005580                             @ 0x50005580
 */
/* Reconstructed FUN_000651d8 @ 0x651d8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
#include "../../../headers/g1_log.h"
extern void assert_post_action(unsigned int, unsigned int);
extern int arch_irq_is_enabled(int);
extern void arch_irq_enable(int);

void nrfx_clock_enable(void)
{
  if (*(volatile char*)(((unsigned long)&g_clock_cb) /*=0x2000b31c*/ + 4) == 0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f6acd) /*=0xf6acd*/, ((unsigned long)&rodata_f6a4e) /*=0xf6a4e*/, 0x12e, 0);
    assert_post_action(((unsigned long)&rodata_f6a4e) /*=0xf6a4e*/, 0x12e);
  }
  int iVar1 = arch_irq_is_enabled(5);
  if (iVar1 == 0) {
    arch_irq_enable(5);
  }
  *(volatile uint32_t*)REG_50005518 /*=0x50005518*/ = 1;
  *(volatile uint32_t*)REG_50005514 /*=0x50005514*/ = 1;
  *(volatile uint32_t*)REG_50005580 /*=0x50005580*/ = 1;
}
