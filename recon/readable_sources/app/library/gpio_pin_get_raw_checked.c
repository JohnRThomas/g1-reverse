#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_gpio_pin_get_raw_ctx__param_0030       [param_0030; G1-original]
 * Raw function identity: 0x000177c4.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000177c4 @ 0x000177c4
 * public-name: gpio_pin_get_raw_checked
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_pin_get_raw_checked                 <= FUN_000177c4 @ 0x000177c4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99c53                             @ 0x00099c53
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_99de0                             @ 0x00099de0
 *   rodata_99e1e                             @ 0x00099e1e
 */
/* Reconstructed FUN_000177c4 @ 0x177c4  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int, unsigned int, unsigned int, unsigned int);
extern void assert_post_action(unsigned int, unsigned int);
typedef int (*fnptr)(int, unsigned int*, unsigned int, void*, int);

int gpio_pin_get_raw_checked(char *param_1, unsigned int param_2)
{
  unsigned int uVar3 = 1u << (param_2 & 0xff);
  unsigned int local_c = param_2;
  if ((uVar3 & **(unsigned int**)(param_1+4)) == 0) {
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_99de0) /*=0x99de0*/, ((unsigned long)&rodata_99c53) /*=0x99c53*/, 0x5d1);
    printk(((unsigned long)&rodata_99e1e) /*=0x99e1e*/, 0, 0, 0);
    assert_post_action(((unsigned long)&rodata_99c53) /*=0x99c53*/, 0x5d1);
  }
  fnptr pcVar2 = *(fnptr*)(*(int*)(param_1+8)+4);
  int iVar1 = pcVar2((int)param_1, &local_c, **(unsigned int**)(param_1+4), (void*)pcVar2, (int)param_1);
  if (iVar1==0) {
    iVar1 = (uVar3 & local_c)!=0 ? 1:0;
  }
  return iVar1;
}
