#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00051c38 @ 0x00051c38
 * public-name: img_mgmt_get_opposite_slot
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   img_mgmt_get_opposite_slot               <= FUN_00051c38 @ 0x00051c38
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f2561                             @ 0x000f2561
 *   rodata_f25c5                             @ 0x000f25c5   [INLINED -- G6 literal batch]
 *   rodata_f25e2                             @ 0x000f25e2   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_00051c38 @ 0x51c38  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int, unsigned int, unsigned int, unsigned int);
extern void assert_post_action(unsigned int, unsigned int) __attribute__((noreturn));

void img_mgmt_get_opposite_slot(void)
{
  unsigned int uVar1;

  uVar1 = ((unsigned long)&rodata_f2561) /*=0xf2561*/;
  printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"slot >= 0 && slot < (2 << 1)") /*=0xf25c5*/,((unsigned long)&rodata_f2561) /*=0xf2561*/,0x71);
  printk(((unsigned long)"\tImpossible slot number\n") /*=0xf25e2*/,0,0,0);
  assert_post_action(uVar1,0x71);
}
