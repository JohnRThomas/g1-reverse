#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00063570 @ 0x00063570
 * public-name: FUN_00063570
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6659                             @ 0x000f6659
 *   rodata_f668a                             @ 0x000f668a
 */
/* Reconstructed FUN_00063570 @ 0x63570  (parity: 300/300 trials, PROVEN) */

extern void printk(int a, int b, int c, int d, int e);
extern unsigned int assert_post_action(int a, int b);
unsigned int FUN_00063570(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int idx = param_1;
  if (1 < param_1) {
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f668a) /*=0xf668a*/, ((unsigned long)&rodata_f6659) /*=0xf6659*/, 0x86, param_4);
    idx = assert_post_action(((unsigned long)&rodata_f6659) /*=0xf6659*/, 0x86);
  }
  return 0x50015140UL + idx * 4;
}
