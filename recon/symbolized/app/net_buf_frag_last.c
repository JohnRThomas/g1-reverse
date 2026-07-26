#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005f304 @ 0x0005f304
 * public-name: net_buf_frag_last
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_frag_last                        <= FUN_0005f304 @ 0x0005f304
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f45be                             @ 0x000f45be
 *   rodata_f539a                             @ 0x000f539a
 */
/* Reconstructed FUN_0005f304 @ 0x5f304  (parity: 300/300 trials, PROVEN) */

extern int printk(unsigned int a,unsigned int b,unsigned int c,unsigned int d,unsigned int e);
extern int assert_post_action(unsigned int a,unsigned int b);

int net_buf_frag_last(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  if (param_1 == 0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f45be) /*=0xf45be*/, ((unsigned long)&rodata_f539a) /*=0xf539a*/, 0x236, param_4);
    assert_post_action(((unsigned long)&rodata_f539a) /*=0xf539a*/, 0x236);
    return 0x236;
  }
  do {
    iVar1 = param_1;
    param_1 = *(int*)(param_1+4);
  } while (param_1 != 0);
  return iVar1;
}
