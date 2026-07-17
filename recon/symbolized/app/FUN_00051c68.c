#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00051c68 @ 0x00051c68
 * public-name: FUN_00051c68
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f2561                             @ 0x000f2561
 *   rodata_f25c5                             @ 0x000f25c5
 *   rodata_f25e2                             @ 0x000f25e2
 */
/* Reconstructed FUN_00051c68 @ 0x51c68  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int, unsigned int, unsigned int, unsigned int);
extern void assert_post_action(unsigned int, unsigned int) __attribute__((noreturn));

void FUN_00051c68(void)
{
  unsigned int uVar1;

  uVar1 = ((unsigned long)&rodata_f2561) /*=0xf2561*/;
  printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f25c5) /*=0xf25c5*/,((unsigned long)&rodata_f2561) /*=0xf2561*/,0x62);
  printk(((unsigned long)&rodata_f25e2) /*=0xf25e2*/,0,0,0);
  assert_post_action(uVar1,0x62);
}
