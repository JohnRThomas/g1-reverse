#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00064fa8 @ 0x00064fa8
 * public-name: FUN_00064fa8
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6a09                             @ 0x000f6a09
 *   rodata_f6a46                             @ 0x000f6a46
 */
/* Reconstructed FUN_00064fa8 @ 0x64fa8  (parity: 300/300 trials, PROVEN) */

extern unsigned long long assert_post_action(unsigned int,unsigned int);
extern void printk(unsigned int,unsigned int,unsigned int,unsigned int);
void FUN_00064fa8(unsigned int param_1,int param_2,unsigned int param_3,unsigned int param_4)
{
  if (param_2 == 0) {
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f6a46) /*=0xf6a46*/,((unsigned long)&rodata_f6a09) /*=0xf6a09*/,0x5c);
    param_2 = (int)(assert_post_action(((unsigned long)&rodata_f6a09) /*=0xf6a09*/,0x5c) >> 32);
  }
  *(unsigned int *)(param_2 + 0x80) = 0;
  return;
}
